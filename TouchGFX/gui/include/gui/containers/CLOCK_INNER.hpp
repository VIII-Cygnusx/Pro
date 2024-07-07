#ifndef CLOCK_INNER_HPP
#define CLOCK_INNER_HPP

#include <gui_generated/containers/CLOCK_INNERBase.hpp>

class CLOCK_INNER : public CLOCK_INNERBase
{
public:
    CLOCK_INNER();
    virtual ~CLOCK_INNER() {}

    virtual void initialize();


    //user
    void setHour(int no)
    {
        switch(no % 24)
        {
        case 0:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "0");
        break;
        case 1:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "1");
        break;
        case 2:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "2");
        break;
        case 3:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "3");
        break;
        case 4:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "4");
        break;
        case 5:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "5");
        break;
        case 6:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "6");
        break;
        case 7:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "7");
        break;
        case 8:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "8");
        break;
        case 9:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "9");
        break;
        case 10:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "10");
        break;
        case 11:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "11");
        break;
        case 12:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "12");
        break;
        case 13:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "13");
        break;
        case 14:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "14");
        break;
        case 15:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "15");
        break;
        case 16:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "16");
        break;
        case 17:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "17");
        break;
        case 18:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "18");
        break;
        case 19:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "19");
        break;
        case 20:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "20");
        break;
        case 21:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "21");
        break;
        case 22:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "22");
        break;
        case 23:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "23");
        break;
        }
    }

    void setMIN(int no)
    {
        switch(no % 60)
        {
        case 0:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "0");
        break;
        case 1:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "1");
        break;
        case 2:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "2");
        break;
        case 3:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "3");
        break;
        case 4:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "4");
        break;
        case 5:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "5");
        break;
        case 6:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "6");
        break;
        case 7:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "7");
        break;
        case 8:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "8");
        break;
        case 9:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "9");
        break;
        case 10:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "10");
        break;
        case 11:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "11");
        break;
        case 12:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "12");
        break;
        case 13:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "13");
        break;
        case 14:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "14");
        break;
        case 15:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "15");
        break;
        case 16:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "16");
        break;
        case 17:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "17");
        break;
        case 18:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "18");
        break;
        case 19:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "19");
        break;
        case 20:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "20");
        break;
        case 21:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "21");
        break;
        case 22:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "22");
        break;
        case 23:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "23");
        break;
        case 24:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "24");
        break;
        case 25:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "25");
        break;
        case 26:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "26");
        break;
        case 27:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "27");
        break;
        case 28:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "28");
        break;
        case 29:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "29");
        break;
        case 30:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "30");
        break;
        case 31:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "31");
        break;
        case 32:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "32");
        break;
        case 33:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "33");
        break;
        case 34:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "34");
        break;
        case 35:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "35");
        break;
        case 36:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "36");
        break;
        case 37:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "37");
        break;
        case 38:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "38");
        break;
        case 39:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "39");
        break;
        case 40:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "40");
        break;
        case 41:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "41");
        break;
        case 42:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "42");
        break;
        case 43:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "43");
        break;
        case 44:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "44");
        break;
        case 45:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "45");
        break;
        case 46:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "46");
        break;
        case 47:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "47");
        break;
        case 48:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "48");
        break;
        case 49:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "49");
        break;
        case 50:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "50");
        break;
        case 51:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "51");
        break;
        case 52:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "52");
        break;
        case 53:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "53");
        break;
        case 54:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "54");
        break;
        case 55:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "55");
        break;
        case 56:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "56");
        break;
        case 57:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "57");
        break;
        case 58:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "58");
        break;
        case 59:
            Unicode::snprintf(txtBuffer, TXT_SIZE, "59");
        break;
        }
    }

    //user
protected:
};

#endif // CLOCK_INNER_HPP
