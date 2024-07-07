#include "screem_info.h"




static uint8_t DFT_SCAN_DIR; //扫描方向 
//管理ILI9341重要参数
struct _ILI9341_dev ILI9341dev;	
/*
**********************************************************************
* @fun     :ILI9341_Display_Dir 
* @brief   :设置ILI9341的自动扫描方向
							Memory Access Control (36h)
							This command defines read/write scanning direction of the frame memory.

							These 3 bits control the direction from the MPU to memory write/read.

							Bit  Symbol  Name  Description
							D7   MY  Row Address Order
							D6   MX  Column Address Order
							D5   MV  Row/Column Exchange
							D4   ML  Vertical Refresh Order  LCD vertical refresh direction control. 、

							D3   BGR RGB-BGR Order   Color selector switch control
										(0 = RGB color filter panel, 1 = BGR color filter panel )
							D2   MH  Horizontal Refresh ORDER  LCD horizontal refreshing direction control.
							D1   X   Reserved  Reserved
							D0   X   Reserved  Reserved
* @param   :
* @return  :None 
**********************************************************************
*/
void ILI9341_Display_Dir(enum screen_ShowDIR ShowDIR)
{
	uint16_t regval=0x08; //RGB-BGR Order不能改变
	uint8_t dirreg=0;
	
	if(ShowDIR == SCAN_Vertical)	//竖屏
	{
		ILI9341dev.width=240;
		ILI9341dev.height=320;
 
		ILI9341dev.wramcmd=0X2C;
		ILI9341dev.setxcmd=0X2A;
		ILI9341dev.setycmd=0X2B;  
    DFT_SCAN_DIR=L2R_U2D;		
		
		switch(DFT_SCAN_DIR)
		{
			case L2R_U2D://从左到右,从上到下  //竖屏
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_D2U://从右到左,从下到上   //竖屏
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
		}
	}else //横屏
	{	  				
		ILI9341dev.width=320;
		ILI9341dev.height=240;
 
		ILI9341dev.wramcmd=0X2C;
		ILI9341dev.setxcmd=0X2A;
		ILI9341dev.setycmd=0X2B;  
		DFT_SCAN_DIR=D2U_L2R;	
		
		switch(DFT_SCAN_DIR)
		{
			case U2D_R2L://从上到下,从右到左  //横屏
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://从下到上,从左到右  //横屏
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
		}
	}
	dirreg=0X36; 
  	regval|=0x00;	
	LCD.W_REG(dirreg);
	LCD.W_DATA(regval);
	//设置光标在原点位置		
	LCD.W_REG(ILI9341dev.setxcmd); 
	LCD.W_DATA(0);LCD.W_DATA(0);
	LCD.W_DATA((ILI9341dev.width-1)>>8);LCD.W_DATA((ILI9341dev.width-1)&0XFF);
	LCD.W_REG(ILI9341dev.setycmd); 
	LCD.W_DATA(0);LCD.W_DATA(0);
	LCD.W_DATA((ILI9341dev.height-1)>>8);LCD.W_DATA((ILI9341dev.height-1)&0XFF);  	
}


