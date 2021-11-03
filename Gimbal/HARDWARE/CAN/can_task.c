/**
 * @file：  can_task.c文件在此文件内进行上位机与电调的通信
 * @brief： 包括电调返还信息解码，给电调发送信息控制电机的函数         
 * @details：此外还有总角度连续化的函数
 * @author：
 * @date：   2021.10.28
 * @version： 
 * @par History:
    version:
 */
#include "can_task.h"
#include "usart.h"

#include <stdio.h>
#include <string.h>


///<限幅宏定义
#ifndef VAL_LIMIT
#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\
else {val = val;}
#endif


/// @brief CAN通信设备配置配置信息
static Can_Cfg_Info_t 	can_cfg_info[CAN_DEVICE_NUM];
/// @brief CAN通信设备接收数据(ecd_angle取4000防止电机启动时在特殊位置导致cycles++)
static Motor_Data_t 	motor_data[CAN_DEVICE_NUM]={4000,0,0,0,0};
static Motor_Data_t 	motor_last_data[CAN_DEVICE_NUM]={4000,0,0,0,0};

/// @brief CAN通信设备发送数据
static uint8_t data_CAN1_0x200[8] = {0};
static uint8_t data_CAN1_0x1FF[8] = {0};
static uint8_t data_CAN1_0x2FF[8] = {0};
static uint8_t data_CAN2_0x200[8] = {0};
static uint8_t data_CAN2_0x1FF[8] = {0};
static uint8_t data_CAN2_0x2FF[8] = {0};

///@brief 底盘自检变量
int8_t chassis_motorselfcheck = 1;     //1表示自检未成功

///
int16_t disc = 0;


//------------------------------------------------------------
//电机配置函数
//------------------------------------------------------------
void CAN_Device_Init(void)
{
	CAN_Motor_Config(Craw_MOTOR_1, Craw_MOTOR_1_ID, Craw_MOTOR_1_TYPE, Craw_MOTOR_1_CH, Craw_MOTOR_1_BIAS);  //1号GM3508电机
	CAN_Motor_Config(Craw_MOTOR_2, Craw_MOTOR_2_ID, Craw_MOTOR_2_TYPE, Craw_MOTOR_2_CH, Craw_MOTOR_2_BIAS);  //2号GM3508电机
	CAN_Motor_Config(updown_MOTOR_1, updown_MOTOR_1_ID, updown_MOTOR_1_TYPE, updown_MOTOR_1_CH, updown_MOTOR_1_BIAS);  //3号GM3508电机
	CAN_Motor_Config(updown_MOTOR_2, updown_MOTOR_2_ID, updown_MOTOR_2_TYPE, updown_MOTOR_2_CH, updown_MOTOR_2_BIAS);  //4号GM3508电机
	CAN_Motor_Send_ID_Print();
	CAN_Motor_ID_CHECK();
}

/**
@brief CAN电机信息配置 
@param device_seq	设备序列号,用于区分设备，必须小于CAN_DEVICE_NUM
@param ID			电调拨码卡关ID
@param device		设备类型，详细参考Motor_Data_t结构体注释
@param CAN_x 		CAN_1或CAN_2
@param bias			码盘角度计算的参考偏移量
*/
//电调ID为1-4时，标识符为0x200；电调ID为5-8时，标识符为0x1FF。
void CAN_Motor_Config( uint8_t device_seq, uint32_t ID, Device_Type_e device, Can_Channel_e CAN_x, int16_t bias )
{
	if( device_seq<=CAN_DEVICE_NUM )
	{
		can_cfg_info[ device_seq - 1 ].id = ID;
		can_cfg_info[ device_seq - 1 ].ch = CAN_x;
		can_cfg_info[ device_seq - 1 ].type = device;
		can_cfg_info[ device_seq - 1 ].ecd_bias = bias;
		switch( device )
		{
			case C610:{
				if( ID <= 4 ){
					can_cfg_info[ device_seq - 1 ].id_send = 0x200;
					can_cfg_info[ device_seq - 1 ].id_recieve = 0x200 + ID;
				}
				else if( ID <= 8 ){
					can_cfg_info[ device_seq - 1 ].id_send = 0x1FF;
					can_cfg_info[ device_seq - 1 ].id_recieve = 0x200 + ID;
				}
				else printf( "ID wrong\r\n" );
			}break;
			case C620:{
				if(ID <= 4){
					can_cfg_info[ device_seq - 1].id_send = 0x200;
					can_cfg_info[ device_seq - 1].id_recieve = 0x200 + ID;
				}
				else if( ID <= 8 ){
					can_cfg_info[ device_seq - 1 ].id_send = 0x1FF;
					can_cfg_info[ device_seq - 1 ].id_recieve = 0x200 + ID;
				}
				else printf( "ID wrong\r\n" );
			}break;
			case GM6020:{
				if( ID >= 1 && ID <= 4 ){
					can_cfg_info[ device_seq - 1 ].id_send = 0x1FF;
					can_cfg_info[ device_seq - 1 ].id_recieve = 0x204 + ID;
				}
				else if( ID <= 7 ){
					can_cfg_info[ device_seq - 1 ].id_send = 0x2FF;
					can_cfg_info[ device_seq - 1 ].id_recieve = 0x204 + ID;
				}
				else printf("ID wrong\r\n");
			}break;			
			case GM3510:{
				if( ID >= 1 && ID <= 3 ){
					can_cfg_info[ device_seq - 1 ].id_send = 0x1FF;
					can_cfg_info[ device_seq - 1 ].id_recieve = 0x204 + ID;
				}
				else printf( "ID wrong\r\n" );
			}break;
			case Chassis:{
				can_cfg_info[ device_seq - 1 ].id_send = ID;
			}break;
			default:{} break;
		}
	}
	else printf( "seq必须小于CAN_DEVICE_NUM\r\n" );
}

/**
@brief 判断是否有重复ID
只能在所有设备配置完后执行
*/
bool CAN_Motor_ID_CHECK(void){
	bool Error=0;
	for( int i = 0; i < CAN_DEVICE_NUM; i++ ){
		int id_i = 0;
		id_i = can_cfg_info[i].id;
		for( int j = i + 1; j < CAN_DEVICE_NUM; j++ ){
			int id_j = 0;
			id_j = can_cfg_info[j].id;
			if( can_cfg_info[i].ch == can_cfg_info[j].ch ){
				if( can_cfg_info[i].id_send == can_cfg_info[j].id_send ){
					if( id_i == id_j ) printf( "序列%d设备发送ID重复\r\n", i + 1 ), Error = 1;
				}
				if( can_cfg_info[i].id_recieve == can_cfg_info[j].id_recieve ){
					printf( "序列%d设备接收ID重复\r\n", i + 1 ), Error = 1;
				}
			}
		}
	}
	return Error;
}
/**
@brief 打印设备控制ID
	只能在所有设备配置完后执行
*/
void CAN_Motor_Send_ID_Print(void)
{
	//记得在最后将这段注释掉
	for( int i = 0; i < CAN_DEVICE_NUM; i++ )
	{
		if( can_cfg_info[i].ch == CAN_1 )
			printf("设备序列:%d\tid_send:%#X\tChannle:CAN1\r\n",i+1,can_cfg_info[i].id_send);
		else if( can_cfg_info[i].ch == CAN_2 )
			printf("设备序列:%d\tid_send:%#X\tChannle:CAN2\r\n",i+1,can_cfg_info[i].id_send);
	}
}
/**
@brief 获取指定电机当前或上一次数据
@param device_seq 配置列表中的电机的设备序列号
@param last_data:false-当前数据，true-上一次数据
@return 设备对应的Motor_Data_t类型的数据，
	所有电机都有角度信息，不一定有其他信息
	详细参考Motor_Data_t结构体注释
*/
Motor_Data_t GetMotorData( uint8_t device_seq, bool last_data )
{
	if( last_data )return motor_last_data[ device_seq - 1 ];
		return motor_data[ device_seq - 1 ];
}

/**
@brief 设定电机的控制数据(未发送)
控制报文ID与可对应电机
0x200	C610,C620
0x1FF	C610,C620,GM6020,RM6623,GM3510
0x2FF	GM6020,RM6623
@param 配置列表中电机的设备序列号
@param current是电机的输出值
*/
void SetMotorCurrent( uint8_t device_seq, int16_t current ){
	///<限幅（按照手册上的幅值限幅）
    switch( can_cfg_info[device_seq-1].type ){
    case C610:		VAL_LIMIT( current, -10000, 10000 );break; //C610是-10000到10000
    case C620:		VAL_LIMIT( current, -16384, 16384 );break; //C620是-16384到16384
    case GM6020:	VAL_LIMIT( current, -30000, 30000 );break;
    case GM3510:	VAL_LIMIT( current, -5000, 5000 );break;
    default:break;
    }
    ///<判断并存储
    if( can_cfg_info[ device_seq - 1 ].ch == CAN_1 ){
        switch( can_cfg_info[ device_seq - 1 ].id_send ){
            case 0x200:{
                data_CAN1_0x200[ 2 * can_cfg_info[ device_seq - 1 ].id - 2 ] = ( uint8_t )( current >> 8 );
                data_CAN1_0x200[ 2 * can_cfg_info[ device_seq - 1 ].id - 1 ] = ( uint8_t )current;
            }break;
            case 0x1FF:{
                if( can_cfg_info[ device_seq - 1 ].type == C610 || can_cfg_info[ device_seq - 1 ].type == C620){
                    data_CAN1_0x1FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 2 ] = ( uint8_t )( current >> 8 );
                    data_CAN1_0x1FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 1 ] = ( uint8_t )current;
                }
                else if( can_cfg_info[device_seq - 1 ].type == GM6020 || can_cfg_info[ device_seq - 1 ].type == GM6020){
                    data_CAN1_0x1FF[ 2 * can_cfg_info[ device_seq - 1 ].id - 2 ] = ( uint8_t )( current >> 8 );
                    data_CAN1_0x1FF[ 2 * can_cfg_info[ device_seq - 1 ].id - 1 ] = ( uint8_t )current;
                }
            }break;
            case 0x2FF:{
                if( can_cfg_info[ device_seq - 1 ].type == GM6020 ){
                    data_CAN1_0x2FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 2 ] = ( uint8_t )( current >> 8 );
                    data_CAN1_0x2FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 1 ] = ( uint8_t )current;
                }
            }break;
        }
    }
    else if( can_cfg_info[ device_seq - 1 ].ch == CAN_2 ){
        switch( can_cfg_info[ device_seq - 1 ].id_send){
            case 0x200:{
                data_CAN2_0x200[ 2 * can_cfg_info[ device_seq - 1 ].id - 2 ] = ( uint8_t )( current >> 8 );
                data_CAN2_0x200[ 2 * can_cfg_info[ device_seq - 1 ].id - 1 ] = ( uint8_t )current;
            }break;
            case 0x1FF:{
                if( can_cfg_info[ device_seq - 1 ].type == C610 || can_cfg_info[ device_seq - 1 ].type == C620 ){
                    data_CAN2_0x1FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 2 ] = ( uint8_t )( current >> 8 );
                    data_CAN2_0x1FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 1 ] = ( uint8_t )current;
                }
                else if( can_cfg_info[ device_seq - 1 ].type == GM6020 || can_cfg_info[ device_seq - 1 ].type == GM6020 ){
                    data_CAN2_0x1FF[ 2 * can_cfg_info[ device_seq - 1 ].id - 2 ] = ( uint8_t )( current >> 8 );
                    data_CAN2_0x1FF[ 2 * can_cfg_info[ device_seq - 1 ].id - 1 ] = ( uint8_t )current;
                }
            }break;
            case 0x2FF:{
                if( can_cfg_info[ device_seq - 1 ].type == GM6020 ){
                    data_CAN2_0x2FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 2 ] = ( uint8_t )( current >> 8 );
                    data_CAN2_0x2FF[ 2 * ( can_cfg_info[ device_seq - 1 ].id - 4 ) - 1 ] = ( uint8_t )current;
                }
            }break;
        }
    }
}


void SendChassisInfo(CAN_TypeDef *CANx, uint8_t mode, int16_t Vx, int16_t Vy, int16_t W){
    CanTxMsg tx_message;
    tx_message.StdId = 0x401;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    tx_message.Data[0] = mode;
    tx_message.Data[1] = mode;
    tx_message.Data[2] = (uint8_t)(Vx >> 8);
    tx_message.Data[3] = (uint8_t)Vx;
    tx_message.Data[4] = (uint8_t)(Vy >> 8);
    tx_message.Data[5] = (uint8_t)Vy;
    tx_message.Data[6] = (uint8_t)(W >> 8);
    tx_message.Data[7] = (uint8_t)W;
    CAN_Transmit(CANx,&tx_message);
}

void SendChassisInfo_2(CAN_TypeDef *CANx, uint8_t mode1, uint8_t mode2, int16_t Vx, int16_t Vy, int16_t W){
    CanTxMsg tx_message;
    tx_message.StdId = 0x401;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    tx_message.Data[0] = mode1;               //底盘状态
    tx_message.Data[1] = mode2;               //云台状态
    tx_message.Data[2] = (uint8_t)(Vx >> 8);
    tx_message.Data[3] = (uint8_t)Vx;
    tx_message.Data[4] = (uint8_t)(Vy >> 8);
    tx_message.Data[5] = (uint8_t)Vy;
    tx_message.Data[6] = (uint8_t)(W >> 8);
    tx_message.Data[7] = (uint8_t)W;
    CAN_Transmit(CANx,&tx_message);
}
//设置底盘自检
void setchassis_MotorSelfCheck(int8_t chassis_check){
    chassis_motorselfcheck = chassis_check;
}

//对底盘发送的数据进行分析，判断模式
void ReceiveChassisInfo( uint32_t StdId,uint8_t Data[8] ){
	if( StdId == 0x402 ){
		
		if( Data[0]&0x01 ){
			setchassis_MotorSelfCheck( checkok );
			
			switch(Data[0]){
				
				case 0x13:{
					disc = small_discup;
				}break;
				case 0x33:{
					disc = small_discmid;
				}break;
				
				case 0x15:{
				  disc = exchange_discmid;
				}break;
				case 0x35:{
				  disc = exchange_discup;
				}break;
				
				case 0x17:{
				  disc = large_discmid;
				}break;
				case 0x37:{
				  disc = large_discup;
				}break;
				
				case 0x19:{
				  disc = setturncylinder;
				}break;
				case 0x39:{
				  disc = resetturncylinder;
				}break;
				
				default:{
					disc = 0;
				}break;
			}

			
		}
		
		else{
			setchassis_MotorSelfCheck( checkfalse );
		}
		
	}
}

int16_t get_discstate(void){
  return disc;
}

/**
@brief  同时发送所有电机的数据，建议放在1ms独立循环内。
0x200	C610,C620
0x1FF	C610,C620,GM6020,RM6623,GM3510
0x2FF	GM6020,RM6623
*/
void SendMotorCurrent(void)
{
	static uint8_t can_send_id_flags=0x00;
	//7-null;6-state flag;5:3-CAN2-0x200/0x1FF/0x2FF;2:0-CAN1-0x200/0x1FF/0x2FF;
	///<获得有哪些发送id需要发送，以及在哪条can总线上，只需进入一次获取can_send_id_flags各标志位
	if((can_send_id_flags&0x40)==0x00)
	{
		for(uint8_t device_seq=1;device_seq<=CAN_DEVICE_NUM;device_seq++)
		{
			switch(can_cfg_info[device_seq-1].id_send)
			{
				case 0x200:
				{
					if(can_cfg_info[device_seq-1].ch==CAN_1){can_send_id_flags|=(0x01<<2);}
					else{can_send_id_flags|=(0x01<<5);}
				}break;
				case 0x1FF:
				{
					if(can_cfg_info[device_seq-1].ch==CAN_1){can_send_id_flags|=(0x01<<1);}
					else{can_send_id_flags|=(0x01<<4);}
				}break;
				case 0x2FF:
				{
					if(can_cfg_info[device_seq-1].ch==CAN_1){can_send_id_flags|=(0x01<<0);}
					else{can_send_id_flags|=(0x01<<3);}
				}break;
			}
		}
		can_send_id_flags|=0x40;//获得所有电机标志位后不再进入
	}
    ///<按照标志位发送数据
	{
		if((can_send_id_flags&(0x01<<0)))
		{//CAN1_0x2FF
			CAN_Data_Tx(0x2FF,data_CAN1_0x2FF,CAN_1);
		}
		if((can_send_id_flags&(0x01<<1)))
		{//CAN1_0x1FF
			CAN_Data_Tx(0x1FF,data_CAN1_0x1FF,CAN_1);
		}
		if((can_send_id_flags&(0x01<<2)))
		{//CAN1_0x200
			CAN_Data_Tx(0x200,data_CAN1_0x200,CAN_1);
		}
		if((can_send_id_flags&(0x01<<3)))
		{//CAN2_0x2FF
			CAN_Data_Tx(0x2FF,data_CAN2_0x2FF,CAN_2);
		}
		if((can_send_id_flags&(0x01<<4)))
		{//CAN2_0x1FF
			CAN_Data_Tx(0x1FF,data_CAN2_0x1FF,CAN_2);
		}
		if((can_send_id_flags&(0x01<<5)))
		{//CAN2_0x200
			CAN_Data_Tx(0x200,data_CAN2_0x200,CAN_2);
		}
	}
}

//角度转换函数（内部函数），判断是否超过一圈，并对总圈数进行修改
void angle_convert( uint8_t seq )
{
	motor_data[ seq - 1 ].angle = ( motor_data[ seq - 1 ].ecd_angle - can_cfg_info[ seq - 1 ].ecd_bias ) * 360.00 / Full_Ecd_Angle;
	if( motor_data[ seq - 1 ].angle > 180 )
	{
		motor_data[ seq - 1 ].angle -= 360.0f;
	}
	else if( motor_data[ seq - 1 ].angle < -180 )
	{
		motor_data[ seq - 1 ].angle += 360.0f;
	}
	if( ( motor_data[ seq - 1 ].angle - motor_last_data[ seq - 1 ].angle ) > 300 ) 
		motor_data[ seq - 1 ].cycles--;
	else if( ( motor_data[ seq - 1 ].angle - motor_last_data[ seq - 1 ].angle ) < -300 ) 
		motor_data[ seq - 1 ].cycles++;
}

//编码器角度转换（内部函数）
void EcdAngle_convert( uint8_t seq )
{
	if( ( motor_data[ seq - 1 ].ecd_angle - motor_last_data[ seq - 1 ].ecd_angle ) > 6000 ) 
		motor_data[ seq - 1 ].ecd_cycles--;
	else if( ( motor_data[ seq - 1 ].ecd_angle - motor_last_data[ seq - 1 ].ecd_angle ) < -6000 ) 
		motor_data[ seq - 1 ].ecd_cycles++;
}


//------------------------------------------------------------
//底层实现函数
//------------------------------------------------------------
/**
 * @brief 电机数据解码函数，放在CAN通信中断回调函数中，电机在该函数中进行处理
 *  	  电调发送频率为1kHz，即接收电调返回数据时时最快1ms接收一次
 * @param uint32_t	StdId		CAN通信报文ID
 * @param uint8_t	Data[8]		CAN通信8位数据
 * @param Can_Channel_e	CAN_x	CAN_1或CAN_2，取决于在哪个中断回调函数中
 */
void CAN_Message_Encode( uint32_t StdId,uint8_t Data[8], Can_Channel_e CAN_x)
{
	int i=0;
	///接收电机数据
	for(;i<CAN_DEVICE_NUM;i++){
		if(can_cfg_info[i].ch==CAN_x){
			if(StdId==can_cfg_info[i].id_recieve){
				switch(can_cfg_info[i].type){
					case C610:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].speed	=(Data[2]<<8)|Data[3];    //转速值单位为rpm
						motor_data[i].torque=(Data[4]<<8)|Data[5];
						motor_data[i].selfcheck = 0;
						angle_convert(i+1);           //换算角度
						EcdAngle_convert( i + 1);     //换算编码器角度
					}break;
					case C620:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].speed	=(Data[2]<<8)|Data[3];
						motor_data[i].torque=(Data[4]<<8)|Data[5];
						motor_data[i].temperature=Data[6];
						motor_data[i].selfcheck = 0;
						angle_convert(i+1);
						EcdAngle_convert( i + 1);
					}break;
					case GM6020:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].speed	=(Data[2]<<8)|Data[3];
						motor_data[i].torque=(Data[4]<<8)|Data[5];
						motor_data[i].temperature=Data[6];
						motor_data[i].selfcheck = 0;
						angle_convert(i+1);
						EcdAngle_convert( i + 1);
					}break;
					case GM3510:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].torque=(Data[2]<<8)|Data[3];
						angle_convert(i+1);
						EcdAngle_convert( i + 1);
						motor_data[i].selfcheck = 0;
					}break;
					default:break;
				}
				i=CAN_DEVICE_NUM;	///<结束循环
			}
		}
	}
	if(i==CAN_DEVICE_NUM)printf("存在未识别设备,ID=%#X\r\n",StdId);///<若数组内有该设备，运行至此处时i=CAN_DEVICE_NUM+1
}


/**
 * @brief 电机启动自检，自检不通过则报警
 * @param void
 * @return 电机序列号
 */
int8_t getgimbal_MotorSelfCheck(void)
{
	int i =0;
	for(;i<CAN_DEVICE_NUM;i++)
	{
		motor_data[i].selfcheck++;
		if(motor_data[i].selfcheck>=500)
		{
			//warning		
			printf("设备序列号%d掉线\r\n",i+1); // 用户看到序列号
			return ( i+1 );//
		}
	}	
  return checkok;	
}


int8_t getchassis_MotorSelfCheck(void)
{
	return chassis_motorselfcheck;
}


/**
 * @brief CAN通信数据发送函数，需要在对应工程底层文件中实现
 * 
 * @param Can_Channel_e	CAN_x	CAN_1或CAN_2，取决于在哪个中断回调函数中
 * @param uint32_t	StdId		CAN通信报文ID
 * @param uint8_t	Data[8]		CAN通信8位数据
 */

void CAN_Data_Tx(uint32_t StdId,uint8_t Data[8],Can_Channel_e CAN_X)
{
	CanTxMsg tx_message;
	tx_message.IDE = CAN_Id_Standard;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 0x08;
	tx_message.StdId=StdId;
	memcpy(tx_message.Data,Data,sizeof(tx_message.Data));
	switch(CAN_X){
		case CAN_1: CAN_Transmit(CAN1,&tx_message);break;
		case CAN_2: CAN_Transmit(CAN2,&tx_message);break;
		default: break;
	}	
}

