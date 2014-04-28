/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_SerialInterrupt��-----------------
 * @file LPLD_SerialInterrupt.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����UARTģ�鼰���жϹ��ܣ�ʵ�ִ��ڵ������շ���
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
void uart_isr(void);
//��������
UART_InitTypeDef uart5_init_struct;

void main (void)
{
  
  uart_init();
  LPLD_UART_PutCharArr(UART5, "Input something:\r\n", 20);
  
  while(1)
  {

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
  uart5_init_struct.UART_RxIntEnable = TRUE;    //ʹ�ܽ����ж�
  uart5_init_struct.UART_RxIsr = uart_isr;      //���ý����жϺ���
  //��ʼ��UART
  LPLD_UART_Init(uart5_init_struct);
  //ʹ��UART�ж�
  LPLD_UART_EnableIrq(uart5_init_struct);
}

/*
 * UART5�����жϺ���
 *
 */
void uart_isr(void)
{
  int8 recv;
  
  recv = LPLD_UART_GetChar(UART5);
  LPLD_UART_PutChar(UART5, recv);
}
