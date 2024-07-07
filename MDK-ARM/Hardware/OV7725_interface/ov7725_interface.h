#ifndef OV7725_INTERFACE_H_
#define OV7725_INTERFACE_H_
///////////////////////////////////////////////////////////////////////////////////////////
#include "SCCB.h"
#include "ov7725_api_lib.h"
//#include "usart.h"
///////////////////////////////////////////////////////////////////////////////////////////
//SCCB接口函数指针
typedef void (*VSYNC_iterrupt)(void);
typedef uint8_t (*SCCB_read)(uint8_t reg_addr);
typedef void (*SCCB_write)(uint8_t reg_addr, uint8_t data);
typedef void (*com_delay)(uint32_t Delay);
//OV7725摄像头端口与SCCB接口函数配置
struct ov7725_hw_interface_conf
{
    VSYNC_iterrupt v_interrupt;
    SCCB_read read;
    SCCB_write write;
    com_delay delay;
    GPIO_TypeDef * D0_PORT; 
    GPIO_TypeDef * D1_PORT;
    GPIO_TypeDef * D2_PORT;
    GPIO_TypeDef * D3_PORT;
    GPIO_TypeDef * D4_PORT;
    GPIO_TypeDef * D5_PORT;
    GPIO_TypeDef * D6_PORT;
    GPIO_TypeDef * D7_PORT;
    GPIO_TypeDef * WRST_PORT;
    GPIO_TypeDef * RRST_PORT;
    GPIO_TypeDef * RCLK_PORT;
    GPIO_TypeDef * VSYNC_PORT;
    GPIO_TypeDef * WEN_PORT;
    GPIO_TypeDef * OE_PORT;
    uint16_t D0;
    uint16_t D1; 
    uint16_t D2;
    uint16_t D3;
    uint16_t D4;
    uint16_t D5;
    uint16_t D6; 
    uint16_t D7;
    uint16_t WRST;
    uint16_t RRST;
    uint16_t RCLK;
    uint16_t VSYNC;
    uint16_t WEN;
    uint16_t OE;
};

//对外公共使用
extern struct ov7725_hw_interface_conf ov7725_hw;


#endif

