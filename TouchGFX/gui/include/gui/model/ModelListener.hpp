#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

//user
extern "C"
{
    #include "GPS_interface.h"
    #include "myMath.h"
	#include "task_PIPE.h"
    #include "user_MPU6050.h"
    #include "ov7725_interface.h"
    #include "user_max30102.h"
    #include "bsp_sht20.h"
    #include "bsp_ap3216c.h"
}
//user
class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
