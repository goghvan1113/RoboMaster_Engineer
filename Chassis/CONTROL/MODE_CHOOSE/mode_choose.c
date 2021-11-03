/**
 * @file��  ������̨���ݵ���Ϣ�ı����״̬��mode_choose.c�ļ�
 * @brief�� Ŀǰ�����󾮸߶ȡ���ʯ��ת��������Ԯ������Ԯצ�ĸ�״̬         
 * @details��
 * @author��
 * @date��  2021.10.29
 * @version��
 * @par History:
    version:
 */
#include "mode_choose.h"

//�����ϴε�״̬
Chassis_State Last_Chassis_State = Chassis_State_DEFAULT;
//������ε�״̬
Chassis_State Now_Chassis_State  = Chassis_State_DEFAULT;


// ������̨��Ϣ,�ı����״̬
void ModeChoose(uint8_t *Info)            
{
	uint8_t ModeInfo = Info[0];
	uint8_t Small_Mode = ModeInfo & 0x0f;               // 0��3λΪСģʽ
	uint8_t Big_Mode = ( ModeInfo & 0xf0 ) >> 4;        // 4��7λΪ��ģʽ
	switch( Big_Mode ){
		case(3):{                                              
			switch( Small_Mode ){// �󾮸߶�
				case(1):Change_MineHeight(Reset);  break;
				case(2):Change_MineHeight(Height1);break;
				case(3):Change_MineHeight(Height2);break;
				case(4):Change_MineHeight(Height3);break;
				default:break;
			}
		}break;
		case(7):{                                              
			switch(Small_Mode){// ��ʯ��ת���
				case(1):Change_RotateState(Clockwise);       break;      //˳ʱ����ת
				case(2):Change_RotateState(CounterClockwise);break;      //��ʱ����ת
				default:break;
			}
		}break;
		case(11):{
			switch(Small_Mode){ // ��Ԯ��
				case(1):Change_ResCueCard_State(CARD_BACK);   break;     // �ջؾ�Ԯ��
				case(2):Change_ResCueCard_State(CARD_OUT);    break;     // �����Ԯ��
				default:break;
			}
		}break;
		case(13):{
			switch(Small_Mode){ // ��Ԯצ
				case(1):Change_ResCueClaw_State(CLAW_BACK);break;        //�ջؾ�Ԯצ
				case(2):Change_ResCueClaw_State(CLAW_OUT); break;        //�����Ԯצ
				default:break;
			}
		}break;
		default: break;
	}
}



// ��ʼ������״̬
void Clear_ChassisState(void)                            
{
	Now_Chassis_State.MineHeight_e   = Reset;
	Now_Chassis_State.RotateMotor_e  = Stop_Rotate;
	Now_Chassis_State.RescueCard_e   = CARD_BACK;
	Now_Chassis_State.RescueClaw_e   = CLAW_OUT;
}

// �ı�󾮸߶�
void Change_MineHeight(Mine_Height TargetHeight)            
{
	Now_Chassis_State.MineHeight_e = TargetHeight;
}

// ��ʯ��ת����(ͣ��˳/��ʱ��ת��)
void Change_RotateState(Rotate_Motor Goal)               
{
	Now_Chassis_State.RotateMotor_e = Goal;
}

// ��Ԯ��
void Change_ResCueCard_State(Rescue_Card Goal)              
{
	Now_Chassis_State.RescueCard_e = Goal;
}

// ��Ԯצ
void Change_ResCueClaw_State( Rescue_Claw On_Or_Off ) 
{
	Now_Chassis_State.RescueClaw_e = On_Or_Off;
}

// �ı��ʯ��ת�������һ��״̬
void Change_LastRotateMotor_State( Rotate_Motor state )     
{
	Last_Chassis_State.RotateMotor_e = state;
}

// ��õ��̵�ǰ״̬,trueΪ��ǰ״̬��falseΪ�´ε�״̬
Chassis_State GetChassisState(bool now_state)            
{
	if( now_state ) 
		return Now_Chassis_State;
	else 
		return Last_Chassis_State;
}
