#ifndef _CHASSIS_RUN_H_
#define _CHASSIS_RUN_H_

#include "sys.h"

#define L1  0.3       //RM2021赛季工程底盘纵向尺寸/2(m)
#define L2  0.3       //RM2021赛季工程底盘横向尺寸/2(m)
#define L0  -0.15     //RM2021赛季工程底盘纵向偏心尺寸/(m), 测试定位-0.1
#define L01 0         //RM2021赛季工程底盘横向偏心尺寸/(m), 测试定位0
#define WHEEL_DIAMETER 1.52    //麦轮直径:dm

typedef struct{
//底盘速度三分量
	int16_t Vx;
	int16_t Vy;
	int16_t Vw;
	
//底盘四个电机的速度
	int16_t V1;
	int16_t V2;
	int16_t V3;
	int16_t V4;
}ChassisSpeed;


void ChassisMotorRun_Init(void);
void SetChassisMotorSpeed_WithRamp(uint8_t num, int16_t TargetSpeed);
void SetChassisMotorPosition_WithRamp(uint8_t num, int16_t TargetSpeed);
int16_t GetChassisTargetSpeed(uint8_t i);


void ChassisRunMotorCtrl(void);                    			  //代表底盘的速度在控制
void SetChassisMotorCurrent( uint8_t SPEED );      			  //设置底盘的四电机电流，参数为倍率，一般为1
void SpeedSolving(void);                         			  //速度解算至对应结构体
void SetChassisSpeed(int16_t VX, int16_t VY, int16_t VW);     //设置底盘的速度三分量


#endif



