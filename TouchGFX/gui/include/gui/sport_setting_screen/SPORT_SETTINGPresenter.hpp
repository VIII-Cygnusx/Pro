#ifndef SPORT_SETTINGPRESENTER_HPP
#define SPORT_SETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SPORT_SETTINGView;

class SPORT_SETTINGPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SPORT_SETTINGPresenter(SPORT_SETTINGView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~SPORT_SETTINGPresenter() {}

private:
    SPORT_SETTINGPresenter();

    SPORT_SETTINGView& view;
};

#endif // SPORT_SETTINGPRESENTER_HPP
