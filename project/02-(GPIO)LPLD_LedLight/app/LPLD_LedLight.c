/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_LedLight��-----------------
 * @file LPLD_LedLight.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����GPIOģ�飬����LEDС�Ƶ�����
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
   *ͨ���޸�CARD�궨����Ӧ��ͬ���İ�
 ****************************************/

//��ʹ����������K60 Card��Ϊ1����ʹ��K60 Nano��Ϊ0
#define CARD  1   

//��������
void init_gpio(void);
void delay(void);
//��������
GPIO_InitTypeDef gpio_init_struct;

void main (void)
{
  int i;

  //��ʼ�� GPIO
  init_gpio();
  
#if(CARD) 
  i=8;
#else
  i=4;
#endif
  
  while(1)
  {
#if(CARD)
    //D1��D8���δ���������Ϩ��
    LPLD_GPIO_Toggle_b(PTD, i);
    i+=1;
    if(i==16)
       i=8;
#else
    //D1��D4���δ���������Ϩ��
    LPLD_GPIO_Toggle_b(PTA, i);
    i+=2;
    if(i==12)
       i=4;
#endif
    delay();
  }
}

/*
 * ��ʼ������LED�Ƶ�GPIO����
 *
 */
void init_gpio()
{
  
#if(CARD)
  // ���� PTD8~PTD15 ΪGPIO����,���,�ߵ�ƽ�������ж�
  gpio_init_struct.GPIO_PTx = PTD;
  gpio_init_struct.GPIO_Pins = GPIO_Pin8_15;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
#else
  gpio_init_struct.GPIO_PTx = PTA;
  gpio_init_struct.GPIO_Pins = GPIO_Pin4|GPIO_Pin6|GPIO_Pin8|GPIO_Pin10;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
#endif
  
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

