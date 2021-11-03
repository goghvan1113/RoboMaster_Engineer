#include "usart.h"
#include "data_fifo.h"

#define PrintLengthMax	2048		//���ͻ�������С


//USART1_TX��Ӧ��DMA2��������7��ͨ��4

typedef struct
{
	uint8_t Usart1DmaSendBuff[PrintLengthMax];//DMA���ͻ�����
	uint16_t Usart1_DmaBuffSize;//DMA���Ͷ�Ӧ�����ݳ���
	uint8_t Usart1DmaSending;//DMA���ڷ���	
	uint8_t Usart1DmaPuting;//������fifo�����
}Usart1DmaState_t;//DMA����״̬

Usart1DmaState_t Usart1DmaState = { {0}, 0, 0, 0};

static uint8_t Usart1PrintBuff[PrintLengthMax] = {0};//fifo���ͻ�����
static fifo_s_t Usart1PrintFifo;


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if USE_USART1_PRINTF
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout; 

//����use MicroLib���Բ���������Ĵ���
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//}

int fputc(int ch, FILE *f)
{ 	
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//	USART1->DR = (u8) ch;
	Usart1DmaState.Usart1DmaPuting = 1;
	if(fifo_s_put(&Usart1PrintFifo,ch) == -1)
	{//fifo����
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
	{//fifo����
		fifo_flush(&Usart1PrintFifo);
	}
	fifo_s_put(&Usart1PrintFifo,'\n');
	Usart1DmaState.Usart1DmaPuting = 0;
}

void Usart1DmaSend(uint16_t HowMany)
{//��Usart1DmaSendBuffΪ��ʼ��ַ�����Ͷ��ٸ��ֽ�
	DMA_Cmd(DMA2_Stream7,DISABLE);//ȷ��DMA���Ա�����  	
	DMA_SetCurrDataCounter(DMA2_Stream7,HowMany);
	DMA_Cmd(DMA2_Stream7,ENABLE);	
}

//
void Usart1DmaLoop(void)
{//DMA����print����ѭ������
	
	//static uint32_t HowMany_Byte = 0;
	
	if(Usart1DmaState.Usart1DmaSending == 0 && Usart1DmaState.Usart1DmaPuting == 0)
	{//DMA�������ڷ�����fifo�ǿ��е�
		if(!fifo_is_empty(&Usart1PrintFifo) )
		{//fifo�ǿ�
			//HowMany_Byte = Usart1PrintFifo.used;
			Usart1DmaState.Usart1_DmaBuffSize = fifo_s_gets(&Usart1PrintFifo,Usart1DmaState.Usart1DmaSendBuff,Usart1PrintFifo.used);
			//��fifo�еĶ���������
			Usart1DmaSend(Usart1DmaState.Usart1_DmaBuffSize);
			Usart1DmaState.Usart1DmaSending = 1;
		}
	}	
}
//
//
void DMA2_Stream7_IRQHandler(void)
{//dma�ж�
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
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART1_RX_STA=0;       //����״̬���	

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef	DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//��������DMA
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_DeInit(DMA2_Stream7);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;//ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR); //DMA�����ַ����DR���ж������൱�ڽ��գ���DR����д�����൱�ڷ���
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Usart1DmaState.Usart1DmaSendBuff;//DMA�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//���赽�洢ģʽ
	DMA_InitStructure.DMA_BufferSize = Usart1DmaState.Usart1_DmaBuffSize;//���ݴ�����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ��ȣ�8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ��ȣ�8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//��ʹ��ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//������ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//��ʹ��FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;//����FIFO��ֵ��Ч
	DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;//����DMA�洢��ͻ��ģʽΪ����ģʽ
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA2_Stream7,&DMA_InitStructure);
	
	DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA2_Stream7,DISABLE);
}



#if EN_USART1_RX
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		
		if((USART1_RX_STA&0x8000)==0)//����δ���
		{
			if(USART1_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
  } 
} 
 
#endif	


void Usart1PrintInit(void)
{//��ʼ������fifo
	fifo_s_init(&Usart1PrintFifo,Usart1PrintBuff,PrintLengthMax);
	uart_init(115200);
}



