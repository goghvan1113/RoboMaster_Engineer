/**
 * @file：  根据云台传递的信息改变底盘状态的mode_choose.c文件
 * @brief： 目前包括矿井高度、矿石旋转机构、救援卡、救援爪四个状态         
 * @details：
 * @author：
 * @date：  2021.10.29
 * @version：
 * @par History:
    version:
 */
#include "mode_choose.h"

//底盘上次的状态
Chassis_State Last_Chassis_State = Chassis_State_DEFAULT;
//底盘这次的状态
Chassis_State Now_Chassis_State  = Chassis_State_DEFAULT;


// 根据云台信息,改变底盘状态
void ModeChoose(uint8_t *Info)            
{
	uint8_t ModeInfo = Info[0];
	uint8_t Small_Mode = ModeInfo & 0x0f;               // 0～3位为小模式
	uint8_t Big_Mode = ( ModeInfo & 0xf0 ) >> 4;        // 4～7位为大模式
	switch( Big_Mode ){
		case(3):{                                              
			switch( Small_Mode ){// 矿井高度
				case(1):Change_MineHeight(Reset);  break;
				case(2):Change_MineHeight(Height1);break;
				case(3):Change_MineHeight(Height2);break;
				case(4):Change_MineHeight(Height3);break;
				default:break;
			}
		}break;
		case(7):{                                              
			switch(Small_Mode){// 矿石旋转电机
				case(1):Change_RotateState(Clockwise);       break;      //顺时针旋转
				case(2):Change_RotateState(CounterClockwise);break;      //逆时针旋转
				default:break;
			}
		}break;
		case(11):{
			switch(Small_Mode){ // 救援卡
				case(1):Change_ResCueCard_State(CARD_BACK);   break;     // 收回救援卡
				case(2):Change_ResCueCard_State(CARD_OUT);    break;     // 伸出救援卡
				default:break;
			}
		}break;
		case(13):{
			switch(Small_Mode){ // 救援爪
				case(1):Change_ResCueClaw_State(CLAW_BACK);break;        //收回救援爪
				case(2):Change_ResCueClaw_State(CLAW_OUT); break;        //伸出救援爪
				default:break;
			}
		}break;
		default: break;
	}
}



// 初始化底盘状态
void Clear_ChassisState(void)                            
{
	Now_Chassis_State.MineHeight_e   = Reset;
	Now_Chassis_State.RotateMotor_e  = Stop_Rotate;
	Now_Chassis_State.RescueCard_e   = CARD_BACK;
	Now_Chassis_State.RescueClaw_e   = CLAW_OUT;
}

// 改变矿井高度
void Change_MineHeight(Mine_Height TargetHeight)            
{
	Now_Chassis_State.MineHeight_e = TargetHeight;
}

// 矿石旋转机构(停或顺/逆时针转动)
void Change_RotateState(Rotate_Motor Goal)               
{
	Now_Chassis_State.RotateMotor_e = Goal;
}

// 救援卡
void Change_ResCueCard_State(Rescue_Card Goal)              
{
	Now_Chassis_State.RescueCard_e = Goal;
}

// 救援爪
void Change_ResCueClaw_State( Rescue_Claw On_Or_Off ) 
{
	Now_Chassis_State.RescueClaw_e = On_Or_Off;
}

// 改变矿石旋转电机的上一次状态
void Change_LastRotateMotor_State( Rotate_Motor state )     
{
	Last_Chassis_State.RotateMotor_e = state;
}

// 获得底盘当前状态,true为当前状态，false为下次的状态
Chassis_State GetChassisState(bool now_state)            
{
	if( now_state ) 
		return Now_Chassis_State;
	else 
		return Last_Chassis_State;
}
