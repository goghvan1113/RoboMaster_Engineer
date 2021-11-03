#include "pid_controller.h"

//PID������


void PID_Update(PID_t* WhichPID, float NowInput)
{//����PID�����ݣ�������PID������ֵ
	WhichPID->PID_Input = NowInput;
	if(WhichPID->State_RampOrNormal == Ramp_e)
	{
		if(WhichPID->RampCountTime < WhichPID->RampTartgetTime)
		{
			++ WhichPID ->RampCountTime;
		}
		else
		{
			WhichPID->RampCountTime = 0;
			if(WhichPID->PID_Target <  WhichPID->RampTarget )
			{//б�º�����û�����꣬
				WhichPID->PID_Target += WhichPID->RampTartgetStep;
				if(WhichPID->PID_Target >= WhichPID->RampTarget)
				{
					WhichPID->PID_Target = WhichPID->RampTarget;
					WhichPID->State_RampOrNormal = Normal_e;
				}
			}
			else if(WhichPID->PID_Target >  WhichPID->RampTarget)
			{
				WhichPID->PID_Target -= WhichPID->RampTartgetStep;
				if(WhichPID->PID_Target <= WhichPID->RampTarget)
				{
					WhichPID->PID_Target = WhichPID->RampTarget;
					WhichPID->State_RampOrNormal = Normal_e;
				}
			}
			else
			{//б�º��������Ѿ���ɣ�Ҫ�˳�б�º���ģʽ
				WhichPID->State_RampOrNormal = Normal_e;
			}
		}
	}	
	WhichPID->PID_Err_lastlast = WhichPID->PID_Err_last;
	WhichPID->PID_Err_last = WhichPID->PID_Err_now;
	WhichPID->PID_Err_now = WhichPID->PID_Target - NowInput;
	
	if( WhichPID->PID_Err_now < WhichPID->PID_Precision && WhichPID->PID_Err_now > -WhichPID->PID_Precision )
		WhichPID->PID_Err_now = 0;  //�ж�Ӧ��Ϊ���жϰ�
	
	WhichPID->PID_Err_all += WhichPID->PID_Err_now;
	
	if( WhichPID->PID_Err_all > WhichPID->PID_ErrAllMax)
	{
		WhichPID->PID_Err_all = WhichPID->PID_ErrAllMax;
	}
	else if( WhichPID->PID_Err_all < -WhichPID->PID_ErrAllMax)
	{
		WhichPID->PID_Err_all = -WhichPID->PID_ErrAllMax;
	}//�����޷�
}


float PID_GetPositionPID(PID_t* WhichPID)
{
	WhichPID->PID_Out = WhichPID->Kp1 * WhichPID->PID_Err_now + WhichPID->Kd1 * (WhichPID->PID_Err_now - WhichPID->PID_Err_last);
	WhichPID->PID_Out += ( WhichPID->PID_Err_all * WhichPID->Ki1 );
	
	if(WhichPID->PID_Out >= WhichPID->PID_OutMax)
		WhichPID->PID_Out = WhichPID->PID_OutMax;
	if(WhichPID->PID_Out <= -WhichPID->PID_OutMax)
		WhichPID->PID_Out = -WhichPID->PID_OutMax;
	//����޷�
	
	if(WhichPID->PID_Out - WhichPID->PID_lastout > WhichPID->PID_OutStep)
	{
		WhichPID->PID_Out = WhichPID->PID_lastout + WhichPID->PID_OutStep;
	}
	if(WhichPID->PID_Out - WhichPID->PID_lastout < -WhichPID->PID_OutStep)
	{
		WhichPID->PID_Out = WhichPID->PID_lastout + -WhichPID->PID_OutStep;
	}
	
	WhichPID->PID_lastout = WhichPID->PID_Out;

	return WhichPID->PID_Out;
}

//
float PID_GetIncrementalPID(PID_t* WhichPID)
{
	WhichPID->PID_Out += WhichPID->Ki1 * WhichPID->PID_Err_now + WhichPID->Kp1 * (WhichPID->PID_Err_now - WhichPID->PID_Err_last);
	WhichPID->PID_Out += WhichPID->Kd1 * (WhichPID->PID_Err_now - 2 * WhichPID->PID_Err_last + WhichPID->PID_Err_lastlast);

	if(WhichPID->PID_Out >= WhichPID->PID_OutMax)
		WhichPID->PID_Out = WhichPID->PID_OutMax;
	if(WhichPID->PID_Out <= -WhichPID->PID_OutMax)
		WhichPID->PID_Out = -WhichPID->PID_OutMax;

	if(WhichPID->PID_Out - WhichPID->PID_lastout > WhichPID->PID_OutStep)
	{
		WhichPID->PID_Out = WhichPID->PID_lastout + WhichPID->PID_OutStep;
	}
	if(WhichPID->PID_Out - WhichPID->PID_lastout < -WhichPID->PID_OutStep)
	{
		WhichPID->PID_Out = WhichPID->PID_lastout + -WhichPID->PID_OutStep;
	}
	
	WhichPID->PID_lastout = WhichPID->PID_Out;	
	return WhichPID->PID_Out;
}

//
void PID_DefaultInit(PID_t* WhichPID)
{//��ʼ��PID��Ĭ�ϲ���
	WhichPID->Kp1 = 0.0;
	WhichPID->Ki1 = 0.0;
	WhichPID->Kd1 = 0.0;
	WhichPID->PID_Err_now = 0.0;
	WhichPID->PID_Err_last = 0.0;
	WhichPID->PID_Err_lastlast = 0.0;
	WhichPID->PID_Err_all = 0.0;
	WhichPID->PID_Out = 0.0;
	WhichPID->PID_lastout = 0.0;
	WhichPID->PID_Target = 0.0;
	WhichPID->PID_Input = 0.0;
	WhichPID->State_RampOrNormal = Normal_e;
	WhichPID->RampTarget = 0.0;
	WhichPID->RampCountTime = 0.0;
	WhichPID->RampTartgetTime = RampDefault_Time;
	WhichPID->RampTartgetStep = RampDefault_Step;
	WhichPID->PID_WorkType = PositionPID_e;
	WhichPID->PID_Precision = PID_DEFAULT_PRECISION;
	WhichPID->PID_ErrAllMax = PID_DEFAULT_ERRALL_MAX;
	WhichPID->PID_OutMax = PID_DEFAULT_OUTPUT_MAX;
	WhichPID->PID_OutStep = PID_DEFAULT_OUTPUT_STEP_MAX;
}

void PID_SetTargetWithRamp(PID_t* WhichPID,float Target)
{//����PID��Ŀ��ֵ��ʹ��б�º���
	if(WhichPID->RampTarget != Target)
	{
		WhichPID->RampTarget = Target;
		WhichPID->State_RampOrNormal = Ramp_e;
	}
}


void PID_Clear(PID_t* WhichPID)
{
	WhichPID->PID_Err_now = 0.0;
	WhichPID->PID_Err_last = 0.0;
	WhichPID->PID_Err_lastlast = 0.0;
	WhichPID->PID_Err_all = 0.0;
	WhichPID->PID_Out = 0.0;
	WhichPID->PID_lastout = 0.0;
	WhichPID->PID_Target = 0.0;
	WhichPID->PID_Input = 0.0;
	WhichPID->State_RampOrNormal = Normal_e;
	WhichPID->RampTarget = 0.0;
	WhichPID->RampCountTime = 0.0;
}






