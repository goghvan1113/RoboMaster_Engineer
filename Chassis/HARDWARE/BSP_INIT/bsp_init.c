#include "bsp_init.h"

//��ģ��ĳ�ʼ������
void BspInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  // NVIC_PriorityGroup_4
	delay_init(168);
	Usart1PrintInit();               // ����1DMA��ӡ��ʼ��,���ڵ���ʱ������Ϣ
	TIM5_Init();                     // 1ms��ʱ����ʼ�� 
	CAN1_Init();                     // CAN1���ͨ�ų�ʼ��
	CAN2_Init();                     // CAN2��̨ͨ�ų�ʼ��
	CAN_Device_Init();               // ���õ��̵����CAN����
	
	ChassisMotorRun_Init();          // �����˶������ʼ��
	MineMotor_Init();                // ������ʯ�����ʼ�����������̺���ת��ʯ      
}

