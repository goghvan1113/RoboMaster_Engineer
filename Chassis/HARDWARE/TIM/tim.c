#include "tim.h"
#include "usart.h"


void TIM5_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM5时钟
	
	TIM_TimeBaseInitStructure.TIM_Period =1000; 	//自动重装载值，1ms
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;  //定时器分频,1MHZ,计一个数1us
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM5
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器5更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

uint32_t Timer5Flag=0;//每1ms进一次中断，该值+1，
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET)
	{//溢出中断
		++ Timer5Flag;
		Usart1DmaLoop();
			
		if(Timer5Flag == 100)
		{
			Timer5Flag = 0;         			
		}  
	}	 
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}



