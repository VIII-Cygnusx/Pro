#ifndef MAINPRESENTER_HPP
#define MAINPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainView;

class MainPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainPresenter(MainView& v);

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

    virtual ~MainPresenter() {}



    //user

    //MPU6050
    void IMU_RX()
    {
        model->IMU_RX();
    }
    void IMU_ANGLE(float* RX) 
    {
        model->IMU_ANGLE(RX);
    }
    unsigned int STEP_RX()
    {
        return model->STEP_RX();
    }
    //MPU6050


    // 
    
    //user

private:
    MainPresenter();

    MainView& view;
};

#endif // MAINPRESENTER_HPP
