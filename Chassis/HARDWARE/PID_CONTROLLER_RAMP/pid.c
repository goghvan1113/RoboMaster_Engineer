/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       pid.c/h
  * @brief      pid实现函数，包括初始化，PID计算函数，
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. 完成
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
 * @brief：    PID初始化函数
 * @details：
 * @param[in]：PID结构体指针，PID更新模式（位置式、增量式），控制的变量（角度、速度、编码器角度），PID参数数组，输出限幅，积分限幅
 * @param[out]：void
 * @par 修改日志：
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
 * @brief：     PID计算
 * @details：
 * @param[in]： PID结构体
 * @param[out]：返回PID.Out
 * @par 修改日志：
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
		
	else if( pid->mode == Integral_seperated )           //积分分离PID(增量式)
	{
		uint16_t limit = 0;
		switch( pid->type ){                             //根据PID类型选择合适的积分分离上下限
			case(angle):    limit = 30; break;
			case(speed):    limit = 500;break;
			case(ecd_angle):limit = 800;break;
		}
		if( ( pid->error[0] >= -limit ) && ( pid->error[0] <= limit ) ){    //误差在上下限之内,为普通PID控制器
			  pid->Iout = pid->Ki * pid->error[0];
		}
		else {pid->Iout = 0;}                                                 //否则,积分输出为0
		pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
		pid->Dbuf[2] = pid->Dbuf[1];
		pid->Dbuf[1] = pid->Dbuf[0];
		pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
		pid->Dout = pid->Kd * pid->Dbuf[0];
		pid->output += pid->Pout + pid->Iout + pid->Dout;
		LimitMax(pid->output, pid->max_out);
	}
		
	else if( pid->mode == Anti_Integral_saturation )     //抗积分饱和PID(增量式)
	{
		if( pid->type == angle ) { }
		if( pid->type == speed ) { }
		if( pid->type == ecd_angle )                    //稳态输出电流应该为0
		{
			if( pid->output >= 500 )
			{
				if( pid->error[0] <= 0 )
				{               //积分累积
					pid->Iout = pid->Ki * pid->error[0];
				}
				else
				{                                   //积分不累积
					pid->Iout = 0;
				}
			}
			else if( pid->output <= -500 )
			{
				if( pid->error[0] >= 0 )
				{               //积分累积
					pid->Iout = pid->Ki * pid->error[0];
				}
				else
				{                                   //积分不累积
					pid->Iout = 0;
				}
			}
			else
			{                                       //普通PID控制
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
	//不完全微分PID（增量式）代码未给出
	else if( pid->mode == Incomplete_DerivativePID )     //不完全微分PID(增量式)
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
