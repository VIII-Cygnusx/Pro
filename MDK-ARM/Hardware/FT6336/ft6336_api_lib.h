#ifndef FT6336_API_LIB_H__
#define FT6336_API_LIB_H__

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "ft6336_reg_lib.h"
#include "touch_info.h"






void FT6336_init(void);

uint16_t FT6336_read_touch1_x(void);
uint16_t FT6336_read_touch1_y(void);

uint16_t FT6336_read_touch2_x(void);
uint16_t FT6336_read_touch2_y(void);

void FT6336_scan();


#endif