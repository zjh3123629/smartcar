/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_TestRUSH��-----------------
 * @file LPLD_TestRUSH.c
 * @version 0.1
 * @date 2013-10-22
 * @brief �����������RUSH Kinetis������
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
//����LCD�豸����
#include "DEV_LCD.h"
//����SDRAM�豸����
#include "DEV_SDRAM.h"
//����������
#include "DEV_Touchscreen.h"

//��ƷSN�ų���
#define SN_LEN  6

//Ϊ�򻯴��룬����ͳһ��ɫ�����Ĵ�ӡ����
#define LCD_PRINT_LINE(str) LPLD_LCD_PrintStringLine(str,COLOR_White,COLOR_Blue2)
#define LCD_PRINT(str) LPLD_LCD_PrintString(str,COLOR_White,COLOR_Blue2)

//������Ч����ֵ������ʶ����Ч����
#define PRESS_CNT       (50)
//�����������
#define PAD_X   0
#define PAD_O   1
//TSI��������
void tsi_init(void);
void tsi_isr(void);
//TSI��������
TSI_InitTypeDef tsi_init_struct;
uint8 press_counter[2] = {PRESS_CNT, PRESS_CNT};

//GPIO��������
void init_gpio(void);
void portb_isr(void);
//GPIO��������
GPIO_InitTypeDef gpiob_init_struct;
GPIO_InitTypeDef gpioe_init_struct;

//ADC��������
void adc_init(void);
void delay(uint16);
//ADC��������
ADC_InitTypeDef adc_init_struct;

//ENET��������
ENET_InitTypeDef enet_init_struct;
//����MAC�����ַ����
uint8  gCfgLoca_MAC[] = {0x22, 0x22, 0x22, 0x00, 0x00, 0x01};

//RTC��������
RTC_InitTypeDef rtc_init_struct;

//������ʾ�ַ���
uint8 strBuff[40];
//��Χ�豸��ʼ�����
boolean check_sdcard(void);
boolean check_sdram(void);
boolean check_netport(void);
//�������
uint8 err=0;

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

void main (void)
{
  boolean check_result;
  uint16 color;
  int16 result;
  uint16 X_Positon = 0; //����X�����
  uint16 Y_Positon = 0; //����Y�����

  //��ʼ��RTC
  if(LPLD_RTC_IsRunning() == 0) 
  {  
    rtc_init_struct.RTC_Seconds = 0;
    LPLD_RTC_Init(rtc_init_struct);
  }
  
  //��ʼ��LCD
  LPLD_LCD_Init();
  //��ʼ��LCD����ʱһ��ʱ��
  LPLD_LPTMR_DelayMs(100);
  //��䱳��ɫ
  LPLD_LCD_FillBackground(COLOR_Blue2);
  //��ӡ��������Ϣ
  LCD_PRINT_LINE("******** RUSH Kinetis ********");
  //Ϊ�ַ�����ֵ
  sprintf((int8 *)strBuff, "Core CLK:%dMHZ  Bus CLK:%dMHZ", g_core_clock/1000000u, g_bus_clock/1000000u);
  LCD_PRINT_LINE(strBuff);
  
  check_result = check_sdcard();
  LCD_PRINT_LINE("Check SD card:    ");
  if(check_result)
  {
    LCD_PRINT("[OK!]");
  }
  else
  {
    err++;
    LCD_PRINT("[Error!]");
  }
       
  check_result = check_sdram();
  LCD_PRINT_LINE("Check Ext SDRAM:  ");
  if(check_result)
  {
    LCD_PRINT("[OK!]");
  }
  else
  {
    err++;
    LCD_PRINT("[Error!]");
  }
  
  check_result = check_netport();
  LCD_PRINT_LINE("Check Ether Port: ");
  if(check_result)
  {
    LCD_PRINT("[OK!]");
  }
  else
  {
    err++;
    LCD_PRINT("[Error!]");
  }
  
  //��ʼ�������豸
  tsi_init();
  init_gpio();
  adc_init();
  LPLD_Touchscreen_Init(); 
  
  LCD_PRINT_LINE("Check TouchPad\\Button\\ADC\\TouchScreen:");
  LCD_PRINT_LINE("  TouchPad:");
  LCD_PRINT_LINE("  Button:");
  LCD_PRINT_LINE("  ADC:");
  LCD_PRINT_LINE("  TouchScreen: X-      Y-");

  if(err==0)
  {
    LPLD_LCD_ShowString(220,198,"Test Passed!",COLOR_Green,COLOR_Blue2);
  }
  else
  {
    LPLD_LCD_ShowString(220,198,"Test Failed!",COLOR_Red,COLOR_Blue2);
  }
  
  while(1)
  {
    //��ʾ���ADC�ɼ�ֵ
    result = (int16)LPLD_ADC_Get(ADC0, DAD1); 
    color = result>0?COLOR_Cyan:COLOR_Magenta;
    sprintf((int8 *)strBuff, "%5d", result);
    LPLD_LCD_ShowString(88,162,strBuff,color,COLOR_Blue2);
      
    //��ʾ������XYֵ
    //���LCD IRQ����Ϊ�ʹ����д���
    if(PTE12_I == 0)
    {
      X_Positon=LPLD_Touchscreen_GetResult(LPLD_SER_SAMPLE_X);
      Y_Positon=LPLD_Touchscreen_GetResult(LPLD_SER_SAMPLE_Y);
      sprintf((int8 *)strBuff, "%4d", X_Positon);
      LPLD_LCD_ShowString(144,180,strBuff,COLOR_Magenta,COLOR_Blue2);
      sprintf((int8 *)strBuff, "%4d", Y_Positon);
      LPLD_LCD_ShowString(200,180,strBuff,COLOR_Cyan,COLOR_Blue2);
    }
    
    //��ʾϵͳ����ʱ�� 
    sprintf((int8 *)strBuff, "Run Time:%ds", LPLD_RTC_GetRealTime());
    LPLD_LCD_ShowString(0,218,strBuff,COLOR_Black,COLOR_Blue2);
    
    delay(500);
  } 
}


boolean check_sdcard(void)
{
  // ���±������������FatFs�ļ�ϵͳ��������
  FRESULT rc;			//������� 
  FATFS fatfs;			// �ļ�ϵͳ���� 
  FIL fil;			// �ļ����� 
  UINT br;
  BYTE buff[SN_LEN+4] = "SN:";
  
  // ע��һ�����̹����� 
  f_mount(0, &fatfs);
  
  //��SN�ļ�
  rc = f_open(&fil, "0:/SN", FA_READ);
  if (rc) 
    return FALSE;
  
  //��ӡ���ļ��ڵ�����
  for (;;) 
  {
    rc = f_read(&fil, buff+3, sizeof(buff)-3, &br);	// ��ȡ�ļ���һ�� 
    if (rc || !br) break;			// ������ȡ��� 
    buff[SN_LEN+3] = '\0';
  }
  LCD_PRINT_LINE(buff);
  if (rc)
    return FALSE;
  
  //�ر��ļ�
  rc = f_close(&fil);
  
  if (rc) 
    return FALSE;
  
  return TRUE;
}


boolean check_sdram(void)
{ 
  uint8 *buff;
  //��ʼ��SDRAM
  //������
  //  ��ʼ��FlexBus��FB1ģ�顢256KѰַ�ռ䡢8λ���д��
  LPLD_SDRAM_Init();
  
  //��̬����SDRAM�е�һ�οռ�
  buff = LPLD_SDRAM_Malloc(10);
  
  //������д�붯̬�����SDRAM�ռ�
  for(uint8 i=0; i<10; i++)
  {
    buff[i] = i;
  }  
  
  //��ȡд�뵽SDRAM�е�����
  for(uint8 i=0; i<10; i++)
  {
    if(buff[i] != i)
      return FALSE;
  }
  
  return TRUE;
}


boolean check_netport(void)
{
  uint32 IDR=0;
  uint16 data;
  
  //����������̫������оƬ�Ƿ�����
  //����ֻ��ʼ��MII�ӿ�
 
  //ʹ��ENETʱ��
  SIM->SCGC2 |= SIM_SCGC2_ENET_MASK;
  //��λENET
  ENET->ECR = ENET_ECR_RESET_MASK;
  //��ʼ��MII�ӿ�
  LPLD_ENET_MiiInit(g_bus_clock/1000000/*MHz*/);   
  //ʹ��GPIO���Ÿ��ù���
  PORTB->PCR[0]  = PORT_PCR_MUX(4);  //GPIO;//RMII0_MDIO/MII0_MDIO
  PORTB->PCR[1]  = PORT_PCR_MUX(4);  //GPIO;//RMII0_MDC/MII0_MDC    
  PORTA->PCR[14] = PORT_PCR_MUX(4);  //RMII0_CRS_DV/MII0_RXDV
  PORTA->PCR[12] = PORT_PCR_MUX(4);  //RMII0_RXD1/MII0_RXD1
  PORTA->PCR[13] = PORT_PCR_MUX(4);  //RMII0_RXD0/MII0_RXD0
  PORTA->PCR[15] = PORT_PCR_MUX(4);  //RMII0_TXEN/MII0_TXEN
  PORTA->PCR[16] = PORT_PCR_MUX(4);  //RMII0_TXD0/MII0_TXD0
  PORTA->PCR[17] = PORT_PCR_MUX(4);  //RMII0_TXD1/MII0_TXD1  
  
  //��ȡ����оƬʶ���
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_PHYIDR1, &data );     
  IDR = (uint32)data<<16;
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_PHYIDR2, &data );  
  IDR |= data;
  
  if(IDR == 0x20005C90)
    return TRUE;
  
  return FALSE;
}

/*
 * ��ʼ��TSI
 *
 */
void tsi_init(void)
{
  //����TSI��ʼ������
  tsi_init_struct.TSI_Chs = TSI_Ch7 | TSI_Ch8;  //X��O���������ֱ�Ϊ7��8ͨ��
  tsi_init_struct.TSI_ScanTriggerMode = TSI_SCAN_PERIOD;        //����ɨ��ģʽ
  tsi_init_struct.TSI_IsInitSelfCal = TRUE;     //���ó�ʼ��ʱ��У�鹦��
  tsi_init_struct.TSI_EndScanOrOutRangeInt = TSI_ENDOFDCAN_INT; //ʹ��ɨ������ж�
  tsi_init_struct.TSI_EndScanIsr = tsi_isr;     //�����жϺ���
  //��ʼ��TSI
  LPLD_TSI_Init(tsi_init_struct);
  //ʹ��TSI�ж�
  LPLD_TSI_EnableIrq();
}

/*
 * TSI����ɨ���ж�
 *
 */
void tsi_isr()
{
  uint8 valid_touch = 0;
  
  //�ж�7ͨ���Ƿ񳬹�������ֵ
  if(LPLD_TSI_IsChxTouched(7))
  {
    //������Ч�������Լ�
    press_counter[PAD_X]--;
    //���Լ���0ʱ����ʶ��Ϊ��Ч����
    if(press_counter[PAD_X]==0)
    {
      //��Ч������־��λ
      valid_touch |= (1<<PAD_X);
      //�ָ���Ч��������ֵ
      press_counter[PAD_X] = PRESS_CNT;
    }
  }
  else
  {
    //����ָ���Ч��������ֵ
    press_counter[PAD_X] = PRESS_CNT;
  }
  
  //����ͬ��
  if(LPLD_TSI_IsChxTouched(8))
  {
    press_counter[PAD_O]--;
    if(press_counter[PAD_O]==0)
    {
      valid_touch |= (1<<PAD_O);
      press_counter[PAD_O] = PRESS_CNT;
    }
  }
  else
  {
    press_counter[PAD_O] = PRESS_CNT;
  }
  
  //���X����Ϊ��Ч���������ӡ״̬
  if(valid_touch & (1<<PAD_X))
  {
    LPLD_LCD_ShowString(88,126,"X",COLOR_Magenta,COLOR_Blue2);
  }
  
  //���O����Ϊ��Ч���������ӡ״̬
  if(valid_touch & (1<<PAD_O))
  {
    LPLD_LCD_ShowString(88,126,"O",COLOR_Cyan,COLOR_Blue2);
  }
}


/*
 * ��ʼ�����Ӱ�����GPIO���š�LCD���������ж�����
 *
 */
void init_gpio()
{
  //������ʼ��
  // ���� PTB7��PTB6 ΪGPIO����,����,�ڲ������������ز����ж�
  gpiob_init_struct.GPIO_PTx = PTB;      //PORTB
  gpiob_init_struct.GPIO_Pins = GPIO_Pin6|GPIO_Pin7;     //����6��7
  gpiob_init_struct.GPIO_Dir = DIR_INPUT;        //����
  gpiob_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;     //�ڲ�����|�������ж�
  gpiob_init_struct.GPIO_Isr = portb_isr;        //�жϺ���
  LPLD_GPIO_Init(gpiob_init_struct);
  //ʹ���ж�
  LPLD_GPIO_EnableIrq(gpiob_init_struct);
  
  //LCD�����ж�����
  gpioe_init_struct.GPIO_PTx = PTE;
  gpioe_init_struct.GPIO_Pins = GPIO_Pin12;
  gpioe_init_struct.GPIO_Dir = DIR_INPUT;  
  LPLD_GPIO_Init(gpioe_init_struct);
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
    if(PTB6_I==0)
    {
      LPLD_LCD_ShowString(88,144,"S1-PTB6",COLOR_Magenta,COLOR_Blue2);
    }
  }
  
  //���PTB7�����ж�
  if(LPLD_GPIO_IsPinxExt(PORTB, GPIO_Pin7))
  {
    if(PTB7_I==0)
    {
      LPLD_LCD_ShowString(88,144,"S2-PTB7",COLOR_Cyan,COLOR_Blue2);
    }
  }
}

/*
 * ��ʼ��ADC����ͨ��
 *
 */
void adc_init(void)
{
  //����ADC��������
  adc_init_struct.ADC_Adcx = ADC0;
  adc_init_struct.ADC_DiffMode = ADC_DIFF;      //��ֲɼ�
  adc_init_struct.ADC_BitMode = DIFF_13BIT;     //���13λ����
  adc_init_struct.ADC_SampleTimeCfg = SAMTIME_LONG;    //�̲���ʱ��
  adc_init_struct.ADC_HwAvgSel = HW_32AVG;       //4��Ӳ��ƽ��
  adc_init_struct.ADC_CalEnable = TRUE; //ʹ�ܳ�ʼ��У��
  //��ʼ��ADC
  LPLD_ADC_Init(adc_init_struct);
  //Ϊ�˱�֤���ù��ܲ���ռ�ã����ʹ����ӦADCͨ��
  //RUSH������ĵ�λ��ʹ��DAD1ͨ�����вɼ�
  //���DAD1ͨ��������Ϊ(ADC0_DP1��ADC0_DM1)
  LPLD_ADC_Chn_Enable(ADC0, DAD1); 
}

/*
 * ��ʱ����
 */
void delay(uint16 n)
{
  uint16 i;
  while(n--)
  {
    for(i=0; i<1000; i++)
    {
      asm("nop");
    }
  }
}