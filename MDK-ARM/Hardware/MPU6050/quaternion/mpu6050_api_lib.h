#ifndef MPU6050_API_LIB_H_
#define MPU6050_API_LIB_H_

#define LPF_1_(hz,t,in,out) ((out) += ( 1 / ( 1 + 1 / ( (hz) *6.2831853071795864769252867665F *(t) ) ) ) *( (in) - (out) ))	//低通滤波
#include "mpu6050_interface.h"

void MPU6050_init();
void MPU6050_offset();
void MPU6050_get_raw_data();
void MPU6050_get_Quaternion();
void MPU6050_get_Eular_angle();
#endif