#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_
#include "main.h"
#include "GPS_info.h"
#include "GPS__api_lib.h"
typedef void (*UART_IT)();
typedef void (*delay)(uint32_t ms);
struct GNSS_interface
{
    UART_IT it;
    delay   ms;
    uint8_t buffer;

};
extern struct GNSS_interface GNSS_interface;


static uint8_t year,mon,day,hour,min,sec,lat_,lon_,sat_num,pdop;
static float lat,lon,kmph,alti;
#endif