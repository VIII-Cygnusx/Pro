#include <gui/locat_screen/LOCATView.hpp>


extern "C"
{
    int flag_GPS=0;
    #include "GPS_interface.h"
}



LOCATView::LOCATView()
{

}

void LOCATView::setupScreen()
{
    LOCATViewBase::setupScreen();
}

void LOCATView::tearDownScreen()
{
    LOCATViewBase::tearDownScreen();
    flag_GPS=0;
}



void LOCATView::handleTickEvent()
{
    //select GNSS
    static int page = 0;
    page = scrollWheel1.getSelectedItem();
    switch (page)
    {
        //GPS
    case 5:
        USE = _GPS;
        break;
        //BDS
    case 0:
        USE = _BDS;
        break;
        //GLONASS
    case 1:
        USE = _GLONASS;
        break;
        //GALILEO
    case 2:
        USE = _GALILEO;
        break;
        //QZSS
    case 3:
        USE = _QZSS;
        break;
        //MIX
    case 4:
        USE = _MIX;
        break;
    }
    //select GNSS






    //Change DATA
    {

        //MODE
        {
            if(GPS.XXGSA.position_type == GPS.XXGSA.None)Unicode::snprintf(MODEBuffer, MODE_SIZE, "None");
            if(GPS.XXGSA.position_type == GPS.XXGSA._2D )Unicode::snprintf(MODEBuffer, MODE_SIZE, "2D");
            if(GPS.XXGSA.position_type == GPS.XXGSA._3D )Unicode::snprintf(MODEBuffer, MODE_SIZE, "3D");
            MODE.invalidate();
        }

        //PDOP
        if(pdop != GPS.PDOP && GPS.PDOP != 0)
        {
            Unicode::snprintf(PDOPBuffer, PDOP_SIZE, "%d", GPS.PDOP);
            PDOP.invalidate();
            pdop = GPS.PDOP;
        }

        if(GPS.XXGSA.position_type != GPS.XXGSA.None)
        {
            //kmph
            if(kmph != GPS.kmph_vel)
            {
                Unicode::snprintfFloat(KMPHBuffer, KMPH_SIZE, "%2.1f", GPS.kmph_vel);

                //INIT
                KMPH.invalidate();
                
                kmph = GPS.kmph_vel;
            }  

            //Sat_Num
            {
                Unicode::snprintf(satellite_numBuffer, SATELLITE_NUM_SIZE, "%d", GPS.Sat_Num);
                satellite.invalidate();
                sat_num = GPS.Sat_Num;
            }

            //Alt
            if(GPS.altitude != alti)
            {
                Unicode::snprintfFloat(AltBuffer, ALT_SIZE, "%3.1f", GPS.altitude);
                Alt.invalidate();
                GPS.altitude = alti;
            }
        }
        
        if(GPS.XXRMC.isok == 'A')
        {
            //lat
            if(lat != GPS.latitude && GPS.latitude != 0)
            {
                //lat
                touchgfx::Unicode::snprintfFloat(LatBuffer1, LATBUFFER1_SIZE, "%3.5f",GPS.latitude);
                touchgfx::Unicode::snprintf(LatBuffer2, LATBUFFER2_SIZE, "%c", GPS.latitude_); 
                //init
                Lat.invalidate();    

                lat = GPS.latitude;
            }

            //Lon
            if(lon != GPS.longitude && GPS.longitude != 0)
            {
                //LON
                touchgfx::Unicode::snprintfFloat(LonBuffer1, LONBUFFER1_SIZE, "%3.5f", GPS.longitude);
                touchgfx::Unicode::snprintf(LonBuffer2, LONBUFFER2_SIZE, "%c",GPS.longitude_);     
                //init
                Lon.invalidate();   

                lon = GPS.longitude;
            }
        }            
    }
    //Change DATA


    //keep on 
    if(flag_GPS == 0)
    {
        NMEA_0183_analyse();
        flag_GPS = 1;
        GNSS_interface.it();
    }
    //keep on 
}