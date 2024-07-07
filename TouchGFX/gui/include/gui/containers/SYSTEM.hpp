#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <gui_generated/containers/SYSTEMBase.hpp>

class SYSTEM : public SYSTEMBase
{
public:
    SYSTEM();
    virtual ~SYSTEM() {}

    virtual void initialize();
protected:
};

#endif // SYSTEM_HPP
