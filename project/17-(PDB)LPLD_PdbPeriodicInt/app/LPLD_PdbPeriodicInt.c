/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_PdbPeriodicInt��-----------------
 * @file LPLD_PdbPeriodicInt.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����PDBģ�飬ʵ����ʱ���ڶ�ʱ�жϡ�
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
 ****************************************/

//��������
void pdb_init(void);
void pdb_isr(void);
//��������
PDB_InitTypeDef pdb_init_struct;

void main (void)
{
  //��ʼ��PDB��ʱ�ж�
  pdb_init();   
  //��ӡ�˾䷽��鿴��ʱЧ��
  printf("Waiting for 200ms, and then:\r\n");

  while(1)
  {

  } 
}

/*
 * ��ʼ��PDB
 *
 */
void pdb_init(void)
{
  //����PDB��ʱ��ʱ�жϲ���
  pdb_init_struct.PDB_CounterPeriodMs = 1000;   //�������������1000����
  pdb_init_struct.PDB_TriggerInputSourceSel = TRIGGER_SOFTWARE; //����ԴΪ�������
  pdb_init_struct.PDB_ContinuousModeEnable = TRUE;      //��������ģʽ
  pdb_init_struct.PDB_DelayMs = 200;    //�ж���ʱʱ��200����
  pdb_init_struct.PDB_IntEnable = TRUE; //ʹ����ʱ�ж�
  pdb_init_struct.PDB_Isr = pdb_isr;    //�жϺ�������
  //��ʼ��PDB
  LPLD_PDB_Init(pdb_init_struct);
  //ʹ��PDB�ж�
  LPLD_PDB_EnableIrq();
  //�������
  LPLD_PDB_SoftwareTrigger();
}

/*
 * PDB�жϺ���
 *
 */
void pdb_isr(void)
{
  //�˾��ӡʱ��ΪPDB��ʼ�����200ms
  printf("This is a PDB delay interrupt!\r\n");
}