#include <gui/timer_screen/TIMERView.hpp>

//user
static int week_change = 1;
static int start_signal = 1;    //每此的启动页面动画，每次进入只启动一次
//user


TIMERView::TIMERView()
{
    USE = _TIME_ONLY;
    week_change = 1;
    start_signal = 1; 
}

void TIMERView::setupScreen()
{
    TIMERViewBase::setupScreen();
}

void TIMERView::tearDownScreen()
{
    TIMERViewBase::tearDownScreen();
}

//Tick event
void TIMERView::handleTickEvent()
{
    //load
    static int factor = 0,flag = 1;
    if(start_signal)
    {
        //quit & line & image1 & start
        if(flag == 1)
        {
            int quit_factor;
            quit_factor = (factor-155)*(factor-155)/100;        //f(x)
            if(quit_factor > 189)
            {
                image1.setAlpha(100+factor);
                start.setAlpha(100+factor);
                quit.setY(quit_factor);
            }
            else
            {
                image1.setAlpha(255);
                start.setAlpha(255);
                quit.setY(189);
                line.setAlpha(255);
                factor = 0;
                flag   = 2;
            }
            image1.invalidate();
            start.invalidate();
            quit.invalidate();
            line.invalidate();
        }

        //digitalclock1 & week_txt
        if(flag == 2)
        {
            int digitalclock1_factor;
            digitalclock1_factor = -(factor-69)*(factor-69)/100;    //f(x)
            if(digitalclock1_factor < 0)
            {
                digitalClock1.setY(digitalclock1_factor);
                week_txt.setY(digitalclock1_factor);
            }
            else
            {
                digitalClock1.setY(0);
                week_txt.setY(0);
                factor = 0;
                flag   = 3;
                
            }
            digitalClock1.invalidate();
            week_txt.invalidate();
        }

        //HOUR & MIN & POINT
        if(flag == 3)
        {
            int clock_factor;
            clock_factor = (factor-128)*(factor-128)/50-128;    //f(x)
            if(clock_factor > 128)
            {
                MIN.setY(clock_factor);
                POINT.setY(clock_factor);
                HOUR.setY(clock_factor);
            }
            else
            {
                MIN.setY(128);
                POINT.setY(128);
                HOUR.setY(128);
                factor = 0;
                flag   = 1;
                start_signal = 0;
            }
            MIN.invalidate();
            POINT.invalidate();
            HOUR.invalidate();
        }

        static int factor_step=0;
        if(factor_step == 3)
        {
           factor++; 
           factor_step = 0;
        }
        factor_step++;
        
    }
    //load

    //tick
    else
    {

    //week
    if(week_change)
    {
        week_change = 0;

        int week = weekday(GPS.year,GPS.month,GPS.day);
        if(week == 0) week =7;
        Unicode::snprintf(week_txtBuffer, WEEK_TXT_SIZE, "%d",week);
        week_txt.invalidate();
    }
    //week
    
    //Change data
    GNSS();
    //Change data



    }
    //tick






}


void TIMERView::GNSS()
{
    //change data
    {
        digitalClock1.setTime24Hour(GPS.hours,GPS.minutes,GPS.seconds);
    }
    //change data


    //keep on 
    if(flag_GPS == 0)
    {
        NMEA_0183_analyse();
        flag_GPS = 1;
        GNSS_interface.it();
    }
    //keep on 
}

//only used in 20 centrys
int TIMERView::weekday(uint16_t year, uint8_t mon, uint8_t day) {
    // 基姆拉尔森计算公式
    if (mon < 3) {
        mon += 12;
        year--;
    }
    int h = year + year/4 -35 + 26*(mon+1)/10+day-1;
    // 星期日为0，星期一为1，以此类推
    return h % 7;
}


