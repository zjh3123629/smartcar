#ifndef  _DEV_OLED_H_
#define  _DEV_OLED_H_

#include "common.h"

#if 0
//----------------------OLED�ܽ�����----------------------//
/*
 * 4��SPIʹ��˵����

 * GND ��
 * 3V3 ���ڲ��߼���ѹ 1.8~6V   
 * D0��SCLK�� ʱ�ӽţ���MCU����
 * D1��MOSI�� ��������������ݽţ���MCU����
 * RES ģ�鸴λ�ܽ� 
 * DC  ��������ѡ��ܽ�
 * CS  Ƭѡ�ܽ�
 */
// OLED��D0���ӵ�PAD00
#define  OLED_SCL_OUT()    DDR1AD0_DDR1AD00 = 1
#define  OLED_SCL_ON()     PT1AD0_PT1AD00 = 1
#define  OLED_SCL_OFF()    PT1AD0_PT1AD00 = 0
// OLED��D1���ӵ�PAD01
#define  OLED_SDA_OUT()    DDR1AD0_DDR1AD01 = 1
#define  OLED_SDA_ON()     PT1AD0_PT1AD01 = 1
#define  OLED_SDA_OFF()    PT1AD0_PT1AD01 = 0
// OLED��RST���ӵ�PAD02
#define  OLED_RST_OUT()    DDR1AD0_DDR1AD02 = 1
#define  OLED_RST_ON()     PT1AD0_PT1AD02 = 1
#define  OLED_RST_OFF()    PT1AD0_PT1AD02 = 0
// OLED��DC���ӵ�PAD03
#define  OLED_DC_OUT()     DDR1AD0_DDR1AD03 = 1
#define  OLED_DC_ON()      PT1AD0_PT1AD03 = 1
#define  OLED_DC_OFF()     PT1AD0_PT1AD03 = 0
#else
/* 
 * PTE0 <--> D0, 
 * PTE1 <--> D1, 
 * PTE2 <--> RST, 
 * PTE3 <--> DC
 */
#endif

//----------------------OLED����ָ��----------------------//
#define  XLevelL		                  0x00        // ��ʼ�е�ַ�ĵ���λ         
#define  XLevelH		                  0x10        // ��ʼ�е�ַ�ĸ���λ
#define  XLevel		                  ((XLevelH&0x0F)*16+XLevelL)
//#define  Max_Column	                  128
//#define  Max_Row	                     64

#define	X_WIDTH                       128
#define Y_WIDTH                       64

#define OLED_FIRST_PAGE_ADDRESS       0xb0

#define OLED_DISPLAY_OFF              0x00
#define OLED_DISPLAY_ON               0x01

#define OLED_DISABLE_CHARGE_PUMP      0x00
#define OLED_ENABLE_CHARGE_PUMP       0x04

#define OLED_HORIZONTAL_ADDRESS_MODE  0x00
#define OLED_VERTICAL_ADDRESS_MODE    0x01
#define OLED_PAGE_ADDRESS_MODE        0x02

#define NORMAL_DISPLAY_MODE           0x00
#define INVERSE_DISPLAY_MODE          0x01
#define ENTIRE_DISPLAY_MODE           0x01

#define	CONTRAST_VALUE	               0xcf

#define NORMAL_DISPLAY                0
#define INVERSE_DISPLAY               1

//----------------------��������----------------------//
extern const uint8 startLogo[];

//----------------------��������----------------------//
enum {
	DARK = 0,
	LIGHT
};
extern void init_oled(void);
extern void oled_clear(void);
extern void oled_fill(uint8 flag);
// ��ʾ�ַ���
extern void oled_print(uint8 x, uint8 y, uint8 ch[], uint8 mode);
// ��ʾͼƬ
extern void oled_draw_pixel(uint8 x, uint8 y);
extern void oled_draw_rectangle(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 gif);
extern void oled_draw_picture(const uint8 *ptr);
// ��ʾ����
extern void OLED_Print_Uint8_Variable(uint8 x, uint8 y, uint8 display, uint8 mode);
extern void OLED_Print_Uint16_Variable(uint8 x, uint8 y, uint16 display, uint8 mode);
extern void OLED_Print_Int16_Variable(uint8 x, uint8 y, int16 display, uint8 mode);
extern void OLED_Print_Float_Variable(uint8 x, uint8 y, float display, uint8 mode);
extern void OLED_Print_Blackline(void);

#endif