#ifndef IMUVIEW_HPP
#define IMUVIEW_HPP

#include <gui_generated/imu_screen/IMUViewBase.hpp>
#include <gui/imu_screen/IMUPresenter.hpp>

class IMUView : public IMUViewBase
{
public:
    IMUView();
    virtual ~IMUView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //User
    int16_t x,y;
    void handleTickEvent();
    //User
protected:
};

#endif // IMUVIEW_HPP
