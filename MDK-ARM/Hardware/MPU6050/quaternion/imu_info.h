#ifndef IMU_INFO_H_
#define IMU_INFO_H_

#include "mpu6050_interface.h"

struct imu_data
{
    float pitch;
    float yaw;
    float roll;

    float ACC_X;
    float ACC_Y;
    float ACC_Z;

    float GYR_X;
    float GYR_Y;
    float GYR_Z;
    uint8_t read_buf[14];
};

struct Quaternion{
  volatile float w;
  volatile float q1;
  volatile float q2;
  volatile float q3;
};

struct V{
	volatile float x;
	volatile float y;
	volatile float z;
	};

struct _1_ekf_filter
{
	float LastP;
	float Now_P;
	float out;
	float Kg;
	float Q;
	float R;	
};

struct imu_info
{
    enum{
        _2G_ =0X00<<3,
        _4G_ =0X01<<3,
        _8G_ =0x02<<3,
        _16G_=0x03<<3,
    }ACC_range;

    enum{
        _250dps_ =0X00<<3,
        _500dps_ =0X01<<3,
        _1000dps_=0X02<<3,
        _2000dps_=0X03<<3,
    }GYRO_range;
  
    enum{
        _A260_1K_G256_8K_ =0X00,
        _A184_1K_G188_1K_,
        _A94_1K_G98_1K_,
        _A44_1K_G42_1K_,
        _A21_1K_G20_1K_,
        _A10_1K_G10_1K_,
        _A5_1K_G5_1K_,
    }DLPF;
   
    enum{
        _8MRC_ =0X00,
        _XPLL_,         //X-Axis Gyroscope timer
        _YPLL_,         //Y-Axis Gyroscope timer
        _ZPLL_,         //Z-Axis Gyroscope timer
    }CLOCK;
};

extern struct _1_ekf_filter ekf[6];		//存放卡尔曼滤波参数
extern struct imu_data IMU_data;
extern struct imu_info IMU_conf;
extern struct Quaternion Q;
#endif