#ifndef __DBUS_REMOTE__H__
#define __DBUS_REMOTE__H__

#include "sys.h"


//------------------------------------------------------------
//常量定义
//------------------------------------------------------------
///	@brief接收原始数据，为18个字节，给了36个字节长度，防止DMA传输越界
#define DBUS_RX_BUF_NUM 36u
#define RC_FRAME_LENGTH 18u
///	@brief 遥控器通道中间偏移值
#define REMOTE_CONTROLLER_OFFSET      (1024u) 


//------------------------------------------------------------
//数据结构体定义
//------------------------------------------------------------

/**
@brief	遥控器switch开关通道
	在某位置则为1，不在该位置则为0
*/
typedef __packed struct
{
	uint8_t up:1;
	uint8_t mid:1;
	uint8_t down:1;
}Sw_Data_t;


/**
@brief	遥控器通道
	ch[0]~ch[3]遥控器遥杆(已经减去中间偏移量)：
		最大值 660 右/上
		中间值 0
		最小值 -660  左/下
	ch[0]右摇杆向右为正
	ch[1]右摇杆向下为负
	ch[2]左摇杆向右为正
	ch[3]左摇杆向下为负

	ch[4]遥控器左上角拨轮(已经减去中间偏移量)：
		最大值 660 下
		中间值 0
		最小值 -660 上
	s1~s2:拨杆
		上 1
		中 3
		下 2
*/
typedef __packed struct
{
	int16_t ch[5];
	Sw_Data_t s1;		///<左
	Sw_Data_t s2;		///<右
}Remote_Data_t;

///	@brief	输入模式枚举
typedef enum
{
	REMOTE_INPUT    = 1,///<遥控输入
	KEY_MOUSE_INPUT = 3,///<键盘输入
	STOP            = 2,
}InputMode_e;

/**
@brief	鼠标通道
	x,y,z:
		最大值 32767 右 下
		最小值‐32768 左 上
		静止值 0	
	press_l，press_r:
		按下	1
		没按下	0
*/
typedef __packed struct
{
	int16_t x;				///<鼠标x轴
	int16_t y;				///<鼠标y轴
	int16_t z;				///<鼠标z轴实际用不了
	uint8_t press_l;        //左键
	uint8_t press_r;
}Mouse_Data_t;

/**
@brief	键盘通道
		按下	1
		没按下	0
*/
typedef	__packed struct
{   //大写
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
@brief	控制信息
*/
typedef __packed struct{
	Remote_Data_t rc;
	Mouse_Data_t  mouse;
	Key_Data_t    key;
}RC_Data_t;



//函数定义
void DbusUsart2_Init(void);
void Remote_Swich_Encode(Sw_Data_t *SW,uint8_t sw);
void Remote_Data_Encode(uint8_t *pData);

RC_Data_t GetRcData(void);
RC_Data_t *get_remote_control_point(void);
RC_Data_t GetLastRcData(void);
RC_Data_t *get_remote_last_point(void);
int16_t Getdbusoffline_flag(void);

#endif




