#include "ANTOTC.h"
/***********************************************************************
 * @brief 适配匿名上位机v7，目前只有发送功能，待完善
 * @param[in] 
 * @param[out] 
 * @return [viod]
 * @date 2023/10/25
 * @version 1.0.0
 **********************************************************************/
void ANTO_Send(const enum ANTO_SEND FUNCTION)	//发送协议
{
	uint8_t Anto[20]={0};
	switch(FUNCTION) 
	{
		// case ANTO_IMU:
		// 	Anto[0] = 0XAA;
		// 	Anto[1] = 0xFF;
		// 	Anto[2] = ANTO_IMU;
		// 	Anto[3] = 13;
		// 	int16_t AX=(int16_t)(IMU_data.ACC_X*10.0f);
		// 	Anto[4] = BYTE0(AX);
		// 	Anto[5] = BYTE1(AX);
		// 	int16_t AY=(int16_t)(IMU_data.ACC_Y*10.0f);					
		// 	Anto[6] = BYTE0(AY);
		// 	Anto[7] = BYTE1(AY);
		// 	int16_t AZ=(int16_t)(IMU_data.ACC_Z*10.0f);			
		// 	Anto[8] = BYTE0(AZ);
		// 	Anto[9] = BYTE1(AZ);
		// 	int16_t GX=(int16_t)(IMU_data.GYR_X);			
		// 	Anto[10] = BYTE0(GX);
		// 	Anto[11] = BYTE1(GX);
		// 	int16_t GY=(int16_t)(IMU_data.GYR_Y);			
		// 	Anto[12] = BYTE0(GY);
		// 	Anto[13] = BYTE1(GY);
		// 	int16_t GZ=(int16_t)(IMU_data.GYR_Z);			
		// 	Anto[14] = BYTE0(GZ);
		// 	Anto[15] = BYTE1(GZ);			
		// 	Anto[16] = 0;
		// break;
		// case ANTO_QUA:     //发送四元数
		// 	Anto[0] = 0XAA;
		// 	Anto[1] = 0xFF;
		// 	Anto[2] = ANTO_QUA;
		// 	Anto[3] = 9;
		// 	int16_t W0=(int16_t)(Q.w*10000.0f);
		// 	Anto[4] = BYTE0(W0);
		// 	Anto[5] = BYTE1(W0);
		// 	int16_t Q1;
		// 	Q1=(int16_t)(Q.q1*10000.0f);			
		// 	Anto[6] = BYTE0(Q1);
		// 	Anto[7] = BYTE1(Q1);
		// 	int16_t Q2;
		// 	Q2=(int16_t)(Q.q2*10000.0f);				
		// 	Anto[8] = BYTE0(Q2);
		// 	Anto[9] = BYTE1(Q2);
		// 	int16_t Q3;
		// 	Q3=(int16_t)(Q.q3*10000.0f);				
		// 	Anto[10] = BYTE0(Q3);
		// 	Anto[11] = BYTE1(Q3);
		// 	Anto[12]=0;
		// break;	
		case ANTO_STATUS:     //send angle
			Anto[0] = 0XAA;
			Anto[1] = 0xFF;
			Anto[2] = ANTO_STATUS;
			Anto[3] = 7;
			int16_t now_roll=(int16_t)(ROLL*100.0f);			
			Anto[4] = BYTE0(now_roll);
			Anto[5] = BYTE1(now_roll);
			int16_t now_pitch=(int16_t)(PITCH*100.0f);			
			Anto[6] = BYTE0(now_pitch);
			Anto[7] = BYTE1(now_pitch);
			int16_t now_yaw=(int16_t)(YAW*100.0f);			
			Anto[8] = BYTE0(now_yaw);
			Anto[9] = BYTE1(now_yaw);
			Anto[10] = 0;
		break;	
	}
	int16_t sumcheck=0;
	int16_t addcheck=0;
	for(int i=0;i<(Anto[3]+4);i++){
		sumcheck+=Anto[i];
		addcheck+=sumcheck;
	}
	Anto[(Anto[3]+4)]=((uint8_t)sumcheck);
	Anto[(Anto[3]+4)+1]=((uint8_t)addcheck);
	HAL_UART_Transmit(&huart1,Anto,Anto[3]+6,100);
}
