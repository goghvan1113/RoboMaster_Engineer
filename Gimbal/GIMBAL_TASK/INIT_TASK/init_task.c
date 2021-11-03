#include "init_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "can_task.h"


//------------------------------------------------------------
//任务列表
//------------------------------------------------------------


////命令任务
#define CMD_TASK_PRIO	2			//任务优先级
#define CMD_STK_SIZE	128		//任务堆栈大小
#define CMD_TASK_PERIOD 7			//任务运行周期ms
TaskHandle_t CMD_Task_Handler;		//任务句柄
void CMD_Task(void*p_arg);			//任务函数
//CAN任务
#define CAN_TASK_PRIO	2			//任务优先级
#define CAN_STK_SIZE	128			//任务堆栈大小
#define CAN_TASK_PERIOD 1			//任务运行周期ms
TaskHandle_t CAN_Task_Handler;		//任务句柄
void CAN_Task(void*p_arg);			//任务函数
//控制任务
#define CONTROL_TASK_PRIO	2			//任务优先级
#define CONTROL_STK_SIZE	1024		//任务堆栈大小
#define CONTROL_TASK_PERIOD 1			//任务运行周期ms
TaskHandle_t Control_Task_Handler;		//任务句柄
void Control_Task(void*p_arg);			//任务函数

//------------------------------------------------------------
//任务
//------------------------------------------------------------

/**	
*@brief	任务初始化函数
*/
void Task_Init(void){
	taskENTER_CRITICAL();//进入临界区
			
		xTaskCreate((TaskFunction_t	)CMD_Task,
				(const char*	)"CMD_Task",
				(uint16_t		)CMD_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)CMD_TASK_PRIO,
				(TaskHandle_t*	)&CMD_Task_Handler);
		
	xTaskCreate((TaskFunction_t	)CAN_Task,
				(const char*	)"CAN_Task",
				(uint16_t		)CAN_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)CAN_TASK_PRIO,
				(TaskHandle_t*	)&CAN_Task_Handler);
				
		xTaskCreate((TaskFunction_t	)Control_Task,
				(const char*	)"Control_Task",
				(uint16_t		)CONTROL_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)CONTROL_TASK_PRIO,
				(TaskHandle_t*	)&Control_Task_Handler);
				
	taskEXIT_CRITICAL();//退出临界区
}

/**	
*@brief	命令任务(遥控器)
*/
void CMD_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
//		RcCmdPrc();
		
		vTaskDelayUntil(&currentTime, CMD_TASK_PERIOD/portTICK_RATE_MS);
	}
}
/**	
*@brief	CAN通信处理任务
*/
void CAN_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
		SendMotorCurrent();                 //发送电流
		
		vTaskDelayUntil(&currentTime, CAN_TASK_PERIOD/portTICK_RATE_MS);
	}
}
/**	
*@brief	控制任务
*/
void Control_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
//		ControlPrc();

		vTaskDelayUntil(&currentTime, CONTROL_TASK_PERIOD/portTICK_RATE_MS);
	}
}



