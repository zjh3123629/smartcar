/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_MacComm��-----------------
 * @file LPLD_MacComm.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����ENETģ�飬ʵ����̫��MAC������ͨѶ��
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
   *��SER_A��չ��嵽RUSH�������ϣ�ͨ������
    ����SER_A����PC����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ͨ��Wireshake���PC�������۲����н����
 ****************************************/

//��������
void enet_init(void);
void enet_rx_init(void);
void pit_init(void);
void pit_isr(void);
//��������
ENET_InitTypeDef enet_init_struct;
PIT_InitTypeDef pit_init_struct;

//�������Ͷ���
#define ENET_TYPE_ARP   {0x08, 0x06}
#define ENET_TYPE_IP    {0x08, 0x00}

//����MAC�����ַ����
uint8  gCfgLoca_MAC[] = {0x22, 0x22, 0x22, 0x00, 0x00, 0x01};
//Ŀ��MAC�����ַ���壬�㲥��ַ
uint8  gCfgDest_MAC[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//��̫֡���ͣ�ARP����
uint8  gCfgEnet_Type[] = ENET_TYPE_ARP;
//��̫֡���ͻ�����
uint8  gTxBuffer[CFG_ENET_TX_BUFFER_SIZE]; 
//��̫֡���ձ�־
uint8  gRecvFlag=0;  

void main (void)
{

  DisableInterrupts;
  
  enet_init();
  
  pit_init();
  
  EnableInterrupts;
  
  while(1)
  {
    //�ж��Ƿ���յ���̫֡
    if(gRecvFlag == 1)
    {
      printf("\tMac Message Received!\r\n");
      gRecvFlag = 0;
    }
  } 
}

/*
 * ��ʼ��ENETģ��
 *
 */
void enet_init(void)
{
  //����ENETģ�����
  enet_init_struct.ENET_MacAddress = gCfgLoca_MAC;      //����MAC��ַ
  enet_init_struct.ENET_RxIsr = enet_rx_init;   //���ý����жϺ���
  //��ʼ��ENET
  LPLD_ENET_Init(enet_init_struct);
}

/*
 * ��̫֡�����жϺ���
 *
 */
void enet_rx_init( void )
{  
  gRecvFlag = 1;
}

/*
 * PIT��ʱ�жϳ�ʼ��
 *
 */
void pit_init(void)
{
  pit_init_struct.PIT_Pitx = PIT0;
  pit_init_struct.PIT_PeriodMs = 1000;  //��ʱ1000ms
  pit_init_struct.PIT_Isr = pit_isr;
  LPLD_PIT_Init(pit_init_struct);
  LPLD_PIT_EnableIrq(pit_init_struct);
}

/*
 * ��ʱ�жϺ�����������̫�㲥֡
 *
 */
void pit_isr(void)
{
  uint32 i;
  static uint32 j=0;
  
  //������̫֡0~5�ֽ�Ϊ��Ŀ�ĵ�ַ
  gTxBuffer[0]  = gCfgDest_MAC[0];
  gTxBuffer[1]  = gCfgDest_MAC[1];
  gTxBuffer[2]  = gCfgDest_MAC[2];
  gTxBuffer[3]  = gCfgDest_MAC[3];
  gTxBuffer[4]  = gCfgDest_MAC[4];
  gTxBuffer[5]  = gCfgDest_MAC[5];
  //������̫֡1~11�ֽ�Ϊ��������ַ
  gTxBuffer[6]  = gCfgLoca_MAC[0];
  gTxBuffer[7]  = gCfgLoca_MAC[1];
  gTxBuffer[8]  = gCfgLoca_MAC[2];
  gTxBuffer[9]  = gCfgLoca_MAC[3];
  gTxBuffer[10] = gCfgLoca_MAC[4];
  gTxBuffer[11] = gCfgLoca_MAC[5];
  //������̫֡12~13�ֽ�Ϊ����������
  gTxBuffer[12] = gCfgEnet_Type[0];
  gTxBuffer[13] = gCfgEnet_Type[1];
  //������̫֡14�ֽ��Ժ������
  for(i=14; i<CFG_ENET_TX_BUFFER_SIZE; i++)
  {
    gTxBuffer[i] = j++;  
  }
  //����MAC����
  LPLD_ENET_MacSend(gTxBuffer, 100);
  printf("Mac Message Send!\r\n");

}
