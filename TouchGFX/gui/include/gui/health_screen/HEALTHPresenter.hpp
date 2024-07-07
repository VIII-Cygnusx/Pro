#ifndef HEALTHPRESENTER_HPP
#define HEALTHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HEALTHView;

class HEALTHPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HEALTHPresenter(HEALTHView& v);

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

    virtual ~HEALTHPresenter() {}

    //user
    void MAX30102_RX(int *RED,int *IR,int counter)
    {
        return model->MAX30102_RX(RED,IR,counter);
    }
    void MAX30102_HR_OS(int *O2,int *HR)
    {
        return model->MAX30102_HR_OS(O2,HR);
    }
    bool MAX30102_OK()
    {
        return model->MAX30102_OK();
    }
    void MAX30102_INIT()
    {
        return model->MAX30102_INIT();
    }
    //user

private:
    HEALTHPresenter();

    HEALTHView& view;
};

#endif // HEALTHPRESENTER_HPP
