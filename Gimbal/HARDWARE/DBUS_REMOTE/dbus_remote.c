#include "dbus_remote.h"
#include "usart.h"

//˫������
static uint8_t DBUS_RX_BUFF[2][DBUS_RX_BUF_NUM]; 

static RC_Data_t RC_data;           //����ң������
static RC_Data_t RC_data_last;      //�ϴ�ң������

uint16_t Dbus_OffLine_Count=0;      //ң�������߼���
uint8_t Dbus_OffLine_Flag=0;        //ң�������߱�־λ


void DbusUsart2_Init(void)//100000������
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/* -------------- Configure GPIO ---------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;         //PA3 USART2_RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //����
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����Ϊ����2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	/* -------------- Configure USART ---------------------------------------*/
	USART_InitStructure.USART_BaudRate = 100000;  
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_Even;  //żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
	
	USART_Cmd(USART2, ENABLE);
	
	/* -------------- Configure NVIC ---------------------------------------*/
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* -------------- Configure DMA -----------------------------------------*/
	//DMA1_stream5_ch4��DMA1������5ͨ��4
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART2->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DBUS_RX_BUFF[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 36;   //˫������Ϊ36���ֽ�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	
	DMA_DoubleBufferModeConfig(DMA1_Stream5, (uint32_t)DBUS_RX_BUFF[1], DMA_Memory_0);
	DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);
	
	DMA_Cmd(DMA1_Stream5, DISABLE);   //�˴����һ��DISABLE
	DMA_Cmd(DMA1_Stream5, ENABLE);
}

/**	
*@brief	��ȡң����������Ϣ
*@return RC_Data_t
*/
RC_Data_t GetRcData(void)
{
	return RC_data;
}

RC_Data_t *get_remote_control_point(void)
{//ʹ��ָ�뷽ʽ������Ϣ
    return &RC_data;
}


/**	
*@brief	��ȡң������һ�ο�����Ϣ
*@return RC_Data_t
*/
RC_Data_t GetLastRcData(void)
{
	return RC_data_last;
}

RC_Data_t *get_remote_last_point(void)
{//ʹ��ָ�뷽ʽ������Ϣ
    return &RC_data_last;
}
/**	
*@brief	��ȡң�����Ƿ�����
*@return dbus_offline_flag
*/
int16_t Getdbusoffline_flag(void)
{
	return Dbus_OffLine_Flag;
}




/**	
*@brief	����ң�������յ�����
*@input uint8_t *pData���洢���յ���ң���������ݻ�������˫���棩
*�����õ�ң�ˡ����Ͻǻ��ֺͲ��˵�����
*/
void Remote_Data_Encode(uint8_t *pData)
{
	RC_data_last=RC_data;
	uint8_t s1,s2;
	
	//�м�Ĳ���
	RC_data.rc.ch[0]  = ( pData[0] | (pData[1]<<8)) & 0x07FF; 
	RC_data.rc.ch[1]  = ((pData[1]>>3) | (pData[2]<<5)) & 0x07FF;
	RC_data.rc.ch[2]  = ((pData[2]>>6) | (pData[3]<<2) |(pData[4] << 10)) & 0x07FF;
	RC_data.rc.ch[3]  = ((pData[4]>>1) | (pData[5]<<7)) & 0x07FF;
	
	RC_data.rc.ch[4]  =	pData[16]|(pData[17]<<8);  //���Ͻǲ��˿���
	s1   = ((pData[5] >> 4) & 0x000C)>>2;
	s2   = ((pData[5] >> 4) & 0x0003);
	
	Remote_Swich_Encode(&RC_data.rc.s1,s1);    //��ȡ�󲦸�״̬���ϣ��У��£�
	Remote_Swich_Encode(&RC_data.rc.s2,s2);    //��ȡ�Ҳ���״̬���ϣ��У��£�
	
	if(Dbus_OffLine_Flag==0)   //�������ģʽ
	{   
		memcpy(&RC_data.mouse, &pData[6], sizeof(Mouse_Data_t));
		memcpy(&RC_data.key,&pData[14],sizeof(Key_Data_t));
	
	}
	
	RC_data.rc.ch[0] -= REMOTE_CONTROLLER_OFFSET;
	RC_data.rc.ch[1] -= REMOTE_CONTROLLER_OFFSET;
	RC_data.rc.ch[2] -= REMOTE_CONTROLLER_OFFSET;
	RC_data.rc.ch[3] -= REMOTE_CONTROLLER_OFFSET;
	RC_data.rc.ch[4] -= REMOTE_CONTROLLER_OFFSET;
 	
}


/**	
*@brief	��ȡң�������˵�λ��
*@input Sw_Data_t *SW:���˽ṹ������������������λ�ı�־λ
*				uint8_t sw����һ�����ˣ���S1��S2)
*�ı���Ӧ����,���ڸõ�λ���򽫸õ�λ�ı�־λ��1��������0
*����ͨ�����˵Ĳ�ͬλ�����û����˲�ͬģʽ
*/
void Remote_Swich_Encode(Sw_Data_t *SW,uint8_t sw)
{
	switch (sw)
	{
		case 1:{      //��
			SW->up=1;
			SW->mid=0;
			SW->down=0;
		}break;
		case 3:{      //��
			SW->up=0;
			SW->mid=1;
			SW->down=0;
		}break;
		case 2:{      //��
			SW->up=0;
			SW->mid=0;
			SW->down=1;
		}break;
	}
}


void USART2_IRQHandler(void)
{
//�ڴ���2�жϴ����У�����Ϊ���ڽ���DMA����DMA�д���ң�������ݣ�˫��������
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        static uint16_t this_time_rx_len = 0;
        USART_ReceiveData(USART2);

        if(DMA_GetCurrentMemoryTarget(DMA1_Stream5) == 0)
        {
            //��������DMA
            DMA_Cmd(DMA1_Stream5, DISABLE);
            this_time_rx_len = DBUS_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);
            DMA_SetCurrDataCounter(DMA1_Stream5, DBUS_RX_BUF_NUM);
            DMA1_Stream5->CR |= DMA_SxCR_CT;    //��ǰĿ��洢��Ϊ�洢��1����CR�Ĵ�����CTλ��һ
            //��DMA�жϱ�־
            DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA1_Stream5, ENABLE);
            if(this_time_rx_len == RC_FRAME_LENGTH)
            {
                //����ң��������
                Remote_Data_Encode(DBUS_RX_BUFF[0]);
            }
        }
        else
        {
            //��������DMA
            DMA_Cmd(DMA1_Stream5, DISABLE);
            this_time_rx_len = DBUS_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);
            DMA_SetCurrDataCounter(DMA1_Stream5, DBUS_RX_BUF_NUM);
            DMA1_Stream5->CR &= ~(DMA_SxCR_CT);  //��ǰĿ��洢��Ϊ�洢��2����CR�Ĵ�����CTλ����
            //��DMA�жϱ�־
            DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA1_Stream5, ENABLE);
            if(this_time_rx_len == RC_FRAME_LENGTH)
            {
                //����ң��������
                Remote_Data_Encode(DBUS_RX_BUFF[1]);
				Dbus_OffLine_Count=0;  	      //���ң�������߼���
            }

        }
    }
}
