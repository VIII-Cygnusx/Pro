
#ifndef FT6336_INTERFACE_H_
#define FT6336_INTERFACE_H_
#include "main.h"
#include "i2c.h"
#include "ft6336_reg_lib.h"
#include "ft6336_api_lib.h"
#include "touch_info.h"
typedef uint8_t (*_readByte)(uint8_t addr);
typedef void    (*MS_)(uint32_t ms);
typedef void    (*RES_)(uint8_t num);
struct ft6336_interface
{
    GPIO_TypeDef*   RES_PORT;
    uint16_t        RES_PIN;
    GPIO_TypeDef*   EXIT_PORT;
    uint16_t        EXTI_PIN;
    _readByte   Read;
    MS_         MS;
    RES_        RES;

};
extern struct ft6336_interface ft6336;


#endif