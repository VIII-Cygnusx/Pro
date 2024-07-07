#include <gui/imu_screen/IMUView.hpp>


//user
extern "C"
{
    #include "myMath.h"
}
//user


IMUView::IMUView()
{
}

void IMUView::setupScreen()
{
    IMUViewBase::setupScreen();
}

void IMUView::tearDownScreen()
{
    IMUViewBase::tearDownScreen();
}

void IMUView::handleTickEvent()
{
        static float RX[3]={0};
        static short int i=0;
        switch (i)
        {
        //RECEVICE DATA
        case 1:
            presenter->IMU_RX();

            break;
        //PHREASEE DATA
        case 2:
            presenter->IMU_ANGLE(RX);
            break;
        //PRINT DATA
        case 3:
            x=BALL.getX()+RX[0];
            y=BALL.getY()+RX[2];

            x=LIMIT(x,0,280);
            y=LIMIT(y,0,200);
            BALL.setXY(x,y);  
            BALL.invalidate();
            i=0;
            break;
            
        }
        i++;
        
        static int x=0;
        x++;
        if(x == 10)
        {
            x = 0;
            back.invalidate();
        }

}