/**
  ******************************************************************************
  * @file   user_app.h
  * @brief  用户应用程序部分的代码
  * 
  ******************************************************************************
  */
#ifndef __USER_MAX30102_H__
#define __USER_MAX30102_H__
//
#include "stdio.h"  //串口实现Printf打印输出

//MAX30102驱动文件
#include "max30102.h"
#define MAX30102_BUFF_LENGTH 200	//Defined in the "algorithm.h",MAX30102_BUFF_LENGTH = BUFFER_SIZE

extern uint32_t aun_ir_buffer[MAX30102_BUFF_LENGTH];		//
extern uint32_t aun_red_buffer[MAX30102_BUFF_LENGTH];

extern int32_t n_sp02; //SPO2 value
extern int32_t n_heart_rate;   //heart rate value


#endif /* __USER_APP_H__ */

