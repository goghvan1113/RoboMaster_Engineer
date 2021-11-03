#include "dbus_remote.h"
#include "usart.h"

//双缓冲区
static uint8_t DBUS_RX_BUFF[2][DBUS_RX_BUF_NUM]; 

static RC_Data_t RC_data;           //本次遥控数据
static RC_Data_t RC_data_last;      //上次遥控数据

uint16_t Dbus_OffLine_Count=0;      //遥控器离线计数
uint8_t Dbus_OffLine_Flag=0;        //遥控器离线标志位


void DbusUsart2_Init(void)//100000波特率
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/* -------------- Configure GPIO ---------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;         //PA3 USART2_RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //悬空
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//复用为串口2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	/* -------------- Configure USART ---------------------------------------*/
	USART_InitStructure.USART_BaudRate = 100000;  
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_Even;  //偶校验
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
	//DMA1_stream5_ch4，DMA1数据流5通道4
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART2->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DBUS_RX_BUFF[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 36;   //双缓冲区为36个字节
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
	
	DMA_Cmd(DMA1_Stream5, DISABLE);   //此处添加一个DISABLE
	DMA_Cmd(DMA1_Stream5, ENABLE);
}

/**	
*@brief	获取遥控器控制信息
*@return RC_Data_t
*/
RC_Data_t GetRcData(void)
{
	return RC_data;
}

RC_Data_t *get_remote_control_point(void)
{//使用指针方式传递信息
    return &RC_data;
}


/**	
*@brief	获取遥控器上一次控制信息
*@return RC_Data_t
*/
RC_Data_t GetLastRcData(void)
{
	return RC_data_last;
}

RC_Data_t *get_remote_last_point(void)
{//使用指针方式传递信息
    return &RC_data_last;
}
/**	
*@brief	获取遥控器是否离线
*@return dbus_offline_flag
*/
int16_t Getdbusoffline_flag(void)
{
	return Dbus_OffLine_Flag;
}




/**	
*@brief	处理遥控器接收的数据
*@input uint8_t *pData：存储接收到的遥控器的数据缓存区（双缓存）
*包含得到遥杆、左上角滑轮和拨杆的数据
*/
void Remote_Data_Encode(uint8_t *pData)
{
	RC_data_last=RC_data;
	uint8_t s1,s2;
	
	//中间的拨杆
	RC_data.rc.ch[0]  = ( pData[0] | (pData[1]<<8)) & 0x07FF; 
	RC_data.rc.ch[1]  = ((pData[1]>>3) | (pData[2]<<5)) & 0x07FF;
	RC_data.rc.ch[2]  = ((pData[2]>>6) | (pData[3]<<2) |(pData[4] << 10)) & 0x07FF;
	RC_data.rc.ch[3]  = ((pData[4]>>1) | (pData[5]<<7)) & 0x07FF;
	
	RC_data.rc.ch[4]  =	pData[16]|(pData[17]<<8);  //左上角拨杆开关
	s1   = ((pData[5] >> 4) & 0x000C)>>2;
	s2   = ((pData[5] >> 4) & 0x0003);
	
	Remote_Swich_Encode(&RC_data.rc.s1,s1);    //获取左拨杆状态（上，中，下）
	Remote_Swich_Encode(&RC_data.rc.s2,s2);    //获取右拨杆状态（上，中，下）
	
	if(Dbus_OffLine_Flag==0)   //键鼠控制模式
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
*@brief	获取遥控器拨杆的位置
*@input Sw_Data_t *SW:拨杆结构，包含上中下三个档位的标志位
*				uint8_t sw：哪一个拨杆，（S1或S2)
*改变相应变量,若在该档位，则将该档位的标志位置1，其余置0
*可以通过拨杆的不同位置设置机器人不同模式
*/
void Remote_Swich_Encode(Sw_Data_t *SW,uint8_t sw)
{
	switch (sw)
	{
		case 1:{      //上
			SW->up=1;
			SW->mid=0;
			SW->down=0;
		}break;
		case 3:{      //中
			SW->up=0;
			SW->mid=1;
			SW->down=0;
		}break;
		case 2:{      //下
			SW->up=0;
			SW->mid=0;
			SW->down=1;
		}break;
	}
}


void USART2_IRQHandler(void)
{
//在串口2中断处理中，配置为串口接收DMA，在DMA中处理遥控器数据（双缓冲区）
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        static uint16_t this_time_rx_len = 0;
        USART_ReceiveData(USART2);

        if(DMA_GetCurrentMemoryTarget(DMA1_Stream5) == 0)
        {
            //重新设置DMA
            DMA_Cmd(DMA1_Stream5, DISABLE);
            this_time_rx_len = DBUS_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);
            DMA_SetCurrDataCounter(DMA1_Stream5, DBUS_RX_BUF_NUM);
            DMA1_Stream5->CR |= DMA_SxCR_CT;    //当前目标存储器为存储器1，将CR寄存器的CT位置一
            //清DMA中断标志
            DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA1_Stream5, ENABLE);
            if(this_time_rx_len == RC_FRAME_LENGTH)
            {
                //处理遥控器数据
                Remote_Data_Encode(DBUS_RX_BUFF[0]);
            }
        }
        else
        {
            //重新设置DMA
            DMA_Cmd(DMA1_Stream5, DISABLE);
            this_time_rx_len = DBUS_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);
            DMA_SetCurrDataCounter(DMA1_Stream5, DBUS_RX_BUF_NUM);
            DMA1_Stream5->CR &= ~(DMA_SxCR_CT);  //当前目标存储器为存储器2，将CR寄存器的CT位清零
            //清DMA中断标志
            DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA1_Stream5, ENABLE);
            if(this_time_rx_len == RC_FRAME_LENGTH)
            {
                //处理遥控器数据
                Remote_Data_Encode(DBUS_RX_BUFF[1]);
				Dbus_OffLine_Count=0;  	      //清空遥控器离线计数
            }

        }
    }
}
