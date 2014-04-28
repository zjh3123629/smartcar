/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_Nvic��-----------------
 * @file LPLD_Nvic.c
 * @version 0.1
 * @date 2013-12-1
 * @brief ����ͨ��NVICģ�������жϵ���ռʽ���ȼ�
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

//���������ռʽ�жϣ�����Ϊ1������Ϊ0
#define PREEMPTION      1

PIT_InitTypeDef pit0_init_struct;
PIT_InitTypeDef pit1_init_struct;
NVIC_InitTypeDef nvic_init_struct;

void pit0_isr(void);
void pit1_isr(void);

void main (void)
{
#if(PREEMPTION == 1)
  //����PIT0��NVIC����
  nvic_init_struct.NVIC_IRQChannel = PIT0_IRQn;
  nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_1;
  nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
  LPLD_NVIC_Init(nvic_init_struct);
  //����PIT1��NVIC����
  nvic_init_struct.NVIC_IRQChannel = PIT1_IRQn;
  nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_1;
  nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
  LPLD_NVIC_Init(nvic_init_struct);
#endif
  
  //����PIT0
  pit0_init_struct.PIT_Pitx = PIT0;
  pit0_init_struct.PIT_PeriodMs = 500;
  pit0_init_struct.PIT_Isr = pit0_isr;
  LPLD_PIT_Init(pit0_init_struct);
  //����PIT1
  pit1_init_struct.PIT_Pitx = PIT1;
  pit1_init_struct.PIT_PeriodMs = 1000;
  pit1_init_struct.PIT_Isr = pit1_isr;
  LPLD_PIT_Init(pit1_init_struct);
  
  LPLD_PIT_EnableIrq(pit0_init_struct);
  LPLD_PIT_EnableIrq(pit1_init_struct);
  
  while(1)
  {
  } 
}

void pit0_isr(void)
{
  printf(">>PIT0 enter int.\r\n");
  LPLD_SYSTICK_DelayMs(50);
  printf("<<PIT0 leave int.\r\n");
}

void pit1_isr(void)
{
  printf("  >>PIT1 enter int.\r\n");
  LPLD_SYSTICK_DelayMs(150);
  LPLD_SYSTICK_DelayMs(150);
  LPLD_SYSTICK_DelayMs(150);
  LPLD_SYSTICK_DelayMs(150);
  printf("  <<PIT1 leave int.\r\n");
}

