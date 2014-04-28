/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_AlarmClock��-----------------
 * @file LPLD_AlarmClock.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����RTCģ�飬ʵ�����ӹ��ܡ�
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

/********************************************
 * ˵��: 
 * RTC ÿ10s��ʱ�����������������ж�
 * ��MiniUSB�߲���RUSH Kinetis�������USB
 * ������������������USB�ӿڡ�
 * ʹ�ô��ڵ������ֲ���������Ϊ115200
 * ʹ�ô��ڵ������ֲ鿴���н����
 ********************************************/

void rtc_isr();

RTC_InitTypeDef rtc_init_structure;

/********************************************************************/
void main (void)
{
  rtc_init_structure.RTC_Seconds = 0;
  rtc_init_structure.RTC_AlarmTime = 10; //���ñ���ʱ�䣬��10sʱ����
  rtc_init_structure.RTC_AlarmIsr = rtc_isr;
  rtc_init_structure.RTC_AlarmIntEnable = TRUE; //ʹ�ܱ����ж�
  
  LPLD_RTC_Init(rtc_init_structure); //��ʼ��RTC
  LPLD_RTC_EnableIrq(); //�����ж�
  while(1)
  {

  } 
}

void rtc_isr()
{
  rtc_init_structure.RTC_AlarmTime += 10;
  printf("the AlarmTime is : 10s\r\n"); 
  LPLD_RTC_SetAlarmTime(rtc_init_structure.RTC_AlarmTime); //�������ñ���ʱ��
}

