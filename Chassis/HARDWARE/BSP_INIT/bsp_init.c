#include "bsp_init.h"

//各模块的初始化程序
void BspInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  // NVIC_PriorityGroup_4
	delay_init(168);
	Usart1PrintInit();               // 串口1DMA打印初始化,用于调试时发送信息
	TIM5_Init();                     // 1ms定时器初始化 
	CAN1_Init();                     // CAN1电机通信初始化
	CAN2_Init();                     // CAN2云台通信初始化
	CAN_Device_Init();               // 配置底盘电机和CAN总线
	
	ChassisMotorRun_Init();          // 底盘运动电机初始化
	MineMotor_Init();                // 操作矿石电机初始化，包括矿井盘和旋转矿石      
}

