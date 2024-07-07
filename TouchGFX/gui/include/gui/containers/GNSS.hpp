#ifndef GNSS_HPP
#define GNSS_HPP

#include <gui_generated/containers/GNSSBase.hpp>

class GNSS : public GNSSBase
{
public:
    GNSS();
    virtual ~GNSS() {}

    virtual void initialize();

    void setITEM(int no)
    {
        switch(no%6)
        {
            case 0:
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"GPS");
                break;
            case 1:		//无触发事件时，姿态读取图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"BDS");
                break;
            case 2:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"GLONASS");
                break;
            case 3:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"GALILEO");
                break;
            case 4:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"QZSS");
                break;
            case 5:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"MIX");
                break;
        }
    }

    void setCAM(int no)
    {
        switch(no%7)
        {
            case 0:
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"NORMAL");
                break;
            case 1:		//无触发事件时，姿态读取图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"BW");
                break;
            case 2:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"BLUISH");
                break;
            case 3:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"SEPIA");
                break;
            case 4:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"REDISH");
                break;
            case 5:		//无触发事件时，环境信息图标与文字
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"GREENISH");
                break;
            case 6:
                Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE,"NEGATIVE");
                break;
        }
    }

protected:
};

#endif // GNSS_HPP
