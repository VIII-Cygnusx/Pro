#ifndef SYSTEMPRESENTER_HPP
#define SYSTEMPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SYSTEMView;

class SYSTEMPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SYSTEMPresenter(SYSTEMView& v);

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

    virtual ~SYSTEMPresenter() {}

private:
    SYSTEMPresenter();

    SYSTEMView& view;
};

#endif // SYSTEMPRESENTER_HPP
