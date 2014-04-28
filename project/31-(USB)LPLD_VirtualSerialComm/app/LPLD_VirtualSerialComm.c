/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_VirtualSerialComm��-----------------
 * @file LPLD_VirtualSerialComm.c
 * @version 0.0
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

/********************************************
 * ˵��: 
 * ��MiniUSB�߲���RUSH Kinetis������Card�ϵ�USB
   ������������������USB�ӿڡ�
 * ��װlib\usb\LPLD_CDC_class_Driver_Kinetis CDC����
 * ʹ�ô��ڵ������ֲ������������á�
 * ʹ�ô��ڵ������ַ�������,��Ƭ�����յ����ݺ󣬽����ݷ��ء�
 ********************************************/
#include "common.h"
#include "HW_USB.h"
uint8_t rx_len = 0;
uint8_t rx_buf[64];

void usb_rev_handle(void);
/********************************************************************/
void main (void)
{
  LPLD_USB_Init();                    //��ʼ��K60����
  LPLD_USB_SetRevIsr(usb_rev_handle); //����USB�����ж�
  while(1)
  {
  
  } 
}

/*
*  usb_rev_handle
*  USB�жϽ��պ���
*/
void usb_rev_handle(void)
{
  rx_len = LPLD_USB_VirtualCom_Rx(rx_buf);
  LPLD_USB_QueueData();
  LPLD_USB_VirtualCom_Tx(rx_buf,rx_len);
}

