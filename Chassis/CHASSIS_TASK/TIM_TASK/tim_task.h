#ifndef _TIM_TASK_H_
#define _TIM_TASK_H_

#include "sys.h"

// 控制底盘障碍块抓取电推杆与救援机构电推杆两部分的运动时间

typedef enum                   // 救援电推杆的控时任务
{
	RLA_Null         = 0,        // 无(初始态),注意:在控制收回此电推杆后,重置为RLA_Null
	RLA_Hero         = 1,        // 救援英雄
	RLA_Infantry     = 2,        // 救援步兵
	Tim_Del_Forward  = 3,        // 由救援英雄长度,伸至救援步兵长度
	Tim_Del_Backward = 4,        // 由救援步兵长度,伸至救援英雄长度
}Rescue_LinearActuator_TimSetCount;

typedef enum
{
	OLA_Null   = 0,                // 无(初始态),注意:在控制收回此电推杆后,重置为OLA_Null
	OLA_Out_1  = 1,                // 伸到与障碍块上的孔平齐
	OLA_Out_2  = 2,                // 在执行OLA_Out_1后,再执行此,可使电推杆降低至能丢下障碍块的高度
	OLA_Back_1 = 3,                // 在执行OLA_Out_1后,再执行此,可使电推杆提高至能搬运障碍块的高度
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

