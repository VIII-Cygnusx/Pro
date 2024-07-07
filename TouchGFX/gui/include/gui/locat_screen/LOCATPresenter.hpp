#ifndef LOCATPRESENTER_HPP
#define LOCATPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class LOCATView;

class LOCATPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    LOCATPresenter(LOCATView& v);

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

    virtual ~LOCATPresenter() {}

private:
    LOCATPresenter();

    LOCATView& view;
};

#endif // LOCATPRESENTER_HPP
