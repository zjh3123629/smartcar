/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_uCosV292��-----------------
 * @file LPLD_uCosV292.c
 * @version 0.0
 * @date 2013-9-29
 * @brief ���ڸù��̵�����
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
 * ��������UCOS����, App_TaskStart�� App_Task1
 * App_TaskStart����2ms�ͷ�һ��CPUʹ��Ȩ��
 * App_Task1����1ms�ͷ�һ��CPUʹ��Ȩ��
 * ͨ�����ڵ������ֲ鿴����������л�״̬
 * ��MiniUSB�߲���RUSH Kinetis�������USB
 * ������������������USB�ӿڡ�
 * ʹ�ô��ڵ������ֲ���������Ϊ115200
 * ʹ�ô��ڵ������ֲ鿴���н����
 ********************************************/

//UCOS
//���������ջ
OS_STK App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];	//������ʼ�����ջ
OS_STK App_Task1_Stk[APP_CFG_TASK_START_STK_SIZE];      //������ʼ����1��ջ

//�����ź���
OS_EVENT *Task_Start; 

void App_TaskStart(void  *p_arg);
void App_Task1 (void *p_arg);
/********************************************************************/
void  main (void)
{
#if (defined(UCOS_II))
  INT8U err;
  
  //��ʼ��UCOS������ϵͳ�ں�
  OSInit();      
  
  printf("uCOS_Kernel_Init \r\n");
  
  //������ʼ����
  OSTaskCreateExt((void (*)(void *)) App_TaskStart,         
                  (void           *) 0,
                  (OS_STK         *)&App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                  (INT8U           ) APP_CFG_TASK_START_PRIO,
                  (INT16U          ) APP_CFG_TASK_START_PRIO,
                  (OS_STK         *)&App_TaskStartStk[0],
                  (INT32U          ) APP_CFG_TASK_START_STK_SIZE,
                  (void           *) 0,
                  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
  //����������֣��Ա��ڼ��Ӵ��ڿ��Կ���
#if (OS_TASK_NAME_EN > 0)
  OSTaskNameSet(APP_CFG_TASK_START_PRIO, "App_TaskStart", &err);
#endif    
  //��ʼ�������������ں˽��е���
  OSStart();                                                 
#endif  
  while(1);
}

//��ʼ����
void  App_TaskStart (void *p_arg)
{
 (void)p_arg;
 
 INT8U err;
  //��ʼ��OSʱ��
  SystemTickInit(); 

#if (OS_TASK_STAT_EN > 0)
  OSStatInit();                                              
#endif    
  OSTaskCreate((void (*)(void *)) App_Task1,     //��������1                                      
                (void*) 0,
                (OS_STK*)&App_Task1_Stk[APP_CFG_TASK_START_STK_SIZE - 1],
                (INT8U) APP_TASK1_PRIO
                );
   //����������֣��Ա��ڼ��Ӵ��ڿ��Կ���
#if (OS_TASK_NAME_EN > 0)
  OSTaskNameSet(APP_TASK1_PRIO, "APP_TASK1", &err);
#endif 
  while (TRUE) 
  {                                          
    OSTimeDlyHMSM(0, 0,2,0);
    printf("App_TaskStart:\tApp_TaskStart \r\n");
  }
}

void  App_Task1 (void *p_arg)
{
  (void)p_arg;
  
  printf("App_Task1 !!\n");
  
  while(TRUE)
  {
    OSTimeDlyHMSM(0, 0,1,0);
    printf("App_Task1:\tApp_Task1 \r\n");
  }
}

