#include "DEV_OLED.h"
#include "Font_OLED.h"

/****************************************************************************
 - �����������������ݵ�OLED
 - ����˵����data��Ҫ���͵�8λ����
 - ����˵���� 			
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Write_Data(uint8 data)
{
   uint8 i = 8;

   OLED_DC_ON();  // ��������
   OLED_SCL_OFF();
   while (i--)
   {
      // ÿ�η������ݵ����λ
      if (data & 0x80)
      {
         OLED_SDA_ON();
      }
      else
      {
         OLED_SDA_OFF();
      }
      // ʱ�ӵ������ط���
      #if (BUS_CLOCK == 88000000)
      {
         asm("nop");    // 1��
      }
      #endif
      OLED_SCL_ON();
      OLED_SCL_OFF();

      data <<= 1;
   }
}

/****************************************************************************
 - �����������������OLED
 - ����˵����cmd��Ҫ���͵�8λ����
 - ����˵���� 			
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Write_Cmd(uint8 cmd)
{
   uint8 i=8;

   OLED_DC_OFF();    // ��������
   OLED_SCL_OFF();
   while (i--)
   {
      // ÿ�η�����������λ
      if (cmd & 0x80)
      {
         OLED_SDA_ON();
      }
      else
      {
         OLED_SDA_OFF();
      }
      // ʱ�ӵ������ط���
      #if (BUS_CLOCK == 88000000)
      {
         asm("nop");    // 1��
      }
      #endif
      OLED_SCL_ON();
      OLED_SCL_OFF();

      cmd <<= 1;
   }
}

/****************************************************************************
 - ��������������OLED���е�ַ��ҳ��ַ
 - ����˵����columnAddress:�е�ַ
             pageAddress:  ҳ��ַ
 - ����˵���� 			
 - ʾ����
 - �޸ļ�¼��
 - ע�����1��ֻ����ҳ��ַģʽ������
             2���еĵ���λĬ��Ϊ0x00���еĸ���λĬ��Ϊ0x10
****************************************************************************/
static void OLED_Set_Position(uint8 columnAddress, uint8 pageAddress)
{
   OLED_Write_Cmd(0xb0+pageAddress);
   OLED_Write_Cmd((columnAddress&0x0f)|0x00);
   OLED_Write_Cmd(((columnAddress&0xf0)>>4)|0x10);
}

/****************************************************************************
 - ��������������SSD1306�������Ĵ洢����ַģʽ
 - ����˵����mode:
             0:ˮƽ��ַ����ģʽ
             1:��ֱ��ַ����ģʽ
             2:ҳ��ַ����ģʽ
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ�ҳ��ַ����ģʽ
****************************************************************************/
static void OLED_Set_Address_Mode(uint8 mode)
{
   OLED_Write_Cmd(0x20);   // Set Memory Addressing Mode
   OLED_Write_Cmd(mode);   // Default => 0x02
   					         // 0x00 => Horizontal Addressing Mode
   					         // 0x01 => Vertical Addressing Mode
   					         // 0x02 => Page Addressing Mode
}

/****************************************************************************
 - ����������������ʾ����RAM����ʼҳ��ַ����ֹҳ��ַ
 - ����˵����beginPageAddress:��ʼҳ��ַ
             endPageAddress:  ��ֹҳ��ַ
 - ʾ����
 - �޸ļ�¼��
 - ע�����1��Ĭ�ϣ�0->7ҳ
             2��ֻ�������õ�ҳ��ַ֮����ʾ���ݣ�
****************************************************************************/
static void OLED_Set_Page_Address(uint8 beginPageAddress, uint8 endPageAddress)
{
	OLED_Write_Cmd(0x22);               // Set Page Address
	OLED_Write_Cmd(beginPageAddress);   // Default => 0x00 (Page Start Address)
	OLED_Write_Cmd(endPageAddress);	   // Default => 0x07 (Page End Address)
}

/****************************************************************************
 - ����������������ʾ����RAM����ʼ�е�ַ����ֹ�е�ַ
 - ����˵����beginColumnAddress:��ʼ�е�ַ
             endColumnAddress:  ��ֹ�е�ַ
 - ʾ����
 - �޸ļ�¼��
 - ע�����1��Ĭ�ϣ�0->127��
             2��ֻ�������õ��е�ַ֮����ʾ���ݣ�
****************************************************************************/
static void OLED_Set_Column_Address(uint8 beginColumnAddress, uint8 endColumnAddress)
{
	OLED_Write_Cmd(0x21);               // Set Column Address
	OLED_Write_Cmd(beginColumnAddress); // Default => 0x00 (Column Start Address)
	OLED_Write_Cmd(endColumnAddress);   // Default => 0x7F (Column End Address)
}

/****************************************************************************
 - ����������������ʾRAM����ʼ��ַ
 - ����˵����startLine:��ʾRAM�Ŀ�ʼ��ַ
 - ʾ����    d=1:��ʾRAM�ĵ�1��ӳ��COM0
 - �޸ļ�¼��
 - ע�����1:0x00->0x3f(0->63��)
             2:Ĭ�ϣ�0��
****************************************************************************/
static void OLED_Set_Start_Line(uint8 d)
{
	OLED_Write_Cmd(0x40|d);    // Set Display Start Line
						            // Default => 0x40 (0x00)
}

/****************************************************************************
 - ��������������OLED��ʾ�ĶԱȶ�
 - ����˵����contrast:�Աȶȣ�0x00->0xff��
 - ʾ����
 - �޸ļ�¼��
 - ע�����1:0x00->0xff
             2:Ĭ�ϣ�0x7f
             3:�ε�����������ŶԱȶ���ֵ�����������
****************************************************************************/
static void OLED_Set_Contrast(uint8 d)
{
	OLED_Write_Cmd(0x81);      // Set Contrast Control
	OLED_Write_Cmd(d);         // Default => 0x7F
}

/****************************************************************************
 - �������������ô�/�ر�OLED�ĵ�ɱ�
 - ����˵����chargePumpStatus:
             0x00:�رյ�ɱ�
             0x04:�򿪵�ɱ�
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ��رյ�ɱ�
****************************************************************************/
static void OLED_Set_Charge_Pump(uint8 d)
{
	OLED_Write_Cmd(0x8D);   // Set Charge Pump
	OLED_Write_Cmd(0x10|d); // Default => 0x10
						         // 0x10 (0x00) => Disable Charge Pump
						         // 0x14 (0x04) => Enable Charge Pump
}

/****************************************************************************
 - �����������ı���ʾ�����е�ַ���ε�ӳ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Set_Segment_Remap(uint8 d)
{
	OLED_Write_Cmd(0xA0|d);    // Set Segment Re-Map
						            // Default => 0xA0
						            // 0xA0 (0x00) => Column Address 0 Mapped to SEG0
						            // 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

/****************************************************************************
 - �������������ô�/�ر�OLED��������ʾ
 - ����˵����entireDisplayStatus:
             0x00:��ʾGDDRAM�е����ݣ���ͨ��ʾ��
             0x01:ǿ�ƿ�������ʾ������GDDRAM�е�����
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ��ر�������ʾ����ͨ��ʾ��
****************************************************************************/
static void OLED_Set_Entire_Display(uint8 d)
{
	OLED_Write_Cmd(0xA4|d);    // Set Entire Display On / Off
						            // Default => 0xA4
						            // 0xA4 (0x00) => Normal Display
						            // 0xA5 (0x01) => Entire Display On
}

/****************************************************************************
 - ����������������ͨ/������ʾ
 - ����˵����inverseDisplayStatus:
             0x00:RAM��'1'�������ص�Ĵ�������ͨ��ʾ��
             0x01:RAM��'0'�������ص�Ĵ�����������ʾ��
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ���ͨ��ʾ
****************************************************************************/
static void OLED_Set_Inverse_Display(uint8 d)
{
	OLED_Write_Cmd(0xA6|d);    // Set Inverse Display On/Off
						            // Default => 0xA6
						            // 0xA6 (0x00) => Normal Display
						            // 0xA7 (0x01) => Inverse Display On
}

/****************************************************************************
 - ��������������OLED��ʾ��������
 - ����˵����multiplexRatio:16->63
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ�63��0->63���ܹ�64�У�
****************************************************************************/
static void OLED_Set_Multiplex_Ratio(uint8 d)
{
	OLED_Write_Cmd(0xA8);   // Set Multiplex Ratio
	OLED_Write_Cmd(d);      // Default => 0x3F (1/64 Duty)
}

/****************************************************************************
 - �������������ô�/�ر�OLED����ʾ���
 - ����˵����displayStatus:
             0x00:�ر���ʾ
             0x01:����ʾ
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ��ر���ʾ
****************************************************************************/
static void OLED_Set_Display_On_Off(uint8 d)
{
	OLED_Write_Cmd(0xAE|d); // Set Display On/Off
         				      // Default => 0xAE
         					   // 0xAE (0x00) => Display Off
         					   // 0xAF (0x01) => Display On
}

/****************************************************************************
 - ��������������OLED����ʼҳ��ַ
 - ����˵����startPageAddress:0->7
 - ʾ����
 - �޸ļ�¼��
 - ע�����1:Ĭ�ϣ���ʼҳ��ַΪ0
             2:ֻ����ҳ��ַģʽ������
****************************************************************************/
static void OLED_Set_Start_Page_Address(uint8 d)
{
	OLED_Write_Cmd(0xB0|d); // Set Page Start Address for Page Addressing Mode
						         // Default => 0xB0 (0x00)
}

/****************************************************************************
 - ��������������COM�����ɨ�跽��
 - ����˵����startPageAddress:0->7
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ�ɨ�跽��Ϊ��0��->��63��
****************************************************************************/
static void OLED_Set_Common_Remap(uint8 d)
{
	OLED_Write_Cmd(0xC0|d);    // Set COM Output Scan Direction
						            // Default => 0xC0
						            // 0xC0 (0x00) => Scan from COM0 to 63
					            	// 0xC8 (0x08) => Scan from COM63 to 0
}

/****************************************************************************
 - ��������������OLED�е���ʾƫ��������ʾ��ʼ��ӳ�䵽0->63�е�����һ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ���ʾ��ƫ����Ϊ0
****************************************************************************/
static void OLED_Set_Display_Offset(uint8 d)
{
	OLED_Write_Cmd(0xD3);   // Set Display Offset
	OLED_Write_Cmd(d);      // Default => 0x00
}

/****************************************************************************
 - ��������������OLED��ʾʱ�ӵ����ʺ;����Ƶ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Set_Display_Clock(uint8 d)
{
	OLED_Write_Cmd(0xD5);   // Set Display Clock Divide Ratio / Oscillator Frequency
	OLED_Write_Cmd(d);      // Default => 0x80
					            // D[3:0] => Display Clock Divider
					            // D[7:4] => Oscillator Frequency
}

/****************************************************************************
 - ��������������Ԥ������ڵĳ���ʱ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Set_Precharge_Period(uint8 d)
{
	OLED_Write_Cmd(0xD9);   // Set Pre-Charge Period
	OLED_Write_Cmd(d);	   // Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
					         	// D[3:0] => Phase 1 Period in 1~15 Display Clocks
						         // D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

/****************************************************************************
 - ��������������COM�źŹܽ���������ƥ��OLED����Ӳ������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Set_Common_Config(uint8 d)
{
	OLED_Write_Cmd(0xDA);      // Set COM Pins Hardware Configuration
	OLED_Write_Cmd(0x02|d);    // Default => 0x12 (0x10)
						            // Alternative COM Pin Configuration
						            // Disable COM Left/Right Re-Map
}

/****************************************************************************
 - ��������������Vcomh�����������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Set_VCOMH(uint8 d)
{
	OLED_Write_Cmd(0xDB);   // Set VCOMH Deselect Level
	OLED_Write_Cmd(d);      // Default => 0x20 (0.77*VCC)
}

/****************************************************************************
 - ����������OLED�Ŀղ���
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Set_NOP(void)
{
	OLED_Write_Cmd(0xE3);   // Command for No Operation
}

/****************************************************************************
 - ����������OLED�����0/1
 - ����˵����flag:
             0:ȫ��
             1:ȫ��
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_fill(uint8 flag)
{
   uint8 pageAddress=0, columnAddress=0;

   // 1��8ҳȫ�����
   for (pageAddress=0; pageAddress<8; pageAddress++)
   {
      OLED_Write_Cmd(0xb0+pageAddress);   // ����ҳ��ַ
      OLED_Write_Cmd(0x00);               // �����е�ַ
      OLED_Write_Cmd(0x10);
      // �������
      for (columnAddress=0; columnAddress<X_WIDTH; columnAddress++)
      {
         OLED_Write_Data(flag);
      }
   }
}

/****************************************************************************
 - ����������OLED�����0=>����
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_clear(void)
{
	oled_fill(DARK);
}

/****************************************************************************
 - ������������ʼ��OLED
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void init_oled(void)
{
   // �ܽ�����Ϊ���״̬
   OLED_SCL_OUT();
   OLED_SDA_OUT();
   OLED_RST_OUT();
   OLED_DC_OUT();

   OLED_SCL_ON();
   OLED_RST_OFF();
   Delay_1ms(50);
   OLED_RST_ON();

   //���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���
   OLED_Set_Display_On_Off(OLED_DISPLAY_OFF);      // Display Off (0x00/0x01)
   OLED_Set_Display_Clock(0x80);		               // Set Clock as 100 Frames/Sec
   OLED_Set_Multiplex_Ratio(0x3F);		            // 1/64 Duty (0x0F~0x3F)
   OLED_Set_Display_Offset(0x00);		            // Shift Mapping RAM Counter (0x00~0x3F)
   OLED_Set_Start_Line(0x00);			               // Set Mapping RAM Display Start Line (0x00~0x3F)
   OLED_Set_Charge_Pump(OLED_ENABLE_CHARGE_PUMP);  // Enable Embedded DC/DC Converter (0x00/0x04)
   OLED_Set_Address_Mode(OLED_PAGE_ADDRESS_MODE);  // Set Page Addressing Mode (0x00/0x01/0x02)
   OLED_Set_Segment_Remap(0x01);		               // Set SEG/Column Mapping     0x00���ҷ��� 0x01����
   OLED_Set_Common_Remap(0x08);			            // Set COM/Row Scan Direction 0x00���·��� 0x08����
   OLED_Set_Common_Config(0x10);		               // Set Sequential Configuration (0x00/0x10)
   OLED_Set_Contrast(CONTRAST_VALUE);              // Set SEG Output Current
   OLED_Set_Precharge_Period(0xF1);		            // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
   OLED_Set_VCOMH(0x40);			                  // Set VCOM Deselect Level
   OLED_Set_Entire_Display(NORMAL_DISPLAY_MODE);   // Disable Entire Display On (0x00/0x01)
   OLED_Set_Inverse_Display(NORMAL_DISPLAY_MODE);  // Disable Inverse Display On (0x00/0x01)
   OLED_Set_Display_On_Off(OLED_DISPLAY_ON);		   // Display On (0x00/0x01)
   OLED_Fill(0x00);                                // ��ʼ����
   OLED_Set_Position(0, 0);	                     // ����ԭ��
   
   oled_clear();
}

/****************************************************************************
 - ��������������һ����(x,y)
 - ����˵������ʵ����ֵ(x,y),x�ķ�Χ0��127��y�ķ�Χ0��63
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Draw_Pixel(uint8 x, uint8 y)
{
   uint8 data;   // data��ǰ�������

   data = 0x01<<(y%8);                 // ��λ��8λ��������һλ
   OLED_Write_Cmd(0xb0+(y>>3));        // ��λ���ڼ�ҳ
   OLED_Write_Cmd(((x&0xf0)>>4)|0x10); // ��λ���ڼ���
   OLED_Write_Cmd((x&0x0f)|0x00);
   OLED_Write_Data(data);              // �����õ�
}

/****************************************************************************
 - ��������������һ��ʵ�ľ���
 - ����˵�������Ͻ����꣨x1,y1��,���½����꣨x2��y2��
             ����x1��x2�ķ�Χ0��127��y1��y2�ķ�Χ0��63������ʵ����ֵ
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Draw_Rectangle(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 gif)
{
	uint8 n;
		
   OLED_Set_Position(x1, y1>>3); // ��λ���굽��ҳ����
   for (n=x1; n<=x2; n++)
   {
      OLED_Write_Data(0x01<<(y1%8)); 			
      if (gif == 1) 	
      {
         Delay_1ms(50);
      }
   }
   OLED_Set_Position(x1, y2>>3);
   for (n=x1; n<=x2; n++)
   {
      OLED_Write_Data(0x01<<(y2%8)); 			
      if (gif == 1)
      {
         Delay_1ms(5);
      }
   }	
}

/****************************************************************************
 - ������������ʾ6��x8�д�С��ASCII���ַ���
 - ����˵����x��   �е�ַ
             y��   ҳ��ַ
             ch[]����Ҫ��ʾ���ַ���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Print_6x8_String(uint8 x, uint8 y, uint8 ch[])
{
   uint8 c=0, i=0, j=0;    // c����Ҫ��ʾ�ı�����ASCII���е�λ��

   while (ch[j] != '\0')   // �ж��ַ����Ƿ����
   {
      c = ch[j]-32;        // ���ļ������õ�ASCII���Ǵ�������ASCII��ĵ�32λ��ʼ��
      // ��λ����λ��
      if (x > 126)
      {
         x=0;
         y++;
      }
      OLED_Set_Position(x, y);
      // д������
      for (i=0; i<6; i++)
      {
         OLED_Write_Data(Front_6x8[c][i]);
      }
      // Ϊ��ʾ�ַ����е���һ���ַ���׼��
      x += 6;
      j++;
   }
}

/****************************************************************************
 - ������������ʾ8��16�д�С��ASCII���ַ���
 - ����˵����x��   �е�ַ
             y��   ҳ��ַ
             ch[]����Ҫ��ʾ���ַ���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Print_8x16_String(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
   uint8 c=0, i=0, j=0;    // c����Ҫ��ʾ�ı�����ASCII���е�λ��

   while (ch[j] != '\0')   // �ж��ַ����Ƿ����
   {
      c = ch[j] - 32;      // ���ļ������õ�ASCII���Ǵ�������ASCII��ĵ�32λ��ʼ��
      // ��λ����λ��
      if (x > 120)
      {
         x = 0;
         y++;
      }
      OLED_Set_Position(x,y);
      // д������
      for (i=0; i<8; i++)
      {
         if (mode == NORMAL_DISPLAY)
         {
            OLED_Write_Data(Front_8x16[c*16+i]);
         }
         else
         {
            OLED_Write_Data(~Front_8x16[c*16+i]);
         }
      }
      OLED_Set_Position(x,y+1);
      for (i=0; i<8; i++)
      {
         if (mode == NORMAL_DISPLAY)
         {
            OLED_Write_Data(Front_8x16[c*16+i+8]);
         }
         else
         {
            OLED_Write_Data(~Front_8x16[c*16+i+8]);
         }
      }
      // Ϊ��ʾ�ַ����е���һ���ַ���׼��
      x += 8;
      j++;
   }
}

/****************************************************************************
 - ������������ʾ14��x16�д�С�ĺ����ַ���
 - ����˵����x��   �е�ַ
             y��   ҳ��ַ
             ch[]����Ҫ��ʾ���ַ���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void OLED_Print_14x16_String(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
   uint8 wm=0, ii=0;
   uint16 adder = 1;         // ��Ҫ��ʾ�ĺ��ֱ�����Front_14x16[]�е�λ��

   while (ch[ii] != '\0')  // �ж���Ҫ��ʾ���ַ����Ƿ����
   {
      wm = 0;
      adder = 1;
      // ���ң���Ҫ��ʾ�ĺ��ֱ�����Front_14x16_Idx[]����һ�����ֵı������Ӧ
      while (Front_14x16_Idx[wm] > 127)   // ���ҵ�Front_14x16_Idx[]��ĩβ
      {
         if (Front_14x16_Idx[wm] == ch[ii])
         {
            if (Front_14x16_Idx[wm + 1] == ch[ii + 1])
            {
               adder = wm * 14;
               // �����ֽڵı��붼���=>Ѱ�ҵ���Ҫ��ʾ�ĺ��ֱ���=>�˳�����
               break;
            }
         }
         wm += 2;
      }
      // ��λ����λ��
      if (x > 118)
      {
         x=0;
         y++;
      }
      OLED_Set_Position(x, y);

      // ���ҵ�������ʾ��Ӧ�ĺ���
      if (adder != 1)
      {
         OLED_Set_Position(x, y);
         for (wm=0; wm<14; wm++)
         {
            if (mode == NORMAL_DISPLAY)
            {
               OLED_Write_Data(Front_14x16[adder]);
            }
            else
            {
               OLED_Write_Data(~Front_14x16[adder]);
            }
            adder += 1;
         }
         OLED_Set_Position(x, y+1);
         for (wm=0; wm<14; wm++)
         {
            if (mode == NORMAL_DISPLAY)
            {
               OLED_Write_Data(Front_14x16[adder]);
            }
            else
            {
               OLED_Write_Data(~Front_14x16[adder]);
            }
            adder += 1;
         }   		
      }
      // ���Ҳ�����������ʾ�հײ��ҽ�����һ�ֵĲ���
      else
      {
         OLED_Set_Position(x, y);
         for (wm=0; wm<16; wm++)
         {
            OLED_Write_Data(0);
         }
         OLED_Set_Position(x, y+1);
         for (wm=0; wm<16; wm++)
         {   		
            OLED_Write_Data(0);	
         }
      }
      // Ϊ��ʾ�ַ����е���һ���ַ���׼��
      x += 14;
      ii += 2;
   }
}

/****************************************************************************
 - ������������ʾ16�д�С�ĺ��ֺ��ַ��Ļ���ַ���
 - ����˵����x��   �е�ַ
            y��   ҳ��ַ
            ch[]����Ҫ��ʾ���ַ���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_print(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
	uint8 ch2[3];
	uint8 ii = 0;
	
	while (ch[ii] != '\0')
	{
	   // ��Ҫ��ʾ���Ǻ���
		if (ch[ii] > 127)
		{
			ch2[0] = ch[ii];  // ����Ϊ�����ֽ�
	 		ch2[1] = ch[ii+1];
			ch2[2] = '\0';
			OLED_Print_14x16_String(x, y, ch2, mode); // ��ʾ����
			// Ϊ��ʾ�ַ����е���һ���ַ���׼��
			x += 14;
			ii += 2;
		}
		// ��Ҫ��ʾ������ĸ
		else
		{
			ch2[0] = ch[ii];  // ��ĸռһ���ֽ�
			ch2[1] = '\0';
			OLED_Print_8x16_String(x, y, ch2, mode);	// ��ʾ��ĸ
			// Ϊ��ʾ�ַ����е���һ���ַ���׼��
			x += 8;
			ii += 1;
		}
	}
}

/****************************************************************************
 - ������������ʾ128x48��С��ͼƬ
 - ����˵�������128��48��СͼƬ�����������
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Draw_Picture(const uint8 *ptr)
{
   uint8 x=0, y=0;

   for (y=2; y<8; y++)
   {
      OLED_Set_Position(0, y);				
      for (x=0; x<128; x++)
      {
         OLED_Write_Data(*(ptr++));
      }
   }
}

/****************************************************************************
 - ������������ʾռ3��λ�õı���
 - ����˵����x��      �е�ַ
             y��      ҳ��ַ
             display����Ҫ��ʾ�ı���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Print_Uint8_Variable(uint8 x, uint8 y, uint8 display, uint8 mode)
{
   uint8 temp[4];

   temp[0] = display/100+'0';
   temp[1] = display/10%10+'0';
   temp[2] = display%10+'0';
   temp[3] = '\0';

   OLED_Print(x, y, temp, mode);
}

/****************************************************************************
 - ������������ʾռ5��λ�õı���
 - ����˵����x��      �е�ַ
             y��      ҳ��ַ
             display����Ҫ��ʾ�ı���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Print_Uint16_Variable(uint8 x, uint8 y, uint16 display, uint8 mode)
{
   uint8 temp[6];

   temp[0] = display/10000+'0';
   temp[1] = display/1000%10+'0';
   temp[2] = display/100%10+'0';
   temp[3] = display/10%10+'0';
   temp[4] = display%10+'0';
   temp[5] = '\0';

   OLED_Print(x, y, temp, mode);
}

/****************************************************************************
 - ������������ʾռ5��λ�õı���
 - ����˵����x��      �е�ַ
             y��      ҳ��ַ
             display����Ҫ��ʾ�ı���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Print_Int16_Variable(uint8 x, uint8 y, int16 display, uint8 mode)
{
   uint8 temp[7];

   if (display >= 0)
   {
      temp[0] = '+';
   }
   else
   {
      temp[0] = '-';
   }
   temp[1] = display/10000+'0';
   temp[2] = display/1000%10+'0';
   temp[3] = display/100%10+'0';
   temp[4] = display/10%10+'0';
   temp[5] = display%10+'0';
   temp[6] = '\0';

   OLED_Print(x, y, temp, mode);
}

/****************************************************************************
 - ������������ʾ��һλ��С������(00.0)
 - ����˵����x��      �е�ַ
             y��      ҳ��ַ
             display����Ҫ��ʾ�ı���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Print_Float_Variable(uint8 x, uint8 y, float display, uint8 mode)
{
   uint8 temp[5];
   uint16 displayTemp = (uint16)(display*10);

   temp[0] = displayTemp/1000+'0';
   temp[1] = displayTemp/10%10+'0';
   temp[2] = '.';
   temp[3] = displayTemp%10+'0';

   temp[4] = '\0';

   OLED_Print(x, y, temp, mode);
}

/****************************************************************************
 - ������������ʾ16������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Print_Hex(uint8 x, uint8 y, uint8 display, uint8 mode)
{
   uint8 i = 0;
   uint8 temp[2];

   // ��ʾ16���Ƶ�ǰһ����ĸ
   i = (uint8)(display/16);
   if (i < 10)
   {
      temp[0] = i+0x30;
   }
   else
   {
      temp[0] = i+0x37;
   }
   temp[1] = '\0';
   OLED_Print(x, y, temp, mode);

   // ��ʾ16���Ƶĺ�һ����ĸ
   i = (uint8)(display%16);
   if (i < 10)
   {
      temp[0] = i+0x30;
   }
   else
   {
      temp[0] = i+0x37;
   }
   temp[1] = '\0';
   OLED_Print(x+8, y, temp, mode);
}

/****************************************************************************
 - ������������ʾ���Һ��ߵ�ǰ10������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void OLED_Print_Blackline(void)
{
   uint8 i = 0;

   // ��ʾ����ǰ10������
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 0, leftBlackline[i], NORMAL_DISPLAY);
   }
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 2, leftBlackline[5+i], NORMAL_DISPLAY);
   }


   // ��ʾ����ǰ10������
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 4, rightBlackline[i], NORMAL_DISPLAY);
   }
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 6, rightBlackline[5+i], NORMAL_DISPLAY);
   }
}