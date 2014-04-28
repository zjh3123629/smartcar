/**
* --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_OV7670��-----------------
* @file LPLD_OV7670.c
* @version 0.1
* @date 2013-9-29
* @brief ����DMAģ�飬ʵ����������ͷOV7670��ͼ���ȡ��
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
#include "DEV_SCCB.h"

/****************************************
˵����
*��MiniUSB�߲���RUSH Kinetis�������USB
������������������USB�ӿڡ�
*��OV7670��λ������������Ϊ115200
*ʹ����λ���鿴���н��
****************************************/

//ͼ����
#define H 250
//ͼ��߶�
#define V 200
#define PHOTO_SIZE H*V

void porta_isr(void);
void portb_isr(void);
void gpio_init(void);
void dma_init(void);

uint8 ov7670_init();
void delay(void);

GPIO_InitTypeDef pta_init;
GPIO_InitTypeDef ptb_init;
GPIO_InitTypeDef pte_init;
GPIO_InitTypeDef ptd_init;
DMA_InitTypeDef dma_init_struct;

uint8 Pix_Data[PHOTO_SIZE];       //�ɼ�50�� 200�е�ͼ������  
uint32 V_Cnt;                     //�вɼ�����
uint8 Is_DispPhoto;               //ͼ���ͱ�־

/********************************************************************/
void main (void)
{
 
  //�ر�ȫ���ж�
  DisableInterrupts;
  
  ov7670_init();
  delay();
  
  V_Cnt=0;          //�м���
  Is_DispPhoto=0;   //��ʾͼ��
  
  gpio_init();
  dma_init();
  
  //ʹ��PORTA��PORTB�ж�
  enable_irq(PORTB_IRQn);
  enable_irq(PORTA_IRQn);
  //ʹ��ȫ���ж�
  EnableInterrupts;
  
  
  while(1)
  {
    
    if(Is_DispPhoto==1)
    {   
      Is_DispPhoto = 0;
      //��ʾ����ͼ������
      //�ɸ�����λ����������޸Ĵ˴�
      
      //��PORTA�жϱ�־
      LPLD_GPIO_ClearIntFlag(PORTA);
      //ʹ��PORTA�ж�
      enable_irq(PORTA_IRQn);
      
    } 
    
  } 
}

void gpio_init()
{
  //OV���ݿڳ�ʼ����PTD8~PTD15
  ptd_init.GPIO_PTx = PTD;
  ptd_init.GPIO_Dir = DIR_INPUT;
  ptd_init.GPIO_Pins = GPIO_Pin8_15;
  ptd_init.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
  LPLD_GPIO_Init(ptd_init);
  
  //OV���źŽӿڳ�ʼ����PTB3-H
  ptb_init.GPIO_PTx = PTB;
  ptb_init.GPIO_Dir = DIR_INPUT;
  ptb_init.GPIO_Pins = GPIO_Pin3;
  ptb_init.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN;
  ptb_init.GPIO_Isr = portb_isr;
  LPLD_GPIO_Init(ptb_init); 
  
  //OV���źŽӿڳ�ʼ����PTA5-V
  pta_init.GPIO_PTx = PTA;
  pta_init.GPIO_Dir = DIR_INPUT;
  pta_init.GPIO_Pins = GPIO_Pin5;
  pta_init.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN;
  pta_init.GPIO_Isr = porta_isr;
  LPLD_GPIO_Init(pta_init); 
  
  //OV PCLK�źŽӿڳ�ʼ����PTE6-PCLK
  pte_init.GPIO_PTx = PTE;
  pte_init.GPIO_Pins = GPIO_Pin6;
  pte_init.GPIO_Dir = DIR_INPUT;
  pte_init.GPIO_PinControl = IRQC_DMARI | INPUT_PULL_DIS;
  LPLD_GPIO_Init(pte_init); 
  
}

void dma_init()
{
  //DMA��������
  dma_init_struct.DMA_CHx = DMA_CH0;    //CH0ͨ��
  dma_init_struct.DMA_Req = PORTE_DMAREQ;       //PORTEΪ����Դ
  dma_init_struct.DMA_MajorLoopCnt = H; //��ѭ������ֵ���вɼ����������
  dma_init_struct.DMA_MinorByteCnt = 1; //��ѭ���ֽڼ�����ÿ�ζ���1�ֽ�
  dma_init_struct.DMA_SourceAddr = (uint32)&PTD->PDIR+1;        //Դ��ַ��PTD8~15
  dma_init_struct.DMA_DestAddr = (uint32)Pix_Data;      //Ŀ�ĵ�ַ�����ͼ�������
  dma_init_struct.DMA_DestAddrOffset = 1;       //Ŀ�ĵ�ַƫ�ƣ�ÿ�ζ�������1
  dma_init_struct.DMA_AutoDisableReq = TRUE;    //�Զ���������
  //��ʼ��DMA
  LPLD_DMA_Init(dma_init_struct);
}


void porta_isr()
{
  if(LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin5))
  {
    //��⵽����ʼ�źţ�����Ŀ�ĵ�ַ
    LPLD_DMA_LoadDstAddr(DMA_CH0, Pix_Data);
    //�����жϱ�־����ֹ������Ч���ж�
    LPLD_GPIO_ClearIntFlag(PORTB);
    enable_irq(PORTB_IRQn);
  }
  
}
void portb_isr()
{
  if(LPLD_GPIO_IsPinxExt(PORTB, GPIO_Pin3))
  {
    //��⵽�п�ʼ�źţ�ʹ��DMA����
    if(V_Cnt<V){
      LPLD_DMA_EnableReq(DMA_CH0);  
      V_Cnt++; 
    }
    //�����ɼ��������ر��ж�
    else
    {
      //��GPIO�ж� 
      disable_irq(PORTA_IRQn);
      disable_irq(PORTB_IRQn);
      Is_DispPhoto = 1;//������ʾͼ��
      V_Cnt=0;  
    }
  }
}


uint8 ov7670_init(void)
{
  uint16 i = 0;
  uint8 device_id = 0;
  
  LPLD_SCCB_Init();
  
  delay();
  
  //��λOV7670�Ĵ���
  while( 0 == LPLD_SCCB_WriteReg(0x12, 0x80 )) 
  {
    i++;
    if(i == 500)
    {
      return 0 ;
    }    
  }
  delay();
  
  //��ȡ�豸ID
  while( 0 == LPLD_SCCB_ReadReg(0x1C, &device_id, 1));	
  
  //���ΪOV7670
  if(device_id == 0x7F)
  {  
    //while( 0 == LPLD_SCCB_WriteReg(0x1E, 0x21) );
    while( 0 == LPLD_SCCB_WriteReg(0x3E, 0x19) );	
    while( 0 == LPLD_SCCB_WriteReg(0x73, 0x09) );	
    //while( 0 == LPLD_SCCB_WriteReg(0x15, 0x20) );	
  }
  else
  {
    return 0;
  }
  
  return 1;
}

/*
 * ��ʱһ��ʱ��
 */
void delay()
{
  uint16 i, n;
  for(i=0;i<30000;i++)
  {
    for(n=0;n<200;n++)
    {
      asm("nop");
    }
  }
}