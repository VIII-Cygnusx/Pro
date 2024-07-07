#ifndef TOUCH_H_
#define TOUCH_H_
#include "ft6336_interface.h"
struct TouchPoint
{
    uint16_t x;
    uint16_t y;
};

struct FT6336_TouchPointType
{
    uint8_t touch_count;
    struct TouchPoint tp[2];
};

extern struct FT6336_TouchPointType touch;

#endif