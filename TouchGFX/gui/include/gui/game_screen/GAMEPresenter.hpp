#ifndef GAMEPRESENTER_HPP
#define GAMEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GAMEView;

class GAMEPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GAMEPresenter(GAMEView& v);

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

    virtual ~GAMEPresenter() {}

private:
    GAMEPresenter();

    GAMEView& view;
};

#endif // GAMEPRESENTER_HPP
