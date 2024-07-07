#ifndef TIMERVIEW_HPP
#define TIMERVIEW_HPP

#include <gui_generated/timer_screen/TIMERViewBase.hpp>
#include <gui/timer_screen/TIMERPresenter.hpp>

//user
extern int flag_GPS;
extern "C"
{
    #include "GPS_interface.h"
    #include "myMath.h"
}
//user


class TIMERView : public TIMERViewBase
{
public:
    TIMERView();
    virtual ~TIMERView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    

    //user
    int hour,min,sec;
    void handleTickEvent();
    void MINUpdateItem(CLOCK_INNER &inner, int16_t item)
    {
        inner.setMIN(item);
    }

    void HOURUpdateItem(CLOCK_INNER &inner, int16_t item)
    {
        inner.setHour(item);
    }



    /**
     * @brief 根据年月日算出周日
     * 
     * @return int 
     */
    int weekday(uint16_t year,uint8_t mon,uint8_t day);


    //hardware
    void GNSS();
    //hardware


    //user


protected:
};

#endif // TIMERVIEW_HPP
