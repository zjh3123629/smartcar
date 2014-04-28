/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_SdCard��-----------------
 * @file LPLD_SdCard.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����SDHCģ�飬ʵ��SD�������ݶ�д��
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
   *��MicroSD�����뵽K60���İ��SD����ۡ�
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
 ****************************************/
//���ж�д�����Ŀ���
#define BLOCK_LEN     2
#define BUFFER_SIZE   512*BLOCK_LEN

/********************************************************************/
void main (void)
{
  uint32 i;	
  //��д��������
  uint8  sdhc_dat_buffer1[BUFFER_SIZE];    
  //SD����������ֵ
  SDHCRES sd_state;    
  
  //���ж�
  DisableInterrupts;                                      
  
  //SDHC��ʼ��
  sd_state = (SDHCRES)LPLD_SDHC_InitCard();  
  
  //���ж�
  EnableInterrupts;			                            
  
  //�ж�SD������״̬
  if (SDHCRES_OK == sd_state)
  {
    printf("\r\nSD init success.\r\n");
    //��(��)����������������SD����״̬
    sd_state = LPLD_SDHC_ReadBlocks(sdhc_dat_buffer1, 0, BLOCK_LEN);
  }
  else
  {
    printf("\r\nSD init failure.\r\n");
  }
  
  //�ж�SD������״̬
  if (SDHCRES_OK == sd_state)
  {
    printf("Read disk success.\r\n");
    printf("SD data: \r\n");
    //�����ɹ�����ӡ����������
    for(i = 0;i < BUFFER_SIZE;i++) 
    {
      printf("%02X ", sdhc_dat_buffer1[i]);
    }  
    printf("\r\n");
  }
  else
  {
    printf("Read disk failed.\n\r");
  }
  
  
  //�ж�SD������״̬
  if (SDHCRES_OK == sd_state)
  {
    printf("Update data success.\r\n");
    //�����������飬�Լ�1
    for (i = 0; i < BUFFER_SIZE; i++)
    {
      sdhc_dat_buffer1[i] ++;
    }
    //д(��)����������������SD����״̬
    sd_state = LPLD_SDHC_WriteBlocks(sdhc_dat_buffer1, 0, BLOCK_LEN);  
  }
  
  //�ж�SD������״̬
  if (SDHCRES_OK == sd_state)
  {
    printf("Write Disk success.\r\n");
    //�ٴζ�(��)����������������SD����״̬
    sd_state = LPLD_SDHC_ReadBlocks(sdhc_dat_buffer1, 0, BLOCK_LEN);
  }
  else
  {
    printf("Write Disk failure.\r\n");
  }
  
  //�ж�SD������״̬
  if (SDHCRES_OK == sd_state)
  {
    printf("Read disk success.\r\n");
    printf("SD data: \r\n");
    //�����ɹ�����ӡ����������
    for(i = 0;i < BUFFER_SIZE;i++) 
    {
      printf("%02X ", sdhc_dat_buffer1[i]);
    }
    printf("\r\n");
  }
  else
  {
    printf("Read disk failure.\r\n");
  }
  
  while(1)
  {
    
  } 
}
