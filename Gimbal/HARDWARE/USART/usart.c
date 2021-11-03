#include "usart.h"
#include "data_fifo.h"

#define PrintLengthMax	2048		//发送缓存区大小


//USART1_TX对应于DMA2的数据流7，通道4

typedef struct
{
	uint8_t Usart1DmaSendBuff[PrintLengthMax];//DMA发送缓存区
	uint16_t Usart1_DmaBuffSize;//DMA发送对应的数据长度
	uint8_t Usart1DmaSending;//DMA正在发送	
	uint8_t Usart1DmaPuting;//正在往fifo里面放
}Usart1DmaState_t;//DMA工作状态

Usart1DmaState_t Usart1DmaState = { {0}, 0, 0, 0};

static uint8_t Usart1PrintBuff[PrintLengthMax] = {0};//fifo发送缓存区
static fifo_s_t Usart1PrintFifo;


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if USE_USART1_PRINTF
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout; 

//开启use MicroLib可以不定义下面的代码
////定义_sys_exit()以避免使用半主机模式    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//}

int fputc(int ch, FILE *f)
{ 	
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//	USART1->DR = (u8) ch;
	Usart1DmaState.Usart1DmaPuting = 1;
	if(fifo_s_put(&Usart1PrintFifo,ch) == -1)
	{//fifo满了
		fifo_flush(&Usart1PrintFifo);
	}		
	Usart1DmaState.Usart1DmaPuting = 0;	
	return ch;
}

#endif
 

void UseDmaSendChars(uint8_t *source, uint32_t HowMany)
{
	Usart1DmaState.Usart1DmaPuting = 1;	
	if(fifo_s_puts(&Usart1PrintFifo,source,HowMany) != HowMany)
	{//fifo满了
		fifo_flush(&Usart1PrintFifo);
	}
	fifo_s_put(&Usart1PrintFifo,'\n');
	Usart1DmaState.Usart1DmaPuting = 0;
}

void Usart1DmaSend(uint16_t HowMany)
{//以Usart1DmaSendBuff为开始地址，发送多少个字节
	DMA_Cmd(DMA2_Stream7,DISABLE);//确保DMA可以被设置  	
	DMA_SetCurrDataCounter(DMA2_Stream7,HowMany);
	DMA_Cmd(DMA2_Stream7,ENABLE);	
}

//
void Usart1DmaLoop(void)
{//DMA负责print的主循环任务
	
	//static uint32_t HowMany_Byte = 0;
	
	if(Usart1DmaState.Usart1DmaSending == 0 && Usart1DmaState.Usart1DmaPuting == 0)
	{//DMA不是正在发送且fifo是空闲的
		if(!fifo_is_empty(&Usart1PrintFifo) )
		{//fifo非空
			//HowMany_Byte = Usart1PrintFifo.used;
			Usart1DmaState.Usart1_DmaBuffSize = fifo_s_gets(&Usart1PrintFifo,Usart1DmaState.Usart1DmaSendBuff,Usart1PrintFifo.used);
			//把fifo中的东西读出来
			Usart1DmaSend(Usart1DmaState.Usart1_DmaBuffSize);
			Usart1DmaState.Usart1DmaSending = 1;
		}
	}	
}
//
//
void DMA2_Stream7_IRQHandler(void)
{//dma中断
	if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7))
	{
		if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7) )
		{
			DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
			Usart1DmaState.Usart1DmaSending = 0;
		}
		DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7);
		//Usart1DmaLoop();
	}			
}
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef	DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1	
	USART_Cmd(USART1, ENABLE);  //使能串口1 	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//开启串口DMA
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_DeInit(DMA2_Stream7);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;//通道选择
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR); //DMA外设地址，对DR进行读操作相当于接收，对DR进行写操作相当于发送
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Usart1DmaState.Usart1DmaSendBuff;//DMA内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//外设到存储模式
	DMA_InitStructure.DMA_BufferSize = Usart1DmaState.Usart1_DmaBuffSize;//数据传输量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储区增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度：8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度：8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//不使用循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//最高优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//不使用FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;//设置FIFO阈值无效
	DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;//设置DMA存储器突发模式为正常模式
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
	DMA_Init(DMA2_Stream7,&DMA_InitStructure);
	
	DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA2_Stream7,DISABLE);
}



#if EN_USART1_RX
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		
		if((USART1_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART1_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else USART1_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
  } 
} 
 
#endif	


void Usart1PrintInit(void)
{//初始化发送fifo
	fifo_s_init(&Usart1PrintFifo,Usart1PrintBuff,PrintLengthMax);
	uart_init(115200);
}



