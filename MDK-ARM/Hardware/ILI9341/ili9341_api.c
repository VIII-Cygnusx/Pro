#include "ili9341_api_lib.h"

/**
 * @brief ILI9431 screem init 
 * 
 * @param ShowDIR display direction
 */
void ILI9341_Init(enum screen_ShowDIR ShowDIR){ 
  	//ILI9341复位 
    LCD.RES(1);
    LCD.MS(1);
    LCD.RES(0);
    LCD.MS(80);
    LCD.RES(1);
    LCD.MS(10);
	//************* Start Initial Sequence **********//
	LCD.W_REG(0xCF);  
	LCD.W_DATA(0x00); 
	LCD.W_DATA(0xC1); 
	LCD.W_DATA(0X30); 
	
	LCD.W_REG(0xED);  
	LCD.W_DATA(0x64); 
	LCD.W_DATA(0x03); 
	LCD.W_DATA(0X12); 
	LCD.W_DATA(0X81); 
	
	LCD.W_REG(0xE8);  
	LCD.W_DATA(0x85); 
	LCD.W_DATA(0x10); 
	LCD.W_DATA(0x7A); 
	
	LCD.W_REG(0xCB);  
	LCD.W_DATA(0x39); 
	LCD.W_DATA(0x2C); 
	LCD.W_DATA(0x00); 
	LCD.W_DATA(0x34); 
	LCD.W_DATA(0x02); 
	
	LCD.W_REG(0xF7);  
	LCD.W_DATA(0x20); 
	
	LCD.W_REG(0xEA);  
	LCD.W_DATA(0x00); 
	LCD.W_DATA(0x00); 
	
	LCD.W_REG(0xC0);    //Power control 
	LCD.W_DATA(0x1B);   //VRH[5:0] 
	
	LCD.W_REG(0xC1);    //Power control 
	LCD.W_DATA(0x01);   //SAP[2:0];BT[3:0] 
	
	LCD.W_REG(0xC5);    //VCM control 
	LCD.W_DATA(0x30); 	 //3F
	LCD.W_DATA(0x30); 	 //3C
	
	LCD.W_REG(0xC7);    //VCM control2 
	LCD.W_DATA(0XB7); 
	
	LCD.W_REG(0x36);    // Memory Access Control 
	LCD.W_DATA(0x48);	 //RGB 
	
	LCD.W_REG(0x3A);   
	LCD.W_DATA(0x55); 
	
	LCD.W_REG(0xB1);   
	LCD.W_DATA(0x00);   
	LCD.W_DATA(0x10);   //Frame Rate 119(Hz)
	
	LCD.W_REG(0xB6);    // Display Function Control 
	LCD.W_DATA(0x0A); 
	LCD.W_DATA(0xA2); 
	
	LCD.W_REG(0xF2);    // 3Gamma Function Disable 
	LCD.W_DATA(0x00); 
	
	LCD.W_REG(0x26);    //Gamma curve selected 
	LCD.W_DATA(0x01); 
	
	LCD.W_REG(0xE0);    //Set Gamma 
	{
		LCD.W_DATA(0x0F); 
		LCD.W_DATA(0x2A); 
		LCD.W_DATA(0x28); 
		LCD.W_DATA(0x08); 
		LCD.W_DATA(0x0E); 
		LCD.W_DATA(0x08); 
		LCD.W_DATA(0x54); 
		LCD.W_DATA(0XA9); 
		LCD.W_DATA(0x43); 
		LCD.W_DATA(0x0A); 
		LCD.W_DATA(0x0F); 
		LCD.W_DATA(0x00); 
		LCD.W_DATA(0x00); 
		LCD.W_DATA(0x00); 
		LCD.W_DATA(0x00); 		
	}

	
	LCD.W_REG(0XE1);    //Set Gamma 
	{
		LCD.W_DATA(0x00); 
		LCD.W_DATA(0x15); 
		LCD.W_DATA(0x17); 
		LCD.W_DATA(0x07); 
		LCD.W_DATA(0x11); 
		LCD.W_DATA(0x06); 
		LCD.W_DATA(0x2B); 
		LCD.W_DATA(0x56); 
		LCD.W_DATA(0x3C); 
		LCD.W_DATA(0x05); 
		LCD.W_DATA(0x10); 
		LCD.W_DATA(0x0F); 
		LCD.W_DATA(0x3F); 
		LCD.W_DATA(0x3F); 
		LCD.W_DATA(0x0F); 		
	}

	
	LCD.W_REG(0x2B); 
	{
		LCD.W_DATA(0x00);
		LCD.W_DATA(0x00);
		LCD.W_DATA(0x01);
		LCD.W_DATA(0x3f);		
	}

	
	LCD.W_REG(0x2A); 
	{
		LCD.W_DATA(0x00);
		LCD.W_DATA(0x00);
		LCD.W_DATA(0x00);
		LCD.W_DATA(0xef);
	}

	
	LCD.W_REG(0x35);	//Tearing Effect Line ON  
	LCD.W_DATA(0x00);
	
	LCD.W_REG(0x11);	//Sleep Out  
	LCD.W_REG(0x21);	//Display Inversion ON 
	LCD.MS(120);
	LCD.W_REG(0x29); //display on	
  	ILI9341_Display_Dir(ShowDIR);	//竖屏显示
}  



/**
 * @brief 设置光标位置
 * 
 * @param Xpos x横坐标
 * @param Ypos y纵坐标
 */
void ILI9341_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
	uint8_t TempBufferX[2] = {Xpos >> 8, Xpos & 0XFF};
	uint8_t TempBufferY[2] = {Ypos >> 8, Ypos & 0XFF};
	LCD.W_REG(ILI9341dev.setxcmd); 
	LCD.W_DATAS(TempBufferX,2);			
	LCD.W_REG(ILI9341dev.setycmd);
	LCD.W_DATAS(TempBufferY,2);		
} 


static uint16_t old_x0=0xFFFF, old_x1=0xFFFF, old_y0=0xFFFF, old_y1=0xFFFF;
/**
 * @brief 两点设置显示区域
 * 
 * @param x0 X0 横坐标
 * @param y0 Y0 纵坐标
 * @param x1 X1 横坐标
 * @param y1 Y1 纵坐标
 */
void ILI9341_SetArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{	 
  uint8_t arguments[4];
  // Set columns, if changed
  if (x0 != old_x0 || x1 != old_x1)
  {
    arguments[0] = x0 >> 8;
    arguments[1] = x0 & 0xFF;
    arguments[2] = x1 >> 8;
    arguments[3] = x1 & 0xFF;
		//
		LCD.W_REG(ILI9341dev.setxcmd); 
		LCD.W_DATAS(arguments, 4);
		//
    old_x0 = x0;
    old_x1 = x1;
  }
  // Set rows, if changed
  if (y0 != old_y0 || y1 != old_y1)
  {
    arguments[0] = y0 >> 8;
    arguments[1] = y0 & 0xFF;
    arguments[2] = y1 >> 8;
    arguments[3] = y1 & 0xFF;
		//
		LCD.W_REG(ILI9341dev.setycmd); 
		LCD.W_DATAS(arguments, 4);
		//
    old_y0 = y0;
    old_y1 = y1;
  }	
} 


/**
 * @brief 清屏函数
 * 
 * @param color 要清屏的填充色
 */
void ILI9341_Clear(uint16_t color)
{
	uint8_t TempBufferD[2] = {color >> 8, color};
	//
	uint32_t index=0;      
	uint32_t totalpoint=ILI9341dev.width;
	totalpoint*=ILI9341dev.height; 	//得到总点数
	//
  	ILI9341_SetCursor(0x00,0x00);	//设置光标位置
	LCD.W_REG(ILI9341dev.wramcmd);     //开始写入GRAM	

	//	
	for(index=0;index < totalpoint;index++)
	{
		LCD.W_DATAS(TempBufferD,2); 		
	}
}


/**
 * @brief 画点函数
 * 
 * @param x x坐标
 * @param y y坐标
 * @param color 点的颜色
 */
void _HW_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{	
	uint8_t TempBufferX[2] = {x >>8, x & 0XFF};
	uint8_t TempBufferY[2] = {y >>8, y & 0XFF};
	uint8_t TempBufferD[2] = {color >> 8, color};
	//
	LCD.W_REG(ILI9341dev.setxcmd); 
	//
	LCD.W_DATAS(TempBufferX,2);		
	//
	LCD.W_REG(ILI9341dev.setycmd); 
	//
	LCD.W_DATAS(TempBufferY,2);		
	//
	LCD.W_REG(ILI9341dev.wramcmd); 
	//
	LCD.W_DATAS(TempBufferD,2);		
}	


/*
**********************************************************************
* @fun     :_HW_FillFrame 
* @brief   :在指定区域内填充单个颜色
* @param   :(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1),color:要填充的颜色
* @return  :None 
**********************************************************************
*/
void _HW_FillFrame(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{  
	uint16_t i = 0,j = 0;
	uint16_t xlen = 0;
	xlen= ex - sx + 1;	   
	//
	uint8_t TempBuffer[2] = {color >> 8, color};	
	//数据写入屏幕
	for(i=sy;i<=ey;i++)
	{
	 	ILI9341_SetCursor(sx,i);      				//设置光标位置 
		LCD.W_REG(ILI9341dev.wramcmd);     			//开始写入GRAM	  
		for(j=0;j<xlen;j++) 
		{
			LCD.W_DATAS(TempBuffer,2);//点设置颜色	
		}
	}
} 


/**
 * @brief 画线
 * 
 * @param _usX1 x起点坐标
 * @param _usY1 y起点坐标
 * @param _usX2 x终点坐标
 * @param _usY2 y终点坐标
 * @param _usColor 要填充的颜色
 */
void _HW_DrawLine(uint16_t _usX1,uint16_t _usY1,uint16_t _usX2,uint16_t _usY2,uint16_t _usColor)
{
	int32_t dx,dy;
	int32_t tx ,ty;
	int32_t inc1,inc2;
	int32_t d,iTag;
	int32_t x,y;
	/* 采用 Bresenham 算法，在2点间画一条直线 */
	_HW_DrawPoint(_usX1,_usY1,_usColor);
	/* 如果两点重合，结束后面的动作。*/
	if (_usX1==_usX2 && _usY1==_usY2) {return;}

	iTag =0;
	/* dx = abs ( _usX2 - _usX1 ); */
	if (_usX2 >=_usX1) {dx=_usX2-_usX1;}
	else {dx =_usX1-_usX2;}

	/* dy =abs (_usY2-_usY1); */
	if (_usY2 >=_usY1) {dy = _usY2-_usY1;}
	else {dy = _usY1-_usY2;}

	if (dx < dy)   /*如果dy为计长方向，则交换纵横坐标。*/
	{
		uint16_t temp;
		iTag = 1;
		temp = _usX1; _usX1 = _usY1; _usY1 = temp;
		temp = _usX2; _usX2 = _usY2; _usY2 = temp;
		temp = dx; dx = dy; dy = temp;
	}
	
	tx = _usX2 > _usX1 ? 1 : -1;    /* 确定是增1还是减1 */
	ty = _usY2 > _usY1 ? 1 : -1;
	x = _usX1;
	y = _usY1;
	inc1 = 2 * dy;
	inc2 = 2 * (dy - dx);
	d = inc1 - dx;
	while (x != _usX2)     /* 循环画点 */
	{
		if (d < 0) {d += inc1;}
		else {y += ty ; d += inc2 ;}
		
		if (iTag) { _HW_DrawPoint(y,x,_usColor);}
		else {_HW_DrawPoint(x,y,_usColor);}
		
		x += tx ;
	}	
}   

/*
**********************************************************************
* @fun     :LCD_DrawRect 
* @brief   :绘制水平放置的矩形
* @param   :
*			_usX,_usY: 矩形左上角的坐标
*			_ush : 矩形的高度
*			_usw  : 矩形的宽度
* @return  :None 
**********************************************************************
*/
void LCD_DrawRect(uint16_t _usX, uint16_t _usY, uint16_t _ush, uint16_t _usw, uint16_t _usColor)
{	
	_HW_DrawLine(_usX, _usY, _usX + _usw - 1, _usY, _usColor);	/* 顶 */
	_HW_DrawLine(_usX, _usY + _ush - 1, _usX + _usw - 1, _usY + _ush - 1, _usColor);	/* 底 */

	_HW_DrawLine(_usX, _usY, _usX, _usY + _ush - 1, _usColor);	/* 左 */
	_HW_DrawLine(_usX + _usw - 1, _usY, _usX + _usw - 1, _usY + _ush, _usColor);	/* 右 */	
}
/*
**********************************************************************
* @fun     :LCD_DrawCircle 
* @brief   :绘制一个圆，笔宽为1个像素
* @param   :
*			_usX,_usY  : 圆心的坐标
*			_usRadius  : 圆的半径
* @return  :None 
**********************************************************************
*/
void LCD_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor)
{
	int32_t  D;			/* Decision Variable */
	uint32_t  CurX;		/* 当前 X 值 */
	uint32_t  CurY;		/* 当前 Y 值 */

	D = 3 - (_usRadius << 1);
	CurX = 0;
	CurY = _usRadius;

	while (CurX <= CurY)
	{
		_HW_DrawPoint(_usX + CurX, _usY + CurY, _usColor);
		_HW_DrawPoint(_usX + CurX, _usY - CurY, _usColor);
		_HW_DrawPoint(_usX - CurX, _usY + CurY, _usColor);
		_HW_DrawPoint(_usX - CurX, _usY - CurY, _usColor);
		_HW_DrawPoint(_usX + CurY, _usY + CurX, _usColor);
		_HW_DrawPoint(_usX + CurY, _usY - CurX, _usColor);
		_HW_DrawPoint(_usX - CurY, _usY + CurX, _usColor);
		_HW_DrawPoint(_usX - CurY, _usY - CurX, _usColor);

		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}




///////////////////////////////////////////////TouchGFX_interface///////////////////////////////////////////////
///////////////////////////////////////////////TouchGFX_interface///////////////////////////////////////////////
///////////////////////////////////////////////TouchGFX_interface///////////////////////////////////////////////
///////////////////////////////////////////////TouchGFX_interface///////////////////////////////////////////////
///////////////////////////////////////////////TouchGFX_interface///////////////////////////////////////////////
///////////////////////////////////////////////TouchGFX_interface///////////////////////////////////////////////
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv//
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv//
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv//

#ifdef LCD_USE_DMA2D
extern DMA2D_HandleTypeDef hdma2d;
//当TouchGFX也用了DMA2D不建议SPI驱动也用DMA2D进行处理
/**
 * @brief 提取图像内框选的矩形区域，输入原图像一维数组，输出提取矩阵区域数组
 * 
 * 
 * @param pSrc 		矩形区域在原图像一维数组的首地址
 * @param pDst 		存放目标地址
 * @param w 		矩形区域宽
 * @param h 		矩形区域高
 * @param OffLineSrc 	矩形区域在原图像一维数组的首地址偏移
 * @param OffLineDst 	存放目标地址偏移
 */
void DMA2D_MemCopy(const uint16_t* pSrc, uint16_t* pDst, int w, int h, int OffLineSrc, int OffLineDst) {
	while(HAL_DMA2D_GetState(&hdma2d) !=HAL_DMA2D_STATE_READY){}
	LCD.MS(0);
	HAL_DMA2D_Abort(&hdma2d);
    DMA2D->CR 		= 0x00000000U;				//mem 2 mem
    DMA2D->FGMAR 	= (uint32_t)pSrc;			//source add
    DMA2D->OMAR		= (uint32_t)pDst;			//dst    add
    DMA2D->FGOR 	= OffLineSrc;				//source 偏移
    DMA2D->OOR 		= OffLineDst;				//dst	 偏移
    DMA2D->FGPFCCR 	= DMA2D_INPUT_RGB565;
    DMA2D->NLR 		= (uint32_t)(w << 16) | (uint16_t)h;		//set width & height
    DMA2D->CR 	   |= DMA2D_CR_START;
}
#endif

/**
 * @brief SPI u16 格式发送
 * 
 * @param pData u16数据
 * @param pSize 大小
 */
void USER_SPI_Transmit_DMA(const uint16_t *pData, uint16_t pSize)
{
		//Set the transaction information
		LCD.SPI->State       = HAL_SPI_STATE_READY;
		LCD.SPI->ErrorCode   = HAL_SPI_ERROR_NONE;

		//Init field not used in handle to zero
		LCD.SPI->RxISR       = NULL;
		LCD.SPI->TxISR       = NULL;

		//Configure communication direction : 1Line
		SPI_2LINES_TX(LCD.SPI);

		// Packing mode management is enabled by the DMA settings
		IS_SPI_FULL_INSTANCE(LCD.SPI->Instance);

		//Clear TXDMAEN bit
		CLEAR_BIT(LCD.SPI->Instance->CFG1, SPI_CFG1_TXDMAEN);

		//Update the DMA channel state
		LCD.SPI_DMA->State = HAL_DMA_STATE_BUSY;
		//Update the DMA channel error code
		LCD.SPI_DMA->ErrorCode = HAL_DMA_ERROR_NONE;

		//Configure the source address, destination address, the data size and clear flags
		MODIFY_REG(LCD.SPI_DMA->Instance->CBR1, DMA_CBR1_BNDT, ((pSize) & DMA_CBR1_BNDT));

		//Clear all interrupt flags
		__HAL_DMA_CLEAR_FLAG(LCD.SPI_DMA, DMA_FLAG_TC | DMA_FLAG_HT | DMA_FLAG_DTE | DMA_FLAG_ULE | DMA_FLAG_USE | DMA_FLAG_SUSP |
												 DMA_FLAG_TO);

		//Configure DMA channel source address
		LCD.SPI_DMA->Instance->CSAR = (uint32_t)pData;

		//Configure DMA channel destination address
		LCD.SPI_DMA->Instance->CDAR = (uint32_t)&LCD.SPI->Instance->TXDR;

		//Enable common interrupts: Transfer Complete and Transfer Errors ITs
		__HAL_DMA_ENABLE_IT(LCD.SPI_DMA, (DMA_IT_TC | DMA_IT_DTE | DMA_IT_ULE | DMA_IT_USE | DMA_IT_TO));

		//If Half Transfer complete callback is set, enable the corresponding IT
		__HAL_DMA_ENABLE_IT(LCD.SPI_DMA, DMA_IT_HT);

		//Enable DMA channel
		__HAL_DMA_ENABLE(LCD.SPI_DMA);

		//Set the number of data at current transfer
		MODIFY_REG(LCD.SPI->Instance->CR2, SPI_CR2_TSIZE, (pSize));

		//Enable Tx DMA Request
		SET_BIT(LCD.SPI->Instance->CFG1, SPI_CFG1_TXDMAEN);

		//Enable the SPI Error Interrupt Bit
		__HAL_SPI_ENABLE_IT(LCD.SPI, (SPI_IT_UDR | SPI_IT_FRE | SPI_IT_MODF));

		//Enable SPI peripheral
		__HAL_SPI_ENABLE(LCD.SPI);
		//
		if (((LCD.SPI->Instance->AUTOCR & SPI_AUTOCR_TRIGEN) == 0U) && (LCD.SPI->Init.Mode == SPI_MODE_MASTER))
		{
			/* Master transfer start */
			SET_BIT(LCD.SPI->Instance->CR1, SPI_CR1_CSTART);
		}	
}


uint16_t flushAreaBuf[0XFFFF]={0};
/**
 * @brief 用于在Touchgfx显示渲染帧
 * 
 * 
 * @example 放入TouchGFX的接口函数
 * 
 * void TouchGFXHAL::flushFrameBuffer(const touchgfx::Rect& rect){
 * 		TouchGFX_flushFrameBuffer(getClientFrameBuffer(),x,rect.y,rect.width,h,HAL::DISPLAY_WIDTH,HAL::DISPLAY_HEIGHT);
 * 		TouchGFXGeneratedHAL::flushFrameBuffer(rect);
 * }
 * 
 * @param Pix 输入getClientFrameBuffer()获取屏幕帧首地址
 * @param x   特定渲染区域x    	x
 * @param y   特定渲染区域y    	rect.y
 * @param w   特定渲染区域宽	rect.width
 * @param h   特定渲染区域长	rect.heighrt
 * @param screen_w 屏幕宽	 	HAL::DISPLAY_WIDTH
 * @param screen_h 屏幕长		HAL::DISPLAY_HEIGHT
 */
inline void TouchGFX_flushFrameBuffer(uint16_t* Pix,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t screen_w,uint16_t screen_h){
		__IO uint16_t *pixels; 
		__IO uint16_t h_ptr = 0,w_ptr = 0,pBuffCnt = 0;

		//获取渲染好的帧像素首地址
		pixels = Pix + x + y * screen_w;	

		ILI9341_SetArea(x, y,x+w-1, y+h-1);
		LCD.W_REG(ILI9341dev.wramcmd);	
	

		LCD.SPI->Instance->CFG1 &= (~0x1F);
		LCD.SPI->Instance->CFG1 |= SPI_DATASIZE_16BIT;

		if((w == screen_w) && (h == screen_h))
		{
				USER_SPI_Transmit_DMA((const uint16_t*)pixels,0XFFFE);	//DMA单次传输0xFFFF  此处传输0XFFFE
					pixels = pixels + 0X7FFF;  //地址偏移 0XFFFE>>1 
					while(HAL_DMA_GetState(LCD.SPI_DMA) != HAL_DMA_STATE_READY);
					LCD.MS(0);
					HAL_SPI_Abort(LCD.SPI);
				
				USER_SPI_Transmit_DMA((const uint16_t*)pixels,0XFFFE);	//DMA单次传输0xFFFF  此处传输0XFFFE
					pixels = pixels + 0X7FFF;  //地址偏移 0XFFFE>>1 
					while(HAL_DMA_GetState(LCD.SPI_DMA) != HAL_DMA_STATE_READY);	
					LCD.MS(0);
					HAL_SPI_Abort(LCD.SPI);
				
				USER_SPI_Transmit_DMA((const uint16_t*)pixels,22532);	//剩余数据传输//pTotalPixel % 0XFFFF  22532		
					while(HAL_DMA_GetState(LCD.SPI_DMA) != HAL_DMA_STATE_READY);	
					LCD.MS(0);
					HAL_SPI_Abort(LCD.SPI);
		}
		else
		{
			for (h_ptr = 0; h_ptr < h; h_ptr++)
			{
				//缓冲区数据采用小端模式，ILI9341数据传输高字节在前
				pixels = Pix + x + (h_ptr + y) * screen_w;
				//读取限度点至缓冲区
				for (w_ptr = 0; w_ptr < w; w_ptr++)
				{
					flushAreaBuf[pBuffCnt++] = *pixels;	//读取像素点
					pixels++;	//调整偏移地址
					if(pBuffCnt >= 31744)	//缓冲区数据满，传输数据至屏幕
					{
						//启动DMA传输
						USER_SPI_Transmit_DMA(flushAreaBuf,63488);
						//等待DMA传输完成
						while(HAL_DMA_GetState(LCD.SPI_DMA) != HAL_DMA_STATE_READY);	
						//适当延时
						HAL_Delay(0);
						//阻塞模式下，终止正在的传输
						HAL_SPI_Abort(LCD.SPI);
						//复位计数值
						pBuffCnt =0;
					}
				}
			}
			//启动DMA传输
				USER_SPI_Transmit_DMA(flushAreaBuf,pBuffCnt * 2);
			//等待DMA传输完成
			while(HAL_DMA_GetState(LCD.SPI_DMA) != HAL_DMA_STATE_READY);	
			//适当延时
			HAL_Delay(0);
			//阻塞模式下，终止正在的传输
			HAL_SPI_Abort(LCD.SPI);
		}
		LCD.SPI->Instance->CFG1 &= (~0x1F);
		LCD.SPI->Instance->CFG1 |= SPI_DATASIZE_8BIT;   
}

















