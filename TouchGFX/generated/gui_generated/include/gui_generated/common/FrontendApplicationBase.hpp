/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDAPPLICATIONBASE_HPP
#define FRONTENDAPPLICATIONBASE_HPP

#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

class FrontendApplicationBase : public touchgfx::MVPApplication
{
public:
    FrontendApplicationBase(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplicationBase() { }

    virtual void changeToStartScreen()
    {
        gotoMainScreenNoTransition();
    }

    // Main
    void gotoMainScreenNoTransition();

    // COMPASS
    void gotoCOMPASSScreenCoverTransitionEast();

    // TIMER
    void gotoTIMERScreenCoverTransitionEast();

    // IMU
    void gotoIMUScreenCoverTransitionEast();

    // LOCAT
    void gotoLOCATScreenCoverTransitionEast();

    // SYSTEM
    void gotoSYSTEMScreenCoverTransitionEast();

    // CAM
    void gotoCAMScreenCoverTransitionEast();

    void gotoCAMScreenNoTransition();

    // CAM_setting
    void gotoCAM_settingScreenNoTransition();

    // SPORT
    void gotoSPORTScreenCoverTransitionEast();

    void gotoSPORTScreenNoTransition();

    // SPORT_SETTING
    void gotoSPORT_SETTINGScreenNoTransition();

    // HEALTH
    void gotoHEALTHScreenCoverTransitionEast();

    // ENV
    void gotoENVScreenCoverTransitionEast();

    // GAME
    void gotoGAMEScreenCoverTransitionEast();

protected:
    touchgfx::Callback<FrontendApplicationBase> transitionCallback;
    FrontendHeap& frontendHeap;
    Model& model;

    // Main
    void gotoMainScreenNoTransitionImpl();

    // COMPASS
    void gotoCOMPASSScreenCoverTransitionEastImpl();

    // TIMER
    void gotoTIMERScreenCoverTransitionEastImpl();

    // IMU
    void gotoIMUScreenCoverTransitionEastImpl();

    // LOCAT
    void gotoLOCATScreenCoverTransitionEastImpl();

    // SYSTEM
    void gotoSYSTEMScreenCoverTransitionEastImpl();

    // CAM
    void gotoCAMScreenCoverTransitionEastImpl();

    void gotoCAMScreenNoTransitionImpl();

    // CAM_setting
    void gotoCAM_settingScreenNoTransitionImpl();

    // SPORT
    void gotoSPORTScreenCoverTransitionEastImpl();

    void gotoSPORTScreenNoTransitionImpl();

    // SPORT_SETTING
    void gotoSPORT_SETTINGScreenNoTransitionImpl();

    // HEALTH
    void gotoHEALTHScreenCoverTransitionEastImpl();

    // ENV
    void gotoENVScreenCoverTransitionEastImpl();

    // GAME
    void gotoGAMEScreenCoverTransitionEastImpl();
};

#endif // FRONTENDAPPLICATIONBASE_HPP
