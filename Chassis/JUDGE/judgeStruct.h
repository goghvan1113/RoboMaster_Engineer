#ifndef __JUDGESTRUCT_H__
#define __JUDGESTRUCT_H__

#include "stm32f4xx.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"


#define HEADER_LEN 5
#define CMD_LEN 2
#define CRC_LEN 2
#define PROTOCAL_FRAME_MAX_SIZE 128		//整个交互数据的包总共长最大为 128 个字节
#define FrameHeaderSOF	0xA5


/////////////////////////////////////////////////////////下面是从新写的裁判系统拷贝过来的


/************************************
*	裁判系统，汪晨晨
*	最后更新时间：2021年5月8日
*************************************/

//注意：注意：一定要加结构体的对齐，https://zhidao.baidu.com/question/418245481.html
//https://www.cnblogs.com/zhaoyl/archive/2012/04/21/2461077.html

#pragma pack(1)

typedef struct {
    uint8_t 	SOF;			//数据帧起始字节，固定值为0xA5;
    uint16_t    DataLength;		//数据帧内Data长度;
    uint8_t     Seq;			//包序号;
    uint8_t     CRC8;			//帧头CRC8;
}frame_header_t;//一个完整的通信帧里面的帧头详细定义

typedef enum
{
    GAME_STATE_ID       = 0x0001,   //比赛状态（1Hz）
    GAME_RESUIT_ID       = 0x0002,   //比赛结果
    ROBOT_HP_ID         = 0x0003,   //机器人血量数据（1Hz）
	//DART_FIRE_STATE		= 0x0004,	//飞镖发射状态		//说明，2021年协议V1.2把该命令码去掉了
	GAIN_AND_PUNISHMENT_STATE	= 0x0005,	//人工智能挑战赛加成与惩罚区状态，1HZ
    FIELD_EVENT_ID      = 0x0101,   //场地事件，1HZ
    SUPPLY_ACTION_ID    = 0x0102,   //补给站动作标识
    //REQUEST_BULLET_ID   = 0x0103,   //请求补弹（RM对抗赛尚未开放）
    JUDGE_WARNING_ID    = 0x0104,   //裁判警告数据
	DART_FIRE_COUNTDOWN	= 0x0105,	//飞镖发射口倒计时，1HZ发送
    ROBOT_STATE_ID      = 0x0201,   //机器人状态（10Hz）
    REALTIME_POWER_ID   = 0x0202,   //实时功率热量（50Hz）
    ROBOT_POSITION_ID   = 0x0203,   //机器人位置（10Hz）
    ROBOT_BUFF_ID       = 0x0204,   //机器人增益
    DRONE_POWER_ID      = 0x0205,   //空中机器人能量状态数据，10HZ，只有空中机器人主控发送
    ROBOT_HURT_ID       = 0x0206,   //伤害数据
    ROBOT_SHOOT_ID      = 0x0207,   //射击数据
    SURPLUS_BULLET_ID   = 0X0208,   //剩余子弹数（哨兵和空中机器人）
	ROBOT_RFID_STATE	= 0x0209,	//机器人RFID状态，1HZ周期发送
	ROBOT_OPERATOR_CMD	= 0x020A,	//飞镖机器人客户端指令数据，10HZ
    ROBOT_INTERACTIVE_ID= 0x0301,    //机器人间交互，发送触发
	SELF_CONTROL_INTERACTIVE_ID= 0x0302,	//自定义控制器交互数据
	ROBOT_COMMAND_ID	= 0x0303,	//客户端小地图交互数据
	KEY_AND_MOUSE_ID	= 0x0304,	//键鼠信息
	RADAR_SEND_MAP_ID	= 0x0305,	//小地图
} frame_cmd_id_e;
//frame_cmd_id_e;

typedef struct
{
	frame_header_t header;
	frame_cmd_id_e frame_cmd_id;
	uint8_t data[PROTOCAL_FRAME_MAX_SIZE];
	uint16_t frame_tail;
}JudgeFullFrame_t;
//一个完整的通信帧格式

/////////////////////////////////////////下面是cmd_id对应的数据格式
//比赛状态数据，cmd_id == 0x0001
typedef __packed struct {	//字节对齐，https://blog.csdn.net/weibo1230123/article/details/84106028
    uint8_t game_type : 4;	//1是机甲大师赛，2是机甲大师单项赛，3是人工智能挑战赛
    uint8_t game_progress : 4;	//0是未开始比赛，1是准备阶段，2是自检阶段，3是5S倒计时，4是对战中，5是比赛结算中
    uint16_t stage_remain_time; 	//比赛剩余时间
	uint64_t SyncTimeStamp;		//机器人接收到该指令的精确 Unix 时间
}ext_game_state_t;

//比赛结果，cmd_id == 0x0002
typedef __packed struct { 
uint8_t winner; 	//0 平局 1 红方胜利 2 蓝方胜利
} ext_game_result_t;

//机器人血量数据，cmd_id == 0x0003
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

////飞镖发射状态，cmd_id == 0x0004
//typedef __packed struct
//{
// uint8_t dart_belong; //1是红方飞镖，2是蓝方飞镖
// uint16_t stage_remaining_time; //发射时的剩余比赛时间
//}ext_dart_status_t;


//人工智能挑战赛加成与惩罚区状态，cmd_id == 0x0005
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

//场地事件，cmd_id == 0x0101
typedef __packed struct { 
uint32_t event_type; 
} ext_event_data_t;


//补给站动作，cmd_id == 0x0102
typedef __packed struct { 
    uint8_t supply_projectile_id; 
    uint8_t supply_robot_id; 
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num; 
} ext_supply_projectile_action_t;


//请求补弹，cmd_id == 0x0103，（RM对抗赛尚未开放）
//typedef __packed struct { 
//    uint8_t supply_projectile_id; 
//    uint8_t supply_robot_id;
//    uint8_t supply_num; 
//} ext_supply_projectile_booking_t;

//警告信息，cmd_id == 0x0104
typedef __packed struct {
    uint8_t level;
    uint8_t foul_robot_id ;
} referee_warning_t;


//飞镖发射口倒计时，cmd_id == 0x0105
typedef __packed struct
{
 uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;

//机器人状态，cmd_id == 0x0201
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

//实时功率热量，cmd_id == 0x0202
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

//机器人位置，cmd_id == 0x0203
typedef __packed struct {
    float x; 
    float y; 
    float z; 
    float yaw; 
} ext_game_robot_pos_t;

//机器人增益，cmd_id == 0x0204
typedef __packed struct { 
    uint8_t power_rune_buff; 
}ext_buff_t;

//空中机器人能量状态，cmd_id == 0x0205
typedef __packed struct
{
 uint8_t attack_time;
} ext_aerial_robot_energy_t;

//伤害数据，cmd_id == 0x0206
typedef __packed struct { 
    uint8_t armor_id : 4; 
    uint8_t hurt_type : 4; 
} ext_robot_hurt_t;

//射击数据，cmd_id == 0x0207
typedef __packed struct {
    uint8_t bullet_type;
	uint8_t shooter_id;
    uint8_t bullet_freq; 
    float bullet_speed; 
} ext_shoot_data_t;

//剩余子弹数，只针对无人机和哨兵，cmd_id == 0x0208
typedef __packed struct
{
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm; 
	uint16_t coin_remaining_num;
} ext_bullet_remaining_t;

//机器人 RFID 状态：0x0209。发送频率：1Hz，发送范围：单一机器人
typedef __packed struct
{
 uint32_t rfid_status;
} ext_rfid_status_t;

//飞镖机器人客户端指令数据：0x020A。发送频率：10Hz，发送范围：单一机器人
typedef __packed struct
{
 uint8_t dart_launch_opening_status;
 uint8_t dart_attack_target;
 uint16_t target_change_time;
 uint16_t operate_launch_cmd_time;
}ext_dart_client_cmd_t;
////////////////////////////////////////////////上面是cmd_id对应的数据格式

////////////////////////////////////////////////下面是机器人间交互数据
//对应的CMD_ID为ROBOT_INTERACTIVE_ID= 0x0301    //机器人间交互，发送触发

typedef enum
{
	RedHero = 1,//红方英雄
	RedEngineer = 2,//红方工程
	RedInfantry1 = 3,//红方步兵1
	RedInfantry2 = 4,//红方步兵2
	RedInfantry3 = 5,//红方步兵3
	RedAirplane = 6,//红方无人机
	RedSentry = 7,//红方哨兵
	RedRadar = 9,//红方雷达
	
	BlueHero = 101,//蓝方英雄
	BlueEngineer = 102,//蓝方工程
	BlueInfantry1 = 103,//蓝方步兵1
	BlueInfantry2 = 104,//蓝方步兵2
	BlueInfantry3 = 105,//蓝方步兵3
	BlueAirplane = 106,//蓝方无人机
	BlueSentry = 107,//蓝方哨兵
	BlueRadar = 109,//蓝方雷达
}Robots_ID_e;

typedef enum
{
	RedHeroOperator = 0x0101,//红方英雄
	RedEngineerOperator = 0x0102,//红方工程
	RedInfantry1Operator = 0x0103,//红方步兵1
	RedInfantry2Operator = 0x0104,//红方步兵2
	RedInfantry3Operator = 0x0105,//红方步兵3
	RedAirplaneOperator = 0x0106,//红方无人机
	//RedSentryOperator = 7,//红方哨兵
	//RedRadarOperator = 8,//红方雷达
	
	BlueHeroOperator = 0x0165,//蓝方英雄
	BlueEngineerOperator = 0x0166,//蓝方工程
	BlueInfantry1Operator = 0x0167,//蓝方步兵1
	BlueInfantry2Operator = 0x0168,//蓝方步兵2
	BlueInfantry3Operator = 0x0169,//蓝方步兵3
	BlueAirplaneOperator = 0x016A,//蓝方无人机
	//BlueSentryOperator = 107,//蓝方哨兵
	//BlueRadarOperator = 108,//蓝方雷达
}Operators_ID_e;	//操作手的ID


#define student_interactive_data_max_length	113		//发送的内容数据段最大为 113。
//机器人间交互，包头
typedef __packed struct
{
 uint16_t data_cmd_id;//数据段的内容id，注意与整帧的cmd_id区分，各值意义见ext_student_interactive_data_cmd_id_e;
 uint16_t sender_ID;
 uint16_t receiver_ID;
}ext_student_interactive_header_data_t;

//机器人间交互，包头及传过来的数据
typedef __packed struct
{
    ext_student_interactive_header_data_t interactive_header_data;
	uint8_t Data[student_interactive_data_max_length ];
}ext_student_interactive_all_data_t;

//下面定义数据段内容id的枚举
typedef enum
{
	RobotCommunications		=		0x0200,	//0x0200~0x02FF之间都认为是己方机器人互相通信通道
	ClientDeleteGraph		=		0x0100,	//在客户端删除图形
	ClientAddOneGraph		=		0x0101,	//在客户端绘制一个图形
	ClientAddTwoGraph		=		0x0102,	//在客户端绘制三个图形
	ClientAddFiveGraph		=		0x0103,	//在客户端绘制五个图形
	ClientAddSevenGraph		=		0x0104,	//在客户端绘制七个图形
	ClientAddStringGraph	=		0x0110,	//在客户端绘制字符图形
}ext_student_interactive_data_cmd_id_e;


typedef __packed struct
{
	uint8_t operate_tpye; 
	uint8_t layer; 
} ext_client_custom_graphic_delete_t;
//客户端删除图形

typedef __packed struct
{ 
	uint8_t graphic_name[3]; //图形名，
	uint32_t operate_tpye:3; //图像操作，0是空操作，1是增加图形，2是修改图形，3是删除图形
	uint32_t graphic_tpye:3; //图形类型，0是直线，1是矩形，2是整圆，3是椭圆，4是圆弧，5是浮点数，6是整型数，7是字符
	uint32_t layer:4; //图层数
	uint32_t color:4; //颜色
	uint32_t start_angle:9;//起始角度
	uint32_t end_angle:9;//终止角度
	uint32_t width:10; //宽度
	uint32_t start_x:11; //起点x坐标,[0,1920].左下角为（0,0）中央为（960,540）
	uint32_t start_y:11; //起点y坐标,0-1080
	uint32_t radius:10; //半径
	uint32_t end_x:11; //终止x坐标
	uint32_t end_y:11; //终止y坐标
}graphic_data_struct_t;
//图形数据

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;
//客户端绘制一个图形

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;
////客户端绘制二个图形

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;
////客户端绘制五个图形

typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[7];
} ext_client_custom_graphic_seven_t;
////客户端绘制七个图形

typedef __packed struct
{
graphic_data_struct_t grapic_data_struct;
uint8_t data[30];
} ext_client_custom_character_t;
//客户端绘制字符
////////////////////////////////////////////////上面是机器人间交互数据
//下面是自定义控制器命令交互数据
//SELF_CONTROL_INTERACTIVE_ID
#define self_control_interactive_data_max_length	30		//发送的内容数据段最大为 30

//自定义控制器，cmd_id == 0x0302
typedef __packed struct
{
	uint8_t Data[self_control_interactive_data_max_length];
}self_control_interactive_all_data_t;

//下面是小地图交互数据，cmd_id == 0x0303
typedef __packed struct
{
	float target_position_x;
	float target_position_y;
	float target_position_z;
	uint8_t commd_keyboard;
	uint16_t target_robot_ID;
}ext_robot_command_t;//客户端下发

typedef __packed struct
{
	uint16_t target_robot_ID;
	float target_position_x;
	float target_position_y;
} ext_client_map_command_t;//客户端接收

//下面是客户端下发鼠标键盘信息，cmd_id == 0x0304
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

///////////////////////////////////////////////////////////////////////////以上结构体已经把官方给的所有数据定义完毕，下面为方便操作定义结构体

typedef struct
{
    ext_game_state_t                gameState;//比赛状态信息
    ext_game_result_t               gameResult;
    ext_game_robot_HP_t             robotHP;
	ext_ICRA_buff_debuff_zone_status_t 	BuffDebuffStatus;	//人工智能挑战赛加成与惩罚区状态
    ext_event_data_t                fieldEvent;//场地事件
    ext_supply_projectile_action_t  supplyAction;//补给站动作
    referee_warning_t               warning;//警告信息
	ext_dart_remaining_time_t		DartRemainTime;//飞镖发射口倒计时
    ext_game_robot_status_t         robotState;//机器人状态
    ext_power_heat_data_t           powerHeat;//实时功率热量
    ext_game_robot_pos_t            robotPosition;//机器人位置
    ext_buff_t                 robotBUFF;//机器人增益
    ext_aerial_robot_energy_t       droneEnergy;////空中机器人能量状态
    ext_robot_hurt_t                robotHurt;//伤害数据
    ext_shoot_data_t                robotShoot;//射击数据
    ext_bullet_remaining_t          bulletRemaining;//剩余子弹数，只针对无人机和哨兵
	ext_rfid_status_t				rfid_status;//机器人 RFID 状态
	ext_dart_client_cmd_t			DartClientCmd;////飞镖机器人客户端指令数据
	ext_student_interactive_all_data_t student_interactive_all_data;//机器人间学生串口数据
	self_control_interactive_all_data_t	self_control_interactive_all_data;//自定义控制器命令交互数据
	ext_robot_command_t				ext_robot_command;//小地图交互数据
	key_and_mouse_t					key_and_mouse;//鼠标和键盘数据
} receive_judge_t;
//解包后获得的数据存在此结构体内

#define Judge_RecDataBuffDepth	200		//接收缓存区单个通道深度，
#define Judge_TxDataBuffDepth	200		//DMA发送缓存区

typedef struct
{
	uint8_t *WhichBuffToDMA;	//现在DMA往哪一个BUFF里面存数据
	uint8_t *WhichBuffToCPU;	//现在CPU可以处理那个BUFF里面数据
	uint8_t Buff_0[Judge_RecDataBuffDepth + 1];//最后一个字节放'\0'
	uint8_t Buff_1[Judge_RecDataBuffDepth + 1];
}Rec_DataDoubleBuff_t;//DMA接收缓存区结构体，

typedef struct
{
	uint8_t *WhichBuffToDMA;	//现在DMA往哪一个BUFF里面存数据
	uint8_t *WhichBuffToCPU;	//现在CPU可以处理那个BUFF里面数据
	uint8_t Buff_0[Judge_TxDataBuffDepth + 1];//最后一个字节放'\0'
	uint8_t Buff_1[Judge_TxDataBuffDepth + 1];
	uint16_t HowLongWillSend_Buff0;
	uint16_t HowLongWillSend_Buff1;
	uint16_t NowDMASendIng;//
}Judge_TxDataBuff_t;


typedef struct
{
    uint32_t   gameState;//比赛状态信息
    uint32_t   gameResult;
    uint32_t   robotHP;
	uint32_t   DartStatus;//飞镖发射状态
	uint32_t   BuffDebuffStatus;	//人工智能挑战赛加成与惩罚区状态
    uint32_t   fieldEvent;//场地事件
    uint32_t   supplyAction;//补给站动作
    uint32_t   warning;//警告信息
	uint32_t   DartRemainTime;//飞镖发射口倒计时
    uint32_t   robotState;//机器人状态
    uint32_t   powerHeat;//实时功率热量
    uint32_t   robotPosition;//机器人位置
    uint32_t   robotBUFF;//机器人增益
    uint32_t   droneEnergy;////空中机器人能量状态
    uint32_t   robotHurt;//伤害数据
    uint32_t   robotShoot;//射击数据
    uint32_t   bulletRemaining;//剩余子弹数，只针对无人机和哨兵
	uint32_t   rfid_status;//机器人 RFID 状态
	uint32_t   DartClientCmd;////飞镖机器人客户端指令数据
	uint32_t   student_interactive_all_data;////机器人间学生串口数据
	uint32_t	self_control_interactive_all_data;//自定义控制器命令交互数据
	uint32_t	ext_robot_command;//小地图交互数据
	uint32_t	key_and_mouse;//鼠标和键盘数据
}Judge_UndateFlag_t;


typedef enum
{
	Line = 0,//直线
	Rectangle = 1,//矩形
	Circle = 2,//整圆
	Ellipse = 3,//椭圆
	Arc = 4,//圆弧
	GraphFloat = 5,//浮点数
	GraphInt = 6,//整数
	GraphChar = 7,//字符
}graphic_graphic_tpye_e;//图形类型枚举
typedef enum
{
	RedBlue = 0 ,//红蓝色
	Yellow = 1,//黄色
	Green = 2,//绿色
	Orange = 3,//橙色
	Purplish = 4,//紫红色
	Pink = 5,//粉色
	Cyan = 6,//青色
	Black = 7,//黑色
	White = 8,//白色
}graphic_color_tpye_e;//图形颜色枚举

//串口通信中尽量不要用到枚举类型，以免因为枚举所占空间大小而发生歧义
//但这里用枚举确实方便
typedef enum
{
	DoNothing = 0,
	AddGraph = 1,
	ReviseGraph = 2,
	DelGraph = 3,
	
}graphic_operate_tpye_e;//图形操作类型枚举



#pragma pack()

/////////////////////////////////////////////////////////////////上面是2021年5月8日新改的




#endif







