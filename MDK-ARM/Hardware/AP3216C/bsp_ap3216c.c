/**
  ******************************************************************************
  * @file   bsp_ap3216c.c
  * @brief  光强度、接近、红外传感器AP3216C驱动
  *   
  ******************************************************************************
  */
#include "bsp_ap3216c.h"
#include "i2c.h"
//
volatile StruAP3216C_Val gAP3216C_Val;	//AP3216数据结构
//
/* 写寄存器的值 */
static void write_reg(uint8_t reg, uint8_t data)
{
		HAL_I2C_Mem_Write(&hi2c1, AP3216C_ADDR_WRITE, reg, 1, &data, 1, 10);
}

/* 读寄存器的值 */
static void read_regs(uint8_t reg, uint8_t len, uint8_t *buf)
{
	HAL_I2C_Mem_Read(&hi2c1, AP3216C_ADDR_READ, reg, 1, buf, len, 10);	
}

/* 软件复位传感器 */
static void reset_sensor(void)
{
    write_reg(AP3216C_SYS_CONFIGURATION_REG, AP3216C_MODE_SW_RESET); // reset
}

/**
 * This function is convenient to getting data except including high and low
 * data for this sensor. note:after reading lower register first,reading higher
 * add one.
 */
static uint32_t read_low_and_high(uint8_t reg, uint8_t len)
{
    uint32_t data;
    uint8_t  buf = 0;

    read_regs(reg, len, &buf); // 读低字节
    data = buf;
    read_regs(reg + 1, len, &buf);  // 读高字节
    data = data + (buf << len * 8); // 合并数据

    return data;
}

/**
 * This function is only used to set threshold without filtering times
 *
 * @param cmd first register , and other cmd count by it.
 * @param threshold threshold and filtering times of als threshold
 */
static void set_als_threshold(ap3216c_cmd_t cmd, ap3216c_threshold_t threshold)
{
    uint8_t Resolution;
    double  DB = 1.0;

    /* 读光照强度的范围 */
    ap3216c_get_param(AP3216C_ALS_RANGE, &Resolution);

    if (Resolution == AP3216C_ALS_RANGE_20661) {
        // 光照强度范围 0 - 20661
        DB = 0.35; // 光照强度的分辨率
    } else if (Resolution == AP3216C_ALS_RANGE_5162) {
        // 光照强度范围 0 - 5162
        DB = 0.0788; // 光照强度的分辨率
    } else if (Resolution == AP3216C_ALS_RANGE_1291) {
        // 光照强度范围 0 - 1291
        DB = 0.0197; // 光照强度的分辨率
    } else if (Resolution == AP3216C_ALS_RANGE_323) {
        // 光照强度范围 0 - 323
        DB = 0.0049; // 光照强度的分辨率
    }

    threshold.min /= DB; // 根据不同的分辨率来设置
    threshold.max /= DB;

    ap3216c_set_param(cmd, (threshold.min & 0xff));
    ap3216c_set_param((ap3216c_cmd_t)(cmd + 1), (threshold.min >> 8));
    ap3216c_set_param((ap3216c_cmd_t)(cmd + 2), (threshold.max & 0xff));
    ap3216c_set_param((ap3216c_cmd_t)(cmd + 3), threshold.max >> 8);
}

static void set_ps_threshold(ap3216c_cmd_t cmd, ap3216c_threshold_t threshold)
{
    if (threshold.min > 1020) {
        // 大于1020 时需要设置低字节的低两位
        ap3216c_set_param(cmd, (threshold.min - 1020 & 0x03));
    }

    ap3216c_set_param((ap3216c_cmd_t)(cmd + 1),
                      threshold.min / 4); // 设置高字节参数

    if (threshold.max > 1020) {
        // 大于1020 时需要设置低字节的低两位
        ap3216c_set_param((ap3216c_cmd_t)(cmd + 2),
                          (threshold.max - 1020 & 0x03));
    }

    ap3216c_set_param((ap3216c_cmd_t)(cmd + 3),
                      threshold.max / 4); // 设置高字节参数
}

/**
 * This function reads status register by ap3216c sensor measurement
 *
 * @param no
 *
 * @return status register value.
 */

uint8_t ap3216c_get_IntStatus(void)
{
    uint8_t IntStatus;

    /* 读中断状态寄存器 */

    read_regs(AP3216C_SYS_INT_STATUS_REG, 1, &IntStatus);
    // IntStatus 第 0 位表示 ALS 中断，第 1 位表示 PS 中断。

    return IntStatus; // 返回状态
}

static void ap3216c_int_init(void) { ; }

/**
 * @brief  配置 中断输入引脚
 * @param  无
 * @retval 无
 */
void ap3216c_int_Config(void) { ; }

/**
 * This function initializes ap3216c registered device driver
 *
 * @param no
 *
 * @return the ap3216c device.
 */
void ap3216c_init(void)
{
    /* reset ap3216c */
    reset_sensor();
    HAL_Delay(100);
    ap3216c_set_param(AP3216C_SYSTEM_MODE, AP3216C_MODE_ALS_AND_PS);
    HAL_Delay(150); // delay at least 112.5ms
		//
    ap3216c_int_Config();
    ap3216c_int_init();
}
/**
 * This function reads light by ap3216c sensor measurement
 *
 * @param no
 *
 * @return the ambient light converted to float data.
 */
float ap3216c_read_ambient_light(void)
{
    float brightness = 0; 
    uint16_t read_data;
    uint8_t  range;

    read_data = (uint16_t)read_low_and_high(AP3216C_ALS_DATA_L_REG, 1);
    ap3216c_get_param(AP3216C_ALS_RANGE, &range);
    if (range == AP3216C_ALS_RANGE_20661) {
        brightness =
            0.35 * read_data; // sensor ambient light converse to reality
    } else if (range == AP3216C_ALS_RANGE_5162) {
        brightness =
            0.0788 * read_data; // sensor ambient light converse to reality
    } else if (range == AP3216C_ALS_RANGE_1291) {
        brightness =
            0.0197 * read_data; // sensor ambient light converse to reality
    } else if (range == AP3216C_ALS_RANGE_323) {
        brightness =
            0.0049 * read_data; // sensor ambient light converse to reality
    }
    return brightness;
}

/**
 * This function reads proximity by ap3216c sensor measurement
 *
 * @param no
 *
 * @return the proximity data.
 */
uint16_t ap3216c_read_ps_data(void)
{
    uint16_t proximity = 0;

    uint32_t read_data;
    read_data = read_low_and_high(AP3216C_PS_DATA_L_REG, 1); // read two data
    // printf("ap3216c_read_ps_data read_data %d\n",read_data);
    if (1 == ((read_data >> 6) & 0x01 || (read_data >> 14) & 0x01)) {
        return proximity =
                   55555; // 红外过高（IR），PS无效 返回一个 55555 的无效数据
    }

    proximity =
        (read_data & 0x000f) + (((read_data >> 8) & 0x3f)
                                << 4); // sensor proximity converse to reality

    proximity |= read_data & 0x8000; // 取最高位，0 表示物体远离，1 表示物体靠近

    return proximity; // proximity 后十位是数据位，最高位为状态位
}

/**
 * This function reads ir by ap3216c sensor measurement
 *
 * @param no
 *
 * @return the ir data.
 */
uint16_t ap3216c_read_ir_data(void)
{
    uint16_t proximity = 0;

    uint32_t read_data;
    read_data = read_low_and_high(AP3216C_IR_DATA_L_REG, 1); // read two data
    // printf("ap3216c_read_ir_data read_data %d\n",read_data);
    proximity =
        (read_data & 0x0003) +
        ((read_data >> 8) & 0xFF); // sensor proximity converse to reality

    return proximity;
}

/**
 * This function sets parameter of ap3216c sensor
 *
 * @param cmd the parameter cmd of device
 * @param value for setting value in cmd register
 *
 * @return the setting parameter status,RT_EOK reprensents setting successfully.
 */
void ap3216c_set_param(ap3216c_cmd_t cmd, uint8_t value)
{
    switch (cmd) {
        case AP3216C_SYSTEM_MODE:
            {
                /* default 000,power down */
                write_reg(AP3216C_SYS_CONFIGURATION_REG, value);
                break;
            }
        case AP3216C_INT_PARAM:
            {
                write_reg(AP3216C_SYS_INT_CLEAR_MANNER_REG, value);

                break;
            }

        case AP3216C_ALS_RANGE:
            {
                uint8_t args;

                read_regs(AP3216C_ALS_CONFIGURATION_REG, 1, &args);
                args &= 0xcf;
                args |= value << 4;
                write_reg(AP3216C_ALS_CONFIGURATION_REG, args);

                break;
            }
        case AP3216C_ALS_PERSIST:
            {
                uint8_t args = 0;

                read_regs(AP3216C_ALS_CONFIGURATION_REG, 1, &args);
                args &= 0xf0;
                args |= value;
                write_reg(AP3216C_ALS_CONFIGURATION_REG, args);

                break;
            }
        case AP3216C_ALS_LOW_THRESHOLD_L:
            {
                write_reg(AP3216C_ALS_THRESHOLD_LOW_L_REG, value);

                break;
            }
        case AP3216C_ALS_LOW_THRESHOLD_H:
            {
                write_reg(AP3216C_ALS_THRESHOLD_LOW_H_REG, value);

                break;
            }
        case AP3216C_ALS_HIGH_THRESHOLD_L:
            {
                write_reg(AP3216C_ALS_THRESHOLD_HIGH_L_REG, value);

                break;
            }
        case AP3216C_ALS_HIGH_THRESHOLD_H:
            {
                write_reg(AP3216C_ALS_THRESHOLD_HIGH_H_REG, value);

                break;
            }
        case AP3216C_PS_GAIN:
            {
                uint8_t args = 0;

                read_regs(AP3216C_PS_CONFIGURATION_REG, 1, &args);
                args &= 0xf3;
                args |= value;
                write_reg(AP3216C_PS_CONFIGURATION_REG, args);

                break;
            }
        case AP3216C_PS_PERSIST:
            {
                uint8_t args = 0;

                read_regs(AP3216C_PS_CONFIGURATION_REG, 1, &args);
                args &= 0xfc;
                args |= value;
                write_reg(AP3216C_PS_CONFIGURATION_REG, args);

                break;
            }
        case AP3216C_PS_LOW_THRESHOLD_L:
            {
                write_reg(AP3216C_PS_THRESHOLD_LOW_L_REG, value);

                break;
            }
        case AP3216C_PS_LOW_THRESHOLD_H:
            {
                write_reg(AP3216C_PS_THRESHOLD_LOW_H_REG, value);

                break;
            }
        case AP3216C_PS_HIGH_THRESHOLD_L:
            {
                write_reg(AP3216C_PS_THRESHOLD_HIGH_L_REG, value);

                break;
            }
        case AP3216C_PS_HIGH_THRESHOLD_H:
            {
                write_reg(AP3216C_PS_THRESHOLD_HIGH_H_REG, value);

                break;
            }

        default:
            {
            }
    }
}

/**
 * This function gets parameter of ap3216c sensor
 *
 * @param cmd the parameter cmd of device
 * @param value to get value in cmd register
 *
 * @return the getting parameter status,RT_EOK reprensents getting successfully.
 */
void ap3216c_get_param(ap3216c_cmd_t cmd, uint8_t *value)
{
    switch (cmd) {
        case AP3216C_SYSTEM_MODE:
            {
                read_regs(AP3216C_SYS_CONFIGURATION_REG, 1, value);

                break;
            }
        case AP3216C_INT_PARAM:
            {
                read_regs(AP3216C_SYS_INT_CLEAR_MANNER_REG, 1, value);

                break;
            }
        case AP3216C_ALS_RANGE:
            {
                uint8_t temp;

                read_regs(AP3216C_ALS_CONFIGURATION_REG, 1, value);
                temp = (*value & 0xff) >> 4;

                *value = temp;

                break;
            }
        case AP3216C_ALS_PERSIST:
            {
                uint8_t temp;

                read_regs(AP3216C_ALS_CONFIGURATION_REG, 1, value);
                temp = *value & 0x0f;

                *value = temp;

                break;
            }
        case AP3216C_ALS_LOW_THRESHOLD_L:
            {
                read_regs(AP3216C_ALS_THRESHOLD_LOW_L_REG, 1, value);

                break;
            }
        case AP3216C_ALS_LOW_THRESHOLD_H:
            {
                read_regs(AP3216C_ALS_THRESHOLD_LOW_H_REG, 1, value);

                break;
            }
        case AP3216C_ALS_HIGH_THRESHOLD_L:
            {
                read_regs(AP3216C_ALS_THRESHOLD_HIGH_L_REG, 1, value);

                break;
            }
        case AP3216C_ALS_HIGH_THRESHOLD_H:
            {
                read_regs(AP3216C_ALS_THRESHOLD_HIGH_H_REG, 1, value);

                break;
            }
        case AP3216C_PS_GAIN:
            {
                uint8_t temp;

                read_regs(AP3216C_PS_CONFIGURATION_REG, 1, &temp);

                *value = (temp & 0xc) >> 2;

                break;
            }
        case AP3216C_PS_PERSIST:
            {
                uint8_t temp;

                read_regs(AP3216C_PS_CONFIGURATION_REG, 1, &temp);

                *value = temp & 0x3;

                break;
            }
        case AP3216C_PS_LOW_THRESHOLD_L:
            {
                read_regs(AP3216C_PS_THRESHOLD_LOW_L_REG, 1, value);

                break;
            }
        case AP3216C_PS_LOW_THRESHOLD_H:
            {
                read_regs(AP3216C_PS_THRESHOLD_LOW_H_REG, 1, value);
                break;
            }
        case AP3216C_PS_HIGH_THRESHOLD_L:
            {
                read_regs(AP3216C_PS_THRESHOLD_HIGH_L_REG, 1, value);

                break;
            }
        case AP3216C_PS_HIGH_THRESHOLD_H:
            {
                read_regs(AP3216C_PS_THRESHOLD_HIGH_H_REG, 1, value);

                break;
            }

        default:
            {
            }
    }
}



