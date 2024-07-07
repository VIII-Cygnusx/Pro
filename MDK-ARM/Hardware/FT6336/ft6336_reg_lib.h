#ifndef FT6336_REG_LIB_H_
#define FT6336_REG_LIB_H_

//
#define I2C_ADDR_FT6336 0x38
//
#define FT6336_ADDR_READ  0x71
#define FT6336_ADDR_WRITE 0x70

// Touch Parameter
#define FT6336_PRES_DOWN 0x2
#define FT6336_COORD_UD 0x1

// Registers
#define FT6336_ADDR_DEVICE_MODE 0x00



#define FT6336_ADDR_GESTURE_ID 0x01
#define FT6336_ADDR_TD_STATUS 0x02

#define FT6336_ADDR_TOUCH1_EVENT 0x03
#define FT6336_ADDR_TOUCH1_ID 0x05
#define FT6336_ADDR_TOUCH1_X 0x03
#define FT6336_ADDR_TOUCH1_Y 0x05
#define FT6336_ADDR_TOUCH1_WEIGHT 0x07
#define FT6336_ADDR_TOUCH1_MISC 0x08

#define FT6336_ADDR_TOUCH2_EVENT 0x09
#define FT6336_ADDR_TOUCH2_ID 0x0B
#define FT6336_ADDR_TOUCH2_X 0x09
#define FT6336_ADDR_TOUCH2_Y 0x0B
#define FT6336_ADDR_TOUCH2_WEIGHT 0x0D
#define FT6336_ADDR_TOUCH2_MISC 0x0E

#define FT6336_ADDR_THRESHOLD 0x80
#define FT6336_ADDR_FILTER_COE 0x85
#define FT6336_ADDR_CTRL 0x86

#define FT6336_ADDR_TIME_ENTER_MONITOR 0x87
#define FT6336_ADDR_ACTIVE_MODE_RATE 0x88
#define FT6336_ADDR_MONITOR_MODE_RATE 0x89

#define FT6336_ADDR_RADIAN_VALUE 0x91
#define FT6336_ADDR_OFFSET_LEFT_RIGHT 0x92
#define FT6336_ADDR_OFFSET_UP_DOWN 0x93
#define FT6336_ADDR_DISTANCE_LEFT_RIGHT 0x94
#define FT6336_ADDR_DISTANCE_UP_DOWN 0x95
#define FT6336_ADDR_DISTANCE_ZOOM 0x96

#define FT6336_ADDR_LIBRARY_VERSION_H 0xA1
#define FT6336_ADDR_LIBRARY_VERSION_L 0xA2
#define FT6336_ADDR_CHIP_ID 0xA3
#define FT6336_ADDR_G_MODE 0xA4


#define FT6336_ADDR_POWER_MODE 0xA5
#define FT6336_ADDR_FIRMARE_ID 0xA6
#define FT6336_ADDR_FOCALTECH_ID 0xA8
#define FT6336_ADDR_RELEASE_CODE_ID 0xAF
#define FT6336_ADDR_STATE 0xBC




#endif