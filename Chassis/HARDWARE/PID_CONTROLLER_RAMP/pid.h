/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       pid.c/h
  * @brief      pid实现函数，包括初始化，PID计算函数，
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. 完成
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
	Integral_seperated = 2,   //积分分离PID(增量式)
	Anti_Integral_saturation = 3,    //抗积分饱和PID(增量式)
	Incomplete_DerivativePID = 4,    //不完全微分PID(增量式)
};


enum TYPE
{
	angle = 0,          //用于计算角度
	speed = 1,          //用于计算速度
	ecd_angle = 2,      //用于计算码盘值
};

typedef struct PID_TypeDef
{
    uint8_t mode;
	uint8_t type;

    //PID 三参数
    float Kp;
    float Ki;
    float Kd;

    float max_out;  //最大输出
    float max_iout; //最大积分输出

    float ref;
    float fdb;

    float output;
    float Pout;
    float Iout;
    float Dout;
    float Dbuf[3];  //微分项 0最新 1上一次 2上上次
    float error[3]; //误差项 0最新 1上一次 2上上次

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

