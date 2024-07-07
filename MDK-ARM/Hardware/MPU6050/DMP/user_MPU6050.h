/**
  ******************************************************************************
  * @file   user_app.h
  * @brief  用户应用程序部分的代码
  * 
  ******************************************************************************
  */
#ifndef __USER_MPU6050_H__
#define __USER_MPU6050_H__
//
#include "stdio.h"  //串口实现Printf打印输出

//MPU605的DMP应用
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

// Retrieve year info
#define OS_YEAR     ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
                                    + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))

// Retrieve month info
#define OS_MONTH    (__DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
                                : __DATE__ [2] == 'b' ? 2 \
                                : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
                                : __DATE__ [2] == 'y' ? 5 \
                                : __DATE__ [2] == 'l' ? 7 \
                                : __DATE__ [2] == 'g' ? 8 \
                                : __DATE__ [2] == 'p' ? 9 \
                                : __DATE__ [2] == 't' ? 10 \
                                : __DATE__ [2] == 'v' ? 11 : 12)

// Retrieve day info
#define OS_DAY      ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
                                + (__DATE__ [5] - '0'))

// Retrieve hour info
#define OS_HOUR     ((__TIME__ [0] - '0') * 10 + (__TIME__ [1] - '0'))

// Retrieve minute info
#define OS_MINUTE   ((__TIME__ [3] - '0') * 10 + (__TIME__ [4] - '0'))

// Retrieve second info
#define OS_SECOND   ((__TIME__ [6] - '0') * 10 + (__TIME__ [7] - '0'))

extern float PITCH,YAW,ROLL;
extern unsigned int gSportStep;	//运动步数
extern unsigned int gSportTime;	//运动时间

void mpu_init_dmp(void);
void Update_EulerAngle(void);
void Update_step();
#endif /* __USER_APP_H__ */

