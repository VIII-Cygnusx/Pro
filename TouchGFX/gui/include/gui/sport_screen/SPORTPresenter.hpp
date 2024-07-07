#ifndef SPORTPRESENTER_HPP
#define SPORTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SPORTView;

class SPORTPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SPORTPresenter(SPORTView& v);

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

    virtual ~SPORTPresenter() {}

    //user
    //Mpu6050
    unsigned int STEP_RX()
    {
        return model->STEP_RX();
    }
    //MPU6050
    //user

private:
    SPORTPresenter();

    SPORTView& view;
};

#endif // SPORTPRESENTER_HPP
