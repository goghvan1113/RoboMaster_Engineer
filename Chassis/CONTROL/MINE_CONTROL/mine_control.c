/**
 * @file��  ���̵�����ڿ�ʯ�;�Ԯ����mine_control.c�ļ�
 * @brief��           
 * @details��
 * @author��
 * @date��  2021.10.29
 * @version��
 * @par History:
    version:
 */
#include "mine_control.h"
#include "ramp.h"
#include "pid.h"
#include "can_task.h"
#include "usart.h"
#include "delay.h"


uint16_t Num2 = 600;        // 300
uint16_t Num3 = 1200;       // 600
uint16_t AngleNum = 2000;   // 1000


//-------------------------
//���¿���̧���������������תһ�����
//-------------------------

int16_t MineMotor1_Speed = 0;     ///���ڴ��ڵ��Ե�
int16_t MineMotor2_Speed = 0;     ///���ڴ��ڵ��Ե�
int16_t RotateMotor_Speed = 0;

int16_t MineMotorSpeedChange_flag1 = 0;    //�ٶȱ仯��־λ
int16_t MineMotorSpeedChange_flag2 = 0;
int16_t RotateMotorSpeedChange_flag = 0;

float MineMotor1_Angle = 0;       ///���ڴ��ڵ���
float MineMotor2_Angle = 0;       ///���ڴ��ڵ���
float RotateMotor_Angle = 0;

int32_t MineMotorAngleChange_flag1 = 0;    //�Ƕȱ仯��־λ
int32_t MineMotorAngleChange_flag2 = 0;
int32_t RotateMotorAngleChange_flag = 0;

RampGen_t MineMotor_Ramp_1 = RAMP_GEN_DAFAULT;    //�����б�º���
RampGen_t MineMotor_Ramp_2 = RAMP_GEN_DAFAULT;
RampGen_t RotateMotor_Ramp = RAMP_GEN_DAFAULT;

PID_TypeDef MineMotorAnglePositionPID1  = PID_POSITION_DEFAULT;   // ����1�ŵ���Ƕȵ�λ�û�PID��λ��ʽ
PID_TypeDef MineMotorAngleSpeedPID1     = PID_POSITION_DEFAULT;   // ����1�ŵ���Ƕȵ��ٶȻ�PID��λ��ʽ
PID_TypeDef MineMotorSpeedPID1          = PID_POSITION_DEFAULT;   // ����1�ŵ���ٶȵ��ٶȻ�PID��λ��ʽ

PID_TypeDef MineMotorAnglePositionPID2  = PID_POSITION_DEFAULT;   // ����2�ŵ���Ƕȵ�λ�û�PID��λ��ʽ
PID_TypeDef MineMotorAngleSpeedPID2     = PID_POSITION_DEFAULT;   // ����2�ŵ���Ƕȵ��ٶȻ�PID��λ��ʽ
PID_TypeDef MineMotorSpeedPID2          = PID_POSITION_DEFAULT;   // ����2�ŵ���ٶȵ��ٶȻ�PID��λ��ʽ

PID_TypeDef RotateMotorAnglePositionPID = PID_POSITION_DEFAULT;   // ��ת����Ƕȵ�λ�û�PID��λ��ʽ
PID_TypeDef RotateMotorAngleSpeedPID    = PID_POSITION_DEFAULT;   // ��ת����Ƕȵ��ٶȻ�PID��λ��ʽ
PID_TypeDef RotateMotorSpeedPID         = PID_POSITION_DEFAULT;   // ��ת����ٶȵ��ٶȻ�PID��λ��ʽ

const float M2006_Angle_P[3] = {10,0,0};           // �Ƕȿ���λ�û�����
const float M2006_Angle_S[3] = {10,0,1};        // �Ƕȿ����ٶȻ�����

const float Mine_Speed_PID[3] = {2.4,0.0,0.0};         // �󾮵���ٶȻ�����

//��ʯ�˶����PID��ʼ��
void MinePID_Init(void)
{	//������������ֱ�Ϊ����޷��ͻ����޷�
	//�Ƕȿ���ʱ��������ʽPID���ٶȿ���ʱ��ȡλ��ʽPID
	// ����ʽPID��������޷�
	PID_Init(&MineMotorAnglePositionPID1, PID_DELTA, angle, M2006_Angle_P, 10000, 1000);
	PID_Init(&MineMotorAngleSpeedPID1, PID_DELTA, speed, M2006_Angle_S, 10000, 1000);
	PID_Init(&MineMotorSpeedPID1, PID_POSITION, speed, Mine_Speed_PID, 8000, 1000);       //
	
	PID_Init(&MineMotorAnglePositionPID2, PID_DELTA, angle, M2006_Angle_P, 10000, 1000);
	PID_Init(&MineMotorAngleSpeedPID2, PID_DELTA, speed, M2006_Angle_S, 10000, 1000);
	PID_Init(&MineMotorSpeedPID2, PID_POSITION, speed, Mine_Speed_PID, 5000, 1000);        
	
	PID_Init(&RotateMotorAnglePositionPID, PID_DELTA, angle, M2006_Angle_P, 10000, 1000);
	PID_Init(&RotateMotorAngleSpeedPID, PID_DELTA, speed, M2006_Angle_S, 10000, 1000);
	PID_Init(&RotateMotorSpeedPID, PID_POSITION, speed, Mine_Speed_PID, 5000, 1000);       	
}

//��ʯ�˶����б�³�ʼ��
void MineRAMP_Init(void)
{
	MineMotor_Ramp_1.Init(&MineMotor_Ramp_1, 100);
	MineMotor_Ramp_2.Init(&MineMotor_Ramp_2, 100);
	RotateMotor_Ramp.Init(&RotateMotor_Ramp, 100);
}

//��ʯ�˶����PID��ʼ����б�º�����ʼ��
void MineMotor_Init(void)
{
	MinePID_Init();
	MineRAMP_Init();
}


/**
 * @brief��  ���ÿ��̵����Ŀ���ٶȣ�ʹ��б�º���
 * @details��Ŀ���ٶ�Ϊrpm��תÿ��
 * @param[in]��
 * @param[out]��
 * @par �޸���־��
 *  
 */
//�ٶȿ���,ʵ�ʲ�ʹ��,����������
void SetMineMotorSpeed_WithRamp(uint8_t num, int16_t TargetSpeed)
{
	static int16_t last_target1 = 0;
	static int16_t last_target2 = 0;
	static int16_t present_target_speed1 = 0;
	static int16_t present_target_speed2 = 0;
	
	switch(num)
	{
		case 1:
		{//���ÿ��̵�1�ŵ��
			if(MineMotorSpeedChange_flag1 != TargetSpeed)
			{
				MineMotor_Ramp_1.ResetCounter(&MineMotor_Ramp_1);
				last_target1 = present_target_speed1;
				MineMotorSpeedChange_flag1 = TargetSpeed;
			}
			if(present_target_speed1 < TargetSpeed)
			{
				present_target_speed1 = last_target1 + (TargetSpeed - last_target1) *MineMotor_Ramp_1.Calc(&MineMotor_Ramp_1);
			}
			else if(present_target_speed1 > TargetSpeed)
			{
				present_target_speed1 = last_target1 - (last_target1 - TargetSpeed) *MineMotor_Ramp_1.Calc(&MineMotor_Ramp_1);
			}
	
			MineMotor1_Speed = present_target_speed1;                       //���ڴ��ڹ۲�
	
			MineMotorSpeedPID1.ref = present_target_speed1;
			MineMotorSpeedPID1.fdb = GetMotorData(MINE_MOTOR_1,false).speed;
			MineMotorSpeedPID1.Calc(&MineMotorSpeedPID1);
			
			SetMotorCurrent(MINE_MOTOR_1, (int16_t)MineMotorSpeedPID1.output);
		}break;
		
		case 2:
		{//���ÿ��̵�2�ŵ��
			if(MineMotorSpeedChange_flag2 != TargetSpeed)
			{
				MineMotor_Ramp_2.ResetCounter(&MineMotor_Ramp_2);
				last_target2 = present_target_speed2;
				MineMotorSpeedChange_flag2 = TargetSpeed;
			}
			if(present_target_speed2 < TargetSpeed)
			{
				present_target_speed2 = last_target2 + (TargetSpeed - last_target2) *MineMotor_Ramp_2.Calc(&MineMotor_Ramp_2);
			}
			else if(present_target_speed2 > TargetSpeed)
			{
				present_target_speed2 = last_target2 - (last_target2 - TargetSpeed) *MineMotor_Ramp_2.Calc(&MineMotor_Ramp_2);
			}
			
			MineMotor2_Speed = present_target_speed2;                       //���ڴ��ڹ۲�
			
			MineMotorSpeedPID2.ref = present_target_speed2;
			MineMotorSpeedPID2.fdb = GetMotorData(MINE_MOTOR_2,false).speed;
			MineMotorSpeedPID2.Calc(&MineMotorSpeedPID2);
			
			SetMotorCurrent(MINE_MOTOR_2, (int16_t)MineMotorSpeedPID2.output);	
		}break;
		
		default: break;
	}
}

void PrintSpeedPID(void)
{
	printf("V:%d,%.2f,%.2f\n",MineMotor1_Speed,MineMotorSpeedPID1.fdb,MineMotorSpeedPID1.output);

}



void MINE_MOTOR_1_ANGLE( int32_t TargetPosition )
{
	static float last_target = 0;
	static float present_target_angle = 0;
	static uint16_t i = 0;
	static float increment = 0;
	static uint16_t step = 100;
	i += 1;
	if( i >= step ){
		i = step;
	}
	if( MineMotorAngleChange_flag1 != TargetPosition ){
//		static uint8_t j = 0;
//		if( j == 0 ){
//			j = 1;
//			last_target = Initial_Angle1();       // �״ν���,��Ҫ����ǰ�Ƕȱ�Ϊ�󾮵���ĳ�ʼ�Ƕ�
//			                                             // ����,��������ǶȻ��0��ʼ�ı�,�󾮻�������б
//		}
//		else{
			last_target = present_target_angle;
//		}
		
		if( -5000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 5000 ){
			step = Num2;
		}
		else if( -15000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 15000 ){
			step = Num3;
		}
		else if( -35000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 35000 ){
			step = AngleNum;
		}
		MineMotorAngleChange_flag1 = TargetPosition;
		increment = ( TargetPosition - last_target ) / step;
		i = 0;
	}

	present_target_angle = last_target + (float) ( increment * i );

	MineMotor1_Angle = present_target_angle;
	
	MineMotorAnglePositionPID1.ref = present_target_angle; 
	MineMotorAnglePositionPID1.fdb = (GetMotorData(MINE_MOTOR_1,false).angle + GetMotorData(MINE_MOTOR_1,false).cycles * 360);
	MineMotorAnglePositionPID1.Calc(&MineMotorAnglePositionPID1);
	
	MineMotorAngleSpeedPID1.ref = MineMotorAnglePositionPID1.output;
	MineMotorAngleSpeedPID1.fdb = GetMotorData(MINE_MOTOR_1,false).speed;
	MineMotorAngleSpeedPID1.Calc(&MineMotorAngleSpeedPID1);
	
	SetMotorCurrent(MINE_MOTOR_1,(int16_t)MineMotorAngleSpeedPID1.output);
}


void PrintPositionPID(void)
{
	printf("V:%.2f,%.2f,%.2f\n",MineMotor1_Angle,MineMotorAnglePositionPID1.fdb,MineMotorAngleSpeedPID1.output);
}

//��Ԯ�������ԣ����ת�������ܿ�
void RescueTest(void)
{
//	delay_ms(1000);
//	SetMotorCurrent(5,-300);
//	SetMineMotorSpeed_WithRamp(1,3000);
	MINE_MOTOR_1_ANGLE(500);
//	PrintSpeedPID();
	PrintPositionPID();
}


//void MINE_MOTOR_2_ANGLE(int32_t TargetPosition){
//	static float last_target = 0;
//	static float present_target_angle = 0;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	static uint16_t i = 0;
//	static float increment = 0;
//	static uint16_t step = 100;
//	i += 1;
//	if( i >= step ){
//		i = step;
//	}
//	if( MineMotorAngleChange_flag2 != TargetPosition ){
//		static uint8_t j = 0;
//		if( j == 0 ){
//			j = 1;
//			last_target = Initial_Angle2();       // �״ν���,��Ҫ����ǰ�Ƕȱ�Ϊ�󾮵���ĳ�ʼ�Ƕ�
//			                                             // ����,��������ǶȻ��0��ʼ�ı�,�󾮻�������б
//		}
//		else{
//			last_target = present_target_angle;
//		}
//		if( -5000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 5000 ){
//			step = Num2;
//		}
//		else if( -15000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 15000 ){
//			step = Num3;
//		}
//		else if( -35000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 35000 ){
//			step = AngleNum;
//		}
//		MineMotorAngleChange_flag2 = TargetPosition;
//		increment = ( TargetPosition - last_target ) / step;
//		i = 0;
//	}

//	present_target_angle = last_target + (float) ( increment * i );
//	
//	MineMotor2_Angle = present_target_angle;
//	
//	MineMotorAnglePositionPID2.ref = 0.003f * present_target_angle;    // �൱��PID��������������0.003
//	MineMotorAnglePositionPID2.fdb = 0.003f * ( GetMotorData( MINE_MOTOR_2, false ).angle + GetMotorData( MINE_MOTOR_2, false ).cycles * 360);
//	MineMotorAnglePositionPID2.Calc( &MineMotorAnglePositionPID2 );
//	
//	MineMotorAngleSpeedPID2.ref = MineMotorAnglePositionPID2.output;
//	MineMotorAngleSpeedPID2.fdb = GetMotorData( MINE_MOTOR_2,false ).speed;
//	MineMotorAngleSpeedPID2.Calc( &MineMotorAngleSpeedPID2 );
//	
//	SetMotorCurrent( MINE_MOTOR_2,( int16_t )MineMotorAngleSpeedPID2.output );
//}



//void ROTATE_MOTOR_ANGLE(int16_t TargetPosition){
//	static float last_target = 0;
//	static float present_target_angle = 0;
//	static uint16_t i = 0;
//	static float increment = 0;
//	static uint16_t step = 100;
//	i += 1;
//	if( i >= step ){
//		i = step;
//	}
//	if( RotateMotorAngleChange_flag != TargetPosition ){
//		last_target = present_target_angle;
//		if( -5000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 5000 ){
//			step = Num2;
//		}
//		else if( -15000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 15000 ){
//			step = Num3;
//		}
//		else if( -35000 <= (TargetPosition - last_target) && (TargetPosition - last_target) <= 35000 ){
//			step = AngleNum;
//		}
//		RotateMotorAngleChange_flag = TargetPosition;
//		increment = ( TargetPosition - last_target ) / step;
//		i = 0;
//	}

//	present_target_angle = last_target + (float) ( increment * i );
//	
//	RotateMotor_Angle = present_target_angle;
//	
//	RotateMotorAnglePositionPID.ref = 0.003f*present_target_angle;    // �൱��PID��������������0.003
//	RotateMotorAnglePositionPID.fdb = 0.003f*(GetMotorData(Rotate_Motor,false).angle + GetMotorData(Rotate_Motor,false).cycles * 360);
//	RotateMotorAnglePositionPID.Calc(&RotateMotorAnglePositionPID);
//	
//	RotateMotorAngleSpeedPID.ref = RotateMotorAnglePositionPID.output;
//	RotateMotorAngleSpeedPID.fdb = GetMotorData(Rotate_Motor,false).speed;
//	RotateMotorAngleSpeedPID.Calc(&RotateMotorAngleSpeedPID);
//	
//	SetMotorCurrent(Rotate_Motor,(int16_t)RotateMotorAngleSpeedPID.output);
//}


void ROTATE_MOTOR_SPEED(int16_t TargetSpeed){
	static int16_t last_target = 0;
	static int16_t present_target_speed = 0;
	if(RotateMotorSpeedChange_flag != TargetSpeed){
		RotateMotor_Ramp.ResetCounter(&RotateMotor_Ramp);
		last_target = present_target_speed;
		RotateMotorSpeedChange_flag = TargetSpeed;
	}
	if(present_target_speed < TargetSpeed){
		present_target_speed = last_target + (TargetSpeed - last_target) *RotateMotor_Ramp.Calc(&RotateMotor_Ramp);
	}
	else if(present_target_speed > TargetSpeed){
		present_target_speed = last_target - (last_target - TargetSpeed) *RotateMotor_Ramp.Calc(&RotateMotor_Ramp);
	}
	
	RotateMotor_Speed = present_target_speed;                       //���ڴ��ڹ۲�
	
	RotateMotorSpeedPID.ref = present_target_speed;
	RotateMotorSpeedPID.fdb = GetMotorData(Rotate_Motor,false).speed;
	RotateMotorSpeedPID.Calc(&RotateMotorSpeedPID);
	SetMotorCurrent(Rotate_Motor, (int16_t)RotateMotorSpeedPID.output);	
}










