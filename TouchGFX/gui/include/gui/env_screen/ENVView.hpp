#ifndef ENVVIEW_HPP
#define ENVVIEW_HPP

#include <gui_generated/env_screen/ENVViewBase.hpp>
#include <gui/env_screen/ENVPresenter.hpp>

class ENVView : public ENVViewBase
{
public:
    ENVView();
    virtual ~ENVView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user
    void handleTickEvent();
    //user
protected:
};

#endif // ENVVIEW_HPP
