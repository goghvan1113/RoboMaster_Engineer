/*
*	实现通用的PID控制器
*/


#ifndef __PID_CONTROLLER_H__
#define __PID_CONTROLLER_H__

#include "sys.h"

#define PID_DEFAULT_PRECISION	0.0f	//控制精度，当目标速度与实际速度小于此值时，认为没有误差，使PID更稳定
#define PID_DEFAULT_ERRALL_MAX 2000	//控制ERR_ALL最大值，否则ERR_ALL最大值过大，会使PID反应慢，不稳定，积分限幅
#define PID_DEFAULT_OUTPUT_MAX 2000	//输出限幅
#define PID_DEFAULT_OUTPUT_STEP_MAX 2000	//输出微分限幅

typedef enum
{	
	IncrementPID_e = 0,//增量式PID
	PositionPID_e = 1,//位置式PID
}PID_Type_e;

typedef enum
{
	Normal_e = 0,////PID工作在正常状态
	Ramp_e = 1,//PID工作在斜坡函数状态
	Ramping_Add = 2,//斜坡还没完成，并且是加
	Ramping_Reduce = 3,//斜坡还没完成，并且是减
	RampDefault_Step = 100,//斜坡函数步幅
	RampDefault_Time = 1,//计数多少次才把count加上1个步幅
}PID_RampState_e;

typedef struct
{
    float Kp1;				
    float Ki1;				
    float Kd1;				
    float PID_Err_now;		
    float PID_Err_last;
	float PID_Err_lastlast;
    float PID_Err_all;	
    float PID_Out;
	float PID_lastout;
    float PID_Target;
	float PID_Input;
	uint8_t State_RampOrNormal;
	float RampTarget;
	float RampCountTime;
	float RampTartgetTime;//计数多少次才把count加上1个步幅
	float RampTartgetStep;//斜坡函数步幅
	uint8_t PID_WorkType;//PID工作在位置式还是增量式
	float PID_Precision;//PID最小精度
	float PID_ErrAllMax;//PID积分限幅
	float PID_OutMax;//PID输出限幅
	float PID_OutStep;//PID输出步幅限制
}PID_t;


void PID_Update(PID_t* WhichPID, float NowInput);//更新PID的数据，即更新PID的输入值
float PID_GetPositionPID(PID_t* WhichPID);
float PID_GetIncrementalPID(PID_t* WhichPID);
void PID_Clear(PID_t* WhichPID);
void PID_SetTargetWithRamp(PID_t* WhichPID,float Tartget);
void PID_DefaultInit(PID_t* WhichPID);

#endif



