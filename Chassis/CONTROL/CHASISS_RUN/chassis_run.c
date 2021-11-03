/**
 * @file：   底盘电机运动控制chassis_run.c文件
 * @brief：  包含底盘四电机角度的速度、位置环；前后两组速度的速度环；底盘的速度解算
 * @details：
 * @author： 
 * @date：   2021.10.28
 * @version：
 * @par History:
    version:
 */
#include "chassis_run.h"
#include "ramp.h"
#include "pid.h"
#include "can_task.h"

int16_t ChassisMotor1_Speed  = 0;     //速度、用于串口调试
int16_t ChassisMotor2_Speed  = 0;     //用于串口调试
int16_t ChassisMotor3_Speed  = 0;     //用于串口调试
int16_t ChassisMotor4_Speed  = 0;     //用于串口调试

int16_t MotorSpeedChange_flag1 = 0;    //速度变化标志位
int16_t MotorSpeedChange_flag2 = 0;
int16_t MotorSpeedChange_flag3 = 0;
int16_t MotorSpeedChange_flag4 = 0;

float ChassisMotor1_Angle    = 0;     //角度、用于串口调试
float ChassisMotor2_Angle    = 0;     //用于串口调试
float ChassisMotor3_Angle    = 0;     //用于串口调试
float ChassisMotor4_Angle    = 0;     //用于串口调试

int16_t MotorAngleChange_flag1 = 0;    //角度变化标志位
int16_t MotorAngleChange_flag2 = 0;
int16_t MotorAngleChange_flag3 = 0;
int16_t MotorAngleChange_flag4 = 0;


RampGen_t Motor_Ramp_1 = RAMP_GEN_DAFAULT;    //电机的斜坡函数
RampGen_t Motor_Ramp_2 = RAMP_GEN_DAFAULT;
RampGen_t Motor_Ramp_3 = RAMP_GEN_DAFAULT;
RampGen_t Motor_Ramp_4 = RAMP_GEN_DAFAULT;


PID_TypeDef MotorAnglePositionPID1 = PID_POSITION_DEFAULT;     //1号轮角度的位置环PID，位置式
PID_TypeDef MotorAngleSpeedPID1    = PID_POSITION_DEFAULT;     //1号轮角度的速度环PID，位置式
PID_TypeDef MotorSpeedPID1         = PID_POSITION_DEFAULT;     //1号轮速度的速度环PID，位置式

PID_TypeDef MotorAnglePositionPID2 = PID_POSITION_DEFAULT;     //2号轮角度的位置环PID，位置式
PID_TypeDef MotorAngleSpeedPID2    = PID_POSITION_DEFAULT;     //2号轮角度的速度环PID，位置式
PID_TypeDef MotorSpeedPID2         = PID_POSITION_DEFAULT;     //2号轮速度的速度环PID，位置式

PID_TypeDef MotorAnglePositionPID3 = PID_POSITION_DEFAULT;     //3号轮角度的位置环PID，位置式
PID_TypeDef MotorAngleSpeedPID3    = PID_POSITION_DEFAULT;     //3号轮角度的速度环PID，位置式
PID_TypeDef MotorSpeedPID3         = PID_POSITION_DEFAULT;     //3号轮速度的速度环PID，位置式

PID_TypeDef MotorAnglePositionPID4 = PID_POSITION_DEFAULT;     //4号轮角度的位置环PID，位置式
PID_TypeDef MotorAngleSpeedPID4    = PID_POSITION_DEFAULT;     //4号轮角度的速度环PID，位置式
PID_TypeDef MotorSpeedPID4         = PID_POSITION_DEFAULT;     //4号轮速度的速度环PID，位置式

const float AnglePID_Position[3] = { 2000, 0, 0 };        //角度控制位置环参数
const float AnglePID_Speed[3]    = { 10, 0.02, 0};        //角度控制速度环参数

//前两个轮的速度PID
const float BackWard_PID_S[3] = { 15, 0.2, 0.8 };      // 工程车的重心距离车的几何中心有些距离,后两个轮子承受较大的压力
//后两个轮的速度PID
const float Front_PID_S[3]    = { 8, 0.05, 0.1 };



//设置底盘的速度解算
ChassisSpeed chassis = { 0, 0, 0, 0, 0, 0, 0 };       // 在主循环中接收云台数据时,便已经设置好了底盘的速度三分量


//底盘运动电机PID初始化
void ChassisMotorPID_Init(void)
{	//最后两个参数分别为输出限幅和积分限幅
	//角度控制时采用增量式PID，速度控制时采取位置式PID，前轮的启动能够更快，因此应该采取较小的节积分区间以免进入积分饱和状态
	PID_Init(&MotorAnglePositionPID1, PID_DELTA, angle, AnglePID_Position, 10000, 1000);
	PID_Init(&MotorAngleSpeedPID1, PID_DELTA, speed, AnglePID_Speed, 10000, 1000);
	PID_Init(&MotorSpeedPID1, PID_POSITION, speed, Front_PID_S, 16000, 3200);  
	                                                              	
	PID_Init(&MotorAnglePositionPID2, PID_DELTA, angle, AnglePID_Position, 10000, 1000);
	PID_Init(&MotorAngleSpeedPID2, PID_DELTA, speed, AnglePID_Speed, 10000, 1000);
	PID_Init(&MotorSpeedPID2, PID_POSITION, speed, Front_PID_S, 16000, 3200);    
	
	PID_Init(&MotorAnglePositionPID3, PID_DELTA, angle, AnglePID_Position, 10000, 1000);
	PID_Init(&MotorAngleSpeedPID3, PID_DELTA, speed, AnglePID_Speed, 10000, 1000);
	PID_Init(&MotorSpeedPID3, PID_POSITION, speed, BackWard_PID_S, 16000, 5300);     
	
	PID_Init(&MotorAnglePositionPID4, PID_DELTA, angle, AnglePID_Position, 10000, 1000);
	PID_Init(&MotorAngleSpeedPID4, PID_DELTA, speed, AnglePID_Speed, 10000, 1000);
	PID_Init(&MotorSpeedPID4, PID_POSITION, speed, BackWard_PID_S, 16000, 5300);    
}

//底盘运动电机斜坡函数初始化
void ChassisMotorRAMP_Init(void)
{
	Motor_Ramp_1.Init(&Motor_Ramp_1, 500);   // 一、二是前轮,承受重量更轻,减速更慢,应减少斜坡完成时间,让其速度更快降低为0,避免停车时漂移
	Motor_Ramp_2.Init(&Motor_Ramp_2, 500);
	Motor_Ramp_3.Init(&Motor_Ramp_3, 800);
	Motor_Ramp_4.Init(&Motor_Ramp_4, 800);
}

//底盘运动电机PID初始化和斜坡函数初始化
void ChassisMotorRun_Init(void)
{
	ChassisMotorPID_Init();
	ChassisMotorRAMP_Init();
}


/**
 * @brief：     设置底盘运动电机的目标速度，使用斜坡函数
 * @details：   直接控制电机的速度单位为rpm，在设置电机的目标速度时
 * @param[in]： num:底盘电机标号, TargetSpeed：目标速度
 * @param[out]：void
 * @par 修改日志： 2021.10.28
 *  
 */
void SetChassisMotorSpeed_WithRamp(uint8_t num, int16_t TargetSpeed)
{
	static int16_t last_target1 = 0;
	static int16_t last_target2 = 0;
	static int16_t last_target3 = 0;
	static int16_t last_target4 = 0;
	static int16_t present_target_speed1 = 0;
	static int16_t present_target_speed2 = 0;
	static int16_t present_target_speed3 = 0;
	static int16_t present_target_speed4 = 0;
	
	switch(num)
	{
		case 1:
		{//需要设置1号电机的速度
			if(MotorSpeedChange_flag1 != TargetSpeed)
			{
				Motor_Ramp_1.ResetCounter(&Motor_Ramp_1);
				last_target1 = present_target_speed1;
				MotorSpeedChange_flag1 = TargetSpeed;
			}
			if(present_target_speed1 < TargetSpeed)
			{
				present_target_speed1 = last_target1 + (TargetSpeed - last_target1) *Motor_Ramp_1.Calc(&Motor_Ramp_1);
			}
			else if(present_target_speed1 > TargetSpeed)
			{
				present_target_speed1 = last_target1 - (last_target1 - TargetSpeed) *Motor_Ramp_1.Calc(&Motor_Ramp_1);
			}
	
			ChassisMotor1_Speed = present_target_speed1;                       //用于串口观察
	
			MotorSpeedPID1.ref = present_target_speed1;
			MotorSpeedPID1.fdb = GetMotorData(CHASSIS_MOTOR_1,false).speed;    //得到这一次的电机速度
			MotorSpeedPID1.Calc(&MotorSpeedPID1);
			
			SetMotorCurrent(CHASSIS_MOTOR_1, (int16_t)MotorSpeedPID1.output);
		}break;
		
		case 2:
		{//需要设置2号电机的速度
			if(MotorSpeedChange_flag2 != TargetSpeed)
			{
				Motor_Ramp_2.ResetCounter(&Motor_Ramp_2);
				last_target2 = present_target_speed2;
				MotorSpeedChange_flag2 = TargetSpeed;
			}
			if(present_target_speed2 < TargetSpeed)
			{
				present_target_speed2 = last_target2 + (TargetSpeed - last_target2) *Motor_Ramp_2.Calc(&Motor_Ramp_2);
			}
			else if(present_target_speed2 > TargetSpeed)
			{
				present_target_speed2 = last_target2 - (last_target2 - TargetSpeed) *Motor_Ramp_2.Calc(&Motor_Ramp_2);
			}
	
			ChassisMotor2_Speed = present_target_speed2;                       //用于串口观察
	
			MotorSpeedPID2.ref = present_target_speed2;
			MotorSpeedPID2.fdb = GetMotorData(CHASSIS_MOTOR_2,false).speed;    //得到这一次的电机速度
			MotorSpeedPID2.Calc(&MotorSpeedPID2);
			
			SetMotorCurrent(CHASSIS_MOTOR_2, (int16_t)MotorSpeedPID2.output);
		}break;
		
		case 3:
		{//需要设置3号电机的速度
			if(MotorSpeedChange_flag3 != TargetSpeed)
			{
				Motor_Ramp_3.ResetCounter(&Motor_Ramp_3);
				last_target3 = present_target_speed3;
				MotorSpeedChange_flag3 = TargetSpeed;
			}
			if(present_target_speed3 < TargetSpeed)
			{
				present_target_speed3 = last_target3 + (TargetSpeed - last_target3) *Motor_Ramp_3.Calc(&Motor_Ramp_3);
			}
			else if(present_target_speed3 > TargetSpeed)
			{
				present_target_speed3 = last_target3 - (last_target3 - TargetSpeed) *Motor_Ramp_3.Calc(&Motor_Ramp_3);
			}
	
			ChassisMotor3_Speed = present_target_speed3;                       //用于串口观察
	
			MotorSpeedPID3.ref = present_target_speed3;
			MotorSpeedPID3.fdb = GetMotorData(CHASSIS_MOTOR_3,false).speed;  //得到这一次的电机速度
			MotorSpeedPID3.Calc(&MotorSpeedPID3);
			
			SetMotorCurrent(CHASSIS_MOTOR_3, (int16_t)MotorSpeedPID3.output);
		}break;
			
		case 4:
		{//需要设置4号电机的速度
			if(MotorSpeedChange_flag4 != TargetSpeed)
			{
				Motor_Ramp_4.ResetCounter(&Motor_Ramp_4);
				last_target4 = present_target_speed4;
				MotorSpeedChange_flag4 = TargetSpeed;
			}
			if(present_target_speed4 < TargetSpeed)
			{
				present_target_speed4 = last_target4 + (TargetSpeed - last_target4) *Motor_Ramp_4.Calc(&Motor_Ramp_4);
			}
			else if(present_target_speed4 > TargetSpeed)
			{
				present_target_speed4 = last_target4 - (last_target4 - TargetSpeed) *Motor_Ramp_4.Calc(&Motor_Ramp_4);
			}
	
			ChassisMotor4_Speed = present_target_speed4;                       //用于串口观察
	
			MotorSpeedPID4.ref = present_target_speed4;
			MotorSpeedPID4.fdb = GetMotorData(CHASSIS_MOTOR_4,false).speed;  //得到这一次的电机速度
			MotorSpeedPID4.Calc(&MotorSpeedPID4);
			
			SetMotorCurrent(CHASSIS_MOTOR_4, (int16_t)MotorSpeedPID4.output);
		}break;
		
		default: break;
	}
}


//--------------------------------
//以下为底盘的速度解算，并进行相应的控制函数
//--------------------------------

// 底盘运动四电机速度控制函数
void ChassisRunMotorCtrl(void)
{
	SpeedSolving();
	SetChassisMotorCurrent(1);
}

//底盘速度逆解算
void SpeedSolving(void)
{
  int16_t vx = chassis.Vx;
  int16_t vy = chassis.Vy;
  int16_t w0 = chassis.Vw;

  chassis.V1 =  ( vy + vx + w0 * ( L1 + L2 - L0 - L01 ) ) / WHEEL_DIAMETER;
  chassis.V2 = -( vy - vx - w0 * ( L1 + L2 - L0 + L01 ) ) / WHEEL_DIAMETER;
  chassis.V3 = -( vy + vx - w0 * ( L1 + L2 + L0 + L01 ) ) / WHEEL_DIAMETER;
  chassis.V4 =  ( vy - vx + w0 * ( L1 + L2 + L0 - L01 ) ) / WHEEL_DIAMETER;
}

//设置底盘四电机电流,SPEED为倍率
void SetChassisMotorCurrent(uint8_t SPEED)
{
	SetChassisMotorSpeed_WithRamp(1, SPEED * chassis.V1 );
	SetChassisMotorSpeed_WithRamp(2, SPEED * chassis.V2 );
	SetChassisMotorSpeed_WithRamp(3, SPEED * chassis.V3 );
	SetChassisMotorSpeed_WithRamp(4, SPEED * chassis.V4 );
}

//将底盘速度三分量设置并存储到表示底盘速度结构体中
void SetChassisSpeed( int16_t VX, int16_t VY, int16_t VW )
{
	chassis.Vx = VX;
	chassis.Vy = VY;
	chassis.Vw = VW;
}


//--------------------------------
//以下为电机的位置环速度环双环控制，主要用于调试时控制位置
//--------------------------------


/**
 * @brief：  设置底盘运动电机的位置环速度环双环
 * @details：
 * @param[in]： num：电机编号，TargetPosition：目标位置
 * @param[out]：void
 * @par 修改日志：2021.10.28
 *  
 */
void SetChassisMotorPosition_WithRamp(uint8_t num, int16_t TargetPosition)
{
	static int16_t last_target1 = 0;
	static int16_t last_target2 = 0;
	static int16_t last_target3 = 0;
	static int16_t last_target4 = 0;
	static int16_t present_target_angle1 = 0;
	static int16_t present_target_angle2 = 0;
	static int16_t present_target_angle3 = 0;
	static int16_t present_target_angle4 = 0;
	
	switch(num)
	{
		case 1:
		{//设置1号轮位置环速度环双环PID
			if(MotorAngleChange_flag1 != TargetPosition)
			{
				Motor_Ramp_1.ResetCounter(&Motor_Ramp_1);
				last_target1 = present_target_angle1;
				MotorAngleChange_flag1 = TargetPosition;
			}
			if(present_target_angle1 < TargetPosition)
			{
				present_target_angle1 = last_target1 + (TargetPosition - last_target1) *Motor_Ramp_1.Calc(&Motor_Ramp_1);
			}
			else if(present_target_angle1 > TargetPosition)
			{
				present_target_angle1 = last_target1 - (last_target1 - TargetPosition) *Motor_Ramp_1.Calc(&Motor_Ramp_1);
			}
	
			ChassisMotor1_Angle = present_target_angle1;
			
			MotorAnglePositionPID1.ref = 0.003f*present_target_angle1;    // 相当于PID三个参数都乘以0.003
			MotorAnglePositionPID1.fdb = 0.003f*(GetMotorData(CHASSIS_MOTOR_1,false).angle + GetMotorData(CHASSIS_MOTOR_1,false).cycles * 360);
			MotorAnglePositionPID1.Calc(&MotorAnglePositionPID1);
			
			MotorAngleSpeedPID1.ref = MotorAnglePositionPID1.output;
			MotorAngleSpeedPID1.fdb = GetMotorData(CHASSIS_MOTOR_1,false).speed;
			MotorAngleSpeedPID1.Calc(&MotorAngleSpeedPID1);
			
			SetMotorCurrent(CHASSIS_MOTOR_1,(int16_t)MotorAngleSpeedPID1.output);
		}
		
		case 2:
		{//设置2号轮位置环速度环双环PID
			if(MotorAngleChange_flag2 != TargetPosition)
			{
				Motor_Ramp_2.ResetCounter(&Motor_Ramp_2);
				last_target2 = present_target_angle2;
				MotorAngleChange_flag2 = TargetPosition;
			}
			if(present_target_angle2 < TargetPosition)
			{
				present_target_angle2 = last_target2 + (TargetPosition - last_target2) *Motor_Ramp_2.Calc(&Motor_Ramp_2);
			}
			else if(present_target_angle2 > TargetPosition)
			{
				present_target_angle2 = last_target2 - (last_target2 - TargetPosition) *Motor_Ramp_2.Calc(&Motor_Ramp_2);
			}
			
			ChassisMotor2_Angle = present_target_angle2;
			
			MotorAnglePositionPID2.ref = 0.003f*present_target_angle2;    // 相当于PID三个参数都乘以0.003
			MotorAnglePositionPID2.fdb = 0.003f*(GetMotorData(CHASSIS_MOTOR_2,false).angle + GetMotorData(CHASSIS_MOTOR_2,false).cycles * 360);
			MotorAnglePositionPID2.Calc(&MotorAnglePositionPID2);
			
			MotorAngleSpeedPID2.ref = MotorAnglePositionPID2.output;
			MotorAngleSpeedPID2.fdb = GetMotorData(CHASSIS_MOTOR_2,false).speed;
			MotorAngleSpeedPID2.Calc(&MotorAngleSpeedPID2);
			
			SetMotorCurrent(CHASSIS_MOTOR_2,(int16_t)MotorAngleSpeedPID2.output);
		}
		
		case 3:
		{//设置3号轮位置环速度环双环PID
			if(MotorAngleChange_flag3 != TargetPosition)
			{
				Motor_Ramp_3.ResetCounter(&Motor_Ramp_3);
				last_target3 = present_target_angle3;
				MotorAngleChange_flag3 = TargetPosition;
			}
			if(present_target_angle3 < TargetPosition)
			{
				present_target_angle3 = last_target3 + (TargetPosition - last_target3) *Motor_Ramp_3.Calc(&Motor_Ramp_3);
			}
			else if(present_target_angle3 > TargetPosition)
			{
				present_target_angle3 = last_target3 - (last_target3 - TargetPosition) *Motor_Ramp_3.Calc(&Motor_Ramp_3);
			}
	
			ChassisMotor3_Angle = present_target_angle3;
			
			MotorAnglePositionPID3.ref = 0.003f*present_target_angle3;    // 相当于PID三个参数都乘以0.003
			MotorAnglePositionPID3.fdb = 0.003f*(GetMotorData(CHASSIS_MOTOR_3,false).angle + GetMotorData(CHASSIS_MOTOR_3,false).cycles * 360);
			MotorAnglePositionPID3.Calc(&MotorAnglePositionPID3);
			
			MotorAngleSpeedPID3.ref = MotorAnglePositionPID3.output;
			MotorAngleSpeedPID3.fdb = GetMotorData(CHASSIS_MOTOR_3,false).speed;
			MotorAngleSpeedPID3.Calc(&MotorAngleSpeedPID3);
			
			SetMotorCurrent(CHASSIS_MOTOR_3,(int16_t)MotorAngleSpeedPID3.output);
		}
		case 4:
		{//设置4号轮位置环速度环双环PID
			if(MotorAngleChange_flag4 != TargetPosition)
			{
				Motor_Ramp_4.ResetCounter(&Motor_Ramp_4);
				last_target4 = present_target_angle4;
				MotorAngleChange_flag4 = TargetPosition;
			}
			if(present_target_angle4 < TargetPosition)
			{
				present_target_angle4 = last_target4 + (TargetPosition - last_target4) *Motor_Ramp_4.Calc(&Motor_Ramp_4);
			}
			else if(present_target_angle4 > TargetPosition)
			{
				present_target_angle4 = last_target4 - (last_target4 - TargetPosition) *Motor_Ramp_4.Calc(&Motor_Ramp_4);
			}
	
			ChassisMotor4_Angle = present_target_angle4;
			
			MotorAnglePositionPID4.ref = 0.003f*present_target_angle4;    // 相当于PID三个参数都乘以0.003
			MotorAnglePositionPID4.fdb = 0.003f*(GetMotorData(CHASSIS_MOTOR_4,false).angle + GetMotorData(CHASSIS_MOTOR_4,false).cycles * 360);
			MotorAnglePositionPID4.Calc(&MotorAnglePositionPID4);
			
			MotorAngleSpeedPID4.ref = MotorAnglePositionPID4.output;
			MotorAngleSpeedPID4.fdb = GetMotorData(CHASSIS_MOTOR_4,false).speed;
			MotorAngleSpeedPID4.Calc(&MotorAngleSpeedPID4);
			
			SetMotorCurrent(CHASSIS_MOTOR_4,(int16_t)MotorAngleSpeedPID4.output);
		}
	}
}


//返回底盘目标速度
int16_t GetChassisTargetSpeed(uint8_t i)
{
	int16_t Speed=0;
	
	switch (i)
	{
		case 1 : 
			Speed = ChassisMotor1_Speed; 
			break;
		case 2 : 
			Speed = ChassisMotor2_Speed; 
			break;
		case 3 : 
			Speed = ChassisMotor3_Speed; 
			break;
		case 4 : 
			Speed = ChassisMotor4_Speed; 
			break;
		default: break;
	}
	return Speed;
}


