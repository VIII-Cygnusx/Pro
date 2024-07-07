#include <gui/compass_screen/COMPASSView.hpp>

COMPASSView::COMPASSView()
{

}

void COMPASSView::setupScreen()
{
    COMPASSViewBase::setupScreen();
}

void COMPASSView::tearDownScreen()
{
    COMPASSViewBase::tearDownScreen();
}


void COMPASSView::handleTickEvent()
{
    static int i=0;
    static float RX[3]={0};
    switch (i)
    {
    case 1:
        presenter->IMU_RX();
        break;
    case 2:
        presenter->IMU_ANGLE(RX);
        break;
    case 3:
        if(RX[1]<0)
        {
            RX[1]+=360;
        }
        compass.setValue(RX[1]);
        compass.invalidate();
        i= 0;
        break;
    }
        i++;

}