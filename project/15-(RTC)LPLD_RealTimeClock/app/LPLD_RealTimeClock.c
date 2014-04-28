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
#include "TimeStamp.h"
/********************************************
 * ˵��: 
 * RTC ÿ10s��ʱ�����������������ж�
 * ��MiniUSB�߲���RUSH Kinetis�������USB
 * ������������������USB�ӿڡ�
 * ʹ�ô��ڵ������ֲ���������Ϊ115200
 * ʹ�ô��ڵ������ֲ鿴���н����
 ********************************************/
RTC_InitTypeDef rtc_init_structure;
TimeStamp_FormatTypeDef time;

void rtc_isr(void);
/********************************************************************/
void main (void)
{
  uint32 temp;
  
  //����RTC SIM ʱ�ӣ�ͨ���ж�TIF��֪
  //��ǰRTC�Ƿ���VBAT POR���� Software Reset
  //���û�з�����RTC��������   
  if(LPLD_RTC_IsRunning() == 0) 
  {
    printf("RTC init\r\n");
    
    LPLD_AutoInitTimeStamp(&time);

    rtc_init_structure.RTC_Seconds = LPLD_DateTimeToTimeStamp(&time);
    rtc_init_structure.RTC_InvalidIsr = rtc_isr;
    rtc_init_structure.RTC_InvalidIntEnable = TRUE;
    LPLD_RTC_Init(rtc_init_structure);
    LPLD_RTC_EnableIrq();
  }
  else //RTC��������
  {
    printf("RTC run\r\n");
  }
  
  while(1)
  {
    temp = LPLD_RTC_GetRealTime();
    LPLD_TimeStampToDateTime(temp,&time);
    printf("%4d-%02d-%02d %02d:%02d:%02d\r\n", time.year, time.month, time.day, time.hour, time.minute, time.second);
    LPLD_LPTMR_DelayMs(1000);
  } 
}

void rtc_isr()
{
  printf("RTC VBAT POR\r\n"); //������ص����ж�
}


