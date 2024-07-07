#include <gui/env_screen/ENVView.hpp>

//user
extern "C"
{
    #include "bsp_ap3216c.h"
    float tem,hum,light;
}
//user

ENVView::ENVView()
{

}

void ENVView::setupScreen()
{
    ENVViewBase::setupScreen();
}

void ENVView::tearDownScreen()
{
    ENVViewBase::tearDownScreen();
}


void ENVView::handleTickEvent()
{
    
    static int x=0;
    if(x==10)
    {
    light = presenter->AP3216C_RX();
    presenter->SHT20_RX(&tem,&hum);
    Unicode::snprintfFloat(TEMBuffer, TEM_SIZE,     "%2.3f", tem);
    Unicode::snprintfFloat(WETBuffer, WET_SIZE,     "%2.3f", hum);
    Unicode::snprintfFloat(LIGHTBuffer, LIGHT_SIZE, "%2.3f", light);
    WET.invalidate();
    LIGHT.invalidate();    
    x=0;     
    }
    x++;
}