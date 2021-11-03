#include "stm32f4xx.h"     //STM32F4系列底层头文件
#include "sys.h"           //操作单个IO口的定义
#include "delay.h"         //耗时系统资源的绝对延时函数定义

#include "FreeRTOS.H"      
#include "task.h"          //FreeRTOS操作系统头文件

#include "bsp_init.h"      //外设
#include "init_task.h"     //任务初始化




int main(void){
	
	BspInit();   
	Task_Init();
	vTaskStartScheduler();
	
	while(1)
	{
		//正常程序不会运行到这
		RedLED_Toggle();
	}    
	
}

