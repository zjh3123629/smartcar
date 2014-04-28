/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_DelayMs��-----------------
 * @file LPLD_DelayMs.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����LPTMRģ�飬ʵ�ֺ��뼶��׼��ʱ��
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
 * ����K60��Ƭ����LPTMRģ�����Ms����ʱ
 * 1��ͨ��LPTMR��ʱ�жϵķ�ʽ���ö�ʱʱ��
 * 2��ͨ��LPTMR��ѯ��־λ�ķ�ʽ������ʱ
 * ��MiniUSB�߲���RUSH Kinetis�������USB
 * ������������������USB�ӿڡ�
 * ʹ�ô��ڵ������ֲ���������Ϊ115200
 * ʹ�ô��ڵ������ֲ鿴���н����
 * ͨ���ı�DELAY_MODE�ķ�ʽ�ı��жϻ����ǲ�ѯ
 * POLLING_DELAY ��ѯ��ʽ
 * INETERRUPT_DELAY �жϷ�ʽ
 ********************************************/

//ͨ��DELAY_MODEѡ�����ж϶�ʱ������ѯ��ʱ
#define DELAY_MODE INETERRUPT_DELAY 
#define POLLING_DELAY     (0)
#define INETERRUPT_DELAY  (1)
LPTMR_InitTypeDef lptmr_init_param;

#if DELAY_MODE == INETERRUPT_DELAY
void lptmr_isr(void);
#endif

void main (void)
{
#if DELAY_MODE == INETERRUPT_DELAY
  //LPTMR_MODE_TIMER�͹��Ķ�ʱ������
  //ʹ���ж�
  lptmr_init_param.LPTMR_Mode = LPTMR_MODE_TIMER;
  lptmr_init_param.LPTMR_PeriodMs = 1000; //1s
  lptmr_init_param.LPTMR_IntEnable = TRUE;
  lptmr_init_param.LPTMR_Isr = lptmr_isr;
  LPLD_LPTMR_Init(lptmr_init_param); 
  LPLD_LPTMR_EnableIrq();
#endif  
  while(1)
  {
#if DELAY_MODE == POLLING_DELAY
    LPLD_LPTMR_DelayMs(2000);
    printf("the interval is 2s\r\n");
#endif
  } 
}

#if DELAY_MODE == INETERRUPT_DELAY
void lptmr_isr(void)
{
  printf("the interval is 1s\r\n");
}
#endif 
