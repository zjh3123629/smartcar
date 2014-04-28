/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_FatFs��-----------------
 * @file LPLD_FatFs.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����SDHC+FatFs�ļ�ϵͳ����SD���ϵ��ļ����ж�д��
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
   *��MicroSD�����뵽K60���İ��SD����ۡ�
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н��
   *������д��󣬽�����PC���ȸ�ʽ��SD����
    ���뵽���İ��ϡ����߸���SDHC����������
 ****************************************/

// ��ӡ�ļ����ش���
void die(FRESULT rc)
{
  printf("������� rc=%u.\n", rc);
  for (;;) ;
}
// �û��Զ����ΪFatFsϵͳ�ṩʵʱʱ��ĺ���
DWORD get_fattime (void)
{
  return ((DWORD)(2013 - 1980) << 25)	//2013��
       | ((DWORD)3 << 21)               //3��
       | ((DWORD)15 << 16)              //15��
       | ((DWORD)0 << 11)
       | ((DWORD)0 << 5)
       | ((DWORD)0 >> 1);
}

/********************************************************************/
void main (void)
{
  uint16 i;
  // ���±������������FatFs�ļ�ϵͳ��������
  FRESULT rc;			//������� 
  FATFS fatfs;			// �ļ�ϵͳ���� 
  FIL fil;			// �ļ����� 
  UINT bw, br;
  BYTE buff[128];
  
  // ע��һ�����̹����� 
  f_mount(0, &fatfs);		
  //����һ���µ�txt�ĵ�
  printf("�½�һ���ļ� (LPLD_FatFs.TXT).\n");
  rc = f_open(&fil, "0:/LPLD_FatFs.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  //���´������ĵ���д��"Hello LPLD!"������
  printf("д���ı�����. (Hello LPLD!)\n");
  rc = f_write(&fil, "Hello LPLD!\r\n", 13, &bw);
  if (rc) die(rc);
  printf("��д�� %u Bytes.\n", bw);
  
  //�ر��½����ļ�
  printf("�ر��ļ�.\n\n");
  rc = f_close(&fil);
  if (rc) die(rc);
  
  //�򿪸ղ��½����ļ�
  printf("��һ���ļ� (LPLD_FatFs.TXT).\n");
  rc = f_open(&fil, "0:/LPLD_FatFs.TXT", FA_READ);
  if (rc) die(rc);
  
  //��ӡ���ļ��ڵ�����
  printf("��ӡ���ļ�����.\n");
  for (;;) 
  {
    rc = f_read(&fil, buff, sizeof(buff), &br);	// ��ȡ�ļ���һ�� 
    if (rc || !br) break;			// ������ȡ��� 
    for (i = 0; i < br; i++)		        // �����ȡ���ֽ����� 
      LPLD_UART_PutChar(TERM_PORT, buff[i]);
  }
  if (rc) die(rc);
  
  //�ر��ļ�
  printf("\n�ر��ļ�.\n");
  rc = f_close(&fil);
  if (rc) die(rc);
  
  printf("�ļ�ϵͳ�������.\n");

  for (;;) 
  {
  }
  
}
