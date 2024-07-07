#ifndef CAMPRESENTER_HPP
#define CAMPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class CAMView;

class CAMPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    CAMPresenter(CAMView& v);

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

    virtual ~CAMPresenter() {}


//OV7725
void OV7725_sample()
{
    return model->OV7725_sample();
}
void OV7725_send2LCD(int x,int y)
{   
    return model->OV7725_send2LCD(x,y);
}
//OV7725

private:
    CAMPresenter();

    CAMView& view;
};

#endif // CAMPRESENTER_HPP
