#include <gui/main_screen/MainView.hpp>

extern "C"
{
    #include "myMath.h"
    #include "ov7725_interface.h"
}

//init
MainView::MainView():SWClickHandler(this, &MainView::SW_click_handler)
{
    scrollWheel1.setClickAction(SWClickHandler);

}


void MainView::setupScreen()
{
    
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}


//tick
void MainView::handleTickEvent()
{
    static int old_page;
    int page = scrollWheel1.getSelectedItem();


    //AMINATION
    //AMINATION

    


    //txt_amination
    {
        static int txt_xt=0,txt_xr=255;
        if(page == old_page)
        {

            txt_xt = 0;

            txt0.setVisible(true);
            txt1.setVisible(true);

            if(txt_xr > -1)txt_xr -=45;

            if(txt_xr > -1)
            {
                txt0.setX(110+txt_xr);
                txt0.setAlpha(LIMIT(255-txt_xr,0,200));  
                txt1.setX(110+txt_xr);
                txt1.setAlpha(LIMIT(255-txt_xr,0,200));   
            }
            if(txt_xr < -1) txt_xr = -5;

            if(txt_xr == -5)
            {
                txt0.setX(110);
                txt0.setAlpha(200);
                txt1.setX(110);
                txt1.setAlpha(200);
            }
        
        }
        else
        {
            txt_xr = 320;

            if(txt_xt < 320)txt_xt +=45;
            
            if(txt_xt < 320)
            {
                txt0.setX(110+txt_xt); 
                txt0.setAlpha(LIMIT(255-txt_xr,0,200));
                txt1.setX(110+txt_xt); 
                txt1.setAlpha(LIMIT(255-txt_xr,0,200));
            }
            if(txt_xt > 320)
            {
                old_page = page;
                txt0.setVisible(false);  
                txt1.setVisible(false);  
            }
        }
                
    }
    //txt_amination

    //txt_inner
    {
        switch (page)
        {
        case 0:
            TIMER();
        break;
        case 1:
            IMU();
        break;
        case 2:
            LOCAT();
        break;
        case 3:
            SYSTEM();
        break;
        case 4:
            CAM();
        break;
        case 5:
            SPORT();
        break;
        case 6:
            HEALTH();
        break;
        case 7:
            ENV();
        break;
        case 8:
            GAME();
        break;
        case 9:
            COMPASS();
        break;
        }
    }
    //txt_inner




}


extern int flag_GPS;
extern float milage;
extern int O2,HR;
extern "C"
{
    #include "GPS_interface.h"
}


void MainView::TIMER()
{
    USE = _TIME_ONLY;


    //TIME
    {
        //No Data
        if(GPS.year == 0)
        {
            Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "no signal to calibra-");
            Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "te the Timer,please");
            Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "go to the open field.");
            txt0.invalidate();
            txt1.invalidate(); 
        }        

        //YYYY-MM-DD
        //hh:mm
        if(sec != GPS.seconds)
        {
            //yyyy/mm/dd
            Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "data:%d/%d/%d", GPS.year+2000,GPS.month,GPS.day       );      
            Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "UTC :%02d:%02d:%02d",GPS.hours,GPS.minutes,GPS.seconds);
            Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "GNSS successful connected."                                                     );
            txt0.invalidate();
            txt1.invalidate(); 
            sec = GPS.seconds;          
        }




    }
    //TIME     

    //keep on 
    if(flag_GPS == 0)
    {
        NMEA_0183_analyse();
        flag_GPS = 1;
        GNSS_interface.it();
    }
    //keep on 
}

void MainView::IMU()
{
    static float RX[3]={0};
    static short int i=0;
    switch (i)
    {
    //RECEVICE DATA
    case 0:
        presenter->IMU_RX();
        i++;
        break;
    //PHREASEE DATA
    case 1:
        presenter->IMU_ANGLE(RX);
        i++;
        break;
    //PRINT DATA
    case 2:
        if(RX[0]!=0)Unicode::snprintfFloat(txt0Buffer1, TXT0BUFFER1_SIZE, "Pitch:%3.1f", RX[0]);
        if(RX[1]!=0)Unicode::snprintfFloat(txt0Buffer2, TXT0BUFFER2_SIZE, "Yaw:%3.1f", RX[1]);
        if(RX[2]!=0)Unicode::snprintfFloat(txt1Buffer , TXT1_SIZE       , "Roll:%3.1f", RX[2]);
        txt0.invalidate();
        txt1.invalidate();
        i++;
        break;
    default:
        i ++;
        if(i == 10)
        {
            i = 0;
        }            
        break;
    }
}

void MainView::LOCAT()
{
    USE = _GNGSA_ONLY;

    //MODE
    {
        if(GPS.XXGSA.position_type == GPS.XXGSA.None)
        {
             Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "GNSS_MODE:None");
             Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "not Locate");
        }
        else Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "Locate successful");
        if(GPS.XXGSA.position_type == GPS.XXGSA._2D )Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "GNSS_MODE:2D");
        if(GPS.XXGSA.position_type == GPS.XXGSA._3D )Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "GNSS_MODE:3D");        
        txt0.invalidate();    
    }

    



    //PDOP
    {
        if(GPS.PDOP < 8)                    Unicode::snprintf(txt1Buffer , TXT1_SIZE, "PDOP:Good");
        if(GPS.PDOP < 14)                   Unicode::snprintf(txt1Buffer , TXT1_SIZE, "PDOP:Normal");
        if(GPS.PDOP < 30 || GPS.PDOP == 0)  Unicode::snprintf(txt1Buffer , TXT1_SIZE, "PDOP:Bad");
        txt1.invalidate();               
    }


    //keep on 
    if(flag_GPS == 0)
    {
        NMEA_0183_analyse();
        flag_GPS = 1;
        GNSS_interface.it();
    }
    //keep on 
}

void MainView::SYSTEM()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "Core: STM32U5");
        Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "Ver : 1.0.0-test");
        Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "");

        txt0.invalidate();
        txt1.invalidate();   
}

void MainView::CAM()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "Dev: OV7725");
        if(image.shape.format == 0)Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "font: RGB444.");
        if(image.shape.format == 1)Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "font: RGB565.");
        Unicode::snprintf(txt1Buffer , TXT1_SIZE, "w:%d,h:%d",image.shape.width,image.shape.height);

        txt0.invalidate();
        txt1.invalidate();   
}

void MainView::SPORT()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "use DMP count");
        Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "step:%d",presenter->STEP_RX());
        Unicode::snprintfFloat(txt1Buffer , TXT1_SIZE       , "mileage:%fKm",milage);

        txt0.invalidate();
        txt1.invalidate();   
}

void MainView::HEALTH()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "Dev: max30102");
        Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "Last-heartbeat:%d",HR);
        Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "Last-SPO2:%d%",O2);

        txt0.invalidate();
        txt1.invalidate();   
}

void MainView::ENV()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "mix sensor");
        Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "Wet:SHT20");
        Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "Light:AP3216C");
        txt0.invalidate();
        txt1.invalidate();   
}

void MainView::GAME()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "1.ARONA");
        Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "2.-----");
        Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "");

        txt0.invalidate();
        txt1.invalidate();   
}

void MainView::COMPASS()
{
        Unicode::snprintf(txt0Buffer1, TXT0BUFFER1_SIZE, "No electronic");
        Unicode::snprintf(txt0Buffer2, TXT0BUFFER2_SIZE, "compass.use");
        Unicode::snprintf(txt1Buffer , TXT1_SIZE       , "mpu6050 replace");

        txt0.invalidate();
        txt1.invalidate();    
}


