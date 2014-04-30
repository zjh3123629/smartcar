#ifndef  _DEV_OLED_H_
#define  _DEV_OLED_H_

#include "common.h"

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
 * PTE0 <--> D0, 
 * PTE1 <--> D1, 
 * PTE2 <--> RST, 
 * PTE3 <--> DC
 */

/* 
 * FIXME
 * 1: need to modify
 */
#define init_oled_pin()	\
		do {\
			GPIO_InitTypeDef gpio_init_struct;\
			\
			gpio_init_struct.GPIO_PTx = PTE;\
			gpio_init_struct.GPIO_Pins = GPIO_Pin0|GPIO_Pin1|GPIO_Pin2|GPIO_Pin3;\
			gpio_init_struct.GPIO_Dir = DIR_OUTPUT;\
			gpio_init_struct.GPIO_Output = OUTPUT_H;\
			gpio_init_struct.GPIO_PinControl = IRQC_DIS;\
			\
			LPLD_GPIO_Init(gpio_init_struct);\
		} while(0)
/* 
 * FIXME
 * 2: need to modify
 */
#define oled_d0_on()	LPLD_GPIO_Output_b(PTE, 0, 1)
#define oled_d0_off()	LPLD_GPIO_Output_b(PTE, 0, 0)
#define oled_d1_on()	LPLD_GPIO_Output_b(PTE, 1, 1)
#define oled_d1_off()	LPLD_GPIO_Output_b(PTE, 1, 0)
#define oled_rst_on()	LPLD_GPIO_Output_b(PTE, 2, 1)
#define oled_rst_off()	LPLD_GPIO_Output_b(PTE, 2, 0)
#define oled_dc_on()	LPLD_GPIO_Output_b(PTE, 3, 1)
#define oled_dc_off()	LPLD_GPIO_Output_b(PTE, 3, 0)

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