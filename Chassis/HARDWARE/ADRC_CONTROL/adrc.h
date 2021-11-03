#ifndef _ADRC_H
#define _ADRC_H

#include "sys.h"
#include "math.h"
#include "CAN_TASK.h"

#define T 0.001    //��������1ms
#define r 500      //�ٶ�����,����΢��������
#define h 0.001    //�˲�����,����΢��������
#define d r * h    //fst����
#define d0 h * d   //fst����

typedef struct{
	
	float x1;
	float x2;
	
	float b;
	float Kp;
	float Kd;	
	
	uint16_t w0;
	float z1;
	float z2;
	float z3;
	
	float e;
	float e1;
	float e2;
	
	float u0;
	float output;
	
	uint8_t MotorSerialNumber;
	
}ADRC_Param;

#define ADRC_DEFAULT \
{\
	.x1 = 0.0f,\
	.x2 = 0.0f,\
	.b = 0.0f,\
	.Kp = 0.0f,\
	.Kd = 0.0f,\
	.w0 = 0,\
	.z1 = 0.0f,\
	.z2 = 0.0f,\
	.z3 = 0.0f,\
	.e = 0.0f,\
	.e1 = 0.0f,\
	.e2 = 0.0f,\
	.u0 = 0.0f,\
	.output = 0.0f,\
	.MotorSerialNumber = 0,\
}

float ADRC_PROCEDURE( ADRC_Param *ADRC, int16_t Target );
float fst( float v1, float x2 );
void ESO( ADRC_Param *ADRC );
void TD( ADRC_Param *ADRC, int16_t Target );
void ADRC_Init( ADRC_Param *ADRC, uint16_t W0, float b, float kp, float kd, uint8_t Motor_Number );

#endif

