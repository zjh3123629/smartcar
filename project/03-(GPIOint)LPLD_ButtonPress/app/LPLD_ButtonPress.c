/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_ButtonPress��-----------------
 * @file LPLD_ButtonPress.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����GPIOģ�鼰���жϣ��жϰ���������
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
   *ʹ��RUSH Kinetis�������ϵİ���S1��S2
    ��Ϊ���ư�����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н����
   *ͨ���޸�INT�ı��жϺͲ�ѯ��ʽ��
 ****************************************/

//��ʹ���жϷ�ʽ��Ϊ1����ʹ��ѯ��ʽ��Ϊ0
#define INT  0   

//��������
void init_gpio(void);
void delay(void);
void portb_isr(void);
//��������
GPIO_InitTypeDef gpio_init_struct;

void main (void)
{
  
  //��ʼ�� GPIO
  init_gpio();
  
  while(1)
  {
#if(INT!=1) //���Ϊ��ѯ��ʽ
    if(PTB6_I == 0)
    {
      //ȥ��
      delay();
      if(PTB6_I==0)
      {
        printf("Button1-PTB6 Pressed!\r\n");
      }
      //ֱ�������ɿ�������
      while(PTB6_I==0);
    }
    if(PTB7_I == 0)
    {
      //ȥ��
      delay();
      if(PTB7_I==0)
      {
        printf("Button2-PTB7 Pressed!\r\n");
      }
      //ֱ�������ɿ�������
      while(PTB7_I==0);
    }
#endif
  } 
}

/*
 * ��ʼ�����Ӱ�����GPIO����
 *
 */
void init_gpio()
{

#if(INT) //���Ϊ�жϷ�ʽ
  // ���� PTB7��PTB6 ΪGPIO����,����,�ڲ������������ز����ж�
  gpio_init_struct.GPIO_PTx = PTB;      //PORTB
  gpio_init_struct.GPIO_Pins = GPIO_Pin6|GPIO_Pin7;     //����6��7
  gpio_init_struct.GPIO_Dir = DIR_INPUT;        //����
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;     //�ڲ�����|�������ж�
  gpio_init_struct.GPIO_Isr = portb_isr;        //�жϺ���
  LPLD_GPIO_Init(gpio_init_struct);
  //ʹ���ж�
  LPLD_GPIO_EnableIrq(gpio_init_struct);
#else //���Ϊ��ѯ��ʽ
  // ���� PTB7��PTB6 ΪGPIO����,����,�ڲ��������������ж�
  gpio_init_struct.GPIO_PTx = PTB;      //PORTB
  gpio_init_struct.GPIO_Pins = GPIO_Pin6|GPIO_Pin7;     //����6��7
  gpio_init_struct.GPIO_Dir = DIR_INPUT;        //����
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS;     //�ڲ�����|�������ж�
  LPLD_GPIO_Init(gpio_init_struct);
#endif
  
}

/*
 * PortB�жϻص�����
 *
 */
void portb_isr()
{
  //���PTB6�����ж�
  if(LPLD_GPIO_IsPinxExt(PORTB, GPIO_Pin6))
  {
    //ȥ��
    delay();
    if(PTB6_I==0)
    {
      printf("Button1-PTB6 Interrupt!\r\n");
    }
  }
  
  //���PTB7�����ж�
  if(LPLD_GPIO_IsPinxExt(PORTB, GPIO_Pin7))
  {
    //ȥ��
    delay();
    if(PTB7_I==0)
    {
      printf("Button2-PTB7 Interrupt!\r\n");
    }
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
    for(n=0;n<50;n++)
    {
      asm("nop");
    }
  }
}