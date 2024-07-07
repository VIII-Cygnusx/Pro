#ifndef CAM_SETTINGVIEW_HPP
#define CAM_SETTINGVIEW_HPP

#include <gui_generated/cam_setting_screen/CAM_settingViewBase.hpp>
#include <gui/cam_setting_screen/CAM_settingPresenter.hpp>

//user
extern "C"
{
    #include "ov7725_interface.h"
}
//user


class CAM_settingView : public CAM_settingViewBase
{
public:
    CAM_settingView();
    virtual ~CAM_settingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user
    void handleTickEvent();
    
    //user
protected:
};

#endif // CAM_SETTINGVIEW_HPP
