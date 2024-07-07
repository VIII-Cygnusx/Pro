/**
 * @file GPS_api.c
 * @author CygnusX_VIII (13509485575@163.com)
 * @brief NMEA-0183
 *          test GNSS device by BZ-121
 * @version 0.1
 * @date 2024-05-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "GPS__api_lib.h"
#include "usart.h"
#include "stdio.h"

//private
static uint8_t GPS_buf_ptr=0;
__IO   uint8_t GPS_buf[50];    //record from '$' to '\n'
static uint8_t GPS_p_ptr=0;
__IO   uint8_t GPS_p[20];       //record ',' position
//private




/**
 * @brief XXRMC推荐定位信息
 */
void XXRMC()
{
    //<1>   UTC时间, 格式hhmmss.ssss，代表时分秒.毫秒
    {
        if((GPS_p[1]-GPS_p[0]) > 1)
        {
            GPS.XXRMC.hhmmss = &GPS_buf[GPS_p[0]+1];   
            GPS.hours   =   (GPS.XXRMC.hhmmss[0]-48)*10 + (GPS.XXRMC.hhmmss[1]-48)+8;
            GPS.minutes =   (GPS.XXRMC.hhmmss[2]-48)*10 + (GPS.XXRMC.hhmmss[3]-48);
            GPS.seconds =   (GPS.XXRMC.hhmmss[4]-48)*10 + (GPS.XXRMC.hhmmss[5]-48);
            if((GPS.hours) > 24) GPS.hours -= 24; 
        }
        else
        {
            GPS.hours       = 0;
            GPS.minutes     = 0;
            GPS.seconds     = 0;                  
        }

    }
    //<2>   定位状态，A=有效定位，V=无效定位
    {
        GPS.XXRMC.isok=(GPS_buf[GPS_p[1]+1]);
    }
    //<3>   纬度 ddmm.mmmmm（度分）格式
    {
        if((GPS_p[3]-GPS_p[2]) >1)
        {
            GPS.XXRMC.latitude = &GPS_buf[GPS_p[2]+1];
            /////
            GPS.latitude =  
                            //dd
                            ((GPS.XXRMC.latitude[0]-48)*10.0f +                                 \
                             (GPS.XXRMC.latitude[1]-48))                                       \
                             +                                                                  \
                            //mm.mmmmm
                            ((GPS.XXRMC.latitude[2]-48)*10.0f +                                 \
                             (GPS.XXRMC.latitude[3]-48)+                                        \
                             (GPS.XXRMC.latitude[5]-48)*0.1+                                    \
                             (GPS.XXRMC.latitude[6]-48)*0.01+                                   \
                             (GPS.XXRMC.latitude[7]-48)*0.001+                                  \
                             (GPS.XXRMC.latitude[8]-48)*0.0001+                                 \
                             (GPS.XXRMC.latitude[9]-48)*0.00001)/60.0f                          \
                             +                                                                  \
                             //calibrate
                             0.0031f;                                                           \
                                 
                             

                            
        }
        else
        {
            GPS.latitude = 0;
        }
    }
    //<4>   纬度半球 N（北纬）或 S（南纬）
    {
        if((GPS_p[4]-GPS_p[3]) >1)
        {
            GPS.XXRMC.latitude_ = GPS_buf[GPS_p[3]+1];
            
        }
        else
        {
            GPS.XXRMC.latitude_ = 0;
        }
        GPS.latitude_ = GPS.XXRMC.latitude_;
    }
    //<5>   经度 dddmm.mmmmm（度分）格式
    {
        if((GPS_p[5]-GPS_p[4]) >1)
        {
            GPS.XXRMC.longitude = &GPS_buf[GPS_p[4]+1];
            GPS.longitude = 
                            //ddd
                            ((GPS.XXRMC.longitude[0]-48)*100.0f+                                \
                             (GPS.XXRMC.longitude[1]-48)*10.0f+                                 \
                             (GPS.XXRMC.longitude[2]-48))                                       \
                             +                                                                  \
                            //mm.mmmmm
                            ((GPS.XXRMC.longitude[3]-48)*10.0f+                                 \
                             (GPS.XXRMC.longitude[4]-48)+                                       \
                             (GPS.XXRMC.longitude[6]-48)*0.1+                                   \
                             (GPS.XXRMC.longitude[7]-48)*0.01+                                  \
                             (GPS.XXRMC.longitude[8]-48)*0.001+                                 \
                             (GPS.XXRMC.longitude[9]-48)*0.0001+                                \
                             (GPS.XXRMC.longitude[10]-48)*0.00001)/60.0f                        \
                             +                                                                  \
                             //calibrate
                             0.0102f;                                                          \
                             
        }
        else
        {
            GPS.longitude = 0;
        }
    }
    //<6>   经度半球 E（东经）或 W（西经）
    {
        if((GPS_p[6]-GPS_p[5]) >1)
        { 
            GPS.XXRMC.longitude_ = GPS_buf[GPS_p[5]+1];
        }
        else
        {
            GPS.XXRMC.longitude_ = 0;
        }
        GPS.longitude_ = GPS.XXRMC.longitude_;
    }
    //<7>   地面速率（000.0~999.9 节，前面的 0 也将被传输）
    {
        if((GPS_p[7]-GPS_p[6]) > 1)
        {
            GPS.XXRMC.ground_vel_knph = &GPS_buf[GPS_p[6]+1];
            //find '.'
            int point_ptr=0;
            while (GPS.XXRMC.ground_vel_knph[point_ptr] != '.') point_ptr++;  
            //xxx.
            for(int i=point_ptr-1,j=0;i>=0;i--,j++)
            {
                if(j == 0)GPS.knph_vel  = (GPS.XXRMC.ground_vel_knph[i]-48);
                if(j == 1)GPS.knph_vel += (GPS.XXRMC.ground_vel_knph[i]-48)*10;
                if(j == 2)GPS.knph_vel += (GPS.XXRMC.ground_vel_knph[i]-48)*100;
            }
            //.x
            GPS.knph_vel += (GPS.XXRMC.ground_vel_knph[point_ptr+1]-48)*0.1;
            GPS.kmph_vel = GPS.knph_vel*1.852f;
        }
        else
        {
            GPS.knph_vel=0;
            GPS.kmph_vel=0;
        }
    }
    //<8>   地面航向（方位角），等效于二维罗盘（000.0~359.9 度，以真北为参考基准，前面的 0 也将被传输）
    {

    }
    //<9>   UTC 日期，DDMMYY（日月年）格式
    {
        if((GPS_p[9]-GPS_p[8]) > 1)
        {
            GPS.XXRMC.ddmmyy = &GPS_buf[GPS_p[8]+1];   
            GPS.day   =   (GPS.XXRMC.ddmmyy[0]-48)*10 + (GPS.XXRMC.ddmmyy[1]-48);
            GPS.month =   (GPS.XXRMC.ddmmyy[2]-48)*10 + (GPS.XXRMC.ddmmyy[3]-48);
            GPS.year  =   (GPS.XXRMC.ddmmyy[4]-48)*10 + (GPS.XXRMC.ddmmyy[5]-48);

        }
        else
        {
            GPS.day       = 0;
            GPS.month     = 0;
            GPS.year      = 0;
        }
    }
    //<10>  磁偏角（000.0~180.0 度，前面的 0 也将被传输）
    {

    }
    //<11>  磁偏角方向，E（东）或 W（西）
    {

    }
    //<12>  模式指示（仅 NMEA0183 3.0 版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
    {

    }
}
    void XXRMC_only_time()
    {
        //<1>   UTC时间, 格式hhmmss.ssss，代表时分秒.毫秒
        {
            if((GPS_p[1]-GPS_p[0]) > 1)
            {
                GPS.XXRMC.hhmmss = &GPS_buf[GPS_p[0]+1];   
                GPS.hours   =   (GPS.XXRMC.hhmmss[0]-48)*10 + (GPS.XXRMC.hhmmss[1]-48)+8;
                GPS.minutes =   (GPS.XXRMC.hhmmss[2]-48)*10 + (GPS.XXRMC.hhmmss[3]-48);
                GPS.seconds =   (GPS.XXRMC.hhmmss[4]-48)*10 + (GPS.XXRMC.hhmmss[5]-48);
                if((GPS.hours) > 24) GPS.hours -= 24; 


            }
            else
            {
                GPS.hours       = 0;
                GPS.minutes     = 0;
                GPS.seconds     = 0;                  
            }

        }
        //<2>   定位状态，A=有效定位，V=无效定位
        {
            GPS.XXRMC.isok=(GPS_buf[GPS_p[1]+1]);
        }
        //<9>   UTC 日期，DDMMYY（日月年）格式
        {
            if((GPS_p[9]-GPS_p[8]) > 1)
            {
                GPS.XXRMC.ddmmyy = &GPS_buf[GPS_p[8]+1];   
                GPS.day   =   (GPS.XXRMC.ddmmyy[0]-48)*10 + (GPS.XXRMC.ddmmyy[1]-48);
                GPS.month =   (GPS.XXRMC.ddmmyy[2]-48)*10 + (GPS.XXRMC.ddmmyy[3]-48);
                GPS.year  =   (GPS.XXRMC.ddmmyy[4]-48)*10 + (GPS.XXRMC.ddmmyy[5]-48);

            }
            else
            {
                GPS.day       = 0;
                GPS.month     = 0;
                GPS.year      = 0;
            }
        }
    }
    void XXRMC_only_speed()
    {
        //<7>   地面速率（000.0~999.9 节，前面的 0 也将被传输）
        {
            if((GPS_p[7]-GPS_p[6]) > 1)
            {
                GPS.XXRMC.ground_vel_knph = &GPS_buf[GPS_p[6]+1];
                //find '.'
                int point_ptr=0;
                while (GPS.XXRMC.ground_vel_knph[point_ptr] != '.') point_ptr++;  
                //xxx.
                for(int i=point_ptr-1,j=0;i>=0;i--,j++)
                {
                    if(j == 0)GPS.knph_vel  = (GPS.XXRMC.ground_vel_knph[i]-48);
                    if(j == 1)GPS.knph_vel += (GPS.XXRMC.ground_vel_knph[i]-48)*10;
                    if(j == 2)GPS.knph_vel += (GPS.XXRMC.ground_vel_knph[i]-48)*100;
                }
                //.x
                GPS.knph_vel += (GPS.XXRMC.ground_vel_knph[point_ptr+1]-48)*0.1;
                GPS.kmph_vel = GPS.knph_vel*1.852f;
            }
            else
            {
                GPS.knph_vel=0;
                GPS.kmph_vel=0;
            }
        }
    }

/**
 * @brief XXVTG地面速度信息
 */
void XXVTG()
{
    //<5>   地面速率（000.0~999.9 节，前面的 0 也将被传输）
    {
        if((GPS_p[5]-GPS_p[4]) > 1)
        {
            GPS.XXVTG.ground_vel_knph = &GPS_buf[GPS_p[4]+1];
            //find '.'
            int point_ptr=0;
            while (GPS.XXVTG.ground_vel_knph[point_ptr] != 0x2E) point_ptr++;  
            //xxx.
            for(int i=point_ptr,j=0;i>0;i--,j++)
            {
                if(j == 0)GPS.knph_vel  = (GPS.XXVTG.ground_vel_knph[i-1]-48);
                if(j == 1)GPS.knph_vel += (GPS.XXVTG.ground_vel_knph[i-1]-48)*10;
                if(j == 2)GPS.knph_vel += (GPS.XXVTG.ground_vel_knph[i-1]-48)*100;
            }
            //.x
            GPS.knph_vel  += (GPS.XXVTG.ground_vel_knph[point_ptr+1]-48)*0.1;
            GPS.kmph_vel  = GPS.knph_vel*1.852;
        }
        else
        {
            GPS.knph_vel=0;
            GPS.kmph_vel=0;
        }
    }
    //<7> ????????(0000.0~1851.8????/��???????0?????????)
    {
        // if(GPS_p[7]-GPS_p[6] > 1)
        // {
        //     GPS.XXVTG.ground_vel_kmph = &GPS_buf[GPS_p[6]+1];
        //     //find '.'
        //     int point_ptr = 0;
        //     while (GPS.XXVTG.ground_vel_kmph[point_ptr] !='.') point_ptr++;
        //     point_ptr -=1;
        //     //xxx.
        //     for(int i=point_ptr,j=0;i>=0;i--,j++)
        //     {
        //         if(j == 0)GPS.kmph_vel  = (float)(GPS.XXVTG.ground_vel_kmph[i]-48);
        //         if(j == 1)GPS.kmph_vel += (GPS.XXVTG.ground_vel_kmph[i]-48)*10.0f;
        //         if(j == 2)GPS.kmph_vel += (GPS.XXVTG.ground_vel_kmph[i]-48)*100.0f;
        //         if(j == 3)GPS.kmph_vel += (GPS.XXVTG.ground_vel_kmph[i]-48)*1000.0f;
        //     }
        //     //.x
        //     GPS.kmph_vel += (GPS.XXVTG.ground_vel_kmph[point_ptr+1]-48)*0.1f;
        // }
        // else
        // {
        //     GPS.kmph_vel = 0;
        // }
    }
}


/**
 * @brief XXGGA定位信息
 */
void XXGGA()
{
    //<6>   GPS 状态：0=未定位，1=非差分定位，2=差分定位，6=正在估算
    {
        if((GPS_p[6]-GPS_p[5]) > 1)
        {
            GPS.XXGGA.Qf = (GPS_buf[GPS_p[5]+1]-48);
        }
        else
        {
            GPS.XXGGA.Qf = 0;
        }        
    }
    //<7>   正在使用解算位置的卫星数量（00~12）（前面的 0 也将被传输）
    {
        if((GPS_p[7]-GPS_p[6]) > 1)
        {
            GPS.XXGGA.Sat_Num = (GPS_buf[GPS_p[6]+1]-48)*10+(GPS_buf[GPS_p[6]+2]-48);
        }
        else
        {
            GPS.XXGGA.Sat_Num = 0;
        }
        GPS.Sat_Num = GPS.XXGGA.Sat_Num;
    }
    //<9>   海拔高度（-9999.9~99999.9）   
    {
        if((GPS_p[9]-GPS_p[8]) > 1)
        {
            GPS.XXGGA.altitude = &GPS_buf[GPS_p[8]+1];
            //find '.'
            int point_ptr=0;
            while (GPS.XXGGA.altitude[point_ptr] != '.') point_ptr++;  
            point_ptr-=1;
            //xxxx.
            for(int i=point_ptr,j=0;i>=0;i--,j++)
            {
                if(j == 0)GPS.altitude  = (float)(GPS.XXGGA.altitude[i]-48);
                if(j == 1)GPS.altitude += (GPS.XXGGA.altitude[i]-48)*10.0f;
                if(j == 2)GPS.altitude += (GPS.XXGGA.altitude[i]-48)*100.0f;
                if(j == 3)GPS.altitude += (GPS.XXGGA.altitude[i]-48)*1000.0f;
            }
            //.x
            GPS.altitude += (GPS.XXGGA.altitude[point_ptr+1]-48)*0.1f;
        }
        else
        {
            GPS.altitude = 0;
        }
    }
}


/**
 * @brief XXGSA当前卫星信息
 */
void XXGSA()
{
    //<2> 定位型式 1 = 未定位， 2 = 二维定位， 3 = 三维定位。
    {
        if(GPS_buf[GPS_p[1]+1] == '1') GPS.XXGSA.position_type = None;
        if(GPS_buf[GPS_p[1]+1] == '2') GPS.XXGSA.position_type = _2D;
        if(GPS_buf[GPS_p[1]+1] == '3') GPS.XXGSA.position_type = _3D;
    }
    //<4> PDOP 位置精度因子（0.5~99.9）
    {
        if((GPS_p[4]-GPS_p[3]) > 1)
        {
            //XX.
            GPS.XXGSA.PDOP = &GPS_buf[GPS_p[3]+1];
            GPS.PDOP = ((GPS.XXGSA.PDOP[0]-48)*10+(GPS.XXGSA.PDOP[1]-48));
        }
    }
}


/**
 * @brief XXGLL地理定位信息
 */
void XXGLL()
{
    //<1>   纬度 ddmm.mmmmm（度分）格式
    {
        if((GPS_p[1]-GPS_p[0]) >1)
        {
            GPS.XXGLL.latitude = &GPS_buf[GPS_p[0]+1];
            /////
            GPS.latitude =  
                            //dd
                            ((GPS.XXGLL.latitude[0]-48)*10.0f +                                 \
                             (GPS.XXGLL.latitude[1]-48))+                                       \
                            //mm.mmmmm
                            ((GPS.XXGLL.latitude[2]-48)*10.0f +                                 \
                             (GPS.XXGLL.latitude[3]-48)+                                        \
                             (GPS.XXGLL.latitude[5]-48)*0.1f+                                    \
                             (GPS.XXGLL.latitude[6]-48)*0.01f+                                   \
                             (GPS.XXGLL.latitude[7]-48)*0.001f+                                  \
                             (GPS.XXGLL.latitude[8]-48)*0.0001f+                                 \
                             (GPS.XXGLL.latitude[9]-48)*0.00001f)/60.0f;                                                
                            
        }
        else
        {
            GPS.latitude = 0;
        }
    }
    //<2>  纬度半球 N（北纬）或 S（南纬）
    {
        if((GPS_p[2]-GPS_p[1]) >1)
        {
            GPS.XXGLL.latitude_ = GPS_buf[GPS_p[1]+1];
        }
        else
        {
            GPS.XXGLL.latitude_ = 0;
        }
        GPS.latitude_ = GPS.XXGLL.latitude_;
    }
    //<3> 经度 dddmm.mmmmm（度分）格式
    {
        if((GPS_p[3]-GPS_p[2]) >1)
        {
            GPS.XXGLL.longitude = &GPS_buf[GPS_p[2]+1];
            GPS.longitude = 
                            //ddd
                            ((GPS.XXGLL.longitude[0]-48)*100.0f+                                \
                             (GPS.XXGLL.longitude[1]-48)*10.0f+                                 \
                             (GPS.XXGLL.longitude[2]-48))+                                      \
                            //mm.mmmmm
                            ((GPS.XXGLL.longitude[3]-48)*10.0f+                                 \
                             (GPS.XXGLL.longitude[4]-48)+                                       \
                             (GPS.XXGLL.longitude[6]-48)*0.1f+                                   \
                             (GPS.XXGLL.longitude[7]-48)*0.01f+                                  \
                             (GPS.XXGLL.longitude[8]-48)*0.001f+                                 \
                             (GPS.XXGLL.longitude[9]-48)*0.0001f+                                \
                             (GPS.XXGLL.longitude[10]-48)*0.00001f)/60.0f;
        }
        else
        {
            GPS.longitude = 0;
        }
    }
    //<4> 经度半球 E（东经）或 W（西经）
    {
        if((GPS_p[4]-GPS_p[3]) >1)
        { 
            GPS.XXGLL.longitude_ = GPS_buf[GPS_p[3]+1];
        }
        else
        {
            GPS.XXGLL.longitude_ = 0;
        }
        GPS.longitude_ = GPS.XXGLL.longitude_;
    }
}









/**
 * @brief 每次中断只接收一个字符，并控制当前接收字符的指针,并且记录","的位置
 * 
 */
void NMEA_0183_uart_it_1byte()
{
    // head 
    if(GNSS_interface.buffer == '$') 
    {
        GPS_buf_ptr =0; 
        GPS_p_ptr   =0;
    }     
    else                   GPS_buf_ptr++;
    // head

    GPS_buf[GPS_buf_ptr] = GNSS_interface.buffer; 

    // point
    if(GNSS_interface.buffer == ',')
    {
        GPS_p[GPS_p_ptr++] = GPS_buf_ptr;
    }
    // point   
}



/**
 * @brief 判断当前累计接收的字符串是否符合一帧NMEA-0183协议
 * 
 * @return yes:1 no:0
 */
uint8_t NMEA_0183_message_complete()
{
    if(GPS_buf[0] == '$' && GPS_buf[7] != ',' && GPS_buf[GPS_buf_ptr] == '\n')  return 1;
    else                                                                        return 0;
    
}



/**
 * @brief 解析一帧完整的NMEA-0183信号
 * 
 * @param USE 决定了分析哪个国家的卫星或者只分析哪种类型的信号
 * 
 * @return 分析好的信号会存储到 [GPS] 结构体里面
 */
void NMEA_0183_analyse()
{

        //USE World     GNSS
        if(GPS_buf[2] == 'N' && USE == _MIX)
        {
            //GNRMC
             if(GPS_buf[4] == 'M')XXRMC();              
            //GNVTG
            //if(GPS_buf[4] == 'T')XXVTG();
            //GNGGA
            if(GPS_buf[4] == 'G')XXGGA();
            //GNGSA
            if(GPS_buf[4] == 'S')XXGSA();
            //GNGLL
            //if(GPS_buf[4] == 'L')XXGLL();
        }
            //Other require
            if(GPS_buf[2] == 'N' && USE == _TIME_ONLY)
            {
                //GNRMC
                if(GPS_buf[4] == 'M')XXRMC_only_time();    
            }
            if(GPS_buf[2] == 'N' && USE == _GNGSA_ONLY)
            {
                //GNGSA
                if(GPS_buf[4] == 'S')XXGSA();
            }
            if(GPS_buf[2] == 'N' && USE == _SPEED_ONLY)
            {
                //GNGSA
                if(GPS_buf[4] == 'S')XXRMC_only_speed();
            }

        //USE GPS       GNSS
        if(GPS_buf[2] == 'P' && USE == _GPS)
        {
            //GPGSA

            //GPGSV

            //GPGGA

            //GPGLL

            //Debug;
            {
                GPS.kmph_vel  = 1; 
                GPS.latitude  = 0;
                GPS.longitude = 0;
                GPS.year = 10;
                GPS.month = 10 ;
                GPS.day = 10;
                GPS.hours = 10;
                GPS.minutes = 10;
                GPS.seconds = 10;                
            }
            //Debug
        }
        
        //USE BDS       GNSS
        if(GPS_buf[2] == 'B' && USE == _BDS)
        {
            //Debug;
            {
            GPS.kmph_vel  = 2; 
            GPS.latitude  = 20;
            GPS.longitude = 20;
            GPS.year = 20;
            GPS.month = 20 ;
            GPS.day = 20;
            GPS.hours = 20;
            GPS.minutes = 20;
            GPS.seconds = 20;                
            }
            //Debug
        }
        
        //USE GLONASS GNSS    
        if(GPS_buf[2] == 'L' && USE == _GLONASS)
        {
            //Debug;
            {
                GPS.kmph_vel  = 3; 
                GPS.latitude  = 30;
                GPS.longitude = 30;
                GPS.year = 30;
                GPS.month = 30 ;
                GPS.day = 30;
                GPS.hours = 30;
                GPS.minutes = 30;
                GPS.seconds = 30;
            }
            //Debug
        }
        
        //USE Galileo   GNSS
        if(GPS_buf[2] == 'A' && USE == _GALILEO)
        {
            //Debug;
            {
                GPS.kmph_vel  = 4; 
                GPS.latitude  = 40;
                GPS.longitude = 40;
                GPS.year = 40;
                GPS.month = 40 ;
                GPS.day = 40;
                GPS.hours = 40;
                GPS.minutes = 40;
                GPS.seconds = 40;
            }
            //Debug
        }
        
        //USE QZSS      GNSS
        if(GPS_buf[2] == 'Q' && USE == _QZSS)
        {
            //Debug;
            {
                GPS.kmph_vel  = 5; 
                GPS.latitude  = 50;
                GPS.longitude = 50;
                GPS.year = 50;
                GPS.month = 50 ;
                GPS.day = 50;
                GPS.hours = 50;
                GPS.minutes = 50;
                GPS.seconds = 50;
            }
            //Debug
        }


        //empty Head & end
        for(int i=0;i<=GPS_buf_ptr;i++)
        {
            GPS_buf[i] = 0;
        }
        //empty Head & end

}




