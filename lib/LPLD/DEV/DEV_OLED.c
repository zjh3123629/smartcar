#include "DEV_OLED.h"
#include "Font_OLED.h"

/****************************************************************************
 - 功能描述：发送数据到OLED
 - 参数说明：data：要发送的8位数据
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Write_Data(uint8 data)
{
   uint8 i = 8;

   OLED_DC_ON();  // 发送数据
   OLED_SCL_OFF();
   while (i--)
   {
      // 每次发送数据的最高位
      if (data & 0x80)
      {
         OLED_SDA_ON();
      }
      else
      {
         OLED_SDA_OFF();
      }
      // 时钟的上升沿发送
      #if (BUS_CLOCK == 88000000)
      {
         asm("nop");    // 1个
      }
      #endif
      OLED_SCL_ON();
      OLED_SCL_OFF();

      data <<= 1;
   }
}

/****************************************************************************
 - 功能描述：发送命令到OLED
 - 参数说明：cmd：要发送的8位命令
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Write_Cmd(uint8 cmd)
{
   uint8 i=8;

   OLED_DC_OFF();    // 发送命令
   OLED_SCL_OFF();
   while (i--)
   {
      // 每次发送命令的最高位
      if (cmd & 0x80)
      {
         OLED_SDA_ON();
      }
      else
      {
         OLED_SDA_OFF();
      }
      // 时钟的上升沿发送
      #if (BUS_CLOCK == 88000000)
      {
         asm("nop");    // 1个
      }
      #endif
      OLED_SCL_ON();
      OLED_SCL_OFF();

      cmd <<= 1;
   }
}

/****************************************************************************
 - 功能描述：设置OLED的列地址和页地址
 - 参数说明：columnAddress:列地址
             pageAddress:  页地址
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：1：只有在页地址模式下适用
             2：列的低四位默认为0x00，列的高四位默认为0x10
****************************************************************************/
static void OLED_Set_Position(uint8 columnAddress, uint8 pageAddress)
{
   OLED_Write_Cmd(0xb0+pageAddress);
   OLED_Write_Cmd((columnAddress&0x0f)|0x00);
   OLED_Write_Cmd(((columnAddress&0xf0)>>4)|0x10);
}

/****************************************************************************
 - 功能描述：设置SSD1306控制器的存储器地址模式
 - 返回说明：mode:
             0:水平地址自增模式
             1:垂直地址自增模式
             2:页地址自增模式
 - 示例：
 - 修改记录：
 - 注意事项：默认：页地址自增模式
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
 - 功能描述：设置显示数据RAM的起始页地址和终止页地址
 - 返回说明：beginPageAddress:起始页地址
             endPageAddress:  终止页地址
 - 示例：
 - 修改记录：
 - 注意事项：1：默认：0->7页
             2：只能在设置的页地址之间显示数据！
****************************************************************************/
static void OLED_Set_Page_Address(uint8 beginPageAddress, uint8 endPageAddress)
{
	OLED_Write_Cmd(0x22);               // Set Page Address
	OLED_Write_Cmd(beginPageAddress);   // Default => 0x00 (Page Start Address)
	OLED_Write_Cmd(endPageAddress);	   // Default => 0x07 (Page End Address)
}

/****************************************************************************
 - 功能描述：设置显示数据RAM的起始列地址和终止列地址
 - 返回说明：beginColumnAddress:起始列地址
             endColumnAddress:  终止列地址
 - 示例：
 - 修改记录：
 - 注意事项：1：默认：0->127列
             2：只能在设置的列地址之间显示数据！
****************************************************************************/
static void OLED_Set_Column_Address(uint8 beginColumnAddress, uint8 endColumnAddress)
{
	OLED_Write_Cmd(0x21);               // Set Column Address
	OLED_Write_Cmd(beginColumnAddress); // Default => 0x00 (Column Start Address)
	OLED_Write_Cmd(endColumnAddress);   // Default => 0x7F (Column End Address)
}

/****************************************************************************
 - 功能描述：设置显示RAM的起始地址
 - 返回说明：startLine:显示RAM的开始地址
 - 示例：    d=1:显示RAM的第1行映射COM0
 - 修改记录：
 - 注意事项：1:0x00->0x3f(0->63行)
             2:默认：0行
****************************************************************************/
static void OLED_Set_Start_Line(uint8 d)
{
	OLED_Write_Cmd(0x40|d);    // Set Display Start Line
						            // Default => 0x40 (0x00)
}

/****************************************************************************
 - 功能描述：设置OLED显示的对比度
 - 返回说明：contrast:对比度（0x00->0xff）
 - 示例：
 - 修改记录：
 - 注意事项：1:0x00->0xff
             2:默认：0x7f
             3:段的输出电流随着对比度数值的增大而增大
****************************************************************************/
static void OLED_Set_Contrast(uint8 d)
{
	OLED_Write_Cmd(0x81);      // Set Contrast Control
	OLED_Write_Cmd(d);         // Default => 0x7F
}

/****************************************************************************
 - 功能描述：设置打开/关闭OLED的电荷泵
 - 返回说明：chargePumpStatus:
             0x00:关闭电荷泵
             0x04:打开电荷泵
 - 示例：
 - 修改记录：
 - 注意事项：默认：关闭电荷泵
****************************************************************************/
static void OLED_Set_Charge_Pump(uint8 d)
{
	OLED_Write_Cmd(0x8D);   // Set Charge Pump
	OLED_Write_Cmd(0x10|d); // Default => 0x10
						         // 0x10 (0x00) => Disable Charge Pump
						         // 0x14 (0x04) => Enable Charge Pump
}

/****************************************************************************
 - 功能描述：改变显示数据列地址到段的映射
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Set_Segment_Remap(uint8 d)
{
	OLED_Write_Cmd(0xA0|d);    // Set Segment Re-Map
						            // Default => 0xA0
						            // 0xA0 (0x00) => Column Address 0 Mapped to SEG0
						            // 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

/****************************************************************************
 - 功能描述：设置打开/关闭OLED的整体显示
 - 返回说明：entireDisplayStatus:
             0x00:显示GDDRAM中的内容（普通显示）
             0x01:强制开整体显示，不管GDDRAM中的内容
 - 示例：
 - 修改记录：
 - 注意事项：默认：关闭整体显示（普通显示）
****************************************************************************/
static void OLED_Set_Entire_Display(uint8 d)
{
	OLED_Write_Cmd(0xA4|d);    // Set Entire Display On / Off
						            // Default => 0xA4
						            // 0xA4 (0x00) => Normal Display
						            // 0xA5 (0x01) => Entire Display On
}

/****************************************************************************
 - 功能描述：设置普通/反白显示
 - 返回说明：inverseDisplayStatus:
             0x00:RAM中'1'代表像素点的打亮（普通显示）
             0x01:RAM中'0'代表像素点的打亮（反白显示）
 - 示例：
 - 修改记录：
 - 注意事项：默认：普通显示
****************************************************************************/
static void OLED_Set_Inverse_Display(uint8 d)
{
	OLED_Write_Cmd(0xA6|d);    // Set Inverse Display On/Off
						            // Default => 0xA6
						            // 0xA6 (0x00) => Normal Display
						            // 0xA7 (0x01) => Inverse Display On
}

/****************************************************************************
 - 功能描述：设置OLED显示的总行数
 - 返回说明：multiplexRatio:16->63
 - 示例：
 - 修改记录：
 - 注意事项：默认：63（0->63：总共64行）
****************************************************************************/
static void OLED_Set_Multiplex_Ratio(uint8 d)
{
	OLED_Write_Cmd(0xA8);   // Set Multiplex Ratio
	OLED_Write_Cmd(d);      // Default => 0x3F (1/64 Duty)
}

/****************************************************************************
 - 功能描述：设置打开/关闭OLED的显示面板
 - 返回说明：displayStatus:
             0x00:关闭显示
             0x01:打开显示
 - 示例：
 - 修改记录：
 - 注意事项：默认：关闭显示
****************************************************************************/
static void OLED_Set_Display_On_Off(uint8 d)
{
	OLED_Write_Cmd(0xAE|d); // Set Display On/Off
         				      // Default => 0xAE
         					   // 0xAE (0x00) => Display Off
         					   // 0xAF (0x01) => Display On
}

/****************************************************************************
 - 功能描述：设置OLED的起始页地址
 - 返回说明：startPageAddress:0->7
 - 示例：
 - 修改记录：
 - 注意事项：1:默认：起始页地址为0
             2:只有在页地址模式下适用
****************************************************************************/
static void OLED_Set_Start_Page_Address(uint8 d)
{
	OLED_Write_Cmd(0xB0|d); // Set Page Start Address for Page Addressing Mode
						         // Default => 0xB0 (0x00)
}

/****************************************************************************
 - 功能描述：设置COM输出的扫描方向
 - 返回说明：startPageAddress:0->7
 - 示例：
 - 修改记录：
 - 注意事项：默认：扫描方向为第0行->第63行
****************************************************************************/
static void OLED_Set_Common_Remap(uint8 d)
{
	OLED_Write_Cmd(0xC0|d);    // Set COM Output Scan Direction
						            // Default => 0xC0
						            // 0xC0 (0x00) => Scan from COM0 to 63
					            	// 0xC8 (0x08) => Scan from COM63 to 0
}

/****************************************************************************
 - 功能描述：设置OLED行的显示偏移量：显示起始行映射到0->63行的其中一行
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：默认：显示的偏移量为0
****************************************************************************/
static void OLED_Set_Display_Offset(uint8 d)
{
	OLED_Write_Cmd(0xD3);   // Set Display Offset
	OLED_Write_Cmd(d);      // Default => 0x00
}

/****************************************************************************
 - 功能描述：设置OLED显示时钟的速率和晶振的频率
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Set_Display_Clock(uint8 d)
{
	OLED_Write_Cmd(0xD5);   // Set Display Clock Divide Ratio / Oscillator Frequency
	OLED_Write_Cmd(d);      // Default => 0x80
					            // D[3:0] => Display Clock Divider
					            // D[7:4] => Oscillator Frequency
}

/****************************************************************************
 - 功能描述：设置预充电周期的持续时间
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Set_Precharge_Period(uint8 d)
{
	OLED_Write_Cmd(0xD9);   // Set Pre-Charge Period
	OLED_Write_Cmd(d);	   // Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
					         	// D[3:0] => Phase 1 Period in 1~15 Display Clocks
						         // D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

/****************************************************************************
 - 功能描述：设置COM信号管脚配置用于匹配OLED面板的硬件布局
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Set_Common_Config(uint8 d)
{
	OLED_Write_Cmd(0xDA);      // Set COM Pins Hardware Configuration
	OLED_Write_Cmd(0x02|d);    // Default => 0x12 (0x10)
						            // Alternative COM Pin Configuration
						            // Disable COM Left/Right Re-Map
}

/****************************************************************************
 - 功能描述：调整Vcomh调节器的输出
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Set_VCOMH(uint8 d)
{
	OLED_Write_Cmd(0xDB);   // Set VCOMH Deselect Level
	OLED_Write_Cmd(d);      // Default => 0x20 (0.77*VCC)
}

/****************************************************************************
 - 功能描述：OLED的空操作
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Set_NOP(void)
{
	OLED_Write_Cmd(0xE3);   // Command for No Operation
}

/****************************************************************************
 - 功能描述：OLED上填充0/1
 - 返回说明：flag:
             0:全灭
             1:全亮
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void oled_fill(uint8 flag)
{
   uint8 pageAddress=0, columnAddress=0;

   // 1到8页全部填充
   for (pageAddress=0; pageAddress<8; pageAddress++)
   {
      OLED_Write_Cmd(0xb0+pageAddress);   // 设置页地址
      OLED_Write_Cmd(0x00);               // 设置列地址
      OLED_Write_Cmd(0x10);
      // 填充数据
      for (columnAddress=0; columnAddress<X_WIDTH; columnAddress++)
      {
         OLED_Write_Data(flag);
      }
   }
}

/****************************************************************************
 - 功能描述：OLED上填充0=>清屏
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void oled_clear(void)
{
	oled_fill(DARK);
}

/****************************************************************************
 - 功能描述：初始化OLED
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void init_oled(void)
{
   // 管脚设置为输出状态
   OLED_SCL_OUT();
   OLED_SDA_OUT();
   OLED_RST_OUT();
   OLED_DC_OUT();

   OLED_SCL_ON();
   OLED_RST_OFF();
   Delay_1ms(50);
   OLED_RST_ON();

   //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕
   OLED_Set_Display_On_Off(OLED_DISPLAY_OFF);      // Display Off (0x00/0x01)
   OLED_Set_Display_Clock(0x80);		               // Set Clock as 100 Frames/Sec
   OLED_Set_Multiplex_Ratio(0x3F);		            // 1/64 Duty (0x0F~0x3F)
   OLED_Set_Display_Offset(0x00);		            // Shift Mapping RAM Counter (0x00~0x3F)
   OLED_Set_Start_Line(0x00);			               // Set Mapping RAM Display Start Line (0x00~0x3F)
   OLED_Set_Charge_Pump(OLED_ENABLE_CHARGE_PUMP);  // Enable Embedded DC/DC Converter (0x00/0x04)
   OLED_Set_Address_Mode(OLED_PAGE_ADDRESS_MODE);  // Set Page Addressing Mode (0x00/0x01/0x02)
   OLED_Set_Segment_Remap(0x01);		               // Set SEG/Column Mapping     0x00左右反置 0x01正常
   OLED_Set_Common_Remap(0x08);			            // Set COM/Row Scan Direction 0x00上下反置 0x08正常
   OLED_Set_Common_Config(0x10);		               // Set Sequential Configuration (0x00/0x10)
   OLED_Set_Contrast(CONTRAST_VALUE);              // Set SEG Output Current
   OLED_Set_Precharge_Period(0xF1);		            // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
   OLED_Set_VCOMH(0x40);			                  // Set VCOM Deselect Level
   OLED_Set_Entire_Display(NORMAL_DISPLAY_MODE);   // Disable Entire Display On (0x00/0x01)
   OLED_Set_Inverse_Display(NORMAL_DISPLAY_MODE);  // Disable Inverse Display On (0x00/0x01)
   OLED_Set_Display_On_Off(OLED_DISPLAY_ON);		   // Display On (0x00/0x01)
   OLED_Fill(0x00);                                // 初始清屏
   OLED_Set_Position(0, 0);	                     // 设置原点
   
   oled_clear();
}

/****************************************************************************
 - 功能描述：绘制一个点(x,y)
 - 返回说明：真实坐标值(x,y),x的范围0～127，y的范围0～63
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void OLED_Draw_Pixel(uint8 x, uint8 y)
{
   uint8 data;   // data当前点的数据

   data = 0x01<<(y%8);                 // 定位到8位数据中哪一位
   OLED_Write_Cmd(0xb0+(y>>3));        // 定位到第几页
   OLED_Write_Cmd(((x&0xf0)>>4)|0x10); // 定位到第几列
   OLED_Write_Cmd((x&0x0f)|0x00);
   OLED_Write_Data(data);              // 打亮该点
}

/****************************************************************************
 - 功能描述：绘制一个实心矩形
 - 返回说明：左上角坐标（x1,y1）,右下角坐标（x2，y2）
             其中x1、x2的范围0～127，y1，y2的范围0～63，即真实坐标值
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void OLED_Draw_Rectangle(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 gif)
{
	uint8 n;
		
   OLED_Set_Position(x1, y1>>3); // 定位坐标到几页几列
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
 - 功能描述：显示6列x8行大小的ASCII码字符串
 - 返回说明：x：   列地址
             y：   页地址
             ch[]：需要显示的字符串
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Print_6x8_String(uint8 x, uint8 y, uint8 ch[])
{
   uint8 c=0, i=0, j=0;    // c：需要显示的编码在ASCII表中的位置

   while (ch[j] != '\0')   // 判断字符串是否结束
   {
      c = ch[j]-32;        // 该文件中所用的ASCII表是从完整的ASCII表的第32位开始的
      // 定位坐标位置
      if (x > 126)
      {
         x=0;
         y++;
      }
      OLED_Set_Position(x, y);
      // 写入数据
      for (i=0; i<6; i++)
      {
         OLED_Write_Data(Front_6x8[c][i]);
      }
      // 为显示字符串中的下一个字符做准备
      x += 6;
      j++;
   }
}

/****************************************************************************
 - 功能描述：显示8列16行大小的ASCII码字符串
 - 返回说明：x：   列地址
             y：   页地址
             ch[]：需要显示的字符串
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Print_8x16_String(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
   uint8 c=0, i=0, j=0;    // c：需要显示的编码在ASCII表中的位置

   while (ch[j] != '\0')   // 判断字符串是否结束
   {
      c = ch[j] - 32;      // 该文件中所用的ASCII表是从完整的ASCII表的第32位开始的
      // 定位坐标位置
      if (x > 120)
      {
         x = 0;
         y++;
      }
      OLED_Set_Position(x,y);
      // 写入数据
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
      // 为显示字符串中的下一个字符做准备
      x += 8;
      j++;
   }
}

/****************************************************************************
 - 功能描述：显示14列x16行大小的汉字字符串
 - 返回说明：x：   列地址
             y：   页地址
             ch[]：需要显示的字符串
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
static void OLED_Print_14x16_String(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
   uint8 wm=0, ii=0;
   uint16 adder = 1;         // 需要显示的汉字编码在Front_14x16[]中的位置

   while (ch[ii] != '\0')  // 判断需要显示的字符串是否结束
   {
      wm = 0;
      adder = 1;
      // 查找：需要显示的汉字编码与Front_14x16_Idx[]中哪一个汉字的编码相对应
      while (Front_14x16_Idx[wm] > 127)   // 查找到Front_14x16_Idx[]的末尾
      {
         if (Front_14x16_Idx[wm] == ch[ii])
         {
            if (Front_14x16_Idx[wm + 1] == ch[ii + 1])
            {
               adder = wm * 14;
               // 两个字节的编码都相等=>寻找到需要显示的汉字编码=>退出查找
               break;
            }
         }
         wm += 2;
      }
      // 定位坐标位置
      if (x > 118)
      {
         x=0;
         y++;
      }
      OLED_Set_Position(x, y);

      // 查找到编码显示相应的汉字
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
      // 查找不到编码则显示空白并且进行下一轮的查找
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
      // 为显示字符串中的下一个字符做准备
      x += 14;
      ii += 2;
   }
}

/****************************************************************************
 - 功能描述：显示16行大小的汉字和字符的混合字符串
 - 返回说明：x：   列地址
            y：   页地址
            ch[]：需要显示的字符串
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void oled_print(uint8 x, uint8 y, uint8 ch[], uint8 mode)
{
	uint8 ch2[3];
	uint8 ii = 0;
	
	while (ch[ii] != '\0')
	{
	   // 需要显示的是汉字
		if (ch[ii] > 127)
		{
			ch2[0] = ch[ii];  // 汉字为两个字节
	 		ch2[1] = ch[ii+1];
			ch2[2] = '\0';
			OLED_Print_14x16_String(x, y, ch2, mode); // 显示汉字
			// 为显示字符串中的下一个字符做准备
			x += 14;
			ii += 2;
		}
		// 需要显示的是字母
		else
		{
			ch2[0] = ch[ii];  // 字母占一个字节
			ch2[1] = '\0';
			OLED_Print_8x16_String(x, y, ch2, mode);	// 显示字母
			// 为显示字符串中的下一个字符做准备
			x += 8;
			ii += 1;
		}
	}
}

/****************************************************************************
 - 功能描述：显示128x48大小的图片
 - 返回说明：存放128×48大小图片编码的数组名
 - 示例：
 - 修改记录：
 - 注意事项：
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
 - 功能描述：显示占3格位置的变量
 - 返回说明：x：      列地址
             y：      页地址
             display：需要显示的变量
 - 示例：
 - 修改记录：
 - 注意事项：
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
 - 功能描述：显示占5格位置的变量
 - 返回说明：x：      列地址
             y：      页地址
             display：需要显示的变量
 - 示例：
 - 修改记录：
 - 注意事项：
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
 - 功能描述：显示占5格位置的变量
 - 返回说明：x：      列地址
             y：      页地址
             display：需要显示的变量
 - 示例：
 - 修改记录：
 - 注意事项：
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
 - 功能描述：显示带一位的小数变量(00.0)
 - 返回说明：x：      列地址
             y：      页地址
             display：需要显示的变量
 - 示例：
 - 修改记录：
 - 注意事项：
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
 - 功能描述：显示16进制数
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void OLED_Print_Hex(uint8 x, uint8 y, uint8 display, uint8 mode)
{
   uint8 i = 0;
   uint8 temp[2];

   // 显示16进制的前一个字母
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

   // 显示16进制的后一个字母
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
 - 功能描述：显示左右黑线的前10个数据
 - 返回说明：
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
void OLED_Print_Blackline(void)
{
   uint8 i = 0;

   // 显示左线前10个数据
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 0, leftBlackline[i], NORMAL_DISPLAY);
   }
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 2, leftBlackline[5+i], NORMAL_DISPLAY);
   }


   // 显示右线前10个数据
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 4, rightBlackline[i], NORMAL_DISPLAY);
   }
   for (i=0; i<5; i++)
   {
      OLED_Print_Hex(i*24, 6, rightBlackline[5+i], NORMAL_DISPLAY);
   }
}