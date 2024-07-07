#ifndef SPORT_SETTINGVIEW_HPP
#define SPORT_SETTINGVIEW_HPP

#include <gui_generated/sport_setting_screen/SPORT_SETTINGViewBase.hpp>
#include <gui/sport_setting_screen/SPORT_SETTINGPresenter.hpp>

class SPORT_SETTINGView : public SPORT_SETTINGViewBase
{
public:
    SPORT_SETTINGView();
    virtual ~SPORT_SETTINGView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SPORT_SETTINGVIEW_HPP
