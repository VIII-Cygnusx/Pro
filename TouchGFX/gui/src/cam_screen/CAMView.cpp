#include <gui/cam_screen/CAMView.hpp>

CAMView::CAMView()
{
    x=170,y=0;
}

void CAMView::setupScreen()
{
    CAMViewBase::setupScreen();
}

void CAMView::tearDownScreen()
{
    CAMViewBase::tearDownScreen();
}

void CAMView::handleTickEvent()
{
    //select GNSS
    static int old_page = 0;
    int page = spetial.getSelectedItem();
    if(old_page != page)
    {
        switch (page)
        {
        case 6:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_NEGATIVE;
            break;
        case 0:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_NORMAL;
            break;
        case 1:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_BW;
            break;
        case 2:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_BLUISH;
            break;
        case 3:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_SEPIA;
            break;
        case 4:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_REDISH;
            break;
        case 5:
            image.special_effect_t = image_mix::SPECIAL_EFFECT_GREENISH;
            break;
        }  
        set_special_effect();
        old_page = page;      
    }

    //select GNSS


    static int init = 1;
    if(init)
    {
        
        OV7725_init_v();
        init=0;

    }
    else
    {
        wait_txt.setVisible(false);
    }



    
    

    
    static int i=0;
    switch (i)
    {
    case 1:
        presenter->OV7725_sample();

        break;

    case 2:
        presenter->OV7725_send2LCD(x,y);
        i=0;
        break;
    
    case 3:
        
        
        break;
    }
    i++;

    static int ii=0;
    ii++;
    if(ii == 30)
    {
        back.invalidate();
        ii = 0;
    }
}

