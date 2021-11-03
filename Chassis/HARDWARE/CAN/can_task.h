#ifndef _CAN_TASK_H_
#define _CAN_TASK_H_

#include "sys.h"

#define Full_Ecd_Angle (8192.00)     //���תһȦΪ8192������

#define CAN_DEVICE_NUM        7       //�������

#define CHASSIS_MOTOR_1		    1       //������
#define	CHASSIS_MOTOR_1_ID	  1       //���ID
#define CHASSIS_MOTOR_1_TYPE	C620    //�������
#define CHASSIS_MOTOR_1_CH	  CAN_1   //ʹ�õ����ݴ�������
#define CHASSIS_MOTOR_1_BIAS	1900    //��ʼƫ��

#define CHASSIS_MOTOR_2		    2       //������
#define	CHASSIS_MOTOR_2_ID	  2       //���ID
#define CHASSIS_MOTOR_2_TYPE	C620    //�������
#define CHASSIS_MOTOR_2_CH	  CAN_1   //ʹ�õ����ݴ�������
#define CHASSIS_MOTOR_2_BIAS	1900    //��ʼƫ��

#define CHASSIS_MOTOR_3		    3       //������
#define	CHASSIS_MOTOR_3_ID	  3       //���ID
#define CHASSIS_MOTOR_3_TYPE	C620    //�������
#define CHASSIS_MOTOR_3_CH	  CAN_1   //ʹ�õ����ݴ�������
#define CHASSIS_MOTOR_3_BIAS	1900    //��ʼƫ��

#define CHASSIS_MOTOR_4		    4       //������
#define	CHASSIS_MOTOR_4_ID	  4       //���ID
#define CHASSIS_MOTOR_4_TYPE	C620    //�������
#define CHASSIS_MOTOR_4_CH	  CAN_1   //ʹ�õ����ݴ�������
#define CHASSIS_MOTOR_4_BIAS	1900    //��ʼƫ��

#define MINE_MOTOR_1		      5       //������
#define	MINE_MOTOR_1_ID	      5       //���ID
#define MINE_MOTOR_1_TYPE	    C610    //�������
#define MINE_MOTOR_1_CH	      CAN_1   //ʹ�õ����ݴ�������
#define MINE_MOTOR_1_BIAS	    1900    //��ʼƫ��

#define MINE_MOTOR_2		      6       //������
#define	MINE_MOTOR_2_ID	      6       //���ID
#define MINE_MOTOR_2_TYPE	    C610    //�������
#define MINE_MOTOR_2_CH	      CAN_1   //ʹ�õ����ݴ�������
#define MINE_MOTOR_2_BIAS	    1900    //��ʼƫ��

#define Rotate_Motor		      7       //������
#define	Rotate_Motor_ID	      1       //���ID
#define Rotate_Motor_TYPE	    C610    //�������
#define Rotate_Motor_CH	      CAN_2   //ʹ�õ����ݴ�������
#define Rotate_Motor_BIAS	    1900    //��ʼƫ��

//����̨������Ϣ�ĺ궨��
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
//ö�����������ݽṹ�嶨��
//------------------------------------------------------------
/**
@brief CANͨ��ö��
*/
typedef enum
{
	CAN_1	= 1,
	CAN_2	= 2,
}Can_Channel_e;

/**
@brief CAN�豸ö��
*/
typedef enum
{
	Chassis	= 0,   //����̷�����Ϣ
	C610    = 1,   ///<C610���,��Ҫ����M2006
	C620	  = 2,   ///<C620�������Ҫ����M3508
	GM6020	= 3,
	GM3510  = 4
}Device_Type_e;
/**
@brief CAN�豸������Ϣ
*/
typedef struct
{
	Can_Channel_e	ch;			  	///<CAN�豸ͨ��
	uint8_t			id;				    ///<CAN������뿪��ID
	uint32_t		id_send;		  ///<CAN����ID
	uint32_t 		id_recieve;		///<CAN����ID
	Device_Type_e	type;			  ///<CAN�豸����
	int16_t 		ecd_bias;	  	///<���̽Ƕȼ���Ĳο�ƫ����
}Can_Cfg_Info_t;
/**
@brief ������ݽṹ��(*Ϊ���������)
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
	int16_t  ecd_angle;  //�������Ƕ�
	int16_t  cycles;
	int16_t  ecd_cycles;
	float    angle;
	int16_t  speed;
	int16_t  torque;    //ת��
	int8_t  temperature;
	int16_t selfcheck;
}Motor_Data_t;


Motor_Data_t GetMotorData(uint8_t device_seq,bool last_data);
void CAN_Motor_Send_ID_Print(void);
bool CAN_Motor_ID_CHECK(void);
void CAN_Motor_Config(uint8_t device_seq,uint32_t ID,Device_Type_e device,Can_Channel_e CAN_x,int16_t bias);
void CAN_Message_Encode( uint32_t StdId,uint8_t Data[8], Can_Channel_e CAN_x);

int8_t ChassisSelfCheck(void);

//CANͨ�ŷ���
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

