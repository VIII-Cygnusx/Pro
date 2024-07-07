#ifndef COMPASSPRESENTER_HPP
#define COMPASSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class COMPASSView;

class COMPASSPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    COMPASSPresenter(COMPASSView& v);

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

    virtual ~COMPASSPresenter() {}


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
    COMPASSPresenter();

    COMPASSView& view;
};

#endif // COMPASSPRESENTER_HPP
