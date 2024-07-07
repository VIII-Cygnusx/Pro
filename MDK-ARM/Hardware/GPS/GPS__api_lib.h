#ifndef GPS_API_LIB_H_
#define GPS_API_LIB_H_
#include "GPS_interface.h"



void XXRMC();
void XXVTG();
void XXGGA();
void XXGSA();
void XXGLL();

void NMEA_0183_uart_it_1byte();
uint8_t NMEA_0183_message_complete();
void NMEA_0183_analyse();
#endif