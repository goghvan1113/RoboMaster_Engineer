#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "sys.h" 
/*

 PA9,USART_TX,,,,,,,
 PA10,USART_RX,,,,,,,
 已经使用DMA2的数据流7，通道4。

*/



#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define USE_USART1_PRINTF 1



//如果想串口中断接收，请不要注释以下宏定义
void Usart1PrintInit(void);
void Usart1DmaLoop(void);
#endif


