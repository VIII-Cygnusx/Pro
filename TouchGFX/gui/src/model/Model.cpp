#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

//user
unsigned char fifo_data[32];
//user

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}


//MPU6050
void Model::IMU_RX()
{
    unsigned char more;
    mpu_read_fifo_stream(32, fifo_data, &more);
}

void Model::IMU_ANGLE(float* RX)
{
        long quat[4];
        float q30 = 1073741824.0f;
        float q0=1.0f, q1=0.0f, q2=0.0f,q3=0.0f;
        quat[0] =   ((long)fifo_data[0 ] << 24) | ((long)fifo_data[1 ] << 16) |
                    ((long)fifo_data[2 ] << 8)  |        fifo_data[3 ];
        quat[1] =   ((long)fifo_data[4 ] << 24) | ((long)fifo_data[5 ] << 16) |
                    ((long)fifo_data[6 ] << 8)  |        fifo_data[7 ];
        quat[2] =   ((long)fifo_data[8 ] << 24) | ((long)fifo_data[9 ] << 16) |
                    ((long)fifo_data[10] << 8)  |        fifo_data[11];
        quat[3] =   ((long)fifo_data[12] << 24) | ((long)fifo_data[13] << 16) |
                    ((long)fifo_data[14] << 8)  |        fifo_data[15];
		q0=quat[0] / q30;
		q1=quat[1] / q30;
		q2=quat[2] / q30;
		q3=quat[3] / q30;        
        RX[0]   = fast_sin( (-2) * q1 * q3 + 2 * q0 * q2 ) * 57.3f;
		RX[2]	= atan2_approx( 2 * q2 * q3 + 2 * q0 * q1 , (-2) * q1 * q1 - 2 * q2 * q2 + 1) * 57.3f;
		RX[1]	= atan2_approx( 2 * (q1 * q2 + q0 * q3) , q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) * 57.3f;
}
unsigned int Model::STEP_RX()
{
        Update_step();
        return gSportStep;	
}
//MPU6050


//OV7725
void Model::OV7725_sample()
{
    get_frame();
}
void Model::OV7725_send2LCD(int x,int y)
{
    send_frame2LCD(x,y);
}
//OV7725


//MAX30102
extern "C"
{
void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer,  int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, 
																									 int32_t *pn_heart_rate, int8_t  *pch_hr_valid);    
}

void Model::MAX30102_INIT()
{
    maxim_max30102_init();
}
bool Model::MAX30102_OK()
{
    uint8_t uch_dummy = 0x00;
    maxim_max30102_read_reg(REG_INTR_STATUS_1,&uch_dummy);
    if((uch_dummy&0xC0) == 0x00) return false;
    else                         return true;
}
void Model::MAX30102_RX(int *RED,int *IR,int counter)
{
            maxim_max30102_read_fifo((aun_red_buffer+counter), (aun_ir_buffer+counter));
            *RED = *(aun_red_buffer+counter);
            *IR  = *(aun_ir_buffer+counter);
}
void Model::MAX30102_HR_OS(int *O2,int *HR)
{   
        int8_t ch_spo2_valid,ch_hr_valid;
        maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, MAX30102_BUFF_LENGTH, aun_red_buffer,         \
                                                &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);      \
        if(ch_hr_valid){
            *HR = n_heart_rate/4;
        }
        else *HR = 0;
        if(ch_spo2_valid){
            *O2 = n_sp02;
        }
        else *O2 = 0;
        maxim_max30102_reset();
}
//MAX30102

//SHT20
void Model::SHT20_RX(float *tem,float *hum)
{
        BSP_SHT20_GetData();
        *tem = gTemRH_Val.Tem;
        *hum = gTemRH_Val.Hum;
}
//SHT20


//AP3216C
float Model::AP3216C_RX()
{
    return (float)ap3216c_read_ambient_light();
}
//AP3216C

