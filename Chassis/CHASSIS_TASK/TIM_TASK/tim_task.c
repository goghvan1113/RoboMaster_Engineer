#include "tim_task.h"


// 定时任务每20ms执行一次。Target = 100,运行约两秒

Rescue_LinearActuator_TimSetCount RLA_Last   = RLA_Null;
Rescue_LinearActuator_TimSetCount RLA_Now    = RLA_Null;
Obstacle_LinearActuator_TimSetCount OLA_Last = OLA_Null;
Obstacle_LinearActuator_TimSetCount OLA_Now  = OLA_Null;
TimReady ReadyFlag = Not;
TimReady OLA_Ready = Not;
TimReady RLA_Ready = Not;
uint16_t count = 0;

void RLA_Time_Task(void){
	static uint16_t Target = 0;
	static uint16_t Count  = 0;
	Count++;
	
	if( RLA_Now != RLA_Last ){    //目标切换时
		RLA_Last  = RLA_Now;
		RLA_Ready = Not;
		Count = 0;
		switch( RLA_Now ){
			case( RLA_Null ):         Count  = 0;    break;
		  case( RLA_Hero ):         Target = 1400; break;
		  case( RLA_Infantry ):     Target = 1000; break;
			case( Tim_Del_Forward ):  Target = 400;  break;
			case( Tim_Del_Backward ): Target = 400;  break;
		  default:break;
	  }
	}
	
	if( Count		== Target ){
		switch( RLA_Now ){
		  case( RLA_Hero ):         RLA_Ready = RLA_InfantryReady; break;
		  case( RLA_Infantry ):     RLA_Ready = RLA_InfantryReady; break;
			case( Tim_Del_Forward ):  RLA_Ready = Res_Tim_Del_Ready; break;
			case( Tim_Del_Backward ): RLA_Ready = Res_Tim_Del_Ready; break;
		  default:break;
	  }
	}
}

void OLA_Time_Task(void){
	static uint16_t Target = 0;
	static uint16_t Count  = 0;
	Count++;
	
	if( OLA_Now != OLA_Last ){    //目标切换时
		OLA_Last  = OLA_Now;
		OLA_Ready = Not;
		Count = 0;
		switch( OLA_Now ){
			case( OLA_Null ):   Count  = 0;  break;
		  case( OLA_Out_1 ):  Target = 50; break;
		  case( OLA_Out_2 ):  Target = 50; break;
			case( OLA_Back_1 ): Target = 50; break;
		  default:break;
	  }
	}
	
	if( Count		== Target ){
		switch( OLA_Now ){
		  case( OLA_Out_1 ):  OLA_Ready = OLA_Out1Ready;  break;
		  case( OLA_Out_2 ):  OLA_Ready = OLA_Out2Ready;  break;
			case( OLA_Back_1 ): OLA_Ready = OLA_Back1Ready; break;
		  default:break;
	  }
	}
}

TimReady GetReadyFlag( void ){
	return ReadyFlag;
}

TimReady Get_RLA_ReadyFlag( void ){
	return RLA_Ready;
}

TimReady Get_OLA_ReadyFlag( void ){
	return OLA_Ready;
}

void Set_RLA_Target( Rescue_LinearActuator_TimSetCount rla_target ){
	RLA_Now = rla_target;
}

void Set_OLA_Target( Obstacle_LinearActuator_TimSetCount ola_target ){
	OLA_Now = ola_target;
}
