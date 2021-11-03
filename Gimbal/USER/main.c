#include "stm32f4xx.h"     //STM32F4ϵ�еײ�ͷ�ļ�
#include "sys.h"           //��������IO�ڵĶ���
#include "delay.h"         //��ʱϵͳ��Դ�ľ�����ʱ��������

#include "FreeRTOS.H"      
#include "task.h"          //FreeRTOS����ϵͳͷ�ļ�

#include "bsp_init.h"      //����
#include "init_task.h"     //�����ʼ��




int main(void){
	
	BspInit();   
	Task_Init();
	vTaskStartScheduler();
	
	while(1)
	{
		//�������򲻻����е���
		RedLED_Toggle();
	}    
	
}

