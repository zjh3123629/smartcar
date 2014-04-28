/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_PdbAnalogSample��-----------------
 * @file LPLD_PdbAnalogSample.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����PDB+ADC��ʵ��ADC�Զ���ʱ�ɼ����ܡ�
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
 ****************************************/

//ģ���ʼ���ṹ�嶨��
PDB_InitTypeDef pdb_init_struct;
ADC_InitTypeDef adc0_init_struct;
PIT_InitTypeDef pit0_init_struct;
//��������
void adc0_isr();

void main (void)
{
  //1.����ADC��������
  //��ʼ��ADC0ģ���A��ͨ��
  adc0_init_struct.ADC_Adcx = ADC0;     //ѡ��ADC0
  adc0_init_struct.ADC_BitMode = SE_12BIT;      //����ת������
  adc0_init_struct.ADC_CalEnable = TRUE;        //ʹ�ܳ�ʼ���Զ�У׼
  adc0_init_struct.ADC_HwTrgCfg = HW_TRGA;      //����ΪӲ������ת��
  adc0_init_struct.ADC_Isr = adc0_isr;  //����ADC�жϺ���
  //��ʼ��ADC0
  LPLD_ADC_Init(adc0_init_struct);   
  //ʹ��ADC0��DAD1�������Ÿ��ù���
  LPLD_ADC_Chn_Enable(ADC0, DAD1);
  //ʹ��ADC0��DAD1����ͨ������ת������ж�
  LPLD_ADC_EnableConversion(ADC0, DAD1, 0, TRUE);
  //ʹ��ADC0�ж�
  LPLD_ADC_EnableIrq(adc0_init_struct);

  //2.����PDB��������
  //��ʼ��PDB��������
  pdb_init_struct.PDB_CounterPeriodMs = 1000;   //PDB��������������
  pdb_init_struct.PDB_LoadModeSel = LOADMODE_0; //����ģʽ����
  pdb_init_struct.PDB_ContinuousModeEnable = FALSE;     //������������ģʽ
  pdb_init_struct.PDB_TriggerInputSourceSel = TRIGGER_PIT0;     //���ô���ԴΪPIT0
  //��ʼ��PDB
  LPLD_PDB_Init(pdb_init_struct);
  //����PDB����ADC����������ADC0ģ�顢ʹ��A��ͨ��Ԥ������������ʱ0
  LPLD_PDB_AdcTriggerCfg(ADC0, PRETRIG_EN_A, 0);
  
  //3.����PIT��������
  //��ʼ��PIT����
  pit0_init_struct.PIT_Pitx = PIT0;     //ѡ��PIT0
  pit0_init_struct.PIT_PeriodMs = 500;  //PIT0��������500ms
  //��ʼ��PIT0
  LPLD_PIT_Init(pit0_init_struct);      
  
  while(1)
  {
    
  } 
}

/*
 * ADC0�жϺ���
 *
 */
void adc0_isr()
{
  int16 result;
  //�ж�ת����ɵ���A�黹��B��
  uint8 ab = LPLD_ADC_GetSC1nCOCO(ADC0);
  //��ȡ�������
  result = LPLD_ADC_GetResult(ADC0, ab);
  //��ӡ������
  printf("ADC0_R[%d]=%d\r\n", ab, result);
}