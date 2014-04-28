/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_SerialComm��-----------------
 * @file LPLD_SerialComm.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����UARTģ�飬ʵ�ִ��ڵ������շ���
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
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ9600
   *ʹ�ô��ڵ������ֲ鿴���н��
 ****************************************/

//��������  
void uart_init(void);
//��������
UART_InitTypeDef uart5_init_struct;

void main (void)
{
  int8 recv;
  
  uart_init();
  LPLD_UART_PutCharArr(UART5, "Input something:\r\n", 18);
  
  while(1)
  {
    recv = LPLD_UART_GetChar(UART5);
    LPLD_UART_PutChar(UART5, recv);
  } 
  
}

/*
 * ��ʼ��UART5ģ��
 *
 */
void uart_init(void)
{
  uart5_init_struct.UART_Uartx = UART5; //ʹ��UART5
  uart5_init_struct.UART_BaudRate = 9600; //���ò�����9600
  uart5_init_struct.UART_RxPin = PTE9;  //��������ΪPTE9
  uart5_init_struct.UART_TxPin = PTE8;  //��������ΪPTE8
  //��ʼ��UART
  LPLD_UART_Init(uart5_init_struct);
}
