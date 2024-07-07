#include "ili9341_interface.h"



void ILI9341_WR_REG                 (uint8_t    REG                                     );
void ILI9341_WR_DATA                (uint8_t    DATA                                    );
void ILI9341_WR_DATAS               (uint8_t*   DATA,           uint8_t num             );
void ILI9341_WriteReg               (uint8_t    ILI9341_Reg,    uint8_t ILI9341_RegValue);
void CS                             (uint8_t    num                                     );
void RES                            (uint8_t    num                                     );
void DISPLAY_DELAY                  (uint32_t   TICK                                    );


extern DMA_HandleTypeDef handle_GPDMA1_Channel0;

struct ili9341_interface LCD={  .CS_PORT=       GPIOA,
                                .RES_PORT=      GPIOA,
                                .CS_PIN=        GPIO_PIN_4,
                                .RES_PIN=       GPIO_PIN_8,
                                .SPI=           &hspi1,
                                .SPI_DMA=       &handle_GPDMA1_Channel0,
                                .W_REG=         ILI9341_WR_REG,
                                .W_DATA=        ILI9341_WR_DATA,
                                .W_DATAS=       ILI9341_WR_DATAS,
                                .CS=            CS,
                                .RES=           RES,
                                .MS=            DISPLAY_DELAY,
};

void RES(uint8_t num){
num ?(LCD.RES_PORT->BSRR = LCD.RES_PIN) : (LCD.RES_PORT->BRR = LCD.RES_PIN);
}

void CS(uint8_t num){
num ?(LCD.CS_PORT->BSRR = LCD.CS_PIN) : (LCD.CS_PORT->BRR = LCD.CS_PIN);
}

void ILI9341_WR_REG(uint8_t REG){ 
	LCD.CS(0);
	HAL_SPI_Transmit(&hspi1,&REG,1,1);  //不读取从机返回数据 	
    //HAL_SPI_Transmit_DMA(&hspi1,&REG,1);
	LCD.CS(1);
}

void ILI9341_WR_DATA(uint8_t DATA){										    	   
	HAL_SPI_Transmit(&hspi1,&DATA,1, 1);  //不读取从机返回数据 
    //HAL_SPI_Transmit_DMA(&hspi1,&DATA,1);
}

void ILI9341_WR_DATAS(uint8_t* DATA,uint8_t num){										    	   
	HAL_SPI_Transmit(&hspi1,DATA,num, 1);  //不读取从机返回数据 	
    //HAL_SPI_Transmit_DMA(&hspi1,DATA,num);
}

void DISPLAY_DELAY(uint32_t   TICK){
    HAL_Delay(TICK);
}
