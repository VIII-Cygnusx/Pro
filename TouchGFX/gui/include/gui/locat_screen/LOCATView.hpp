#ifndef LOCATVIEW_HPP
#define LOCATVIEW_HPP

#include <gui_generated/locat_screen/LOCATViewBase.hpp>
#include <gui/locat_screen/LOCATPresenter.hpp>

class LOCATView : public LOCATViewBase
{
public:
    LOCATView();
    virtual ~LOCATView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //user
    void scrollWheel1UpdateItem(GNSS& item, int16_t itemIndex)
    {
        item.setITEM(itemIndex);
    }
    
    void handleTickEvent();
    //user
protected:
};

#endif // LOCATVIEW_HPP
