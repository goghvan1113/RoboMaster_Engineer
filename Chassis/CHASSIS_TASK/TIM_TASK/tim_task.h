#ifndef _TIM_TASK_H_
#define _TIM_TASK_H_

#include "sys.h"

// ���Ƶ����ϰ���ץȡ���Ƹ����Ԯ�������Ƹ������ֵ��˶�ʱ��

typedef enum                   // ��Ԯ���Ƹ˵Ŀ�ʱ����
{
	RLA_Null         = 0,        // ��(��ʼ̬),ע��:�ڿ����ջش˵��Ƹ˺�,����ΪRLA_Null
	RLA_Hero         = 1,        // ��ԮӢ��
	RLA_Infantry     = 2,        // ��Ԯ����
	Tim_Del_Forward  = 3,        // �ɾ�ԮӢ�۳���,������Ԯ��������
	Tim_Del_Backward = 4,        // �ɾ�Ԯ��������,������ԮӢ�۳���
}Rescue_LinearActuator_TimSetCount;

typedef enum
{
	OLA_Null   = 0,                // ��(��ʼ̬),ע��:�ڿ����ջش˵��Ƹ˺�,����ΪOLA_Null
	OLA_Out_1  = 1,                // �쵽���ϰ����ϵĿ�ƽ��
	OLA_Out_2  = 2,                // ��ִ��OLA_Out_1��,��ִ�д�,��ʹ���Ƹ˽������ܶ����ϰ���ĸ߶�
	OLA_Back_1 = 3,                // ��ִ��OLA_Out_1��,��ִ�д�,��ʹ���Ƹ�������ܰ����ϰ���ĸ߶�
}Obstacle_LinearActuator_TimSetCount;

typedef enum
{
	Not               = 0,
	RLA_HeroReady     = 1,
	RLA_InfantryReady = 2,
	OLA_Out1Ready,
	OLA_Out2Ready,
	OLA_Back1Ready,
	Res_Tim_Del_Ready
}TimReady;

void RLA_Time_Task(void);
void OLA_Time_Task(void);
void Set_RLA_Target( Rescue_LinearActuator_TimSetCount rla_target );
void Set_OLA_Target( Obstacle_LinearActuator_TimSetCount ola_target );
void Resetcount( void );
TimReady Get_RLA_ReadyFlag( void );
TimReady Get_OLA_ReadyFlag( void );


#endif

