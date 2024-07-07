#ifndef SYSTEMVIEW_HPP
#define SYSTEMVIEW_HPP

#include <gui_generated/system_screen/SYSTEMViewBase.hpp>
#include <gui/system_screen/SYSTEMPresenter.hpp>

class SYSTEMView : public SYSTEMViewBase
{
public:
    SYSTEMView();
    virtual ~SYSTEMView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SYSTEMVIEW_HPP
