/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_uCosOSSem��-----------------
 * @file LPLD_uCosOSSem.c
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
 * ��MiniUSB�߲���RUSH Kinetis������Card�ϵ�USB
   ������������������USB�ӿڡ�
 * App_TaskStart�������Ϊ�ȴ��ź���Task_Start������
 * ������RUSH Kinetis������S1�������ᴥ�������жϲ�����
   �ź���
 * ��ʱApp_TaskStart������յ��ź�����תΪִ��̬
   �ɴ��ڷ�������
 ********************************************/

//UCOS
//���������ջ
OS_STK App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];		 
//�����ź���
OS_EVENT *Task_Start; 

GPIO_InitTypeDef Key_S1;

void App_TaskStart(void  *p_arg);
void key_isr(void);
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
  Key_S1.GPIO_PTx  = PTB;
  Key_S1.GPIO_Pins = GPIO_Pin6;
  Key_S1.GPIO_PinControl = INPUT_PULL_UP | IRQC_FA;
  Key_S1.GPIO_Dir  = DIR_INPUT;
  Key_S1.GPIO_Isr  = key_isr;
  
  LPLD_GPIO_Init(Key_S1); 
  LPLD_GPIO_EnableIrq(Key_S1);
  //�����ź��������ó�ֵΪ0
  //�����ź������
  Task_Start = OSSemCreate(0); 
  while (TRUE) 
  {                                          
    //�ȴ��ź���������ź���δ�����������ڹ���״̬
    OSSemPend(Task_Start,0,&err);
    
    if(err == OS_ERR_NONE )
    {
      printf("App_TaskStart:\tApp_TaskStart \r\n");
    }
  }
}

void key_isr(void)
{
  if(LPLD_GPIO_IsPinxExt(PORTB,GPIO_Pin6))
  {
    //�����ź���
    OSSemPost(Task_Start);
  }
}

