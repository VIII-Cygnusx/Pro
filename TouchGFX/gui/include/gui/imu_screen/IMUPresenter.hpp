#ifndef IMUPRESENTER_HPP
#define IMUPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class IMUView;

class IMUPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    IMUPresenter(IMUView& v);

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

    virtual ~IMUPresenter() {}


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
    //MPU6050
    //user
private:
    IMUPresenter();

    IMUView& view;
};

#endif // IMUPRESENTER_HPP
