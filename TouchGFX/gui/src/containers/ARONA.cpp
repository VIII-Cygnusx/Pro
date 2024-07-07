#include <gui/containers/ARONA.hpp>

ARONA::ARONA()
{

}

void ARONA::initialize()
{
    ARONABase::initialize();
}


void ARONA::animation()
{
    static int Ami_counter;
    switch (Ami_counter)
    {
    case 20:
        ARONABase::ARONA.setBitmaps(touchgfx::Bitmap(BITMAP_STANDBY_ID), touchgfx::Bitmap(BITMAP_JOY1_ID));
    break;
    case 40:
        ARONABase::ARONA.setBitmaps(touchgfx::Bitmap(BITMAP_STANDBY_ID), touchgfx::Bitmap(BITMAP_JOY2_ID));
    break;
    case 60:
        ARONABase::ARONA.setBitmaps(touchgfx::Bitmap(BITMAP_STANDBY_ID), touchgfx::Bitmap(BITMAP_JOY3_ID));
    break;
    case 80:
        ARONABase::ARONA.setBitmaps(touchgfx::Bitmap(BITMAP_STANDBY_ID), touchgfx::Bitmap(BITMAP_JOY2_ID));
        Ami_counter = 0;
    break;
    }
    ARONABase::ARONA.invalidate();
    Ami_counter ++ ;
}