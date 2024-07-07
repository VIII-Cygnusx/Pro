#include "mpu6050_api_lib.h"

//test
#include "usart.h"
#include <stdio.h>
#include "ANTOTC.h"
//

static float ACC_factor;
static float GYro_factor;
static float acxo,acyo,gyxo,gyyo,gyzo;
void MPU6050_init()
{
//        if(IMU.R_B(WHO_AM_I) == )
        IMU.W_B(PWR_MGMT_1,     0X80);          //RESET
        IMU.MS(100);
        IMU.W_B(PWR_MGMT_1,     0X00);          //weak up
        

        IMU.W_B(CONFIG,         IMU_conf.DLPF);         //acc&gyro带宽
        IMU.W_B(SMPLRT_DIV,     0x13);                  //50hz     (1000/(19+1))
        IMU.W_B(ACCEL_CONFIG,   IMU_conf.ACC_range);          //accelerate config     0，±2g；1，±4g；2，±8g；3，±16g
        IMU.W_B(GYRO_CONFIG,    IMU_conf.GYRO_range);          //gyro config   0，±250°/S；1，±500°/S；2，±1000°/S；3，±2000°/S
        
        IMU.W_B(PWR_MGMT_1,     IMU_conf.CLOCK);
        IMU.W_B(PWR_MGMT_2,     0X00);


        if(IMU_conf.ACC_range == _2G_) ACC_factor  = 16384.0f;
        if(IMU_conf.ACC_range == _4G_) ACC_factor  = 8192.0f;
        if(IMU_conf.ACC_range == _8G_) ACC_factor  = 4096.0f;
        if(IMU_conf.ACC_range == _16G_) ACC_factor = 2048.0f;

        if(IMU_conf.GYRO_range == _250dps_)  GYro_factor  = 131.0f;
        if(IMU_conf.GYRO_range == _500dps_)  GYro_factor  = 65.5f;
        if(IMU_conf.GYRO_range == _1000dps_) GYro_factor  = 32.8f;
        if(IMU_conf.GYRO_range == _2000dps_) GYro_factor  = 16.4f;


}

void MPU6050_offset(){
	IMU.MS(3000);
    float acx,acy,gyx,gyy,gyz;
    IMU.R_BL(ACCEL_XOUT_H,IMU_data.read_buf,14);
    acxo = ((int16_t)(IMU_data.read_buf[0]<<8  | IMU_data.read_buf[1]))/ACC_factor;     
    acyo = ((int16_t)(IMU_data.read_buf[2]<<8  | IMU_data.read_buf[3]))/ACC_factor;

    gyxo = ((int16_t)(IMU_data.read_buf[8]<<8  | IMU_data.read_buf[9]))/GYro_factor;     
    gyyo = ((int16_t)(IMU_data.read_buf[10]<<8 | IMU_data.read_buf[11]))/GYro_factor;
    gyzo = ((int16_t)(IMU_data.read_buf[12]<<8 | IMU_data.read_buf[13]))/GYro_factor;
}

void MPU6050_get_raw_data(){
    IMU.R_BL(ACCEL_XOUT_H,IMU_data.read_buf,14);
    IMU_data.ACC_X = ((int16_t)(IMU_data.read_buf[0 ]<<8  | IMU_data.read_buf[1 ]))/ACC_factor-acxo;   
    IMU_data.ACC_Y = ((int16_t)(IMU_data.read_buf[2 ]<<8  | IMU_data.read_buf[3 ]))/ACC_factor-acyo;
    IMU_data.ACC_Z = ((int16_t)(IMU_data.read_buf[4 ]<<8  | IMU_data.read_buf[5 ]))/ACC_factor;
    IMU_data.GYR_X = ((int16_t)(IMU_data.read_buf[8 ]<<8  | IMU_data.read_buf[9 ]))/GYro_factor-gyxo;    
    IMU_data.GYR_Y = ((int16_t)(IMU_data.read_buf[10]<<8  | IMU_data.read_buf[11]))/GYro_factor-gyyo;
    IMU_data.GYR_Z = ((int16_t)(IMU_data.read_buf[12]<<8  | IMU_data.read_buf[13]))/GYro_factor-gyzo;
    LPF_1_(4.0f,0.02f,IMU_data.ACC_X,IMU_data.ACC_X);
    LPF_1_(4.0f,0.02f,IMU_data.ACC_Y,IMU_data.ACC_Y);
    LPF_1_(4.0f,0.02f,IMU_data.ACC_Z,IMU_data.ACC_Z);
    LPF_1_(4.0f,0.02f,IMU_data.GYR_X,IMU_data.GYR_X);
    LPF_1_(4.0f,0.02f,IMU_data.GYR_Y,IMU_data.GYR_Y);
    LPF_1_(4.0f,0.02f,IMU_data.GYR_Z,IMU_data.GYR_Z);
    //........//
    ANTO_Send(ANTO_IMU);
    //........//
}


void kalman_1(struct _1_ekf_filter *ekf,float input)  //һά������
{
	ekf->Now_P = ekf->LastP + ekf->Q;
	ekf->Kg = ekf->Now_P / (ekf->Now_P + ekf->R);
	ekf->out = ekf->out + ekf->Kg * (input - ekf->out);
	ekf->LastP = (1-ekf->Kg) * ekf->Now_P ;
}

//50HZ
volatile	 struct V GyroIntegError = {0}; 
float KpDef = 200.0f ; //200.0f
float KiDef = 0.002f;  //0.002d
void MPU6050_get_Quaternion(){
    float AX,AY,AZ,GX,GY,GZ;
    //LSB->g
    AX = IMU_data.ACC_X;
    AY = IMU_data.ACC_Y;
    AZ = IMU_data.ACC_Z;
    //LSB->deg/s
    GX = IMU_data.GYR_X;
    GY = IMU_data.GYR_Y;
    GZ = IMU_data.GYR_Z;
    //low pass filter rate:200hz pass:1hz

//  kalman_1(&ekf[0],AX);AX=ekf[0].out;
//	kalman_1(&ekf[1],AY);AY=ekf[1].out;
//	kalman_1(&ekf[2],AZ);AZ=ekf[2].out;
//	kalman_1(&ekf[3],GX);GX=ekf[3].out;
//	kalman_1(&ekf[4],GY);GY=ekf[4].out;
//	kalman_1(&ekf[5],GZ);GZ=ekf[5].out;	

    volatile struct V Gravity,Acc,Gyro,AccGravity;
    float NormAcc;	
    float NormQuat; 
    float HalfTime = 0.02f * 0.5f;
    NormAcc=Q_rsqrt(pow_(AX)+pow_(AY)+pow_(AZ));
    Acc.x = AX*NormAcc;
    Acc.y = AY*NormAcc;
    Acc.z = AZ*NormAcc;

        Gravity.x = 2*(Q.q1 * Q.q3 - Q.w * Q.q2);                      //[2][0]             
        Gravity.y = 2*(Q.w * Q.q1 + Q.q2 * Q.q3);			//[2][1]  
        Gravity.z = 1-2*(Q.q1 * Q.q1 + Q.q2 * Q.q2);		//[2][2]	

        AccGravity.x += (Acc.y * Gravity.z - Acc.z * Gravity.y);			//ex p
        AccGravity.y += (Acc.z * Gravity.x - Acc.x * Gravity.z);
        AccGravity.z += (Acc.x * Gravity.y - Acc.y * Gravity.x);

        GyroIntegError.x += AccGravity.x * KiDef* 0.02f;                     //in i
        GyroIntegError.y += AccGravity.y * KiDef* 0.02f;
        GyroIntegError.z += AccGravity.z * KiDef* 0.02f;

        Gyro.x += GX + KpDef * AccGravity.x  +  GyroIntegError.x;//������
        Gyro.y += GY + KpDef * AccGravity.y  +  GyroIntegError.y;
        Gyro.z += GZ + KpDef * AccGravity.z  +  GyroIntegError.z;		

        Q.w +=(-Q.q1*Gyro.x - Q.q2*Gyro.y - Q.q3*Gyro.z) * HalfTime;
        Q.q1 +=( Q.w*Gyro.x - Q.q3*Gyro.y + Q.q2*Gyro.z) * HalfTime;
        Q.q2 +=( Q.q3*Gyro.x + Q.w*Gyro.y - Q.q1*Gyro.z) * HalfTime;
        Q.q3 +=(-Q.q2*Gyro.x + Q.q1*Gyro.y + Q.w*Gyro.z) * HalfTime;

        NormQuat = Q_rsqrt(pow_(Q.w) + pow_(Q.q1) + pow_(Q.q2) + pow_(Q.q3));
            Q.w *= NormQuat;
            Q.q1 *= NormQuat;
            Q.q2 *= NormQuat;
            Q.q3 *= NormQuat;

    //........//
    ANTO_Send(ANTO_QUA);
    //........//
}

void MPU6050_get_Eular_angle(){
	{
		 
			#ifdef	YAW_GYRO
				Angle.yaw = atan2f(2 * NumQ.q1 *NumQ.q2 + 2 * NumQ.q0 * NumQ.q3, 1 - 2 * NumQ.q2 *NumQ.q2 - 2 * NumQ.q3 * NumQ.q3) * RtA;  //yaw
			#else
				float yaw_G = IMU_data.GYR_Z/GYro_factor;
				if((yaw_G > 0.5f) || (yaw_G < -0.5f)) 
				{
					IMU_data.yaw  -= yaw_G * 0.02f;			
				}
			#endif				
			IMU_data.pitch = -RAD2DEG(fast_sin(2 * Q.w *Q.q2 - 2 * Q.q1 * Q.q3));
			IMU_data.roll  = -RAD2DEG(atan2_approx(2 * Q.q2 *Q.q3 + 2 * Q.w * Q.q1, 1 - 2 * Q.q1 *Q.q1 - 2 * Q.q2 * Q.q2));  
			
	}
    //........//
    ANTO_Send(ANTO_STATUS);
    //........//
}