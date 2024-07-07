#ifndef CAMVIEW_HPP
#define CAMVIEW_HPP

#include <gui_generated/cam_screen/CAMViewBase.hpp>
#include <gui/cam_screen/CAMPresenter.hpp>


//user
extern "C"
{
#include "ov7725_interface.h"
}
//user


class CAMView : public CAMViewBase
{
public:
    
    CAMView();
    virtual ~CAMView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user
    int x,y;
    void handleTickEvent();
    void up_button()
    {
        y-=5;
    }
    void dwon_button()
    {
        y+=5;
    }
    void left_button()
    {
        x-=5;
    }
    void right_button()
    {
        x+=5;
    }
    
    void spetialUpdateItem(GNSS &message,int16_t itemIndex)
    {
        message.setCAM(itemIndex);
    }

    //user
protected:
};

#endif // CAMVIEW_HPP
