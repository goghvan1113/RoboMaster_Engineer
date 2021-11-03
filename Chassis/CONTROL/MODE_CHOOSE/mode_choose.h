#ifndef _MODE_CHOOSE_H
#define _MODE_CHOOSE_H

#include "sys.h"

/*

��������ģʽ��ѡ��
���̸�����̨�ı�־λ�����п���,��̨ÿ����һ������,��ᷢ����Ӧ�ı�־λ
��ʵ�ʲ�����,��Щ��������ϣ��ֻ����һ��,��Ӧ�ĵ��̲�λ���ܵ���ָ��λ��,
����Щ��λ�ǳ�������,�������Ƶ�,������˶����ĸ����
���,��Ҫ����Щ��λ�ϸ�ֿ����п���,���ⷢ����־λ�ĸ���,���²��ֲ�λʧ��
��Ҫ��Ϊ3������:  1�������˶����(��̨��ʱ�ᷢ���ٶ�,ֻ������ٶȽ�������õ�������)
                 2����Ԯ���;�Ԯצ:����һ�ΰ���,��ϣ������ֵ��λ��
                 3�����̵������ʯ��ת���:����һ�ΰ���,��ϣ������ֵ��λ��
ÿ�����ֵ�ģ�����в�ͬ,���,������Ҫ7����Ӧ��״̬�����п���


*/


typedef enum
{// ���̵ĸ߶�,�Կ��ƿ󾮵��
	Reset   = 0,           // ���̵���͵�λ��
	Height1 = 1,           // ���(ȡһ��)
	Height2 = 2,           // ��һ��,׼���ٴ�С��Դ����ȡһ��
	Height3 = 3,           // ������,׼���ٴ�С��Դ����ȡһ��
	Height4 = 4,           // ������,��ʱ�߶�Ӧ��Height3һ��,���Ե�һЩ
	Initial = 5,
}Mine_Height;

typedef enum
{// ��ʯ��ת���
	Stop_Rotate      = 0, // ֹͣ
	Clockwise        = 1, // ˳ʱ��
	CounterClockwise = 2, // ��ʱ��
}Rotate_Motor;

typedef enum
{// ��Ԯ������
	CARD_BACK = 0,
	CARD_OUT  = 1,
}Rescue_Card;

typedef enum
{// ��Ԯ�������/����
	CLAW_OUT  = 0,
	CLAW_BACK = 1,
}Rescue_Claw;

typedef struct
{// ����״̬����
	Mine_Height   MineHeight_e;         // �󾮸߶�
	Rotate_Motor  RotateMotor_e;        // ��ʯ��ת���
	Rescue_Card   RescueCard_e;         // ��Ԯ������
	Rescue_Claw   RescueClaw_e;         // ��Ԯ�������/����
}Chassis_State;


#define Chassis_State_DEFAULT \
{\
	.MineHeight_e    = Reset,\
	.RotateMotor_e   = Stop_Rotate,\
	.RescueCard_e   = CARD_BACK,\
	.RescueClaw_e   = CLAW_BACK,\
}


void Clear_ChassisState(void);                             // ��ʼ������״̬

void Change_MineHeight(Mine_Height TargetHeight);          // �ı�󾮸߶�
void Change_RotateState(Rotate_Motor Goal);                // ��ʯ��ת����(ͣ��˳/��ʱ��ת��)
void Change_ResCueCard_State(Rescue_Card Goal);            // ��Ԯ��
void Change_ResCueClaw_State(Rescue_Claw On_Or_Off);       // ��Ԯ����

void Change_LastRotateMotor_State( Rotate_Motor state );   // �ı��ʯ��ת�������һ��״̬

Chassis_State GetChassisState(bool now_state);             // ��õ��̵�ǰ״̬
void ModeChoose(uint8_t *Info);                            // ������̨��Ϣ,�ı����״̬

#endif

