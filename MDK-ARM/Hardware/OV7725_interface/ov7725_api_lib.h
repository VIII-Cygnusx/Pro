#ifndef OV7725_API_LIB_H_
#define OV7725_API_LIB_H_
///////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include "image_info.h"
///////////////////////////////////////////////////////////////////////////////////////////
#define OV7725_WRST(x)  x ? HAL_GPIO_WritePin(ov7725_hw.WRST_PORT , ov7725_hw.WRST ,GPIO_PIN_SET) : HAL_GPIO_WritePin(ov7725_hw.WRST_PORT , ov7725_hw.WRST ,GPIO_PIN_RESET);
#define OV7725_RRST(x)  x ? HAL_GPIO_WritePin(ov7725_hw.RRST_PORT , ov7725_hw.RRST ,GPIO_PIN_SET) : HAL_GPIO_WritePin(ov7725_hw.RRST_PORT , ov7725_hw.RRST ,GPIO_PIN_RESET);   
#define OV7725_OE(x)    x ? HAL_GPIO_WritePin(ov7725_hw.OE_PORT   , ov7725_hw.OE   ,GPIO_PIN_SET) : HAL_GPIO_WritePin(ov7725_hw.OE_PORT   , ov7725_hw.OE   ,GPIO_PIN_RESET);
#define OV7725_RCLK(x)  x ? HAL_GPIO_WritePin(ov7725_hw.RCLK_PORT , ov7725_hw.RCLK ,GPIO_PIN_SET) : HAL_GPIO_WritePin(ov7725_hw.RCLK_PORT , ov7725_hw.RCLK ,GPIO_PIN_RESET);
#define OV7725_WEN(x)   x ? HAL_GPIO_WritePin(ov7725_hw.WEN_PORT  , ov7725_hw.WEN  ,GPIO_PIN_SET) : HAL_GPIO_WritePin(ov7725_hw.WEN_PORT  , ov7725_hw.WEN  ,GPIO_PIN_RESET);


/* 错误代码 */
#define EOK      0   /* 没有错误 */
#define EERROR   1   /* 错误 */
#define EINVAL   2   /* 非法参数 */
#define EEMPTY   3   /* 资源为空 */
/*7725F模块制造商ID和产品ID */
#define MID 0x7FA2
#define PID 0x7721


uint8_t OV7725_manufacture_id(void); //获取制造商ID
uint8_t OV7725_product_id(void);     //获取产品ID
void OV7725_reset_v(void);              //reg复位
void OV7725_init_all_reg_v(void);       //配置所有寄存器位
/*↑↑↑上面的函数都在这里面*/
void OV7725_init_v(void);                                                   /* 初始7725F模块 */
void disable_output_image(void);                                            /* 失能7725F模块输出图像 */
void enable_output_image(void);                                             /* 使能7725F模块输出图像 */
uint8_t set_special_effect(void);       /* 设置7725F模块特殊效果 */
uint8_t set_contrast(void);             /* 设置7725F模块对比度 */
uint8_t set_output(void);               /* 设置7725F模块输出模式与尺寸*/
uint8_t set_light_mode(void);           /* 设置7725F模块灯光模式 */
uint8_t set_color_saturation(void);     /* 设置7725F模块色彩饱和度 */
uint8_t set_brightness(void);           /* 设置7725F模块亮度 */
void get_frame();
void send_frame2LCD(uint16_t x,uint16_t y);
void ov7725_test(void);                                                     /* 测试7725F */
#endif

