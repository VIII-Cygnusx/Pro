#include <gui/sport_screen/SPORTView.hpp>

//
extern int flag_GPS;
extern "C"
{
    float milage;
    #include "myMath.h"
    #include "ov7725_interface.h"
    #include "GPS_interface.h"
}
//

SPORTView::SPORTView()
{
    USE = _MIX;

}

void SPORTView::setupScreen()
{
    SPORTViewBase::setupScreen();
}

void SPORTView::tearDownScreen()
{
    SPORTViewBase::tearDownScreen();
}

void SPORTView::handleTickEvent()
{
    
    static unsigned int old_steps;
    unsigned int steps = presenter->STEP_RX();
    //Step
    if(steps != old_steps)
    {
    Unicode::snprintf(stepBuffer, STEP_SIZE, "%03d",steps);
    step.invalidate(); 
    
    }
    //Step

    //Cal
    {

    }
    //Cal


    //Speed
    if(kmph != GPS.kmph_vel)
    {
        Unicode::snprintfFloat(speedBuffer, SPEED_SIZE, "%2.1f", GPS.kmph_vel);
        speed.invalidate();
        kmph = GPS.kmph_vel;
    }
    //Speed

    //Milage
    if(kmph != GPS.kmph_vel)
    {
        milage += GPS.kmph_vel/50;
        Unicode::snprintfFloat(MilageBuffer, MILAGE_SIZE, "%4.3f", milage);       

        kmph = GPS.kmph_vel;
    }
    if(kmph == GPS.kmph_vel && old_steps != steps)
    {
        milage += 0.0005;
        Unicode::snprintfFloat(MilageBuffer, MILAGE_SIZE, "%4.3f", milage);      
        Milage.invalidate();
        
    }
    //Milage

    //old
    {
    old_steps = steps;
    }
    //old

    //keep on 
    if(flag_GPS == 0)
    {
        NMEA_0183_analyse();
        flag_GPS = 1;
        GNSS_interface.it();
    }
    //keep on 


}