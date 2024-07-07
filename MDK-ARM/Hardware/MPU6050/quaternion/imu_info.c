#include "imu_info.h"
struct imu_data IMU_data;
struct Quaternion Q={   .w=1,
                        .q1=0,
                        .q2=0,
                        .q3=0,
};
struct imu_info IMU_conf={  .ACC_range  =   _4G_,
                            .GYRO_range =   _2000dps_,
                            .DLPF       =   _A5_1K_G5_1K_,
                            .CLOCK      =   _XPLL_,
};  
/* 一维卡尔曼协方差参数 */
struct _1_ekf_filter ekf[6] = {{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543},{0.02,0,0,0,0.001,0.543}};
