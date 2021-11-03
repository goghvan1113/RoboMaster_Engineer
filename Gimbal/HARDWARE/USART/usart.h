#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "sys.h" 
/*

 PA9,USART_TX,,,,,,,
 PA10,USART_RX,,,,,,,
 �Ѿ�ʹ��DMA2��������7��ͨ��4��

*/



#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define USE_USART1_PRINTF 1



//����봮���жϽ��գ��벻Ҫע�����º궨��
void Usart1PrintInit(void);
void Usart1DmaLoop(void);
#endif


