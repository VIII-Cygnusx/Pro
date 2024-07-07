#ifndef ILI9341_API_H_
#define ILI9341_API_H_
#include "ili9341_interface.h"

void ILI9341_Init       (enum screen_ShowDIR ShowDIR                                                );  //初始化
void ILI9341_Clear      (uint16_t Color                                                     );	//清屏
void ILI9341_SetCursor  (uint16_t Xpos, uint16_t Ypos                                       );	//设置光标
void ILI9341_SetArea    (uint16_t x0,   uint16_t y0,    uint16_t x1,        uint16_t y1     );	//设置显示区域
void USER_SPI_Transmit_DMA(const uint16_t *pData, uint16_t pSize);
void TouchGFX_flushFrameBuffer(uint16_t* Pix,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t screen_w,uint16_t screen_h);
//Draw
void _HW_DrawPoint              (uint16_t x,    uint16_t y,     uint16_t color                                              );  //point
void _HW_FillFrame              (uint16_t sx,   uint16_t sy,    uint16_t ex,        uint16_t ey,        uint16_t color      );  //fillframe            
void _HW_DrawLine               (uint16_t _usX1,uint16_t _usY1, uint16_t _usX2,     uint16_t _usY2,     uint16_t _usColor   );  //line
void LCD_DrawRect               (uint16_t _usX, uint16_t _usY,  uint16_t _usHeight, uint16_t _usWidth,  uint16_t _usColor   );	//绘制水平放置的矩形
void LCD_DrawCircle             (uint16_t _usX, uint16_t _usY,  uint16_t _usRadius, uint16_t _usColor                       );	//绘制一个圆，笔宽为1个像素 
#endif





