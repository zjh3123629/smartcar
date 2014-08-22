#ifndef  _DEV_OLED_H_
#define  _DEV_OLED_H_

#include "common.h"
#include "delay.h"

/*
 * 4��SPIʹ��˵����
 * GND ��
 * 3V3 ���ڲ��߼���ѹ 1.8~6V   
 * D0��SCLK�� ʱ�ӽţ���MCU����
 * D1��MOSI�� ��������������ݽţ���MCU����
 * RST ģ�鸴λ�ܽ� 
 * DC  ��������ѡ��ܽ�
 * CS  Ƭѡ�ܽ�
 */

/* ��ֲ��Ҫ�޸ĵ�gpio���� */
/* 
 * PTA12 <--> D0, 
 * PTA13 <--> D1, 
 * PTA14 <--> RST, 
 * PTA15 <--> DC
 */
#define OLED_PORT	PTA
enum {
	OFF = 0,
	ON = 1,

	D0 = 12,
	D1 = 13,
	RST = 14,
	DC = 15
};

#define init_oled_pin()	\
		do {\
			GPIO_InitTypeDef gpio_init_struct;\
			\
			gpio_init_struct.GPIO_PTx = OLED_PORT;\
			gpio_init_struct.GPIO_Pins = (1<<D0) | (1<<D1) | (1<<RST) | (1<<DC);\
			gpio_init_struct.GPIO_Dir = DIR_OUTPUT;\
			gpio_init_struct.GPIO_Output = OUTPUT_H;\
			gpio_init_struct.GPIO_PinControl = IRQC_DIS;\
			\
			LPLD_GPIO_Init(gpio_init_struct);\
		} while(0)

#define oled_d0_on()	LPLD_GPIO_Output_b(OLED_PORT, D0, ON)
#define oled_d0_off()	LPLD_GPIO_Output_b(OLED_PORT, D0, OFF)
#define oled_d1_on()	LPLD_GPIO_Output_b(OLED_PORT, D1, ON)
#define oled_d1_off()	LPLD_GPIO_Output_b(OLED_PORT, D1, OFF)
#define oled_rst_on()	LPLD_GPIO_Output_b(OLED_PORT, RST, ON)
#define oled_rst_off()	LPLD_GPIO_Output_b(OLED_PORT, RST, OFF)
#define oled_dc_on()	LPLD_GPIO_Output_b(OLED_PORT, DC, ON)
#define oled_dc_off()	LPLD_GPIO_Output_b(OLED_PORT, DC, OFF)

//----------------------OLED����ָ��----------------------//
#define  XLevelL						0x00        // ��ʼ�е�ַ�ĵ���λ         
#define  XLevelH		         		0x10        // ��ʼ�е�ַ�ĸ���λ
#define  XLevel		                  	((XLevelH&0x0F)*16+XLevelL)
//#define  Max_Column	          		128
//#define  Max_Row						64

#define	X_WIDTH                       	128
#define Y_WIDTH                       	64

#define OLED_FIRST_PAGE_ADDRESS       	0xb0

#define OLED_DISPLAY_OFF              	0x00
#define OLED_DISPLAY_ON               	0x01

#define OLED_DISABLE_CHARGE_PUMP      	0x00
#define OLED_ENABLE_CHARGE_PUMP       	0x04

#define OLED_HORIZONTAL_ADDRESS_MODE	0x00
#define OLED_VERTICAL_ADDRESS_MODE    	0x01
#define OLED_PAGE_ADDRESS_MODE        	0x02

#define NORMAL_DISPLAY_MODE           	0x00
#define INVERSE_DISPLAY_MODE          	0x01
#define ENTIRE_DISPLAY_MODE           	0x01

#define	CONTRAST_VALUE	               	0xcf

/* add by zhouzuoyu */
#define NORMAL_DISPLAY                	0
#define INVERSE_DISPLAY               	1
			
#define DARK	0
#define LIGHT	1

//----------------------��������----------------------//
extern const uint8 startLogo[];

//----------------------��������----------------------//
extern void init_oled(void);
extern void oled_clear(void);
extern void oled_fill(uint8 flag);
// ��ʾ�ַ���
extern void oled_print(uint8 x, uint8 y, uint8 ch[], uint8 mode);
// ��ʾͼƬ
extern void oled_draw_pixel(uint8 x, uint8 y);
extern void oled_draw_rectangle(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 gif);
extern void oled_draw_picture(const uint8 *ptr);

#if 0
// ��ʾ����
extern void OLED_Print_Uint8_Variable(uint8 x, uint8 y, uint8 display, uint8 mode);
extern void OLED_Print_Uint16_Variable(uint8 x, uint8 y, uint16 display, uint8 mode);
extern void OLED_Print_Int16_Variable(uint8 x, uint8 y, int16 display, uint8 mode);
extern void OLED_Print_Float_Variable(uint8 x, uint8 y, float display, uint8 mode);
extern void OLED_Print_Blackline(void);
#endif

#endif