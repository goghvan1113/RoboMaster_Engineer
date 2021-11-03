#include "judge_interact.h"
#include "stm32f4xx_dma.h"
#include "string.h"
#include "math.h"


static ext_student_interactive_all_data_t Judge_DrawBuff;//��ͼ��ʾ������
static int8_t CountGraph = 0;//ͳ�ƻ����������ж��ٸ�ͼ�Σ����һ�η���7��
static graphic_data_struct_t *GraphDataBuff[7];
static int8_t NowSendingGraph = 0;//�Ƿ����ڻ�ͼ��
static uint8_t FrameSeq	=	0;//�����
uint16_t SelfRobot = RedHero;
uint16_t SelfOperator= RedHeroOperator;
static float VoltageLast = 1.0;
static float VoltageNow = 2.0;
static float CapicityPercentLast = 0.1;
static float CapicityPercentNow = 0.0;

static float ScreenPitch = 1.0;
static float LastScreenPitch = 2.0;
static float ScreenYaw = 0.1;
static float LastScreenYaw = 0.2;

static uint8_t RadarNeedUpdate = 0;

static uint8_t IsDrawEqualLine = 0;//���»���ʱ����Ϊ�����ڸ������ݻ���ֳ�ͻ

//������װ�װ���ת
static graphic_color_tpye_e	Armor_Color_1 = Green,Armor_Color_2 = Green,Armor_Color_3 = Green,Armor_Color_4 = Green;
static float Armor_YawAngle = 0.0;

//�����ǹ��̻�����
static float JudgeAngineer_Height = 0.0;

Rec_DataDoubleBuff_t Judge_DataBuff = {NULL,NULL,{0},{0} };
Judge_TxDataBuff_t	Judge_TxDataBuff = {NULL,NULL,{0} ,{0} ,0,0,0};
receive_judge_t judge_recv_mesg;//�����õ��������ݴ������
Judge_UndateFlag_t	Judge_UndateFlag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

#define CHANNEL_NUMBER_STR	7
#define CHANNEL_NUMBER_MAX	9	//ͨ����Ŀ�����Ҫ����2λ����һ���ַ���ռ1��ͨ����7��ͼ��ռһ��ͨ��
	
static graphic_color_tpye_e Judge_GraphChannelColor[CHANNEL_NUMBER_MAX - CHANNEL_NUMBER_STR][7];

typedef struct
{
	uint64_t LastTime;
	uint32_t TimeSpaceMS;
	uint8_t HasExisted;
	uint8_t NeedUpdate;
	char NextStr[31]; 
	char Name[4];
	graphic_data_struct_t GraphData;
}ChannelMsg_t;

ChannelMsg_t Channel[CHANNEL_NUMBER_MAX];
	
	
//�βα�Position_x���е�x��Position_y���е�y��LongestLineLen��߳��ȣ�DistancePerLineÿ���߼��
void Draw_EqualHeightLine(uint8_t RobotLevel);
void Judge_SetDMASend(uint8_t* Addr,uint16_t HowMany);
void Judge_TestSpeed(frame_cmd_id_e WhichMsg);
void DefaultGraphData(graphic_data_struct_t *GraphData_t,uint8_t *GraphName);
void Judge_Delay_us(uint32_t Time_us);
void Judge_Delay_ms(uint32_t Time_ms);
//

void Judge_SelfControl(uint8_t *DataAddr)
{//�Զ�����������һ�η�30���ֽڣ�
	static JudgeFullFrame_t *Temp = NULL;
	static self_control_interactive_all_data_t *TempOfSelfInteractive_all_data = NULL;
	static uint8_t SendSEQ	=	0;//�����
	
	++SendSEQ;
	Temp = (JudgeFullFrame_t*)Judge_TxDataBuff.WhichBuffToCPU;
	Temp->header.SOF = FrameHeaderSOF;
	Temp->header.DataLength = sizeof(DataAddr);
	Temp->header.Seq = SendSEQ;
	Temp->header.CRC8 = get_crc8_check_sum(Judge_TxDataBuff.WhichBuffToCPU,4,CRC8_INIT_NUM);
	
	Temp->frame_cmd_id = SELF_CONTROL_INTERACTIVE_ID;
	strcpy((char*)TempOfSelfInteractive_all_data->Data,(char*)DataAddr);
	*((uint16_t*)(Temp->data + Temp->header.DataLength)) = get_crc16_check_sum(Judge_TxDataBuff.WhichBuffToCPU,7 + sizeof(DataAddr),CRC16_INIT_NUM);
	if(Judge_TxDataBuff.NowDMASendIng == 0)
	{
	
		if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 9 + Temp->header.DataLength;
			Judge_SetDMASend(Judge_TxDataBuff.Buff_0,Judge_TxDataBuff.HowLongWillSend_Buff0);
			Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_1;
			Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_0;	
		}
		else if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 9 + Temp->header.DataLength;
			Judge_SetDMASend(Judge_TxDataBuff.Buff_1,Judge_TxDataBuff.HowLongWillSend_Buff1);
			Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
			Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;
		}
	}
	else
	{
		if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 9 + Temp->header.DataLength;
		}
		else if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 9 + Temp->header.DataLength;
		}

	}
}
	
	
//	
void Judge_RobotToRobot(Robots_ID_e receiver, uint8_t *DataAddr)
{//�����˼佻��
	static JudgeFullFrame_t *Temp = NULL;
	static ext_student_interactive_all_data_t *TempOfinteractive_all_data = NULL;
	static uint8_t SendSEQ	=	0;//�����
	
	++SendSEQ;
	
	Temp = (JudgeFullFrame_t*)Judge_TxDataBuff.WhichBuffToCPU;
	
	Temp->header.SOF = FrameHeaderSOF;
	Temp->header.DataLength = sizeof(DataAddr) + 6;
	Temp->header.Seq = SendSEQ;
	Temp->header.CRC8 = get_crc8_check_sum(Judge_TxDataBuff.WhichBuffToCPU,4,CRC8_INIT_NUM);
	
	Temp->frame_cmd_id = ROBOT_INTERACTIVE_ID;
	
	TempOfinteractive_all_data = (ext_student_interactive_all_data_t*)Temp->data;
	
	TempOfinteractive_all_data->interactive_header_data.sender_ID = SelfRobot;
	TempOfinteractive_all_data->interactive_header_data.receiver_ID = receiver;
	TempOfinteractive_all_data->interactive_header_data.data_cmd_id = 0x0200;
	//memcmp(TempOfinteractive_all_data->Data,DataAddr,HowManyDatas);
	strcpy((char*)TempOfinteractive_all_data->Data,(char*)DataAddr);
	
	*((uint16_t*)(Temp->data + Temp->header.DataLength)) = get_crc16_check_sum(Judge_TxDataBuff.WhichBuffToCPU,13 + sizeof(DataAddr),CRC16_INIT_NUM);
	
	if(Judge_TxDataBuff.NowDMASendIng == 0)
	{
	
		if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 9 + Temp->header.DataLength;
			Judge_SetDMASend(Judge_TxDataBuff.Buff_0,Judge_TxDataBuff.HowLongWillSend_Buff0);
			Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_1;
			Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_0;	
		}
		else if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 9 + Temp->header.DataLength;
			Judge_SetDMASend(Judge_TxDataBuff.Buff_1,Judge_TxDataBuff.HowLongWillSend_Buff1);
			Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
			Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;
		}
	}
	else if(Judge_TxDataBuff.NowDMASendIng == 1)
	{
		if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 9 + Temp->header.DataLength;
			//Judge_SetDMASend(Judge_TxDataBuff.Buff_0,Judge_TxDataBuff.HowLongWillSend_Buff0);
			//Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_1;
			//Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_0;	
		}
		else if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 9 + Temp->header.DataLength;
			//Judge_SetDMASend(Judge_TxDataBuff.Buff_1,Judge_TxDataBuff.HowLongWillSend_Buff1);
			//Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
			//Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;
		}

	}
}

//DrawHowMuchGraphֻ����1��2��5��7
//�βα�GraphOrString=='G'��ʾ����ͼ�����ݣ�Ϊ'S'��ʾ�����ַ�����
void SendGraphBuffData(char GraphOrString)
{
	static JudgeFullFrame_t *Temp = NULL;
		
	NowSendingGraph = 1;//��ֹ�ڷ��͵�ʱ�����¼ӻ�ͼ��ͼ�ΰ������޸���
	++ FrameSeq;
	Temp = (JudgeFullFrame_t*)Judge_TxDataBuff.WhichBuffToCPU;
	
	Temp->header.SOF = FrameHeaderSOF;
	//Temp->header.DataLength = HowManyDatas + 6;
	Temp->header.Seq = FrameSeq;
	//Temp->header.CRC8 = get_crc8_check_sum(Judge_TxDataBuff.WhichBuffToCPU,4,CRC8_INIT);
	
	Temp->frame_cmd_id = ROBOT_INTERACTIVE_ID;
	Temp->header.DataLength = 6;//֡ͷ��֡CMD��ͼ��CMD��crc16֡β == 5 + 2 + 6 + 2== 15�ֽ�
	
	//�±�0-4֡ͷ��5-6֡CMD��7-12ͼ��CMD��
	//13-27�ǵ�һͼ�Σ�28-42�ڶ���43-57������58-72���ģ�73-87���壬88-102������103-117���ߣ�118-119Ϊcrc16
	//Judge_DrawBuff.Data[]���±�0-14�ǵ�һͼ�Σ�15-29�ڶ���30-44������45-59���ģ�60-74���壬75-89������90-104���ߣ�105-106Ϊcrc16
	switch(CountGraph)
	{
		case 1:
		{
			//memcpy(&JudgeTXBuff[13],(uint8_t*)&graphic_data,15);
			Temp->header.DataLength += 15;			
			Judge_DrawBuff.interactive_header_data.data_cmd_id = 0x0101;			
			break;
		}
		
		case 2:
		{
			Temp->header.DataLength += 30;
			Judge_DrawBuff.interactive_header_data.data_cmd_id = 0x0102;
			break;
		}
		case 3:
		{//
			if(GraphOrString == 'G')
			{
				memcpy(&Judge_DrawBuff.Data[45],&Judge_DrawBuff.Data[30],15);//�ѵ�����ͼ�ε����ݸ��Ƶ����ĸ�ͼ��
			}
			else if(GraphOrString == 'S')
			{
				Temp->header.DataLength += 45;
				Judge_DrawBuff.interactive_header_data.data_cmd_id = 0x0110;//�ַ���
				break;
			}
		}
		case 4:
		{//4������ֱ�ӷ���Ҫ�ճ�5����
			memcpy(&Judge_DrawBuff.Data[60],&Judge_DrawBuff.Data[45],15);//�ѵ��ĸ�ͼ�ε����ݸ��Ƶ������ͼ��
		}
		case 5:
		{
			Temp->header.DataLength += 75;
			Judge_DrawBuff.interactive_header_data.data_cmd_id = 0x0103;
			break;
		}
		case 6:
		{//6������ֱ�ӷ���Ҫ�ճ�7����
			memcpy(&Judge_DrawBuff.Data[90],&Judge_DrawBuff.Data[75],15);//�ѵ�����ͼ�ε����ݸ��Ƶ����߸�ͼ��
		}
		case 7:
		{
			Temp->header.DataLength += 105;
			Judge_DrawBuff.interactive_header_data.data_cmd_id = 0x0104;
			break;
		}
	}
	
	Temp->header.CRC8 = get_crc8_check_sum(Judge_TxDataBuff.WhichBuffToCPU,4,CRC8_INIT_NUM);
	memcpy(Temp->data,(uint8_t*)&Judge_DrawBuff,Temp->header.DataLength);
	*((uint16_t*)(Temp->data + Temp->header.DataLength)) = get_crc16_check_sum(Judge_TxDataBuff.WhichBuffToCPU,7 + Temp->header.DataLength,CRC16_INIT_NUM);

	if(Judge_TxDataBuff.NowDMASendIng == 0)
	{
	
		if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 9 + Temp->header.DataLength;
			Judge_SetDMASend(Judge_TxDataBuff.Buff_0,Judge_TxDataBuff.HowLongWillSend_Buff0);
			Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_1;
			Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_0;	
		}
		else if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 9 + Temp->header.DataLength;
			Judge_SetDMASend(Judge_TxDataBuff.Buff_1,Judge_TxDataBuff.HowLongWillSend_Buff1);
			Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
			Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;
		}
	}
	else
	{
		if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 9 + Temp->header.DataLength;
			//Judge_SetDMASend(Judge_TxDataBuff.Buff_0,Judge_TxDataBuff.HowLongWillSend_Buff0);
			//Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_1;
			//Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_0;	
		}
		else if(Judge_TxDataBuff.WhichBuffToCPU == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 9 + Temp->header.DataLength;
			//Judge_SetDMASend(Judge_TxDataBuff.Buff_1,Judge_TxDataBuff.HowLongWillSend_Buff1);
			//Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
			//Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;
		}

	}		
	CountGraph = 0;//���GraphDataBuff
	NowSendingGraph = 0;
}
//����ֵ��-1��ʾ������������0��ʾ���뻺�����ɹ���1��ʾ���ڻ�ͼ������һ������ӻ���������Ϊû����FIFO�������ڶ���ʱ���ܽ���д��
int8_t AddGraphToBuff(graphic_data_struct_t *GraphData_t)
{
	if(NowSendingGraph == 1)
	{
		return 1;
	}
	else if(NowSendingGraph == 0 && CountGraph < 7)
	{
		GraphDataBuff[CountGraph] = (graphic_data_struct_t*)&Judge_DrawBuff.Data[CountGraph * 15];
		//��*GraphData_tӳ�䵽TXBUFF���棬�ͽ�ʡ�˴�graphic_data_struct_t�Ŀռ�
		//HEADER_LEN == 5��CMD_LEN == 2��Ҳ���ǻ���0��ͼ��ʱ���Ǵ�JudgeTXBuff�ĵ�13λ��ʼ���
		GraphDataBuff[CountGraph]->graphic_name[0] = GraphData_t->graphic_name[0];
		GraphDataBuff[CountGraph]->graphic_name[1] = GraphData_t->graphic_name[1];
		GraphDataBuff[CountGraph]->graphic_name[2] = GraphData_t->graphic_name[2];
		GraphDataBuff[CountGraph]->operate_tpye = GraphData_t->operate_tpye;
		GraphDataBuff[CountGraph]->graphic_tpye= GraphData_t->graphic_tpye;
		GraphDataBuff[CountGraph]->layer = GraphData_t->layer;
		GraphDataBuff[CountGraph]->color = GraphData_t->color;
		GraphDataBuff[CountGraph]->start_angle = GraphData_t->start_angle;
		GraphDataBuff[CountGraph]->end_angle = GraphData_t->end_angle;
		GraphDataBuff[CountGraph]->width = GraphData_t->width;
		GraphDataBuff[CountGraph]->start_x = GraphData_t->start_x;
		GraphDataBuff[CountGraph]->start_y = GraphData_t->start_y;
		GraphDataBuff[CountGraph]->radius = GraphData_t->radius;
		GraphDataBuff[CountGraph]->end_x = GraphData_t->end_x;
		GraphDataBuff[CountGraph]->end_y = GraphData_t->end_y;
		++ CountGraph;
	}
	else if(NowSendingGraph == 0 && CountGraph < 7)
	{
		return -1;
	}

	return 2;
}


//��ӡװ�װ���ת�ǶȺ�װ�װ���ɫ��10HZ���Ƕ�0-360����ʱ��Ϊ��
int8_t PrintArmorRotate(float Yaw,graphic_color_tpye_e Armor_1,graphic_color_tpye_e Armor_2,
						graphic_color_tpye_e Armor_3,graphic_color_tpye_e Armor_4)
{
	if(Yaw < 0 || Yaw > 360)
		return 1;
	
	if(Yaw != Armor_YawAngle || Armor_1 != Armor_Color_1 || Armor_2 != Armor_Color_2 || Armor_3 != Armor_Color_3 || Armor_4 != Armor_Color_4)
	{
		Yaw = Armor_YawAngle;
		Armor_Color_1 = Armor_1;
		Armor_Color_2 = Armor_2;
		Armor_Color_3 = Armor_3;
		Armor_Color_4 = Armor_4;
		Channel[7].NeedUpdate = 1;
	}
	
	return 0;
	
}
	


int8_t Judge_AngineerPrintLadder(float Percent)
{//���̻�������ʾ���ӡ������β�Ϊ�ٷֱȣ���Χ��0-100
	
	static float HasExistPercent = -10;
	
	if( Percent < 0 || Percent > 100)
		return 1;
	
	if(HasExistPercent != Percent)
	{
		HasExistPercent = Percent;
		JudgeAngineer_Height = HasExistPercent;
		Channel[7].NeedUpdate = 1;
	}
	
	return 0;
}

//����Ļ�ϴ�ӡ�ַ��������βΣ�WhichChannel��ΧΪ0-7����ʾ8��ͨ����STRΪͨ��Ҫ��ʾ���ַ���
int8_t PrintfToScreen(uint8_t WhichChannel,char *STR)
{
	uint8_t BuffTemp[31] = {0};

	if(WhichChannel > 7)
		return 1;

	
	if(strlen((char*)STR) <= 30)
	{
		memcpy(BuffTemp,STR,strlen((char*)STR));
	}
	else
	{
		memcpy(BuffTemp,STR,30);
	}
	memcpy(Channel[WhichChannel].NextStr,BuffTemp,30);
	
	Channel[WhichChannel].NeedUpdate = 1;
	
	return 0;
}
//����Ļ�ϴ�ӡYAW���PITCH�����ݡ�
int8_t PrintfYawPitchToScreen(float YawAngel,float PitchAngel)
{
	
	if(ScreenPitch != PitchAngel || ScreenYaw != YawAngel)
	{
		LastScreenPitch = PitchAngel;
		ScreenPitch = PitchAngel;
		LastScreenYaw = ScreenYaw;
		ScreenYaw = YawAngel;	
		Channel[7].NeedUpdate = 1;
	}
	
	return 0;
}
//����Ļ�ϴ�ӡ�������ݵĵ�ѹ��
int8_t PrintfVoltageToScreen(float Votlage2,float Percent)
{	
	if(Percent < 0)
		Percent = 0;
	if(Percent > 100)
		Percent = 100;
	
	if(CapicityPercentNow != Percent)
	{
		if(CapicityPercentNow - Percent < 0.0 || CapicityPercentNow - Percent > 0.0)
		{
			CapicityPercentLast = CapicityPercentNow;
			CapicityPercentNow = Percent;
			VoltageLast = VoltageNow;
			VoltageNow = Votlage2;	
			Channel[7].NeedUpdate = 1;
		}
	}
	return 0;
}
//
int8_t PrintCircleColor(uint8_t WhichChannel,graphic_color_tpye_e NextColor)
{//ʹ��ͨ��8��7��ͼ����Ϊͼ��ͨ��
	if(WhichChannel > 7)
		return 1;

	if(Judge_GraphChannelColor[1][WhichChannel] != NextColor)
	{
		Judge_GraphChannelColor[1][WhichChannel] = NextColor;
		Channel[8].NeedUpdate = 1;
	}
}

//����ֵ��-1��ʾ���ܳ�ʼ����0��ʾ��ʼ���ɹ�
void DefaultGraphData(graphic_data_struct_t *GraphData_t,uint8_t *GraphName)
{
	GraphData_t->graphic_name[0] = GraphName[0];
	GraphData_t->graphic_name[1] = GraphName[1];
	GraphData_t->graphic_name[2] = GraphName[2];
	GraphData_t->operate_tpye =	AddGraph;
	GraphData_t->graphic_tpye = Line;
	GraphData_t->layer = 1;
	GraphData_t->color = Green;
	GraphData_t->start_angle = 50;
	GraphData_t->end_angle = 180;
	GraphData_t->width = 2;
	GraphData_t->start_x = 840;
	GraphData_t->start_y = 540;
	GraphData_t->radius = 300;
	GraphData_t->end_x = 1080;
	GraphData_t->end_y = 540;	
}
//
void Judge_DrawInit(uint16_t senderID,uint16_t receiverID)
{
	Judge_DrawBuff.interactive_header_data.data_cmd_id = 0x0101;
	Judge_DrawBuff.interactive_header_data.sender_ID = senderID;
	Judge_DrawBuff.interactive_header_data.receiver_ID = receiverID;
	
//	((ext_student_interactive_all_data_t*)JudgeTXBuff)->interactive_header_data.data_cmd_id = 0x0101;//����ID��0101��1��ͼ�Σ�data����21
//	((ext_student_interactive_all_data_t*)JudgeTXBuff)->interactive_header_data.sender_ID = senderID;
//	((ext_student_interactive_all_data_t*)JudgeTXBuff)->interactive_header_data.receiver_ID = receiverID;
	
//	JudgeTXBuff[HEADER_LEN + CMD_LEN + 2] = senderID % 256;//16���������ȴ��8λ���ٴ��8λ
//    JudgeTXBuff[HEADER_LEN + CMD_LEN + 3] = senderID / 256;
//	
//	JudgeTXBuff[HEADER_LEN + CMD_LEN + 4] = receiverID % 256;
//    JudgeTXBuff[HEADER_LEN + CMD_LEN + 5] = receiverID / 256;
}


//
void Draw_EqualHeightLine_Vice(uint8_t *Name,uint16_t Position_Y,uint16_t Length_L,uint16_t Length_S,uint16_t Length_V,uint8_t HasExi)
{
	graphic_data_struct_t GraphData;
	
	DefaultGraphData(&GraphData, Name);
	GraphData.width = Judge_Equ_Line_All_Width;
	GraphData.color = Judge_Equ_Line_All_Color;
	
	if(HasExi == 1)
		GraphData.operate_tpye = ReviseGraph;
	
	GraphData.start_x = Judge_Equ_Line_ALL_Position_X - Length_L / 2.0;
	GraphData.start_y = Position_Y;
	GraphData.end_x = Judge_Equ_Line_ALL_Position_X + Length_L / 2.0 ;
	GraphData.end_y = Position_Y;
	AddGraphToBuff(&GraphData);//������
	
//	GraphData.graphic_name[2] = '2';
//	GraphData.start_x = Judge_Equ_Line_ALL_Position_X - Length_L / 2.0;
//	GraphData.start_y = Position_Y + Length_V / 2.0;
//	GraphData.end_x = Judge_Equ_Line_ALL_Position_X - Length_L / 2.0 ;
//	GraphData.end_y = Position_Y - Length_V / 2.0;
//	AddGraphToBuff(&GraphData);//����߶�����
//	
//	GraphData.graphic_name[2] = '3';
//	GraphData.start_x = Judge_Equ_Line_ALL_Position_X + Length_L / 2.0;
//	GraphData.start_y = Position_Y - Length_V / 2.0;
//	GraphData.end_x = Judge_Equ_Line_ALL_Position_X + Length_L / 2.0 ;
//	GraphData.end_y = Position_Y + Length_V / 2.0;
//	AddGraphToBuff(&GraphData);//���ұ߶�����
	
	GraphData.graphic_name[2] = '4';
	GraphData.start_x = Judge_Equ_Line_ALL_Position_X - Length_S / 2.0;
	GraphData.start_y = Position_Y + Length_V / 2.0;
	GraphData.end_x = Judge_Equ_Line_ALL_Position_X - Length_S / 2.0 ;
	GraphData.end_y = Position_Y - Length_V / 2.0;
	AddGraphToBuff(&GraphData);//������
	
	GraphData.graphic_name[2] = '5';
	GraphData.start_x = Judge_Equ_Line_ALL_Position_X + Length_S / 2.0;
	GraphData.start_y = Position_Y + Length_V / 2.0;
	GraphData.end_x = Judge_Equ_Line_ALL_Position_X + Length_S / 2.0 ;
	GraphData.end_y = Position_Y - Length_V / 2.0;
	AddGraphToBuff(&GraphData);//������
	
	GraphData.graphic_name[2] = '6';
	GraphData.start_x = Judge_Equ_Line_ALL_Position_X;
	GraphData.start_y = Position_Y + Length_V / 4.0;
	GraphData.end_x = Judge_Equ_Line_ALL_Position_X;
	GraphData.end_y = Position_Y - Length_V / 4.0;
	AddGraphToBuff(&GraphData);//�м������
	
	SendGraphBuffData('G');
	
	Judge_Delay_ms(200);
	
	
}
//
void Draw_HorizontalInit(void)
{//���̻�������
	graphic_data_struct_t GraphData;
	
	DefaultGraphData(&GraphData, (uint8_t*)"HO1");
	GraphData.width = JUDGE_ENGINEER_ANOTHER_1_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_1_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_1_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_1_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_1_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_1_END_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '2';
	GraphData.width = JUDGE_ENGINEER_ANOTHER_2_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_2_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_2_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_2_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_2_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_2_END_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '3';
	GraphData.width = JUDGE_ENGINEER_ANOTHER_3_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_3_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_3_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_3_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_3_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_3_END_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.width = JUDGE_ENGINEER_ANOTHER_4_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_4_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_4_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_4_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_4_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_4_END_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '5';
	GraphData.width = JUDGE_ENGINEER_ANOTHER_5_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_5_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_5_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_5_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_5_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_5_END_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '6';
	GraphData.width = JUDGE_ENGINEER_ANOTHER_6_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_6_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_6_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_6_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_6_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_6_END_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '7';
	GraphData.width = JUDGE_ENGINEER_ANOTHER_7_WIDTH;
	GraphData.color = JUDGE_ENGINEER_ANOTHER_7_COLOR;
	GraphData.start_x = JUDGE_ENGINEER_ANOTHER_7_START_X;
	GraphData.start_y = JUDGE_ENGINEER_ANOTHER_7_START_Y;
	GraphData.end_x = JUDGE_ENGINEER_ANOTHER_7_END_X;
	GraphData.end_y = JUDGE_ENGINEER_ANOTHER_7_END_Y;
	AddGraphToBuff(&GraphData);
	SendGraphBuffData('G');
	
	Judge_Delay_ms(200);
}
//�������ݳ�ʼ��
void Draw_CapicityInit(void)
{
	graphic_data_struct_t GraphData;
	
	if(judge_recv_mesg.robotState.robot_id != RedEngineer && judge_recv_mesg.robotState.robot_id != RedAirplane
			&& judge_recv_mesg.robotState.robot_id != BlueEngineer && judge_recv_mesg.robotState.robot_id != BlueAirplane)
	{//���˻������̲�������
	
		DefaultGraphData(&GraphData, (uint8_t*)"CP1");
		GraphData.color = Cyan;
		GraphData.graphic_tpye = Rectangle;
		GraphData.width = RECTANGLE_WIDTH;
		GraphData.start_x = POSITION_X_CAP - RECTANGLE_WIDTH/2;
		GraphData.start_y = POSITION_Y_CAP - RECTANGLE_WIDTH/2;
		GraphData.end_x = POSITION_X_CAP + RECTANGLE_LENGTH + RECTANGLE_WIDTH/2;
		GraphData.end_y = POSITION_Y_CAP + RECTANGLE_HEIGHT + RECTANGLE_WIDTH/2;
		GraphData.layer = 2;
		AddGraphToBuff(&GraphData);//�߿�
		
	//	DefaultGraphData(&GraphData, (uint8_t*)"CP2");
	//	GraphData.color = Cyan;
	//	GraphData.width = 20;
	//	GraphData.start_x = POSITION_X_CAP + RECTANGLE_LENGTH + RECTANGLE_WIDTH/2.0;
	//	GraphData.start_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
	//	GraphData.end_x = GraphData.start_x + 20 ;
	//	GraphData.end_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
	//	AddGraphToBuff(&GraphData);//����Ҳ�ͷ
		
		DefaultGraphData(&GraphData, (uint8_t*)"CP3");
		GraphData.layer = 2;
		GraphData.color = Green;
		GraphData.width = RECTANGLE_HEIGHT;
		GraphData.start_x = POSITION_X_CAP;
		GraphData.start_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
		GraphData.end_x = POSITION_X_CAP + RECTANGLE_LENGTH;
		GraphData.end_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
		AddGraphToBuff(&GraphData);//����ڲ�����
		
		if(VOLTAGE_DONT_USE == 0)
		{
			float Voltage_Temp = 24.0;
			
			DefaultGraphData(&GraphData, (uint8_t*)"CP4");
			GraphData.layer = 2;
			GraphData.start_angle = CHAR_SIZE_VOLTAGE_2;
			GraphData.width = WIDTH_VOLTAGE_2;
			GraphData.graphic_tpye = GraphFloat;
			GraphData.end_angle = 2;//С������Чλ��
			GraphData.start_x = POSITION_X_CAP + RECTANGLE_LENGTH + RECTANGLE_WIDTH/2.0;
			GraphData.start_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
			memcpy((uint8_t*)&GraphData + 11,(uint8_t*)&Voltage_Temp,4);
			AddGraphToBuff(&GraphData);
		}
		SendGraphBuffData('G');
	}
	else if(judge_recv_mesg.robotState.robot_id == RedEngineer || judge_recv_mesg.robotState.robot_id == BlueEngineer)
	{//���̣��ó������ݵ����ͳ������ݵ���������ʾ���ӵ��ƶ��͸߶�
		DefaultGraphData(&GraphData, (uint8_t*)"EN1");
		GraphData.layer = 3;
		GraphData.color = JUDGE_ENGINEER_LADDER_COLOR_ALL;
		GraphData.width = JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH;
		GraphData.start_x = JUDGE_ENGINEER_LADDER_POSITION_X;
		GraphData.start_y = JUDGE_ENGINEER_LADDER_POSITION_Y - JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH / 2.0;
		GraphData.end_x = JUDGE_ENGINEER_LADDER_POSITION_X;
		GraphData.end_y = JUDGE_ENGINEER_LADDER_POSITION_Y + JUDGE_ENGINEER_LADDER_HEIGHT_ALL + JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH / 2.0;
		AddGraphToBuff(&GraphData);//����������
		
		GraphData.graphic_name[2] = '2';
		GraphData.start_x = JUDGE_ENGINEER_LADDER_POSITION_X + JUDGE_ENGINEER_LADDER_SPACE;
		GraphData.start_y = JUDGE_ENGINEER_LADDER_POSITION_Y - JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH / 2.0;
		GraphData.end_x = JUDGE_ENGINEER_LADDER_POSITION_X + JUDGE_ENGINEER_LADDER_SPACE;
		GraphData.end_y = JUDGE_ENGINEER_LADDER_POSITION_Y + JUDGE_ENGINEER_LADDER_HEIGHT_ALL + JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH / 2.0;
		AddGraphToBuff(&GraphData);//�����Ҳ����
		
		GraphData.graphic_name[2] = '3';
		GraphData.color = JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_COLOR;
		GraphData.width = JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH;
		GraphData.start_x = JUDGE_ENGINEER_LADDER_POSITION_X + JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH / 2.0;
		GraphData.start_y = JUDGE_ENGINEER_LADDER_POSITION_Y;
		GraphData.end_x = JUDGE_ENGINEER_LADDER_POSITION_X + JUDGE_ENGINEER_LADDER_SPACE - JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH / 2.0;
		GraphData.end_y = JUDGE_ENGINEER_LADDER_POSITION_Y;
		AddGraphToBuff(&GraphData);//�����м����
		
		/////////////////////////���Ƹ˶�����
		GraphData.graphic_name[2] = '4';
		GraphData.color = JUDGE_ENGINEER_LINEAR_COLOR;
		GraphData.width = JUDGE_ENGINEER_LINEAR_WIDTH;
		GraphData.start_x = JUDGE_ENGINEER_LINEAR_LEFT_START_X;
		GraphData.start_y = JUDGE_ENGINEER_LINEAR_LEFT_START_Y;
		GraphData.end_x = JUDGE_ENGINEER_LINEAR_LEFT_END_X;
		GraphData.end_y = JUDGE_ENGINEER_LINEAR_LEFT_END_Y;
		AddGraphToBuff(&GraphData);
		
		GraphData.graphic_name[2] = '5';
		GraphData.start_x = JUDGE_ENGINEER_LINEAR_RIGHT_1_START_X;
		GraphData.start_y = JUDGE_ENGINEER_LINEAR_RIGHT_1_START_Y;
		GraphData.end_x = JUDGE_ENGINEER_LINEAR_RIGHT_1_END_X;
		GraphData.end_y = JUDGE_ENGINEER_LINEAR_RIGHT_1_END_Y;
		AddGraphToBuff(&GraphData);
		
		GraphData.graphic_name[2] = '6';
		GraphData.start_x = JUDGE_ENGINEER_LINEAR_RIGHT_2_START_X;
		GraphData.start_y = JUDGE_ENGINEER_LINEAR_RIGHT_2_START_Y;
		GraphData.end_x = JUDGE_ENGINEER_LINEAR_RIGHT_2_END_X;
		GraphData.end_y = JUDGE_ENGINEER_LINEAR_RIGHT_2_END_Y;
		AddGraphToBuff(&GraphData);
		
		GraphData.graphic_name[2] = '7';
		GraphData.start_x = JUDGE_ENGINEER_LINEAR_RIGHT_3_START_X;
		GraphData.start_y = JUDGE_ENGINEER_LINEAR_RIGHT_3_START_Y;
		GraphData.end_x = JUDGE_ENGINEER_LINEAR_RIGHT_3_END_X;
		GraphData.end_y = JUDGE_ENGINEER_LINEAR_RIGHT_3_END_Y;
		AddGraphToBuff(&GraphData);
		
		
		SendGraphBuffData('G');
	}
		
}
//
//�βα�RobotLevel�����˵ȼ�
void Draw_EqualHeightLine(uint8_t RobotLevel)
{//ִ��һ�θú�����Ҫ��ʱ1.4�������ҡ�����ִ��ʱ���������ݡ�ͨ����YAW�������
	static uint8_t HadExisted_1 = 0;
	static uint8_t HadExisted_2 = 0;
	static uint8_t HadExisted_3 = 0;
	static uint8_t HadExisted_4 = 0;
	static uint8_t HadExisted_5 = 0;
	static uint8_t HadExisted_6 = 0;
	static uint8_t HadExisted_7 = 0;
	
	IsDrawEqualLine = 1;
	
	Judge_Delay_ms(200);
	
	if(CountGraph != 0)
	{
		SendGraphBuffData('G');
		Judge_Delay_ms(200);
	}
	
	switch(RobotLevel)
	{
		case 1:
		{
			if(Judge_Equ_Line_1_1_length_L != 0 || HadExisted_1 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"111",Judge_Equ_Line_1_1_Position_Y,Judge_Equ_Line_1_1_length_L,Judge_Equ_Line_1_1_length_S,Judge_Equ_Line_1_1_Length_Vertical,HadExisted_1);
				HadExisted_1 = 1;
			}
			
			if(Judge_Equ_Line_1_2_length_L != 0 || HadExisted_2 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"121",Judge_Equ_Line_1_2_Position_Y,Judge_Equ_Line_1_2_length_L,Judge_Equ_Line_1_2_length_S,Judge_Equ_Line_1_2_Length_Vertical,HadExisted_2);
				HadExisted_2 = 1;
			}
			
			if(Judge_Equ_Line_1_3_length_L != 0 || HadExisted_3 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"131",Judge_Equ_Line_1_3_Position_Y,Judge_Equ_Line_1_3_length_L,Judge_Equ_Line_1_3_length_S,Judge_Equ_Line_1_3_Length_Vertical,HadExisted_3);
				HadExisted_3 = 1;
			}
			
			if(Judge_Equ_Line_1_4_length_L != 0 || HadExisted_4 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"141",Judge_Equ_Line_1_4_Position_Y,Judge_Equ_Line_1_4_length_L,Judge_Equ_Line_1_4_length_S,Judge_Equ_Line_1_4_Length_Vertical,HadExisted_4);
				HadExisted_4 = 1;
				
			}
			
			if(Judge_Equ_Line_1_5_length_L != 0 || HadExisted_5 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"151",Judge_Equ_Line_1_5_Position_Y,Judge_Equ_Line_1_5_length_L,Judge_Equ_Line_1_5_length_S,Judge_Equ_Line_1_5_Length_Vertical,HadExisted_5);
				HadExisted_5 = 1;
			}
			
			
			if(Judge_Equ_Line_1_6_length_L != 0 || HadExisted_6 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"161",Judge_Equ_Line_1_6_Position_Y,Judge_Equ_Line_1_6_length_L,Judge_Equ_Line_1_6_length_S,Judge_Equ_Line_1_6_Length_Vertical,HadExisted_6);
				HadExisted_6 = 1;
			}
			
			if(Judge_Equ_Line_1_7_length_L != 0 || HadExisted_7 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"171",Judge_Equ_Line_1_7_Position_Y,Judge_Equ_Line_1_7_length_L,Judge_Equ_Line_1_7_length_S,Judge_Equ_Line_1_7_Length_Vertical,HadExisted_7);
				HadExisted_7 = 1;
			}
			
			break;
			
		}
		case 2:
		{
			if(Judge_Equ_Line_2_1_length_L != 0 || HadExisted_1 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"111",Judge_Equ_Line_2_1_Position_Y,Judge_Equ_Line_2_1_length_L,Judge_Equ_Line_2_1_length_S,Judge_Equ_Line_2_1_Length_Vertical,HadExisted_1);
				HadExisted_1 = 1;
			}
			
			if(Judge_Equ_Line_2_2_length_L != 0 || HadExisted_2 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"121",Judge_Equ_Line_2_2_Position_Y,Judge_Equ_Line_2_2_length_L,Judge_Equ_Line_2_2_length_S,Judge_Equ_Line_2_2_Length_Vertical,HadExisted_2);
				HadExisted_2 = 1;
			}
			
			if(Judge_Equ_Line_2_3_length_L != 0 || HadExisted_3 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"131",Judge_Equ_Line_2_3_Position_Y,Judge_Equ_Line_2_3_length_L,Judge_Equ_Line_2_3_length_S,Judge_Equ_Line_2_3_Length_Vertical,HadExisted_3);
				HadExisted_3 = 1;
			}
			
			if(Judge_Equ_Line_2_4_length_L != 0 || HadExisted_4 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"141",Judge_Equ_Line_2_4_Position_Y,Judge_Equ_Line_2_4_length_L,Judge_Equ_Line_2_4_length_S,Judge_Equ_Line_2_4_Length_Vertical,HadExisted_4);
				HadExisted_4 = 1;
			}
			
			if(Judge_Equ_Line_2_5_length_L != 0 || HadExisted_5 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"151",Judge_Equ_Line_2_5_Position_Y,Judge_Equ_Line_2_5_length_L,Judge_Equ_Line_2_5_length_S,Judge_Equ_Line_2_5_Length_Vertical,HadExisted_5);
				HadExisted_5 = 1;
			}
			
			if(Judge_Equ_Line_2_6_length_L != 0 || HadExisted_6 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"161",Judge_Equ_Line_2_6_Position_Y,Judge_Equ_Line_2_6_length_L,Judge_Equ_Line_2_6_length_S,Judge_Equ_Line_2_6_Length_Vertical,HadExisted_6);
				HadExisted_6 = 1;
			}
			
			if(Judge_Equ_Line_2_7_length_L != 0 || HadExisted_7 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"171",Judge_Equ_Line_2_7_Position_Y,Judge_Equ_Line_2_7_length_L,Judge_Equ_Line_2_7_length_S,Judge_Equ_Line_2_7_Length_Vertical,HadExisted_7);
				HadExisted_7 = 1;
			}
			
			break;
		}
		case 3:
		{
			if(Judge_Equ_Line_3_1_length_L != 0 || HadExisted_1 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"111",Judge_Equ_Line_3_1_Position_Y,Judge_Equ_Line_3_1_length_L,Judge_Equ_Line_3_1_length_S,Judge_Equ_Line_3_1_Length_Vertical,HadExisted_1);
				HadExisted_1 = 1;
			}
			
			if(Judge_Equ_Line_3_2_length_L != 0 || HadExisted_2 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"121",Judge_Equ_Line_3_2_Position_Y,Judge_Equ_Line_3_2_length_L,Judge_Equ_Line_3_2_length_S,Judge_Equ_Line_3_2_Length_Vertical,HadExisted_2);
				HadExisted_2 = 1;
			}
			
			if(Judge_Equ_Line_3_3_length_L != 0 || HadExisted_3 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"131",Judge_Equ_Line_3_3_Position_Y,Judge_Equ_Line_3_3_length_L,Judge_Equ_Line_3_3_length_S,Judge_Equ_Line_3_3_Length_Vertical,HadExisted_3);
				HadExisted_3 = 1;
			}
			
			if(Judge_Equ_Line_3_4_length_L != 0 || HadExisted_4 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"141",Judge_Equ_Line_3_4_Position_Y,Judge_Equ_Line_3_4_length_L,Judge_Equ_Line_3_4_length_S,Judge_Equ_Line_3_4_Length_Vertical,HadExisted_4);
				HadExisted_4 = 1;
			}
			
			if(Judge_Equ_Line_3_5_length_L != 0 || HadExisted_5 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"151",Judge_Equ_Line_3_5_Position_Y,Judge_Equ_Line_3_5_length_L,Judge_Equ_Line_3_5_length_S,Judge_Equ_Line_3_5_Length_Vertical,HadExisted_5);
				HadExisted_5 = 1;
			}
			
			if(Judge_Equ_Line_3_6_length_L != 0 || HadExisted_6 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"161",Judge_Equ_Line_3_6_Position_Y,Judge_Equ_Line_3_6_length_L,Judge_Equ_Line_3_6_length_S,Judge_Equ_Line_3_6_Length_Vertical,HadExisted_6);
				HadExisted_6 = 1;
			}
			
			if(Judge_Equ_Line_3_7_length_L != 0 || HadExisted_7 == 1)
			{
				Draw_EqualHeightLine_Vice((uint8_t*)"171",Judge_Equ_Line_3_7_Position_Y,Judge_Equ_Line_3_7_length_L,Judge_Equ_Line_3_7_length_S,Judge_Equ_Line_3_7_Length_Vertical,HadExisted_7);
				HadExisted_7 = 1;
			}
			
			break;
		}
	}
	
	IsDrawEqualLine = 0;
}

void Draw_GraphChannel_StrInit_Vice(uint8_t *Name,uint16_t Position_X,uint16_t Position_Y,uint8_t* DisplayStr)
{//ͼ��1
	graphic_data_struct_t GraphData;
	uint8_t StrTemp[30] = {0};
	
	DefaultGraphData(&GraphData, Name);
	GraphData.graphic_tpye = GraphChar;
	GraphData.color = GRAPH_CHANNEL_STR_COLOR_ALL;
	GraphData.width = GRAPH_CHANNEL_STR_WIDTH_ALL;
	GraphData.start_angle = GRAPH_CHANNEL_STR_LARGE_ALL;
	GraphData.end_angle = strlen((char*)DisplayStr);
	GraphData.start_x = Position_X;
	GraphData.start_y = Position_Y;
	
	AddGraphToBuff(&GraphData);
	memcpy(StrTemp,DisplayStr,strlen((char*)DisplayStr));
	memcpy(&Judge_DrawBuff.Data[15],StrTemp,30);
	CountGraph = 3;
	SendGraphBuffData('S');
	
	Judge_Delay_ms(200);
}
//
void Draw_GraphChannel_StrInit(void)
{//��ʼ��ɫ��˵���ַ���
	static uint16_t SendTime_ms = 0;
	
	while(Judge_TxDataBuff.NowDMASendIng != 0 || NowSendingGraph != 0)
	{
		++ SendTime_ms;
		if(SendTime_ms >= 200)
		{
			SendTime_ms = 0;
			Judge_TxDataBuff.NowDMASendIng = 0;
			NowSendingGraph = 0;
		}
		else
		{
			Judge_Delay_ms(1);
		}
	}
	
	if(GRAPH_USE_THIS_GRAPH_8_1)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M81",GRAPH_CHANNEL_STR_8_1_POSITION_X,GRAPH_CHANNEL_STR_8_1_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_1);
	
	if(GRAPH_USE_THIS_GRAPH_8_2)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M82",GRAPH_CHANNEL_STR_8_2_POSITION_X,GRAPH_CHANNEL_STR_8_2_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_2);
	
	if(GRAPH_USE_THIS_GRAPH_8_3)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M83",GRAPH_CHANNEL_STR_8_3_POSITION_X,GRAPH_CHANNEL_STR_8_3_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_3);
	
	if(GRAPH_USE_THIS_GRAPH_8_4)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M84",GRAPH_CHANNEL_STR_8_4_POSITION_X,GRAPH_CHANNEL_STR_8_4_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_4);
	
	if(GRAPH_USE_THIS_GRAPH_8_5)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M85",GRAPH_CHANNEL_STR_8_5_POSITION_X,GRAPH_CHANNEL_STR_8_5_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_5);
	
	if(GRAPH_USE_THIS_GRAPH_8_6)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M86",GRAPH_CHANNEL_STR_8_6_POSITION_X,GRAPH_CHANNEL_STR_8_6_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_6);
	
	if(GRAPH_USE_THIS_GRAPH_8_7)
		Draw_GraphChannel_StrInit_Vice((uint8_t*)"M87",GRAPH_CHANNEL_STR_8_7_POSITION_X,GRAPH_CHANNEL_STR_8_7_POSITION_Y,(uint8_t*)GRAPH_CHANNEL_STR_8_7);
	
	
}
//
//����Ļ�ϻ�����ߴ���
void Draw_SizeLine(void)
{
	graphic_data_struct_t GraphData;
	
	DefaultGraphData(&GraphData, (uint8_t*)"SZ1");
	GraphData.color = Judge_Car_Size_Line_Color;
	GraphData.width = Judge_Car_Size_Line_Width;
	GraphData.start_x = 960 - Judge_Car_Size_BottomWidthMax / 2.0;
	GraphData.start_y = 0;
	GraphData.end_x = 960 - Judge_Car_Size_TopWidthMax / 2.0 ;
	GraphData.end_y = Judge_Car_Size_LineHign;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '2';
	GraphData.start_x = 960 - Judge_Car_Size_TopWidthMax / 2.0;
	GraphData.start_y = Judge_Car_Size_LineHign;
	GraphData.end_x = 960 + Judge_Car_Size_TopWidthMax / 2.0 ;
	GraphData.end_y = Judge_Car_Size_LineHign;
	//AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '3';
	GraphData.start_x = 960 + Judge_Car_Size_TopWidthMax / 2.0;
	GraphData.start_y = Judge_Car_Size_LineHign;
	GraphData.end_x = 960 + Judge_Car_Size_BottomWidthMax / 2.0 ;
	GraphData.end_y = 0;
	AddGraphToBuff(&GraphData);
	
	GraphData.color = Yellow;
	
	GraphData.graphic_name[2] = '4';
	GraphData.start_x = 960 - Judge_Car_Size_BottomWidthMin / 2.0;
	GraphData.start_y = 0;
	GraphData.end_x = 960 - Judge_Car_Size_TopWidthMin / 2.0 ;
	GraphData.end_y = Judge_Car_Size_LineHign;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '5';
	GraphData.start_x = 960 + Judge_Car_Size_TopWidthMin / 2.0;
	GraphData.start_y = Judge_Car_Size_LineHign;
	GraphData.end_x = 960 + Judge_Car_Size_BottomWidthMin / 2.0 ;
	GraphData.end_y = 0;
	AddGraphToBuff(&GraphData);
	
	/////////////////////׼��
	GraphData.graphic_name[2] = '6';
	GraphData.color = JUDGE_ENGINEER_AIM_COLOR;
	GraphData.width = JUDGE_ENGINEER_AIM_WIDTH;
	GraphData.start_x = JUDGE_ENGINEER_AIM_X - JUDGE_ENGINEER_AIM_LENGTH_H / 2.0;
	GraphData.start_y = JUDGE_ENGINEER_AIM_Y;
	GraphData.end_x = JUDGE_ENGINEER_AIM_X + JUDGE_ENGINEER_AIM_LENGTH_H / 2.0;
	GraphData.end_y = JUDGE_ENGINEER_AIM_Y;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '7';
	GraphData.start_x = JUDGE_ENGINEER_AIM_X ;
	GraphData.start_y = JUDGE_ENGINEER_AIM_Y - JUDGE_ENGINEER_AIM_LENGTH_V / 2.0;
	GraphData.end_x = JUDGE_ENGINEER_AIM_X;
	GraphData.end_y = JUDGE_ENGINEER_AIM_Y + JUDGE_ENGINEER_AIM_LENGTH_V / 2.0;
	AddGraphToBuff(&GraphData);
	
	SendGraphBuffData('G');
	Judge_Delay_ms(200);
	
}


void Draw_Int32InScreen(uint16_t Position_x,uint16_t Position_y, int32_t UserNum,uint8_t *Name)
{
	graphic_data_struct_t GraphData;
	
	DefaultGraphData(&GraphData, Name);
	GraphData.color = Green;
	GraphData.layer = 1;
	GraphData.graphic_tpye = GraphInt;
	GraphData.start_angle = 10;//�����С
	GraphData.width = 1;
	GraphData.start_x = Position_x ;
	GraphData.start_y = Position_y;
	memcpy((uint8_t*)&GraphData + 11,(uint8_t*)&UserNum,4);

	AddGraphToBuff(&GraphData);
	GraphData.operate_tpye = ReviseGraph;
	AddGraphToBuff(&GraphData);
	
	SendGraphBuffData('G');
	
}

void Judge_UseUART_Function_Name(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef	DMA_InitStructure;
	//uint8_t DMA_PreStart = 0;
	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE); 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,ENABLE);
//	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_DMA1, ENABLE);
	
	RCC_AHB1PeriphClockCmd(Judge_UseGPIO_GPIO_PeriphClock,ENABLE); 
	RCC_APB1PeriphClockCmd(Judge_UseUART_PeriphClock,ENABLE);
	RCC_AHB1PeriphClockCmd(Judge_UseDMA_PeriphClock_RX, ENABLE);
	RCC_AHB1PeriphClockCmd(Judge_UseDMA_PeriphClock_TX, ENABLE);	
	
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_UART8);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_UART8);
	
	GPIO_PinAFConfig(Judge_UseGPIO_GPIO_Typedef_Name,Judge_UseGPIO_GPIO_PINSource_TX,Judge_UseUART_GPIOAF_Name);
	GPIO_PinAFConfig(Judge_UseGPIO_GPIO_Typedef_Name,Judge_UseGPIO_GPIO_PINSource_RX,Judge_UseUART_GPIOAF_Name);
	
	GPIO_InitStructure.GPIO_Pin = Judge_UseGPIO_GPIO_GPIO_Pin_TX | Judge_UseGPIO_GPIO_GPIO_Pin_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(Judge_UseGPIO_GPIO_Typedef_Name,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//	USART_Init(UART8, &USART_InitStructure);	
//	USART_Cmd(UART8, ENABLE); 
//	USART_ClearFlag(UART8, USART_FLAG_TC);
	
	USART_Init(Judge_UseUART_Typedef_Name, &USART_InitStructure);	
	USART_Cmd(Judge_UseUART_Typedef_Name, ENABLE); 
	USART_ClearFlag(Judge_UseUART_Typedef_Name, USART_FLAG_TC);
	
//	USART_ITConfig(UART8, USART_IT_IDLE, ENABLE);//���������ж�
	USART_ITConfig(Judge_UseUART_Typedef_Name, USART_IT_IDLE, ENABLE);//���������ж�
//  NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
	NVIC_InitStructure.NVIC_IRQChannel = Judge_UseUART_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_DMACmd(Judge_UseUART_Typedef_Name,USART_DMAReq_Rx,ENABLE);//��������DMA
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannel = Judge_UseDMA_IRQChannel_RX;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
//	DMA_DeInit(DMA1_Stream6);
	DMA_DeInit(Judge_UseDMA_Stream_Typedef_Name_RX);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_5;//ͨ��ѡ��
	DMA_InitStructure.DMA_Channel = Judge_UseDMA_Channel_RX;//ͨ��ѡ��
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(UART8->DR);//DMA�����ַ����DR���ж������൱�ڽ��գ���DR����д�����൱�ڷ���
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(Judge_UseUART_Typedef_Name->DR);//DMA�����ַ����DR���ж������൱�ڽ��գ���DR����д�����൱�ڷ���
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Judge_DataBuff.WhichBuffToDMA;//DMA�洢����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢ģʽ
	DMA_InitStructure.DMA_BufferSize = Judge_RecDataBuffDepth;//���ݴ�����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ��ȣ�8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ��ȣ�8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ʹ��ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//������ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//��ʹ��FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;//����FIFO��ֵ��Ч
	DMA_InitStructure.DMA_MemoryBurst = DMA_Mode_Normal;//����DMA�洢��ͻ��ģʽΪ����ģʽ
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
//	DMA_Init(DMA1_Stream6,&DMA_InitStructure);
	DMA_Init(Judge_UseDMA_Stream_Typedef_Name_RX,&DMA_InitStructure);
		
//	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);
//	DMA_Cmd(DMA1_Stream6,ENABLE);
	DMA_ITConfig(Judge_UseDMA_Stream_Typedef_Name_RX,DMA_IT_TC,ENABLE);
	DMA_Cmd(Judge_UseDMA_Stream_Typedef_Name_RX,ENABLE);
	
	/////////////////////���濪ʼ����DMA�ķ��ͣ�������0��ͨ��5
//	USART_DMACmd(UART8,USART_DMAReq_Tx,ENABLE);//��������DMA
	USART_DMACmd(Judge_UseUART_Typedef_Name,USART_DMAReq_Tx,ENABLE);//��������DMA
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannel = Judge_UseDMA_IRQChannel_TX;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
//	DMA_DeInit(DMA1_Stream0);
	DMA_DeInit(Judge_UseDMA_Stream_Typedef_Name_TX);	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_5;//ͨ��ѡ��
	DMA_InitStructure.DMA_Channel = Judge_UseDMA_Channel_TX;//ͨ��ѡ��
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(UART8->DR); //DMA�����ַ����DR���ж������൱�ڽ��գ���DR����д�����൱�ڷ���
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(Judge_UseUART_Typedef_Name->DR); //DMA�����ַ����DR���ж������൱�ڽ��գ���DR����д�����൱�ڷ���
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Judge_TxDataBuff.WhichBuffToDMA;//DMA�洢����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//���赽�洢ģʽ
	DMA_InitStructure.DMA_BufferSize = 200;//���ݴ�����
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
//	DMA_Init(DMA1_Stream0,&DMA_InitStructure);
	DMA_Init(Judge_UseDMA_Stream_Typedef_Name_TX,&DMA_InitStructure);
		
//	DMA_ITConfig(DMA1_Stream0,DMA_IT_TC,ENABLE);
//	DMA_Cmd(DMA1_Stream0,DISABLE);
	DMA_ITConfig(Judge_UseDMA_Stream_Typedef_Name_TX,DMA_IT_TC,ENABLE);
	DMA_Cmd(Judge_UseDMA_Stream_Typedef_Name_TX,DISABLE);
}

void Judge_SetDMASend(uint8_t* Addr,uint16_t HowMany)
{
//	DMA_Cmd(DMA1_Stream0,DISABLE);
	DMA_Cmd(Judge_UseDMA_Stream_Typedef_Name_TX,DISABLE);
//	while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE)
	while(DMA_GetCmdStatus(Judge_UseDMA_Stream_Typedef_Name_TX) != DISABLE)
	{
		//ȷ��DMA���Ա�����  
	}
//	DMA1_Stream0->M0AR = (uint32_t)Addr;
//	DMA_SetCurrDataCounter(DMA1_Stream0,HowMany);
//	DMA_Cmd(DMA1_Stream0, ENABLE);                      //����DMA���� 
	Judge_UseDMA_Stream_Typedef_Name_TX->M0AR = (uint32_t)Addr;
	DMA_SetCurrDataCounter(Judge_UseDMA_Stream_Typedef_Name_TX,HowMany);
	DMA_Cmd(Judge_UseDMA_Stream_Typedef_Name_TX, ENABLE);                      //����DMA���� 
	Judge_TxDataBuff.NowDMASendIng = 1;
}



void Judge_Delay_us(uint32_t Time_us)
{
	volatile uint32_t Temp = 0;
	volatile uint32_t Temp_1 = 0;
	volatile uint32_t Temp_2 = 0;
	for(Temp = 0; Temp < Time_us ; ++ Temp)
	{
		for(Temp_1 = 0; Temp_1 < 14000; ++ Temp_1)
		{
			Temp_2 = Temp_2 + 1;
		}		
	}
	
}

void Judge_Delay_ms(uint32_t Time_ms)
{
	volatile uint32_t HasDelayed_ms = 0;
	for(HasDelayed_ms = 0; HasDelayed_ms < Time_ms; ++ HasDelayed_ms)
	{
		Judge_Delay_us(1);
	}	
}

void JudgeInit(void) 
{
	volatile ext_game_robot_status_t State;
	uint32_t TimeTemp = 1;
	
	Judge_DataBuff.WhichBuffToDMA = Judge_DataBuff.Buff_0;
	Judge_DataBuff.WhichBuffToCPU = Judge_DataBuff.Buff_0;
	
	Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
	Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;	
	Judge_TxDataBuff.HowLongWillSend_Buff0 = 0;
	Judge_TxDataBuff.HowLongWillSend_Buff0 = 1;
	Judge_UseUART_Function_Name();
	while(Judge_GetFlag(ROBOT_STATE_ID) < 10)
	{
		++ TimeTemp;
		Judge_Delay_ms(10);
		if(TimeTemp % 500 == 0)
		{//����ϵͳ���ߴ���
			if(Judge_GetFlag(0x4000) == 0)
			{
				printf("����ϵͳ���ߴ���");
				//if(TimeTemp == 3000)
					break;
			}
			else 
			{
				//printf("����ϵͳ��������");
				if(TimeTemp == 3000)
					break;
				break;
			}
			//����ϵͳ����ӿ�
		}
	}
	State = *Judge_GetRobotState();
	SelfRobot = State.robot_id;
	switch(State.robot_id)
	{
		case RedHero:
		{
			Judge_DrawInit(RedHero,RedHeroOperator);
			SelfOperator = RedHeroOperator;
		}
		break;
		case RedEngineer:
		{
			Judge_DrawInit(RedEngineer,RedEngineerOperator);
			SelfOperator = RedEngineerOperator;
		}
		break;
		case RedInfantry1:
		{
			Judge_DrawInit(RedInfantry1,RedInfantry1Operator);
			SelfOperator = RedInfantry1Operator;
		}
		break;
		case RedInfantry2:
		{
			Judge_DrawInit(RedInfantry2,RedInfantry2Operator);
			SelfOperator = RedInfantry2Operator;
		}
		break;
		case RedInfantry3:
		{
			Judge_DrawInit(RedInfantry3,RedInfantry3Operator);
			SelfOperator = RedInfantry3Operator;
		}
		break;
		case RedAirplane:
		{
			Judge_DrawInit(RedAirplane,RedAirplaneOperator);
			SelfOperator = RedAirplaneOperator;
		}
		break;
		case RedSentry:
		{//�ڱ�
			//Judge_DrawInit(RedHero,RedHeroOperator);
			SelfOperator = 0;
		}
		break;
		case RedRadar:
		{//�״�
			//Judge_DrawInit(RedHero,RedHeroOperator);
			SelfOperator = 0;
		}
		break;
		case BlueHero:
		{
			Judge_DrawInit(BlueHero,BlueHeroOperator);
			SelfOperator = BlueHeroOperator;
		}
		break;
		case BlueEngineer:
		{
			Judge_DrawInit(BlueEngineer,BlueEngineerOperator);
			SelfOperator = BlueEngineerOperator;
		}
		break;
		case BlueInfantry1:
		{
			Judge_DrawInit(BlueInfantry1,BlueInfantry1Operator);
			SelfOperator = BlueInfantry1Operator;
		}
		break;
		case BlueInfantry2:
		{
			Judge_DrawInit(BlueInfantry2,BlueInfantry2Operator);
			SelfOperator = BlueInfantry2Operator;
		}
		break;
		case BlueInfantry3:
		{
			Judge_DrawInit(BlueInfantry3,BlueInfantry3Operator);
			SelfOperator = BlueInfantry3Operator;
		}
		break;
		case BlueAirplane:
		{
			Judge_DrawInit(BlueAirplane,BlueAirplaneOperator);
			SelfOperator = BlueAirplaneOperator;
		}
		break;
		case BlueSentry:
		{//�ڱ�
			//Judge_DrawInit(RedHero,RedHeroOperator);
			SelfOperator = 0;
		}
		break;
		case BlueRadar:
		{//�״�
			//Judge_DrawInit(RedHero,RedHeroOperator);
			SelfOperator = 0;
		}
		break;	
	}	
}

void Judge_SwapDMABuff(void)
{//����DMA��BUFF
//	if(Judge_DataBuff.WhichBuffToDMA == Judge_DataBuff.Buff_0)
//	{
//		Judge_DataBuff.WhichBuffToDMA = Judge_DataBuff.Buff_1;
//		Judge_DataBuff.WhichBuffToCPU = Judge_DataBuff.Buff_0;
//		//ԭ����ΪֻҪ������Judge_DataBuff.WhichBuffToDMA��ֵ��DMA��BUFF��ַ�ͻ���֮���ģ���������̫�����ˣ�
//		//DMA��BUFF�ڳ�ʼ����Ͳ����ˣ���ʹ�������ʼ����һ��ָ���ϣ����ٸ����ָ��DMA��BUFFָ��Ҳ������ˣ�
//		//������ֱ�Ӹ��ļĴ�����ֵ
//		//���ֻ��ǲ��ܸı�DMA��Ŀ��BUFF��ַ��
//		
//		DMA1_Stream6->M0AR = (uint32_t)Judge_DataBuff.WhichBuffToDMA;
//	}
//	else if(Judge_DataBuff.WhichBuffToDMA == Judge_DataBuff.Buff_1)
//	{
//		Judge_DataBuff.WhichBuffToDMA = Judge_DataBuff.Buff_0;
//		Judge_DataBuff.WhichBuffToCPU = Judge_DataBuff.Buff_1;
//		//ԭ����ΪֻҪ������Judge_DataBuff.WhichBuffToDMA��ֵ��DMA��BUFF��ַ�ͻ���֮���ģ���������̫�����ˣ�
//		//DMA��BUFF�ڳ�ʼ����Ͳ����ˣ���ʹ�������ʼ����һ��ָ���ϣ����ٸ����ָ��DMA��BUFFָ��Ҳ������ˣ�
//		//������ֱ�Ӹ��ļĴ�����ֵ
//		DMA1_Stream6->M0AR = (uint32_t)Judge_DataBuff.WhichBuffToDMA;
//	}
	
	
	
	return;
}

uint8_t* Judge_FindTureFrame(uint8_t *WhereStart)
{//�ӿ�ʼ��ַ���ҵ�һ������Э�����ȷ֡����֡�׵�ַ����
	static uint8_t *LinShiAddr = NULL;
	static uint8_t CRC8_Result = 0;
	static uint16_t CRC16_Result = 0;
	
	LinShiAddr = (uint8_t*)strchr((const char*)WhereStart,0XA5);//��0XA5
	
	if(LinShiAddr == NULL)
	{//˵��û��0XA5�ˣ�����NULL
		return NULL;
	}
	else
	{
		CRC8_Result = get_crc8_check_sum(LinShiAddr,4,CRC8_INIT_NUM);
		if(CRC8_Result == LinShiAddr[4] )
		{//֡ͷУ����ȷ
			CRC16_Result = get_crc16_check_sum(LinShiAddr,7 + (uint16_t)*(uint16_t*)&LinShiAddr[1],CRC16_INIT_NUM);
			if(CRC16_Result == (uint16_t)*(uint16_t*)&LinShiAddr[ 7 + (uint16_t)*(uint16_t*)&LinShiAddr[1] ] )
			{//ȫ֡У����ȷ
				return LinShiAddr;
			}
		}
	}
	return NULL;
}

void Judge_UnpackRecData(uint16_t HowManyDataRec)
{//���յ������ݽ�����judge_recv_mesg
	//static uint16_t WhereFirst_A5	= 0;//�ҳ������֡���棬�ڼ�����ĸ��0xA5
	static uint8_t *HereStartUnpack = NULL;//�洢��һ�γ���A5�ĵ�ַ
	//static JudgeFullFrame_t *Temp;
	static uint32_t tmp;
	HereStartUnpack = Judge_FindTureFrame(Judge_DataBuff.WhichBuffToCPU);
	
	while(HereStartUnpack != NULL)
	{
		//Temp = (JudgeFullFrame_t*)HereStartUnpack;
		switch( ( ( JudgeFullFrame_t* )HereStartUnpack)->frame_cmd_id )
		{
			case GAME_STATE_ID:
			{//����״̬��1Hz��
				memcpy((char*)&judge_recv_mesg.gameState,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_game_state_t));
				++ Judge_UndateFlag.gameState;
			}
			break;
			case GAME_RESUIT_ID:
			{//�������
				memcpy((char*)&judge_recv_mesg.gameResult,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_game_result_t));
				++ Judge_UndateFlag.gameResult;
			}
			break;
			case ROBOT_HP_ID:
			{//������Ѫ�����ݣ�1Hz��
				memcpy((char*)&judge_recv_mesg.robotHP,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_game_robot_HP_t));
				++ Judge_UndateFlag.robotHP;
			}
			break;
//			case DART_FIRE_STATE:
//			{//���ڷ���״̬
//				memcpy((char*)&judge_recv_mesg.DartStatus,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_dart_status_t));
//				++ Judge_UndateFlag.DartStatus;
//			}
			break;
			case GAIN_AND_PUNISHMENT_STATE:
			{//�˹�������ս���ӳ���ͷ���״̬��1HZ
				memcpy((char*)&judge_recv_mesg.BuffDebuffStatus,
						(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,
						sizeof(ext_ICRA_buff_debuff_zone_status_t));
				++ Judge_UndateFlag.BuffDebuffStatus;
			}
			break;
			case FIELD_EVENT_ID:
			{//�����¼���1HZ
				memcpy((char*)&judge_recv_mesg.fieldEvent,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_event_data_t));
				++ Judge_UndateFlag.fieldEvent;
			}
			break;
			case SUPPLY_ACTION_ID:
			{//����վ������ʶ
				memcpy((char*)&judge_recv_mesg.supplyAction,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_supply_projectile_action_t));
				++ Judge_UndateFlag.supplyAction;
			}
			break;
			case JUDGE_WARNING_ID:
			{//���о�������
				memcpy((char*)&judge_recv_mesg.warning,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(referee_warning_t));
				++ Judge_UndateFlag.warning;
			}
			break;
			case DART_FIRE_COUNTDOWN:
			{//���ڷ���ڵ���ʱ��1HZ����
				memcpy((char*)&judge_recv_mesg.DartRemainTime,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_dart_remaining_time_t));
				++ Judge_UndateFlag.DartRemainTime;
			}
			break;
			case ROBOT_STATE_ID:
			{//������״̬��10Hz��
				memcpy((char*)&judge_recv_mesg.robotState,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_game_robot_status_t));
				++ Judge_UndateFlag.robotState;
			}
			break;
			case REALTIME_POWER_ID:
			{//ʵʱ����������50Hz��
				memcpy((char*)&judge_recv_mesg.powerHeat,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_power_heat_data_t));
				++ Judge_UndateFlag.powerHeat;
			}
			break;
			case ROBOT_POSITION_ID:
			{//������λ�ã�10Hz��
				memcpy((char*)&judge_recv_mesg.robotPosition,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_game_robot_pos_t));
				++ Judge_UndateFlag.robotPosition;
			}
			break;
			case ROBOT_BUFF_ID:
			{//����������
				memcpy((char*)&judge_recv_mesg.robotBUFF,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_buff_t));
				++ Judge_UndateFlag.robotBUFF;
			}
			break;
			case DRONE_POWER_ID:
			{//���л���������״̬���ݣ�10HZ��ֻ�п��л��������ط���
				memcpy((char*)&judge_recv_mesg.droneEnergy,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_aerial_robot_energy_t));
				++ Judge_UndateFlag.droneEnergy;
			}
			break;
			case ROBOT_HURT_ID:
			{//�˺�����
				memcpy((char*)&judge_recv_mesg.robotHurt,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_robot_hurt_t));
				++ Judge_UndateFlag.robotHurt;
			}
			break;
			case ROBOT_SHOOT_ID:
			{//�������
				memcpy((char*)&judge_recv_mesg.robotShoot,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_shoot_data_t));
				++ Judge_UndateFlag.robotShoot;
			}
			break;
			case SURPLUS_BULLET_ID:
			{//ʣ���ӵ������ڱ��Ϳ��л����ˣ�
				memcpy((char*)&judge_recv_mesg.bulletRemaining,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_bullet_remaining_t));
				++ Judge_UndateFlag.bulletRemaining;
			}
			break;
			case ROBOT_RFID_STATE:
			{//������RFID״̬��1HZ���ڷ���
				memcpy((char*)&judge_recv_mesg.rfid_status,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_rfid_status_t));
				++ Judge_UndateFlag.rfid_status;
			}
			break;
			case ROBOT_OPERATOR_CMD:
			{//���ڻ����˿ͻ���ָ�����ݣ�10HZ
				memcpy((char*)&judge_recv_mesg.DartClientCmd,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_dart_client_cmd_t));
				++ Judge_UndateFlag.DartClientCmd;
			}
			break;
			case ROBOT_INTERACTIVE_ID:
			{//�����˼佻�������ʹ���
				memset((char*)&judge_recv_mesg.student_interactive_all_data,0,sizeof(ext_student_interactive_all_data_t));
				memcpy((char*)&judge_recv_mesg.student_interactive_all_data,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_student_interactive_all_data_t));
				++ Judge_UndateFlag.student_interactive_all_data;
			}
			break;
			case SELF_CONTROL_INTERACTIVE_ID:
			{///�Զ����������������
				memset((char*)&judge_recv_mesg.self_control_interactive_all_data,0,sizeof(self_control_interactive_all_data_t));
				memcpy((char*)&judge_recv_mesg.self_control_interactive_all_data,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(self_control_interactive_all_data_t));
				++ Judge_UndateFlag.self_control_interactive_all_data;
			}
			break;
			case ROBOT_COMMAND_ID:
			{//С��ͼ�������ݣ�cmd_id == 0x0303
				memcpy((char*)&judge_recv_mesg.ext_robot_command,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(ext_robot_command_t));
				++ Judge_UndateFlag.ext_robot_command;
			}
			break;
			case KEY_AND_MOUSE_ID:
			{//�ͻ����·���������Ϣ
				memcpy((char*)&judge_recv_mesg.key_and_mouse,(char*)&( ( JudgeFullFrame_t* )HereStartUnpack)->data,sizeof(key_and_mouse_t));
				++ Judge_UndateFlag.key_and_mouse;
			}
			break;	
		}
		
		if(( ( JudgeFullFrame_t* )HereStartUnpack)->header.DataLength +  9 < HowManyDataRec)
		{//˵�������������ݱ�һ֡����Ҫ��
			//HereStartUnpack = (uint8_t*)( ((uint8_t*)&(( JudgeFullFrame_t* )HereStartUnpack)->data) + 2 + (( JudgeFullFrame_t* )HereStartUnpack)->header.DataLength);
			*HereStartUnpack = 0xFF;//�Ѵ������֡�ƻ�����һ��Ҫ��
			(( JudgeFullFrame_t* )HereStartUnpack)->frame_cmd_id = 0x00;
			HereStartUnpack += 9 + (( JudgeFullFrame_t* )HereStartUnpack)->header.DataLength;
			//�ڶ���ȵ�һ��Ч�ʸ�
			HereStartUnpack = Judge_FindTureFrame(HereStartUnpack);
		}
		else
		{
			HereStartUnpack = NULL;
		}
	}
}





//void UART8_IRQHandler(void) 
void Judge_UseUART_IRQHandler(void) 
{
	static uint8_t rec = 0;
	static uint32_t HowManyDataRec = 0;//��Ϊ�������ÿ�ν��ж϶�Ҫ�ã���������Ϊstatic������Ҫÿ�ν�����������������ʡһ����������
	
//    if (USART_GetITStatus(UART8, USART_IT_IDLE) != RESET) 
    if (USART_GetITStatus(Judge_UseUART_Typedef_Name, USART_IT_IDLE) != RESET)
	{//�����ж�
//		DMA_Cmd(DMA1_Stream6, DISABLE); //�ر�DMA,��ֹ�������������
//		rec = UART8->SR;
//		rec = UART8->DR;//��������жϣ������ȶ�SR���ٶ�DR
		DMA_Cmd(Judge_UseDMA_Stream_Typedef_Name_RX, DISABLE); //�ر�DMA,��ֹ�������������
		rec = Judge_UseUART_Typedef_Name->SR;
		rec = Judge_UseUART_Typedef_Name->DR;//��������жϣ������ȶ�SR���ٶ�DR
		rec = 0;
		
		Judge_SwapDMABuff();
//		HowManyDataRec = Judge_RecDataBuffDepth - DMA_GetCurrDataCounter(DMA1_Stream6);//�õ���ǰDMA�յ��˶����ֽ�
//		DMA_SetCurrDataCounter(DMA1_Stream6, Judge_RecDataBuffDepth);
		HowManyDataRec = Judge_RecDataBuffDepth - DMA_GetCurrDataCounter(Judge_UseDMA_Stream_Typedef_Name_RX);//�õ���ǰDMA�յ��˶����ֽ�
		DMA_SetCurrDataCounter(Judge_UseDMA_Stream_Typedef_Name_RX, Judge_RecDataBuffDepth);
		//////////////////��ʱ�����������һ֡�µ����ݣ�Ҳ��Ӱ�����ݴ���Ҳ���ᵢ�����ݽ���

//		DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);
//		DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);//����DMA�ж�
		DMA_ClearFlag(Judge_UseDMA_Stream_Typedef_Name_RX,Judge_UseDMA_ClearFlag);
		DMA_ClearITPendingBit(Judge_UseDMA_Stream_Typedef_Name_RX, Judge_UseDMA_ClearIT_RX);//����DMA�ж�
		
		Judge_UnpackRecData(HowManyDataRec);
		
		DMA_Cmd(Judge_UseDMA_Stream_Typedef_Name_RX, ENABLE);     //��DMA,		
    }
}

//void DMA1_Stream6_IRQHandler(void)
void Judge_UseDMA_IRQHandler_RX(void) 
{//ֻ�д��ڵĿ����ж�ʧЧ�Ż��DMA�ж�
//	if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6)) 
//	{
//        DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6);
//        DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);        
//    }
	if (DMA_GetITStatus(Judge_UseDMA_Stream_Typedef_Name_RX, Judge_UseDMA_ClearIT_RX)) 
	{
        DMA_ClearFlag(Judge_UseDMA_Stream_Typedef_Name_RX, Judge_UseDMA_ClearIT_RX);
        DMA_ClearITPendingBit(Judge_UseDMA_Stream_Typedef_Name_RX, Judge_UseDMA_ClearIT_RX);        
    }
}

//void DMA1_Stream0_IRQHandler(void)
void Judge_UseDMA_IRQHandler_TX(void) 
{//����8�ķ����ж�
//	if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0))
	if (DMA_GetITStatus(Judge_UseDMA_Stream_Typedef_Name_TX, Judge_UseDMA_ClearIT_TX)) 	
	{
		
//        DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0);
//        DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);
		  DMA_ClearFlag(Judge_UseDMA_Stream_Typedef_Name_TX, Judge_UseDMA_ClearIT_TX);
          DMA_ClearITPendingBit(Judge_UseDMA_Stream_Typedef_Name_TX, Judge_UseDMA_ClearIT_TX);
		
//		if(NowSendingGraph == 1)
//		{
//			NowSendingGraph = 0;
//		}
		
		Judge_TxDataBuff.NowDMASendIng = 0;
		
		if(Judge_TxDataBuff.WhichBuffToDMA == Judge_TxDataBuff.Buff_0)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff0 = 0;
			if(Judge_TxDataBuff.HowLongWillSend_Buff1 != 0)
			{//˵����DMA�����ڼ䣬����DMA�����������һ֡���ݣ���BUFF1����
				Judge_SetDMASend(Judge_TxDataBuff.Buff_1,Judge_TxDataBuff.HowLongWillSend_Buff1);
				Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_0;
				Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_1;
				Judge_TxDataBuff.NowDMASendIng = 1;
			}
		}
		else if(Judge_TxDataBuff.WhichBuffToDMA == Judge_TxDataBuff.Buff_1)
		{
			Judge_TxDataBuff.HowLongWillSend_Buff1 = 0;
			if(Judge_TxDataBuff.HowLongWillSend_Buff0 != 0)
			{//˵����DMA�����ڼ䣬����DMA�����������һ֡���ݣ���BUFF0����
				Judge_SetDMASend(Judge_TxDataBuff.Buff_0,Judge_TxDataBuff.HowLongWillSend_Buff0);
				Judge_TxDataBuff.WhichBuffToCPU = Judge_TxDataBuff.Buff_1;
				Judge_TxDataBuff.WhichBuffToDMA = Judge_TxDataBuff.Buff_0;
				Judge_TxDataBuff.NowDMASendIng = 1;
			}
		}
    }
}

//void UART8_SendChar(uint8_t b)
void Judge_UseUART_SendChar(uint8_t b) 
{
//    while (USART_GetFlagStatus(UART8, USART_FLAG_TXE) == RESET);
//    USART_SendData(UART8, b);
    while (USART_GetFlagStatus(Judge_UseUART_Typedef_Name, USART_FLAG_TXE) == RESET);
    USART_SendData(Judge_UseUART_Typedef_Name, b);
}

void Draw_DmaDoubleBuffTest(void)
{//dma˫�������
	Judge_Init();
	//Judge_TestSpeed(ROBOT_POSITION_ID);
	Judge_TestSpeed(0x4000);
	while(1)
		;
}

//
void Judge_DefaultChannel(ChannelMsg_t *ppp,uint16_t Channel_X,char GphOrStr)
{
	ppp->HasExisted = 0;
	
	ppp->GraphData.color = COLOR_CH1;
	ppp->GraphData.layer = 1;
	ppp->GraphData.graphic_tpye = GraphChar;
	ppp->GraphData.start_angle = CHAR_SIZE_CH1;//15;//�����С
	ppp->GraphData.width = WIDTH_CH1;
	ppp->GraphData.start_x = POSITION_X_CH1;
	ppp->GraphData.start_y = POSITION_Y_CH1 - Channel_X * SPACE_Y_CHANNEL;
	
	ppp->LastTime = 0;
	ppp->NeedUpdate = 0;
	ppp->NextStr[0] = 0;
	ppp->TimeSpaceMS = 150;
	ppp->Name[0] = '0' + Channel_X / 100;
	ppp->Name[1] = '0' + (Channel_X % 100) / 10;
	ppp->Name[2] = '0' + Channel_X % 10;
	
	if(GphOrStr == 'G')
	{
		ppp->Name[0] = 'G';
		ppp->GraphData.graphic_tpye = Circle;
	}
	
	ppp->GraphData.graphic_name[0] = ppp->Name[0];
	ppp->GraphData.graphic_name[1] = ppp->Name[1];
	ppp->GraphData.graphic_name[2] = ppp->Name[2];
	
}
//
void Judge_Init(void)
{//�ú�����ʱ�ϳ����������ϵͳ������ȷ��ִ����ɴ˺��������Ҫ1���ӵ�ʱ�䡣�������ϵͳ���߳����ҳ�ʼ����printf������
//��ȫִ����Ҫ�����Ҫ6���ӵ�ʱ�䡣���û�г�ʼ��printf��������ú����Ῠ����
	uint16_t Temp = 0;
	
	Judge_Delay_ms(200);
	JudgeInit();
	
	if((judge_recv_mesg.robotState.robot_id >= RedHero && judge_recv_mesg.robotState.robot_id <= RedAirplane) || 
		(judge_recv_mesg.robotState.robot_id >= BlueHero && judge_recv_mesg.robotState.robot_id <= BlueAirplane))
	{
	
		Draw_HorizontalInit();
		//Draw_EqualHeightLine(1);           // ��һ���궨��׼����
		//Judge_Delay_ms(200);	
		Draw_CapicityInit();               // ����������(���ڹ������ǻ�����)
		Judge_Delay_ms(200);
		Draw_GraphChannel_StrInit();       // 7·ͨ��ͼ
		Judge_Delay_ms(200);
		Draw_SizeLine();                   // ��������
		for(Temp = 0; Temp < CHANNEL_NUMBER_MAX; ++ Temp)
		{
			if(Temp < CHANNEL_NUMBER_STR - 1)
			{
				Judge_DefaultChannel(&Channel[Temp],Temp,'S');
			}
			else
			{
				Judge_DefaultChannel(&Channel[Temp],Temp,'G');
			}
		}
	}
}

void Judge_SendStrChannel(ChannelMsg_t *WhichP)
{//�ַ���ͨ��
	static uint16_t SendTime_ms = 0;
	
	if(Judge_TxDataBuff.NowDMASendIng != 0 || NowSendingGraph != 0)
	{
		++ SendTime_ms;
		if(SendTime_ms >= 200)
		{
			SendTime_ms = 0;
			Judge_TxDataBuff.NowDMASendIng = 0;
			NowSendingGraph = 0;
		}
		else
		{
			return;
		}
	}
	else
	{
		SendTime_ms = 0;
	}
	
	if(WhichP->HasExisted == 0)
	{
		WhichP->GraphData.operate_tpye = AddGraph;
		WhichP->HasExisted = 1;
	}
	else
	{
		WhichP->GraphData.operate_tpye = ReviseGraph;
	}
	
	AddGraphToBuff(&WhichP->GraphData);
	memcpy(&Judge_DrawBuff.Data[15],WhichP->NextStr,30);
	CountGraph = 3;
	SendGraphBuffData('S');
	WhichP->NeedUpdate = 0;
}


void Judge_CheckGraphChannel_7_1(void)
{//ͨ��7_1��7_2���ǳ�������ͨ��������һ��ͼ�κ�һ��������
	graphic_data_struct_t GraphData;
	static uint16_t SendTime_ms = 0;
	static int32_t FloatTemp_V = 0;
	
	if(judge_recv_mesg.robotState.robot_id != RedEngineer && judge_recv_mesg.robotState.robot_id != RedAirplane
			&& judge_recv_mesg.robotState.robot_id != BlueEngineer && judge_recv_mesg.robotState.robot_id != BlueAirplane)
	{//���˻������̲�������
		
		//���³��������ڲ�ͼ����ɫ�ͳ���
		DefaultGraphData(&GraphData, (uint8_t*)"CP3");
		GraphData.operate_tpye = ReviseGraph;
		GraphData.layer = 2;
		if(CapicityPercentNow <= 20)
		{
			GraphData.color = Purplish;
		}
		else if(CapicityPercentNow >= 80)
		{
			GraphData.color = Green;
		}
		else
		{
			GraphData.color = Yellow;
		}
		GraphData.width = RECTANGLE_HEIGHT;
		GraphData.start_x = POSITION_X_CAP;
		GraphData.start_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
		GraphData.end_x = (POSITION_X_CAP + (CapicityPercentNow * RECTANGLE_LENGTH / 100.0f));
		GraphData.end_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
		AddGraphToBuff(&GraphData);//����ڲ�����			
			
		if(VOLTAGE_DONT_USE == 0)
		{	
			DefaultGraphData(&GraphData, (uint8_t*)"CP4");
			GraphData.operate_tpye = ReviseGraph;
			GraphData.layer = 2;
			GraphData.start_angle = CHAR_SIZE_VOLTAGE_2;
			GraphData.graphic_tpye = GraphFloat;
			GraphData.color = COLOR_VOLTAGE_2;
			GraphData.end_angle = 2;//С������Чλ��
			GraphData.start_x = POSITION_X_CAP + RECTANGLE_LENGTH + RECTANGLE_WIDTH/2.0;
			GraphData.start_y = POSITION_Y_CAP + RECTANGLE_HEIGHT / 2.0f;
			FloatTemp_V = VoltageNow * 1.0f;
			memcpy((uint8_t*)&GraphData + 11,(uint8_t*)&FloatTemp_V,4);
			AddGraphToBuff(&GraphData);
		}
	}
	else if(judge_recv_mesg.robotState.robot_id == RedEngineer || judge_recv_mesg.robotState.robot_id == BlueEngineer)
	{//���̣��ó������ݵ����ͳ������ݵ���������ʾ���ӵ��ƶ��͸߶�
		DefaultGraphData(&GraphData, (uint8_t*)"EN3");
		GraphData.operate_tpye = ReviseGraph;
		GraphData.layer = 3;
		GraphData.color = JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_COLOR;
		GraphData.width = JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH;
		GraphData.start_x = JUDGE_ENGINEER_LADDER_POSITION_X + JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH / 2.0;
		GraphData.start_y = JUDGE_ENGINEER_LADDER_POSITION_Y + JudgeAngineer_Height / 100.0 * JUDGE_ENGINEER_LADDER_HEIGHT_ALL;
		GraphData.end_x = JUDGE_ENGINEER_LADDER_POSITION_X + JUDGE_ENGINEER_LADDER_SPACE - JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH / 2.0;
		GraphData.end_y = JUDGE_ENGINEER_LADDER_POSITION_Y + JudgeAngineer_Height / 100.0 * JUDGE_ENGINEER_LADDER_HEIGHT_ALL;
		AddGraphToBuff(&GraphData);//�����м����
	}
}

void Judge_CheckGraphChannel_7_3(void)
{//ͨ��7_3��ͨ��7_4����PITCH���YAW��ͨ��
	static uint8_t HasExist3_4 = 0;
	static int32_t FloatTemp_P = 0;
	static int32_t FloatTemp_Y = 0;
	
	graphic_data_struct_t GraphData;
	
	DefaultGraphData(&GraphData, (uint8_t*)"G73");
	if(HasExist3_4 == 0)
	{
		GraphData.operate_tpye = AddGraph;
		HasExist3_4 = 1;
	}
	else
	{
		GraphData.operate_tpye = ReviseGraph;
	}
	GraphData.graphic_tpye = GraphFloat;
	GraphData.layer = 2;
	GraphData.color = COLOR_YAW_PIT;
	GraphData.start_angle = CHAR_SIZE_YAW_PIT;//15;//�����С
	GraphData.end_angle = 2;//С������Чλ��
	GraphData.width = WIDTH_YAW_PIT;
	GraphData.start_x = POSITION_X__YAW_PIT;
	GraphData.start_y = POSITION_Y__YAW_PIT + CHAR_SIZE_YAW_PIT;
	FloatTemp_P = ScreenPitch * 1.0f;
	memcpy((uint8_t*)&GraphData + 11,(uint8_t*)&FloatTemp_P,4);
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '4';
	GraphData.start_y = POSITION_Y__YAW_PIT - CHAR_SIZE_YAW_PIT;
	FloatTemp_Y = ScreenYaw * 1.0f;
	memcpy((uint8_t*)&GraphData + 11,(uint8_t*)&FloatTemp_Y,4);
	if(GRAPH_USE_YAW_OR_ARMOR == 0)
		AddGraphToBuff(&GraphData);
}



void Judge_CheckGraphChannel_7_5(void)
{//ͨ��7_5/6/7������ͨ��4����ͼ��װ�װ���תͨ��
	
	static uint8_t HasExist7_5 = 0;
	static float Temp_1_X = 0.0,Temp_1_Y = 0.0;
	static float Temp_2_X = 0.0,Temp_2_Y = 0.0;
	static float Temp_3_X = 0.0,Temp_3_Y = 0.0;
	static float Temp_4_X = 0.0,Temp_4_Y = 0.0;
	static float Temp_Angle = 0.0,Temp_Sin = 0.0,Temp_Cos = 0.0;
	static uint16_t PositionStart_X_1 = 0,PositionStart_Y_1 = 0,PositionEnd_X_1 = 0,PositionEnd_Y_1 = 0;
	static uint16_t PositionStart_X_2 = 0,PositionStart_Y_2 = 0,PositionEnd_X_2 = 0,PositionEnd_Y_2 = 0;
	static uint16_t PositionStart_X_3 = 0,PositionStart_Y_3 = 0,PositionEnd_X_3 = 0,PositionEnd_Y_3 = 0;
	static uint16_t PositionStart_X_4 = 0,PositionStart_Y_4 = 0,PositionEnd_X_4 = 0,PositionEnd_Y_4 = 0;
	
	graphic_data_struct_t GraphData;
	
	if(GRAPH_USE_YAW_OR_ARMOR != 1)
		return;
	
	//������ÿ���ߵ���ʼ�������ֹ����
	Temp_Angle = Armor_YawAngle / 3.1415926f;
	Temp_Sin = sinf(Temp_Angle);
	Temp_Cos = cosf(Temp_Angle);
	Temp_1_X = JUDGE_GRAPH_ROTATE_X - JUDGE_GRAPH_DISTANCE * Temp_Sin;
	Temp_1_Y = JUDGE_GRAPH_ROTATE_Y + JUDGE_GRAPH_DISTANCE * Temp_Cos;
	Temp_2_X = JUDGE_GRAPH_ROTATE_X - JUDGE_GRAPH_DISTANCE * Temp_Cos;
	Temp_2_Y = JUDGE_GRAPH_ROTATE_Y - JUDGE_GRAPH_DISTANCE * Temp_Sin;
	Temp_3_X = JUDGE_GRAPH_ROTATE_X + JUDGE_GRAPH_DISTANCE * Temp_Sin;
	Temp_3_Y = JUDGE_GRAPH_ROTATE_Y - JUDGE_GRAPH_DISTANCE * Temp_Cos;
	Temp_4_X = JUDGE_GRAPH_ROTATE_X + JUDGE_GRAPH_DISTANCE * Temp_Cos;
	Temp_4_Y = JUDGE_GRAPH_ROTATE_Y + JUDGE_GRAPH_DISTANCE * Temp_Sin;
	PositionStart_X_1 = Temp_1_X - JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	PositionStart_Y_1 = Temp_1_Y - JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	PositionEnd_X_1 = Temp_1_X + JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	PositionEnd_Y_1 = Temp_1_Y + JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	
	PositionStart_X_2 = Temp_2_X + JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	PositionStart_Y_2 = Temp_2_Y - JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	PositionEnd_X_2 = Temp_2_X - JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	PositionEnd_Y_2 = Temp_2_Y + JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	
	PositionStart_X_3 = Temp_3_X - JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	PositionStart_Y_3 = Temp_3_Y - JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	PositionEnd_X_3 = Temp_3_X + JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	PositionEnd_Y_3 = Temp_3_Y + JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	
	PositionStart_X_4 = Temp_4_X + JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	PositionStart_Y_4 = Temp_4_Y - JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	PositionEnd_X_4 = Temp_4_X - JUDGE_GRAPH_BOARD_LENGTH * Temp_Sin / 2.0f;
	PositionEnd_Y_4 = Temp_4_Y + JUDGE_GRAPH_BOARD_LENGTH * Temp_Cos / 2.0f;
	
	DefaultGraphData(&GraphData, (uint8_t*)"G74");
	if(HasExist7_5 == 0)
	{
		GraphData.operate_tpye = AddGraph;
		HasExist7_5 = 1;
	}
	else
	{
		GraphData.operate_tpye = ReviseGraph;
	}
	GraphData.graphic_tpye = Line;
	GraphData.layer = 2;
	GraphData.color = Armor_Color_1;
	GraphData.width = JUDGE_GRAPH_BOARD_WIDTH;
	GraphData.start_x = PositionStart_X_1;
	GraphData.start_y = PositionStart_Y_1;
	GraphData.end_x = PositionEnd_X_1;
	GraphData.end_y = PositionEnd_Y_1;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '5';
	GraphData.color = Armor_Color_2;
	GraphData.start_x = PositionStart_X_2;
	GraphData.start_y = PositionStart_Y_2;
	GraphData.end_x = PositionEnd_X_2;
	GraphData.end_y = PositionEnd_Y_2;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '6';
	GraphData.color = Armor_Color_3;
	GraphData.start_x = PositionStart_X_3;
	GraphData.start_y = PositionStart_Y_3;
	GraphData.end_x = PositionEnd_X_3;
	GraphData.end_y = PositionEnd_Y_3;
	AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '7';
	GraphData.color = Armor_Color_4;
	GraphData.start_x = PositionStart_X_4;
	GraphData.start_y = PositionStart_Y_4;
	GraphData.end_x = PositionEnd_X_4;
	GraphData.end_y = PositionEnd_Y_4;
	AddGraphToBuff(&GraphData);
	
	
}

void Judge_CheckGraphChannel_7_6(void)
{//ͨ��7_6����ͼ��ͨ��
}

void Judge_CheckGraphChannel_7_7(void)
{//ͨ��7_7����ͼ��ͨ��
	
}

void Judge_CheckGraphChannel_8_7(void)
{//ͨ��8_7����ͼ��ͨ����
	static uint8_t HasExist8_7 = 0;
	graphic_data_struct_t GraphData;
	
	DefaultGraphData(&GraphData, (uint8_t*)"G81");
	if(HasExist8_7 == 0)
	{
		GraphData.operate_tpye = AddGraph;
		HasExist8_7 = 1;
	}
	else
	{
		GraphData.operate_tpye = ReviseGraph;
	}
	GraphData.graphic_tpye = Rectangle;
	GraphData.layer = 2;
	GraphData.radius = GRAPH_CHANNEL_ALL_RADIUS;
	GraphData.color = Judge_GraphChannelColor[1][0];
	GraphData.width = GRAPH_CHANNEL_8_1_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_1_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_1_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_1_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_1_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_1 == 1)
		AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '2';
	GraphData.color = Judge_GraphChannelColor[1][1];
	GraphData.width = GRAPH_CHANNEL_8_2_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_2_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_2_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_2_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_2_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_2 == 1)
		AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '3';
	GraphData.color = Judge_GraphChannelColor[1][2];
	GraphData.width = GRAPH_CHANNEL_8_3_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_3_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_3_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_3_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_3_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_3 == 1)
		AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '4';
	GraphData.color = Judge_GraphChannelColor[1][3];
	GraphData.width = GRAPH_CHANNEL_8_4_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_4_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_4_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_4_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_4_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_4 == 1)
		AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '5';
	GraphData.color = Judge_GraphChannelColor[1][4];
	GraphData.width = GRAPH_CHANNEL_8_5_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_5_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_5_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_5_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_5_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_5 == 1)
		AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '6';
	GraphData.color = Judge_GraphChannelColor[1][5];
	GraphData.width = GRAPH_CHANNEL_8_6_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_6_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_6_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_6_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_6_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_6 == 1)
		AddGraphToBuff(&GraphData);
	
	GraphData.graphic_name[2] = '7';
	GraphData.color = Judge_GraphChannelColor[1][6];
	GraphData.width = GRAPH_CHANNEL_8_7_WIDTH;
	GraphData.start_x = GRAPH_CHANNEL_8_7_POSITION_X;
	GraphData.start_y = GRAPH_CHANNEL_8_7_POSITION_Y;
	GraphData.end_x = GRAPH_CHANNEL_8_7_POSITION_X + GRAPH_CHANNEL_ALL_LENGTH;
	GraphData.end_y = GRAPH_CHANNEL_8_7_POSITION_Y;
	if(GRAPH_USE_THIS_GRAPH_8_7 == 1)
		AddGraphToBuff(&GraphData);
	
}

void Judge_SendGraphChannel(uint8_t WhichG)
{//ͼ��ͨ��,���ͼ��ͨ����ͼ��ͨ����2������һ�����������ַ�������һ�����ַ���ͨ���ڵ�ͼ��ͨ��
	static uint16_t SendTime_ms = 0;
	
	if(Judge_TxDataBuff.NowDMASendIng != 0 || NowSendingGraph != 0)
	{
		++ SendTime_ms;
		if(SendTime_ms >= 200)
		{
			SendTime_ms = 0;
			Judge_TxDataBuff.NowDMASendIng = 0;
			NowSendingGraph = 0;
		}
		else
		{
			return;
		}
	}
	else
	{
		SendTime_ms = 0;
	}//��ȫ
	
	switch(WhichG)
	{
		case 7:
		{
			Judge_CheckGraphChannel_7_1();
			Judge_CheckGraphChannel_7_3();
			Judge_CheckGraphChannel_7_5();
			Judge_CheckGraphChannel_7_6();
			Judge_CheckGraphChannel_7_7();
			SendGraphBuffData('G');
			break;
		}
		case 8:
		{
			Judge_CheckGraphChannel_8_7();
			SendGraphBuffData('G');
			break;
		}
	}
	Channel[WhichG].NeedUpdate = 0;
}

int8_t Judge_RadarSendStr(Robots_ID_e WhichRobot,float Position_M_X,float Position_M_Y)
{
	static uint16_t SendTime_ms = 0;
	
	if(Judge_TxDataBuff.NowDMASendIng != 0 || NowSendingGraph != 0)
	{
		++ SendTime_ms;
		if(SendTime_ms >= 200)
		{
			SendTime_ms = 0;
			Judge_TxDataBuff.NowDMASendIng = 0;
			NowSendingGraph = 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		SendTime_ms = 0;
	}//��ȫ
	
	
}

void Judge_RadarLoop_1MS(void)
{//����ÿ1ms��Ҫִ��һ�����������������׼��ÿ1msִ��һ�Ρ��˺���������ʱ�����������ÿ0.1ms����ȫ����ִ����ɴ˺���
	static uint64_t JudgeSendTime_ms = 151;
	static uint64_t JudgeSendLastTime_ms = 0;
	static uint8_t LastHadUndated = 1;
	static uint8_t LastUndateErr = 0;
	
	
	if(LastUndateErr != 0)
	{
		
	}
	
	if(JudgeSendTime_ms - JudgeSendLastTime_ms < 150)
	{
		return;
	}
	
}

void Judge_LoopPer1MS(void)
{//����ÿ1ms��Ҫִ��һ�����������������׼��ÿ1msִ��һ�Ρ��˺���������ʱ�����������ÿ0.1ms����ȫ����ִ����ɴ˺���
	static uint64_t JudgeSendTime_ms = 151;
	static uint64_t JudgeSendLastTime_ms = 0;
	static uint16_t ChannelCount = 0;
	static uint16_t LastUpdateChannel = 0;
	static uint8_t LastHadUndated = 1;
	static uint8_t SendGr_Temp = 0;
	
	JudgeSendTime_ms += 1;
	
	if((judge_recv_mesg.robotState.robot_id >= RedHero && judge_recv_mesg.robotState.robot_id <= RedAirplane) || 
		(judge_recv_mesg.robotState.robot_id >= BlueHero && judge_recv_mesg.robotState.robot_id <= BlueAirplane))
	{//�ڱ����״ﲻִ�иú���
		;
	}
	else
	{
		return;
	}
	
	if(IsDrawEqualLine != 0)
		return;
	
	if(Channel[LastUpdateChannel].NeedUpdate != 0 && LastHadUndated == 0)
	{
		JudgeSendLastTime_ms = JudgeSendTime_ms;
		Channel[LastUpdateChannel].LastTime = JudgeSendTime_ms;
		if(LastUpdateChannel < CHANNEL_NUMBER_STR)
		{
			Judge_SendStrChannel(&Channel[LastUpdateChannel]);
		}
		else
		{
			Judge_SendGraphChannel(LastUpdateChannel);
		}
		
		if(Channel[LastUpdateChannel].NeedUpdate == 0)
		{
			LastHadUndated = 1;
			++ LastUpdateChannel;
			if(LastUpdateChannel >= CHANNEL_NUMBER_MAX)
				LastUpdateChannel = 0;
		}
		return;
	}
	
	if(JudgeSendTime_ms - JudgeSendLastTime_ms < Channel[LastUpdateChannel].TimeSpaceMS)
	{
		return;
	}
	
	for(ChannelCount = 0; ChannelCount < CHANNEL_NUMBER_MAX ; ++ ChannelCount)
	{
		
		if(Channel[LastUpdateChannel].NeedUpdate != 0)
		{
			JudgeSendLastTime_ms = JudgeSendTime_ms;
			Channel[LastUpdateChannel].LastTime = JudgeSendTime_ms;
			
			if(LastUpdateChannel < CHANNEL_NUMBER_STR)
			{
				Judge_SendStrChannel(&Channel[LastUpdateChannel]);
			}
			else
			{
				Judge_SendGraphChannel(LastUpdateChannel);
			}
			
			if(Channel[LastUpdateChannel].NeedUpdate == 0)
			{
				LastHadUndated = 1;
				++ LastUpdateChannel;
				if(LastUpdateChannel >= CHANNEL_NUMBER_MAX)
					LastUpdateChannel = 0;
			}
			else
			{
				LastHadUndated = 0; 
			}
			break;
		}
		else
		{
			++ LastUpdateChannel;
			if(LastUpdateChannel >= CHANNEL_NUMBER_MAX)
				LastUpdateChannel = 0;
		}
	}
}

//////////////////////////////////////////
//�����ǲ��Ժ�����

void Judge_ClearFlag(void)
{
	Judge_UndateFlag.BuffDebuffStatus = 0;
	Judge_UndateFlag.bulletRemaining = 0;
	Judge_UndateFlag.DartClientCmd = 0;
	Judge_UndateFlag.DartRemainTime = 0;
	Judge_UndateFlag.DartStatus = 0;
	Judge_UndateFlag.droneEnergy = 0;
	Judge_UndateFlag.fieldEvent = 0;
	Judge_UndateFlag.gameResult = 0;
	Judge_UndateFlag.gameState = 0;
	Judge_UndateFlag.powerHeat = 0;
	Judge_UndateFlag.rfid_status = 0;
	Judge_UndateFlag.robotBUFF = 0;
	Judge_UndateFlag.robotHP = 0;
	Judge_UndateFlag.robotHurt = 0;
	Judge_UndateFlag.robotPosition = 0;
	Judge_UndateFlag.robotShoot = 0;
	Judge_UndateFlag.robotState = 0;
	Judge_UndateFlag.student_interactive_all_data = 0;
	Judge_UndateFlag.supplyAction = 0;
	Judge_UndateFlag.warning = 0;
	Judge_UndateFlag.self_control_interactive_all_data = 0;
	Judge_UndateFlag.ext_robot_command = 0;
	Judge_UndateFlag.key_and_mouse = 0;
}

void Judge_TestSpeed(frame_cmd_id_e WhichMsg)
{//���Ը���Ƶ��
	
	while(1)
	{
		Judge_ClearFlag();
		Judge_Delay_ms(1000);
		
		if((uint32_t)WhichMsg == 0x4000)
		{//��ӡ��������
			printf("V:%d,%d,%d,%d,%d#%d,%d,%d,%d,%d#%d,%d,%d,%d,%d#%d,%d,%d,%d,%d#%d,%d,%d\n\r",
					Judge_UndateFlag.gameState,\
					Judge_UndateFlag.gameResult,\
					Judge_UndateFlag.robotHP,\
					Judge_UndateFlag.DartStatus,\
					Judge_UndateFlag.BuffDebuffStatus,\
					Judge_UndateFlag.fieldEvent,\
					Judge_UndateFlag.supplyAction,\
					Judge_UndateFlag.warning,\
					Judge_UndateFlag.DartRemainTime,\
					Judge_UndateFlag.robotState,\
					Judge_UndateFlag.powerHeat,\
					Judge_UndateFlag.robotPosition,\
					Judge_UndateFlag.robotBUFF,\
					Judge_UndateFlag.droneEnergy,\
					Judge_UndateFlag.robotHurt,\
					Judge_UndateFlag.robotShoot,\
					Judge_UndateFlag.bulletRemaining,\
					Judge_UndateFlag.rfid_status,\
					Judge_UndateFlag.DartClientCmd,\
					Judge_UndateFlag.student_interactive_all_data,\
					Judge_UndateFlag.self_control_interactive_all_data,\
					Judge_UndateFlag.ext_robot_command,\
					Judge_UndateFlag.key_and_mouse);
		}
		else
		{
			switch(WhichMsg)
			{
				case GAME_STATE_ID:
				{//����״̬��1Hz��
					printf("V:%d\n\r",Judge_UndateFlag.gameState);
				}
				break;
				case GAME_RESUIT_ID:
				{//�������
					printf("V:%d\n\r",Judge_UndateFlag.gameResult);
				}
				break;
				case ROBOT_HP_ID:
				{//������Ѫ�����ݣ�1Hz��
					printf("V:%d\n\r",Judge_UndateFlag.robotHP);
				}
				break;
//				case DART_FIRE_STATE:
//				{//���ڷ���״̬
//					printf("V:%d\n\r",Judge_UndateFlag.DartStatus);
//				}
//				break;
				case GAIN_AND_PUNISHMENT_STATE:
				{//�˹�������ս���ӳ���ͷ���״̬��1HZ
					printf("V:%d\n\r",Judge_UndateFlag.BuffDebuffStatus);
				}
				break;
				case FIELD_EVENT_ID:
				{//�����¼���1HZ
					printf("V:%d\n\r",Judge_UndateFlag.fieldEvent);
				}
				break;
				case SUPPLY_ACTION_ID:
				{//����վ������ʶ
					printf("V:%d\n\r",Judge_UndateFlag.supplyAction);
				}
				break;
				case JUDGE_WARNING_ID:
				{//���о�������
					printf("V:%d\n\r",Judge_UndateFlag.warning);
				}
				break;
				case DART_FIRE_COUNTDOWN:
				{//���ڷ���ڵ���ʱ��1HZ����
					printf("V:%d\n\r",Judge_UndateFlag.DartRemainTime);
				}
				break;
				case ROBOT_STATE_ID:
				{//������״̬��10Hz��
					printf("V:%d\n\r",Judge_UndateFlag.robotState);
				}
				break;
				case REALTIME_POWER_ID:
				{//ʵʱ����������50Hz��
					printf("V:%d\n\r",Judge_UndateFlag.powerHeat);
				}
				break;
				case ROBOT_POSITION_ID:
				{//������λ�ã�10Hz��
					printf("V:%d\n\r",Judge_UndateFlag.robotPosition);
				}
				break;
				case ROBOT_BUFF_ID:
				{//����������
					printf("V:%d\n\r",Judge_UndateFlag.robotBUFF);
				}
				break;
				case DRONE_POWER_ID:
				{//���л���������״̬���ݣ�10HZ��ֻ�п��л��������ط���
					printf("V:%d\n\r",Judge_UndateFlag.droneEnergy);
				}
				break;
				case ROBOT_HURT_ID:
				{//�˺�����
					printf("V:%d\n\r",Judge_UndateFlag.robotHurt);
				}
				break;
				case ROBOT_SHOOT_ID:
				{//�������
					printf("V:%d\n\r",Judge_UndateFlag.robotShoot);
				}
				break;
				case SURPLUS_BULLET_ID:
				{//ʣ���ӵ������ڱ��Ϳ��л����ˣ�
					printf("V:%d\n\r",Judge_UndateFlag.bulletRemaining);
				}
				break;
				case ROBOT_RFID_STATE:
				{//������RFID״̬��1HZ���ڷ���
					printf("V:%d\n\r",Judge_UndateFlag.rfid_status);
				}
				break;
				case ROBOT_OPERATOR_CMD:
				{//���ڻ����˿ͻ���ָ�����ݣ�10HZ
					printf("V:%d\n\r",Judge_UndateFlag.DartClientCmd);
				}
				break;
				case ROBOT_INTERACTIVE_ID:
				{//�����˼佻�������ʹ���
					printf("V:%d\n\r",Judge_UndateFlag.student_interactive_all_data);
				}
				break;
				case SELF_CONTROL_INTERACTIVE_ID:
				{//������RFID״̬��1HZ���ڷ���
					printf("V:%d\n\r",Judge_UndateFlag.self_control_interactive_all_data);
				}
				break;
				case ROBOT_COMMAND_ID:
				{//���ڻ����˿ͻ���ָ�����ݣ�10HZ
					printf("V:%d\n\r",Judge_UndateFlag.ext_robot_command);
				}
				break;
				case KEY_AND_MOUSE_ID:
				{//�����˼佻�������ʹ���
					printf("V:%d\n\r",Judge_UndateFlag.key_and_mouse);
				}
				break;
			}
		}
		
		
		
		//���������̫���ˣ�����һ�붼�����꣬����ֱ�ӵ�������
//		printf("����ϵͳ����Ƶ�ʲ��ԣ�\n\r \
//		����״̬֡��:%d,\r\n	\
//		�������֡��:%d,\r\n	\
//		Ѫ��֡��:%d,\r\n	\
//		���ڷ���״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		����״̬֡��:%d,\r\n	\
//		���������Ϣ:%d,\r\n	");
		
	}
}


uint16_t Judge_GetFlag(frame_cmd_id_e WhichMsg)
{		
		if((uint32_t)WhichMsg == 0x4000)
		{//��ӡ��������
			return (Judge_UndateFlag.gameState+\
					Judge_UndateFlag.gameResult+\
					Judge_UndateFlag.robotHP+\
					Judge_UndateFlag.DartStatus+\
					Judge_UndateFlag.BuffDebuffStatus+\
					Judge_UndateFlag.fieldEvent+\
					Judge_UndateFlag.supplyAction+\
					Judge_UndateFlag.warning+\
					Judge_UndateFlag.DartRemainTime+\
					Judge_UndateFlag.robotState+\
					Judge_UndateFlag.powerHeat+\
					Judge_UndateFlag.robotPosition+\
					Judge_UndateFlag.robotBUFF+\
					Judge_UndateFlag.droneEnergy+\
					Judge_UndateFlag.robotHurt+\
					Judge_UndateFlag.robotShoot+\
					Judge_UndateFlag.bulletRemaining+\
					Judge_UndateFlag.rfid_status+\
					Judge_UndateFlag.DartClientCmd+\
					Judge_UndateFlag.student_interactive_all_data+\
					Judge_UndateFlag.self_control_interactive_all_data+\
					Judge_UndateFlag.ext_robot_command+\
					Judge_UndateFlag.key_and_mouse);
		}
		else
		{
			switch(WhichMsg)
			{
				case GAME_STATE_ID:
				{//����״̬��1Hz��
					return Judge_UndateFlag.gameState;
				}
				case GAME_RESUIT_ID:
				{//�������
					return Judge_UndateFlag.gameResult;
				}
				case ROBOT_HP_ID:
				{//������Ѫ�����ݣ�1Hz��
					return Judge_UndateFlag.robotHP;
				}
//				case DART_FIRE_STATE:
//				{//���ڷ���״̬
//					return Judge_UndateFlag.DartStatus;
//				}
				case GAIN_AND_PUNISHMENT_STATE:
				{//�˹�������ս���ӳ���ͷ���״̬��1HZ
					return Judge_UndateFlag.BuffDebuffStatus;
				}
				case FIELD_EVENT_ID:
				{//�����¼���1HZ
					return Judge_UndateFlag.fieldEvent;
				}
				case SUPPLY_ACTION_ID:
				{//����վ������ʶ
					return Judge_UndateFlag.supplyAction;
				}
				case JUDGE_WARNING_ID:
				{//���о�������
					return Judge_UndateFlag.warning;
				}
				case DART_FIRE_COUNTDOWN:
				{//���ڷ���ڵ���ʱ��1HZ����
					return Judge_UndateFlag.DartRemainTime;
				}
				case ROBOT_STATE_ID:
				{//������״̬��10Hz��
					return Judge_UndateFlag.robotState;
				}
				case REALTIME_POWER_ID:
				{//ʵʱ����������50Hz��
					return Judge_UndateFlag.powerHeat;
				}
				case ROBOT_POSITION_ID:
				{//������λ�ã�10Hz��
					return Judge_UndateFlag.robotPosition;
				}
				case ROBOT_BUFF_ID:
				{//����������
					return Judge_UndateFlag.robotBUFF;
				}
				case DRONE_POWER_ID:
				{//���л���������״̬���ݣ�10HZ��ֻ�п��л��������ط���
					return Judge_UndateFlag.droneEnergy;
				}
				case ROBOT_HURT_ID:
				{//�˺�����
					return Judge_UndateFlag.robotHurt;
				}
				case ROBOT_SHOOT_ID:
				{//�������
					return Judge_UndateFlag.robotShoot;
				}
				case SURPLUS_BULLET_ID:
				{//ʣ���ӵ������ڱ��Ϳ��л����ˣ�
					return Judge_UndateFlag.bulletRemaining;
				}
				case ROBOT_RFID_STATE:
				{//������RFID״̬��1HZ���ڷ���
					return Judge_UndateFlag.rfid_status;
				}
				case ROBOT_OPERATOR_CMD:
				{//���ڻ����˿ͻ���ָ�����ݣ�10HZ
					return Judge_UndateFlag.DartClientCmd;
				}
				case ROBOT_INTERACTIVE_ID:
				{//�����˼佻�������ʹ���
					return Judge_UndateFlag.student_interactive_all_data;
				}
				case SELF_CONTROL_INTERACTIVE_ID:
				{//������RFID״̬��1HZ���ڷ���
					return Judge_UndateFlag.self_control_interactive_all_data;
				}
				case ROBOT_COMMAND_ID:
				{//���ڻ����˿ͻ���ָ�����ݣ�10HZ
					return Judge_UndateFlag.ext_robot_command;
				}
				case KEY_AND_MOUSE_ID:
				{//�����˼佻�������ʹ���
					return Judge_UndateFlag.key_and_mouse;
				}
			}
		}
	return 0;		
}

void Judge_ClearFlagOf(frame_cmd_id_e WhichMsg)
{
		if((uint32_t)WhichMsg == 0x4000)
		{
					Judge_UndateFlag.gameState = 0;
					Judge_UndateFlag.gameResult= 0;
					Judge_UndateFlag.robotHP= 0;
					Judge_UndateFlag.DartStatus= 0;
					Judge_UndateFlag.BuffDebuffStatus= 0;
					Judge_UndateFlag.fieldEvent= 0;
					Judge_UndateFlag.supplyAction= 0;
					Judge_UndateFlag.warning= 0;
					Judge_UndateFlag.DartRemainTime= 0;
					Judge_UndateFlag.robotState= 0;
					Judge_UndateFlag.powerHeat= 0;
					Judge_UndateFlag.robotPosition= 0;
					Judge_UndateFlag.robotBUFF= 0;
					Judge_UndateFlag.droneEnergy= 0;
					Judge_UndateFlag.robotHurt= 0;
					Judge_UndateFlag.robotShoot= 0;
					Judge_UndateFlag.bulletRemaining= 0;
					Judge_UndateFlag.rfid_status= 0;
					Judge_UndateFlag.DartClientCmd= 0;
					Judge_UndateFlag.student_interactive_all_data = 0;
		}
		else
		{
			switch(WhichMsg)
			{
				case GAME_STATE_ID:
				{//����״̬��1Hz��
					Judge_UndateFlag.gameState = 0;
				}
				case GAME_RESUIT_ID:
				{//�������
					Judge_UndateFlag.gameResult = 0;
				}
				case ROBOT_HP_ID:
				{//������Ѫ�����ݣ�1Hz��
					 Judge_UndateFlag.robotHP = 0;
				}
//				case DART_FIRE_STATE:
//				{//���ڷ���״̬
//					 Judge_UndateFlag.DartStatus = 0;
//				}
				case GAIN_AND_PUNISHMENT_STATE:
				{//�˹�������ս���ӳ���ͷ���״̬��1HZ
					 Judge_UndateFlag.BuffDebuffStatus = 0;
				}
				case FIELD_EVENT_ID:
				{//�����¼���1HZ
					 Judge_UndateFlag.fieldEvent = 0;
				}
				case SUPPLY_ACTION_ID:
				{//����վ������ʶ
					 Judge_UndateFlag.supplyAction = 0;
				}
				case JUDGE_WARNING_ID:
				{//���о�������
					 Judge_UndateFlag.warning = 0;
				}
				case DART_FIRE_COUNTDOWN:
				{//���ڷ���ڵ���ʱ��1HZ����
					 Judge_UndateFlag.DartRemainTime = 0;
				}
				case ROBOT_STATE_ID:
				{//������״̬��10Hz��
					 Judge_UndateFlag.robotState = 0;
				}
				case REALTIME_POWER_ID:
				{//ʵʱ����������50Hz��
					 Judge_UndateFlag.powerHeat = 0;
				}
				case ROBOT_POSITION_ID:
				{//������λ�ã�10Hz��
					 Judge_UndateFlag.robotPosition = 0;
				}
				case ROBOT_BUFF_ID:
				{//����������
					 Judge_UndateFlag.robotBUFF = 0;
				}
				case DRONE_POWER_ID:
				{//���л���������״̬���ݣ�10HZ��ֻ�п��л��������ط���
					 Judge_UndateFlag.droneEnergy = 0;
				}
				case ROBOT_HURT_ID:
				{//�˺�����
					 Judge_UndateFlag.robotHurt = 0;
				}
				case ROBOT_SHOOT_ID:
				{//�������
					 Judge_UndateFlag.robotShoot = 0;
				}
				case SURPLUS_BULLET_ID:
				{//ʣ���ӵ������ڱ��Ϳ��л����ˣ�
					 Judge_UndateFlag.bulletRemaining = 0;
				}
				case ROBOT_RFID_STATE:
				{//������RFID״̬��1HZ���ڷ���
					 Judge_UndateFlag.rfid_status = 0;
				}
				case ROBOT_OPERATOR_CMD:
				{//���ڻ����˿ͻ���ָ�����ݣ�10HZ
					 Judge_UndateFlag.DartClientCmd = 0;
				}
				case ROBOT_INTERACTIVE_ID:
				{//�����˼佻�������ʹ���
					 Judge_UndateFlag.student_interactive_all_data = 0;
				}
			}
		}	
}



//////////////////////////////////////////////////////////////////////////////////////////
//****************************************************************************************
//########################################################################################
//�����ǽӿں������������ǽӿں������������ǽӿں������������ǽӿں������������ǽӿں��������Լ���Ҫʲô���ݾ�д��������ʲô����
//����

//////////////////////////////////////////
//�����ǽӿں���

ext_game_robot_status_t* Judge_GetRobotState(void)
{
	return &judge_recv_mesg.robotState;
	
}

ext_game_robot_pos_t*	Judge_GetRobotPosition(void)
{
	return &judge_recv_mesg.robotPosition;
}

ext_power_heat_data_t* Judge_GetRobot_power_heat(void)
{
	return &judge_recv_mesg.powerHeat;
}

ext_shoot_data_t* Judge_shoot_data(void)
{
	return &judge_recv_mesg.robotShoot;
}
ext_game_robot_status_t* Judge_robot_status(void)
{
	return &judge_recv_mesg.robotState;
}

ext_power_heat_data_t* Judge_heat(void)
{
	return &judge_recv_mesg.powerHeat;
}

//�����ǽӿں������������ǽӿں������������ǽӿں������������ǽӿں������������ǽӿں�������
//########################################################################################
//****************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////


