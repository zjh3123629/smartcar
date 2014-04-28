/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_TouchPad��-----------------
 * @file LPLD_TouchPad.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����TSIģ�飬�жϴ������Ĵ��ز�����
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
   *ʹ�ô��ڵ������ֲ鿴���н����
   *����ָ�����������O��X����鿴���н����
 ****************************************/

//������Ч����ֵ������ʶ����Ч����
#define PRESS_CNT       (50)
//�����������
#define PAD_X   0
#define PAD_O   1

//��������
void tsi_init(void);
void tsi_isr(void);
//��������
TSI_InitTypeDef tsi_init_struct;
uint8 press_counter[2] = {PRESS_CNT, PRESS_CNT};

void main (void)
{
  
  //��ʼ��TSI
  tsi_init();

  while(1)
  {

  } 
}

/*
 * ��ʼ��TSI
 *
 */
void tsi_init(void)
{
  //����TSI��ʼ������
  tsi_init_struct.TSI_Chs = TSI_Ch7 | TSI_Ch8;  //X��O���������ֱ�Ϊ7��8ͨ��
  tsi_init_struct.TSI_ScanTriggerMode = TSI_SCAN_PERIOD;        //����ɨ��ģʽ
  tsi_init_struct.TSI_IsInitSelfCal = TRUE;     //���ó�ʼ��ʱ��У�鹦��
  tsi_init_struct.TSI_EndScanOrOutRangeInt = TSI_ENDOFDCAN_INT; //ʹ��ɨ������ж�
  tsi_init_struct.TSI_EndScanIsr = tsi_isr;     //�����жϺ���
  //��ʼ��TSI
  LPLD_TSI_Init(tsi_init_struct);
  //ʹ��TSI�ж�
  LPLD_TSI_EnableIrq();
}

/*
 * TSI����ɨ���ж�
 *
 */
void tsi_isr()
{
  uint8 valid_touch = 0;
  
  //�ж�7ͨ���Ƿ񳬹�������ֵ
  if(LPLD_TSI_IsChxTouched(7))
  {
    //������Ч�������Լ�
    press_counter[PAD_X]--;
    //���Լ���0ʱ����ʶ��Ϊ��Ч����
    if(press_counter[PAD_X]==0)
    {
      //��Ч������־��λ
      valid_touch |= (1<<PAD_X);
      //�ָ���Ч��������ֵ
      press_counter[PAD_X] = PRESS_CNT;
    }
  }
  else
  {
    //����ָ���Ч��������ֵ
    press_counter[PAD_X] = PRESS_CNT;
  }
  
  //����ͬ��
  if(LPLD_TSI_IsChxTouched(8))
  {
    press_counter[PAD_O]--;
    if(press_counter[PAD_O]==0)
    {
      valid_touch |= (1<<PAD_O);
      press_counter[PAD_O] = PRESS_CNT;
    }
  }
  else
  {
    press_counter[PAD_O] = PRESS_CNT;
  }
  
  //���X����Ϊ��Ч���������ӡ״̬
  if(valid_touch & (1<<PAD_X))
  {
    printf("X Pressed!\r\n");
  }
  
  //���O����Ϊ��Ч���������ӡ״̬
  if(valid_touch & (1<<PAD_O))
  {
    printf("\tO Pressed!\r\n");
  }
}