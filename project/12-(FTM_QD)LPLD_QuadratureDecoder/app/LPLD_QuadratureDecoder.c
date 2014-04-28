/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_QuadratureDecoder��-----------------
 * @file LPLD_QuadratureDecoder.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����FTMģ����������빦�ܣ�ʵ�ֱ�����������ת���١�
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
   *�ֱ𽫱�������AB���źŽ���PTB0��PTB1����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н����
   *ʹ��������������ת���鿴���н����
 ****************************************/

//��������
void qd_init(void);
void pit_init(void);
void pit_isr(void);
void delay(uint16);
//��������
FTM_InitTypeDef ftm_init_struct;
PIT_InitTypeDef pit_init_struct;
int32 qd_result=0;

void main (void)
{
  
  //��ʼ���������빦��
  qd_init();
  //��ʼ��PIT��ʱ�ж�
  //������ʱ��ȡ��������ļ������
  pit_init();

  while(1)
  {
    printf("QD Counter = %d\r\n", qd_result);
    delay(1000);
  } 
}

/*
 * ��ʼ��FTM1���������빦��
 *
 */
void qd_init(void)
{
  //�����������빦�ܲ���
  ftm_init_struct.FTM_Ftmx = FTM1;              //ֻ��FTM1��FTM2���������빦��
  ftm_init_struct.FTM_Mode = FTM_MODE_QD;       //�������빦��
  ftm_init_struct.FTM_QdMode = QD_MODE_PHAB;    //AB������ģʽ
  //��ʼ��FTM
  LPLD_FTM_Init(ftm_init_struct);
  //ʹ��AB������ͨ��
  //PTB0���Ž�A�����롢PTB1���Ž�B������
  LPLD_FTM_QD_Enable(FTM1, PTB0, PTB1);
}

/*
 * ��ʼ��PIT��ʱ��
 *
 */
void pit_init(void)
{
  //���ö�ʱ�����жϲ���
  pit_init_struct.PIT_Pitx = PIT0;
  pit_init_struct.PIT_PeriodMs = 20;    //20�������һ���ж�
  pit_init_struct.PIT_Isr = pit_isr;
  //��ʼ��PIT
  LPLD_PIT_Init(pit_init_struct);
  //ʹ��PIT��ʱ�ж�
  LPLD_PIT_EnableIrq(pit_init_struct);
}

/*
 * PIT�жϺ���
 */
void pit_isr(void)
{
  //��ȡFTM1�������������ֵ
  qd_result = LPLD_FTM_GetCounter(FTM1);
  //��ռ�����
  LPLD_FTM_ClearCounter(FTM1);
}

/*
 * ��ʱ����
 */
void delay(uint16 n)
{
  uint16 i;
  while(n--)
  {
    for(i=0; i<5000; i++)
    {
      asm("nop");
    }
  }
}
