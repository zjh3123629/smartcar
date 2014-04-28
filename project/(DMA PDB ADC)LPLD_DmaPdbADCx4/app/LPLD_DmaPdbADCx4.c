/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_DmaPdbADCx4��-----------------
 * @file LPLD_DmaPdbADCx4.c
 * @version 0.1[By LPLD]
 * @date 2013-10-30
 * @brief �ۺ�����ADC��PDB��DMAģ�飬ʵ����ͨ��AD�Զ������ɼ�������CPU��Ԥ���ɼ������ʱ���ڴ��ȡ
 *
 * ��Ȩ����:�����������µ��Ӽ������޹�˾
 * ���� http://www.lpld.cn
 * ������̳ http://bbs.lpld.cn
 * mail:support@lpld.cn
 * Ӳ��ƽ̨:  RUSH Kinetis������
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
    ��Ϊģ����������������3��AD�����ΪC0,B4,B5��
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н����
   *ͨ�����ڵ�λ������ť�鿴���н��,Ҳ�ɽ�
    ģ�������뵽C0,B4,B5�۲�����ͨ���仯��
 ****************************************/

//�������ģ��ĳ�ʼ���ṹ��
ADC_InitTypeDef adc0_init_struct;
ADC_InitTypeDef adc1_init_struct;
DMA_InitTypeDef dma0_init_struct;
DMA_InitTypeDef dma1_init_struct;
PDB_InitTypeDef pdb_init_struct;

//�������������飬�ֱ�洢ADC0-A��ADC0-B��ADC1-A��ADC1-B
int16 Result[4]={0,0,0,0};

//����ʱ����
void delay(void);

/********************************************************************/
void main (void)
{
  //**********************************************
  //Step 1.����ADC0��ADC1�Ĳ���
  //ADC0-A
  adc0_init_struct.ADC_Adcx = ADC0;
  adc0_init_struct.ADC_BitMode = SE_12BIT;      //12λ����
  adc0_init_struct.ADC_CalEnable = TRUE;        //ʹ�ܳ�ʼ��У��
  adc0_init_struct.ADC_HwAvgSel = HW_4AVG;      //ʹ��4��Ӳ��У׼
  adc0_init_struct.ADC_HwTrgCfg = HW_TRGA;      //����A��ΪӲ������
  adc0_init_struct.ADC_DmaEnable = TRUE;        //ʹ��DMA����
  LPLD_ADC_Init(adc0_init_struct);      //��ʼ��ADC0-A��ͨ��
  //ADC0-B��ֻ�����ò�ͬ�����ĳ�Ա����
  adc0_init_struct.ADC_HwTrgCfg = HW_TRGB;      //����B��ΪӲ������
  LPLD_ADC_Init(adc0_init_struct);      //��ʼ��ADC0-B��ͨ��
  //ʹ��ADC0��ͨ��DAD1��AD14�����Ÿ��ù���
  LPLD_ADC_Chn_Enable(ADC0, DAD1);
  LPLD_ADC_Chn_Enable(ADC0, AD14);
  //ʹ��ADC0�����ת��ͨ��
  LPLD_ADC_EnableConversion(ADC0, DAD1, 0, FALSE);
  LPLD_ADC_EnableConversion(ADC0, AD14, 1, FALSE);
  
  //ADC1A
  adc1_init_struct.ADC_Adcx = ADC1;
  adc1_init_struct.ADC_BitMode = SE_12BIT;
  adc1_init_struct.ADC_CalEnable = TRUE;
  adc1_init_struct.ADC_HwAvgSel = HW_4AVG;
  adc1_init_struct.ADC_HwTrgCfg = HW_TRGA;
  adc1_init_struct.ADC_DmaEnable = TRUE;
  LPLD_ADC_Init(adc1_init_struct);
  //ADC1B
  adc1_init_struct.ADC_HwTrgCfg = HW_TRGB;
  LPLD_ADC_Init(adc1_init_struct);
  LPLD_ADC_Chn_Enable(ADC1, AD10);
  LPLD_ADC_Chn_Enable(ADC1, AD11);
  LPLD_ADC_EnableConversion(ADC1, AD10, 0, FALSE);
  LPLD_ADC_EnableConversion(ADC1, AD11, 1, FALSE);
    
  //**********************************************
  //Step 2.����DMA CH0��DMA CH1���ֱ���ADC0��ADC1��DMA����
  //DMA CH0
  dma0_init_struct.DMA_CHx = DMA_CH0;           //ʹ��Ch0ͨ��
  dma0_init_struct.DMA_Req = ADC0_DMAREQ;       //DMA����ԴΪADC0
  dma0_init_struct.DMA_MajorLoopCnt = 2;        //��ѭ������2��,��ΪҪѭ��ADC0��AB����ͨ��
  dma0_init_struct.DMA_MinorByteCnt = 2;        //��ѭ�������ֽڼ���������ADC����Ϊ12λ����˴���2�ֽڣ�
  dma0_init_struct.DMA_SourceAddr = (uint32)&(ADC0->R[0]);       //Դ��ַ��ADC0����Ĵ���A��ַ
  dma0_init_struct.DMA_SourceDataSize = DMA_SRC_16BIT;   //Դ��ַ�������ݿ��16λ
  dma0_init_struct.DMA_SourceAddrOffset = 4;    //Դ��ַƫ��Ϊ4���ֽڣ���ΪADC0->R�Ĵ�Ϊ32λ��A�鴫����ɺ��ƶ���B��
  dma0_init_struct.DMA_LastSourceAddrAdj = -8;  //��ѭ�������ڵ�ַΪ-8���ֽڣ���Ϊ��ѭ��Ϊ2�μ�������˵�ַƫ����8���ֽ�
  dma0_init_struct.DMA_DestAddr = (uint32)&Result;       //Ŀ�ĵ�ַ��������Ľ����������ͷ��ַ
  dma0_init_struct.DMA_DestDataSize = DMA_DST_16BIT;     //Ŀ�ĵ�ַ�������ݿ��16λ
  dma0_init_struct.DMA_DestAddrOffset = 2;      //Ŀ�ĵ�ַƫ��Ϊ2���ֽڣ���ΪResultΪ16λ����
  dma0_init_struct.DMA_LastDestAddrAdj = -4;    //Ŀ�ĵ�ַ�����ڵ�ַΪ-4���ֽ�
  dma0_init_struct.DMA_AutoDisableReq = FALSE;   //�����Զ��������󣬼�������ѭ��������������
  //��ʼ��DMA
  LPLD_DMA_Init(dma0_init_struct);
  //ʹ��DMA����
  LPLD_DMA_EnableReq(DMA_CH0);
  
  //DMA CH1�����û�����ͬ
  dma1_init_struct.DMA_CHx = DMA_CH1;   
  dma1_init_struct.DMA_Req = ADC1_DMAREQ;       
  dma1_init_struct.DMA_MajorLoopCnt = 2;        
  dma1_init_struct.DMA_MinorByteCnt = 2; 
  dma1_init_struct.DMA_SourceAddr = (uint32)&(ADC1->R[0]);       
  dma1_init_struct.DMA_SourceDataSize = DMA_SRC_16BIT;  
  dma1_init_struct.DMA_SourceAddrOffset = 4;
  dma1_init_struct.DMA_LastSourceAddrAdj = -8;
  dma1_init_struct.DMA_DestAddr = (uint32)&Result+4;       //Ŀ�ĵ�ַ������������ͷ2��Ԫ�ش�ADC0�Ľ�������Ҫƫ��4���ֽ�ȡ��3��Ԫ�صĵ�ַ
  dma1_init_struct.DMA_DestDataSize = DMA_DST_16BIT;  
  dma1_init_struct.DMA_DestAddrOffset = 2;
  dma1_init_struct.DMA_LastDestAddrAdj = -4;
  dma1_init_struct.DMA_AutoDisableReq = FALSE;   
  //��ʼ��DMA
  LPLD_DMA_Init(dma1_init_struct);
  //ʹ��DMA����
  LPLD_DMA_EnableReq(DMA_CH1);
    
  //**********************************************
  //Step 3.����PDB�����ڴ���ADC
  pdb_init_struct.PDB_CounterPeriodMs = 100;    //PDB���������ڣ����������4��ͨ��ÿ�ɼ�һ�εļ��
  pdb_init_struct.PDB_LoadModeSel = LOADMODE_0;
  pdb_init_struct.PDB_ContinuousModeEnable = TRUE;      //ʹ����������ģʽ����ֻ��Ҫ��ʼ����һ�Σ��Ժ�PDB�ͻ���������
  pdb_init_struct.PDB_TriggerInputSourceSel = TRIGGER_SOFTWARE; //�������ģʽ��������Ҫ������ģ�鴥��PDB����
  //��ʼ��PDB
  LPLD_PDB_Init(pdb_init_struct);
  //����PDBԤ��������
  //ʹ��ADC0-A���Ԥ��������
  LPLD_PDB_AdcTriggerCfg(ADC0, PRETRIG_EN_A|PRETRIG_DLY_A, 0);  
  //ʹ��ADC0-B���Ԥ�������ܣ���ʹ��Back to Backģʽ
  LPLD_PDB_AdcTriggerCfg(ADC0, PRETRIG_BB_B|PRETRIG_EN_B|PRETRIG_DLY_B, 0);
  //ʹ��ADC1-A���Ԥ�������ܣ���ʹ��Back to Backģʽ
  LPLD_PDB_AdcTriggerCfg(ADC1, PRETRIG_BB_A|PRETRIG_EN_A|PRETRIG_DLY_A, 0);
  //ʹ��ADC1-B���Ԥ�������ܣ���ʹ��Back to Backģʽ
  LPLD_PDB_AdcTriggerCfg(ADC1, PRETRIG_BB_B|PRETRIG_EN_B|PRETRIG_DLY_B, 0);
  //�������PDB��ʼ����
  LPLD_PDB_SoftwareTrigger();

  while(1)
  {
    delay();
    printf("ADC0_RA=%d\r\n", Result[0]);
    printf("  ADC0_RB=%d\r\n", Result[1]);
    printf("    ADC1_RA=%d\r\n", Result[2]);
    printf("      ADC1_RB=%d\r\n", Result[3]);
  } 
}


void delay()
{
  uint32 i=0,j=0;
  while(i<5000)
  {
    i++;
    j=0;
    while(j<1000)
      j++;
  }
}
