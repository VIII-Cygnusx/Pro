#ifndef HEALTHVIEW_HPP
#define HEALTHVIEW_HPP

#include <gui_generated/health_screen/HEALTHViewBase.hpp>
#include <gui/health_screen/HEALTHPresenter.hpp>

class HEALTHView : public HEALTHViewBase
{
public:
    HEALTHView();
    virtual ~HEALTHView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user
    void handleTickEvent();
    //user
protected:
};

#endif // HEALTHVIEW_HPP
