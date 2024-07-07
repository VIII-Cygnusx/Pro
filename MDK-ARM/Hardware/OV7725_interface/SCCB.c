#include "SCCB.h"

struct SCCB sccb_hw={.SCL_PORT=SCCB_SCL_GPIO_Port,
                     .SDA_PORT=SCCB_SDA_GPIO_Port,
                     .SCL=SCCB_SCL_Pin,
                     .SDA=SCCB_SDA_Pin,
                     .delay=&HAL_Delay
};


/**
 * @brief       设置SCCB接口SDA引脚为输入模式
 * @param       无
 * @retval      无
 */
static void sccb_set_sda_input(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    gpio_init_struct.Pin    = sccb_hw.SDA;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(sccb_hw.SDA_PORT, &gpio_init_struct);
}

/**
 * @brief       设置SCCB接口SDA引脚为输出模式
 * @param       无
 * @retval      无
 */
static void sccb_set_sda_output(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    gpio_init_struct.Pin    = sccb_hw.SDA;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(sccb_hw.SDA_PORT, &gpio_init_struct);
}




/**
 * @brief       SCCB接口起始信号
 * @param       无
 * @retval      无
 */
void sccb_start(void){
    SCCB_SDA(1);
    SCCB_SCL(1);
    sccb_hw.delay(10);
    SCCB_SDA(0);
    sccb_hw.delay(10);
    SCCB_SCL(0);
}

/**
 * @brief       SCCB接口停止信号
 * @param       无
 * @retval      无
 */
static void sccb_stop(void)
{
    SCCB_SDA(0);
    sccb_hw.delay(10);
    SCCB_SCL(1);
    sccb_hw.delay(10);
    SCCB_SDA(1);
    sccb_hw.delay(10);
}

/**
 * @brief       SCCB接口主机向从机写入一个字节数据
 * @param       dat: 待写入的一个字节数据
 * @retval      无
 */
static void sccb_write_byte(uint8_t dat)
{
    int8_t dat_index;
    uint8_t dat_bit;
    
    for (dat_index=7; dat_index>=0; dat_index--)
    {
        dat_bit = (dat >> dat_index) & 0x01;
        SCCB_SDA(dat_bit);
        sccb_hw.delay(10);
        SCCB_SCL(1);
        sccb_hw.delay(10);
        SCCB_SCL(0);
    }
    
    SCCB_SDA(1);
    sccb_hw.delay(10);
    SCCB_SCL(1);
    sccb_hw.delay(10);
    SCCB_SCL(0);
}
/**
 * @brief       SCCB接口主机向从机读取一个字节数据
 * @param       dat: 读取到的一个字节数据
 * @retval      无
 */
static void sccb_read_byte(uint8_t *dat)
{
    int8_t dat_index;
    uint8_t dat_bit;
    
#if (SCCB_GPIO_PULLUP != 0)
    sccb_set_sda_input();
#endif
    
    for (dat_index=7; dat_index>=0; dat_index--)
    {
        sccb_hw.delay(10);
        SCCB_SCL(1);
        dat_bit = SCCB_READ_SDA();
        *dat |= (dat_bit << dat_index);
        sccb_hw.delay(10);
        SCCB_SCL(0);
    }
    
    sccb_hw.delay(10);
    SCCB_SCL(1);
    sccb_hw.delay(10);
    SCCB_SCL(0);
    sccb_hw.delay(10);
    SCCB_SDA(0);
    sccb_hw.delay(10);
    
#if (SCCB_GPIO_PULLUP != 0)
    sccb_set_sda_output();
#endif
}


void sccb_3_phase_write(uint8_t id_addr, uint8_t sub_addr, uint8_t dat)
{
    sccb_start();
    sccb_write_byte((id_addr << 1) | SCCB_WRITE);
    sccb_write_byte(sub_addr);
    sccb_write_byte(dat);
    sccb_stop();
}

void sccb_2_phase_write(uint8_t id_addr, uint8_t sub_addr)
{
    sccb_start();
    sccb_write_byte((id_addr << 1) | SCCB_WRITE);
    sccb_write_byte(sub_addr);
    sccb_stop();
}

void sccb_2_phase_read(uint8_t id_addr, uint8_t *dat)
{
    sccb_start();
    sccb_write_byte((id_addr << 1) | SCCB_READ);
    sccb_read_byte(dat);
    sccb_stop();
}


uint8_t read_reg(uint8_t reg)
{
    uint8_t dat = 0;
    
    sccb_2_phase_write(SCCB_ADDR, reg);
    sccb_2_phase_read(SCCB_ADDR, &dat);
    
    return dat;
}



void write_reg(uint8_t reg, uint8_t dat)
{
    sccb_3_phase_write(SCCB_ADDR, reg, dat);
}

