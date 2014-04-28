/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_WatchDog��-----------------
 * @file LPLD_WatchDog.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����WDOGģ�飬ʵ�ֿ��Ź�ģ���ʹ�á�
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
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
   *ע�͵�while�е�ι���������۲����н����
 ****************************************/

void delay(void);

void main (void)
{
  
  printf("Init Watch Dog!\r\n");
  LPLD_WDOG_Init(1000);
  LPLD_WDOG_Enable();
    
  while(1)
  {
    delay();
    //ע�ʹ˾佫����ϵͳ��λ
    LPLD_WDOG_Feed();
  } 
}

/*
 * ��ʱһ��ʱ��
 */
void delay()
{
  uint16 i, n;
  for(i=0;i<30000;i++)
  {
    for(n=0;n<200;n++)
    {
      asm("nop");
    }
  }
}

