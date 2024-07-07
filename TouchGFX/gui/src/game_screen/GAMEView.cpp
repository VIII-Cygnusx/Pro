#include <gui/game_screen/GAMEView.hpp>

GAMEView::GAMEView()
{

}

void GAMEView::setupScreen()
{
    GAMEViewBase::setupScreen();
}

void GAMEView::tearDownScreen()
{
    GAMEViewBase::tearDownScreen();
}

void GAMEView::handleTickEvent()
{
    ARONA.animation();
}