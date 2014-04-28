/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_Flash��-----------------
 * @file LPLD_Flash.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����Flashģ�飬ʵ��Ƭ��Flash�����ݶ�д��
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
   *ʹ�ô��ڵ������ֲ鿴���н��
 ****************************************/

#define FLASH_TEST_SECTOR   (127)
#define FLASH_TEST_ADDR     (FLASH_TEST_SECTOR*2048)// FLASH_TEST_SECTOR*(2048)
#define DATA_SIZE           (10)

//��������
uint8 read_buffer[DATA_SIZE];  //�����������
uint8 write_buffer[DATA_SIZE]; //����д������

void delay(void);

void main (void)
{
  uint8 read;
  uint8 *ptr;
  uint8 result=NULL;
  int len;
  
  LPLD_Flash_Init();
  
  printf("-------FLASH����д���������-------\r\n");
  printf(" E������%d���������ݡ�\r\n", FLASH_TEST_SECTOR);
  printf(" R����ȡ%d����������(10�ֽ�)��\r\n", FLASH_TEST_SECTOR);
  printf(" W��д��%d�����������10�ֽڣ���\r\n", FLASH_TEST_SECTOR);
  
  while(1)
  { 
    read = LPLD_UART_GetChar(UART5);
    
    switch(read)
    {
      //��ִ�в�������
      case 'E':
      case 'e':  
        
        DisableInterrupts;  
        result=LPLD_Flash_SectorErase(FLASH_TEST_ADDR);
        EnableInterrupts;
        delay();
        
        if(result==FLASH_OK)
        {
          printf("�����ɹ���\r\n");
        }
        else
        {
          printf("����ʧ�ܣ��������:%X��\r\n", result);
        }
        break;
        
      //��ִ��д����� 
      case 'W':
      case 'w':
        
        len=0;
        
        printf("������10���ַ���\r\n");
        
        while(len < DATA_SIZE)
        {
          write_buffer[len++] = LPLD_UART_GetChar(UART5); 
        }
      
        DisableInterrupts;  
        result=LPLD_Flash_ByteProgram((uint32)FLASH_TEST_ADDR, (uint32*)write_buffer, DATA_SIZE);
        EnableInterrupts;
        delay();
        
        if(result==FLASH_OK)
        {
          printf("д��ɹ���\r\n");
        }
        else
        {
          printf("д��ʧ�ܣ��������:%X��\r\n", result);
        }
        break;
      
      //���ִ�ж�ȡ���� 
      case 'R':
      case 'r':
        
        ptr = (uint8*)FLASH_TEST_ADDR;
        
        for( len = 0 ; len < DATA_SIZE ; len++)
        {
            read_buffer[len] = *(ptr + len);
        }
        
        printf("��ȡ���ݣ�\r\n");
        
        LPLD_UART_PutCharArr(UART5, (int8 *)read_buffer, DATA_SIZE);
        
        printf("\r\n��ȡ�ɹ���\r\n");  
        break;  
      default:break;
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
    for(n=0;n<200;n++)
    {
      asm("nop");
    }
  }
}
