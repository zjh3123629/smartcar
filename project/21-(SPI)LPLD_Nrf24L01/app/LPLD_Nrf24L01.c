/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_Nrf24L01��-----------------
 * @file LPLD_Nrf24L01.c
 * @version 0.2
 * @date 2014-2-10
 * @brief ����SPIģ�飬ͨ��Nrf24L01����ģ����������շ���
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
#include "DEV_Nrf24L01.h"

/********************************************
 * ˵��: 
 * Ӳ������˵��:
 * K60��Ƭ������        NRF24L01����
 * ����S1 -PTB6
 *     INT    -PTC1  -----> IRQ
 *     CE     -PTB0  -----> CE
 *     CS     -PTA14 -----> CSN
 *     SCK    -PTA15 -----> SCK
 *     MOSI   -PTA16 -----> MOSI
 *     MISO   -PTA17 <----- MISO
 *
 * ���Ͷˣ�ͨ����������NRF24L01����ָ��
 * ���նˣ�ͨ��PTC1�жϣ���������
 * ��MiniUSB�߲���RUSH Kinetis�������USB
   ������������������USB�ӿڡ�
 * ʹ�ô��ڵ������ֲ���������Ϊ115200
 * ʹ�ô��ڵ������ֲ鿴���н����
 * ͨ���޸�NRF24L01_WORKMODE�ı䷢�ͺͽ��շ�ʽ
 ********************************************/

//ѡ����뷽ʽ ������ǰ������NRF24L01�Ĺ�����ʽ
#define NRF24L01_RX_WORKMODE      (0) //���ͳ���
#define NRF24L01_TX_WORKMODE      (1) //���ճ���
#define NRF24L01_WORKMODE         NRF24L01_TX_WORKMODE 

uint8 rx_buf[NRF24L01_PLOAD_LEN] = {0x00};     //���ջ�����
uint8 tx_buf[NRF24L01_PLOAD_LEN] = {0x00};     //���ͻ�����

uint8 Flag_Smitte = 0; //���ͱ�־��
GPIO_InitTypeDef gpio_init_struct;
//�жϺ�������
void portc_handle(void);
void portb_handle(void);

void main (void)
{
  int i; 
  LPLD_Nrf24L01_Init();
#if NRF24L01_WORKMODE == NRF24L01_TX_WORKMODE 
  gpio_init_struct.GPIO_PTx = PTB;        //PORTB
  gpio_init_struct.GPIO_Pins = GPIO_Pin6; //����6
  gpio_init_struct.GPIO_Dir = DIR_INPUT;  //����
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;  //�ڲ�����|�½����ж�
  gpio_init_struct.GPIO_Isr = portb_handle;        //�жϺ���
  
  LPLD_GPIO_Init(gpio_init_struct);
  LPLD_GPIO_EnableIrq(gpio_init_struct); //�ڲ�����,ʹ�ܿ������ϵİ��� S1 PORTB6
  LPLD_Nrf24L01_TxModeInit();
#else
  gpio_init_struct.GPIO_PTx = PTC;        //PORTC
  gpio_init_struct.GPIO_Pins = GPIO_Pin1; //����1
  gpio_init_struct.GPIO_Dir = DIR_INPUT;  //����
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_DOWN|IRQC_FA;  //�ڲ�����|�½����ж�
  gpio_init_struct.GPIO_Isr = portc_handle;      //�жϺ���
    
  LPLD_GPIO_Init(gpio_init_struct);
  LPLD_GPIO_EnableIrq(gpio_init_struct); //�ڲ�����,ʹ��PORTC1��ΪNRF24L01��IRQ�ж�
  LPLD_Nrf24L01_RxModeInit();
#endif
   
  while(1)
  {
#if NRF24L01_WORKMODE == NRF24L01_TX_WORKMODE
    if(Flag_Smitte)
    {
      for(i = 0 ;i <32 ;i++)//���÷��͵�32���ֽ�����
      {
        tx_buf[i] = i;
      }
      if(LPLD_Nrf24L01_SendFrame(tx_buf,NRF24L01_PLOAD_LEN))
      {
        printf("Nrf24l01 Send Succeed!!\r\n");
      }
      else
      {
        printf("Nrf24l01 Send Error!!\r\n");
      }
      Flag_Smitte = 0;
    }
#endif
    
  }
}

#if NRF24L01_WORKMODE == NRF24L01_TX_WORKMODE
//�����ж�
void portb_handle()
{
  Flag_Smitte = 1; //���÷��ͱ�־
}
#endif

#if NRF24L01_WORKMODE == NRF24L01_RX_WORKMODE
//nrf24l01�����ж�
void portc_handle()
{  
  printf("Nrf24L01 rev Succeed!!\r\n"); 
  LPLD_Nrf24L01_RecvFrame(rx_buf, NRF24L01_PLOAD_LEN);
  LPLD_UART_PutCharArr(UART5, (char*)rx_buf, NRF24L01_PLOAD_LEN);//ͨ������5��ӡ���ֵ
  printf("\r\n");
}
#endif
/********************************************************************/
