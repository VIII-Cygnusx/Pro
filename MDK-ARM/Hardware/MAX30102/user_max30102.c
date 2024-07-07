/**
  ******************************************************************************
  * @file   user_app.c
  * @brief  用户应用程序部分的代码
  * 
  ******************************************************************************
  */
#include "string.h"
#include "math.h"
//
#include "user_max30102.h"
/***************************心率血氧传感器***************************/
float n_temperature;


#define MAX_BRIGHTNESS 255
//


/**
 * @brief 计算心率（Heart Rate）和血氧饱和度（Oxygen Saturation，简称SpO2）
 * 
 * @param pun_ir_buffer 这个缓冲区存储了一段时间内采集到的红外光强度样本
 * @param n_ir_buffer_length 红外光数据样本数量
 * @param pun_red_buffer 红光的吸收情况
 * @param pn_spo2 输出计算得到的血氧饱和度百分比值
 * @param pch_spo2_valid 血氧饱和度计算是否有效 1表示有效
 * @param pn_heart_rate 输出计算得到的心率值
 * @param pch_hr_valid 心率计算是否有效  1表示有效
 */
extern void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer,  int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, 
																									 int32_t *pn_heart_rate, int8_t  *pch_hr_valid);


	



uint32_t aun_ir_buffer[MAX30102_BUFF_LENGTH]; //IR LED sensor data
int32_t n_ir_buffer_length;    //data length
uint32_t aun_red_buffer[MAX30102_BUFF_LENGTH];    //Red LED sensor data
int32_t n_sp02; //SPO2 value
int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
int32_t n_heart_rate;   //heart rate value
int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid
uint8_t uch_dummy;
