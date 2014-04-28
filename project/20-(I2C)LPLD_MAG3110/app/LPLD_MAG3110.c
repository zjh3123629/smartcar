/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_MAG3110��-----------------
 * @file LPLD_MAG3110.c
 * @version 0.2[By LPLD]
 * @date 2013-10-3
 * @brief ����I2Cģ�飬��ȡMAG3110����شŴ�������ֵ��
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
//����MAG3110�豸ͷ�ļ�
#include "DEV_MAG3110.h"

/****************************************
 ˵����
   *��MAG3110��SCL�������ӿ������PTB0����
    ��MAG3110��SDA�������ӿ������PTB1����
    ��MAG3110��VCC��GND�ֱ�ӿ������3V3��GND
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
   *�ڶ�MAG3110���۲����ֵ�ı仯
 ****************************************/

//��������
int16 resultx, resulty, resultz;
uint8 device_id;

void main (void)
{

  //��ʼ��MAG3110�ײ��������Ĵ���
  device_id = LPLD_MAG3110_Init();
  //ͨ���豸ID�ж��豸�Ƿ�ΪMAG3110
  if(device_id == MAG3110_DEV_ID)
  {
    printf("MAG3110 init succeed!\r\n");
    printf("Device ID: 0x%X\r\n", device_id);
  }
  else
  {
    printf("MAG3110 init failed!\r\n");
    printf("Device ID: 0x%X\r\n", device_id);
    while(1);
  }
  
  while(1)
  {  
    resultx = LPLD_MAG3110_GetResult(DR_STATUS_X_READY, MAG3110_OUT_X_MSB);
    resulty = LPLD_MAG3110_GetResult(DR_STATUS_Y_READY, MAG3110_OUT_Y_MSB);
    resultz = LPLD_MAG3110_GetResult(DR_STATUS_Z_READY, MAG3110_OUT_Z_MSB);
    printf("XYZ:\t%d\t%d\t%d\r\n", resultx, resulty, resultz);

    LPLD_LPTMR_DelayMs(100);
  } 
}

