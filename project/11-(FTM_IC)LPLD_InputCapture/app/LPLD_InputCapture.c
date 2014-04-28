/**
 * --------------����"��������K60�ײ��V3"�Ĺ��̣�LPLD_InputCapture��-----------------
 * @file LPLD_InputCapture.c
 * @version 0.1
 * @date 2013-9-29
 * @brief ����FTMģ������벶׽���ܣ�ʵ�����������Ƶ�ʲ�����
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
   *��һ·�����źŽ���PTB0���ţ��������
    ����K60�������ɵ�PWM�źš�
   *����ʹ��FTM0��PTC1����PWM�źţ���˿�
    ֱ�ӽ�PTC1����PTB0�����������Ƶ�ʡ�
   *��MiniUSB�߲���RUSH Kinetis�������USB
    ������������������USB�ӿڡ�
   *ʹ�ô��ڵ������ֲ���������Ϊ115200
   *ʹ�ô��ڵ������ֲ鿴���н����
 ****************************************/

//��������
void ic_init(void);
void ic_isr(void);
void pwm_init(void);
void delay(uint16);
//��������
FTM_InitTypeDef ftm0_init_struct;
FTM_InitTypeDef ftm1_init_struct;
uint32 Freq1;

void main (void)
{
  //����һ·PWM�����Թ����ǲ������벶����
  //PTC1�����Ƶ��Ϊ1000Hz�������޸ĳ�ʼ�������ѹ۲���
  //Ҳ����ע�ʹ˾䣬���һ·PWM��PTB0
  pwm_init();
  
  //��ʼ�����벶����
  ic_init();
  
  while(1)
  {
    printf("Freq = %dHz\r\n", Freq1);
    delay(1000);
  } 
}

/*
 * ��ʼ��FTM0�����벶����
 *
 */
void ic_init(void)
{
  //����FTM0ģ������벶�����
  ftm1_init_struct.FTM_Ftmx = FTM1;      //ʹ��FTM1ͨ��
  ftm1_init_struct.FTM_Mode = FTM_MODE_IC;       //ʹ�����벶��ģʽ
  ftm1_init_struct.FTM_ClkDiv = FTM_CLK_DIV128;  //������Ƶ��Ϊ����ʱ�ӵ�128��Ƶ
  ftm1_init_struct.FTM_Isr = ic_isr;     //�����жϺ���
  //��ʼ��FTM0
  LPLD_FTM_Init(ftm1_init_struct);
  //ʹ�����벶���Ӧͨ��,�����ز�������ж�
  LPLD_FTM_IC_Enable(FTM1, FTM_Ch0, PTB0, CAPTURE_RI);
  
  //ʹ��FTM0�ж�
  LPLD_FTM_EnableIrq(ftm1_init_struct);
}

/*
 * ���벶���ж�
 *
 */
void ic_isr(void)
{
  uint32 cnt;
  //�ж��Ƿ�ΪFTM1��Ch0ͨ�����������ж�
  if(LPLD_FTM_IsCHnF(FTM1, FTM_Ch0))
  {
    //��ȡFTM1��Ch0ͨ������ֵ
    cnt=LPLD_FTM_GetChVal(FTM1, FTM_Ch0);   
    
    //��������Ƶ�ʡ���Ƶϵ��������ֵ��������Ƶ��
    //����Ƶ��=(����Ƶ��/���벶���Ƶ)/����ֵ
    Freq1=(g_bus_clock/LPLD_FTM_GetClkDiv(FTM1))/cnt; 
    
    //���FTM1 COUNTER
    LPLD_FTM_ClearCounter(FTM1);
    //��������жϱ�־
    LPLD_FTM_ClearCHnF(FTM1, FTM_Ch0); 
  }
}


/*
 * ��ʼ��FTM1��PWM�������
 *
 */
void pwm_init(void)
{
  ftm0_init_struct.FTM_Ftmx = FTM0;	//ʹ��FTM0ͨ��
  ftm0_init_struct.FTM_Mode = FTM_MODE_PWM;	//ʹ��PWMģʽ
  ftm0_init_struct.FTM_PwmFreq = 1000;	//PWMƵ��1000Hz
  
  LPLD_FTM_Init(ftm0_init_struct);
  
  LPLD_FTM_PWM_Enable(FTM0, //ʹ��FTM0
                      FTM_Ch0, //ʹ��Ch0ͨ��
                      5000,     //ռ�ձ�50.00%
                      PTC1, //ʹ��Ch0ͨ����PTC1����
                      ALIGN_LEFT        //���������
                      ); 
}

/*
 * ��ʱ����
 */
void delay(uint16 n)
{
  uint16 i;
  while(n--)
  {
    for(i=0; i<5000; i++)
    {
      asm("nop");
    }
  }
}
