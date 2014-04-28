/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_AnalogSampleSE��-----------------
 * @file LPLD_AnalogSampleSE.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����ADCģ��ĵ��˲ɼ����ܣ�ʵ��ģ���ѹ�ĵ��˲ɼ���
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
   *ʹ��RUSH Kinetis�������ϵĵ�λ��R7
    ��Ϊģ������������
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н����
   *ͨ�����ڵ�λ������ť�鿴���н����
   *��ʹ��"LPLD ADC����ʱ�������"����ADC�Ĳ������ʡ�
 ****************************************/

//��������
void adc_init(void);
void delay(uint16);
//��������
ADC_InitTypeDef adc_init_struct;

void main (void)
{
  uint16 result;
  
  //��ʼ��ADC
  adc_init();
  
  while(1)
  {
    result = LPLD_ADC_Get(ADC0, DAD1);
    printf("DAD1 result = %d\r\n", result);
    delay(5000);
  } 
}

/*
 * ��ʼ��ADC����ͨ��
 *
 */
void adc_init(void)
{
  //����ADC��������
  adc_init_struct.ADC_Adcx = ADC0;
  adc_init_struct.ADC_DiffMode = ADC_SE;        //���˲ɼ�
  adc_init_struct.ADC_BitMode = SE_12BIT;       //����12λ����
  adc_init_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;    //�̲���ʱ��
  adc_init_struct.ADC_HwAvgSel = HW_4AVG;       //4��Ӳ��ƽ��
  adc_init_struct.ADC_CalEnable = TRUE; //ʹ�ܳ�ʼ��У��
  //��ʼ��ADC
  LPLD_ADC_Init(adc_init_struct);
  //Ϊ�˱�֤���ù��ܲ���ռ�ã����ʹ����ӦADCͨ��
  //RUSH������ĵ�λ��ʹ��DAD1ͨ�����вɼ�
  //����DAD1ͨ��������Ϊ(ADC0_DP1)
  LPLD_ADC_Chn_Enable(ADC0, DAD1); 
}

/*
 * ��ʱ����
 */
void delay(uint16 n)
{
  uint16 i;
  while(n--)
  {
    for(i=0; i<1000; i++)
    {
      asm("nop");
    }
  }
}