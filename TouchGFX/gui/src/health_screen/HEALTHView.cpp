#include <gui/health_screen/HEALTHView.hpp>

extern "C"
{
    int O2,HR;
}
static int counter;

HEALTHView::HEALTHView()
{
    counter = 0;
}

void HEALTHView::setupScreen()
{
    HEALTHViewBase::setupScreen();
}

void HEALTHView::tearDownScreen()
{
    HEALTHViewBase::tearDownScreen();
}

void HEALTHView::handleTickEvent()
{
            
            //other
            {
                int RED,IR;
                if(counter == 0){
                    presenter->MAX30102_INIT();
                    counter++;
                }
                if(counter <200){
                    if(presenter->MAX30102_OK()){
                        presenter->MAX30102_RX(&RED,&IR,counter);
                        HEART_BEAT.addDataPoint((IR+RED)/3000);
                        counter++;                    
                    }
                    else{
                        HEART_BEAT.addDataPoint(1);
                    }
                }
                
                if(counter == 200){
                    presenter->MAX30102_HR_OS(&O2,&HR);
                    counter = 300;
                    if(O2>0 && HR>0){
                        Unicode::snprintf(O2_TXTBuffer, O2_TXT_SIZE, "%d",O2);
                        Unicode::snprintf(HEART_TXTBuffer, HEART_TXT_SIZE, "%d", HR);
                        HEART_TXT.invalidate();
                        O2_TXT.invalidate();             
                    }
                    else{
                        counter = 0;
                    }
                }                
            }
            //other
}