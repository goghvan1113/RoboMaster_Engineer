#ifndef __JUDGESTRUCT_H__
#define __JUDGESTRUCT_H__

#include "stm32f4xx.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"


#define HEADER_LEN 5
#define CMD_LEN 2
#define CRC_LEN 2
#define PROTOCAL_FRAME_MAX_SIZE 128		//�����������ݵİ��ܹ������Ϊ 128 ���ֽ�
#define FrameHeaderSOF	0xA5


/////////////////////////////////////////////////////////�����Ǵ���д�Ĳ���ϵͳ����������


/************************************
*	����ϵͳ��������
*	������ʱ�䣺2021��5��8��
*************************************/

//ע�⣺ע�⣺һ��Ҫ�ӽṹ��Ķ��룬https://zhidao.baidu.com/question/418245481.html
//https://www.cnblogs.com/zhaoyl/archive/2012/04/21/2461077.html

#pragma pack(1)

typedef struct {
    uint8_t 	SOF;			//����֡��ʼ�ֽڣ��̶�ֵΪ0xA5;
    uint16_t    DataLength;		//����֡��Data����;
    uint8_t     Seq;			//�����;
    uint8_t     CRC8;			//֡ͷCRC8;
}frame_header_t;//һ��������ͨ��֡�����֡ͷ��ϸ����

typedef enum
{
    GAME_STATE_ID       = 0x0001,   //����״̬��1Hz��
    GAME_RESUIT_ID       = 0x0002,   //�������
    ROBOT_HP_ID         = 0x0003,   //������Ѫ�����ݣ�1Hz��
	//DART_FIRE_STATE		= 0x0004,	//���ڷ���״̬		//˵����2021��Э��V1.2�Ѹ�������ȥ����
	GAIN_AND_PUNISHMENT_STATE	= 0x0005,	//�˹�������ս���ӳ���ͷ���״̬��1HZ
    FIELD_EVENT_ID      = 0x0101,   //�����¼���1HZ
    SUPPLY_ACTION_ID    = 0x0102,   //����վ������ʶ
    //REQUEST_BULLET_ID   = 0x0103,   //���󲹵���RM�Կ�����δ���ţ�
    JUDGE_WARNING_ID    = 0x0104,   //���о�������
	DART_FIRE_COUNTDOWN	= 0x0105,	//���ڷ���ڵ���ʱ��1HZ����
    ROBOT_STATE_ID      = 0x0201,   //������״̬��10Hz��
    REALTIME_POWER_ID   = 0x0202,   //ʵʱ����������50Hz��
    ROBOT_POSITION_ID   = 0x0203,   //������λ�ã�10Hz��
    ROBOT_BUFF_ID       = 0x0204,   //����������
    DRONE_POWER_ID      = 0x0205,   //���л���������״̬���ݣ�10HZ��ֻ�п��л��������ط���
    ROBOT_HURT_ID       = 0x0206,   //�˺�����
    ROBOT_SHOOT_ID      = 0x0207,   //�������
    SURPLUS_BULLET_ID   = 0X0208,   //ʣ���ӵ������ڱ��Ϳ��л����ˣ�
	ROBOT_RFID_STATE	= 0x0209,	//������RFID״̬��1HZ���ڷ���
	ROBOT_OPERATOR_CMD	= 0x020A,	//���ڻ����˿ͻ���ָ�����ݣ�10HZ
    ROBOT_INTERACTIVE_ID= 0x0301,    //�����˼佻�������ʹ���
	SELF_CONTROL_INTERACTIVE_ID= 0x0302,	//�Զ����������������
	ROBOT_COMMAND_ID	= 0x0303,	//�ͻ���С��ͼ��������
	KEY_AND_MOUSE_ID	= 0x0304,	//������Ϣ
	RADAR_SEND_MAP_ID	= 0x0305,	//С��ͼ
} frame_cmd_id_e;
//frame_cmd_id_e;

typedef struct
{
	frame_header_t header;
	frame_cmd_id_e frame_cmd_id;
	uint8_t data[PROTOCAL_FRAME_MAX_SIZE];
	uint16_t frame_tail;
}JudgeFullFrame_t;
//һ��������ͨ��֡��ʽ

/////////////////////////////////////////������cmd_id��Ӧ�����ݸ�ʽ
//����״̬���ݣ�cmd_id == 0x0001
typedef __packed struct {	//�ֽڶ��룬https://blog.csdn.net/weibo1230123/article/details/84106028
    uint8_t game_type : 4;	//1�ǻ��״�ʦ����2�ǻ��״�ʦ��������3���˹�������ս��
    uint8_t game_progress : 4;	//0��δ��ʼ������1��׼���׶Σ�2���Լ�׶Σ�3��5S����ʱ��4�Ƕ�ս�У�5�Ǳ���������
    uint16_t stage_remain_time; 	//����ʣ��ʱ��
	uint64_t SyncTimeStamp;		//�����˽��յ���ָ��ľ�ȷ Unix ʱ��
}ext_game_state_t;

//���������cmd_id == 0x0002
typedef __packed struct { 
uint8_t winner; 	//0 ƽ�� 1 �췽ʤ�� 2 ����ʤ��
} ext_game_result_t;

//������Ѫ�����ݣ�cmd_id == 0x0003
typedef __packed struct {
uint16_t red_1_robot_HP;
uint16_t red_2_robot_HP;
uint16_t red_3_robot_HP;
uint16_t red_4_robot_HP;
uint16_t red_5_robot_HP;
uint16_t red_7_robot_HP;
uint16_t red_outpost_HP;
uint16_t red_base_HP;
uint16_t blue_1_robot_HP;
uint16_t blue_2_robot_HP;
uint16_t blue_3_robot_HP;
uint16_t blue_4_robot_HP;
uint16_t blue_5_robot_HP;
uint16_t blue_7_robot_HP;
uint16_t blue_outpost_HP;
uint16_t blue_base_HP;
} ext_game_robot_HP_t;

////���ڷ���״̬��cmd_id == 0x0004
//typedef __packed struct
//{
// uint8_t dart_belong; //1�Ǻ췽���ڣ�2����������
// uint16_t stage_remaining_time; //����ʱ��ʣ�����ʱ��
//}ext_dart_status_t;


//�˹�������ս���ӳ���ͷ���״̬��cmd_id == 0x0005
typedef __packed struct
{
	uint8_t F1_zone_status:1;
	uint8_t F1_zone_buff_debuff_status:3;
	uint8_t F2_zone_status:1;
	uint8_t F2_zone_buff_debuff_status:3; 
	uint8_t F3_zone_status:1;
	uint8_t F3_zone_buff_debuff_status:3; 
	uint8_t F4_zone_status:1;
	uint8_t F4_zone_buff_debuff_status:3; 
	uint8_t F5_zone_status:1;
	uint8_t F5_zone_buff_debuff_status:3; 
	uint8_t F6_zone_status:1;
	uint8_t F6_zone_buff_debuff_status:3;
	uint16_t red1_bullet_left;
	uint16_t red2_bullet_left;
	uint16_t blue1_bullet_left;
	uint16_t blue2_bullet_left;
}ext_ICRA_buff_debuff_zone_status_t;

//�����¼���cmd_id == 0x0101
typedef __packed struct { 
uint32_t event_type; 
} ext_event_data_t;


//����վ������cmd_id == 0x0102
typedef __packed struct { 
    uint8_t supply_projectile_id; 
    uint8_t supply_robot_id; 
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num; 
} ext_supply_projectile_action_t;


//���󲹵���cmd_id == 0x0103����RM�Կ�����δ���ţ�
//typedef __packed struct { 
//    uint8_t supply_projectile_id; 
//    uint8_t supply_robot_id;
//    uint8_t supply_num; 
//} ext_supply_projectile_booking_t;

//������Ϣ��cmd_id == 0x0104
typedef __packed struct {
    uint8_t level;
    uint8_t foul_robot_id ;
} referee_warning_t;


//���ڷ���ڵ���ʱ��cmd_id == 0x0105
typedef __packed struct
{
 uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;

//������״̬��cmd_id == 0x0201
typedef __packed struct
{
 uint8_t robot_id;
 uint8_t robot_level;
 uint16_t remain_HP;
 uint16_t max_HP;
 uint16_t shooter_id1_17mm_cooling_rate;
 uint16_t shooter_id1_17mm_cooling_limit;
 uint16_t shooter_id1_17mm_speed_limit;
 uint16_t shooter_id2_17mm_cooling_rate;
 uint16_t shooter_id2_17mm_cooling_limit;
 uint16_t shooter_id2_17mm_speed_limit;
 uint16_t shooter_id1_42mm_cooling_rate;
 uint16_t shooter_id1_42mm_cooling_limit;
 uint16_t shooter_id1_42mm_speed_limit;
 uint16_t chassis_power_limit;
 uint8_t mains_power_gimbal_output : 1;
 uint8_t mains_power_chassis_output : 1;
 uint8_t mains_power_shooter_output : 1;
} ext_game_robot_status_t;

//ʵʱ����������cmd_id == 0x0202
typedef __packed struct
{
 uint16_t chassis_volt; 
 uint16_t chassis_current; 
 float chassis_power; 
 uint16_t chassis_power_buffer; 
 uint16_t shooter_id1_17mm_cooling_heat;
 uint16_t shooter_id2_17mm_cooling_heat;
 uint16_t shooter_id1_42mm_cooling_heat;
} ext_power_heat_data_t;

//������λ�ã�cmd_id == 0x0203
typedef __packed struct {
    float x; 
    float y; 
    float z; 
    float yaw; 
} ext_game_robot_pos_t;

//���������棬cmd_id == 0x0204
typedef __packed struct { 
    uint8_t power_rune_buff; 
}ext_buff_t;

//���л���������״̬��cmd_id == 0x0205
typedef __packed struct
{
 uint8_t attack_time;
} ext_aerial_robot_energy_t;

//�˺����ݣ�cmd_id == 0x0206
typedef __packed struct { 
    uint8_t armor_id : 4; 
    uint8_t hurt_type : 4; 
} ext_robot_hurt_t;

//������ݣ�cmd_id == 0x0207
typedef __packed struct {
    uint8_t bullet_type;
	uint8_t shooter_id;
    uint8_t bullet_freq; 
    float bullet_speed; 
} ext_shoot_data_t;

//ʣ���ӵ�����ֻ������˻����ڱ���cmd_id == 0x0208
typedef __packed struct
{
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm; 
	uint16_t coin_remaining_num;
} ext_bullet_remaining_t;

//������ RFID ״̬��0x0209������Ƶ�ʣ�1Hz�����ͷ�Χ����һ������
typedef __packed struct
{
 uint32_t rfid_status;
} ext_rfid_status_t;

//���ڻ����˿ͻ���ָ�����ݣ�0x020A������Ƶ�ʣ�10Hz�����ͷ�Χ����һ������
typedef __packed struct
{
 uint8_t dart_launch_opening_status;
 uint8_t dart_attack_target;
 uint16_t target_change_time;
 uint16_t operate_launch_cmd_time;
}ext_dart_client_cmd_t;
////////////////////////////////////////////////������cmd_id��Ӧ�����ݸ�ʽ

////////////////////////////////////////////////�����ǻ����˼佻������
//��Ӧ��CMD_IDΪROBOT_INTERACTIVE_ID= 0x0301    //�����˼佻�������ʹ���

typedef enum
{
	RedHero = 1,//�췽Ӣ��
	RedEngineer = 2,//�췽����
	RedInfantry1 = 3,//�췽����1
	RedInfantry2 = 4,//�췽����2
	RedInfantry3 = 5,//�췽����3
	RedAirplane = 6,//�췽���˻�
	RedSentry = 7,//�췽�ڱ�
	RedRadar = 9,//�췽�״�
	
	BlueHero = 101,//����Ӣ��
	BlueEngineer = 102,//��������
	BlueInfantry1 = 103,//��������1
	BlueInfantry2 = 104,//��������2
	BlueInfantry3 = 105,//��������3
	BlueAirplane = 106,//�������˻�
	BlueSentry = 107,//�����ڱ�
	BlueRadar = 109,//�����״�
}Robots_ID_e;

typedef enum
{
	RedHeroOperator = 0x0101,//�췽Ӣ��
	RedEngineerOperator = 0x0102,//�췽����
	RedInfantry1Operator = 0x0103,//�췽����1
	RedInfantry2Operator = 0x0104,//�췽����2
	RedInfantry3Operator = 0x0105,//�췽����3
	RedAirplaneOperator = 0x0106,//�췽���˻�
	//RedSentryOperator = 7,//�췽�ڱ�
	//RedRadarOperator = 8,//�췽�״�
	
	BlueHeroOperator = 0x0165,//����Ӣ��
	BlueEngineerOperator = 0x0166,//��������
	BlueInfantry1Operator = 0x0167,//��������1
	BlueInfantry2Operator = 0x0168,//��������2
	BlueInfantry3Operator = 0x0169,//��������3
	BlueAirplaneOperator = 0x016A,//�������˻�
	//BlueSentryOperator = 107,//�����ڱ�
	//BlueRadarOperator = 108,//�����״�
}Operators_ID_e;	//�����ֵ�ID


#define student_interactive_data_max_length	113		//���͵��������ݶ����Ϊ 113��
//�����˼佻������ͷ
typedef __packed struct
{
 uint16_t data_cmd_id;//���ݶε�����id��ע������֡��cmd_id���֣���ֵ�����ext_student_interactive_data_cmd_id_e;
 uint16_t sender_ID;
 uint16_t receiver_ID;
}ext_student_interactive_header_data_t;

//�����˼佻������ͷ��������������
typedef __packed struct
{
    ext_student_interactive_header_data_t interactive_header_data;
	uint8_t Data[student_interactive_data_max_length ];
}ext_student_interactive_all_data_t;

//���涨�����ݶ�����id��ö��
typedef enum
{
	RobotCommunications		=		0x0200,	//0x0200~0x02FF֮�䶼��Ϊ�Ǽ��������˻���ͨ��ͨ��
	ClientDeleteGraph		=		0x0100,	//�ڿͻ���ɾ��ͼ��
	ClientAddOneGraph		=		0x0101,	//�ڿͻ��˻���һ��ͼ��
	ClientAddTwoGraph		=		0x0102,	//�ڿͻ��˻�������ͼ��
	ClientAddFiveGraph		=		0x0103,	//�ڿͻ��˻������ͼ��
	ClientAddSevenGraph		=		0x0104,	//�ڿͻ��˻����߸�ͼ��
	ClientAddStringGraph	=		0x0110,	//�ڿͻ��˻����ַ�ͼ��
}ext_student_interactive_data_cmd_id_e;


typedef __packed struct
{
	uint8_t operate_tpye; 
	uint8_t layer; 
} ext_client_custom_graphic_delete_t;
//�ͻ���ɾ��ͼ��

typedef __packed struct
{ 
	uint8_t graphic_name[3]; //ͼ������
	uint32_t operate_tpye:3; //ͼ�������0�ǿղ�����1������ͼ�Σ�2���޸�ͼ�Σ�3��ɾ��ͼ��
	uint32_t graphic_tpye:3; //ͼ�����ͣ�0��ֱ�ߣ�1�Ǿ��Σ�2����Բ��3����Բ��4��Բ����5�Ǹ�������6����������7���ַ�
	uint32_t layer:4; //ͼ����
	uint32_t color:4; //��ɫ
	uint32_t start_angle:9;//��ʼ�Ƕ�
	uint32_t end_angle:9;//��ֹ�Ƕ�
	uint32_t width:10; //���
	uint32_t start_x:11; //���x����,[0,1920].���½�Ϊ��0,0������Ϊ��960,540��
	uint32_t start_y:11; //���y����,0-1080
	uint32_t radius:10; //�뾶
	uint32_t end_x:11; //��ֹx����
	uint32_t end_y:11; //��ֹy����
}graphic_data_struct_t;
//ͼ������

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;
//�ͻ��˻���һ��ͼ��

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;
////�ͻ��˻��ƶ���ͼ��

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;
////�ͻ��˻������ͼ��

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[7];
} ext_client_custom_graphic_seven_t;
////�ͻ��˻����߸�ͼ��

typedef __packed struct
{
graphic_data_struct_t grapic_data_struct;
uint8_t data[30];
} ext_client_custom_character_t;
//�ͻ��˻����ַ�
////////////////////////////////////////////////�����ǻ����˼佻������
//�������Զ�����������������
//SELF_CONTROL_INTERACTIVE_ID
#define self_control_interactive_data_max_length	30		//���͵��������ݶ����Ϊ 30

//�Զ����������cmd_id == 0x0302
typedef __packed struct
{
	uint8_t Data[self_control_interactive_data_max_length];
}self_control_interactive_all_data_t;

//������С��ͼ�������ݣ�cmd_id == 0x0303
typedef __packed struct
{
	float target_position_x;
	float target_position_y;
	float target_position_z;
	uint8_t commd_keyboard;
	uint16_t target_robot_ID;
}ext_robot_command_t;//�ͻ����·�

typedef __packed struct
{
	uint16_t target_robot_ID;
	float target_position_x;
	float target_position_y;
} ext_client_map_command_t;//�ͻ��˽���

//�����ǿͻ����·���������Ϣ��cmd_id == 0x0304
typedef __packed struct
{
	int16_t mouse_x;
	int16_t mouse_y;
	int16_t mouse_z;
	int8_t left_button_down;
	int8_t right_button_down;
	uint16_t keyboard_value;
	uint16_t reserved;
}key_and_mouse_t;

///////////////////////////////////////////////////////////////////////////���Ͻṹ���Ѿ��ѹٷ������������ݶ�����ϣ�����Ϊ�����������ṹ��

typedef struct
{
    ext_game_state_t                gameState;//����״̬��Ϣ
    ext_game_result_t               gameResult;
    ext_game_robot_HP_t             robotHP;
	ext_ICRA_buff_debuff_zone_status_t 	BuffDebuffStatus;	//�˹�������ս���ӳ���ͷ���״̬
    ext_event_data_t                fieldEvent;//�����¼�
    ext_supply_projectile_action_t  supplyAction;//����վ����
    referee_warning_t               warning;//������Ϣ
	ext_dart_remaining_time_t		DartRemainTime;//���ڷ���ڵ���ʱ
    ext_game_robot_status_t         robotState;//������״̬
    ext_power_heat_data_t           powerHeat;//ʵʱ��������
    ext_game_robot_pos_t            robotPosition;//������λ��
    ext_buff_t                 robotBUFF;//����������
    ext_aerial_robot_energy_t       droneEnergy;////���л���������״̬
    ext_robot_hurt_t                robotHurt;//�˺�����
    ext_shoot_data_t                robotShoot;//�������
    ext_bullet_remaining_t          bulletRemaining;//ʣ���ӵ�����ֻ������˻����ڱ�
	ext_rfid_status_t				rfid_status;//������ RFID ״̬
	ext_dart_client_cmd_t			DartClientCmd;////���ڻ����˿ͻ���ָ������
	ext_student_interactive_all_data_t student_interactive_all_data;//�����˼�ѧ����������
	self_control_interactive_all_data_t	self_control_interactive_all_data;//�Զ�����������������
	ext_robot_command_t				ext_robot_command;//С��ͼ��������
	key_and_mouse_t					key_and_mouse;//���ͼ�������
} receive_judge_t;
//������õ����ݴ��ڴ˽ṹ����

#define Judge_RecDataBuffDepth	200		//���ջ���������ͨ����ȣ�
#define Judge_TxDataBuffDepth	200		//DMA���ͻ�����

typedef struct
{
	uint8_t *WhichBuffToDMA;	//����DMA����һ��BUFF���������
	uint8_t *WhichBuffToCPU;	//����CPU���Դ����Ǹ�BUFF��������
	uint8_t Buff_0[Judge_RecDataBuffDepth + 1];//���һ���ֽڷ�'\0'
	uint8_t Buff_1[Judge_RecDataBuffDepth + 1];
}Rec_DataDoubleBuff_t;//DMA���ջ������ṹ�壬

typedef struct
{
	uint8_t *WhichBuffToDMA;	//����DMA����һ��BUFF���������
	uint8_t *WhichBuffToCPU;	//����CPU���Դ����Ǹ�BUFF��������
	uint8_t Buff_0[Judge_TxDataBuffDepth + 1];//���һ���ֽڷ�'\0'
	uint8_t Buff_1[Judge_TxDataBuffDepth + 1];
	uint16_t HowLongWillSend_Buff0;
	uint16_t HowLongWillSend_Buff1;
	uint16_t NowDMASendIng;//
}Judge_TxDataBuff_t;


typedef struct
{
    uint32_t   gameState;//����״̬��Ϣ
    uint32_t   gameResult;
    uint32_t   robotHP;
	uint32_t   DartStatus;//���ڷ���״̬
	uint32_t   BuffDebuffStatus;	//�˹�������ս���ӳ���ͷ���״̬
    uint32_t   fieldEvent;//�����¼�
    uint32_t   supplyAction;//����վ����
    uint32_t   warning;//������Ϣ
	uint32_t   DartRemainTime;//���ڷ���ڵ���ʱ
    uint32_t   robotState;//������״̬
    uint32_t   powerHeat;//ʵʱ��������
    uint32_t   robotPosition;//������λ��
    uint32_t   robotBUFF;//����������
    uint32_t   droneEnergy;////���л���������״̬
    uint32_t   robotHurt;//�˺�����
    uint32_t   robotShoot;//�������
    uint32_t   bulletRemaining;//ʣ���ӵ�����ֻ������˻����ڱ�
	uint32_t   rfid_status;//������ RFID ״̬
	uint32_t   DartClientCmd;////���ڻ����˿ͻ���ָ������
	uint32_t   student_interactive_all_data;////�����˼�ѧ����������
	uint32_t	self_control_interactive_all_data;//�Զ�����������������
	uint32_t	ext_robot_command;//С��ͼ��������
	uint32_t	key_and_mouse;//���ͼ�������
}Judge_UndateFlag_t;


typedef enum
{
	Line = 0,//ֱ��
	Rectangle = 1,//����
	Circle = 2,//��Բ
	Ellipse = 3,//��Բ
	Arc = 4,//Բ��
	GraphFloat = 5,//������
	GraphInt = 6,//����
	GraphChar = 7,//�ַ�
}graphic_graphic_tpye_e;//ͼ������ö��
typedef enum
{
	RedBlue = 0 ,//����ɫ
	Yellow = 1,//��ɫ
	Green = 2,//��ɫ
	Orange = 3,//��ɫ
	Purplish = 4,//�Ϻ�ɫ
	Pink = 5,//��ɫ
	Cyan = 6,//��ɫ
	Black = 7,//��ɫ
	White = 8,//��ɫ
}graphic_color_tpye_e;//ͼ����ɫö��

//����ͨ���о�����Ҫ�õ�ö�����ͣ�������Ϊö����ռ�ռ��С����������
//��������ö��ȷʵ����
typedef enum
{
	DoNothing = 0,
	AddGraph = 1,
	ReviseGraph = 2,
	DelGraph = 3,
	
}graphic_operate_tpye_e;//ͼ�β�������ö��



#pragma pack()

/////////////////////////////////////////////////////////////////������2021��5��8���¸ĵ�




#endif







