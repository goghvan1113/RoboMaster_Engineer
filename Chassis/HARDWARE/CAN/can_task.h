#ifndef _CAN_TASK_H_
#define _CAN_TASK_H_

#include "sys.h"

#define Full_Ecd_Angle (8192.00)     //电机转一圈为8192个脉冲

#define CAN_DEVICE_NUM        7       //电机总数

#define CHASSIS_MOTOR_1		    1       //电机编号
#define	CHASSIS_MOTOR_1_ID	  1       //电机ID
#define CHASSIS_MOTOR_1_TYPE	C620    //电机类型
#define CHASSIS_MOTOR_1_CH	  CAN_1   //使用的数据传输总线
#define CHASSIS_MOTOR_1_BIAS	1900    //初始偏差

#define CHASSIS_MOTOR_2		    2       //电机编号
#define	CHASSIS_MOTOR_2_ID	  2       //电机ID
#define CHASSIS_MOTOR_2_TYPE	C620    //电机类型
#define CHASSIS_MOTOR_2_CH	  CAN_1   //使用的数据传输总线
#define CHASSIS_MOTOR_2_BIAS	1900    //初始偏差

#define CHASSIS_MOTOR_3		    3       //电机编号
#define	CHASSIS_MOTOR_3_ID	  3       //电机ID
#define CHASSIS_MOTOR_3_TYPE	C620    //电机类型
#define CHASSIS_MOTOR_3_CH	  CAN_1   //使用的数据传输总线
#define CHASSIS_MOTOR_3_BIAS	1900    //初始偏差

#define CHASSIS_MOTOR_4		    4       //电机编号
#define	CHASSIS_MOTOR_4_ID	  4       //电机ID
#define CHASSIS_MOTOR_4_TYPE	C620    //电机类型
#define CHASSIS_MOTOR_4_CH	  CAN_1   //使用的数据传输总线
#define CHASSIS_MOTOR_4_BIAS	1900    //初始偏差

#define MINE_MOTOR_1		      5       //电机编号
#define	MINE_MOTOR_1_ID	      5       //电机ID
#define MINE_MOTOR_1_TYPE	    C610    //电机类型
#define MINE_MOTOR_1_CH	      CAN_1   //使用的数据传输总线
#define MINE_MOTOR_1_BIAS	    1900    //初始偏差

#define MINE_MOTOR_2		      6       //电机编号
#define	MINE_MOTOR_2_ID	      6       //电机ID
#define MINE_MOTOR_2_TYPE	    C610    //电机类型
#define MINE_MOTOR_2_CH	      CAN_1   //使用的数据传输总线
#define MINE_MOTOR_2_BIAS	    1900    //初始偏差

#define Rotate_Motor		      7       //电机编号
#define	Rotate_Motor_ID	      1       //电机ID
#define Rotate_Motor_TYPE	    C610    //电机类型
#define Rotate_Motor_CH	      CAN_2   //使用的数据传输总线
#define Rotate_Motor_BIAS	    1900    //初始偏差

//向云台发送信息的宏定义
#define MINE2HEIGHT1 ((uint8_t)0x13)
#define MINE2HEIGHT2 ((uint8_t)0x33)
#define MINE2HEIGHT3 ((uint8_t)0x15)
#define MINE2HEIGHT4 ((uint8_t)0x35)


#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\
else {val = val;}\

//------------------------------------------------------------
//枚举类型与数据结构体定义
//------------------------------------------------------------
/**
@brief CAN通道枚举
*/
typedef enum
{
	CAN_1	= 1,
	CAN_2	= 2,
}Can_Channel_e;

/**
@brief CAN设备枚举
*/
typedef enum
{
	Chassis	= 0,   //向底盘发送信息
	C610    = 1,   ///<C610电调,主要驱动M2006
	C620	  = 2,   ///<C620电调，主要驱动M3508
	GM6020	= 3,
	GM3510  = 4
}Device_Type_e;
/**
@brief CAN设备配置信息
*/
typedef struct
{
	Can_Channel_e	ch;			  	///<CAN设备通道
	uint8_t			id;				    ///<CAN电调拨码开关ID
	uint32_t		id_send;		  ///<CAN控制ID
	uint32_t 		id_recieve;		///<CAN反馈ID
	Device_Type_e	type;			  ///<CAN设备类型
	int16_t 		ecd_bias;	  	///<码盘角度计算的参考偏移量
}Can_Cfg_Info_t;
/**
@brief 电机数据结构体(*为有这个数据)
type	angle	speed	torque	temperature
C610		*		*		*
C620		*		*		*		*
GM6020	*		*		*		*
RM6623	*				*		
GM3510	*				*
RM820R	*		*
Chassis	(Not a motor)
*/
typedef struct
{
	int16_t  ecd_angle;  //编码器角度
	int16_t  cycles;
	int16_t  ecd_cycles;
	float    angle;
	int16_t  speed;
	int16_t  torque;    //转矩
	int8_t  temperature;
	int16_t selfcheck;
}Motor_Data_t;


Motor_Data_t GetMotorData(uint8_t device_seq,bool last_data);
void CAN_Motor_Send_ID_Print(void);
bool CAN_Motor_ID_CHECK(void);
void CAN_Motor_Config(uint8_t device_seq,uint32_t ID,Device_Type_e device,Can_Channel_e CAN_x,int16_t bias);
void CAN_Message_Encode( uint32_t StdId,uint8_t Data[8], Can_Channel_e CAN_x);

int8_t ChassisSelfCheck(void);

//CAN通信发送
void SetMotorCurrent(uint8_t device_seq, int16_t current);
void SendMotorCurrent(void);
void CAN_Data_Tx(uint32_t StdId,uint8_t Data[8],Can_Channel_e CAN_X);
uint8_t SendGimbalInfo( uint8_t* msg, uint8_t len );

//
void ReceiveGimbalData( uint32_t StdId, uint8_t Data[8] );
void GetGimbalData( uint8_t *Data );

void CAN_Device_Init(void);
void Get_Judge_Info( uint8_t *Data );

#endif

