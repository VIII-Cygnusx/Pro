#ifndef TEST_HPP
#define TEST_HPP

#include <gui_generated/containers/TESTBase.hpp>


//user
#include <images/BitmapDatabase.hpp>
//user


class TEST : public TESTBase,Model
{
public:
    TEST();
    virtual ~TEST() {}

    virtual void initialize();




    //user
    int16_t number;    

    virtual void setY(int16_t y)
    {
        //set Y as normal
        TESTBase::setY(y);

        y -= 73;
        int16_t yy = y*y;
        {
            img.setX(yy/150);            
        }

        {
			line.setX (50+yy/4);
            title.setX(65+yy);
        }

        {

        }

    }
    

    void set_img_txt(int no)
    {
        switch(no % 10)
        {
        case 0:
            img.setBitmap(touchgfx::Bitmap(BITMAP_COMPASS_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "COMPASS");
            break;
        case 1:
            img.setBitmap(touchgfx::Bitmap(BITMAP_TIMER_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "TIMER");
            break;
        case 2:
            img.setBitmap(touchgfx::Bitmap(BITMAP_IMU_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "IMU");
            break;
        case 3:
            img.setBitmap(touchgfx::Bitmap(BITMAP_MAP_LOCAT_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "LOCAT");
            break;
        case 4:
            img.setBitmap(touchgfx::Bitmap(BITMAP_SETTING_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "SYSTEM");
            break;
        case 5:
            img.setBitmap(touchgfx::Bitmap(BITMAP_CAM_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "CAM");
            break;
        case 6:
            img.setBitmap(touchgfx::Bitmap(BITMAP_CYCLE_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "SPORT");
            break;
        case 7:
            img.setBitmap(touchgfx::Bitmap(BITMAP_HEALTH_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "HEALTH");
            break;
        case 8:
            img.setBitmap(touchgfx::Bitmap(BITMAP_ENV_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "ENV");
            break;
        case 9:
            img.setBitmap(touchgfx::Bitmap(BITMAP_GAME_ID));
            Unicode::snprintf(titleBuffer, TITLE_SIZE, "GAME");
            break;
        }
        number = no;
    }



    
    //user

protected:

    //user

        /**
         * @brief 针对 IMG 
         * 
         * @param [TEST]                           这是Callback的调用方或者说是拥有者类型。在TouchGFX上下文中，这通常是一个类名，表示定义或使用这个回调的类。
         * @param [const touchgfx::Image &]         让你可以在回调函数中访问这个被点击的图像的相关信息。
         * @param [const touchgfx::ClickEvent &]    这提供了关于点击事件本身的详细信息，比如点击的位置等。
         * 
         * @note imageClickHandler: ����Callback�����?�����?�?�����?��������???�����?��??�??���
         */
		touchgfx::Callback<TEST, const touchgfx::Image & , const touchgfx::ClickEvent &> imageClickHandler;
        

        /**
         * @brief ��??�??���
         * 
         * @param image ?��?����Image�����������?����,���??�����??��
         * @param event �?�?��?�������������?��?�����??�����?���
         */
        void image_click_handler(const touchgfx::Image &image , const touchgfx::ClickEvent &event)
        {
            if(&image == &img)
            {
                switch (number % 10)
                {
                case 0:
                    application().gotoCOMPASSScreenCoverTransitionEast();
                    break;
                case 1:
                    application().gotoTIMERScreenCoverTransitionEast();
                    break;
                case 2:
                    application().gotoIMUScreenCoverTransitionEast();
                    break;
                case 3:
                    application().gotoLOCATScreenCoverTransitionEast();
                    break;
                case 4:
                    application().gotoSYSTEMScreenCoverTransitionEast();
                    break;
                case 5:
                    application().gotoCAMScreenCoverTransitionEast();
                    break;
                case 6:
                    application().gotoSPORTScreenCoverTransitionEast();
                    break;
                case 7:
                    application().gotoHEALTHScreenCoverTransitionEast();
                    break;
                case 8:
                    application().gotoENVScreenCoverTransitionEast();
                    break;
                case 9:
                    application().gotoGAMEScreenCoverTransitionEast();
                    break;
                }
            }
            
        }
    
    //user
};

#endif // TEST_HPP
