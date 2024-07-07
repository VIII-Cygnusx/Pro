#include <gui/containers/TEST.hpp>

/**
 * @brief Construct a new TEST::TEST object
 * 
 * 
 */
TEST::TEST():imageClickHandler(this,&TEST::image_click_handler)
{
    img.setClickAction(imageClickHandler);
}

void TEST::initialize()
{
    
    TESTBase::initialize();
}


