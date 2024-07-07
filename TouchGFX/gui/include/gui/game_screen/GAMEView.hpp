#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <gui_generated/game_screen/GAMEViewBase.hpp>
#include <gui/game_screen/GAMEPresenter.hpp>

class GAMEView : public GAMEViewBase
{
public:
    GAMEView();
    virtual ~GAMEView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();


    //user
    void handleTickEvent();

    
    //user
protected:
};

#endif // GAMEVIEW_HPP
