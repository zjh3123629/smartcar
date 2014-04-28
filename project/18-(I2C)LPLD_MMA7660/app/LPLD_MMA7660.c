/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_MMA7660��-----------------
 * @file LPLD_MMA7660.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����I2Cģ�飬��ȡMMA7660������ٶȴ�������ֵ��
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
//����MMA7660�豸ͷ�ļ�
#include "DEV_MMA7660.h"

/****************************************
 ˵����
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
   *�ڶ�RUSH���������۲���ٶ����ֵ�ı仯
 ****************************************/

//��������
int8 resultx, resulty, resultz;

void main (void)
{

  //��ʼ��MMA7660�ײ��������Ĵ���
  LPLD_MMA7660_Init();

  while(1)
  {
    resultx = LPLD_MMA7660_GetResult(MMA7660_XOUT);    
    resulty = LPLD_MMA7660_GetResult(MMA7660_YOUT);  
    resultz = LPLD_MMA7660_GetResult(MMA7660_ZOUT);
    printf("XYZ:\t%d\t%d\t%d\r\n", resultx, resulty, resultz);

    LPLD_LPTMR_DelayMs(100);
  } 
}

