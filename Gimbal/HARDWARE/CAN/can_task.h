#ifndef _CAN_TASK_H_
#define _CAN_TASK_H_

#include "sys.h"

#define  checkok     0
#define  checkfalse  1


//底盘给云台反馈信息后，将对应变量赋值
#define  small_discup       500
#define  small_discmid      300

#define  exchange_discup    400
#define  exchange_discmid   200

#define  large_discup       300
#define  large_discmid      100

#define  setturncylinder    1
#define  resetturncylinder  0

//给底盘发信息

#define  chassis_free_normal  0x00  //底盘自由运动（普通）
#define  chassis_free_fast    0x10  //底盘自由运动（快速）
#define  chassis_free_slaw    0x20  //底盘自由运动（慢速）
#define  chassis_allstop      0x30  //底盘停止

#define  chassis_scopperil    0x07  //小陀螺

#define  chassis_small_500_right    0x11  //小资源岛，盘子上到500，同时向右
#define  chassis_small_500_stop     0x21  //小资源岛，盘子上到500，底盘停止
#define  chassis_small_300_right    0x31  //小资源岛，盘子上到300，同时向右
#define  chassis_small_300_stop     0x41  //小资源岛，盘子上到300，底盘停止
#define  chassis_small_500_free     0x51  //小资源岛，盘子上到500，自由运动
#define  chassis_small_300_free     0x61  //小资源岛，盘子上到300，自由运动

#define  chassis_large_300_right    0x12  //大资源岛，盘子上到500，同时向右
#define  chassis_large_300_stop     0x22  //大资源岛，盘子上到500，底盘停止
#define  chassis_large_100_right    0x32  //大资源岛，盘子上到300，同时向右
#define  chassis_large_100_stop     0x42  //大资源岛，盘子上到300，底盘停止
#define  chassis_large_300_free     0x52  //大资源岛，盘子上到500，自由运动
#define  chassis_large_100_free     0x62  //大资源岛，盘子上到300，自由运动

#define  chassis_exchange_200_free    0x13  //兑换点，盘子上到200，遥控器控制左右
#define  chassis_exchange_400_free    0x23  //兑换点，盘子上到400，遥控器控制左右
#define  chassis_turnstone            0x33  //兑换点，矿石旋转，然后上升到400，遥控器可用控制随意运动

#define  chassis_up_obstacle    0x14  //抓障碍块
#define  chassis_down_obstacle  0x24  //放障碍块

#define  chassis_rescue_start   0x15  //开始救援
#define  chassis_rescue_end     0x25  //结束救援



//电机相关
#define Full_Ecd_Angle (8192.00)

#define CAN_DEVICE_NUM        4      //电机总数

#define Craw_MOTOR_1		    1       //电机编号
#define	Craw_MOTOR_1_ID	  1       //电机ID
#define Craw_MOTOR_1_TYPE	C620    //电机类型
#define Craw_MOTOR_1_CH	  CAN_1   //使用的数据传输总线
#define Craw_MOTOR_1_BIAS	1900  //初始偏差

#define Craw_MOTOR_2		    2       //电机编号
#define	Craw_MOTOR_2_ID	  2       //电机ID
#define Craw_MOTOR_2_TYPE	C620    //电机类型
#define Craw_MOTOR_2_CH	  CAN_1   //使用的数据传输总线
#define Craw_MOTOR_2_BIAS	1900  //初始偏差

#define updown_MOTOR_1		    3       //电机编号
#define	updown_MOTOR_1_ID	  3       //电机ID
#define updown_MOTOR_1_TYPE	C620    //电机类型
#define updown_MOTOR_1_CH	  CAN_1   //使用的数据传输总线
#define updown_MOTOR_1_BIAS	1900  //初始偏差

#define updown_MOTOR_2		    4       //电机编号
#define	updown_MOTOR_2_ID	  4       //电机ID
#define updown_MOTOR_2_TYPE	C620    //电机类型
#define updown_MOTOR_2_CH	  CAN_1   //使用的数据传输总线
#define updown_MOTOR_2_BIAS	1900  //初始偏差


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


void setchassis_MotorSelfCheck(int8_t chassis_check);

int8_t getgimbal_MotorSelfCheck(void);
int8_t getchassis_MotorSelfCheck(void);
int16_t get_discstate(void);


void SetMotorCurrent(uint8_t device_seq, int16_t current);
void SendMotorCurrent(void);
void angle_convert(uint8_t seq);
void EcdAngle_convert( uint8_t seq );
void CAN_Data_Tx(uint32_t StdId,uint8_t Data[8],Can_Channel_e CAN_X);
void SendChassisInfo(CAN_TypeDef *CANx, uint8_t mode, int16_t Vx, int16_t Vy, int16_t W);
void SendChassisInfo_2(CAN_TypeDef *CANx, uint8_t mode1, uint8_t mode2, int16_t Vx, int16_t Vy, int16_t W);
void CAN_Device_Init(void);
void ReceiveChassisInfo( uint32_t StdId,uint8_t Data[8] );

#endif

