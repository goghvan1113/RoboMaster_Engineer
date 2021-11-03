#ifndef _CAN_TASK_H_
#define _CAN_TASK_H_

#include "sys.h"

#define  checkok     0
#define  checkfalse  1


//���̸���̨������Ϣ�󣬽���Ӧ������ֵ
#define  small_discup       500
#define  small_discmid      300

#define  exchange_discup    400
#define  exchange_discmid   200

#define  large_discup       300
#define  large_discmid      100

#define  setturncylinder    1
#define  resetturncylinder  0

//�����̷���Ϣ

#define  chassis_free_normal  0x00  //���������˶�����ͨ��
#define  chassis_free_fast    0x10  //���������˶������٣�
#define  chassis_free_slaw    0x20  //���������˶������٣�
#define  chassis_allstop      0x30  //����ֹͣ

#define  chassis_scopperil    0x07  //С����

#define  chassis_small_500_right    0x11  //С��Դ���������ϵ�500��ͬʱ����
#define  chassis_small_500_stop     0x21  //С��Դ���������ϵ�500������ֹͣ
#define  chassis_small_300_right    0x31  //С��Դ���������ϵ�300��ͬʱ����
#define  chassis_small_300_stop     0x41  //С��Դ���������ϵ�300������ֹͣ
#define  chassis_small_500_free     0x51  //С��Դ���������ϵ�500�������˶�
#define  chassis_small_300_free     0x61  //С��Դ���������ϵ�300�������˶�

#define  chassis_large_300_right    0x12  //����Դ���������ϵ�500��ͬʱ����
#define  chassis_large_300_stop     0x22  //����Դ���������ϵ�500������ֹͣ
#define  chassis_large_100_right    0x32  //����Դ���������ϵ�300��ͬʱ����
#define  chassis_large_100_stop     0x42  //����Դ���������ϵ�300������ֹͣ
#define  chassis_large_300_free     0x52  //����Դ���������ϵ�500�������˶�
#define  chassis_large_100_free     0x62  //����Դ���������ϵ�300�������˶�

#define  chassis_exchange_200_free    0x13  //�һ��㣬�����ϵ�200��ң������������
#define  chassis_exchange_400_free    0x23  //�һ��㣬�����ϵ�400��ң������������
#define  chassis_turnstone            0x33  //�һ��㣬��ʯ��ת��Ȼ��������400��ң�������ÿ��������˶�

#define  chassis_up_obstacle    0x14  //ץ�ϰ���
#define  chassis_down_obstacle  0x24  //���ϰ���

#define  chassis_rescue_start   0x15  //��ʼ��Ԯ
#define  chassis_rescue_end     0x25  //������Ԯ



//������
#define Full_Ecd_Angle (8192.00)

#define CAN_DEVICE_NUM        4      //�������

#define Craw_MOTOR_1		    1       //������
#define	Craw_MOTOR_1_ID	  1       //���ID
#define Craw_MOTOR_1_TYPE	C620    //�������
#define Craw_MOTOR_1_CH	  CAN_1   //ʹ�õ����ݴ�������
#define Craw_MOTOR_1_BIAS	1900  //��ʼƫ��

#define Craw_MOTOR_2		    2       //������
#define	Craw_MOTOR_2_ID	  2       //���ID
#define Craw_MOTOR_2_TYPE	C620    //�������
#define Craw_MOTOR_2_CH	  CAN_1   //ʹ�õ����ݴ�������
#define Craw_MOTOR_2_BIAS	1900  //��ʼƫ��

#define updown_MOTOR_1		    3       //������
#define	updown_MOTOR_1_ID	  3       //���ID
#define updown_MOTOR_1_TYPE	C620    //�������
#define updown_MOTOR_1_CH	  CAN_1   //ʹ�õ����ݴ�������
#define updown_MOTOR_1_BIAS	1900  //��ʼƫ��

#define updown_MOTOR_2		    4       //������
#define	updown_MOTOR_2_ID	  4       //���ID
#define updown_MOTOR_2_TYPE	C620    //�������
#define updown_MOTOR_2_CH	  CAN_1   //ʹ�õ����ݴ�������
#define updown_MOTOR_2_BIAS	1900  //��ʼƫ��


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

