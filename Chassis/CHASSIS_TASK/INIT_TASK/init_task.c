#include "init_task.h"
#include "tim_task.h"
#include "FreeRTOS.H"
#include "task.h"
#include "bsp_init.h"

//------------------------------------------------------------
//�����б�
//------------------------------------------------------------


////��������
#define CMD_TASK_PRIO	2			//�������ȼ�
#define CMD_STK_SIZE	256		//�����ջ��С
#define CMD_TASK_PERIOD 2			//������������ms
TaskHandle_t CMD_Task_Handler;		//������
void CMD_Task(void*p_arg);			//������

//CAN����
#define CAN_TASK_PRIO	2			//�������ȼ�
#define CAN_STK_SIZE	128			//�����ջ��С
#define CAN_TASK_PERIOD 1			//������������ms
TaskHandle_t CAN_Task_Handler;		//������
void CAN_Task(void*p_arg);			//������

//��������
#define CONTROL_TASK_PRIO	2			//�������ȼ�
#define CONTROL_STK_SIZE	256			//�����ջ��С
#define CONTROL_TASK_PERIOD 1			//������������ms
TaskHandle_t Control_Task_Handler;		//������
void Control_Task(void*p_arg);			//������

//��ʱ����
#define TIM_TASK_PRIO	2			//�������ȼ�
#define TIM_STK_SIZE	512			//�����ջ��С
#define TIM_TASK_PERIOD 20		//������������ms
TaskHandle_t TIM_Task_Handler;		//������
void TIM_Task(void*p_arg);			//������

//����ϵͳ��Ϣ��������
#define JUDGE_TASK_PRIO	2			//�������ȼ�
#define JUDGE_STK_SIZE	1024	 //�����ջ��С
#define JUDGE_TASK_PERIOD 10  	//������������ms,�����ϵͳ���䣬��΢��Щ��
TaskHandle_t Judge_Task_Handler;		//������
void Judge_Task(void*p_arg);			//������

//����ϵͳ��ͼ����
#define GRAPH_TASK_PRIO	2			//�������ȼ�
#define GRAPH_STK_SIZE	512	 //�����ջ��С
#define GRAPH_TASK_PERIOD 1  	//������������ms,�����ϵͳ���䣬��΢��Щ��
TaskHandle_t Graph_Task_Handler;		//������
void Graph_Task(void*p_arg);			//������
//------------------------------------------------------------
//����
//------------------------------------------------------------

/**	
*@brief	�����ʼ������
*/
void Task_Init(void)
{
	taskENTER_CRITICAL();//�����ٽ���
			
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
		
	taskEXIT_CRITICAL();//�˳��ٽ���
}

/**	
*@brief	��������
*/
void CMD_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
//		RescueTest();
		
		vTaskDelayUntil(&currentTime, CMD_TASK_PERIOD/portTICK_RATE_MS);
	}
}
/**	
*@brief	CANͨ�Ŵ�������
*/
void CAN_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
		SendMotorCurrent();	
		
		vTaskDelayUntil(&currentTime, CAN_TASK_PERIOD/portTICK_RATE_MS);
	}
}
/**	
*@brief	��������
*/
void Control_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
//		ControlPrc();
		
		vTaskDelayUntil(&currentTime, CONTROL_TASK_PERIOD/portTICK_RATE_MS);
	}
}

/**	
*@brief	TIM��ʱ����,20msΪһ����
*/
void TIM_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
		printf("hello World\r\n");
	  	
		vTaskDelayUntil(&currentTime, TIM_TASK_PERIOD/portTICK_RATE_MS);  //�������ڲ�Ϊ20ms
	}
}

/**	
*@brief	��ͼϵͳ����
*/
void Judge_Task(void*p_arg)
{
	portTickType currentTime;
	
	//Draw_DmaDoubleBuffTest();
	
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
		
		vTaskDelayUntil(&currentTime, JUDGE_TASK_PERIOD/portTICK_RATE_MS);
	}
	

}

/**	
*@brief	����ϵͳ����
*/
void Graph_Task(void*p_arg)
{
	portTickType currentTime;
	
	//	Draw_DmaDoubleBuffTest();
	
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
		Judge_LoopPer1MS();
		
		vTaskDelayUntil(&currentTime, GRAPH_TASK_PERIOD/portTICK_RATE_MS);
		
	}
}


