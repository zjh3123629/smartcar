/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_DmaPdbAnalogSample��-----------------
 * @file LPLD_DmaPdbAnalogSample.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����DMA+PDB+ADC��ʵ�ַ�CPU��Ԥ�µ�ADC�ɼ���
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
DMA_InitTypeDef dma_init_struct;

uint16 Result;

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
  adc0_init_struct.ADC_DmaEnable = TRUE;        //ʹ��DMA
  //��ʼ��ADC0
  LPLD_ADC_Init(adc0_init_struct);   
  //ʹ��ADC0��DAD1�������Ÿ��ù���
  LPLD_ADC_Chn_Enable(ADC0, DAD1);
  //ʹ��ADC0��DAD1����ͨ��������ת������ж�
  LPLD_ADC_EnableConversion(ADC0, DAD1, 0, FALSE);
  
  //2.����DMA
  //��ʼ��PDB��������
  dma_init_struct.DMA_CHx = DMA_CH0;   //ʹ��Ch0ͨ��
  dma_init_struct.DMA_Req = ADC0_DMAREQ;        //DMA����ԴΪADC0
  dma_init_struct.DMA_MajorLoopCnt = 10;        //��ѭ������10��
  dma_init_struct.DMA_MinorByteCnt = 2; //��ѭ�������ֽڼ���������ADC����Ϊ12λ����˴���2�ֽڣ�
  dma_init_struct.DMA_SourceAddr = (uint32)&(ADC0->R[0]);       //Դ��ַ��ADC0����Ĵ���A��ַ
  dma_init_struct.DMA_SourceDataSize = DMA_SRC_16BIT;   //Դ��ַ�������ݿ��16λ
  dma_init_struct.DMA_DestAddr = (uint32)&Result;       //Ŀ�ĵ�ַ
  dma_init_struct.DMA_DestDataSize = DMA_DST_16BIT;     //Ŀ�ĵ�ַ�������ݿ��16λ
  dma_init_struct.DMA_AutoDisableReq = FALSE;   //�����Զ��������󣬼�������ѭ��������������
  //��ʼ��DMA
  LPLD_DMA_Init(dma_init_struct);
  //ʹ��DMA����
  LPLD_DMA_EnableReq(DMA_CH0);
  
  //3.����PDB��������
  //��ʼ��PDB��������
  pdb_init_struct.PDB_CounterPeriodMs = 1000;   //PDB��������������
  pdb_init_struct.PDB_LoadModeSel = LOADMODE_0; //����ģʽ����
  pdb_init_struct.PDB_ContinuousModeEnable = FALSE;     //������������ģʽ
  pdb_init_struct.PDB_TriggerInputSourceSel = TRIGGER_PIT0;     //���ô���ԴΪPIT0
  //��ʼ��PDB
  LPLD_PDB_Init(pdb_init_struct);
  //����PDB����ADC����������ADC0ģ�顢ʹ��A��ͨ��Ԥ������������ʱ0
  LPLD_PDB_AdcTriggerCfg(ADC0, PRETRIG_EN_A, 0);
  
  //4.����PIT��������
  //��ʼ��PIT����
  pit0_init_struct.PIT_Pitx = PIT0;     //ѡ��PIT0
  pit0_init_struct.PIT_PeriodMs = 500;  //PIT0��������500ms
  //��ʼ��PIT0
  LPLD_PIT_Init(pit0_init_struct);      
  
  while(1)
  {
    LPLD_LPTMR_DelayMs(500);
    printf("Reslut=%d\r\n", Result);
  } 
}

