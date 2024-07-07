#ifndef SPORTVIEW_HPP
#define SPORTVIEW_HPP

#include <gui_generated/sport_screen/SPORTViewBase.hpp>
#include <gui/sport_screen/SPORTPresenter.hpp>

class SPORTView : public SPORTViewBase
{
public:
    SPORTView();
    virtual ~SPORTView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user

    //tick
    void handleTickEvent();


    //user
protected:
};

#endif // SPORTVIEW_HPP
