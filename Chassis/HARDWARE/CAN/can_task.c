/**
 * @file��  can_task.c�ļ��ڴ��ļ��ڽ�����λ��������ͨ��
 * @brief�� �������������Ϣ���룬�����������Ϣ���Ƶ���ĺ���         
 * @details�����⻹���ܽǶ��������ĺ���
 * @author��
 * @date��   2021.10.28
 * @version�� 
 * @par History:
    version:
 */
#include "can_task.h"
#include "usart.h"
#include "chassis_run.h"

#include <stdio.h>
#include <string.h>


///<�޷��궨��
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


/// @brief CANͨ���豸����������Ϣ
static Can_Cfg_Info_t 	can_cfg_info[CAN_DEVICE_NUM];
/// @brief CANͨ���豸��������(ecd_angleȡ4000��ֹ�������ʱ������λ�õ���cycles++)
static Motor_Data_t 	motor_data[CAN_DEVICE_NUM]={4000,0,0,0,0};
static Motor_Data_t 	motor_last_data[CAN_DEVICE_NUM]={4000,0,0,0,0};

/// @brief CANͨ���豸��������
static uint8_t data_CAN1_0x200[8] = {0};
static uint8_t data_CAN1_0x1FF[8] = {0};
static uint8_t data_CAN1_0x2FF[8] = {0};
static uint8_t data_CAN2_0x200[8] = {0};
static uint8_t data_CAN2_0x1FF[8] = {0};
static uint8_t data_CAN2_0x2FF[8] = {0};

/// @brief ����̨�յ��ĵ��̵��ٶ�������,Info[0~1]Ϊ����״̬��Ϣ,Info[2~3,4~5,6~7]�ֱ�ΪVx��Vy��W�ٶ�������
uint8_t Info[8] = {0}; 


//------------------------------------------------------------
//������ú���
//------------------------------------------------------------
void CAN_Device_Init(void)
{
	CAN_Motor_Config( CHASSIS_MOTOR_1, CHASSIS_MOTOR_1_ID, CHASSIS_MOTOR_1_TYPE, CHASSIS_MOTOR_1_CH, CHASSIS_MOTOR_1_BIAS );  //1��GM3508���
	CAN_Motor_Config( CHASSIS_MOTOR_2, CHASSIS_MOTOR_2_ID, CHASSIS_MOTOR_2_TYPE, CHASSIS_MOTOR_2_CH, CHASSIS_MOTOR_2_BIAS );  //2��GM3508���
	CAN_Motor_Config( CHASSIS_MOTOR_3, CHASSIS_MOTOR_3_ID, CHASSIS_MOTOR_3_TYPE, CHASSIS_MOTOR_3_CH, CHASSIS_MOTOR_3_BIAS );  //3��GM3508���
	CAN_Motor_Config( CHASSIS_MOTOR_4, CHASSIS_MOTOR_4_ID, CHASSIS_MOTOR_4_TYPE, CHASSIS_MOTOR_4_CH, CHASSIS_MOTOR_4_BIAS );  //4��GM3508���
	CAN_Motor_Config( MINE_MOTOR_1, MINE_MOTOR_1_ID, MINE_MOTOR_1_TYPE, MINE_MOTOR_1_CH, MINE_MOTOR_1_BIAS );  //5��M2006���
	CAN_Motor_Config( MINE_MOTOR_2, MINE_MOTOR_2_ID, MINE_MOTOR_2_TYPE, MINE_MOTOR_2_CH, MINE_MOTOR_2_BIAS );  //6��M2006���
	CAN_Motor_Send_ID_Print();
	CAN_Motor_ID_CHECK();
}

/**
@brief CAN�����Ϣ���� 
@param device_seq	�豸���к�,���������豸������С��CAN_DEVICE_NUM
@param ID			������뿨��ID
@param device		�豸���ͣ���ϸ�ο�Motor_Data_t�ṹ��ע��
@param CAN_x 		CAN_1��CAN_2
@param bias			���̽Ƕȼ���Ĳο�ƫ����
*/
//���IDΪ1-4ʱ����ʶ��Ϊ0x200�����IDΪ5-8ʱ����ʶ��Ϊ0x1FF��
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
	else printf( "seq����С��CAN_DEVICE_NUM\r\n" );
}

/**
@brief �ж��Ƿ����ظ�ID
ֻ���������豸�������ִ��
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
					if( id_i == id_j ) printf( "����%d�豸����ID�ظ�\r\n", i + 1 ), Error = 1;
				}
				if( can_cfg_info[i].id_recieve == can_cfg_info[j].id_recieve ){
					printf( "����%d�豸����ID�ظ�\r\n", i + 1 ), Error = 1;
				}
			}
		}
	}
	return Error;
}
/**
@brief ��ӡ�豸����ID
	ֻ���������豸�������ִ��
*/
void CAN_Motor_Send_ID_Print(void)
{
	//�ǵ���������ע�͵�
	for( int i = 0; i < CAN_DEVICE_NUM; i++ )
	{
		if( can_cfg_info[i].ch == CAN_1 )
			printf("�豸����:%d\tid_send:%#X\tChannle:CAN1\r\n",i+1,can_cfg_info[i].id_send);
		else if( can_cfg_info[i].ch == CAN_2 )
			printf("�豸����:%d\tid_send:%#X\tChannle:CAN2\r\n",i+1,can_cfg_info[i].id_send);
	}
}
/**
@brief ��ȡָ�������ǰ����һ������
@param device_seq �����б��еĵ�����豸���к�
@param last_data:false-��ǰ���ݣ�true-��һ������
@return �豸��Ӧ��Motor_Data_t���͵����ݣ�
	���е�����нǶ���Ϣ����һ����������Ϣ
	��ϸ�ο�Motor_Data_t�ṹ��ע��
*/
Motor_Data_t GetMotorData( uint8_t device_seq, bool last_data )
{
	if( last_data )return motor_last_data[ device_seq - 1 ];
		return motor_data[ device_seq - 1 ];
}

/**
@brief �趨����Ŀ�������(δ����)
���Ʊ���ID��ɶ�Ӧ���
0x200	C610,C620
0x1FF	C610,C620,GM6020,RM6623,GM3510
0x2FF	GM6020,RM6623
@param �����б��е�����豸���к�
@param current�ǵ�������ֵ
*/
void SetMotorCurrent( uint8_t device_seq, int16_t current ){
	///<�޷��������ֲ��ϵķ�ֵ�޷���
    switch( can_cfg_info[device_seq-1].type ){
    case C610:		VAL_LIMIT( current, -10000, 10000 );break; //C610��-10000��10000
    case C620:		VAL_LIMIT( current, -16384, 16384 );break; //C620��-16384��16384
    case GM6020:	VAL_LIMIT( current, -30000, 30000 );break;
    case GM3510:	VAL_LIMIT( current, -5000, 5000 );break;
    default:break;
    }
    ///<�жϲ��洢
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


/**
 * @brief ����̨���͵�����,�洢��ȫ�ֱ���֮��
 * @param StdidΪ���ݷ��ͷ���ʶ���
 * @param Data[8]Ϊ���ݷ��ͷ����͵�����
 */
void ReceiveGimbalData( uint32_t StdId, uint8_t Data[8] )
{  //��̨���͵�����,Data[0~1]Ϊ����״̬��Ϣ,Data[2~3,4~5,6~7]�ֱ�ΪVx��Vy��W�ٶ�������
	for( int i = 0; i <= 7; i++ )
	{
		Info[i] = Data[i];
	}
}


/**
 * @brief �����̨���͵�����,�����õ��̵��ٶ�������
 * @param DataΪ�洢��̨���ݵ������׵�ַ
 */
void GetGimbalInfo( u8 *Data )
{
	//����̨ͨ��CAN2����������Ϣ�洢��������
	Data[0] = Info[0];
	Data[1] = Info[1];
	
	int16_t VX = ( ( Info[2] << 8 ) | Info[3] );
	int16_t VY = ( ( Info[4] << 8 ) | Info[5] );
	int16_t VW = ( ( Info[6] << 8 ) | Info[7] );
	
	SetChassisSpeed( VX, VY, VW );	
}


//�õ�����ϵͳ����Ϣ
void Get_Judge_Info( u8 *Data )
{
	Data[0] = Info[0];
	Data[1] = Info[1];
}

/**
 * @brief ����̨������Ϣ
 * @param *msgΪ��������Ϣ�ĵ�ַ
 * @param lenΪ��������Ϣ�ĳ���,���Ϊ8(��0λ~��7λ)
 * @return ������к�
 */
uint8_t SendGimbalData( uint8_t* msg, uint8_t len )
{
	uint8_t mbox;
	uint16_t i = 0;
	CanTxMsg TxMessage;
	TxMessage.StdId = 0x402;				 // ��׼��ʶ��
	TxMessage.IDE = CAN_Id_Standard;         // ��׼֡
	TxMessage.RTR = CAN_RTR_Data;		     // ����֡
	TxMessage.DLC = len;				     // Ҫ���͵����ݳ���
	
	for( i = 0; i < len; i++ )
	{
		TxMessage.Data[i]=msg[i];
	}
	
	mbox = CAN_Transmit( CAN2, &TxMessage );
	i = 0;
	while( ( CAN_TransmitStatus( CAN2, mbox ) == CAN_TxStatus_Failed ) && ( i < 0XFFF ) ) i++;	//�ȴ����ͽ���
	if( i >= 0XFFF ) 
	{
		return 1;
	}
	return 0;
}

/**
@brief  ͬʱ�������е�������ݣ��������1ms����ѭ���ڡ�
0x200	C610,C620
0x1FF	C610,C620,GM6020,RM6623,GM3510
0x2FF	GM6020,RM6623
*/
void SendMotorCurrent(void)
{
	static uint8_t can_send_id_flags=0x00;
	//7-null;6-state flag;5:3-CAN2-0x200/0x1FF/0x2FF;2:0-CAN1-0x200/0x1FF/0x2FF;
	///<�������Щ����id��Ҫ���ͣ��Լ�������can�����ϣ�ֻ�����һ�λ�ȡcan_send_id_flags����־λ
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
		can_send_id_flags|=0x40;//������е����־λ���ٽ���
	}
    ///<���ձ�־λ��������
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

//�Ƕ�ת���������ڲ����������ж��Ƿ񳬹�һȦ��������Ȧ�������޸�
void Angle_Convert( uint8_t seq )
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

//�������Ƕ�ת�����ڲ�������
void EcdAngle_Convert( uint8_t seq )
{
	if( ( motor_data[ seq - 1 ].ecd_angle - motor_last_data[ seq - 1 ].ecd_angle ) > 6000 ) 
		motor_data[ seq - 1 ].ecd_cycles--;
	else if( ( motor_data[ seq - 1 ].ecd_angle - motor_last_data[ seq - 1 ].ecd_angle ) < -6000 ) 
		motor_data[ seq - 1 ].ecd_cycles++;
}


//------------------------------------------------------------
//�ײ�ʵ�ֺ���
//------------------------------------------------------------
/**
 * @brief ������ݽ��뺯��������CANͨ���жϻص������У�����ڸú����н��д���
 *  	  �������Ƶ��Ϊ1kHz�������յ����������ʱʱ���1ms����һ��
 * @param uint32_t	StdId		CANͨ�ű���ID
 * @param uint8_t	Data[8]		CANͨ��8λ����
 * @param Can_Channel_e	CAN_x	CAN_1��CAN_2��ȡ�������ĸ��жϻص�������
 */
void CAN_Message_Encode( uint32_t StdId,uint8_t Data[8], Can_Channel_e CAN_x)
{
	int i=0;
	///���յ������
	for(;i<CAN_DEVICE_NUM;i++){
		if(can_cfg_info[i].ch==CAN_x){
			if(StdId==can_cfg_info[i].id_recieve){
				switch(can_cfg_info[i].type){
					case C610:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].speed	=(Data[2]<<8)|Data[3];    //ת��ֵ��λΪrpm
						motor_data[i].torque=(Data[4]<<8)|Data[5];
						motor_data[i].selfcheck = 0;
						Angle_Convert(i+1);           //����Ƕ�
						EcdAngle_Convert( i + 1);     //����������Ƕ�
					}break;
					case C620:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].speed	=(Data[2]<<8)|Data[3];
						motor_data[i].torque=(Data[4]<<8)|Data[5];
						motor_data[i].temperature=Data[6];
						motor_data[i].selfcheck = 0;
						Angle_Convert(i+1);
						EcdAngle_Convert( i + 1);
					}break;
					case GM6020:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].speed	=(Data[2]<<8)|Data[3];
						motor_data[i].torque=(Data[4]<<8)|Data[5];
						motor_data[i].temperature=Data[6];
						motor_data[i].selfcheck = 0;
						Angle_Convert(i+1);
						EcdAngle_Convert( i + 1);
					}break;
					case GM3510:{
						motor_last_data[i]=motor_data[i];
						motor_data[i].ecd_angle	=(Data[0]<<8)|Data[1];
						motor_data[i].torque=(Data[2]<<8)|Data[3];
						Angle_Convert(i+1);
						EcdAngle_Convert( i + 1);
						motor_data[i].selfcheck = 0;
					}break;
					default:break;
				}
				i=CAN_DEVICE_NUM;	///<����ѭ��
			}
		}
	}
	//if(i==CAN_DEVICE_NUM)printf("����δʶ���豸,ID=%#X\r\n",StdId);///<���������и��豸���������˴�ʱi=CAN_DEVICE_NUM+1
}

/**
 * @brief ��������Լ�,�Լ첻ͨ���򱨾�
 * @param  void
 * @return ʧ��������к�
 */
int8_t ChassisSelfCheck(void)
{
	int i =0;
	for( ; i < CAN_DEVICE_NUM; i++)
	{
		motor_data[i].selfcheck++;
		if( motor_data[i].selfcheck >= 100 )
		{
			//warning	
			//printf( "�豸����%d����\r\n",i + 1 ); // �û����������кţ���1��ʼ
			
			return ( i + 1 );//�ݶ���������ϵͳ�Ĳ���
		}
	}	
  return 0;            // �Լ�ͨ��
}


/**
 * @brief CANͨ�����ݷ��ͺ�������Ҫ�ڶ�Ӧ���̵ײ��ļ���ʵ��
 * 
 * @param Can_Channel_e	CAN_x	CAN_1��CAN_2��ȡ�������ĸ��жϻص�������
 * @param uint32_t	StdId		CANͨ�ű���ID
 * @param uint8_t	Data[8]		CANͨ��8λ����
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

