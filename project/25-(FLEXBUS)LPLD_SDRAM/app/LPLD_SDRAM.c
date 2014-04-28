/**
* --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_SDRAM��-----------------
* @file LPLD_SDRAM.c
* @version 0.1
* @date 2013-9-29
* @brief ���ڸù��̵�����
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
//����LCD�豸����
#include "DEV_LCD.h"
//����SDRAM�豸����
#include "DEV_SDRAM.h"

/****************************************
˵����
*��2.8" TFTҺ�����嵽RUSH������J1�����ϡ�
*�������̹۲�Һ������ʾ�����
*���ڿ������ϵ�SDRAM��K60��FB1���ƣ����
�����ȳ�ʼ������LCD��FB0��FB1���ܹ�����
****************************************/

void main (void)
{
  uint8 *buff;
  
  //��ʼ��LCD
  //������
  //  ��ʼ��FlexBus��FB0ģ�顢128KѰַ�ռ䡢16λ���д��
  //  ��ʼ��ILI9320 LCD������
  LPLD_LCD_Init();
  
  //��ʼ��SDRAM
  //������
  //  ��ʼ��FlexBus��FB1ģ�顢256KѰַ�ռ䡢8λ���д��
  LPLD_SDRAM_Init();
  
  //��̬����SDRAM�е�һ�οռ�
  buff = LPLD_SDRAM_Malloc(10);
  
  //��ӡ�ղŷ����SDRAM�ռ��׵�ַ
  printf("buff's ADDR is 0x%X\r\n", buff);
  
  //������д�붯̬�����SDRAM�ռ�
  printf("Write buff with:\r\n\t", buff);
  for(uint8 i=0; i<10; i++)
  {
    buff[i] = i;
    printf("buff[%d]=%d, ", i, i);
  }

  //��ȡд�뵽SDRAM�е�����
  printf("\r\nRead buff:\r\n\t", buff);
  for(uint8 i=0; i<10; i++)
  {
    printf("buff[%d]=%d, ", i, buff[i]);
  }
  
  while(1)
  {
    
  }
}
