#include "init_task.h"
#include "tim_task.h"
#include "FreeRTOS.H"
#include "task.h"
#include "bsp_init.h"

//------------------------------------------------------------
//任务列表
//------------------------------------------------------------


////命令任务
#define CMD_TASK_PRIO	2			//任务优先级
#define CMD_STK_SIZE	256		//任务堆栈大小
#define CMD_TASK_PERIOD 2			//任务运行周期ms
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
#define CONTROL_STK_SIZE	256			//任务堆栈大小
#define CONTROL_TASK_PERIOD 1			//任务运行周期ms
TaskHandle_t Control_Task_Handler;		//任务句柄
void Control_Task(void*p_arg);			//任务函数

//计时任务
#define TIM_TASK_PRIO	2			//任务优先级
#define TIM_STK_SIZE	512			//任务堆栈大小
#define TIM_TASK_PERIOD 20		//任务运行周期ms
TaskHandle_t TIM_Task_Handler;		//任务句柄
void TIM_Task(void*p_arg);			//任务函数

//裁判系统消息更新任务
#define JUDGE_TASK_PRIO	2			//任务优先级
#define JUDGE_STK_SIZE	1024	 //任务堆栈大小
#define JUDGE_TASK_PERIOD 10  	//任务运行周期ms,与裁判系统适配，稍微大些好
TaskHandle_t Judge_Task_Handler;		//任务句柄
void Judge_Task(void*p_arg);			//任务函数

//裁判系统画图任务
#define GRAPH_TASK_PRIO	2			//任务优先级
#define GRAPH_STK_SIZE	512	 //任务堆栈大小
#define GRAPH_TASK_PERIOD 1  	//任务运行周期ms,与裁判系统适配，稍微大些好
TaskHandle_t Graph_Task_Handler;		//任务句柄
void Graph_Task(void*p_arg);			//任务函数
//------------------------------------------------------------
//任务
//------------------------------------------------------------

/**	
*@brief	任务初始化函数
*/
void Task_Init(void)
{
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
		
	xTaskCreate((TaskFunction_t	)TIM_Task,
			(const char*	)"TIM_Task",
			(uint16_t		)TIM_STK_SIZE,
			(void*			)NULL,
			(UBaseType_t	)TIM_TASK_PRIO,
			(TaskHandle_t*	)&TIM_Task_Handler);	
			
			xTaskCreate((TaskFunction_t	)Judge_Task,
			(const char*	)"Judge_Task",
			(uint16_t		)JUDGE_STK_SIZE,
			(void*			)NULL,
			(UBaseType_t	)JUDGE_TASK_PERIOD,
			(TaskHandle_t*	)&Judge_Task_Handler);		
			
	xTaskCreate((TaskFunction_t	)Graph_Task,
			(const char*	)"Graph_Task",
			(uint16_t		)GRAPH_STK_SIZE,
			(void*			)NULL,
			(UBaseType_t	)GRAPH_TASK_PERIOD,
			(TaskHandle_t*	)&Graph_Task_Handler);			
		
	taskEXIT_CRITICAL();//退出临界区
}

/**	
*@brief	命令任务
*/
void CMD_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
//		RescueTest();
		
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
		
		SendMotorCurrent();	
		
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

/**	
*@brief	TIM定时任务,20ms为一周期
*/
void TIM_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
		printf("hello World\r\n");
	  	
		vTaskDelayUntil(&currentTime, TIM_TASK_PERIOD/portTICK_RATE_MS);  //任务周期不为20ms
	}
}

/**	
*@brief	画图系统任务
*/
void Judge_Task(void*p_arg)
{
	portTickType currentTime;
	
	//Draw_DmaDoubleBuffTest();
	
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
		
		vTaskDelayUntil(&currentTime, JUDGE_TASK_PERIOD/portTICK_RATE_MS);
	}
	

}

/**	
*@brief	裁判系统任务
*/
void Graph_Task(void*p_arg)
{
	portTickType currentTime;
	
	//	Draw_DmaDoubleBuffTest();
	
	while(1)
	{
		currentTime = xTaskGetTickCount();	//获取当前系统时间
		
		Judge_LoopPer1MS();
		
		vTaskDelayUntil(&currentTime, GRAPH_TASK_PERIOD/portTICK_RATE_MS);
		
	}
}


