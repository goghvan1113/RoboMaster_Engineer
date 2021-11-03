#ifndef _CHASSIS_RUN_H_
#define _CHASSIS_RUN_H_

#include "sys.h"

#define L1  0.3       //RM2021�������̵�������ߴ�/2(m)
#define L2  0.3       //RM2021�������̵��̺���ߴ�/2(m)
#define L0  -0.15     //RM2021�������̵�������ƫ�ĳߴ�/(m), ���Զ�λ-0.1
#define L01 0         //RM2021�������̵��̺���ƫ�ĳߴ�/(m), ���Զ�λ0
#define WHEEL_DIAMETER 1.52    //����ֱ��:dm

typedef struct{
//�����ٶ�������
	int16_t Vx;
	int16_t Vy;
	int16_t Vw;
	
//�����ĸ�������ٶ�
	int16_t V1;
	int16_t V2;
	int16_t V3;
	int16_t V4;
}ChassisSpeed;


void ChassisMotorRun_Init(void);
void SetChassisMotorSpeed_WithRamp(uint8_t num, int16_t TargetSpeed);
void SetChassisMotorPosition_WithRamp(uint8_t num, int16_t TargetSpeed);
int16_t GetChassisTargetSpeed(uint8_t i);


void ChassisRunMotorCtrl(void);                    			  //������̵��ٶ��ڿ���
void SetChassisMotorCurrent( uint8_t SPEED );      			  //���õ��̵��ĵ������������Ϊ���ʣ�һ��Ϊ1
void SpeedSolving(void);                         			  //�ٶȽ�������Ӧ�ṹ��
void SetChassisSpeed(int16_t VX, int16_t VY, int16_t VW);     //���õ��̵��ٶ�������


#endif



