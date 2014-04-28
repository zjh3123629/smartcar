/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_MMA8451��-----------------
 * @file LPLD_MMA8451.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����I2Cģ�飬��ȡMMA8451������ٶȴ�������ֵ��
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
//����MMA8451�豸ͷ�ļ�
#include "DEV_MMA8451.h"

/****************************************
 ˵����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
   *�ڶ�RUSH������/MMA8451���۲���ٶ����ֵ�ı仯
 ****************************************/

//��������
int16 resultx, resulty, resultz;
uint8 device_id;

void main (void)
{

  //��ʼ��MMA8451�ײ��������Ĵ���
  device_id = LPLD_MMA8451_Init();
  //ͨ���豸ID�ж��豸�Ƿ�ΪMMA8451
  if(device_id == MMA8451_DEV_ID)
  {
    printf("MMA8451 init succeed!\r\n");
    printf("Device ID: 0x%X\r\n", device_id);
  }
  else
  {
    printf("MMA8451 init failed!\r\n");
    printf("Device ID: 0x%X\r\n", device_id);
    while(1);
  }
  
  while(1)
  {  
    resultx = LPLD_MMA8451_GetResult(MMA8451_STATUS_X_READY, MMA8451_REG_OUTX_MSB);
    resulty = LPLD_MMA8451_GetResult(MMA8451_STATUS_Y_READY, MMA8451_REG_OUTY_MSB);
    resultz = LPLD_MMA8451_GetResult(MMA8451_STATUS_X_READY, MMA8451_REG_OUTZ_MSB);
    printf("XYZ:\t%d\t%d\t%d\r\n", resultx, resulty, resultz);

    LPLD_LPTMR_DelayMs(100);
  } 
}

