#include "ft6336_api_lib.h"
/*
**********************************************************************
* @fun     :FT6336_init 
* @brief   :FT6336初始化函数
* @param   :None
* @return  :None 
**********************************************************************
*/
void FT6336_init(void)
{

        ft6336.RES(0);
        ft6336.MS(10);
        ft6336.RES(1);
        ft6336.MS(100);
}

/*
**********************************************************************
* @fun     :FT6336_read_touch1_x 
* @brief   :读取touch1的数据
* @param   :None
* @return  :None 
**********************************************************************
*/

uint8_t touch_num(void)
{
    return ft6336.Read(FT6336_ADDR_TD_STATUS);
}




uint16_t FT6336_read_touch1_x(void)
{
    uint8_t read_buf[2];
    read_buf[0] = ft6336.Read(FT6336_ADDR_TOUCH1_X);
    read_buf[1] = ft6336.Read(FT6336_ADDR_TOUCH1_X + 1);
    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}
//
uint16_t FT6336_read_touch1_y(void)
{
    uint8_t read_buf[2];
    read_buf[0] = ft6336.Read(FT6336_ADDR_TOUCH1_Y);
    read_buf[1] = ft6336.Read(FT6336_ADDR_TOUCH1_Y + 1);
    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}
uint16_t FT6336_read_touch2_x(void)
{
    uint8_t read_buf[2];
    read_buf[0] = ft6336.Read(FT6336_ADDR_TOUCH2_X);
    read_buf[1] = ft6336.Read(FT6336_ADDR_TOUCH2_X + 1);
    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}
//
uint16_t FT6336_read_touch2_y(void)
{
    uint8_t read_buf[2];
    read_buf[0] = ft6336.Read(FT6336_ADDR_TOUCH2_Y);
    read_buf[1] = ft6336.Read(FT6336_ADDR_TOUCH2_Y + 1);
    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}




uint16_t xDiff = 0,yDiff = 0;	
static uint16_t pI_Touch_X = 0, pI_Touch_Y = 0;
/**
 * @brief 
 * 
 * @param touchway 
 */
void FT6336_scan()
{
        touch.touch_count=touch_num();
        if(touch.touch_count==1){
            touch.tp[0].x = FT6336_read_touch1_x();
            touch.tp[0].y = FT6336_read_touch1_y();
        }
        if(touch.touch_count==2){
            touch.tp[0].x = FT6336_read_touch1_x();
            touch.tp[0].y = FT6336_read_touch1_y();
            touch.tp[1].x = FT6336_read_touch2_x();
            touch.tp[1].y = FT6336_read_touch2_y();        
        }        
}



