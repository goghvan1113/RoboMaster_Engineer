/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :�����ñ�
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  *
  * ������־��
  * 2021��1��10�գ����ҵ�judgetest.c�ĵ�512�У�USART_DMACmd(UART8,USART_DMAReq_Tx,ENABLE);//��������DMA
  * Ӧ��ΪUSART_DMACmd(Judge_UseUART_Typedef_Name,USART_DMAReq_Tx,ENABLE);
  *
  *	2021��4��3�գ��յ����°�Ĳ���ϵͳ����ʼ��ֲ��
  */

#ifndef __JUDGE_INTERACT_H__
#define __JUDGE_INTERACT_H__

#include "judgeStruct.h"
#include "CRCCheck.h"


///////////////////////////////////////////////////////////////���̻����������ñ�

//*************������************//
#define JUDGE_ENGINEER_ANOTHER_1_START_X	1329
#define JUDGE_ENGINEER_ANOTHER_1_START_Y	1080 - 430		
#define JUDGE_ENGINEER_ANOTHER_1_END_X	1454
#define JUDGE_ENGINEER_ANOTHER_1_END_Y	1080 - 662		
#define JUDGE_ENGINEER_ANOTHER_1_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_1_WIDTH	5

//*************������************//
#define JUDGE_ENGINEER_ANOTHER_2_START_X	744
#define JUDGE_ENGINEER_ANOTHER_2_START_Y	1080 - 451		
#define JUDGE_ENGINEER_ANOTHER_2_END_X	678
#define JUDGE_ENGINEER_ANOTHER_2_END_Y	1080 - 590		
#define JUDGE_ENGINEER_ANOTHER_2_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_2_WIDTH	5

//*************Ӣ����************//
#define JUDGE_ENGINEER_ANOTHER_3_START_X	1260
#define JUDGE_ENGINEER_ANOTHER_3_START_Y	1080 - 283		
#define JUDGE_ENGINEER_ANOTHER_3_END_X	1375
#define JUDGE_ENGINEER_ANOTHER_3_END_Y	1080 - 373		
#define JUDGE_ENGINEER_ANOTHER_3_COLOR	Green
#define JUDGE_ENGINEER_ANOTHER_3_WIDTH	5

#define JUDGE_ENGINEER_ANOTHER_4_START_X	0
#define JUDGE_ENGINEER_ANOTHER_4_START_Y	0		
#define JUDGE_ENGINEER_ANOTHER_4_END_X	0
#define JUDGE_ENGINEER_ANOTHER_4_END_Y	0		
#define JUDGE_ENGINEER_ANOTHER_4_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_4_WIDTH	0

#define JUDGE_ENGINEER_ANOTHER_5_START_X	0
#define JUDGE_ENGINEER_ANOTHER_5_START_Y	0		
#define JUDGE_ENGINEER_ANOTHER_5_END_X	0
#define JUDGE_ENGINEER_ANOTHER_5_END_Y	0		
#define JUDGE_ENGINEER_ANOTHER_5_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_5_WIDTH	0

#define JUDGE_ENGINEER_ANOTHER_6_START_X	0
#define JUDGE_ENGINEER_ANOTHER_6_START_Y	0		
#define JUDGE_ENGINEER_ANOTHER_6_END_X	0
#define JUDGE_ENGINEER_ANOTHER_6_END_Y	0		
#define JUDGE_ENGINEER_ANOTHER_6_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_6_WIDTH	0

#define JUDGE_ENGINEER_ANOTHER_7_START_X	0
#define JUDGE_ENGINEER_ANOTHER_7_START_Y	0		
#define JUDGE_ENGINEER_ANOTHER_7_END_X	0
#define JUDGE_ENGINEER_ANOTHER_7_END_Y	0		
#define JUDGE_ENGINEER_ANOTHER_7_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_7_WIDTH	0	



///////////////////////////////////////////////////////////////���ñ�

/*********����׼����*******/
#define JUDGE_ENGINEER_AIM_X	960
#define JUDGE_ENGINEER_AIM_Y	540
#define JUDGE_ENGINEER_AIM_LENGTH_H	150		//ˮƽ����
#define JUDGE_ENGINEER_AIM_LENGTH_V	300		//��ֱ����
#define JUDGE_ENGINEER_AIM_COLOR	White
#define JUDGE_ENGINEER_AIM_WIDTH	1


/*********�����ϰ�����Ƹ˶�����*******/
#define JUDGE_ENGINEER_LINEAR_COLOR		Green	// ���Ƹ˶�����������ɫ
#define JUDGE_ENGINEER_LINEAR_WIDTH		10	// С��Դ�������߿��

#define JUDGE_ENGINEER_LINEAR_LEFT_START_X	690
#define JUDGE_ENGINEER_LINEAR_LEFT_START_Y	1080 - 718		//���ˮƽ��
#define JUDGE_ENGINEER_LINEAR_LEFT_END_X	800
#define JUDGE_ENGINEER_LINEAR_LEFT_END_Y	1080 - 716		//���ˮƽ��

#define JUDGE_ENGINEER_LINEAR_RIGHT_1_START_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_1_START_Y	0		//�Ҳ�ˮƽ��
#define JUDGE_ENGINEER_LINEAR_RIGHT_1_END_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_1_END_Y	0		//�Ҳ�ˮƽ��

#define JUDGE_ENGINEER_LINEAR_RIGHT_2_START_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_2_START_Y	0		//�Ҳ�ˮƽ�������
#define JUDGE_ENGINEER_LINEAR_RIGHT_2_END_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_2_END_Y	0		//�Ҳ�ˮƽ�������
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_START_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_START_Y	0		//�Ҳ�ˮƽ���ұ���
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_END_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_END_Y	0		//�Ҳ�ˮƽ���ұ���




/*********�����������ñ���ͳ������ݳ�ͻ�����ʹ�ù������ӣ��Ͳ���ʹ�ó�������*******/
#define JUDGE_ENGINEER_LADDER_POSITION_X	360	//��������X
#define JUDGE_ENGINEER_LADDER_POSITION_Y	540	//��������Y
#define JUDGE_ENGINEER_LADDER_HEIGHT_ALL	150	//�����ܸ߶�
#define JUDGE_ENGINEER_LADDER_COLOR_ALL		Green	//����������ɫ
#define JUDGE_ENGINEER_LADDER_SPACE			75		//����2�����ߵļ�࣬Ҳ���ں��ŵ��߳���
#define JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH	10	//���Ӳ����߿��
#define JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH	10	//�����м���ߵ��߿�
#define JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_COLOR White	//�����м���ߵ���ɫ

/********************4·װ�װ����ñ����ʹ�ã�һ��Ҫ��GRAPH_USE_YAW_OR_ARMOR����Ϊ1***********************/
#define JUDGE_GRAPH_DISTANCE	200.0f		//װ�װ嵽��ת���ľ���
#define JUDGE_GRAPH_ROTATE_X	960.0f		//��ת����X����
#define JUDGE_GRAPH_ROTATE_Y	540.0f		//��ת����Y����
#define JUDGE_GRAPH_BOARD_LENGTH	50.0f	//װ�װ峤��
#define JUDGE_GRAPH_BOARD_WIDTH	20.0f		//װ�װ���


/********************7·�ַ���ͨ�����ñ�***********************/
#define CHAR_SIZE_CH1	15
#define WIDTH_CH1      2
#define COLOR_CH1      Yellow
#define POSITION_X_CH1  50  
#define POSITION_Y_CH1  880
#define SPACE_Y_CHANNEL	30

/********************7·ͼ��ͨ�����ñ�***********************/
//��������
#define GRAPH_CHANNEL_ALL_RADIUS	8	//Բ�뾶
#define GRAPH_CHANNEL_ALL_LENGTH	20	//���γ���
#define GRAPH_CHANNEL_STR_COLOR_ALL	Green
#define GRAPH_CHANNEL_STR_LARGE_ALL	15		//�ַ�����С
#define GRAPH_CHANNEL_STR_WIDTH_ALL	2		//�ַ����߿�

#define Y_Position_Delta  -20       // ͬһͨ��ͼ�����ַ���֮��ľ���
//��������
#define GRAPH_CHANNEL_DELT_POSITION  100 // ͼ�μ��
#define GRAPH_Y_POSITION 350             // ͼ������Ļ����֮��ľ���

// ��ʼ��״̬��־
#define GRAPH_USE_THIS_GRAPH_8_1		1		//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_1_POSITION_X	750
#define GRAPH_CHANNEL_8_1_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_1_WIDTH			20	//�������
#define GRAPH_CHANNEL_STR_8_1_POSITION_X	GRAPH_CHANNEL_8_1_POSITION_X		//ɫ��1˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_1_POSITION_Y	GRAPH_CHANNEL_8_1_POSITION_Y+Y_Position_Delta//ɫ��1˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_1	"Ini"	//ɫ��1����ʾ˵���ַ���

// צ�ӿ��ձ�־
#define GRAPH_USE_THIS_GRAPH_8_2		1		//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_2_POSITION_X	GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION
#define GRAPH_CHANNEL_8_2_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_2_WIDTH			20	//�������
#define GRAPH_CHANNEL_STR_8_2_POSITION_X	GRAPH_CHANNEL_8_2_POSITION_X		//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_2_POSITION_Y	GRAPH_CHANNEL_8_2_POSITION_Y+Y_Position_Delta	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_2	"Cla"	//ɫ�����ʾ˵���ַ���

// ��Ԯ�����Ŀ��ر�־
#define GRAPH_USE_THIS_GRAPH_8_3		1		//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_3_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*2)
#define GRAPH_CHANNEL_8_3_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_3_WIDTH			20	//������ȡ�
#define GRAPH_CHANNEL_STR_8_3_POSITION_X	GRAPH_CHANNEL_8_3_POSITION_X		//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_3_POSITION_Y	GRAPH_CHANNEL_8_3_POSITION_Y+Y_Position_Delta	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_3	"JYZ"	//ɫ�����ʾ˵���ַ���

// �ϰ�����Ƹ˳��ȱ�־
#define GRAPH_USE_THIS_GRAPH_8_4		1	//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_4_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*3)
#define GRAPH_CHANNEL_8_4_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_4_WIDTH			20	//������ȡ�
#define GRAPH_CHANNEL_STR_8_4_POSITION_X	GRAPH_CHANNEL_8_4_POSITION_X		//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_4_POSITION_Y	GRAPH_CHANNEL_8_4_POSITION_Y+Y_Position_Delta	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_4	"JYG"	//ɫ�����ʾ˵���ַ���

// ��Ԯ���Ƹ˳��ȱ�־
#define GRAPH_USE_THIS_GRAPH_8_5		1		//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_5_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*4)
#define GRAPH_CHANNEL_8_5_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_5_WIDTH			20	//������ȡ�
#define GRAPH_CHANNEL_STR_8_5_POSITION_X	GRAPH_CHANNEL_8_5_POSITION_X	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_5_POSITION_Y	GRAPH_CHANNEL_8_5_POSITION_Y+Y_Position_Delta	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_5	"ZAK"	//ɫ�����ʾ˵���ַ���

#define GRAPH_USE_THIS_GRAPH_8_6		0		//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_6_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*5)
#define GRAPH_CHANNEL_8_6_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_6_WIDTH			20	//������ȡ�
#define GRAPH_CHANNEL_STR_8_6_POSITION_X	GRAPH_CHANNEL_8_6_POSITION_X		//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_6_POSITION_Y	GRAPH_CHANNEL_8_6_POSITION_Y	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_6	"GRAPH_1"	//ɫ�����ʾ˵���ַ���

#define GRAPH_USE_THIS_GRAPH_8_7		0		//���������Ϊ1��ʾʹ�����ͼ�Σ�Ϊ0��ʹ�����ͼ��
#define GRAPH_CHANNEL_8_7_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*6)
#define GRAPH_CHANNEL_8_7_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_7_WIDTH			20	//������ȡ�
#define GRAPH_CHANNEL_STR_8_7_POSITION_X	GRAPH_CHANNEL_8_7_POSITION_X		//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_7_POSITION_Y	GRAPH_CHANNEL_8_7_POSITION_Y	//ɫ��˵���ַ���X����
#define GRAPH_CHANNEL_STR_8_7	"GRAPH_1"	//ɫ�����ʾ˵���ַ���


/********************YAW���PITCH�����ñ�***********************/
#define GRAPH_USE_YAW_OR_ARMOR	0	//0��ʱ��ʹ��YAW�ᣬ1ʱ��ʹ��YAW�ᣬʹ��װ�װ���ת

#define CHAR_SIZE_YAW_PIT	16
#define WIDTH_YAW_PIT     0
#define COLOR_YAW_PIT      Green
#define POSITION_X__YAW_PIT  580  
#define POSITION_Y__YAW_PIT  540


/********************��ӡ�����������ñ�***********************/
#define CHAR_SIZE_VOLTAGE_2	15	//��ѹ�ַ���С
#define WIDTH_VOLTAGE_2      2	//��ѹ�ַ��߿�
#define COLOR_VOLTAGE_2      Green	//��ѹ�ַ���ɫ
#define VOLTAGE_DONT_USE	1		//������������Ϊ1�����ǲ�Ҫ����������ʾ�ĵ�ѹ
#define POSITION_X_CAP  720  
#define POSITION_Y_CAP  1080-250
#define RECTANGLE_WIDTH	2	//�����߿��ȣ�����ҪΪż������Ȼ����治�ÿ�������Ҫ��߿�ʱ���������Ϊ0
#define RECTANGLE_LENGTH	470.0f	//�����򳤶ȡ�Ҫ����ż��
#define RECTANGLE_HEIGHT	10	//������߶ȡ�Ҫ����ż��

/********************����ߴ������ñ�***********************/
#define Judge_Car_Size_Line_Color			Green			//�ߵ���ɫ
#define Judge_Car_Size_Line_Width			0				//�߿�
#define Judge_Car_Size_BottomWidthMin		0				//����ߴ����²��ĳ��ȣ���λ�����ء���󳤶ȣ��������ܹ���С�ڴ˳ߴ���Բ��ܹ�
#define Judge_Car_Size_TopWidthMin			0				//����ߴ����ϲ��ĳ��ȣ���λ�����ء�
#define Judge_Car_Size_BottomWidthMax		0				//����ߴ����²��ĳ��ȣ���λ�����ء���󳤶ȣ���һ���ܹ�
#define Judge_Car_Size_TopWidthMax			0				//����ߴ����ϲ��ĳ��ȣ���λ�����ء�
#define Judge_Car_Size_LineHign				0				//����ߴ����ϲ������²��ĸ߶ȣ���λ������


/********************�м��������ñ�***********************/
#define Judge_DontDrawHorizontal	1	//��Ҫ�����ʱ�Ͱ��������Ϊ1��		
#define Judge_Horizontal_Line_Color	Green	//ˮƽ�ߵ���ɫ
#define Judge_Horizontal_Line_Width	2	//�߿�
#define Judge_Horizontal_Line_Length	560	//�߳�
#define Judge_Vertical_Line_Height		10		//С��ֱ�߸߶�



/********************������׼�����ñ�----�ȼ�Ϊ1ʱ***********************/
#define Judge_Equ_Line_All_Color	Green	//�ߵ���ɫ
#define Judge_Equ_Line_All_Width	0	//�߿�
#define Judge_Equ_Line_Length_Vertical	0		//�����߳���
#define Judge_Equ_Line_ALL_Position_X	940		//���Ķ�λ������X

//�ȼ�Ϊ1ʱ���������µ�һ����
#define	Judge_Equ_Line_1_1_length_S	70		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_1_length_L	118		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_1_Position_Y	900		//���Ķ�λ������Y
#define Judge_Equ_Line_1_1_Label_float	5.2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_1_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µڶ�����
#define	Judge_Equ_Line_1_2_length_S	60		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_2_length_L	106		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_2_Position_Y	480		//���Ķ�λ������Y
#define Judge_Equ_Line_1_2_Label_float	2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_2_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µ�������
#define	Judge_Equ_Line_1_3_length_S	40		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_3_length_L	70		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_3_Position_Y	460		//���Ķ�λ������Y
#define Judge_Equ_Line_1_3_Label_float	3		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_3_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µ��ĸ���
#define	Judge_Equ_Line_1_4_length_S	35		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_4_length_L	62		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_4_Position_Y	440		//���Ķ�λ������Y
#define Judge_Equ_Line_1_4_Label_float	4		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_4_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µ������
#define	Judge_Equ_Line_1_5_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_5_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_5_Position_Y	420		//���Ķ�λ������Y
#define Judge_Equ_Line_1_5_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_5_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µ�������
#define	Judge_Equ_Line_1_6_length_S	20		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_6_length_L	60		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_6_Position_Y	150		//���Ķ�λ������Y
#define Judge_Equ_Line_1_6_Label_float	5.2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_6_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µ��߸���
#define	Judge_Equ_Line_1_7_length_S	10		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_1_7_length_L	50		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_1_7_Position_Y	100		//���Ķ�λ������Y
#define Judge_Equ_Line_1_7_Label_float	5.2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_1_7_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����


/********************������׼�����ñ�----�ȼ�Ϊ2ʱ***********************/

//�ȼ�Ϊ1ʱ���������µ�һ����
#define	Judge_Equ_Line_2_1_length_S	70		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_1_length_L	118		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_1_Position_Y	400		//���Ķ�λ������Y
#define Judge_Equ_Line_2_1_Label_float	5.2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_1_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µڶ�����
#define	Judge_Equ_Line_2_2_length_S	60		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_2_length_L	106		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_2_Position_Y	480		//���Ķ�λ������Y
#define Judge_Equ_Line_2_2_Label_float	2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_2_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

//�ȼ�Ϊ1ʱ���������µ�������
#define	Judge_Equ_Line_2_3_length_S	40		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_3_length_L	70		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_3_Position_Y	470		//���Ķ�λ������Y
#define Judge_Equ_Line_2_3_Label_float	3		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_3_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ��ĸ���
#define	Judge_Equ_Line_2_4_length_S	35		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_4_length_L	62		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_4_Position_Y	465		//���Ķ�λ������Y
#define Judge_Equ_Line_2_4_Label_float	4		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_4_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ������
#define	Judge_Equ_Line_2_5_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_5_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_5_Position_Y	465		//���Ķ�λ������Y
#define Judge_Equ_Line_2_5_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_5_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ�������
#define	Judge_Equ_Line_2_6_length_S	20		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_6_length_L	60		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_6_Position_Y	150		//���Ķ�λ������Y
#define Judge_Equ_Line_2_6_Label_float	5.2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_6_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ��߸���
#define	Judge_Equ_Line_2_7_length_S	10		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_2_7_length_L	50		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_2_7_Position_Y	100		//���Ķ�λ������Y
#define Judge_Equ_Line_2_7_Label_float	5.2		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_2_7_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����

/********************������׼�����ñ�----�ȼ�Ϊ3ʱ***********************/

//�ȼ�Ϊ1ʱ���������µ�һ����
#define	Judge_Equ_Line_3_1_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_1_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_1_Position_Y	505		//���Ķ�λ������Y
#define Judge_Equ_Line_3_1_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_1_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µڶ�����
#define	Judge_Equ_Line_3_2_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_2_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_2_Position_Y	505		//���Ķ�λ������Y
#define Judge_Equ_Line_3_2_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_2_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ�������
#define	Judge_Equ_Line_3_3_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_3_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_3_Position_Y	50		//���Ķ�λ������Y
#define Judge_Equ_Line_3_3_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_3_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ��ĸ���
#define	Judge_Equ_Line_3_4_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_4_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_4_Position_Y	505		//���Ķ�λ������Y
#define Judge_Equ_Line_3_4_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_4_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ������
#define	Judge_Equ_Line_3_5_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_5_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_5_Position_Y	505		//���Ķ�λ������Y
#define Judge_Equ_Line_3_5_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_5_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ�������
#define	Judge_Equ_Line_3_6_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_6_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_6_Position_Y	505		//���Ķ�λ������Y
#define Judge_Equ_Line_3_6_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_6_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����
//�ȼ�Ϊ1ʱ���������µ��߸���
#define	Judge_Equ_Line_3_7_length_S	25		//Сװ�װ��Ӧ�߳��ȣ���λ������
#define	Judge_Equ_Line_3_7_length_L	44		//��װ�װ��Ӧ�߳��ȣ���λ����
#define	Judge_Equ_Line_3_7_Position_Y	505		//���Ķ�λ������Y
#define Judge_Equ_Line_3_7_Label_float	5		//��λ���Աߵľ����ǩ����λ��m��С�������1λ
#define Judge_Equ_Line_3_7_Length_Vertical	Judge_Equ_Line_Length_Vertical	//�����߳��ȣ�������Ҫ�����ʱ���ѳ��ȸ�Ϊ0����



/********************���ں�DMA�������ñ�***********************/

//�������
#define Judge_UseGPIO_GPIO_PeriphClock RCC_AHB1Periph_GPIOB
#define Judge_UseGPIO_GPIO_Typedef_Name	GPIOB
#define Judge_UseGPIO_GPIO_PINSource_TX	GPIO_PinSource10
#define Judge_UseGPIO_GPIO_GPIO_Pin_TX	GPIO_Pin_10
#define Judge_UseGPIO_GPIO_PINSource_RX	GPIO_PinSource11
#define Judge_UseGPIO_GPIO_GPIO_Pin_RX	GPIO_Pin_11

//�������
#define Judge_UseUART_PeriphClock	RCC_APB1Periph_USART3
#define Judge_UseUART_GPIOAF_Name GPIO_AF_USART3
#define Judge_UseUART_Typedef_Name	USART3
#define Judge_UseUART_IRQn	USART3_IRQn
#define Judge_UseUART_IRQHandler	USART3_IRQHandler
//���������
#define Judge_UseUART_Function_Name	USART3_Init
#define Judge_UseUART_SendChar	USART3_SendChar

//DMA�������
//RX��DMA
#define Judge_UseDMA_PeriphClock_RX	RCC_AHB1Periph_DMA1
#define Judge_UseDMA_IRQChannel_RX	DMA1_Stream1_IRQn
#define Judge_UseDMA_Stream_Typedef_Name_RX	DMA1_Stream1
#define Judge_UseDMA_ClearIT_RX	DMA_IT_TCIF1	//�����������Ͱ����ָ�Ϊ��
#define Judge_UseDMA_Channel_RX	DMA_Channel_4
#define Judge_UseDMA_ClearFlag	DMA_FLAG_TCIF4 | DMA_FLAG_FEIF4 | DMA_FLAG_DMEIF4 | DMA_FLAG_TEIF4 | DMA_FLAG_HTIF4		//��ͨ�����Ͱ����ָ�Ϊ��
//����
#define Judge_UseDMA_IRQHandler_RX	DMA1_Stream1_IRQHandler
//TX��DMA
#define Judge_UseDMA_PeriphClock_TX		RCC_AHB1Periph_DMA1
#define Judge_UseDMA_IRQChannel_TX				DMA1_Stream3_IRQn
#define Judge_UseDMA_Stream_Typedef_Name_TX		DMA1_Stream3
#define Judge_UseDMA_ClearIT_TX	DMA_IT_TCIF3	//�����������Ͱ����ָ�Ϊ��
#define Judge_UseDMA_Channel_TX					DMA_Channel_4
//����
#define Judge_UseDMA_IRQHandler_TX	DMA1_Stream3_IRQHandler







//////////////////////////////////////////////////////////////////////////////////////////
//****************************************************************************************
//########################################################################################
//�����ǽӿں������������ǽӿں������������ǽӿں������������ǽӿں������������ǽӿں��������Լ���Ҫʲô���ݾ�д��������ʲô����
//����





//�����ǽӿں������������ǽӿں�����,�����ǽӿں������������ǽӿں������������ǽӿں�����
//########################################################################################
//****************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////

/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :�ú����ǵ�һ����ֲ����ϵͳ������Ҫ�ܵ�һ�����Ժ���
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */
void Draw_DmaDoubleBuffTest(void);

/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :�ú����ǲ���ϵͳ��ʼ������
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */
void Judge_Init(void);
/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :�ú������ڲ����ֽ�����ʾ�������������ĺ�����Percent�ǰٷֱȣ�Voltage�ǵ�ѹֵ
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */
int8_t PrintfVoltageToScreen(float Votlage2,float Percent);
  
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//�����ǽӿں���

/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :Judge_GetRobotState�����ǻ�û�����״̬�����ĺ���
  * Description        :
  * Description        :
  * Description        :
  * Description        :
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */



int8_t PrintfYawPitchToScreen(float YawAngel,float PitchAngel);
int8_t PrintCircleColor(uint8_t WhichChannel,graphic_color_tpye_e NextColor);
int8_t PrintfToScreen(uint8_t WhichChannel,char *STR);
//����Ļ�ϴ�ӡ�������ݵ�ƽ����ʹ���ַ���
void Judge_LoopPer1MS(void);
void Draw_EqualHeightLine(uint8_t RobotLevel);

ext_game_robot_status_t* Judge_GetRobotState(void);

ext_power_heat_data_t* Judge_GetRobot_power_heat(void);

ext_shoot_data_t* Judge_shoot_data(void);

ext_game_robot_status_t* Judge_robot_status(void);

ext_power_heat_data_t* Judge_heat(void);

ext_game_robot_pos_t*	Judge_GetRobotPosition(void);
//��ӡװ�װ���ת�ǶȺ�װ�װ���ɫ��10HZ���Ƕ�0-360����ʱ��Ϊ��
int8_t PrintArmorRotate(float Yaw,graphic_color_tpye_e Armor_1,graphic_color_tpye_e Armor_2,
						graphic_color_tpye_e Armor_3,graphic_color_tpye_e Armor_4);

int8_t Judge_AngineerPrintLadder(float Percent);//���̻�����

/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :Judge_GetFlag�����ǻ�û�����ĳ��������û�и��µĺ���
  * Description        :����ֵ�Ǹò������¹��˶��ٴ�
  * Description        :����ֵ��Ҫ����ĳ���ṹ��
  * Description        :
  * Description        :
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */
uint16_t Judge_GetFlag(frame_cmd_id_e WhichMsg);



/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :Judge_ClearFlagOf������������±�־λ�ĺ���
  * Description        :
  * Description        :����ֵ��Ҫ�������FLAG��ĳ���ṹ��
  * Description        :
  * Description        :
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */  
void Judge_ClearFlagOf(frame_cmd_id_e WhichMsg);



/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :void Judge_RobotToRobot(Robots_ID_e receiver, uint8_t *DataAddr);
  * Description        :�����˼�ͨ��
  * Description        :receiver�ǽ��շ�������ID���䶨��� Robots_ID_e
  * Description        :DataAddr��Ҫ���͵���Ϣ���ַ�����ʽ
  * Description        :
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */
void Judge_RobotToRobot(Robots_ID_e receiver, uint8_t *DataAddr);


/**
  ******************************************************************************
  * Copyright (C), 2021 - , �Ĵ���ѧ���ս�� 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021��4��3��
  * Description        :void Judge_SelfControl(uint8_t *DataAddr)
  * Description        :�Զ����������������
  * Description        :DataAddr��Ҫ���͵���Ϣ���ַ�����ʽ
  * Description        :
  * Function List      :
  * History            :
        <author>    <version>    <time>    <desc>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 XXXX.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */
void Judge_SelfControl(uint8_t *DataAddr);


#endif

























/***
 *                    .::::.
 *                  .::::::::.
 *                 :::::::::::  
 *             ..:::::::::::'
 *           '::::::::::::'
 *             .::::::::::
 *        '::::::::::::::..
 *             ..::::::::::::.
 *           ``::::::::::::::::
 *            ::::``:::::::::'        .:::.
 *           ::::'   ':::::'       .::::::::.
 *         .::::'      ::::     .:::::::'::::.
 *        .:::'       :::::  .:::::::::' ':::::.
 *       .::'        :::::.:::::::::'      ':::::.
 *      .::'         ::::::::::::::'         ``::::.
 *  ...:::           ::::::::::::'              ``::.
 * ```` ':.          ':::::::::'                  ::::..
 *                    '.:::::'                    ':'````..
 */













//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!|%%|||!;;!!!!;;!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!|%%&##@#####################$!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!|$@##############################@@@@$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!|$@#########################################$|!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!%@#############################################@@#@$|!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!|&#####################################################&%|!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!%$&@###########################################################@@$!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!$#####################################################################&|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!$#######################################################################@$!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&##########################################################################&$$|!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!$################################################################################$|!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%@###################################################################################@|!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;%@#####################################################################################$!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!$######################################################################################@@$|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%@##########################################################################################$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;|$@#############################################################################################&!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!|&################################################################################################$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;%@##################################################################################################@%!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!|&###################################################################################################@@%!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%@######################################################################################################&%!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!|&########################################################################################################@%!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%@#########################################################################################################$!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%@###########################################################################################################$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%##########################@&&@@##############################@###############################################$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!%@#####################@@##@&$$$&&@@@########################@&&&&&&@@@####@@##@&&@&&@@&&@&&@###@##############@%!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!|&##############@@#@@@@&&&@@&$%%%$$$&&@@@@@@@@@@@#########@@@&$$$$$$$&&@@&&&&&@@$$%%%%%%|%%%%%$%%%%$&@###########@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&############@@&&&&&&&&$$$&$%|%%%%%%$$$&&&&&&&&&&&@@@@##@&$$%%%%%%%%%%$$%%$%%%$%|!|!!!!!!!!!!!!!!!!||%&##########@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;|&##########@&&&$$$$$$$$%%%%%||||||||%%%%%%%%%%%%%$$$&&&$$%|||||||||||||||%||!||!;;;!;;;;;;;;;;;;;;;!!!|$@#########&|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;|@#########@&$$%%%|%%%%%%||||||||!!!||||%|||||||||||%%|||||!!!!!!!!!!!!!!!!!;;;;:::;;;:;:::::::;;:::;;;!|$@########@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!$##########@$%%%||||||||||||!!!!!!!!!||||!!!!!!!!!!!!!!!!!!;;;;!!!;;;;;;;;;;;;;:::::::::::::::::::::::;;!%&########@%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&########@@&%||||||||!!!!!!!!!!!!!!!!!!!!!!!;;;!!;;;;;;;;;;;;;;;;;;;:::;;;;::;:::::::::::::::::::::::::;!|$@########$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&########@&$|||||||||!!!!!!!!!!!!;;!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;:::::;;:::::::::::::::''::::::::::::;;;|%&########%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!$#######@&$%|||!!|||!!!!!!!!!;;;;;;;;;;;;;;;;:::::;;;::;;;;;;;;;;::::::::;:::::::::::::::'::::::::::::;;!!%&@#######%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;$#######@$%%||!!||!!!!!;;;;;;;:;;;;;;;;;;;;;:::::::::::::;;;:::::::::::::::::::::::::::::'''::::::::::;;;!|$@######@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;$######@&$%|||!!!!!!!!!!!!;;;;;;;;;;:;;:::::::::'''::::::::::::::::::'''':::::::::::''''':::::::::::;;;;;!|%$@#####&!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;%######@$%|||!!|!!!!!!!!!;;;;;;;;:::::::::::::::'''''''::::::::::::''''''''''''''''''''''::::'':::::::;;;;!|$&#####%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&####@$%||||!!!!!!!!;!;;;;;;::;;;:::::::::::::''''''''''':::::::::'''''''''''''''''''''''''':::::::::;;;;;|%&####@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;|@####&%|!!!!!;;;!;;;;;;;;;;;;;;;;;:::::'':''''''''''''''''''''''''''''''''''''''''''''''''''':::::::::;;;;!%&@###@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!$####$|!!!!!;;;;;;;;!!!!!!||!!!!;;;;::::::::'::''''''''''''''''''''''''''''''''''':''::::'''''':::::::::;;;|$@###$!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;%###@%!;!!!!;;;;;;|$&&&$$$$%%%%|||!!;;;::::::::':::''''''''::::'''''''''':::::::::;;;;::;;;;;;;:'':::;;;;;;!%@##&|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&##@|!!!!!;;;!|$&@@@@@@#####@@@@@@&&$%|!!;;::::::'''''''::::''''''':::::;;;;;!!||||!!!|||||||%|!:'::;;;;;;!%@##%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;$##@|;;!!!!|%$&@@@@@###############@&&$%%|!!!;;::::::::''::::''''::;!!!|%%|%$&&&$%$&&&&$$$$$$$$$%|;;;;;;;;!$##@|;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;|@#@%!!!!!|$&@@@@@@@&&&&&&&&@@&&&&@@@&&$%%|||!!;;::::::::::::::::;;!!|||%%$$$&&&@@&&@@@&&&&&&&&$%%%|!!;;;;!$##%;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//:;;;;;;;;;;;;;;;;;;;;;;;;;;;:::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::;;;;;;;;;;;;;;;;;;;;;;;;;:::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!&#@%!!!!|%%%||%%||||||||||||||||%%%$$$%%%%|||!!!!!;;;;;:::::::;;;!||||%%%%%$&&$$&&&&&&$$$%$$%%%%|||||!;::!&#&!;;;;;;;;;;;;;:::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:::;;;;;;;;;;;
//:;;;;;;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;;::;;;;;!;;;%##%;;;;;!!||%%%%|||!!!!!!!!!!!||||%%%%%%%%%%||||!!!;;;;;;;;;;;!!!|||||||||||||||||!!!!!!!!!!||!||!!!!!;:!&#$;;;;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//:;;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;::;;;!|%$$%%@@|;::::;!||||||||!!!!!!!!!!!!!!!|||%%%%%%%%%%|||!!!!;;;;;;;;;!!!!||||||%%%%%||||!!!!!;;;;!;;;;;:;;;;;::|@@|;;:;;;:;;;;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//';;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;!%||%$&@#@|::::;;!!!||||||||||||||||||!|||||||%%%%%%%%||||!!!!!;;;;;!!!!|||||%%%%%%%%%|||!!!!;;;;;;;;;;!;;;;::::!@&!;;;;;:;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//';::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;%@@&%%$&#&!::::;;!!!||%%%$$&&@##########@&$%%||%%%%%%%|||!!!!!;;;;;;;!!!|||%%%%%$$$$$$$$$%%%|||||!!;;;;;;;;;::::!&@$%|!;;:::;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!$@@@$%&#$;::;;;!!|%$&@#####$||&####&|$##&%&@$%%%%$$%%%||!!;;:::::;;;!!!||%%%%$$&@###############@$%|!!!;;;:::'';$&!;;;|&$!;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;|&@&%$&@%:::;;!!|$&@####@$!;;!@#########$::%@&%|%%%%%%||!;::''``''::;!!||%%%$&&$|$#########$:''!&###@$%|!;;::'':|%;:!&@&|;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;|$%%$@&!:::;!!|%%$$$&&&@&$|!!$########@!`';|&&|;!||%%|!;;:''`````'':;;;!!|%$$|;;%#########$:..`;%$&@&$%|!;::'''||;!$@&%;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;|%$&$;:;;;;;!!!!||%%%%%$$$$$$@#####&|!|$$@@&|;;!||||!;::''`````'':::::;!%$$$$||&#######$:';|%$%|!!!!!!;:'''''!!::|&%!::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!%&&@%;::;;;;;;!!!!!!!|!!!!!||%%$$$$%|||||!!!!;;!!||!!;;::'`````''':'''::;|%$$$$$&&@&&$&&$%|!;;;;;;;:::''''''':;::;!;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!$&@&|::::;;;;;;;;;;;;!!!!!!!!!!||||!!!!!!;;;;;!!!||!;;;::''`````'''''':::;;!!||%%||!;;:::::;:::::::::'''''''':;!;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!%&@&!::::::::;;;;;;;::;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!;;::'''`'```''''':''::::;;;;;;;;;;;;;::::'''''''''''''''':!|!;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;%&@&!:::::::;;;::::::::::::::::::::;;:::::;;;;!!!!!;;;;:'''``````'''''''''':::::::::''''''''''''''''''''``''':!%!:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!$@&!::::::;;;;::::::::::::::::::::::::::::;;;!!!!!;;::::''```````'''``````'''''''''''''``````````````````''':!|;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!$$;'''::;;;;;;;::::::::::::::::::''::::::;;;;;;!!;;::::'''''`````````````````'''''''''``````````````````''':!!;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;||;'''::;;;;;;;:::::::::::::::::::':::::;;;;;!!!!;::::::'''''''````````````````````'''''``````````````''''';|!:'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!%!''':;;;;;;;;;;;:::::::::::::::::::::;;;;;!!!;;:::::''''''''''````````````````````'''''''``````````'''''::::':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;||:'':;;;;;;;;;;;;;;;::::::::''':::::;;;;;;;;;;:::::'''`''````''```````````````````''''''''``````'''''''':;;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::!|;'':;;;;;;;;;;;;;;;::'':'''''::::;;;;;;!!;;::::::'''``'``'```````````````````````````'''''``'''''''''':;;:'::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//'::::::'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':::::;!%|:':;;;!!!!;;;;;::::::''''':':::;;;!!||!!;;::::::''````````''`''''''``````````````````'''''''''''''''::::::::::::''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//':::'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':::::;||;':;;!!!!!;;;;;;::::::'':::::::;;!|||!;;;;;:::::''`````````'''::::::'''```````````````''''''''''::::::::::::::::''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//':':'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''::'::;|!::;;!!!!!;;;;;;;:::::::::::::;;!|%!;;::;;;:::::''`````````'''''::::''''``````````'''''''''''::::::;:'''':::::''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':':;|!:;;;!!!!!!!!;;;:::::::::::::;!|%!;:::;;;;;;:::''````````'''````'''''''''''```````'''''''':::::;;;;::::':''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':'':;;!!!!!!!;;;;;;;;:::::::::;!|!;:::;;;;!!;;;::'''''''''''``````'''''''''''''''```''''''::::;;;;;;;::'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;!!!!!!!!;;;;;;:::::::::;!||!;;!!!!!|||!!!;;::::::::;::''''``'''```'''''''''''''''':::::;;;;;::''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;;;!!!!!!;;;;;;;;;;::::;;;!|%|||$&@##@&%%||!!!;;;;!|&@@&$|;::::'```````''''''''''''::::;;;;;:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;!!!!!!!!!!;;;;;;;;;::::;:;;!%%$%%%$&&@@@@&$%%|||!!!|||%%%||!;:'```````''''''''''''::::;;;;;::''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;;!!!!!!!!!!;;;;;;;:::::::::;;;!|%%%$$%%%%%|||!;::::;;;;!!!!;:'```````````''''''''''::::;;;;:'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;;;!!!!!!!;;;;;;;;;:::::::::;;;;;!|||%||!!;;;;;;::;;;;::::''``````````````'''''''::::::;;;::'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''::;;;!!!;!!;;;;;;;;;::::::::::;;;;!!|||||!!!;;;;;;;;;;;;;:''```````````````''''':::::::;;;;:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''::;;;!!;;!!!!!!;;;;;;;;;;;;;;;;;!!|||||||!!!!!!!!!;;;;;;;::''''````````````''''''''':::;;;::''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''::;;!!!;!!!!;;;;;;;;;;!!|||||||||||||!!!!!!!!!!;;;;;!!;;;:::::''''``````'''''''''':::;;;;:'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''::;;!!!!!!;;;;;;;;!||%$$%%%%%%%||!!!;;::::;;;;::''':;;;;;;;;;;;;:;::''``''''''''::::;;;;:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;;!!!!!!;;;;;;;!%$$$$%|||||!!!;;;;;;!;;::''''':::'''''''::;;;!!!!!;:'''''''''':::;;;;;:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':
//`'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;;!!!!!;;!!;!!|%%%%%%%%%|||!||%%$$%%%%%%|!!||||!!!||!;:''::;;!!!||!;::::'''::::;;;;!;:''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':;;!!!!!!!!!!|||||%$&@@@@@@@@@@@&&$$$$$$$%$$$%%%%%%$$$$%||||%$$%||!!;::::::::;;;;!!!:'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//`'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''`''`'''':;!!!!!!!!!!|||||||%%%&@####@@@@@@@&&&&&&&&&&&&$$%%%%$$&&&&@@@&%|!!;;:::::::;;;;!!!:'`''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//`'''`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````''```''':;!!!!!!||||||%%%%%%%%%$&&&&$$%%|||||!!!|||!;;;;;;!!!!||||!;!|||!!;;;;:::;;;;!!!!;'`````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````'':;!!!!!|||||%%%%%%%%%%%%$$&$$$%%%||!!;;!!;;;;;;;;!!!||!;:::;;;!!!;;;;;;;;;;!!||;''`````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````':;!!|||%%%%%%%%%%|||%%%%%$$&&&&$$%|||||||||||||%%||!!;;;;;;;;;;;;;;;;;;;;!!||!:'``````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````';!!!|%%%%%%%%%%%%||||%%%$$&&&&&&&&&$$$$$$$$$$%%%||!!!!!!;;;;!;;;;;;;;;!!|||%$!```````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````';||%%%%%%%$$$%%%%%%%%%%%$$$&&&&&&&&&&&&&&$$$%%||||!!!!;;!!!!!!!;;;;;!!!|||$$;```````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````'!|%%|%%%%$$$$$$$$$$%%%%%%%%|||||||||||||||||||||||||!!!!!!!!!!!!!;;;!||||!$&;```````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````':!|%$$%%%%%%%%%$$$$$$%%%%%%||||||!!!!!!!!!!!!!|!!!!!||||!!!!!!;;;;;;!|||!!!$&;```````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````:!%$&&&$%%%%%%%%%%$%%%%%%%|||||!!!!;;;;;;::::;;;;;;!!!!!!!!;;;;;;;!!|%|!!!!&&;```````````````````````````````````````````````````````````````````````````````````````````````````````````````````'
//``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````'%$|$##@@@$|%$&&&&&$$%%%%%%%%%%%%%%||||!!!!!;;;;;::::''''':::;;;;;;;;;;;;;;!||%|!!!!!%&$$$|%&$||:``````````````````````````````````````````````````````````````````````````````````````````````````````````'
//`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````!@#########$%$&&&&&@&&$%%%||||%%|||||!!!!!!!!!;;;;:::::''''''::::::;;;;;;;!!|%|!!!!!!|@###########|'````````````````````````````````````````````````````````````````````````````````````````````````````````'
//.``````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````'%##########@$$&&&&&&&&@&&$%|||||||||||!!!!!!!!!;;;;;;;::::''':::::::::;;;!!||||!!!;!!!|@############@|'``````````````````````````````````````````````````````````````````````````````````````````````````````'
//.````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````'%############@$&@@@&&&&&&&&&&%%%%|%%%||||!!!!!!!!!!!!!!;;;;::::::::::::;;;!|%%|!!!!!!!!!|&##############@|'````````````````````````````````````````````````````````````````````````````````````````````````````'
//.```````````````````````````````````````````````````````````````````````````````````````````````````````````````;|!'````````;&#############@&@##@@@&&&&&&&@&&$$$%%%%%%||||||!!!!!!!|!!;;;;;::::;;;;;;;!|%%||!!!!!!!!!!!$#################|```````````````````````````````````````````````````````````````````````````````````````````````````'
//.````````````````````````````````````````````````````````````````````````````````````````````````````````````:$#####$:``'''|@####################@@@&&&&&&&&@@@&&&$$$$%%%%||!!!!!!!!!!!!!!;;;;;;!!!!||%%||!!!!!!;!!!!!!%@#################&;`````````````````````````````````````````````````````````````````````````````````````````````````'
//.`````````````````````````````````````````````````````````````````````````````````````````````````````````'%######################################@@&&&&&&&&&&@@@@@&&&$$$%%%|||||||%%||||||!!|||||%%%||!!!!!!!!!!!!!!!||&###################%'```````````````````````````````````````````````````````````````````````````````````````````````'
//.````````````````````````````````````````````````````````````````````````````````````````````````````````;&########################################@@&&&&$$&&&&@@@@@@@@@&&$$$$$$$$$$$$%%%%%%%%$$$$%|!!!!!!!!!!!!!!!!!||||!%####################@%!;:'````````````````````````````````````````````````````````````````````````````````````````'
//.```````````````````````````````````````````````````````````````````````````````````````````````````````!@##########################################@@&&$$$$$$&&&&@@@@@@####@@@@@@@@@#@@@@@&&$%|||!!!!!!!!!!!!!!!!!|||%%!:|@################################$||$@##|`````````````````````````````````````````````````````````````````````````'
//.````.``.......................................................................................````````|#############################################@@&&$$$$$$&&&&&@@@@@@@@@@@@@@&&$$$$%%%%|||!!!!!!!!!!!!!!!!!|!||%%|!;!&#######################################&:```````````..............................................................'
//.`...............................................................................................````'$##############################################@@&&$$$$$$$$$&&&&&&&&&@@@&&&&$$$$%%%|||||!!!!!!!!!!!!!!!||||%$%|!!!!$###########################################@%:```````..............................................................'
//.`..................................................................................................`!################################################@@&$$$$$$$$$$$$$$$$$$&$$$$$$$%%%%||||||!!!!!!!!!!!!!||||%$%||!|||%@################################################%`.``...............................................................'
//.`..................................................................................................`;@###############################################@@@&$$$$$$$$$$$$$$$$$$$$$$$$%%%%||||||||||||||||||%%$&@&|;!||%%%$##################################################|`..................................................................'
//.....................................................................................................`!@################################################@&&&$$$$$$$&&&$$$$$$$$%$$$%%%%%%|%||||%%%%%%$$$&@#$||!!||%%%$@###################################################|``..``.............................................................'
//.....................................................................................................'!%&##########################################&|$@#@@@&&&&$$$$$&&&&&&&&$$$$$$$$$$$$$$$$$$$$&&&@@#@&|;!!|%%%$$%$@#####################################################&:`................................................................'
//................................................................................................`:%@###@@###########################################&%!!%@@@&&&&&$$&&&&@@@@@@@@@@@@&&&&&&@@@@@@###@$%!!!!!|%%%%$%$@#########################################################%'`..............................................................`
//...........................................................................................`';%&#####################################################@&$%|!%@@@@&&&&&@@@@@@#############@&@&$%|!|!;!!!!||%%$$$$$&############################################################@%'.`...........................................................`
//.......................................................................................`:%@#############################################################&$%%%%%%|%|||!|||||!|||||%|||!!!!;!!;!!;!!!||||%%$$$%%$@###############################################################&:............................................................`
//...........................................................`;$###&&@####&|;`.....'!$&@##################################################################@&$$$$%%%%|%%||||%||||!!|!;;|!;!|!!|!;!!|!;!||||%%%$$@#################################################################%'............................................................`
//.......................................................`|@####################@@#########################################################################@&&$$$$$$$$$%$%|%%||||!|||!||!!!!;!!;!!!||||||%%%$&##################################################################%`.............................................................`
//....................................................:$####################################################################################################@&&&$$$$$$$%%%|||!|%%!!|!!!|!!!!;!!;!|!!|||||%$@####################################################################|..............................................................`
//.................................................`!########################################################################################################@&$$%%%%%%|%%|||!!||!!||!||!;!!!;!!!!!!!!||%@#####################################################################&;..............................................................`
//...............................................:$#############################################################################################################@$$%%%%!|%|||!!!|!!||;;;!!;!!;!!!||!|%$@#########################################################################@!`...........................................................`
//.............................................:&################################################################################################################@$$%%%|||!||||||||%%||||!!!!;!|||%%&################################################################################$:`......'|@#######@%:....................................`
//............................................;@###################################################################################################################@$$$$$$%%$$%%%%%%%$%|$$%%$%%%%$@####################################################################################@&!:$#################$!`...............................`
//...........................................'$#######################################################################################################################@$$%||||||||!||!;!|!!%%%%&@#########################################################################################@#######################|`...........................`
//...........................................;@##########################################################################################################################@$|||||||||!|||%%$&&@######################################################################################################################$'.........................`
//..........................................:&###################################################################################################################################@####################################################################################################################################%`.......................`
//......................................:$#############################################################################################################################################################################################################################################################################@!......................`
// ...................................;@################################################################################################################################################################################################################################################################################@;.....................`
// .................................;@###################################################################################################################################################################################################################################################################################$'....................`
// .............................`:$#######################################################################################################################################################################################################################################################################################|....................`
// ...........................!@##########################################################################################################################################################################################################################################################################################&:...................`
// .........................`%#############################################################################################################################################################################################################################################################################################&;..................`
// .......................`|##################################################################################################################################################################################################################################################################################################&;`..............`
// ......        ..  ...`|#######################################################################################################################################################################################################################################################################################################@!.......     `
// ..               ...!#############################################################################################################################################@##############################################################################################################################################################&:....     `
// ..             ...!@#############################################################################################################################################@%;;;!%@###########################################################################################################################################################%`......`
// .             .`%#################################################################################################################################################%;;;;|@##############@##############################################################################################################################################$'. . `
//         .. .'%##########################################################################################################################################################################################################################################################################################################################%`..`
//         ..|##################################################################################################################################################################################&&@#########################################################################################################################################@!.`
//         .:&################################################################################################################################################################@%$###############@@#############################################################################################################################################&
//        .;@##################################################################################################################################################################################################################################################################################################################################@
//     :&#############################################################################################################################################################################$||%%%%%&################################################################################################################################################@
//    '$##############################################################################################################################################################################|'''::;|&################################################################################################################################################@
//    :&##############################################################################################################################################################################%'''::!%@################################################################################################################################################@
//   .|###############################################################################################################################################################################$:'::!%&#################################################################################################################################################@
//  .|######################################################################################################################################################################$!;;;!!!!|$@@######################################################################################################################################################@
// :&#######################################################################################################################################################################$;:'''''':$########################################################################################################################################################@
//$#########################################################################################################################################################################$;''''''':%########################################################################################################################################################@
//$#########################################################################################################################################################################&!::''''':%########################################################################################################################################################@
//$########################################################################################################################################################################&@###@@@@@##########################################################################################################################################################@
//$########################################################################################################################################################################@&##################################################################################################################################################################@
//$########################################################################################################################################################################@&@#################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$######################################################################$::!%&###################################################################################################%%###########################################################################################################################################################@
//$#####################################################################&|$####@%!;|&##########################################################################################################################################################################################################################################################@
//$#####################################################################||@###@$&@###$!:!&#####################################################################################################################################################################################################################################################@
//$####################################################################$!$###&$$&##@###@@######################################################################################################################################################################################################################################################@
//$###################################################################@|%###@@&@$$@###@%$######################################################################################################################################################################################################################################################@
//$###################################################################%|@####@$|%#####$%#######################################################################################################################################################################################################################################################@
//$##################################################################&|&#######$!%@##@%&#######################################################################################@%|%$@##########################################################################################################################################################@
//$#################################################################@%$@######@&@####$$########################################################################################@%!;!$##########################################################################################################################################################@
//$#################################################################&%&@@@##########&$#########################################################################################@|;!|&##########################################################################################################################################################@
//$################################################################@$$@&&@##########$&##########################################################################################$!|$###########################################################################################################################################################@
//$################################################################&$@@@@##########&$##########################################################################################################################################################################################################################################################@
//$###############################################################@$&@@@##########@$@##########################################################################################################################################################################################################################################################@
//$###############################################################&&@@&@##########&&###########################################################################################################################################################################################################################################################@
//$###############################################################&@#@@@#########&&############################################################################################################################################################################################################################################################@
//$##############################################################@&#@@@##########&@############################################################################################################################################################################################################################################################@
//$##############################################################@@@@@##########&&#############################################################################################################################################################################################################################################################@
//$#############################################################@@#@@##########@&##############################################################################################################################################################################################################################################################@
//$#############################################################@@#############&@##############################################################################################################################################################################################################################################################@
//$############################################################@@##@##########@&###############################################################################################################################################################################################################################################################@
//$############################################################@##############@################################################################################################################################################################################################################################################################@
//$############################################################@#############@&################################################################################################################################################################################################################################################################@
//$##########################################################################&@################################################################################################################################################################################################################################################################@
//$#########################################################################&&#################################################################################################################################################################################################################################################################@
//$#########################################################################&##################################################################################################################################################################################################################################################################@
//$########################################################################&@##################################################################################################################################################################################################################################################################@
//$########################################################################@###################################################################################################################################################################################################################################################################@
//$#######################################################################@@###################################################################################################################################################################################################################################################################@
//$##############################################################@&@######@####################################################################################################################################################################################################################################################################@
//$#################################################################@@#########################################################################################################################################################################################################################################################################@
//$###################################################################&&@######################################################################################################################################################################################################################################################################@
//$#####################################################################@######################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$############################################################################################################################################################################################################################################################################################################################################@
//$#########################################@&####################################################################################################################################################################################################################################################################@&@##########################@
//$########################################&$$@###################################################################################################################################################################################################################################################################@&@@#########################@




//                                                                                                                                                                                                                                  .....                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                 .......                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                .........                                                                                                                                                                                                                  
//                                                                                                                                                                                                                               ...........                                                                                                                                                                                                                 
//                                                                                                                                                                                                                              .............                                                                                                                                                                                                                
//                                                                                                                                                                                                                             ...............                                                                                                                                                                                                               
//                                                                                                                                                                                                                            ....                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                            .                                                                                                                                                                                                              
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                   .'`                                                                                                                                                                                                                     
//                                                                                                                                                                                                                                  `!|;`                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                 `!: `:'                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                '!'   .:'                                                                                                                                                                                                                  
//                                                                                                                                                                                                                               :!`      ::                                                                                                                                                                                                                 
//                                                                                                                                                                                                                              :;.        ':.                                                                                                                                                                                                               
//                                                                                                                                                                                                                             ;;    `!:    `:.                                                                                                                                                                                                              
//                                                                                                                                                                                                                           .;;    '%$$;    `:`                                                                                                                                                                                                             
//                                                                                                                                                                                                                          .!'    :$&&&&;    .:`                                                                                                                                                                                                            
//                                                                                                                                                                                                                         `!'    ;$$&&&&&!.   .:`                                                                                                                                                                                                           
//                                                                                                                                                                                                                        ';`    ;$$&&&&&&&|`    ''                                                                                                                                                                                                          
//                                                                                                                                                                                                                       ';.   .!$$$$$$$$$&&%'    ''                                                                                                                                                                                                         
//                                                                                                                                                                                                                      :;.   .!$$$$$$$$$$$$$%'    `'.                                                                                                                                                                                                       
//                                                                                                                                                                                                                     ;;    `|$$$$$$$$$$$$$$$$:    `'.                                                                                                                                                                                                      
//                                                                                                                                                                                                                   .;'    '%$$$$$$$$$$$$$$$$$$;    .:`                                                                                                                                                                                                     
//                                                                                                                                                                                                                  `;'    :%$$$$$$$$$$$$$$$$$$$$!.   .'`                                                                                                                                                                                                    
//                                                                                                                                                                                                                 `;`    :%$$$$$$$$$$$$$$$$$$$$$$|`    ''                                                                                                                                                                                                   
//                                                                                                                                                                                                                ';`    ;%$$$$$$$$$$$$$$$$$$$$$$$$|`    ''                                                                                                                                                                                                  
//                                                                                                                                                                                                               :;.   .!$%%%%%$$$$$$$$$$$$$$$$$$$$$|'    `'                                                                                                                                                                                                 
//                                                                                                                                                                                                              ;;    `!%%%%%%%$$%%$%%%%%%%%%$$$$$$$$%:    `'.                                                                                                                                                                                               
//                                                                                                                                                                                                            .;:    `|%%%%%%%$$$$$%%%%%%%%%$%$$$$$$$$$:    .:.                                                                                                                                                                                              
//                                                                                                                                                                                                           .;'    '|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$;    .'`                                                                                                                                                                                             
//                                                                                                                                                                                                          `;'    :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$!.    '`                                                                                                                                                                                            
//                                                                                                                                                                                                         `;`    :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%!`    ''                                                                                                                                                                                           
//                                                                                                                                                                                                        ';.    ;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|`    `'                                                                                                                                                                                          
//                                                                                                                                                                                                       :;.   .!%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|'    `'.                                                                                                                                                                                        
//                                                                                                                                                                                                      ::    `!%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%:    `:.                                                                                                                                                                                       
//                                                                                                                                                                                                    .;:    '|%%%%|%%%|%%%%%%%%%%%%%|%%%%|||%%%%%%%%%%%%%%%%%%:    .'`                                                                                                                                                                                      
//                                                                                                                                                                                                   .;'    '|%%%%|%%|||%%%%%%%%%%%%|||%%||||||||||||%%%%%%%%%%%;.    '`                                                                                                                                                                                     
//                                                                                                                                                                                                  `;`    :%%%%%%||||||%%%%%|||||||||||||||||||||||||%%%|||%%%|%!.    ''                                                                                                                                                                                    
//                                                                                                                                                                                                 ';`    :%%%%|||||||||%|||||||||||||||||||||||||||||||||||||||%%!`    `'                                                                                                                                                                                   
//                                                                                                                                                                                                :;.   .;%%||||||||||||||||||||||||||||||||||||||||||||||||||||||||'    `'                                                                                                                                                                                  
//                                                                                                                                                                                               :;    .!%%||||||||||||||||||||||||||||||||||||||||||||||||||||||||||'    `:.                                                                                                                                                                                
//                                                                                                                                                                                              ;:    `!||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||:    .'`                                                                                                                                                                               
//                                                                                                                                                                                            .;:    `!||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||:    .'`                                                                                                                                                                              
//                                              ........................                                                                                                                     `;'    '|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||;.    '`                                                                                                                                            .                                
//                                               .....................                                                                                                                      ';`    :|||||||||||||||||||||||||||||||||||||||||||||!!!!||!||!!|||||||||||||!`    ''                                                                                                                                                                            
//                                                ................                                                                                                                         ';.    ;|||||||||||||||||||||||||||!|||||!!!!!!!!!!!!!!!!!!!!!!!!!||!!|!!||||||!`    `'                                                                                                                                                                           
//                                                  .............                                                                                                                         :;.   .;|||||||||||||!|||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||!'    `'.                                                                                                                                                                         
//                                                   ...........                                                                                                                         :;.   `;||||||||||||!!!!||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'    .'.                                                                                                                                                                        
//                                                    .........                                                                                                                        .;:    `!||||||||||!|||!!!||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:    .'`                                                                                                                                                                       
//                                                     ......                                                                                                                         .;'    '!|||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:     '`                                                                                                                                                                      
//                                                       .....                                                                                                                       `;`    '||||||||||!!!!!!!!!!|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;.    ''                                                                                                                                                                     
//                                                        ....                                                                                                                      ';`    :|||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;`    `'                                                                                                                                                                    
//                                                         ...                 '||;;;;;::::::::::::::::::::::::::::::::::::::::'''''''''''''''''''''''''''''''''''''''''''''''''''''`    .:||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`    .````````````````````````````````````..``....................................``````````````````````':`                                                               
//                                                          ..                  `!:                                                                                                     .;|||!|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;!!!;;;!;;;;!!;;;!;;;;;;;;!!!!!!!!!!!!!!'                                                                                                     .'`                                                                
//                                                                               .!;                                                                                                   `;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;!!!;;;;;;!;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!:.                                                ..   ........................................     `'.                                                                 
//                                                                                 ;;.   .!$$$$$$$$$$$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%|||||||||||||||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!|||||||||||||||%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$'    `'.                                                                  
//                                                                                  :!.   .!$$$$$$$$$$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||%%||%||||||||||||||||||||||||||||||||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!||||||||||||||||||%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$&&$&&&&&&%'    `'                                                                    
//                                                                                   '!`    ;$$$%$$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||||||||||||||||||||||||||||||||||||||||||||||||||||!|||||!!!!!!!!!!!!!!!!!!!!!!;;!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!|||||||||||||||||%%%%%%%%%%%%%%%%%%%%$%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$$$&&&&&&&|`    ''                                                                     
//                                                                                    `!'    :%%$%%%%%%%%%%%%%%%%%%%%%%||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||!!!!!!|||||!!!!!!!!!!!!!!;;!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!|||||||||||||||||||%%||||||||||||%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$&$&&&&!.    '`                                                                      
//                                                                                     `!:    '%$%%%%%%%%%%%%%%%%%%%|||%|||||||||||||||||||||||||||||||||||||||||||||||||||||!!||!!!!!!!!!!!!!||!!||!!!!;!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!|!!!!!!!!!!||||||||||||||||||||||%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$&&;    .'.                                                                       
//                                                                                      .;;    `|%%%%%%%%%%%%%%%%%%||||||||||||||||||||||||||||||||||||||||||||||||||!!|||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!|!|||||||||||||||||||||%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$:    .'.                                                                        
//                                                                                        ;;    `!$%%%%%%%%%%%%%%%|||||||||||||||||||||||||||||||||||||||||!||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:````````````````````````````````````````````````````````````````':;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!||||||||||||||||||||%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$%:    .'                                                                          
//                                                                                         :;.     `''''''````````````````````````````````````````````````````````````````````````````...........';!;!!!!!!:. :!|!!!||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;``:;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!|||||||||||||||||||%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$%'    `'                                                                           
//                                                                                          '!`                                                                                                    ';!!!;;;;;: .;!!!!!!!!!!!!!!!!!!!;;!!!;!!!;!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;``:;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$|`    ``                                                                            
//                                                                                           '!'                                                                       `:;:;;;'.      ';;;;;;'      .:!;!!!;;;;` `!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;``:;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!||||||||||||||||||%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$!.    ``                                                                             
//                                                                                            .!:    '%%%%%%%%%||||||||||||||||||||||!|||||!!!!!!!!!!!!!!!!!!!!!!'      .:!!!!!;'      .;!!!!!!'      .;!!;;;;;!:. '!!!!!!!!!!!!!!!!!!!!!!!!!;;;;;!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;``:;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!||||||||||||||||||||%%%%%%%%%%%%%%%%%$$$$$$$$$$;.    `.                                                                              
//                                                                                             .;:    '|%%%%|||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`      `;!!!!!;`      `!!!!!!;`      ';!;;;;;;;' .:!!!!!!!!!!!!!!!!!!!;!!!;!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;``:;;;;;;;;;;;!!!!;!!!!!!!!!!!!!!!!!!||||||||||||||||||%|%%%%%%%%%%%%%%%%$$$$$$$$$;    .`.                                                                               
//                                                                                              .;;    .!%%%%%|||||||||||||||!|||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;.      '!!!!!!:.      '!!!!!!:.     .:!!;;;;;;;` `;!!!;!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;``:;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!||||||||||||||||||%%%%%%%%%$%%%%%%%$$$$$$$%:    .`.                                                                                
//                                                                                                :;.   .;%%|||||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:      .:!!!!!;'      .:!!!!!!'      .;!;;;;;;;:. '!!!!!!!!!!!!;;!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;``:;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!||||||||||||||||%%%%%%%$%%%%%%%%%$$$$$$%'    .`                                                                                  
//                                                                                                 :;.    :%%%%||||||||||!||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`      `;;;!;;;`      `;!!!!!;`      `;;;;;;;;;'..:!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;``:;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!|||||||||||%%%%%%%%%%%%$$%%%%%$$$$$|`    ``                                                                                   
//                                                                                                  '!'    :%%||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;!!;!!!;;;;!!;!!!;.      ';!;;;;:.      '!!!!!!:.      ';!;;;;;;;` `;!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!;``:;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!|||||||||%%%%%%%%%%%%%%$$%%%%%%$$$!.    ``                                                                                    
//                                                                                                   `!'    '||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!;;;;!;;;;;;;;;;;;;;;;;;!!!:      .:;;;;;;'      .:!!!!!;'      .:;;;;;;;;:. '!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;!!!!;;!;;;;;;;;;;;;;;;;;;;;;!!!;``:;;;;;;;;;!;!!!!!!!!!!!!!!!!!!!||||||||%%%%%%%%%%%%%%$$$$$$%%$$$!.    `.                                                                                     
//                                                                                                    .;:    `!|||||||||||!!!!!!!!!!!!!!!!!!!;!!;;;;;!;;;;;;;;;;;;;;;;;;;;!!!'      `;;;;;;;`      `;!;!!!;`      `;;;;;;;;;:''`''''''''``''''```````````````````''```'`.`:;;;;;;;;;;;;;;;;;!!!;``:;;;;;;;;!;!!!!!!!!!!!!!!!!||||||||||%%%%%%%%%%%%%%%$$$$$$%$$;     `.                                                                                      
//                                                                                                     .;:    `!%|||||||||!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!;.      ';;;;;;:       '!!!!!!:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'.`:;;;;;;;;;;;;;;;!!!!!;``:;;;;;;;;!!!!!!!!!!!!!!!!!|||||||||%%%%%%%%%%%%%%%%$$$$$$%:    .'.                                                                                       
//                                                                                                       :;    .;||||||||||!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!:      .:;;;;;;'      .:!!!!!!'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'.`:;;;;;;;;;;;;;;!!!!!!;``:;;;;;;!!!!!!!!!!!!!!!|||||||||||%%%%%%%%%%%%%%%%$$$$$%'    .`                                                                                         
//                                                                                                        :;.    :||||||||!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!;'      .:;;;;;;`      `;!!!;!;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;:;;'.`;;;;;;;;;;;;;;;!!!!!!!'`:;;;;;;;!!!!!!!!!||||||||||||||%%%%%%%%%%%%%%%$$$$$|'    .`                                                                                          
//                                                                                                         '!`    :|||||||!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;`      ';;;;;;:.      ';!!;;!:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'.`:;;;;;;;;;;;;!!!!!!!!;``:;!!;;!!!!!!!!||||||||||||||||%%%%%%%%%%%%%%$$$$|`    ``                                                                                           
//                                                                                                          `;`    '|||||||!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!:       ';;;;;;'      .:!;;!!;'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'.`:;;;;;;;;;!!!!!!!!!!!;'`:;!!!!!!!!!!||||||||||||||||%%%%%%%%%%%%%%$$$!.    ``                                                                                            
//                                                                                                           .;'    '!|||||!!!!!!!!!!!!!;;!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!'      .:;;;;;;`      .;!!!;;;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::;;;;;;;;;;;;;;;;;;;'.`;;;;;;;;;;!!!!!!!!!!!!'`:;!!!!!!!!!!!||||||||||||||%%%%%%%%%%%%$$$;     `.                                                                                             
//                                                                                                            .;:    `!|||||!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;`      `;;;;;;:.      ';;!;;!:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'.`:;;;;;!!;;!!;;;;!!!' .:;!!!!!!!!!!!|||||||||||||||%%%%%%%%%%%$$;     `.                                                                                              
//                                                                                                              ;;    .;|||||!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!:.      ';;;;;;'       :!!;;!!:      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'  :;;;;;;;;;;;;!!;' .:;!!!!!!!!!!!!!!|||||||||||||||%%%%%%%%%%%:    .`                                                                                                
//                                                                                                               :;.   .;|||||!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!'      .:;;;;;;`      .:;;!!!;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'  :!;;;;;;;;;;;;!;' .:;;;!!!!!!!!!!!|!!||||||||||||||%%%%%%%%%%|'    .`                                                                                                 
//                                                                                                                '!`    :||||!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;`      `;;;;;;:.      `;;;;;;:.      ';;;;;;;;;'.                                      ';!;;;;;;;;;;;!!' .:;;!;;!!;;!!!!!!!!!|||||||||||||||%%%%%%%%%|`    ``                                                                                                  
//                                                                                                                 `;`    '|||||!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;;;;;;;;;;;;;!:.      ';;;;;;'      .:;!;;;!:      .:;;;;;;;;:` '!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;' .:;;;;;!!;;!!!!!!!!!!!|||||||||||||||%%%%%%%%!`    ``                                                                                                   
//                                                                                                                  .;'    `!||!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!'      .:;;;;;;`      .;!;;;!;'      .:;;;;;;;;:..'!!!!!!!!!!;;!!;;!!;;!!!!!;!!!!!!!!!;;;;;;;;;;' .';;;;;;;;;;;;;!!!!!!!!!!||||||||||||||%%%%%%%;.    ``                                                                                                    
//                                                                                                                   .;:    `!||||!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;`      `:;;;;;:.      `;;;;;!;.      ';;;;;;;;;' .;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;;;;;;' .';;;;;;;;;;;;;;;!!!!!!!!!!||||||||||||||%%%%%%;     `.                                                                                                     
//                                                                                                                     ;;    `;|||!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!:.      ';;;;;;'       ';;;;!!:      .:;;;;;;;;;` `;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;' .';;;;;;;;;;;;;;;;!!!!!!!!!!!||||||||||||||%%%%%:    .`.                                                                                                      
//                                                                                                                      :;.    ;||!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;;;;;;;;;;;;;;;;;;;;;;;'      .:;;;;;;`      .;!!!!!;'      .:;;;;;;;;:.                                      .';;;;;;;;;;;;;;;;;;;;;!!!!!!!!|||||||||||||%%%%|'    .`                                                                                                        
//                                                                                                                       ';.    :||!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;`      `;;;;;;:.      `;!;;;;;`      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!|||||||||||%%%%|`    .`                                                                                                         
//                                                                                                                        ';`    '||!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!:.      ';;;;;;:.      '!!;;;;:.      :;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!||||||||||||%!`    ``                                                                                                          
//                                                                                                                         `;'    '!|!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!'      .:;;;;;;`      .:!;;;!!'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!|||||||||%%;.    ``                                                                                                           
//                                                                                                                          .;'    `!|!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;':!;;;!!!!;`      `:;;;;;:`      `;!;;;!;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;;;;;;;;;;;;;;;;;!!!!!!!!!!!||||||||%;     `.                                                                                                            
//                                                                                                                           .;:    `;!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;`  `;;;!!;;!!;.      ';;;;;;:       '!!;;!!:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;;;;;;;;;;;;;!!!!!!!!!!!!!||||||||:     `.                                                                                                             
//                                                                                                                             :;    .;|!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!'.';` ';!!!!!!!!:      .:;;;;;;'      .:!!;;;;'      `:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!;;;;;;;;;;;;;;;!!!!!!!!!!!!||||!'    .`                                                                                                               
//                                                                                                                              ';.    :!!!!!!!!!!!!!!!!!!!;!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!:.';;;:. '!!!;;!!!!`      `:;;;;;;`      `;!;;;!;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!;;;;;;;;;!!!!!!!!!!!!!!|||!'    .`                                                                                                                
//                                                                                                                              ';`    :||||!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;``::;;;;' .;!!!;;;!!;.      ';;;;;;:.      '!;;!!!:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!;;;;;;;;!!!!!!!!!!!!||||!'    .'                                                                                                                 
//                                                                                                                             ';.    :||||||||!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!'.'::;;;;;;' `;!!!!!!!!:      .:;;;;;;'      .:!!!;!!'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!;;;;;;;!!!!!!!!!!!!!!||!`    `'                                                                                                                
//                                                                                                                            :;.   .;|||||||!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!'.':::;;;;;;;:` :!;;;!!!!!'      `:;;;!;;`      `;!;;;;;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;;!!!!;;;;;;;;!!!!!!!!!!!|||!'    .'.                                                                                                              
//                                                                                                                           ;:    `!|||!!|||||||!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;!!:.`;:::;;;;;::;;' .:!!!!!!!!;`      ';;;;;;:.      ';;;;;;:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!;;;;;!!!!!!!!!!!!||||:    .'.                                                                                                             
//                                                                                                                          ;:    `!||||!!!|||||!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;!;`.::::::;;;;;;;;;;' `;!!!!!!!!:      .:;;;!!;'      .:!;;!!!'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!;;;!!!!!!!!!!!||||||:    .'`                                                                                                            
//                                                                                                                        .;:    '!|||||||!!|||||!!!!!!!!!!!!!!!!;;!;;;;;;;;;;;;;;;;!;;;;!!'.'::::::;;;;;;:::;;:` '!!!!!!!!!'      `:;;;;;;`      .;!!!!!;`      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!;;!!!!!!!!!!!!!||||;.    '`                                                                                                           
//                                                                                                                       .;'    '||||||||||!!||||!!!!!!!!!!!!!!!!!;;!!;;;;;;;;;;;;;;;;;;;!:.'::::::::;;;;;;:;;;:;:..:!;;!!!!!;`      `;;;;;;:.      ';!;;!!:.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!||||;`    ''                                                                                                          
//                                                                                                                      `;`    :|||||||||!!!!!|||!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;!;``::::::::;;;;;;;;;;;;;;;' `;;;!;!!!!:.      ';;;;;;'      .:!!;;;!:      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!|||||!`    `'                                                                                                         
//                                                                                                                     '!`    :%|||||||||!!!!!|||!!!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;!!!`.::::::::::;;;;;;;;;:;;;:;:` '!!!!!!!!!'      .:;;;;;;`      .;!!;;;;`      `:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!|||||!'    `'.                                                                                                       
//                                                                                                                    ';.    ;%||||||||||!!!!!!||||!!!!!!!!!!!!!!!!!!!;!!;;;;;;;;;;!;;!!'.'::::::::::;;;;;;;;;;;;;;;;;:..:!;!!!!!!;`      `;;;;;;:.      ';;!!;!;`      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;!!!!!!!!!!!!!!!!!!!!!!!!|||||||:    .'.                                                                                                      
//                                                                                                                   :;.   .;%||||||||||||!!!!!!|||!!!!!!!!!!!!!!!!!!!;;!!!!;;;;;;;;;;!:.`;::::::::::;;;;;;;;;;;;;;;;;;;' `;!;;!!!;!:       ';;;;;;'       :!!!;;!'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||:    .:`                                                                                                     
//                                                                                                                  :;    `!%%%||||||||!!!!!!!!!!||!!!!!!!!!!!!!!!!!!!!!!;;!!!!!;;!;;!;``::::::::::::;;::;;;;;;;;:;;;;;;;;` ';;;!!!!!!'      .:;;;;;;`      .;!!!!!;'      `;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!;!!!!!!!!!!!!!!!!!!!!!!!||||||||;.    '`                                                                                                    
//                                                                                                                 ;:    `!%%%|%|||||||||!!!!!!!!!||!!!!!!!!!!!!!!!!!!!!!;;!!!!!!;;;!!'.':::::::::::::;;:;;;;;;;;;;;;;;;;;;:..:;;;;!!!!;`      `;;;;;;:.      `;!!!!!;.      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||;.    ''                                                                                                   
//                                                                                                               .;:    '|%%%%|||||||||||!!!!!!!!!||!!!!!!!!!!!!!!!!!!!!!!;!!!!!!;!!!:.':::::::::::::;;;;;;;;;;;;:``':;;;;;;;' `;;;;!!!!!:.      ';;;;;;'       '!!!!!!:      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||!`    `'                                                                                                  
//                                                                                                              .;'    '|%%%%%||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;.`:::::::::::::::;;;;;;;;;;:`.''.  .`:;;;:` ';;;!!!!!!'      .:;;;;;;`      .;!!!!!;'      .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!|!!!!!!|||||||!`    `'.                                                                                                
//                                                                                                             `;'    :%%%%%%%%%||||||||||||!!!!!!!!||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;`.:::::::::::::::;;;;;;::;;;` '!!!!!!;`   .::..:;;;;!!!!;`      `;;;;;;:.      `;!!!!!;`      ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!|||!!!!||||||||'    `'.                                                                                               
//                                                                                                            `;`    :%%%%%%%%%%%|||||||||||!|!!!!!!!|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'.';;:;;:::;:::::::;;;;;;;;;' `;!;;!!!!!!!!;'.   `;;;!;;!!!:.      ';;;;;;'       '!!!!!!:.      :;;;;;;;;;;;;;;;;;;;;;!;;;;;!!;;;;!!!!!!!!!!!!!!!|||||||!!|||||||||:    .'`                                                                                              
//                                                                                                           ';`    ;%%%%%%%%%||||||||||||||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;!!:.';;::;;:::::::::::;;:;;;;;:..;!;;;!!!!!;!!;!!!!!;':;;;;;;!!!'      .:;;;;;;`      .:!!!!!!'      `;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;;;!!!!!!!!!!!!!!!|!|||||||!|||||||||;.    '`                                                                                             
//                                                                                                          ';.   .!$%%%%%%%%%%||||||||||||||!!!!!!!!!|||!!!!!!!!!!!!!!!!!!!!!!!!;``:;;;;::::::::::::::;;;;:;:`.:!!;!!!!!!;!!!!!!!!!!!;;;;;;;;!!!;`      `:;;;;;:`      `;!!!!!;`      `;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||;.    ''                                                                                            
//                                                                                                         :;.   `!$%%%%%%%%%%|||||||||||||||!!!!!!!!!!|||!!!!!!!!!!!!!!!!!!!!!!!`.:;:;;:::::::::::::::;;;;;;' '!!;;!!!!!!!!!!!!!;;;;;;;;;;;;;;;!!!;.      ';;;;;;:.      '!!!!!!:.      ';;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||||!`    ''                                                                                           
//                                                                                                        ::    `|$%%%%%%%%%%%%|||||||||||||||!!!!!!!!!!|||!!!!!!!!!!!!!!!!!!!!!'.';::::::;;:::::::::::;;;;;'.`;!;;;;;;;!!;;!;;;;;;;;;;;;;;;;;;;;!!!!'      .:;;;;;;'      .:!!!!!!'      .:;;;;;;;;;;;;;;!!;!!!!!!!!!;!!!!!!!!!!!!!!!!!!!|||||||||||||||||!'    `'                                                                                          
//                                                                                                       ;:    '%$%%%$%%%%%%%%%%|||||||||||||||!!!!!!!!!!||!!!!!!!!!!!!!!!!!!!!:.';;;;;;;;;;::::::::::;;;;;:..:!;;;;;;;;;!;;;;;;;;;;;;;;;;;;;;;;;;;;;!!'      `:;;;;;;`      `;!!!!!;`      `;!;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||'    `'.                                                                                        
//                                                                                                     .;:    '%$$$%%%%%%%%%%%%%%||||||||||||||!!!!!!!!!!!|!|||!!!!!!!!!!!!!!!;``::;;::;::;;;;;:::::::::;;;` '!;!;;;;!!!;;;;;;;;;;;;;;;;;;;;;;!;;;;;;!!!;`      ';;;;;;:.      '!!!!!!;.      '!;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||%||||||%:    .:`                                                                                       
//                                                                                                    `;'    :%$$$%%%%%%%%%%%%%%%|||||||||||||||!!!!!!!!!!|!!|!!!!!!!!!!!!!!!!'.:;;;;;;;;;;::;;::::::::;;;' `;;;;;;!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!:      .:;;;;;;'      .:!!!!!!'      .:!;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||%%%||||%%;    .'`                                                                                      
//                                                                                                   `;`    ;$$$$$%%%%%%%%%%%%%%%|||||||||||||||!!!!!!!!!!!|||!!!!!!!!!!!!!!!:.';;;;;;;;:;;;::::::;:::::;'..;!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!`      `:;;;;;;`      `;!!!!!;`      `;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||%%%%%%|%%%;.    '`                                                                                     
//                                                                                                  '!`    ;$$$$$$$$%%%%%%%%%%%%||||||||||||||||||!!!!!!!!!!|||!|!!!!!!!!!!!;.`;;:;;;;;;;;;;;:;;;;;::::::..:!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!;.      ';;;;;;:.      '!!!!!!;.      '!;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||%%%%%%%%%%!`    ''                                                                                    
//                                                                                                 ';.   .!$$$$$$$$$$%%%%%%%%%%%%%||||||||||||||||||!!!!!!!!|||!|!!!!!!!!!!!``:;;;;;;;;;;;;;;;;;;:;;;;:;'.';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!:      .:;;;;;;'      .:!!!!!!:      .:!!!;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||%%%%%%%%%%%%|`    `'                                                                                   
//                                                                                                :;.   .|$$$$$$$$$$%%%%%%%%%%%%%%%%|||||||||||||||||!!!!!!!!|||||!!!!!!!!!'.:;;;;;;;;;;;;;;;:;;;;;::;;;;;``:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!;;!!!!!'      .:;;;;;;`      `;!!!!!!`      `;!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||%%%%%%%%%%%%%|'    `:.                                                                                 
//                                                                                               :;    `|$$$$$$$$$$$$%%%%%%%%%%%%%%%|||||||||||||||||||!!!!!!!|||||||!!!!|:.';;;;;;;;;;;;;;;;;;;::;;;;;;;;!:.';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!;`      `;!;;!!:.      '!!!!!!;.      '!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||||||%%%%%%%%%%%%%%%%:    .:.                                                                                
//                                                                                              ::    '%&$$$$$$$$$$$$$%%%%%%%%%%%%%%%|%|||||||||||||||||!!!!!!|||||||!!||;``;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!'.';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!:.      ';!!!!;'       :!!!!!!:      .:!!!!!!!!!!!!!!|||||||||||||||||||||||||||%%%%%%%%%%%%%%$$$%;    .'`                                                                               
//                                                                                            .;:    '$&$$$$$$$$$$$$$$%%%%%%%%%%%%%%%%|||||||||||||||||||!!!!!!|||||||||!`.:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;``:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;;!!!!!!!!!!!!!'      `;!!!!!;`      `;!!!!!!'      `;!!!!||||||||||||||||||||||||||||||||||%%%%%%%%%%%%%%%$$$$$!.    '`                                                                              
//                                                                                           `!'    :$&$$$$$$$$$$$$$$$%%%%%%%%%%%%%%%%%%||||||||||||||||||||!!!|||||||||:.:;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;::;;;;:.`;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;;;;;!!!!!!!!!!!;`      '!!!!!!;.      '!|||||!`                                                                       ''                                                                             
//                                                                                          `;'    ;$&&$$$$$$$$$$$$$$$%$$%%%%%%%%%%%%%%%|%||||||||||||||||||||!!|||||||;.';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;;;!:.';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!;;;;;!!!!!!!!!!!!!:.                                                                                                    ''                                                                            
//                                                                                         `;`    ;$&&&$$$$$$$$$$$$$$$$$$%%%%%%%%%%%%%%%%%%%|||||||||||||||||||!||||||!``;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;;;'.:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!'                                                                                                    `:.                                                                          
//                                                                                        ';`   .!&&&&&$$$$$$$$$$$$$$$$$$$%%%%%%%%%%%%%%%%%%|||||||||||||||||||!||||||'.;!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;.';;;;;;;;;;;;;;;;;;;;;;;;;;!!;!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||||||||||||||||||||||||||||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$&&$:    `'.                                                                         
//                                                                                       :;.   .|&&&&&&&$&$$$$$$$$$$$$$$$$$$%%%$%%%%%%%%%%%%%%||||||||||||||||||||||%:.:!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!'.';!;;;;;;;;;;;;;;;;!;;;;!!;;;!!;;;!!!!!!!!!!!!!!!!!!!!!||||||||||||||||||||||||||||||||||||||||||||||||%||%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$&$;    .:`                                                                        
//                                                                                      :;.   `|&&&&&&&&&&$$$$$$$$$$$$$$$$$$$$$$%%%%%%%%%%%%%%%|||||||||||||||||||||!`                                              .... .`;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||||||||||||||||||||||||%%|||%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$&&&&&!.   .:`                                                                       
//                                                                                     ;;    '%&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$$$$$%$%%%%%%%%%%%%%|%%||||||||||||||||!||||||!||!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;!!;;;!!;;;;;;;;;;;;;;;;;;!!;;!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||||||||||||||||||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$&&&&&&&&|.    ''                                                                      
//                                                                                   .;:    '$&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$$$%%%%%%%%%%%%%%||||||||||||||||||||||!||!|||||!!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;;;;!!!!!!!!!!!!!!!!;!!!!!!!!!!!!!!!!;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||||||||||||||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$%%%$$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&%`    ':                                                                     
//                                                                                  `!:    :$&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$%%%%%%%%%%%%%%%%%%%||||||||||||||||||||||||!!!!!!!!!!!!!!!!!!!!!;;;;;;;;;!!!!!;;;;;;;;;;;!!!!!;;;;!!!;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||||||||||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$%$$$$$$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&$:    ':.                                                                   
//                                                                                 `!'    ;&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$$$$$$$$$%%%%%%%%%%%%%%%%%%%%%%%%%%|||||||||||||||||||!||!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;!!!!!!!!!;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||||||||||||||%|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&$:    `:`                                                                  
//                                                                                '!'    `;;;;:::::::::::::::::::::::::::::::'''''''''''''''''''''''''''''''''''''''``````````````````';!!!!!!!!!!!!!!!;!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||;`.............................................................................................     `:`                                                                 
//                                                                               :|'                                                                                                   .:!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!;!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||:                                                                                                     .:'                                                                
//                                                                              :!`                                                                                                     .:!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||:                                                                                .   ...................';'                                                               
//                                                         ...                 ...............                                                                                     :;.   .:!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;;;;;!!!!!!!!;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||'    .`.                                                                                                                                                                   
//                                                       .....                                                                                                                      :;    .;!!!!!!!!!!!;;;;;;;;;;;;;;;;;;;;!;;;;!;!!!!!!;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||'    .`                                                                                                                                                                     
//                                                      ......                                                                                                                       :;    .;!!!!!!!!!!;;!!;!!;;;;;;;;;!!!!!!!!!!!!!!;!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||!`    .`                                                                                                                                                                      
//                                                     .......                                                                                                                        :;    .;!!!!!!!!!!!!!!!;!!;!!!!!;;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||||;.    ``                                                                                                                                                                       
//                                                    ..........                                                                                                                       :;    `;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||!!|||||||||||||||%;.    ``                                                                                                                                                                        
//                                                   .............                                                                                                                      :;    .;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||%:     `.                                                                                                                                                                         
//                                                  ...............                                                                                                                      :;    .;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|!||||||||||||||||%|:    .`.                                                                                                                                                                          
//                                                ...................                                                                                                                     ::    `!|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||||||||||||||||%%%%|'    .`                                                                                                                                                                            
//                                               .......................                                                                                                                   ::    `!|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|!!|||||||||||||||||||%%%%|'    .`                                                                                                                                                                             
//                                              .........................                                                                                                                   ;:    `!|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|||||||||||||||||||||||||||%%%!`    ``                                                                                                                                                                              
//                                                                                                                                                                                           ;:    `!|!!||!!!!!!!!!!!!!!!!!!!!!!!!!||!||||||||||||||||||||||||||||%%%%!.    ``                                                                                                                                                                               
//                                                                                                                                                                                            ;;    `!|||||||||!!!!!!!!!!!!!|||!!!!!!!|||||||||||||||||||||||%%%%%%%%;.    ``                                                                                                                                                                                
//                                                                                                                                                                                             ;:    `!||||||||||||!||!!||!|||||||||||||||||||||||||||||||%%%%%%%%%%;     `.                                                                                                                                                                                 
//                                                                                                                                                                                              ;:    `!|||||||||||||||||||||||||||||||||||||||||||||||||%%%%%%%%%%:    .`.                                                                                                                                                                                  
//                                                                                                                                                                                               ;:    '!||||||||||||||||||||||||||||||||||||||||||||%%%%%%%%%%%%|'    .`                                                                                                                                                                                    
//                                                                                                                                                                                                ;:    '||||||||||||||||||||||||||||||||||||||||%%||%%%%%%%%%%%|`    ``                                                                                                                                                                                     
//                                                                                                                                                                                                .;:    '||||||||||||||||||||||||||||||||||||%%%%%||%%%%%%%%%%!`    ``                                                                                                                                                                                      
//                                                                                                                                                                                                 .;:    '|%|||||||||||||||||||||||%%%|||||||%%%%%%%%%%%%%%%%!.    ``                                                                                                                                                                                       
//                                                                                                                                                                                                  .;'    '|%|||||||||||||||||||||%|||%|%%%%%%%%%%%%%%%%%%%$;     `.                                                                                                                                                                                        
//                                                                                                                                                                                                   .;'    '|||%%%||||%%||||%%|%%%%%%%%%%%%%%%%%%%%%%%%%%$%:     `.                                                                                                                                                                                         
//                                                                                                                                                                                                    .;'    '|%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$%%$%:    .`                                                                                                                                                                                           
//                                                                                                                                                                                                     .;'    :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$%'    .`                                                                                                                                                                                            
//                                                                                                                                                                                                      .;'    :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$%$$$|`    ``                                                                                                                                                                                             
//                                                                                                                                                                                                       .;'    :%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$|`    ``                                                                                                                                                                                              
//                                                                                                                                                                                                        `;'    :%%%%%%%%%%%%%%%%%%%%%%$%%$$$$$$$$$$$!.    `.                                                                                                                                                                                               
//                                                                                                                                                                                                         .;'    :%$$%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$;     `.                                                                                                                                                                                                
//                                                                                                                                                                                                          `;'    ;$%$$$$$$$$%$$$%$$$$$$$$$$$$$$$$$:    .`.                                                                                                                                                                                                 
//                                                                                                                                                                                                           `;`    ;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$:    .`                                                                                                                                                                                                   
//                                                                                                                                                                                                            `;`    ;$$$$$$$$$$$$$$$$$$$$$$$$$$$%'    .`                                                                                                                                                                                                    
//                                                                                                                                                                                                             `;`    ;$$$$$$$$$$$$$$$$$$$$$$$$&%`    ``                                                                                                                                                                                                     
//                                                                                                                                                                                                              `;`    !&$$$$$$$$$$$$$$$$$$$$$&|.    ``                                                                                                                                                                                                      
//                                                                                                                                                                                                               `;`    ;$$$$$$$$$$$$$$$$$$$$$!.    `.                                                                                                                                                                                                       
//                                                                                                                                                                                                                `;`    ;$$$$$$$$$$$$$&&&&&$;     `.                                                                                                                                                                                                        
//                                                                                                                                                                                                                 `;`   .!&&&$$$$$$$$&&&&&$;    .`.                                                                                                                                                                                                         
//                                                                                                                                                                                                                  ';`   .!&$$$&&&&&&&&&&$:    .'                                                                                                                                                                                                           
//                                                                                                                                                                                                                   ';.   .!&&&&&&&&&&&&%'    ``                                                                                                                                                                                                            
//                                                                                                                                                                                                                    ';.   .!&&&&&&&&&&|`    ``                                                                                                                                                                                                             
//                                                                                                                                                                                                                     ';`   .|&&&&&&&&|.    ``                                                                                                                                                                                                              
//                                                                                                                                                                                                                      ';.   .|&&&&&&!.    '.                                                                                                                                                                                                               
//                                                                                                                                                                                                                       ';.   `|&&&&;    .'.                                                                                                                                                                                                                
//                                                                                                                                                                                                                        :;.   `|&&:    .'.                                                                                                                                                                                                                 
//                                                                                                                                                                                                                         :;.   `!:    `'                                                                                                                                                                                                                   
//                                                                                                                                                                                                                          :;.        `'                                                                                                                                                                                                                    
//                                                                                                                                                                                                                           :;.      ''                                                                                                                                                                                                                     
//                                                                                                                                                                                                                            :!.   .'`                                                                                                                                                                                                                      
//                                                                                                                                                                                                                             ;;. .:`                                                                                                                                                                                                                       
//                                                                                                                                                                                                                              :;':`                                                                                                                                                                                                                        
//                                                                                                                                                                                                                               :;.                                                                                                                                                                                                                         
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                      .                                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                       .                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                     .                                                                                                                                                                                                                     
//                                                                                                                                                                                                                                                                                                                                                                                                                                                           
//       



                                                                                                                                                                                                                                                                                                                                                                 
//       



