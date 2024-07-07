#ifndef GPS_INFO_H_
#define GPS_INFO_H_
#include "GPS_interface.h"


struct NMEA0183_info
{
    //XXRMC
    struct 
    {
        volatile    uint8_t* hhmmss;                    //<1> 
                    uint8_t  isok;                      //<2> 
        volatile    uint8_t* latitude;                  //<3> 
                    uint8_t  latitude_;                 //<4> 
        volatile    uint8_t* longitude;                 //<5> 
                    uint8_t  longitude_;                //<6> 
        volatile    uint8_t* ground_vel_knph;           //<7> 
        volatile    uint8_t* ddmmyy;                    //<9> 
    }XXRMC;

    //XXVTG
    struct 
    {
        volatile    uint8_t* ground_vel_knph;    //<5> 
        volatile    uint8_t* ground_vel_kmph;    //<7> 
    }XXVTG;

    //XXGGA 
    struct
    {
                    uint8_t  Qf;                        //<6 >   解状态
                    uint8_t  Sat_Num;                   //<7 >   卫星数量
        volatile    uint8_t* altitude;                  //<9 >   海拔

    }XXGGA;

    //XXGSA
    struct
    {
        volatile    enum                                //<2>
                    {
                        None    =0,
                        _2D       ,
                        _3D       ,
                    }position_type;
        volatile    uint8_t* PDOP;                      //<4>
    }XXGSA;

    struct
    {
        volatile    uint8_t* latitude;                  //<1 > 
                    uint8_t  latitude_;                 //<2 > 
        volatile    uint8_t* longitude;                 //<3 > 
                    uint8_t  longitude_;                //<4 > 
    }XXGLL;


                    float altitude;       
                    float latitude;
                    uint8_t latitude_;
                    float longitude;
                    uint8_t longitude_;
                
                    float kmph_vel;
                    float knph_vel;

                    uint8_t PDOP;
                    uint8_t Sat_Num;
                    uint16_t year;
                    uint8_t month;
                    uint8_t day;
                    uint8_t hours;
                    uint8_t minutes;
                    uint8_t seconds;

};

enum USE_
{
    _GPS     = 0 ,
    _BDS         ,
    _GLONASS     ,
    _GALILEO     ,
    _QZSS        ,
    _MIX         ,   
    _TIME_ONLY   ,
    _GNGSA_ONLY  ,
    _SPEED_ONLY  ,
};

extern struct NMEA0183_info GPS;
extern enum USE_ USE;
#endif