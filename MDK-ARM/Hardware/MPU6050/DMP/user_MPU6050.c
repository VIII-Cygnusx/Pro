/**
  ******************************************************************************
  * @file   user_app.c
  * @brief  用户应用程序部分的代码
  * 
  ******************************************************************************
  */
#include "string.h"
#include "math.h"
#include "stm32u5xx_hal.h"
//
#include "user_MPU6050.h"
/****************************姿态与运动检测***************************/
#define MPU6050_DMP_ENABLE
//
#ifdef MPU6050_DMP_ENABLE
//dmp相关参数设置
/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (10)

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)

#define MOTION          (0)
#define NO_MOTION       (1)
//
#define READ_MPU6050_DMP_QUAT
//
#ifdef READ_MPU6050_DMP_QUAT
//q30格式,long转float时的除数
#define q30  1073741824.0f
//需要读取的数据

//全局数据
float PITCH,YAW,ROLL;
unsigned long pSportStep = 0;	//运动步数
unsigned long pSportTime = 0;	//运动时间
//全局数据

short aacx,aacy,aacz;			//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
#endif
unsigned int gSportStep = 0;	//运动步数
unsigned int gSportTime = 0;	//运动时间
//初始化过程中相关参数
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
};
static struct hal_s hal = {0};
/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from thei
 * driver(s).
 * TODO: The following matrices refer to the configuration on an internal test
 * board at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};
#endif



#ifdef MPU6050_DMP_ENABLE
/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}
static inline unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}
/*
**********************************************************************
* @fun     :mpu_init_dmp 
* @brief   :初始化dmp
* @param   :
* @return  :None 
**********************************************************************
*/
void mpu_init_dmp(void)
{
	int dmp_Init_Fail = 0;	//mpu6050初始化是否成功
	unsigned char accel_fsr;
	unsigned short gyro_rate, gyro_fsr;
  //unsigned long timestamp;
	//
	dmp_Init_Fail = mpu_init();  //失败返回1，成功返回O
	//
	while(dmp_Init_Fail)	
	{
		dmp_Init_Fail = mpu_init();	
		HAL_Delay(10);
	}
	
  /* Get/set hardware configuration. Start gyro. */
  /* Wake up all sensors. */
  mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);	//配置陀螺仪和加速计传感器的时钟和工作状态函数
  /* Push both gyro and accel data into the FIFO. */
  mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);	//配置陀螺仪和加速计开启FIFO通道函数
  mpu_set_sample_rate(DEFAULT_MPU_HZ);	//配置默认的采样率
  /* Read back configuration in case it was set improperly. */
  mpu_get_sample_rate(&gyro_rate);	//获得陀螺仪采样频率范围
  mpu_get_gyro_fsr(&gyro_fsr);	//获得陀螺仪全尺寸范围
  mpu_get_accel_fsr(&accel_fsr);	//获得加速计全尺寸范围

  /* Initialize HAL state variables. */
  memset(&hal, 0, sizeof(hal));	//初始化hal的变量
  hal.sensors = ACCEL_ON | GYRO_ON;	//标志位-"开启传感器"设置为加速计和陀螺仪

  /* To initialize the DMP:
   * 1. Call dmp_load_motion_driver_firmware(). This pushes the DMP image in
   *    inv_mpu_dmp_motion_driver.h into the MPU memory.
   * 2. Push the gyro and accel orientation matrix to the DMP.
   * 3. Register gesture callbacks. Don't worry, these callbacks won't be
   *    executed unless the corresponding feature is enabled.
   * 4. Call dmp_enable_feature(mask) to enable different features.
   * 5. Call dmp_set_fifo_rate(freq) to select a DMP output rate.
   * 6. Call any feature-specific control functions.
   *
   * To enable the DMP, just call mpu_set_dmp_state(1). This function can
   * be called repeatedly to enable and disable the DMP at runtime.
   *
   * The following is a short summary of the features supported in the DMP
   * image provided in inv_mpu_dmp_motion_driver.c:
   * DMP_FEATURE_LP_QUAT: Generate a gyro-only quaternion on the DMP at
   * 200Hz. Integrating the gyro data at higher rates reduces numerical
   * errors (compared to integration on the MCU at a lower sampling rate).
   * DMP_FEATURE_6X_LP_QUAT: Generate a gyro/accel quaternion on the DMP at
   * 200Hz. Cannot be used in combination with DMP_FEATURE_LP_QUAT.
   * DMP_FEATURE_TAP: Detect taps along the X, Y, and Z axes.
   * DMP_FEATURE_ANDROID_ORIENT: Google's screen rotation algorithm. Triggers
   * an event at the four orientations where the screen should rotate.
   * DMP_FEATURE_GYRO_CAL: Calibrates the gyro data after eight seconds of
   * no motion.
   * DMP_FEATURE_SEND_RAW_ACCEL: Add raw accelerometer data to the FIFO.
   * DMP_FEATURE_SEND_RAW_GYRO: Add raw gyro data to the FIFO.
   * DMP_FEATURE_SEND_CAL_GYRO: Add calibrated gyro data to the FIFO. Cannot
   * be used in combination with DMP_FEATURE_SEND_RAW_GYRO.
   */
	 dmp_load_motion_driver_firmware();	//加载DMP固件
   dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));	//推送陀螺仪和加速度计的方向矩阵到DMP
		//
   hal.dmp_features =   DMP_FEATURE_6X_LP_QUAT      | DMP_FEATURE_TAP               |
                        DMP_FEATURE_ANDROID_ORIENT  | DMP_FEATURE_SEND_RAW_ACCEL    | 
                        DMP_FEATURE_SEND_CAL_GYRO   | DMP_FEATURE_GYRO_CAL;
       	//DMP的功能开启选项标志位设置
   dmp_enable_feature(hal.dmp_features);	//使能上述功能
   dmp_set_fifo_rate(DEFAULT_MPU_HZ);	//置DMP的FIFO速率
   mpu_set_dmp_state(1);	//开启DMP
   hal.dmp_on = 1;	//标志位"DMP状态"为开启
}
/*
**********************************************************************
* @fun     :mpu_get_dmp_data 
* @brief   :读取dmp的数据
* @param   :
* @return  :None 
**********************************************************************
*/
#include "myMath.h"
static void mpu_get_dmp_data(void)
{ 
	#ifdef READ_MPU6050_DMP_QUAT
	float q0=1.0f, q1=0.0f, q2=0.0f,q3=0.0f;
	unsigned long sensor_timestamp;
	short gyro[3], accel[3], sensors;
	unsigned char more;
	long quat[4];
	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);
	//
	// if (!more)	hal.new_gyro = 0;
	// if (sensors & INV_XYZ_GYRO)		{;}
	// if (sensors & INV_XYZ_ACCEL)	{;}
	if (sensors & INV_WXYZ_QUAT)
	{
		q0=quat[0] / q30;
		q1=quat[1] / q30;
		q2=quat[2] / q30;
		q3=quat[3] / q30;
		//
        PITCH	= fast_sin( (-2) * q1 * q3 + 2 * q0 * q2 ) * 57.3f;
		ROLL	= atan2_approx( 2 * q2 * q3 + 2 * q0 * q1 , (-2) * q1 * q1 - 2 * q2 * q2 + 1) * 57.3f;
		YAW 	= atan2_approx( 2 * (q1 * q2 + q0 * q3) , q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) * 57.3f;
	}
	#endif


}
#endif

/*
**********************************************************************
* @fun     :Update_EulerAngle 
* @brief   :更新欧拉角,并通过核心板USB转串口打印
* @param   :None
* @return  :None 
* @remark  :周期性调用-200mS运行一次
**********************************************************************
*/
//#include "ANTOTC.h"
void Update_EulerAngle(void)
{
	mpu_get_dmp_data(); 
	//输出系统时间
	//#ifdef DEBUG_MODE	
    // ANTO_Send(ANTO_STATUS);
	//#endif // DEBUG
}

void Update_step()
{
	//获取步数
	dmp_get_pedometer_step_count(&pSportStep);
	//dmp_get_pedometer_walk_time(&pSportTime);
	//
	gSportStep = pSportStep;
	//gSportTime = pSportTime;
}