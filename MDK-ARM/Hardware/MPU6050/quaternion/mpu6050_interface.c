/**
 * @file mpu6050_interface.c
 * @author CygnusX_VIII (13509485575@163.com)
 * @brief
 * @version 0.1
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mpu6050_interface.h"

uint8_t MPU6050_RB(uint8_t add);
void MPU6050_RBL(uint8_t add,uint8_t *data,uint8_t len);
void MPU6050_WB(uint8_t add,uint8_t data);
void MPU6050_WBL(uint8_t add,uint8_t* data,uint8_t len);

struct mpu6050_interface IMU={  .MS     =   HAL_Delay,
                                .R_B    =   MPU6050_RB,
                                .R_BL   =   MPU6050_RBL,
                                .W_B    =   MPU6050_WB,
                                .W_BL   =   MPU6050_WBL,
};

uint8_t MPU6050_RB(uint8_t add)
{
    uint8_t RX;
    HAL_I2C_Mem_Read(&hi2c1,MPU6050_R,add,1,&RX,1,10);
    return RX;
}

void MPU6050_RBL(uint8_t add,uint8_t *data,uint8_t len)
{
    HAL_I2C_Mem_Read(&hi2c1,MPU6050_R,add,1,data,len,10);
}   

void MPU6050_WB(uint8_t add,uint8_t data)
{
    HAL_I2C_Mem_Write(&hi2c1,MPU6050_W,add,1,&data,1,10);
}

void MPU6050_WBL(uint8_t add,uint8_t* data,uint8_t len)
{
    HAL_I2C_Mem_Write(&hi2c1,MPU6050_W,add,1,data,len,10);
}