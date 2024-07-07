#ifndef CALENDER_HPP
#define CALENDER_HPP

#include <gui_generated/containers/CalenderBase.hpp>

class Calender : public CalenderBase
{
public:
    Calender();
    virtual ~Calender() {}

    virtual void initialize();
protected:
};

#endif // CALENDER_HPP
