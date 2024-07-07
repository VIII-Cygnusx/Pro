/***********************************************************************************************************************************************************************************************************
* @brief  外部端口线，中断，与内部通信函数接口
* @author VIII-Cygnusx
* @date 2024 2/16
* @version 1.0.0-TEST
***********************************************************************************************************************************************************************************************************/
#include "ov7725_interface.h"  
#include "stm32u5xx_it.h"

struct ov7725_hw_interface_conf ov7725_hw={.D0_PORT=D0_GPIO_Port,
                                           .D1_PORT=D1_GPIO_Port,
                                           .D2_PORT=D2_GPIO_Port,  
                                           .D3_PORT=D3_GPIO_Port,     
                                           .D4_PORT=D4_GPIO_Port,     
                                           .D5_PORT=D5_GPIO_Port,                                           
                                           .D6_PORT=D6_GPIO_Port,   
                                           .D7_PORT=D7_GPIO_Port,
                                           .WRST_PORT=WRST_GPIO_Port,    
                                           .RRST_PORT=RRST_GPIO_Port, 
                                           .WEN_PORT=WEN_GPIO_Port,  
                                           .VSYNC_PORT=VSYNC_GPIO_Port,                                                                                                                                                                     
                                           .RCLK_PORT=RCLK_GPIO_Port,
                                           .OE_PORT=OE_GPIO_Port,
                                           .D0=D0_Pin,
                                           .D1=D1_Pin,
                                           .D2=D2_Pin,
                                           .D3=D3_Pin,
                                           .D4=D4_Pin,
                                           .D5=D5_Pin,
                                           .D6=D6_Pin,     
                                           .D7=D7_Pin,
                                           .WRST=WRST_Pin,
                                           .RRST=RRST_Pin,
                                           .WEN=WEN_Pin,
                                           .VSYNC=VSYNC_Pin,
                                           .RCLK=RCLK_Pin,
                                           .OE=OE_Pin,
                                           .delay=&HAL_Delay,
                                           .read=&read_reg,
                                           .write=&write_reg,
                                           .v_interrupt=&EXTI0_IRQHandler
};




/**
 * @brief       VSYNC外部中断服务函数
 * @warning     如果此处报错请删除stm32f1xx_it.c里面名字一样的函数
 * @param       无
 * @retval      无
 */
void EXTI0_IRQHandler(void)
{
    
    if (__HAL_GPIO_EXTI_GET_IT(ov7725_hw.VSYNC) != RESET)
    {
        if (image.frame.handle_flag == FRAME_HANDLE_DONE)
        {
            OV7725_WRST(0);
            OV7725_WEN(1);
            OV7725_WRST(1);
            image.frame.handle_flag = FRAME_HANDLE_PEND;
            
        }
        else
        {
            OV7725_WEN(0);
        }
        
        __HAL_GPIO_EXTI_CLEAR_IT(ov7725_hw.VSYNC);
    }
}

