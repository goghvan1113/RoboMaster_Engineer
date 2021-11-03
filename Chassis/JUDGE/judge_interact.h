/**
  ******************************************************************************
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :看配置表
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
  * 更新日志：
  * 2021年1月10日：查找到judgetest.c的第512行，USART_DMACmd(UART8,USART_DMAReq_Tx,ENABLE);//开启串口DMA
  * 应改为USART_DMACmd(Judge_UseUART_Typedef_Name,USART_DMAReq_Tx,ENABLE);
  *
  *	2021年4月3日：收到了新版的裁判系统，开始移植。
  */

#ifndef __JUDGE_INTERACT_H__
#define __JUDGE_INTERACT_H__

#include "judgeStruct.h"
#include "CRCCheck.h"


///////////////////////////////////////////////////////////////工程画备用线配置表

//*************步兵右************//
#define JUDGE_ENGINEER_ANOTHER_1_START_X	1329
#define JUDGE_ENGINEER_ANOTHER_1_START_Y	1080 - 430		
#define JUDGE_ENGINEER_ANOTHER_1_END_X	1454
#define JUDGE_ENGINEER_ANOTHER_1_END_Y	1080 - 662		
#define JUDGE_ENGINEER_ANOTHER_1_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_1_WIDTH	5

//*************步兵左************//
#define JUDGE_ENGINEER_ANOTHER_2_START_X	744
#define JUDGE_ENGINEER_ANOTHER_2_START_Y	1080 - 451		
#define JUDGE_ENGINEER_ANOTHER_2_END_X	678
#define JUDGE_ENGINEER_ANOTHER_2_END_Y	1080 - 590		
#define JUDGE_ENGINEER_ANOTHER_2_COLOR	White
#define JUDGE_ENGINEER_ANOTHER_2_WIDTH	5

//*************英雄右************//
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



///////////////////////////////////////////////////////////////配置表

/*********工程准星线*******/
#define JUDGE_ENGINEER_AIM_X	960
#define JUDGE_ENGINEER_AIM_Y	540
#define JUDGE_ENGINEER_AIM_LENGTH_H	150		//水平长度
#define JUDGE_ENGINEER_AIM_LENGTH_V	300		//竖直长度
#define JUDGE_ENGINEER_AIM_COLOR	White
#define JUDGE_ENGINEER_AIM_WIDTH	1


/*********工程障碍块电推杆对齐线*******/
#define JUDGE_ENGINEER_LINEAR_COLOR		Green	// 电推杆对齐线总体颜色
#define JUDGE_ENGINEER_LINEAR_WIDTH		10	// 小资源岛对齐线宽度

#define JUDGE_ENGINEER_LINEAR_LEFT_START_X	690
#define JUDGE_ENGINEER_LINEAR_LEFT_START_Y	1080 - 718		//左侧水平线
#define JUDGE_ENGINEER_LINEAR_LEFT_END_X	800
#define JUDGE_ENGINEER_LINEAR_LEFT_END_Y	1080 - 716		//左侧水平线

#define JUDGE_ENGINEER_LINEAR_RIGHT_1_START_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_1_START_Y	0		//右侧水平线
#define JUDGE_ENGINEER_LINEAR_RIGHT_1_END_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_1_END_Y	0		//右侧水平线

#define JUDGE_ENGINEER_LINEAR_RIGHT_2_START_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_2_START_Y	0		//右侧水平线左边线
#define JUDGE_ENGINEER_LINEAR_RIGHT_2_END_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_2_END_Y	0		//右侧水平线左边线
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_START_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_START_Y	0		//右侧水平线右边线
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_END_X	0
#define JUDGE_ENGINEER_LINEAR_RIGHT_3_END_Y	0		//右侧水平线右边线




/*********工程梯子配置表，会和超级电容冲突，如果使用工程梯子，就不能使用超级电容*******/
#define JUDGE_ENGINEER_LADDER_POSITION_X	360	//梯子坐标X
#define JUDGE_ENGINEER_LADDER_POSITION_Y	540	//梯子坐标Y
#define JUDGE_ENGINEER_LADDER_HEIGHT_ALL	150	//梯子总高度
#define JUDGE_ENGINEER_LADDER_COLOR_ALL		Green	//梯子总体颜色
#define JUDGE_ENGINEER_LADDER_SPACE			75		//梯子2根竖线的间距，也等于横着的线长度
#define JUDGE_ENGINEER_LADDER_SIDE_LINE_WIDTH	10	//梯子侧面线宽度
#define JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_WIDTH	10	//梯子中间横线的线宽
#define JUDGE_ENGINEER_LADDER_HORIZONTAL_LINE_COLOR White	//梯子中间横线的颜色

/********************4路装甲板配置表，如果使用，一定要把GRAPH_USE_YAW_OR_ARMOR定义为1***********************/
#define JUDGE_GRAPH_DISTANCE	200.0f		//装甲板到旋转中心距离
#define JUDGE_GRAPH_ROTATE_X	960.0f		//旋转中心X坐标
#define JUDGE_GRAPH_ROTATE_Y	540.0f		//旋转中心Y坐标
#define JUDGE_GRAPH_BOARD_LENGTH	50.0f	//装甲板长度
#define JUDGE_GRAPH_BOARD_WIDTH	20.0f		//装甲板宽度


/********************7路字符串通道配置表***********************/
#define CHAR_SIZE_CH1	15
#define WIDTH_CH1      2
#define COLOR_CH1      Yellow
#define POSITION_X_CH1  50  
#define POSITION_Y_CH1  880
#define SPACE_Y_CHANNEL	30

/********************7路图形通道配置表***********************/
//共性配置
#define GRAPH_CHANNEL_ALL_RADIUS	8	//圆半径
#define GRAPH_CHANNEL_ALL_LENGTH	20	//矩形长度
#define GRAPH_CHANNEL_STR_COLOR_ALL	Green
#define GRAPH_CHANNEL_STR_LARGE_ALL	15		//字符串大小
#define GRAPH_CHANNEL_STR_WIDTH_ALL	2		//字符串线宽

#define Y_Position_Delta  -20       // 同一通道图形与字符串之间的距离
//个性配置
#define GRAPH_CHANNEL_DELT_POSITION  100 // 图形间距
#define GRAPH_Y_POSITION 350             // 图形与屏幕顶端之间的距离

// 初始化状态标志
#define GRAPH_USE_THIS_GRAPH_8_1		1		//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_1_POSITION_X	750
#define GRAPH_CHANNEL_8_1_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_1_WIDTH			20	//线条宽度
#define GRAPH_CHANNEL_STR_8_1_POSITION_X	GRAPH_CHANNEL_8_1_POSITION_X		//色块1说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_1_POSITION_Y	GRAPH_CHANNEL_8_1_POSITION_Y+Y_Position_Delta//色块1说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_1	"Ini"	//色块1的提示说明字符串

// 爪子开闭标志
#define GRAPH_USE_THIS_GRAPH_8_2		1		//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_2_POSITION_X	GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION
#define GRAPH_CHANNEL_8_2_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_2_WIDTH			20	//线条宽度
#define GRAPH_CHANNEL_STR_8_2_POSITION_X	GRAPH_CHANNEL_8_2_POSITION_X		//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_2_POSITION_Y	GRAPH_CHANNEL_8_2_POSITION_Y+Y_Position_Delta	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_2	"Cla"	//色块的提示说明字符串

// 救援机构的开关标志
#define GRAPH_USE_THIS_GRAPH_8_3		1		//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_3_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*2)
#define GRAPH_CHANNEL_8_3_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_3_WIDTH			20	//线条宽度。
#define GRAPH_CHANNEL_STR_8_3_POSITION_X	GRAPH_CHANNEL_8_3_POSITION_X		//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_3_POSITION_Y	GRAPH_CHANNEL_8_3_POSITION_Y+Y_Position_Delta	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_3	"JYZ"	//色块的提示说明字符串

// 障碍块电推杆长度标志
#define GRAPH_USE_THIS_GRAPH_8_4		1	//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_4_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*3)
#define GRAPH_CHANNEL_8_4_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_4_WIDTH			20	//线条宽度。
#define GRAPH_CHANNEL_STR_8_4_POSITION_X	GRAPH_CHANNEL_8_4_POSITION_X		//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_4_POSITION_Y	GRAPH_CHANNEL_8_4_POSITION_Y+Y_Position_Delta	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_4	"JYG"	//色块的提示说明字符串

// 救援电推杆长度标志
#define GRAPH_USE_THIS_GRAPH_8_5		1		//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_5_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*4)
#define GRAPH_CHANNEL_8_5_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_5_WIDTH			20	//线条宽度。
#define GRAPH_CHANNEL_STR_8_5_POSITION_X	GRAPH_CHANNEL_8_5_POSITION_X	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_5_POSITION_Y	GRAPH_CHANNEL_8_5_POSITION_Y+Y_Position_Delta	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_5	"ZAK"	//色块的提示说明字符串

#define GRAPH_USE_THIS_GRAPH_8_6		0		//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_6_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*5)
#define GRAPH_CHANNEL_8_6_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_6_WIDTH			20	//线条宽度。
#define GRAPH_CHANNEL_STR_8_6_POSITION_X	GRAPH_CHANNEL_8_6_POSITION_X		//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_6_POSITION_Y	GRAPH_CHANNEL_8_6_POSITION_Y	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_6	"GRAPH_1"	//色块的提示说明字符串

#define GRAPH_USE_THIS_GRAPH_8_7		0		//把这个设置为1表示使用这个图形，为0不使用这个图形
#define GRAPH_CHANNEL_8_7_POSITION_X	(GRAPH_CHANNEL_8_1_POSITION_X+GRAPH_CHANNEL_DELT_POSITION*6)
#define GRAPH_CHANNEL_8_7_POSITION_Y	1080-GRAPH_Y_POSITION
#define GRAPH_CHANNEL_8_7_WIDTH			20	//线条宽度。
#define GRAPH_CHANNEL_STR_8_7_POSITION_X	GRAPH_CHANNEL_8_7_POSITION_X		//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_7_POSITION_Y	GRAPH_CHANNEL_8_7_POSITION_Y	//色块说明字符的X坐标
#define GRAPH_CHANNEL_STR_8_7	"GRAPH_1"	//色块的提示说明字符串


/********************YAW轴的PITCH轴配置表***********************/
#define GRAPH_USE_YAW_OR_ARMOR	0	//0的时候使用YAW轴，1时不使用YAW轴，使用装甲板旋转

#define CHAR_SIZE_YAW_PIT	16
#define WIDTH_YAW_PIT     0
#define COLOR_YAW_PIT      Green
#define POSITION_X__YAW_PIT  580  
#define POSITION_Y__YAW_PIT  540


/********************打印超级电容配置表***********************/
#define CHAR_SIZE_VOLTAGE_2	15	//电压字符大小
#define WIDTH_VOLTAGE_2      2	//电压字符线宽
#define COLOR_VOLTAGE_2      Green	//电压字符颜色
#define VOLTAGE_DONT_USE	1		//如果把这个定义为1，就是不要电容外面显示的电压
#define POSITION_X_CAP  720  
#define POSITION_Y_CAP  1080-250
#define RECTANGLE_WIDTH	2	//电池外边框厚度，必须要为偶数，不然会干涉不好看。不想要外边框时把这个定义为0
#define RECTANGLE_LENGTH	470.0f	//电池外框长度。要求是偶数
#define RECTANGLE_HEIGHT	10	//电池外框高度。要求是偶数

/********************车身尺寸线配置表***********************/
#define Judge_Car_Size_Line_Color			Green			//线的颜色
#define Judge_Car_Size_Line_Width			0				//线宽
#define Judge_Car_Size_BottomWidthMin		0				//车身尺寸线下部的长度，单位是像素。最大长度，车可能能过，小于此尺寸绝对不能过
#define Judge_Car_Size_TopWidthMin			0				//车身尺寸线上部的长度，单位是像素。
#define Judge_Car_Size_BottomWidthMax		0				//车身尺寸线下部的长度，单位是像素。最大长度，车一定能过
#define Judge_Car_Size_TopWidthMax			0				//车身尺寸线上部的长度，单位是像素。
#define Judge_Car_Size_LineHign				0				//车身尺寸线上部距离下部的高度，单位是像素


/********************中间大横线配置表***********************/
#define Judge_DontDrawHorizontal	1	//不要大横线时就把这个定义为1。		
#define Judge_Horizontal_Line_Color	Green	//水平线的颜色
#define Judge_Horizontal_Line_Width	2	//线宽
#define Judge_Horizontal_Line_Length	560	//线长
#define Judge_Vertical_Line_Height		10		//小竖直线高度



/********************辅助瞄准线配置表----等级为1时***********************/
#define Judge_Equ_Line_All_Color	Green	//线的颜色
#define Judge_Equ_Line_All_Width	0	//线宽
#define Judge_Equ_Line_Length_Vertical	0		//短竖线长度
#define Judge_Equ_Line_ALL_Position_X	940		//中心定位点坐标X

//等级为1时，从上往下第一根线
#define	Judge_Equ_Line_1_1_length_S	70		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_1_length_L	118		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_1_Position_Y	900		//中心定位点坐标Y
#define Judge_Equ_Line_1_1_Label_float	5.2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_1_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第二根线
#define	Judge_Equ_Line_1_2_length_S	60		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_2_length_L	106		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_2_Position_Y	480		//中心定位点坐标Y
#define Judge_Equ_Line_1_2_Label_float	2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_2_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第三根线
#define	Judge_Equ_Line_1_3_length_S	40		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_3_length_L	70		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_3_Position_Y	460		//中心定位点坐标Y
#define Judge_Equ_Line_1_3_Label_float	3		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_3_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第四根线
#define	Judge_Equ_Line_1_4_length_S	35		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_4_length_L	62		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_4_Position_Y	440		//中心定位点坐标Y
#define Judge_Equ_Line_1_4_Label_float	4		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_4_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第五根线
#define	Judge_Equ_Line_1_5_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_5_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_5_Position_Y	420		//中心定位点坐标Y
#define Judge_Equ_Line_1_5_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_5_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第六根线
#define	Judge_Equ_Line_1_6_length_S	20		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_6_length_L	60		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_6_Position_Y	150		//中心定位点坐标Y
#define Judge_Equ_Line_1_6_Label_float	5.2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_6_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第七根线
#define	Judge_Equ_Line_1_7_length_S	10		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_1_7_length_L	50		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_1_7_Position_Y	100		//中心定位点坐标Y
#define Judge_Equ_Line_1_7_Label_float	5.2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_1_7_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可


/********************辅助瞄准线配置表----等级为2时***********************/

//等级为1时，从上往下第一根线
#define	Judge_Equ_Line_2_1_length_S	70		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_1_length_L	118		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_1_Position_Y	400		//中心定位点坐标Y
#define Judge_Equ_Line_2_1_Label_float	5.2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_1_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第二根线
#define	Judge_Equ_Line_2_2_length_S	60		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_2_length_L	106		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_2_Position_Y	480		//中心定位点坐标Y
#define Judge_Equ_Line_2_2_Label_float	2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_2_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

//等级为1时，从上往下第三根线
#define	Judge_Equ_Line_2_3_length_S	40		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_3_length_L	70		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_3_Position_Y	470		//中心定位点坐标Y
#define Judge_Equ_Line_2_3_Label_float	3		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_3_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第四根线
#define	Judge_Equ_Line_2_4_length_S	35		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_4_length_L	62		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_4_Position_Y	465		//中心定位点坐标Y
#define Judge_Equ_Line_2_4_Label_float	4		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_4_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第五根线
#define	Judge_Equ_Line_2_5_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_5_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_5_Position_Y	465		//中心定位点坐标Y
#define Judge_Equ_Line_2_5_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_5_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第六根线
#define	Judge_Equ_Line_2_6_length_S	20		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_6_length_L	60		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_6_Position_Y	150		//中心定位点坐标Y
#define Judge_Equ_Line_2_6_Label_float	5.2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_6_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第七根线
#define	Judge_Equ_Line_2_7_length_S	10		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_2_7_length_L	50		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_2_7_Position_Y	100		//中心定位点坐标Y
#define Judge_Equ_Line_2_7_Label_float	5.2		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_2_7_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可

/********************辅助瞄准线配置表----等级为3时***********************/

//等级为1时，从上往下第一根线
#define	Judge_Equ_Line_3_1_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_1_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_1_Position_Y	505		//中心定位点坐标Y
#define Judge_Equ_Line_3_1_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_1_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第二根线
#define	Judge_Equ_Line_3_2_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_2_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_2_Position_Y	505		//中心定位点坐标Y
#define Judge_Equ_Line_3_2_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_2_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第三根线
#define	Judge_Equ_Line_3_3_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_3_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_3_Position_Y	50		//中心定位点坐标Y
#define Judge_Equ_Line_3_3_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_3_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第四根线
#define	Judge_Equ_Line_3_4_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_4_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_4_Position_Y	505		//中心定位点坐标Y
#define Judge_Equ_Line_3_4_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_4_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第五根线
#define	Judge_Equ_Line_3_5_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_5_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_5_Position_Y	505		//中心定位点坐标Y
#define Judge_Equ_Line_3_5_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_5_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第六根线
#define	Judge_Equ_Line_3_6_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_6_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_6_Position_Y	505		//中心定位点坐标Y
#define Judge_Equ_Line_3_6_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_6_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可
//等级为1时，从上往下第七根线
#define	Judge_Equ_Line_3_7_length_S	25		//小装甲板对应线长度，单位是像素
#define	Judge_Equ_Line_3_7_length_L	44		//大装甲板对应线长度，单位像素
#define	Judge_Equ_Line_3_7_Position_Y	505		//中心定位点坐标Y
#define Judge_Equ_Line_3_7_Label_float	5		//定位线旁边的距离标签，单位是m，小数点后面1位
#define Judge_Equ_Line_3_7_Length_Vertical	Judge_Equ_Line_Length_Vertical	//短竖线长度，当不想要这根线时，把长度改为0即可



/********************串口和DMA引脚配置表***********************/

//引脚相关
#define Judge_UseGPIO_GPIO_PeriphClock RCC_AHB1Periph_GPIOB
#define Judge_UseGPIO_GPIO_Typedef_Name	GPIOB
#define Judge_UseGPIO_GPIO_PINSource_TX	GPIO_PinSource10
#define Judge_UseGPIO_GPIO_GPIO_Pin_TX	GPIO_Pin_10
#define Judge_UseGPIO_GPIO_PINSource_RX	GPIO_PinSource11
#define Judge_UseGPIO_GPIO_GPIO_Pin_RX	GPIO_Pin_11

//串口相关
#define Judge_UseUART_PeriphClock	RCC_APB1Periph_USART3
#define Judge_UseUART_GPIOAF_Name GPIO_AF_USART3
#define Judge_UseUART_Typedef_Name	USART3
#define Judge_UseUART_IRQn	USART3_IRQn
#define Judge_UseUART_IRQHandler	USART3_IRQHandler
//函数名相关
#define Judge_UseUART_Function_Name	USART3_Init
#define Judge_UseUART_SendChar	USART3_SendChar

//DMA配置相关
//RX的DMA
#define Judge_UseDMA_PeriphClock_RX	RCC_AHB1Periph_DMA1
#define Judge_UseDMA_IRQChannel_RX	DMA1_Stream1_IRQn
#define Judge_UseDMA_Stream_Typedef_Name_RX	DMA1_Stream1
#define Judge_UseDMA_ClearIT_RX	DMA_IT_TCIF1	//是数据流几就把数字改为几
#define Judge_UseDMA_Channel_RX	DMA_Channel_4
#define Judge_UseDMA_ClearFlag	DMA_FLAG_TCIF4 | DMA_FLAG_FEIF4 | DMA_FLAG_DMEIF4 | DMA_FLAG_TEIF4 | DMA_FLAG_HTIF4		//是通道几就把数字改为几
//函数
#define Judge_UseDMA_IRQHandler_RX	DMA1_Stream1_IRQHandler
//TX的DMA
#define Judge_UseDMA_PeriphClock_TX		RCC_AHB1Periph_DMA1
#define Judge_UseDMA_IRQChannel_TX				DMA1_Stream3_IRQn
#define Judge_UseDMA_Stream_Typedef_Name_TX		DMA1_Stream3
#define Judge_UseDMA_ClearIT_TX	DMA_IT_TCIF3	//是数据流几就把数字改为几
#define Judge_UseDMA_Channel_TX					DMA_Channel_4
//函数
#define Judge_UseDMA_IRQHandler_TX	DMA1_Stream3_IRQHandler







//////////////////////////////////////////////////////////////////////////////////////////
//****************************************************************************************
//########################################################################################
//下面是接口函数区。下面是接口函数区。下面是接口函数区。下面是接口函数区。下面是接口函数区。自己需要什么数据就写函数返回什么数据
//例如





//上面是接口函数区。上面是接口函数区,上面是接口函数区，上面是接口函数区，上面是接口函数区
//########################################################################################
//****************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////

/**
  ******************************************************************************
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :该函数是第一次移植裁判系统后，首先要跑的一个测试函数
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
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :该函数是裁判系统初始化函数
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
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :该函数是在操作手界面显示超级电容容量的函数，Percent是百分比，Voltage是电压值
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
//下面是接口函数

/**
  ******************************************************************************
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :Judge_GetRobotState函数是获得机器人状态参数的函数
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
//在屏幕上打印超级电容的平方。使用字符串
void Judge_LoopPer1MS(void);
void Draw_EqualHeightLine(uint8_t RobotLevel);

ext_game_robot_status_t* Judge_GetRobotState(void);

ext_power_heat_data_t* Judge_GetRobot_power_heat(void);

ext_shoot_data_t* Judge_shoot_data(void);

ext_game_robot_status_t* Judge_robot_status(void);

ext_power_heat_data_t* Judge_heat(void);

ext_game_robot_pos_t*	Judge_GetRobotPosition(void);
//打印装甲板旋转角度和装甲板颜色，10HZ。角度0-360，逆时针为正
int8_t PrintArmorRotate(float Yaw,graphic_color_tpye_e Armor_1,graphic_color_tpye_e Armor_2,
						graphic_color_tpye_e Armor_3,graphic_color_tpye_e Armor_4);

int8_t Judge_AngineerPrintLadder(float Percent);//工程画梯子

/**
  ******************************************************************************
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :Judge_GetFlag函数是获得机器人某个参数有没有更新的函数
  * Description        :返回值是该参数更新过了多少次
  * Description        :输入值是要看的某个结构体
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
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :Judge_ClearFlagOf函数是清除更新标志位的函数
  * Description        :
  * Description        :输入值是要清除更新FLAG的某个结构体
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
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :void Judge_RobotToRobot(Robots_ID_e receiver, uint8_t *DataAddr);
  * Description        :机器人间通信
  * Description        :receiver是接收方机器人ID，其定义见 Robots_ID_e
  * Description        :DataAddr是要发送的信息。字符串格式
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
  * Copyright (C), 2021 - , 四川大学火锅战队 
  * File Name          :Judgetest.h
  * Author             :wcc
  * Version            :V1.4
  * date               :2021年4月3日
  * Description        :void Judge_SelfControl(uint8_t *DataAddr)
  * Description        :自定义控制器发送数据
  * Description        :DataAddr是要发送的信息。字符串格式
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



