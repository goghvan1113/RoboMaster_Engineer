#include "led.h" 
#include "delay.h"

//PC0�̵ƣ�PC1���
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  GPIO_SetBits(GPIOC,GPIO_Pin_0 | GPIO_Pin_1);

}

//��ɫLED��˸����һ�����ڳ�����Ժ�ָʾ
void GreenLED_Toggle(void)
{
	GreenLED_ON;
	delay_ms(500);
	GreenLED_OFF;
	delay_ms(500);
}

//��ɫLED��˸����,���ڴ�����ʾ
void RedLED_Toggle(void)
{
	RedLED_ON;
	delay_ms(500);
	RedLED_OFF;
	delay_ms(500);
}
