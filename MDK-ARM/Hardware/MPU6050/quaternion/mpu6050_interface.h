#ifndef MPU6050_INTERFACE_H_
#define MPU6050_INTERFACE_H_

#include "main.h"
#include "i2c.h"
#include "mpu6050_api_lib.h"
#include "mpu6050_reg_lib.h"
#include "imu_info.h"
#include "myMath.h"
typedef void (*delay)(uint32_t ms);
typedef uint8_t (*iic_rb)(uint8_t add);
typedef void (*iic_wb)(uint8_t add,uint8_t data);
typedef void (*iic_rbl)(uint8_t add,uint8_t *data,uint8_t len);
typedef void (*iic_wbl)(uint8_t add,uint8_t* data,uint8_t len);
struct mpu6050_interface
{
    iic_rb      R_B;
    iic_rbl     R_BL;
    iic_wb      W_B;
    iic_wbl     W_BL;
    delay       MS;
};
extern struct mpu6050_interface IMU;

#endif