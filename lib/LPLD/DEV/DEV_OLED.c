#include "DEV_oled.h"
#include "Font_oled.h"

/****************************************************************************
 - �����������������ݵ�oled
 - ����˵����data��Ҫ���͵�8λ����
 - ����˵���� 			
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_write_data(uint8 data)
{
	uint8 i = 8;

	oled_dc_on();  // ��������
	
	while (i--) {
		// ÿ�η������ݵ����λ
		if (data & 0x80)
			oled_d1_on();
		else
			oled_d1_off();
		
		//asm("nop");	// ���ʵ�����ʱ
		
		// ʱ�ӵ������ط���
		oled_d0_off();
		oled_d0_on();

		data <<= 1;
	}
	
	oled_d0_off();
}

/****************************************************************************
 - �����������������oled
 - ����˵����cmd��Ҫ���͵�8λ����
 - ����˵���� 			
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_write_cmd(uint8 cmd)
{
	uint8 i = 8;

	oled_dc_off();    // ��������
	
	while (i--) {
		// ÿ�η�����������λ
		if (cmd & 0x80)
			oled_d1_on();
		else
			oled_d1_off();

		//asm("nop");	// ���ʵ�����ʱ

		// ʱ�ӵ������ط���
		oled_d0_off();
		oled_d0_on();

		cmd <<= 1;
	}
	
	oled_d0_off();
}

/****************************************************************************
 - ��������������oled���е�ַ��ҳ��ַ
 - ����˵����columnAddress:�е�ַ
             pageAddress:  ҳ��ַ
 - ����˵���� 			
 - ʾ����
 - �޸ļ�¼��
 - ע�����1��ֻ����ҳ��ַģʽ������
             2���еĵ���λĬ��Ϊ0x00���еĸ���λĬ��Ϊ0x10
****************************************************************************/
static void oled_set_position(uint8 columnAddress, uint8 pageAddress)
{
   oled_write_cmd(0xb0+pageAddress);
   oled_write_cmd((columnAddress&0x0f)|0x00);
   oled_write_cmd(((columnAddress&0xf0)>>4)|0x10);
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
static void oled_set_address_mode(uint8 mode)
{
   oled_write_cmd(0x20);   // set Memory Addressing Mode
   oled_write_cmd(mode);   // Default => 0x02
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
static void oled_set_page_address(uint8 beginPageAddress, uint8 endPageAddress)
{
	oled_write_cmd(0x22);               // set Page Address
	oled_write_cmd(beginPageAddress);   // Default => 0x00 (Page start Address)
	oled_write_cmd(endPageAddress);	   // Default => 0x07 (Page End Address)
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
static void oled_set_column_address(uint8 beginColumnAddress, uint8 endColumnAddress)
{
	oled_write_cmd(0x21);               // set Column Address
	oled_write_cmd(beginColumnAddress); // Default => 0x00 (Column start Address)
	oled_write_cmd(endColumnAddress);   // Default => 0x7F (Column End Address)
}

/****************************************************************************
 - ����������������ʾRAM����ʼ��ַ
 - ����˵����startline:��ʾRAM�Ŀ�ʼ��ַ
 - ʾ����    d=1:��ʾRAM�ĵ�1��ӳ��COM0
 - �޸ļ�¼��
 - ע�����1:0x00->0x3f(0->63��)
             2:Ĭ�ϣ�0��
****************************************************************************/
static void oled_set_start_line(uint8 d)
{
	oled_write_cmd(0x40|d);    // set display start line
						            // Default => 0x40 (0x00)
}

/****************************************************************************
 - ��������������oled��ʾ�ĶԱȶ�
 - ����˵����contrast:�Աȶȣ�0x00->0xff��
 - ʾ����
 - �޸ļ�¼��
 - ע�����1:0x00->0xff
             2:Ĭ�ϣ�0x7f
             3:�ε�����������ŶԱȶ���ֵ�����������
****************************************************************************/
static void oled_set_contrast(uint8 d)
{
	oled_write_cmd(0x81);      // set contrast Control
	oled_write_cmd(d);         // Default => 0x7F
}

/****************************************************************************
 - �������������ô�/�ر�oled�ĵ�ɱ�
 - ����˵����chargePumpStatus:
             0x00:�رյ�ɱ�
             0x04:�򿪵�ɱ�
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ��رյ�ɱ�
****************************************************************************/
static void oled_set_charge_pump(uint8 d)
{
	oled_write_cmd(0x8D);   // set Charge Pump
	oled_write_cmd(0x10|d); // Default => 0x10
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
static void oled_set_segment_remap(uint8 d)
{
	oled_write_cmd(0xA0|d);    // set Segment Re-Map
						            // Default => 0xA0
						            // 0xA0 (0x00) => Column Address 0 Mapped to SEG0
						            // 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

/****************************************************************************
 - �������������ô�/�ر�oled��������ʾ
 - ����˵����entiredisplayStatus:
             0x00:��ʾGDDRAM�е����ݣ���ͨ��ʾ��
             0x01:ǿ�ƿ�������ʾ������GDDRAM�е�����
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ��ر�������ʾ����ͨ��ʾ��
****************************************************************************/
static void oled_set_entire_display(uint8 d)
{
	oled_write_cmd(0xA4|d);    // set Entire display On / Off
						            // Default => 0xA4
						            // 0xA4 (0x00) => Normal display
						            // 0xA5 (0x01) => Entire display On
}

/****************************************************************************
 - ����������������ͨ/������ʾ
 - ����˵����inversedisplayStatus:
             0x00:RAM��'1'�������ص�Ĵ�������ͨ��ʾ��
             0x01:RAM��'0'�������ص�Ĵ�����������ʾ��
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ���ͨ��ʾ
****************************************************************************/
static void oled_set_inverse_display(uint8 d)
{
	oled_write_cmd(0xA6|d);    // set Inverse display On/Off
						            // Default => 0xA6
						            // 0xA6 (0x00) => Normal display
						            // 0xA7 (0x01) => Inverse display On
}

/****************************************************************************
 - ��������������oled��ʾ��������
 - ����˵����multiplexRatio:16->63
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ�63��0->63���ܹ�64�У�
****************************************************************************/
static void oled_set_multiplex_ratio(uint8 d)
{
	oled_write_cmd(0xA8);   // set Multiplex Ratio
	oled_write_cmd(d);      // Default => 0x3F (1/64 Duty)
}

/****************************************************************************
 - �������������ô�/�ر�oled����ʾ���
 - ����˵����displayStatus:
             0x00:�ر���ʾ
             0x01:����ʾ
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ��ر���ʾ
****************************************************************************/
static void oled_set_display_on(uint8 d)
{
	oled_write_cmd(0xAE|d); // set display On/Off
         				      // Default => 0xAE
         					   // 0xAE (0x00) => display Off
         					   // 0xAF (0x01) => display On
}

/****************************************************************************
 - ��������������oled����ʼҳ��ַ
 - ����˵����startPageAddress:0->7
 - ʾ����
 - �޸ļ�¼��
 - ע�����1:Ĭ�ϣ���ʼҳ��ַΪ0
             2:ֻ����ҳ��ַģʽ������
****************************************************************************/
static void oled_set_start_page_address(uint8 d)
{
	oled_write_cmd(0xB0|d); // set Page start Address for Page Addressing Mode
						         // Default => 0xB0 (0x00)
}

/****************************************************************************
 - ��������������COM�����ɨ�跽��
 - ����˵����startPageAddress:0->7
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ�ɨ�跽��Ϊ��0��->��63��
****************************************************************************/
static void oled_set_common_remap(uint8 d)
{
	oled_write_cmd(0xC0|d);    // set COM Output Scan Direction
						            // Default => 0xC0
						            // 0xC0 (0x00) => Scan from COM0 to 63
					            	// 0xC8 (0x08) => Scan from COM63 to 0
}

/****************************************************************************
 - ��������������oled�е���ʾƫ��������ʾ��ʼ��ӳ�䵽0->63�е�����һ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����Ĭ�ϣ���ʾ��ƫ����Ϊ0
****************************************************************************/
static void oled_set_display_offset(uint8 d)
{
	oled_write_cmd(0xD3);   // set display offset
	oled_write_cmd(d);      // Default => 0x00
}

/****************************************************************************
 - ��������������oled��ʾʱ�ӵ����ʺ;����Ƶ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_set_display_clock(uint8 d)
{
	oled_write_cmd(0xD5);   // set display Clock Divide Ratio / Oscillator Frequency
	oled_write_cmd(d);      // Default => 0x80
					            // D[3:0] => display Clock Divider
					            // D[7:4] => Oscillator Frequency
}

/****************************************************************************
 - ��������������Ԥ������ڵĳ���ʱ��
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_set_precharge_period(uint8 d)
{
	oled_write_cmd(0xD9);   // set Pre-Charge Period
	oled_write_cmd(d);	   // Default => 0x22 (2 display Clocks [Phase 2] / 2 display Clocks [Phase 1])
					         	// D[3:0] => Phase 1 Period in 1~15 display Clocks
						         // D[7:4] => Phase 2 Period in 1~15 display Clocks
}

/****************************************************************************
 - ��������������COM�źŹܽ���������ƥ��oled����Ӳ������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_set_common_config(uint8 d)
{
	oled_write_cmd(0xDA);      // set COM Pins Hardware configuration
	oled_write_cmd(0x02|d);    // Default => 0x12 (0x10)
						            // Alternative COM Pin configuration
						            // Disable COM Left/Right Re-Map
}

/****************************************************************************
 - ��������������Vcomh�����������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_set_vcomh(uint8 d)
{
	oled_write_cmd(0xDB);   // set vcomh Deselect Level
	oled_write_cmd(d);      // Default => 0x20 (0.77*VCC)
}

/****************************************************************************
 - ����������oled�Ŀղ���
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
static void oled_set_nop(void)
{
	oled_write_cmd(0xE3);   // Command for No Operation
}

/****************************************************************************
 - ����������oled�����0/1
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
      oled_write_cmd(0xb0+pageAddress);   // ����ҳ��ַ
      oled_write_cmd(0x00);               // �����е�ַ
      oled_write_cmd(0x10);
      // �������
      for (columnAddress=0; columnAddress<X_WIDTH; columnAddress++)
      {
         oled_write_data(flag);
      }
   }
}

/****************************************************************************
 - ����������oled�����0=>����
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
 - ������������ʼ��oled
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void init_oled(void)
{
	// �ܽ�����Ϊ���״̬
	/* Init gpio pin for output */
	init_oled_pin();

	oled_d0_on();
	oled_rst_off();
	delay_ms(50);
	oled_rst_on();

	//���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���
	oled_set_display_on(OLED_DISPLAY_OFF);      // display Off (0x00/0x01)
	oled_set_display_clock(0x80);		       		// set Clock as 100 Frames/Sec
	oled_set_multiplex_ratio(0x3F);		            // 1/64 Duty (0x0F~0x3F)
	oled_set_display_offset(0x00);		            // Shift Mapping RAM Counter (0x00~0x3F)
	oled_set_start_line(0x00);			       		// set Mapping RAM display start line (0x00~0x3F)
	oled_set_charge_pump(OLED_ENABLE_CHARGE_PUMP);	// Enable Embedded DC/DC Converter (0x00/0x04)
	oled_set_address_mode(OLED_PAGE_ADDRESS_MODE);  // set Page Addressing Mode (0x00/0x01/0x02)
	oled_set_segment_remap(0x01);		          	// set SEG/Column Mapping     0x00���ҷ��� 0x01����
	oled_set_common_remap(0x08);			      	// set COM/Row Scan Direction 0x00���·��� 0x08����
	oled_set_common_config(0x10);		        	// set Sequential configuration (0x00/0x10)
	oled_set_contrast(CONTRAST_VALUE);              // set SEG Output Current
	oled_set_precharge_period(0xF1);		      	// set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oled_set_vcomh(0x40);			             	// set VCOM Deselect Level
	oled_set_entire_display(NORMAL_DISPLAY_MODE);   // Disable Entire display On (0x00/0x01)
	oled_set_inverse_display(NORMAL_DISPLAY_MODE);  // Disable Inverse display On (0x00/0x01)
	oled_set_display_on(OLED_DISPLAY_ON);		// display On (0x00/0x01)
	oled_fill(DARK);                                // ��ʼ����
	oled_set_position(0, 0);	                  	// ����ԭ��

	oled_clear();
}

/****************************************************************************
 - ��������������һ����(x,y)
 - ����˵������ʵ����ֵ(x,y),x�ķ�Χ0��127��y�ķ�Χ0��63
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_draw_pixel(uint8 x, uint8 y)
{
   uint8 data;   // data��ǰ�������

   data = 0x01<<(y%8);                 // ��λ��8λ��������һλ
   oled_write_cmd(0xb0+(y>>3));        // ��λ���ڼ�ҳ
   oled_write_cmd(((x&0xf0)>>4)|0x10); // ��λ���ڼ���
   oled_write_cmd((x&0x0f)|0x00);
   oled_write_data(data);              // �����õ�
}

/****************************************************************************
 - ��������������һ��ʵ�ľ���
 - ����˵�������Ͻ����꣨x1,y1��,���½����꣨x2��y2��
             ����x1��x2�ķ�Χ0��127��y1��y2�ķ�Χ0��63������ʵ����ֵ
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_draw_rectangle(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 gif)
{
	uint8 n;
		
	oled_set_position(x1, y1>>3); // ��λ���굽��ҳ����
	for (n=x1; n<=x2; n++) {
		oled_write_data(0x01<<(y1%8)); 			
		if (gif == 1)
			delay_ms(50);
	}
	
	oled_set_position(x1, y2>>3);
	for (n=x1; n<=x2; n++) {
		oled_write_data(0x01<<(y2%8)); 			
		if (gif == 1)
			delay_ms(5);
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
static void oled_print_6x8_string(uint8 x, uint8 y, uint8 ch[])
{
   uint8 c=0, i=0, j=0;    // c����Ҫ��ʾ�ı�����ASCII���е�λ��

   while (ch[j] != '\0')   // �ж��ַ����Ƿ����
   {
      c = ch[j]-32;        // ���ļ������õ�ASCII���Ǵ�������ASCII��ĵ�32λ��ʼ��
      
	  // ���¶�λ����λ��
      if (x > 126) {
         x = 0;
         y++;
      }
      oled_set_position(x, y);
      // д������
      for (i=0; i<6; i++)
      {
         oled_write_data(Front_6x8[c][i]);
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
static void oled_print_8x16_string(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
#define FONT8x16_WIDTH	8
   uint8 c=0, i=0, j=0;    // c����Ҫ��ʾ�ı�����ASCII���е�λ��

   while (ch[j] != '\0')   // �ж��ַ����Ƿ����
   {
      c = ch[j] - 32;      // ���ļ������õ�ASCII���Ǵ�������ASCII��ĵ�32λ��ʼ��
      
	  /* ���ݳ���һ����Ҫд����һ��ʱ��������Ҫ���¶�λ */
      if (x > (X_WIDTH-FONT8x16_WIDTH)) {
         x = 0;
         y += 2;
      }
      oled_set_position(x, y);
      // д������
      for (i=0; i<8; i++)
      {
         if (mode == NORMAL_DISPLAY)
         {
            oled_write_data(Front_8x16[c*16+i]);
         }
         else
         {
            oled_write_data(~Front_8x16[c*16+i]);
         }
      }

      oled_set_position(x, y+1);
      for (i=0; i<8; i++)
      {
         if (mode == NORMAL_DISPLAY)
         {
            oled_write_data(Front_8x16[c*16+i+8]);
         }
         else
         {
            oled_write_data(~Front_8x16[c*16+i+8]);
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
static void oled_print_14x16_string(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
#define FONT14x16_WIDTH		14
   uint8 wm=0, ii=0;
   uint16 addr = 1;         // ��Ҫ��ʾ�ĺ��ֱ�����Front_14x16[]�е�λ��

   while (ch[ii] != '\0')  // �ж���Ҫ��ʾ���ַ����Ƿ����
   {
      wm = 0;
      addr = 1;
      // ���ң���Ҫ��ʾ�ĺ��ֱ�����Front_14x16_Idx[]����һ�����ֵı������Ӧ
      while (Front_14x16_Idx[wm] > 127)   // ���ҵ�Front_14x16_Idx[]��ĩβ
      {
         if (Front_14x16_Idx[wm] == ch[ii])
         {
            if (Front_14x16_Idx[wm + 1] == ch[ii + 1])
            {
               addr = wm * 14;
               // �����ֽڵı��붼���=>Ѱ�ҵ���Ҫ��ʾ�ĺ��ֱ���=>�˳�����
               break;
            }
         }
         wm += 2;
      }
      // ��λ����λ��
      if (x > (X_WIDTH-FONT14x16_WIDTH)) {
         x = 0;
         y += 2;
      }
      oled_set_position(x, y);

      // ���ҵ�������ʾ��Ӧ�ĺ���
      if (addr != 1)
      {
         oled_set_position(x, y);
         for (wm=0; wm<14; wm++)
         {
            if (mode == NORMAL_DISPLAY)
            {
               oled_write_data(Front_14x16[addr]);
            }
            else
            {
               oled_write_data(~Front_14x16[addr]);
            }
            addr += 1;
         }
         oled_set_position(x, y+1);
         for (wm=0; wm<14; wm++)
         {
            if (mode == NORMAL_DISPLAY)
            {
               oled_write_data(Front_14x16[addr]);
            }
            else
            {
               oled_write_data(~Front_14x16[addr]);
            }
            addr += 1;
         }   		
      }
      // ���Ҳ�����������ʾ�հײ��ҽ�����һ�ֵĲ���
      else
      {
         oled_set_position(x, y);
         for (wm=0; wm<16; wm++)
         {
            oled_write_data(0);
         }
         oled_set_position(x, y+1);
         for (wm=0; wm<16; wm++)
         {   		
            oled_write_data(0);	
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
	
	while (ch[ii] != '\0') {
	   // ��Ҫ��ʾ���Ǻ���
		if (ch[ii] > 127) {
			ch2[0] = ch[ii];  // ����Ϊ�����ֽ�
	 		ch2[1] = ch[ii+1];
			ch2[2] = '\0';
			oled_print_14x16_string(x, y, ch2, mode); // ��ʾ����
			// Ϊ��ʾ�ַ����е���һ���ַ���׼��
			x += 14;
			ii += 2;
		}
		// ��Ҫ��ʾ������ĸ
		else {
			ch2[0] = ch[ii];  // ��ĸռһ���ֽ�
			ch2[1] = '\0';
			oled_print_8x16_string(x, y, ch2, mode);	// ��ʾ��ĸ
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
void oled_draw_picture(const uint8 *ptr)
{
   uint8 x=0, y=0;

   for (y=2; y<8; y++)
   {
      oled_set_position(0, y);				
      for (x=0; x<128; x++)
      {
         oled_write_data(*(ptr++));
      }
   }
}

#if 0
/****************************************************************************
 - ������������ʾռ3��λ�õı���
 - ����˵����x��      �е�ַ
             y��      ҳ��ַ
             display����Ҫ��ʾ�ı���
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_Print_Uint8_Variable(uint8 x, uint8 y, uint8 display, uint8 mode)
{
   uint8 temp[4];

   temp[0] = display/100+'0';
   temp[1] = display/10%10+'0';
   temp[2] = display%10+'0';
   temp[3] = '\0';

   oled_print(x, y, temp, mode);
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
void oled_Print_Uint16_Variable(uint8 x, uint8 y, uint16 display, uint8 mode)
{
   uint8 temp[6];

   temp[0] = display/10000+'0';
   temp[1] = display/1000%10+'0';
   temp[2] = display/100%10+'0';
   temp[3] = display/10%10+'0';
   temp[4] = display%10+'0';
   temp[5] = '\0';

   oled_print(x, y, temp, mode);
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
void oled_Print_Int16_Variable(uint8 x, uint8 y, int16 display, uint8 mode)
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

   oled_print(x, y, temp, mode);
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
void oled_Print_Float_Variable(uint8 x, uint8 y, float display, uint8 mode)
{
   uint8 temp[5];
   uint16 displayTemp = (uint16)(display*10);

   temp[0] = displayTemp/1000+'0';
   temp[1] = displayTemp/10%10+'0';
   temp[2] = '.';
   temp[3] = displayTemp%10+'0';

   temp[4] = '\0';

   oled_print(x, y, temp, mode);
}

/****************************************************************************
 - ������������ʾ16������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_Print_Hex(uint8 x, uint8 y, uint8 display, uint8 mode)
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
   oled_print(x, y, temp, mode);

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
   oled_print(x+8, y, temp, mode);
}

/****************************************************************************
 - ������������ʾ���Һ��ߵ�ǰ10������
 - ����˵����
 - ʾ����
 - �޸ļ�¼��
 - ע�����
****************************************************************************/
void oled_Print_Blackline(void)
{
   uint8 i = 0;

   // ��ʾ����ǰ10������
   for (i=0; i<5; i++)
   {
      oled_Print_Hex(i*24, 0, leftBlackline[i], NORMAL_DISPLAY);
   }
   for (i=0; i<5; i++)
   {
      oled_Print_Hex(i*24, 2, leftBlackline[5+i], NORMAL_DISPLAY);
   }


   // ��ʾ����ǰ10������
   for (i=0; i<5; i++)
   {
      oled_Print_Hex(i*24, 4, rightBlackline[i], NORMAL_DISPLAY);
   }
   for (i=0; i<5; i++)
   {
      oled_Print_Hex(i*24, 6, rightBlackline[5+i], NORMAL_DISPLAY);
   }
}

#endif
