/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/timer_screen/TIMERViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TIMERViewBase::TIMERViewBase() :
    updateItemCallback(this, &TIMERViewBase::updateItemCallbackHandler),
    buttonCallback(this, &TIMERViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    line.setPosition(10, 179, 301, 33);
    linePainter.setColor(touchgfx::Color::getColorFromRGB(255, 170, 0));
    line.setPainter(linePainter);
    line.setStart(0, 0);
    line.setEnd(300, 0);
    line.setLineWidth(10);
    line.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    line.setAlpha(0);
    add(line);

    quit.setXY(265, 240);
    quit.setBitmaps(touchgfx::Bitmap(BITMAP_BIG_QUIT_ID), touchgfx::Bitmap(BITMAP_BIG_QUIT_ID));
    quit.setAction(buttonCallback);
    add(quit);

    digitalClock1.setPosition(130, -47, 128, 47);
    digitalClock1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    digitalClock1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_3WSE));
    digitalClock1.displayLeadingZeroForHourIndicator(true);
    digitalClock1.setDisplayMode(touchgfx::DigitalClock::DISPLAY_24_HOUR);
    digitalClock1.setTime24Hour(0, 0, 0);
    add(digitalClock1);

    week_txt.setXY(258, -47);
    week_txt.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    week_txt.setLinespacing(0);
    Unicode::snprintf(week_txtBuffer, WEEK_TXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_PTL7).getText());
    week_txt.setWildcard(week_txtBuffer);
    week_txt.resizeToCurrentText();
    week_txt.setTypedText(touchgfx::TypedText(T___SINGLEUSE_4NFK));
    add(week_txt);

    image1.setXY(10, 133);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK_ID));
    image1.setAlpha(0);
    add(image1);

    start.setXY(169, 149);
    start.setBitmaps(touchgfx::Bitmap(BITMAP_START_NEW_ID), touchgfx::Bitmap(BITMAP_PAUSED_ID));
    start.setAlpha(0);
    add(start);

    MIN.setPosition(104, 240, 38, 50);
    MIN.setHorizontal(false);
    MIN.setCircular(true);
    MIN.setEasingEquation(touchgfx::EasingEquations::backEaseOut);
    MIN.setSwipeAcceleration(10);
    MIN.setDragAcceleration(10);
    MIN.setNumberOfItems(60);
    MIN.setSelectedItemOffset(0);
    MIN.setOvershootPercentage(75);
    MIN.setDrawableSize(41, 0);
    MIN.setDrawables(MINListItems, updateItemCallback);
    MIN.animateToItem(0, 0);
    add(MIN);

    HOUR.setPosition(50, 240, 38, 50);
    HOUR.setHorizontal(false);
    HOUR.setCircular(true);
    HOUR.setEasingEquation(touchgfx::EasingEquations::backEaseOut);
    HOUR.setSwipeAcceleration(10);
    HOUR.setDragAcceleration(10);
    HOUR.setNumberOfItems(24);
    HOUR.setSelectedItemOffset(0);
    HOUR.setOvershootPercentage(75);
    HOUR.setDrawableSize(41, 0);
    HOUR.setDrawables(HOURListItems, updateItemCallback);
    HOUR.animateToItem(0, 0);
    add(HOUR);

    POINT.setXY(92, 240);
    POINT.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    POINT.setLinespacing(0);
    POINT.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9FC0));
    add(POINT);
}

TIMERViewBase::~TIMERViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void TIMERViewBase::setupScreen()
{
    MIN.initialize();
    for (int i = 0; i < MINListItems.getNumberOfDrawables(); i++)
    {
        MINListItems[i].initialize();
    }
    HOUR.initialize();
    for (int i = 0; i < HOURListItems.getNumberOfDrawables(); i++)
    {
        HOURListItems[i].initialize();
    }
}

void TIMERViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &quit)
    {
        //Main
        //When quit clicked change screen to Main
        //Go to Main with no screen transition
        application().gotoMainScreenNoTransition();
        //HU
        //When quit clicked call virtual function
        //Call HU_
        HU_();
        //HD
        //When quit clicked call virtual function
        //Call HD_
        HD_();
        //MU
        //When quit clicked call virtual function
        //Call MU_
        MU_();
        //MD
        //When quit clicked call virtual function
        //Call MD_
        MD_();
        //SU
        //When quit clicked call virtual function
        //Call SU_
        SU_();
        //SD
        //When quit clicked call virtual function
        //Call SD_
        SD_();
    }
}

void TIMERViewBase::updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex)
{
    if (items == &MINListItems)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        CLOCK_INNER* cc = (CLOCK_INNER*)d;
        MINUpdateItem(*cc, itemIndex);
    }

    if (items == &HOURListItems)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        CLOCK_INNER* cc = (CLOCK_INNER*)d;
        HOURUpdateItem(*cc, itemIndex);
    }
}
