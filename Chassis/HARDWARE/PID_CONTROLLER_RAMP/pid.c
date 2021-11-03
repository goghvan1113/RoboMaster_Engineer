/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       pid.c/h
  * @brief      pidʵ�ֺ�����������ʼ����PID���㺯����
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. ���
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2016 DJI****************************
  */

#include "pid.h"

#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

	
/**
 * @brief��    PID��ʼ������
 * @details��
 * @param[in]��PID�ṹ��ָ�룬PID����ģʽ��λ��ʽ������ʽ�������Ƶı������Ƕȡ��ٶȡ��������Ƕȣ���PID�������飬����޷��������޷�
 * @param[out]��void
 * @par �޸���־��
 *  
 */
void PID_Init(PID_TypeDef *pid, uint8_t mode, uint8_t type, const float PID[], float max_out, float max_iout)
{
    if (pid == NULL || PID == NULL)
    {
        return;
    }
		
    pid->mode = mode;
	pid->type = type;
    pid->Kp = PID[0];
    pid->Ki = PID[1];
    pid->Kd = PID[2];
    pid->max_out = max_out;
    pid->max_iout = max_iout;
 
}


/**
 * @brief��     PID����
 * @details��
 * @param[in]�� PID�ṹ��
 * @param[out]������PID.Out
 * @par �޸���־��
 *  
 */
float PID_Calc(PID_TypeDef *pid)
{
    if (pid == NULL)
    {
        return 0.0f;
    }

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    
    pid->error[0] = pid->ref - pid->fdb;
		
    if (pid->mode == PID_POSITION)
    {
        pid->Pout = pid->Kp * pid->error[0];
        pid->Iout += pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        LimitMax(pid->Iout, pid->max_iout);
        pid->output = pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->output, pid->max_out);
    }
		
    else if (pid->mode == PID_DELTA)
    {
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
        pid->Iout = pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        pid->output += pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->output, pid->max_out);
    }
		
	else if( pid->mode == Integral_seperated )           //���ַ���PID(����ʽ)
	{
		uint16_t limit = 0;
		switch( pid->type ){                             //����PID����ѡ����ʵĻ��ַ���������
			case(angle):    limit = 30; break;
			case(speed):    limit = 500;break;
			case(ecd_angle):limit = 800;break;
		}
		if( ( pid->error[0] >= -limit ) && ( pid->error[0] <= limit ) ){    //�����������֮��,Ϊ��ͨPID������
			  pid->Iout = pid->Ki * pid->error[0];
		}
		else {pid->Iout = 0;}                                                 //����,�������Ϊ0
		pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
		pid->Dbuf[2] = pid->Dbuf[1];
		pid->Dbuf[1] = pid->Dbuf[0];
		pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
		pid->Dout = pid->Kd * pid->Dbuf[0];
		pid->output += pid->Pout + pid->Iout + pid->Dout;
		LimitMax(pid->output, pid->max_out);
	}
		
	else if( pid->mode == Anti_Integral_saturation )     //�����ֱ���PID(����ʽ)
	{
		if( pid->type == angle ) { }
		if( pid->type == speed ) { }
		if( pid->type == ecd_angle )                    //��̬�������Ӧ��Ϊ0
		{
			if( pid->output >= 500 )
			{
				if( pid->error[0] <= 0 )
				{               //�����ۻ�
					pid->Iout = pid->Ki * pid->error[0];
				}
				else
				{                                   //���ֲ��ۻ�
					pid->Iout = 0;
				}
			}
			else if( pid->output <= -500 )
			{
				if( pid->error[0] >= 0 )
				{               //�����ۻ�
					pid->Iout = pid->Ki * pid->error[0];
				}
				else
				{                                   //���ֲ��ۻ�
					pid->Iout = 0;
				}
			}
			else
			{                                       //��ͨPID����
				pid->Iout = pid->Ki * pid->error[0];
			}
			pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
			pid->Dbuf[2] = pid->Dbuf[1];
			pid->Dbuf[1] = pid->Dbuf[0];
			pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
			pid->Dout = pid->Kd * pid->Dbuf[0];
			pid->output += pid->Pout + pid->Iout + pid->Dout;
			LimitMax(pid->output, pid->max_out);
		}
	}
	//����ȫ΢��PID������ʽ������δ����
	else if( pid->mode == Incomplete_DerivativePID )     //����ȫ΢��PID(����ʽ)
	{
		if( pid->type == angle ) { }
	}
	
    return pid->output;
}


void PID_clear(PID_TypeDef *pid)
{
    if (pid == NULL)
    {
        return;
    }

    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->output = pid->Pout = pid->Iout = pid->Dout = 0.0f;
    pid->fdb = pid->ref = 0.0f;
}
