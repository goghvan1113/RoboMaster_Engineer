#ifndef __DBUS_REMOTE__H__
#define __DBUS_REMOTE__H__

#include "sys.h"


//------------------------------------------------------------
//��������
//------------------------------------------------------------
///	@brief����ԭʼ���ݣ�Ϊ18���ֽڣ�����36���ֽڳ��ȣ���ֹDMA����Խ��
#define DBUS_RX_BUF_NUM 36u
#define RC_FRAME_LENGTH 18u
///	@brief ң����ͨ���м�ƫ��ֵ
#define REMOTE_CONTROLLER_OFFSET      (1024u) 


//------------------------------------------------------------
//���ݽṹ�嶨��
//------------------------------------------------------------

/**
@brief	ң����switch����ͨ��
	��ĳλ����Ϊ1�����ڸ�λ����Ϊ0
*/
typedef __packed struct
{
	uint8_t up:1;
	uint8_t mid:1;
	uint8_t down:1;
}Sw_Data_t;


/**
@brief	ң����ͨ��
	ch[0]~ch[3]ң����ң��(�Ѿ���ȥ�м�ƫ����)��
		���ֵ 660 ��/��
		�м�ֵ 0
		��Сֵ -660  ��/��
	ch[0]��ҡ������Ϊ��
	ch[1]��ҡ������Ϊ��
	ch[2]��ҡ������Ϊ��
	ch[3]��ҡ������Ϊ��

	ch[4]ң�������Ͻǲ���(�Ѿ���ȥ�м�ƫ����)��
		���ֵ 660 ��
		�м�ֵ 0
		��Сֵ -660 ��
	s1~s2:����
		�� 1
		�� 3
		�� 2
*/
typedef __packed struct
{
	int16_t ch[5];
	Sw_Data_t s1;		///<��
	Sw_Data_t s2;		///<��
}Remote_Data_t;

///	@brief	����ģʽö��
typedef enum
{
	REMOTE_INPUT    = 1,///<ң������
	KEY_MOUSE_INPUT = 3,///<��������
	STOP            = 2,
}InputMode_e;

/**
@brief	���ͨ��
	x,y,z:
		���ֵ 32767 �� ��
		��Сֵ�\32768 �� ��
		��ֵֹ 0	
	press_l��press_r:
		����	1
		û����	0
*/
typedef __packed struct
{
	int16_t x;				///<���x��
	int16_t y;				///<���y��
	int16_t z;				///<���z��ʵ���ò���
	uint8_t press_l;        //���
	uint8_t press_r;
}Mouse_Data_t;

/**
@brief	����ͨ��
		����	1
		û����	0
*/
typedef	__packed struct
{   //��д
	uint16_t W:1;
	uint16_t S:1;
	uint16_t A:1;
	uint16_t D:1;
	uint16_t SHIFT:1;
	uint16_t CONTRL:1;
	uint16_t Q:1;
	uint16_t E:1;
	uint16_t R:1;
	uint16_t F:1;
	uint16_t G:1;
	uint16_t Z:1;
	uint16_t X:1;
	uint16_t C:1;
	uint16_t V:1;
	uint16_t B:1;
}Key_Data_t;

/**
@brief	������Ϣ
*/
typedef __packed struct{
	Remote_Data_t rc;
	Mouse_Data_t  mouse;
	Key_Data_t    key;
}RC_Data_t;



//��������
void DbusUsart2_Init(void);
void Remote_Swich_Encode(Sw_Data_t *SW,uint8_t sw);
void Remote_Data_Encode(uint8_t *pData);

RC_Data_t GetRcData(void);
RC_Data_t *get_remote_control_point(void);
RC_Data_t GetLastRcData(void);
RC_Data_t *get_remote_last_point(void);
int16_t Getdbusoffline_flag(void);

#endif




