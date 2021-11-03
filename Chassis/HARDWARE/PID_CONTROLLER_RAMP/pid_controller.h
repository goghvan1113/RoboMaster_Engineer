/*
*	ʵ��ͨ�õ�PID������
*/


#ifndef __PID_CONTROLLER_H__
#define __PID_CONTROLLER_H__

#include "sys.h"

#define PID_DEFAULT_PRECISION	0.0f	//���ƾ��ȣ���Ŀ���ٶ���ʵ���ٶ�С�ڴ�ֵʱ����Ϊû����ʹPID���ȶ�
#define PID_DEFAULT_ERRALL_MAX 2000	//����ERR_ALL���ֵ������ERR_ALL���ֵ���󣬻�ʹPID��Ӧ�������ȶ��������޷�
#define PID_DEFAULT_OUTPUT_MAX 2000	//����޷�
#define PID_DEFAULT_OUTPUT_STEP_MAX 2000	//���΢���޷�

typedef enum
{	
	IncrementPID_e = 0,//����ʽPID
	PositionPID_e = 1,//λ��ʽPID
}PID_Type_e;

typedef enum
{
	Normal_e = 0,////PID����������״̬
	Ramp_e = 1,//PID������б�º���״̬
	Ramping_Add = 2,//б�»�û��ɣ������Ǽ�
	Ramping_Reduce = 3,//б�»�û��ɣ������Ǽ�
	RampDefault_Step = 100,//б�º�������
	RampDefault_Time = 1,//�������ٴβŰ�count����1������
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
	float RampTartgetTime;//�������ٴβŰ�count����1������
	float RampTartgetStep;//б�º�������
	uint8_t PID_WorkType;//PID������λ��ʽ��������ʽ
	float PID_Precision;//PID��С����
	float PID_ErrAllMax;//PID�����޷�
	float PID_OutMax;//PID����޷�
	float PID_OutStep;//PID�����������
}PID_t;


void PID_Update(PID_t* WhichPID, float NowInput);//����PID�����ݣ�������PID������ֵ
float PID_GetPositionPID(PID_t* WhichPID);
float PID_GetIncrementalPID(PID_t* WhichPID);
void PID_Clear(PID_t* WhichPID);
void PID_SetTargetWithRamp(PID_t* WhichPID,float Tartget);
void PID_DefaultInit(PID_t* WhichPID);

#endif



