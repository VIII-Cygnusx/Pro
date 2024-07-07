#ifndef SCREEM_INFO_H_
#define SCREEM_INFO_H_
#include "ili9341_interface.h"

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上
 
#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 



//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
// 
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)    

struct _ILI9341_dev
{										    
	uint16_t  width;	    //ili9341 宽度
	uint16_t  height;		//ili9341 高度
	uint16_t  id;			//ili9341 ID
	uint8_t	  wramcmd;		//开始写gram指令
	uint8_t   setxcmd;		//设置x坐标指令
	uint8_t   setycmd;		//设置y坐标指令	 
};
extern struct _ILI9341_dev ILI9341dev;	
//屏幕显示方式
enum screen_ShowDIR
{
  SCAN_Vertical= 0x00,  //竖屏
  SCAN_Horizontal,     	//横屏
} ;


void ILI9341_Display_Dir(enum screen_ShowDIR ShowDIR);	//设置屏幕显示方向



#endif