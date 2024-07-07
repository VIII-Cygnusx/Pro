#ifndef COMPASSVIEW_HPP
#define COMPASSVIEW_HPP

#include <gui_generated/compass_screen/COMPASSViewBase.hpp>
#include <gui/compass_screen/COMPASSPresenter.hpp>

class COMPASSView : public COMPASSViewBase
{
public:
    COMPASSView();
    virtual ~COMPASSView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user
    void handleTickEvent();
    
    //user
protected:
};

#endif // COMPASSVIEW_HPP
