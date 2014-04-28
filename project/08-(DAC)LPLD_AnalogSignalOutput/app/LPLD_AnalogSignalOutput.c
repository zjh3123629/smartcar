/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_AnalogSignalOutput��-----------------
 * @file LPLD_AnalogSignalOutput.c
 * @version 0.2
 * @date 2013-11-4
 * @brief ����DACģ�飬ʵ��ģ���ѹ�źŵ������
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
   *��ʾ�����۲�DAC0_OUT���ŵ�������Ρ�
   *����ͨ���޸�DELTA��DELAY��ֵ�۲�����仯��
 ****************************************/

#define DELTA   1       //������������
#define DELAY   1       //��ѹ������

//��������
void dac_init(void);
void delay(uint16);
//��������
DAC_InitTypeDef dac_init_struct;

void main (void)
{
  uint16 i = 0;         //�����������
  int8 delta = DELTA;   //��ѹ��������
  
  //��ʼ��DAC
  dac_init();
  
  while(1)
  {
    if(i==0)
      delta = DELTA;
    else if(i==4095)
      delta = -DELTA;
    
    i += delta;

    //�ڲ�ʹ��DAC�������������
    //��������DAC������0�����ֵ
    LPLD_DAC_SetBufferDataN(DAC0, i, 1);
    
    delay(DELAY);
  } 
}

/*
 * ��ʼ��DACģ��
 *
 */
void dac_init(void)
{
  //�ڲ�ʹ��DAC�������������ж�DMA�������
  //�����ʼ��DACͨ������
  dac_init_struct.DAC_Dacx = DAC0;
  LPLD_DAC_Init(dac_init_struct);
}

/*
 * ��ʱ����
 */
void delay(uint16 n)
{
  uint16 i;
  while(n--)
  {
    for(i=0; i<10; i++)
    {
      asm("nop");
    }
  }
}
