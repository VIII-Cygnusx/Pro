#ifndef ILI9341_INTERFACE_H_
#define ILI9341_INTERFACE_H_
#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "screem_info.h"
#include "ili9341_api_lib.h"


#define LCD_USE_DMA2D     //是否启用DMA2D辅助屏幕显示，如果TOUCHGFX开启不建议开启此项




typedef void (*MS_                  )(uint32_t  num                 );
typedef void (*CS_                  )(uint8_t   num                 );
typedef void (*RES_                 )(uint8_t   num                 );
typedef void (*ILI9431_W_BYTE       )(uint8_t   REG                 );
typedef void (*ILI9431_W_DATA       )(uint8_t   DATA                );
typedef void (*ILI9431_W_DATAS      )(uint8_t*  DATA,   uint8_t num );
struct ili9341_interface
{
    GPIO_TypeDef*           RES_PORT;
    GPIO_TypeDef*           CS_PORT;
    uint16_t                RES_PIN;
    uint16_t                CS_PIN;
    SPI_HandleTypeDef*      SPI;
    DMA_HandleTypeDef*      SPI_DMA;
    uint8_t                 SPI_GPIO_MAP;
    SPI_TypeDef*            SPI_PIPE;
    GPIO_TypeDef*           SPI_PORT;
    uint16_t                SCLK;
    uint16_t                MISO;
    uint16_t                MOSI;
    ILI9431_W_BYTE          W_REG;
    ILI9431_W_DATA          W_DATA;
    ILI9431_W_DATAS         W_DATAS;
 
    CS_                     CS;
    RES_                    RES;
    MS_                     MS;
};
extern struct ili9341_interface LCD;




#endif