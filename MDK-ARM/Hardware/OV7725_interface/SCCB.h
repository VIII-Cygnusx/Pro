#ifndef SCCB_H_
#define SCCB_H_
///////////////////////////////////////////////////////////////////////////////////////////
#include "gpio.h"
#include "main.h"
///////////////////////////////////////////////////////////////////////////////////////////
typedef void (*SCCB_delay)(uint32_t Delay);

struct SCCB
{
    SCCB_delay delay;
    GPIO_TypeDef * SCL_PORT;
    GPIO_TypeDef * SDA_PORT;
    uint16_t SDA;
    uint16_t SCL;

};


extern struct SCCB sccb_hw;


#define SCCB_SDA(x)  do{ x ?                                                                                         \
                            HAL_GPIO_WritePin(sccb_hw.SDA_PORT , sccb_hw.SDA ,GPIO_PIN_SET) :  \
                            HAL_GPIO_WritePin(sccb_hw.SDA_PORT , sccb_hw.SDA ,GPIO_PIN_RESET);   \
                        }while(0)
#define SCCB_SCL(x)   do{ x ?                                                                                         \
                            HAL_GPIO_WritePin(sccb_hw.SCL_PORT , sccb_hw.SCL   ,GPIO_PIN_SET) :  \
                            HAL_GPIO_WritePin(sccb_hw.SCL_PORT , sccb_hw.SCL   ,GPIO_PIN_RESET);   \
                        }while(0)
#define SCCB_READ_SDA()   HAL_GPIO_ReadPin(sccb_hw.SDA_PORT,sccb_hw.SDA)
#define SCCB_GPIO_PULLUP 1
#define SCCB_WRITE  0x00
#define SCCB_READ   0x01
#define SCCB_ADDR   0x21
uint8_t read_reg(uint8_t reg);
void write_reg(uint8_t reg, uint8_t dat);
#endif

