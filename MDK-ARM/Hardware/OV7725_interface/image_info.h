#ifndef OV7725_IMAGE_H_
#define OV7725_IMAGE_H_
///////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
///////////////////////////////////////////////////////////////////////////////////////////

struct image_mix{
    uint8_t  image_data[153600];              /*两位代表一像素*/ 


    struct{                             /* 输出图像大小 */
        enum{
            QVGA=0,
            VGA=1,
        }MOD;
        
        enum{
            RGB444=0,
            RGB565=1,
        }format;
        uint16_t width;                 /* 宽度 */
        uint16_t height;                /* 高度 */
    }shape;

    /* ATK-MC7725F模块灯光模式枚举 */
    enum
    {
        LIGHT_MODE_AUTO = 0x00,         /* Auto */
        LIGHT_MODE_SUNNY,               /* Sunny */
        LIGHT_MODE_CLOUDY,              /* Cloudy */
        LIGHT_MODE_OFFICE,              /* Office */
        LIGHT_MODE_HOME,                /* Home */
        LIGHT_MODE_NIGHT,               /* Night */
    }light_mode_t;

    /* ATK-MC7725F模块色彩饱和度枚举 */
    enum
    {
        COLOR_SATURATION_0 = 0x00,      /* +4 */
        COLOR_SATURATION_1,             /* +3 */
        COLOR_SATURATION_2,             /* +2 */
        COLOR_SATURATION_3,             /* +1 */
        COLOR_SATURATION_4,             /* 0 */
        COLOR_SATURATION_5,             /* -1 */
        COLOR_SATURATION_6,             /* -2 */
        COLOR_SATURATION_7,             /* -3 */
        COLOR_SATURATION_8,             /* -4 */
    } color_saturation_t;

    /* ATK-MC7725F模块亮度枚举 */
    enum
    {
        BRIGHTNESS_0 = 0x00,            /* +4 */
        BRIGHTNESS_1,                   /* +3 */
        BRIGHTNESS_2,                   /* +2 */
        BRIGHTNESS_3,                   /* +1 */
        BRIGHTNESS_4,                   /* 0 */
        BRIGHTNESS_5,                   /* -1 */
        BRIGHTNESS_6,                   /* -2 */
        BRIGHTNESS_7,                   /* -3 */
        BRIGHTNESS_8,                   /* -4 */
    } brightness_t;

    /* ATK-MC7725F模块特殊效果枚举 */
    enum
    {
        SPECIAL_EFFECT_NORMAL = 0x00,   /* Normal */
        SPECIAL_EFFECT_BW,              /* B&W */
        SPECIAL_EFFECT_BLUISH,          /* Bluish */
        SPECIAL_EFFECT_SEPIA,           /* Sepia */
        SPECIAL_EFFECT_REDISH,          /* Redish */
        SPECIAL_EFFECT_GREENISH,        /* Greenish */
        SPECIAL_EFFECT_NEGATIVE,        /* Negative */
    } special_effect_t;

    /* ATK-MC7725F模块对比度枚举 */
    enum
    {
        CONTRAST_0 = 0x00,              /* +4 */
        CONTRAST_1,                     /* +3 */
        CONTRAST_2,                     /* +2 */
        CONTRAST_3,                     /* +1 */
        CONTRAST_4,                     /* 0 */
        CONTRAST_5,                     /* -1 */
        CONTRAST_6,                     /* -2 */
        CONTRAST_7,                     /* -3 */
        CONTRAST_8,                     /* -4 */
    } contrast_t;

    struct{                             /* 接收图像帧信息 */
        enum                            /* 处理标记 */
        {
            FRAME_HANDLE_DONE = 0x00,   /* 处理完成 */
            FRAME_HANDLE_PEND,          /* 等待处理 */
        }handle_flag;
        uint16_t count;                 /* 计数 */
    }frame;
};
extern struct image_mix image;

/* ATK-MC7725F模块在不同输出模式下的最大输出分辨率 */
#define VGA_WIDTH_MAX   640
#define VGA_HEIGHT_MAX  480
#define QVGA_WIDTH_MAX  320
#define QVGA_HEIGHT_MAX 240








/* ATK-MC7725F模块输出模式枚举 */
typedef enum
{
    OUTPUT_MODE_VGA = 0x00,         /* VGA */
    OUTPUT_MODE_QVGA,               /* QVGA */
} output_mode_t;
typedef enum
{
    GET_FRAME_TYPE_NOINC = 0x00,    /* 图片存储地址不自增 */
    GET_FRAME_TYPE_AUTO_INC,        /* 图片存储地址自增 */
} get_frame_type_t;

#endif



