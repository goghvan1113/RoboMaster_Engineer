/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       pid.c/h
  * @brief      pidʵ�ֺ�����������ʼ����PID���㺯����
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. ���
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2016 DJI****************************
  */
#ifndef PID_H
#define PID_H
#include "sys.h"

enum PID_MODE
{
    PID_POSITION = 0,
    PID_DELTA    = 1,
	Integral_seperated = 2,   //���ַ���PID(����ʽ)
	Anti_Integral_saturation = 3,    //�����ֱ���PID(����ʽ)
	Incomplete_DerivativePID = 4,    //����ȫ΢��PID(����ʽ)
};


enum TYPE
{
	angle = 0,          //���ڼ���Ƕ�
	speed = 1,          //���ڼ����ٶ�
	ecd_angle = 2,      //���ڼ�������ֵ
};

typedef struct PID_TypeDef
{
    uint8_t mode;
	uint8_t type;

    //PID ������
    float Kp;
    float Ki;
    float Kd;

    float max_out;  //������
    float max_iout; //���������

    float ref;
    float fdb;

    float output;
    float Pout;
    float Iout;
    float Dout;
    float Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
    float error[3]; //����� 0���� 1��һ�� 2���ϴ�

	void (*Init)(struct PID_TypeDef *pid, uint8_t mode, uint8_t type, const float PID[], float max_out, float max_iout);
	float (*Calc)(struct PID_TypeDef *pid);
	void (*Clear)(struct PID_TypeDef *pid);
	
}PID_TypeDef;


#define PID_POSITION_DEFAULT \
{\
	.mode = PID_POSITION,\
	.type = speed,\
	.Kp = 0,\
	.Ki = 0,\
	.Kd = 0,\
	.max_out = 0,\
    .max_iout = 0,\
	.ref = 0,\
	.fdb = 0,\
    .Dbuf[0] = 0.0f ,\
	.Dbuf[1] = 0.0f ,\
	.Dbuf[2] = 0.0f,\
    .error[0] = 0.0f ,\
	.error[1] = 0.0f ,\
	.error[2] = 0.0f ,\
	.Pout = 0.0f ,\
	.Iout = 0.0f ,\
	.Dout = 0.0f ,\
	.output = 0.0f,\
	.Init = &PID_Init,\
	.Calc = &PID_Calc,\
	.Clear = &PID_clear,\
}

#define PID_INCREAMENTAL_DEFAULT  \
{\
	.mode = PID_DELTA,\
	.type = speed,\
	.Kp = 0,\
	.Ki = 0,\
	.Kd = 0,\
	.max_out = 0,\
    .max_iout = 0,\
	.ref = 0,\
	.fdb = 0,\
    .Dbuf[0] = 0.0f ,\
	.Dbuf[1] = 0.0f ,\
	.Dbuf[2] = 0.0f,\
    .error[0] = 0.0f ,\
	.error[1] = 0.0f ,\
	.error[2] = 0.0f ,\
	.Pout = 0.0f ,\
	.Iout = 0.0f ,\
	.Dout = 0.0f ,\
	.output = 0.0f,\
	.Init = &PID_Init,\
	.Calc = &PID_Calc,\
	.Clear = &PID_clear,\
}


void PID_Init(PID_TypeDef *pid, uint8_t mode,uint8_t type, const float PID[], float max_out, float max_iout);
float PID_Calc(PID_TypeDef *pid);
void PID_clear(PID_TypeDef *pid);

#endif

