#ifndef CAM_SETTINGPRESENTER_HPP
#define CAM_SETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class CAM_settingView;

class CAM_settingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    CAM_settingPresenter(CAM_settingView& v);

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

    virtual ~CAM_settingPresenter() {}

private:
    CAM_settingPresenter();

    CAM_settingView& view;
};

#endif // CAM_SETTINGPRESENTER_HPP
