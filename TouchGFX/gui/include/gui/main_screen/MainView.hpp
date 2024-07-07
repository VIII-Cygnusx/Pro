#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user



    void handleTickEvent();

    void scrollWheel1UpdateItem(TEST& item, int16_t itemIndex)
    {
        item.set_img_txt(itemIndex);
        
    }


    //Hardware
    void TIMER();
    void IMU();
    void LOCAT();
    void SYSTEM();
    void CAM();
    void SPORT();
    void HEALTH();
    void ENV();
    void GAME();
    void COMPASS();   
    //Hardware

    //user
protected:

    //user

    touchgfx::Callback <MainView , const touchgfx::ScrollWheel & , const touchgfx::ClickEvent &> SWClickHandler;

    void SW_click_handler(const touchgfx::ScrollWheel &SW , const touchgfx::ClickEvent &click)
    {
        //txt.setVisible(false);
    } 
    //user
};


#endif // MAINVIEW_HPP
