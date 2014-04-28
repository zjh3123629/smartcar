/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_VirtualMouse��-----------------
 * @file LPLD_VirtualMouse.c
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

/*****************************************************
 * ˵��: 
 * ʹ��HID Mouseʱ��Ҫ��K60_Card��
   �Ƚ�USB_DEVICE_CLASS����Ϊ USB_DEVICE_CLASS_HID
 * ��MiniUSB�߲���RUSH Kinetis������Card�ϵ�USB
   ������������������USB�ӿڡ�
 * ���¿������ϵ�S1��S2������������ƶ���
 ****************************************************/
#include "common.h"
#include "HW_USB.h" 
#include "HW_GPIO.h"
#include "mouse_button.h"
   
GPIO_InitTypeDef Key_left;
GPIO_InitTypeDef Key_right;
   
uint8 Mouse[4] = {0};

void key_isr(void);

void main (void)
{
  Key_left.GPIO_PTx  = PTB;
  Key_left.GPIO_Pins = GPIO_Pin6;
  Key_left.GPIO_PinControl = INPUT_PULL_UP | IRQC_FA;
  Key_left.GPIO_Dir  = DIR_INPUT;
  Key_left.GPIO_Isr  = key_isr;
  
  Key_right.GPIO_PTx  = PTB;
  Key_right.GPIO_Pins = GPIO_Pin7;
  Key_right.GPIO_PinControl = INPUT_PULL_UP | IRQC_FA;
  Key_right.GPIO_Dir  = DIR_INPUT;
  Key_right.GPIO_Isr  = key_isr;
  
  LPLD_GPIO_Init(Key_left); 
  LPLD_GPIO_Init(Key_right); 
  LPLD_GPIO_EnableIrq(Key_left);
  
  LPLD_USB_Init();
  
  while(1)
  {
    LPLD_USB_HID_LoopTask(Mouse);   
  } 
}

void key_isr(void)
{       
  if(LPLD_GPIO_IsPinxExt(PORTB,GPIO_Pin6))
  {
    Mouse[MOUSE_BUTTON_CLICK] = MOUSE_LEFT_CLICK; //������
    //Mouse[MOUSE_X_MOVEMENT] = MOUSE_LEFT_MOVE;  //�������
    //Mouse[MOUSE_Y_MOVEMENT] = MOUSE_UP_MOVE;    //�������
    
  }
  else if(LPLD_GPIO_IsPinxExt(PORTB,GPIO_Pin7))
  {
    Mouse[MOUSE_BUTTON_CLICK] = MOUSE_RIGHT_CLICK;//����Ҽ�
    //Mouse[MOUSE_X_MOVEMENT] = MOUSE_RIGHT_MOVE; //�������
    //Mouse[MOUSE_Y_MOVEMENT] = MOUSE_DOWN_MOVE;  //�������
  }
}

