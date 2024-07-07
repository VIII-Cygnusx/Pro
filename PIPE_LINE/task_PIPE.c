#include "task_PIPE.h"
#include "user_MPU6050.h"
uint8_t PIPE_IMU=0;

extern void NNN();

// 
uint8_t Lock = 1;


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    UNUSED(GPIO_Pin);
    if(GPIO_Pin==ft6336.EXTI_PIN){
        FT6336_scan();
    }
}