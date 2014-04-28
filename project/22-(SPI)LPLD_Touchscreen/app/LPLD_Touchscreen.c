/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_TouchScreen��-----------------
 * @file LPLD_TouchScreen.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����SPIģ�飬ͨ��AD7843���Ƶ���ʽ��������
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
#include "DEV_Touchscreen.h"

/****************************************
 ˵����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
   *��2.8" TFTҺ�����嵽RUSH������J1�����ϡ�
   *�����Ļ��ͬλ�ù۲����н����
 ****************************************/

uint16 X_Positon = 0; //����X�����
uint16 Y_Positon = 0; //����Y�����

void main (void)
{
  LPLD_Touchscreen_Init(); //��ʼ��SPI
  
  while(1)
  {
    X_Positon=LPLD_Touchscreen_GetResult(LPLD_SER_SAMPLE_X);
    Y_Positon=LPLD_Touchscreen_GetResult(LPLD_SER_SAMPLE_Y);
    printf("X,Y:\t%d\t%d\r\n",X_Positon, Y_Positon);
    LPLD_LPTMR_DelayMs(100);
  } 
}

/********************************************************************/
