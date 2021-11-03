#include "tim.h"
#include "usart.h"


void TIM5_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM5ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period =1000; 	//�Զ���װ��ֵ��1ms
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;  //��ʱ����Ƶ,1MHZ,��һ����1us
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM5
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��5�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //��ʱ��5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

uint32_t Timer5Flag=0;//ÿ1ms��һ���жϣ���ֵ+1��
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET)
	{//����ж�
		++ Timer5Flag;
		Usart1DmaLoop();
			
		if(Timer5Flag == 100)
		{
			Timer5Flag = 0;         			
		}  
	}	 
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}



