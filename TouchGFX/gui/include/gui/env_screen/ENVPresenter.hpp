#ifndef ENVPRESENTER_HPP
#define ENVPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ENVView;

class ENVPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ENVPresenter(ENVView& v);

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

    virtual ~ENVPresenter() {}

    //user
    //SHT20
    void SHT20_RX(float *tem,float *hum)
    {
        return model->SHT20_RX(tem,hum);
    }
    //SHT20

    //AP3216C
    float AP3216C_RX()
    {
        return model->AP3216C_RX();
    }
    //AP3216C

    //user

private:
    ENVPresenter();

    ENVView& view;
};

#endif // ENVPRESENTER_HPP
