#include "GPS_interface.h"
#include "usart.h"
void uart_it();
struct GNSS_interface GNSS_interface={.it=uart_it,
                                .ms=HAL_Delay
};

void uart_it()
{
    HAL_UART_Receive_IT(&huart1,&GNSS_interface.buffer,1);
}



extern int flag_GPS;    //from TouchGFX 




void USART1_IRQHandler(void)
{

    HAL_UART_IRQHandler(&huart1);

    NMEA_0183_uart_it_1byte();

        if(NMEA_0183_message_complete())
        {
            flag_GPS = 0;
            
        }

    //again
    if(flag_GPS)GNSS_interface.it();
    //again
}

