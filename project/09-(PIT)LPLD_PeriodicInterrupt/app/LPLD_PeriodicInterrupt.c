/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_PeriodicInterrupt��-----------------
 * @file LPLD_PeriodicInterrupt.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����PITģ�飬ʵ�����ڶ�ʱ�жϡ�
 *
 * ��Ȩ����:�����������µ��Ӽ������޹�˾
 * http://www.lpld.cn
 * mail:support@lpld.cn
 * Ӳ��ƽ̨:  LPLD K60 Card / LPLD K60 Nano
 *
 * �����̻���"��������K60�ײ��V3"������
 * ���п�Դ�������"lib"�ļ����£��û����ظ��ĸ�Ŀ¼�´��룬
 * �����û������豣����"project"�ļ����£��Թ����������ļ�������
 * �ײ��ʹ�÷���������ĵ��� 
 *
 */
#include "common.h"

/****************************************
 ˵����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н����
   *ͨ���޸�PIT0��PIT1�Ķ�ʱ���ڹ۲�����仯��
 ****************************************/

//��������
void pit_init(void);
void pit0_isr(void);
void pit1_isr(void);
//��������
PIT_InitTypeDef pit0_init_struct;
PIT_InitTypeDef pit1_init_struct;

void main (void)
{
  //��ʼ��PIT
  pit_init();

  while(1)
  {

  } 
}

/*
 * ��ʼ��PIT0��PIT1ͨ��
 *
 */
void pit_init(void)
{
  //����PIT0����
  pit0_init_struct.PIT_Pitx = PIT0;
  pit0_init_struct.PIT_PeriodS = 2;     //��ʱ����2��
  pit0_init_struct.PIT_Isr = pit0_isr;  //�����жϺ���
  //��ʼ��PIT0
  LPLD_PIT_Init(pit0_init_struct);  
    
  //����PIT1����
  pit1_init_struct.PIT_Pitx = PIT1;
  pit1_init_struct.PIT_PeriodMs = 1000; //��ʱ����1000����
  pit1_init_struct.PIT_Isr = pit1_isr;  //�����жϺ���
  //��ʼ��PIT1
  LPLD_PIT_Init(pit1_init_struct);
  
  //ʹ��PIT0��PIT1
  LPLD_PIT_EnableIrq(pit0_init_struct);
  LPLD_PIT_EnableIrq(pit1_init_struct);
}

/*
 * PIT0�жϺ���
 *
 */
void pit0_isr(void)
{
  printf("PIT0 Interrupt!\r\n");
}

/*
 * PIT1�жϺ���
 *
 */
void pit1_isr(void)
{
  printf("\tPIT1 Interrupt!\r\n");
}