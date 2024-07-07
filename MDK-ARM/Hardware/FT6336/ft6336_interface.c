/**
 * @file ft6336_interface.c
 * @author CygnusX_VIII (13509485575@163.com)
 * @brief FT6336
 *        IO:(EXIT_pin)
 *              MODE: External Interrupt Mode with Falling edge trigger
 *              PULL: Pull-up 
 *        IO:(Reset_pin)
 *              MODE: Output Push Pull
 *              PULL: NO Pull-up & Pull-down
 *        IIC:
 *              SPEED: 1000khz
 *        
 *                  
 * @version 0.1
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ft6336_interface.h"

uint8_t FT6336_readByte(uint8_t addr);
void RES_pin(uint8_t num);

struct ft6336_interface ft6336={.RES_PORT   =GPIOA,
                                .RES_PIN    =GPIO_PIN_11,
                                .EXIT_PORT  =GPIOB,
                                .EXTI_PIN   =GPIO_PIN_5,
                                .Read       =FT6336_readByte,
                                .MS         =HAL_Delay,
                                .RES        =RES_pin


};

//Template

uint8_t FT6336_readByte(uint8_t addr)
{
    uint8_t data;
		HAL_I2C_Master_Transmit(&hi2c1,FT6336_ADDR_WRITE,&addr,1,10);
		HAL_I2C_Master_Receive (&hi2c1,FT6336_ADDR_READ ,&data,1,10);	  
    return data;
}

void RES_pin(uint8_t num){
    num?(ft6336.RES_PORT->BSRR = ft6336.RES_PIN) : (ft6336.RES_PORT->BRR = ft6336.RES_PIN);
}





