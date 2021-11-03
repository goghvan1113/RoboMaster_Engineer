#ifndef _MODE_CHOOSE_H
#define _MODE_CHOOSE_H

#include "sys.h"

/*

底盘运行模式的选择
底盘根据云台的标志位来进行控制,云台每按下一个按键,便会发送相应的标志位
在实际操作中,有些按键我们希望只按下一次,对应的底盘部位就能到达指定位置,
而有些部位是持续按键,持续控制的,如底盘运动的四个电机
因此,需要将这些部位严格分开进行控制,避免发生标志位的覆盖,导致部分部位失控
主要分为3个部分:  1、底盘运动电机(云台随时会发送速度,只需进行速度解算和设置电流即可)
                 2、救援卡和救援爪:按下一次按键,便希望到达值定位置
                 3、矿井盘电机、矿石旋转电机:按下一次按键,便希望到达值定位置
每个部分的模块又有不同,因此,我们需要7个相应的状态来进行控制


*/


typedef enum
{// 矿井盘的高度,以控制矿井电机
	Reset   = 0,           // 矿井盘到最低的位置
	Height1 = 1,           // 最高(取一箱)
	Height2 = 2,           // 有一箱,准备再从小资源岛中取一箱
	Height3 = 3,           // 有两箱,准备再从小资源岛中取一箱
	Height4 = 4,           // 有三箱,此时高度应与Height3一致,或略低一些
	Initial = 5,
}Mine_Height;

typedef enum
{// 矿石旋转电机
	Stop_Rotate      = 0, // 停止
	Clockwise        = 1, // 顺时针
	CounterClockwise = 2, // 逆时针
}Rotate_Motor;

typedef enum
{// 救援卡气缸
	CARD_BACK = 0,
	CARD_OUT  = 1,
}Rescue_Card;

typedef enum
{// 救援机构电机/气缸
	CLAW_OUT  = 0,
	CLAW_BACK = 1,
}Rescue_Claw;

typedef struct
{// 底盘状态变量
	Mine_Height   MineHeight_e;         // 矿井高度
	Rotate_Motor  RotateMotor_e;        // 矿石旋转电机
	Rescue_Card   RescueCard_e;         // 救援卡气缸
	Rescue_Claw   RescueClaw_e;         // 救援机构电机/气缸
}Chassis_State;


#define Chassis_State_DEFAULT \
{\
	.MineHeight_e    = Reset,\
	.RotateMotor_e   = Stop_Rotate,\
	.RescueCard_e   = CARD_BACK,\
	.RescueClaw_e   = CLAW_BACK,\
}


void Clear_ChassisState(void);                             // 初始化底盘状态

void Change_MineHeight(Mine_Height TargetHeight);          // 改变矿井高度
void Change_RotateState(Rotate_Motor Goal);                // 矿石旋转机构(停或顺/逆时针转动)
void Change_ResCueCard_State(Rescue_Card Goal);            // 救援卡
void Change_ResCueClaw_State(Rescue_Claw On_Or_Off);       // 救援机构

void Change_LastRotateMotor_State( Rotate_Motor state );   // 改变矿石旋转电机的上一次状态

Chassis_State GetChassisState(bool now_state);             // 获得底盘当前状态
void ModeChoose(uint8_t *Info);                            // 根据云台信息,改变底盘状态

#endif

