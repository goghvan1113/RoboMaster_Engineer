#include "init_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "can_task.h"


//------------------------------------------------------------
//�����б�
//------------------------------------------------------------


////��������
#define CMD_TASK_PRIO	2			//�������ȼ�
#define CMD_STK_SIZE	128		//�����ջ��С
#define CMD_TASK_PERIOD 7			//������������ms
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
#define CONTROL_STK_SIZE	1024		//�����ջ��С
#define CONTROL_TASK_PERIOD 1			//������������ms
TaskHandle_t Control_Task_Handler;		//������
void Control_Task(void*p_arg);			//������

//------------------------------------------------------------
//����
//------------------------------------------------------------

/**	
*@brief	�����ʼ������
*/
void Task_Init(void){
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
				
	taskEXIT_CRITICAL();//�˳��ٽ���
}

/**	
*@brief	��������(ң����)
*/
void CMD_Task(void*p_arg)
{
	portTickType currentTime;
	while(1)
	{
		currentTime = xTaskGetTickCount();	//��ȡ��ǰϵͳʱ��
		
//		RcCmdPrc();
		
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
		
		SendMotorCurrent();                 //���͵���
		
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



