#ifndef ARONA_HPP
#define ARONA_HPP

#include <gui_generated/containers/ARONABase.hpp>


//user
#include <images/BitmapDatabase.hpp>
//user


class ARONA : public ARONABase
{
public:
    ARONA();
    virtual ~ARONA() {}

    virtual void initialize();


    //user
    void animation();
    //user
protected:
};

#endif // ARONA_HPP
