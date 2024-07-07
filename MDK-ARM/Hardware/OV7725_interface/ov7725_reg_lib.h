#ifndef OV7725_REG_LIB_H_
#define OV7725_REG_LIB_H_
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REG_BLUE        0x01
#define REG_RED         0x02
#define REG_PID         0x0A
#define REG_VER         0x0B
#define REG_COM3        0x0C
#define REG_COM4        0x0D
#define REG_COM5        0x0E
#define REG_COM6        0x0F
#define REG_CLKRC       0x11
#define REG_COM7        0x12
#define REG_COM8        0x13
#define REG_COM9        0x14
#define REG_HSTART      0x17
#define REG_HSIZE       0x18
#define REG_VSTRT       0x19
#define REG_VSIZE       0x1A
#define REG_MIDH        0x1C
#define REG_MIDL        0x1D
#define REG_BDBase      0x22
#define REG_BDMStep     0x23
#define REG_AEW         0x24
#define REG_AEB         0x25
#define REG_VPT         0x26
#define REG_HOutSize    0x29
#define REG_EXHCH       0x2A
#define REG_EXHCL       0x2B
#define REG_VOutSize    0x2C
#define REG_ADVFL       0x2D
#define REG_ADVFH       0x2E
#define REG_HREF        0x32
#define REG_TGT_B       0x42
#define REG_FixGain     0x4D
#define REG_UFIX        0x60
#define REG_VFIX        0x61
#define REG_AWB_Ctrl0   0x63
#define REG_DSP_Ctrl1   0x64
#define REG_DSP_Ctrl2   0x65
#define REG_DSP_Ctrl3   0x66
#define REG_DSP_Ctrl4   0x67
#define REG_AWBCtrl3    0x6B
#define REG_GAM1        0x7E
#define REG_GAM2        0x7F
#define REG_GAM3        0x80
#define REG_GAM4        0x81
#define REG_GAM5        0x82
#define REG_GAM6        0x83
#define REG_GAM7        0x84
#define REG_GAM8        0x85
#define REG_GAM9        0x86
#define REG_GAM10       0x87
#define REG_GAM11       0x88
#define REG_GAM12       0x89
#define REG_GAM13       0x8A
#define REG_GAM14       0x8B
#define REG_GAM15       0x8C
#define REG_SLOP        0x8D
#define REG_EDGE1       0x90
#define REG_DNSOff      0x91
#define REG_EDGE2       0x92
#define REG_EDGE3       0x93
#define REG_MTX1        0x94
#define REG_MTX2        0x95
#define REG_MTX3        0x96
#define REG_MTX4        0x97
#define REG_MTX5        0x98
#define REG_MTX6        0x99
#define REG_MTX_Ctrl    0x9A
#define REG_BRIGHT      0x9B
#define REG_CNST        0x9C
#define REG_UVADJ0      0x9E
#define REG_SDE         0xA6
#define REG_USAT        0xA7
#define REG_VSAT        0xA8
#define REG_HUECOS      0xA9
#define REG_HUESIN      0xAA
#define REG_SIGN        0xAB
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const uint8_t init_cfg[][2] = {
    {REG_CLKRC,     0x00},  /* 时钟配置 */
    {REG_COM7,      0x46},  /* QVGA RGB565 */
    {REG_HSTART,    0x3F},  /* 水平图像开始 */
    {REG_HSIZE,     0x50},  /* 水平图像宽度320*/
    {REG_VSTRT,     0x03},  /* 垂直开始 */
    {REG_VSIZE,     0x78},  /* 垂直高度240 */
    {REG_HREF,      0x00},  /* 杂项 */
    {REG_HOutSize,  0x50},  /* 水平输出宽度 */
    {REG_VOutSize,  0x78},  /* 垂直输出高度 */
    {REG_TGT_B,     0x7F},  /* 寄存器TGT_B */
    {REG_FixGain,   0x09},  /* 寄存器FixGain */
    {REG_AWB_Ctrl0, 0xE0},  /* 寄存器AWB_Ctrl0 */
    {REG_DSP_Ctrl1, 0xFF},  /* 寄存器DSP_Ctrl1 */
    {REG_DSP_Ctrl2, 0x00},  /* 寄存器DSP_Ctrl2 */
    {REG_DSP_Ctrl3, 0x00},  /* 寄存器DSP_Ctrl3 */
    {REG_DSP_Ctrl4, 0x00},  /* 寄存器DSP_Ctrl4 */
    {REG_COM8,      0xF0},  /* 寄存器COM8 */
    {REG_COM4,      0xC1},  /* 寄存器COM4 */
    {REG_COM6,      0xC5},  /* 寄存器COM6 */
    {REG_COM9,      0x11},  /* 寄存器COM9 */
    {REG_BDBase,    0x7F},  /* 寄存器BDBase */
    {REG_BDMStep,   0x03},  /* 寄存器BDMStep */
    {REG_AEW,       0x40},  /* 寄存器AEW */
    {REG_AEB,       0x30},  /* 寄存器AEB */
    {REG_VPT,       0xA1},  /* 寄存器VPT */
    {REG_EXHCL,     0x9E},  /* 寄存器EXHCL */
    {REG_AWBCtrl3,  0xAA},  /* 寄存器AWBCtrl3 */
    {REG_COM8,      0xFF},  /* 寄存器COM8 */
    {REG_EDGE1,     0x08},  /* 寄存器EDGE1 */
    {REG_DNSOff,    0x01},  /* 寄存器DNSOff */
    {REG_EDGE2,     0x03},  /* 寄存器EDGE2 */
    {REG_EDGE3,     0x00},  /* 寄存器EDGE3 */
    {REG_MTX1,      0xB0},  /* 寄存器MTX1 */
    {REG_MTX2,      0x9D},  /* 寄存器MTX2 */
    {REG_MTX3,      0x13},  /* 寄存器MTX3 */
    {REG_MTX4,      0x16},  /* 寄存器MTX4 */
    {REG_MTX5,      0x7B},  /* 寄存器MTX5 */
    {REG_MTX6,      0x91},  /* 寄存器MTX6 */
    {REG_MTX_Ctrl,  0x1E},  /* 寄存器MTX_Ctrl */
    {REG_BRIGHT,    0x08},  /* 寄存器BRIGHT */
    {REG_CNST,      0x20},  /* 寄存器CNST */
    {REG_UVADJ0,    0x81},  /* 寄存器UVADJ0 */
    {REG_SDE,       0x06},  /* 寄存器SDE */
    {REG_USAT,      0x65},  /* 寄存器USAT */
    {REG_VSAT,      0x65},  /* 寄存器VSAT */
    {REG_HUECOS,    0x80},  /* 寄存器HUECOS */
    {REG_HUESIN,    0x80},  /* 寄存器HUESIN */
    {REG_GAM1,      0x0C},  /* 寄存器GAM1 */
    {REG_GAM2,      0x16},  /* 寄存器GAM2 */
    {REG_GAM3,      0x2A},  /* 寄存器GAM3 */
    {REG_GAM4,      0x4E},  /* 寄存器GAM4 */
    {REG_GAM5,      0x61},  /* 寄存器GAM5 */
    {REG_GAM6,      0x6F},  /* 寄存器GAM6 */
    {REG_GAM7,      0x7B},  /* 寄存器GAM7 */
    {REG_GAM8,      0x86},  /* 寄存器GAM8 */
    {REG_GAM9,      0x8E},  /* 寄存器GAM9 */
    {REG_GAM10,     0x97},  /* 寄存器GAM10 */
    {REG_GAM11,     0xA4},  /* 寄存器GAM11 */
    {REG_GAM12,     0xAF},  /* 寄存器GAM12 */
    {REG_GAM13,     0xC5},  /* 寄存器GAM13 */
    {REG_GAM14,     0xD7},  /* 寄存器GAM14 */
    {REG_GAM15,     0xE8},  /* 寄存器GAM15 */
    {REG_SLOP,      0x20},  /* 寄存器SLOP */
    {REG_COM3,      0x50},  /* 寄存器COM3 */
    {REG_COM5,      0xF5},  /* 寄存器COM5 */
};

#endif

