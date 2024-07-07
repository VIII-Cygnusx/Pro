#include "ov7725_api_lib.h"
#include "ov7725_interface.h"
#include "ov7725_reg_lib.h"


#include <stdio.h>
#include "spi.h"
#include "usart.h"
void OV7725_init_v(void){
    OV7725_WRST(1);
    OV7725_RRST(1);
    OV7725_OE  (1);
    OV7725_RCLK(1);
    OV7725_WEN (1);
    OV7725_reset_v();
    //OV7725_init_all_reg_v();
    if(set_output()==           EOK)    //HAL_UART_Transmit(&huart1,"1_output_ok\n",      sizeof("1_output_ok\n")-1,      10);
    //if(set_light_mode()==       EOK)    //HAL_UART_Transmit(&huart1,"2_light_ok\n",       sizeof("2_light_ok\n")-1,       10);
    //if(set_color_saturation()== EOK)    //HAL_UART_Transmit(&huart1,"3_color_ok\n",       sizeof("3_color_ok\n")-1,       10);
    //if(set_brightness()==       EOK)    //HAL_UART_Transmit(&huart1,"4_brightness_ok\n",  sizeof("4_brightness_ok\n")-1,  10);
    //if(set_contrast()==         EOK)    //HAL_UART_Transmit(&huart1,"5_contrast_ok\n",    sizeof("5_contrast_ok\n")-1,    10);
    //if(set_special_effect()==   EOK)    //HAL_UART_Transmit(&huart1,"6_special_ok\n",     sizeof("6_special_ok\n")-1,     10);
    //if(OV7725_manufacture_id()==EOK)    //HAL_UART_Transmit(&huart1,"7_mid_ok\n",         sizeof("7_mid_ok\n")-1,         10);
    //if(OV7725_product_id()==    EOK)    //HAL_UART_Transmit(&huart1,"8_pid_ok\n",         sizeof("8_pid_ok\n")-1,         10);
    
    enable_output_image();              //HAL_UART_Transmit(&huart1,"output_en\n",        sizeof("output_en\n")-1,        10);
    
}

uint8_t OV7725_manufacture_id(void){
    uint16_t id;
    id=ov7725_hw.read(REG_MIDH)<<8;
    id|=ov7725_hw.read(REG_MIDL);
    ////
    {
    //uint8_t XX[10];
    //sprintf(XX,"MID=%x",id);
    //HAL_UART_Transmit(&huart1,XX,sizeof(XX),10);
    }
    ////
    ov7725_hw.delay(2);
    if(id==MID)return EOK;
    else return EERROR;
}

uint8_t OV7725_product_id(void){
    uint16_t id;
    id=ov7725_hw.read(REG_PID)<<8;
    id|=ov7725_hw.read(REG_VER);
    ////
    {
    //uint8_t XX[10];
    //sprintf(XX,"PID=%x",id);
    //HAL_UART_Transmit(&huart1,XX,sizeof(XX),10);
    }
    ////
    ov7725_hw.delay(2);
    if(id==PID)return EOK;
    else return EERROR;
}

void OV7725_reset_v(void){
    ov7725_hw.write(REG_COM7,0x80); //复位
    ov7725_hw.delay(2);
}

void OV7725_init_all_reg_v(void){
    uint8_t reg_index;
    for (reg_index=0; reg_index<65; reg_index++)
    {
        ov7725_hw.write(init_cfg[reg_index][0], init_cfg[reg_index][1]);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //uint8_t TX[11];
        //sprintf(TX,"--%4.2f%%--\n",reg_index/65.0f*100.0f);
        //HAL_UART_Transmit(&huart1,TX,sizeof(TX),10);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

void enable_output_image(void){
    OV7725_OE(0);
}
void disable_output_image(void){
    OV7725_OE(1);
}






/**
 * @brief       设置ATK-MC7725F模块输出模式与尺寸
 * @param       image.shape.width : 输出图像宽度（VGA，<=640；QVGA，<=320）
 *              image.shape.height: 输出图像高度（VGA，<=480；QVGA，<=240）
 *              mode  : OUTPUT_MODE_VGA : VGA输出模式
 *                      OUTPUT_MODE_QVGA: QVGA输出模式
 * @retval      EOK   : 设置ATK-MC7725F模块输出模式成功
 *              EINVAL: 传入参数错误
 */
uint8_t set_output(void)
{
    uint16_t xs;
    uint16_t ys;
    uint8_t hstart_raw;
    uint8_t hstart_new;
    uint8_t vstrt_raw;
    uint8_t vstrt_new;
    uint8_t href_raw;
    uint8_t href_new;
    uint8_t exhch;

    
    switch (image.shape.MOD)
    {
        case VGA:
        {
            if ((image.shape.width > VGA_WIDTH_MAX) || (image.shape.height > VGA_HEIGHT_MAX))
            {
                return EINVAL;
            }
            break;
        }
        case QVGA:
        {
            if ((image.shape.width > QVGA_WIDTH_MAX) || (image.shape.height > QVGA_HEIGHT_MAX))
            {
                return EINVAL;
            }
            break;
        }
        default:
        {
            return EINVAL;
        }
    }
    
    switch (image.shape.MOD)
    {
        case VGA:
        {
            xs = (VGA_WIDTH_MAX - image.shape.width) >> 1;      //调整图像在水平方向上的位置,右移1位（相当于除以2）
            ys = (VGA_HEIGHT_MAX - image.shape.height) >> 1;    //调整图像在垂直方向上的位置,右移1位（相当于除以2）
            write_reg(REG_COM7, 0x06);
            write_reg(REG_HSTART, 0x23);
            write_reg(REG_HSIZE, 0xA0);
            write_reg(REG_VSTRT, 0x07);
            write_reg(REG_VSIZE, 0xF0);
            write_reg(REG_HREF, 0x00);
            write_reg(REG_HOutSize, 0xA0);
            write_reg(REG_VOutSize, 0xF0);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //HAL_UART_Transmit(&huart1,"VGA!!!\n",sizeof("VGA!!!\n")-1, 10);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            break;
        }
        case QVGA:
        {
            xs = (QVGA_WIDTH_MAX - image.shape.width) >> 1;
            ys = (QVGA_HEIGHT_MAX - image.shape.height) >> 1;
            write_reg(REG_COM7, 0x46);
            write_reg(REG_HSTART, 0x3F);
            write_reg(REG_HSIZE, 0x50);
            write_reg(REG_VSTRT, 0x03);
            write_reg(REG_VSIZE, 0x78);
            write_reg(REG_HREF, 0x00);
            write_reg(REG_HOutSize, 0x50);
            write_reg(REG_VOutSize, 0x78);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //HAL_UART_Transmit(&huart1,"QVGA!!!\n",sizeof("QVGA!!!\n")-1, 10);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            break;
        }
        default:
        {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //HAL_UART_Transmit(&huart1,"MODE_ERROR!!!\n",sizeof("MODE_ERROR!!!\n")-1, 10);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            return EINVAL;
        }
    }
    hstart_raw = read_reg(REG_HSTART);
    hstart_new = hstart_raw + (xs >> 2);
    write_reg(REG_HSTART, hstart_new);
    write_reg(REG_HSIZE, image.shape.width >> 2);
    image.shape.width = read_reg(REG_HSIZE) << 2;
    
    vstrt_raw = read_reg(REG_VSTRT);
    vstrt_new = vstrt_raw + (ys >> 1);
    write_reg(REG_VSTRT, vstrt_new);
    write_reg(REG_VSIZE, image.shape.height >> 1);
    image.shape.height = read_reg(REG_VSIZE) << 1;
    
    href_raw = read_reg(REG_HREF);
    href_new = ((ys & 0x01) << 6) | ((xs & 0x03) << 4) | ((image.shape.height & 0x01) << 2) | (image.shape.width & 0x03) | href_raw;
    write_reg(REG_HREF, href_new);
    
    write_reg(REG_HOutSize, image.shape.width >> 2);
    write_reg(REG_VOutSize, image.shape.height >> 1);
    
    exhch = (href_raw | (image.shape.width & 0x03) | ((image.shape.height & 0x01) << 2));
    write_reg(REG_EXHCH, exhch);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////         
    //uint8_t TX[26];
    //sprintf(TX,"Width= %03d,height= %03d\n",image.shape.width,image.shape.height);
    //HAL_UART_Transmit(&huart1,TX,26, 10);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return EOK;
}


/**
 * @brief       设置ATK-MC7725F模块灯光模式
 * @param       mode: LIGHT_MOED_AUTO  : Auto
 *                    LIGHT_MOED_SUNNY : Sunny
 *                    LIGHT_MOED_CLOUDY: Cloudy
 *                    LIGHT_MOED_OFFICE: Office
 *                    LIGHT_MOED_HOME  : Home
 *                    LIGHT_MOED_NIGHT : Night
 * @retval      EOK   : 设置ATK-MC7725模块灯光模式成功
 *              EINVAL: 传入参数错误
 */
uint8_t set_light_mode(void)
{
    switch (image.light_mode_t)
    {
        case LIGHT_MODE_AUTO:
        {
            write_reg(REG_COM8, 0xFF);
            write_reg(REG_COM5, 0x65);
            write_reg(REG_ADVFL, 0x00);
            write_reg(REG_ADVFH, 0x00);
            break;
        }
        case LIGHT_MODE_SUNNY:
        {
            write_reg(REG_COM8, 0xFD);
            write_reg(REG_BLUE, 0x5A);
            write_reg(REG_RED, 0x5C);
            write_reg(REG_COM5, 0x65);
            write_reg(REG_ADVFL, 0x00);
            write_reg(REG_ADVFH, 0x00);
            break;
        }
        case LIGHT_MODE_CLOUDY:
        {
            write_reg(REG_COM8, 0xFD);
            write_reg(REG_BLUE, 0x58);
            write_reg(REG_RED, 0x60);
            write_reg(REG_COM5, 0x65);
            write_reg(REG_ADVFL, 0x00);
            write_reg(REG_ADVFH, 0x00);
            break;
        }
        case LIGHT_MODE_OFFICE:
        {
            write_reg(REG_COM8, 0xFD);
            write_reg(REG_BLUE, 0x84);
            write_reg(REG_RED, 0x4C);
            write_reg(REG_COM5, 0x65);
            write_reg(REG_ADVFL, 0x00);
            write_reg(REG_ADVFH, 0x00);
            break;
        }
        case LIGHT_MODE_HOME:
        {
            write_reg(REG_COM8, 0xFD);
            write_reg(REG_BLUE, 0x96);
            write_reg(REG_RED, 0x40);
            write_reg(REG_COM5, 0x65);
            write_reg(REG_ADVFL, 0x00);
            write_reg(REG_ADVFH, 0x00);
            break;
        }
        case LIGHT_MODE_NIGHT:
        {
            write_reg(REG_COM8, 0xFF);
            write_reg(REG_COM5, 0xE5);
            break;
        }
        default:
        {
            return EINVAL;
        }
    }
    
    return EOK;
}

/**
 * @brief       设置ATK-MC7725F模块色彩饱和度
 * @param       saturation: COLOR_SATURATION_0: +4
 *                          COLOR_SATURATION_1: +3
 *                          COLOR_SATURATION_2: +2
 *                          COLOR_SATURATION_3: +1
 *                          COLOR_SATURATION_4: 0
 *                          COLOR_SATURATION_5: -1
 *                          COLOR_SATURATION_6: -2
 *                          COLOR_SATURATION_7: -3
 *                          COLOR_SATURATION_8: -4
 * @retval      EOK   : 设置ATK-MC7725F模块色彩饱和度成功
 *              EINVAL: 传入参数错误
 */
uint8_t set_color_saturation(void)
{
    switch (image.color_saturation_t)
    {
        case COLOR_SATURATION_0:
        {
            write_reg(REG_USAT, 0x80);
            write_reg(REG_VSAT, 0x80);
            break;
        }
        case COLOR_SATURATION_1:
        {
            write_reg(REG_USAT, 0x70);
            write_reg(REG_VSAT, 0x70);
            break;
        }
        case COLOR_SATURATION_2:
        {
            write_reg(REG_USAT, 0x60);
            write_reg(REG_VSAT, 0x60);
            break;
        }
        case COLOR_SATURATION_3:
        {
            write_reg(REG_USAT, 0x50);
            write_reg(REG_VSAT, 0x50);
            break;
        }
        case COLOR_SATURATION_4:
        {
            write_reg(REG_USAT, 0x40);
            write_reg(REG_VSAT, 0x40);
            break;
        }
        case COLOR_SATURATION_5:
        {
            write_reg(REG_USAT, 0x30);
            write_reg(REG_VSAT, 0x30);
            break;
        }
        case COLOR_SATURATION_6:
        {
            write_reg(REG_USAT, 0x20);
            write_reg(REG_VSAT, 0x20);
            break;
        }
        case COLOR_SATURATION_7:
        {
            write_reg(REG_USAT, 0x10);
            write_reg(REG_VSAT, 0x10);
            break;
        }
        case COLOR_SATURATION_8:
        {
            write_reg(REG_USAT, 0x00);
            write_reg(REG_VSAT, 0x00);
            break;
        }
        default:
        {
            return EINVAL;
        }
    }
    
    return EOK;
}

/**
 * @brief       设置ATK-MC7725F模块亮度
 * @param       brightness: BRIGHTNESS_0: +4
 *                          BRIGHTNESS_1: +3
 *                          BRIGHTNESS_2: +2
 *                          BRIGHTNESS_3: +1
 *                          BRIGHTNESS_4: 0
 *                          BRIGHTNESS_5: -1
 *                          BRIGHTNESS_6: -2
 *                          BRIGHTNESS_7: -3
 *                          BRIGHTNESS_8: -4
 * @retval      EOK   : 设置ATK-MC7725F模块亮度成功
 *              EINVAL: 传入参数错误
 */
uint8_t set_brightness(void)
{
    switch (image.brightness_t)
    {
        case BRIGHTNESS_0:
        {
            write_reg(REG_BRIGHT, 0x48);
            write_reg(REG_SIGN, 0x06);
            break;
        }
        case BRIGHTNESS_1:
        {
            write_reg(REG_BRIGHT, 0x38);
            write_reg(REG_SIGN, 0x06);
            break;
        }
        case BRIGHTNESS_2:
        {
            write_reg(REG_BRIGHT, 0x28);
            write_reg(REG_SIGN, 0x06);
            break;
        }
        case BRIGHTNESS_3:
        {
            write_reg(REG_BRIGHT, 0x18);
            write_reg(REG_SIGN, 0x06);
            break;
        }
        case BRIGHTNESS_4:
        {
            write_reg(REG_BRIGHT, 0x08);
            write_reg(REG_SIGN, 0x06);
            break;
        }
        case BRIGHTNESS_5:
        {
            write_reg(REG_BRIGHT, 0x08);
            write_reg(REG_SIGN, 0x0E);
            break;
        }
        case BRIGHTNESS_6:
        {
            write_reg(REG_BRIGHT, 0x18);
            write_reg(REG_SIGN, 0x0E);
            break;
        }
        case BRIGHTNESS_7:
        {
            write_reg(REG_BRIGHT, 0x28);
            write_reg(REG_SIGN, 0x0E);
            break;
        }
        case BRIGHTNESS_8:
        {
            write_reg(REG_BRIGHT, 0x38);
            write_reg(REG_SIGN, 0x0E);
            break;
        }
        default:
        {
            return EINVAL;
        }
    }
    
    return EOK;
}

/**
 * @brief       设置ATK-MC7725F模块特殊效果
 * @param       contrast: SPECIAL_EFFECT_NORMAL  : Normal
 *                        SPECIAL_EFFECT_BW      : B&W
 *                        SPECIAL_EFFECT_BLUISH  : Bluish
 *                        SPECIAL_EFFECT_SEPIA   : Sepia
 *                        SPECIAL_EFFECT_REDISH  : Redish
 *                        SPECIAL_EFFECT_GREENISH: Greenish
 *                        SPECIAL_EFFECT_NEGATIE : Negative
 * @retval      EOK   : 设置ATK-MC7725F模块特殊效果成功
 *              EINVAL: 传入参数错误
 */
uint8_t set_special_effect(void)
{
    switch (image.special_effect_t)
    {
        case SPECIAL_EFFECT_NORMAL:
        {
            write_reg(REG_SDE, 0x06);
            write_reg(REG_UFIX, 0x80);
            write_reg(REG_VFIX, 0x80);
            break;
        }
        case SPECIAL_EFFECT_BW:
        {
            write_reg(REG_SDE, 0x26);
            write_reg(REG_UFIX, 0x80);
            write_reg(REG_VFIX, 0x80);
            break;
        }
        case SPECIAL_EFFECT_BLUISH:
        {
            write_reg(REG_SDE, 0x1E);
            write_reg(REG_UFIX, 0xA0);
            write_reg(REG_VFIX, 0x40);
            break;
        }
        case SPECIAL_EFFECT_SEPIA:
        {
            write_reg(REG_SDE, 0x1E);
            write_reg(REG_UFIX, 0x40);
            write_reg(REG_VFIX, 0xA0);
            break;
        }
        case SPECIAL_EFFECT_REDISH:
        {
            write_reg(REG_SDE, 0x1E);
            write_reg(REG_UFIX, 0x80);
            write_reg(REG_VFIX, 0xC0);
            break;
        }
        case SPECIAL_EFFECT_GREENISH:
        {
            write_reg(REG_SDE, 0x1E);
            write_reg(REG_UFIX, 0x60);
            write_reg(REG_VFIX, 0x60);
            break;
        }
        case SPECIAL_EFFECT_NEGATIVE:
        {
            write_reg(REG_SDE, 0x46);
            break;
        }
        default:
        {
            return EINVAL;
        }
    }
    
    return EOK;
}

/**
 * @brief       设置ATK-MC7725F模块对比度
 * @param       contrast: CONTRAST_0: +4
 *                        CONTRAST_1: +3
 *                        CONTRAST_2: +2
 *                        CONTRAST_3: +1
 *                        CONTRAST_4: 0
 *                        CONTRAST_5: -1
 *                        CONTRAST_6: -2
 *                        CONTRAST_7: -3
 *                        CONTRAST_8: -4
 * @retval      EOK   : 设置ATK-MC7725F模块对比度成功
 *              EINVAL: 传入参数错误
 */
uint8_t set_contrast(void)
{
    switch (image.contrast_t)
    {
        case CONTRAST_0:
        {
            write_reg(REG_CNST, 0x30);
            break;
        }
        case CONTRAST_1:
        {
            write_reg(REG_CNST, 0x2C);
            break;
        }
        case CONTRAST_2:
        {
            write_reg(REG_CNST, 0x28);
            break;
        }
        case CONTRAST_3:
        {
            write_reg(REG_CNST, 0x24);
            break;
        }
        case CONTRAST_4:
        {
            write_reg(REG_CNST, 0x20);
            break;
        }
        case CONTRAST_5:
        {
            write_reg(REG_CNST, 0x1C);
            break;
        }
        case CONTRAST_6:
        {
            write_reg(REG_CNST, 0x18);
            break;
        }
        case CONTRAST_7:
        {
            write_reg(REG_CNST, 0x14);
            break;
        }
        case CONTRAST_8:
        {
            write_reg(REG_CNST, 0x10);
            break;
        }
        default:
        {
            return EINVAL;
        }
    }
    
    return EOK;
}




















//Private
uint8_t get_8bit_pix_data(void)
{
    uint8_t dat = 0;
    
    dat |= (((ov7725_hw.D0_PORT->IDR & ov7725_hw.D0) == 0) ? (0) : (1)) << 0;
    dat |= (((ov7725_hw.D1_PORT->IDR & ov7725_hw.D1) == 0) ? (0) : (1)) << 1;
    dat |= (((ov7725_hw.D2_PORT->IDR & ov7725_hw.D2) == 0) ? (0) : (1)) << 2;
    dat |= (((ov7725_hw.D3_PORT->IDR & ov7725_hw.D3) == 0) ? (0) : (1)) << 3;
    dat |= (((ov7725_hw.D4_PORT->IDR & ov7725_hw.D4) == 0) ? (0) : (1)) << 4;
    dat |= (((ov7725_hw.D5_PORT->IDR & ov7725_hw.D5) == 0) ? (0) : (1)) << 5;
    dat |= (((ov7725_hw.D6_PORT->IDR & ov7725_hw.D6) == 0) ? (0) : (1)) << 6;
    dat |= (((ov7725_hw.D7_PORT->IDR & ov7725_hw.D7) == 0) ? (0) : (1)) << 7;
    return dat;
}




void get_frame()
{
    uint16_t width;
    uint16_t height;
    uint16_t dat;
    
    if (image.frame.handle_flag == FRAME_HANDLE_DONE)
    {
        return ;
    }
    
    OV7725_RRST(0);
    OV7725_RCLK(0);
    OV7725_RCLK(1);
    OV7725_RCLK(0);
    OV7725_RRST(1);
    OV7725_RCLK(1);


    //ILI9341_WR_REG(0x2C);
////////////////////////////////////////////////////////////////////////////
//采集图像
{
    uint32_t ptr=0;
    for (height=0; height<image.shape.height; height++) //height
    {
        
        for (width=0; width<image.shape.width; width++) //width
        {
            uint8_t XX[2];

            OV7725_RCLK(0);
            XX[0]=get_8bit_pix_data();                  //采集uint16前8位 
            image.image_data[ptr*2] = XX[0];            //缓存         
            OV7725_RCLK(1);

            OV7725_RCLK(0);
            XX[1]=get_8bit_pix_data();                  //采集uint16后8位
            image.image_data[ptr*2+1] = XX[1];          //缓存
            OV7725_RCLK(1);
          
            ptr++;
        }
    }    
}

//采集图像
    // HAL_UART_Transmit(&huart1,"data:\n",sizeof("data:\n")-1,10);
    // for (height=0; height<image.shape.height; height++) //240
    // {
    //     HAL_UART_Transmit(&huart1,"L",sizeof("L")-1,10);
    //     for (width=0; width<image.shape.width; width++) //320
    //     {
    //         uint16_t XX=0;

    //         OV7725_RCLK(0);
    //         XX=(get_byte_data()<<8); //采集uint16前8位               
    //         OV7725_RCLK(1);

    //         OV7725_RCLK(0);
    //         XX|=get_byte_data(); //采集uint16后8位
    //         OV7725_RCLK(1);
        
    //     uint8_t TT[4];
    //     sprintf(TT,"%04X",XX);
    //     HAL_UART_Transmit(&huart1,TT,4,10);

    //     }
        
    //     HAL_UART_Transmit(&huart1,"\n",sizeof("\n")-1,10);
    // }

    image.frame.handle_flag = FRAME_HANDLE_DONE;
    image.frame.count++;
}

#include "ili9341_interface.h"
//输出图像
void send_frame2LCD(uint16_t x,uint16_t y)
{
    uint32_t length = image.shape.height * image.shape.width*2,i=0,j=0; // 图像数据总长度
    uint8_t temp[10]={0};
    ILI9341_SetArea(x, y,x+image.shape.width-1, y+image.shape.height-1);
    LCD.W_REG(ILI9341dev.wramcmd);//整个页面更新
    while(i<length){
        for(j=0;j<10;j++)temp[j] = image.image_data[j+i];
        HAL_SPI_Transmit(&hspi1,temp,10,1);
        i+=10;
    }    
}

