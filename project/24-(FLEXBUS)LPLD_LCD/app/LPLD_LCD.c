/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_LCD��-----------------
 * @file LPLD_LCD.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����FlexBusģ�飬�����ⲿLCDҺ��������ʾ��
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

/****************************************
 ˵����
   *��2.8" TFTҺ�����嵽RUSH������J1�����ϡ�
   *�������̹۲�Һ������ʾ�����
 ****************************************/

void main (void)
{
  //��ʼ��LCD
  //������
  //  ��ʼ��FlexBus��FB0ģ�顢128KѰַ�ռ䡢16λ���д��
  //  ��ʼ��ILI9320 LCD������
  LPLD_LCD_Init();
  
  //��ʼ��LCD����ʱһ��ʱ��
  LPLD_LPTMR_DelayMs(10);
  
  //���LCD����ɫ����ɫ
  LPLD_LCD_FillBackground(COLOR_Black);
  
  //��ӡһ���ַ�������ɫ���塢��ɫ����
  LPLD_LCD_PrintStringLine("Hello World! ", COLOR_White, COLOR_Black);
  
  //����һ�д�ӡ�ַ�������ɫ���塢��ɫ����
  LPLD_LCD_PrintString("RUSH Kinetis!", COLOR_Red, COLOR_Black);
  
  //��ӡһ�����֣���ɫ���塢��ɫ����
  LPLD_LCD_PrintNumLine(9320, 4, COLOR_White, COLOR_Black);
  
  //��ָ�����꿪ʼ��ʾһ������
  //x,y��ʼ����(0,50) x,y��������(320,50)
  LPLD_LCD_DrawLine(0, 50, 320, 50, COLOR_Blue); 
  
  //��ָ���������һ������
  //x,y��ʼ����(80,80) x����150 y����100
  LPLD_LCD_DrawRectangle(80, 80, 150, 100, COLOR_Magenta, COLOR_Yellow);
  
  while(1)
  {

  } 
}

