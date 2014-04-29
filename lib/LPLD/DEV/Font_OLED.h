#ifndef _FONT_OLED_H_
#define _FONT_OLED_H_

/* 
 * The font used for oled12864
 * 有且仅能在DEV_OLED.c中使用
*/

/****************************************************************************
 - 功能描述：6列x8行矩阵大小的ASCII码
 - 参数说明：
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
const uint8 Front_6x8[][6] =
{
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // space
   { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
   { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
   { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
   { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
   { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
   { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
   { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
   { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
   { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
   { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
   { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
   { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
   { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
   { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
   { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
   { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
   { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
   { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
   { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
   { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
   { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
   { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
   { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
   { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
   { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
   { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
   { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
   { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
   { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
   { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
   { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
   { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
   { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
   { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
   { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
   { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
   { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
   { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
   { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
   { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
   { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
   { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
   { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
   { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
   { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
   { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
   { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
   { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
   { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
   { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
   { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
   { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
   { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
   { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
   { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
   { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
   { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
   { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
   { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
   { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // '\'
   { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
   { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
   { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
   { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
   { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
   { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
   { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
   { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
   { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
   { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
   { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
   { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
   { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
   { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
   { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
   { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
   { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
   { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
   { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
   { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
   { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
   { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
   { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
   { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
   { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
   { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
   { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
   { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
   { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
   { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
   { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};

/****************************************************************************
 - 功能描述：8列x16行矩阵大小的ASCII码
 - 参数说明：
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
const uint8 Front_8x16[]=
{
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //   0
   0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00, // ! 1
   0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // " 2
   0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00, // # 3
   0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00, // $ 4
   0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00, // % 5
   0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10, // & 6
   0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ' 7
   0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00, // ( 8
   0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00, // ) 9
   0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00, // * 10
   0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00, // + 11
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00, // , 12
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01, // - 13
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00, // . 14
   0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00, // / 15
   0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00, // 0 16
   0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00, // 1 17
   0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00, // 2 18
   0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00, // 3 19
   0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00, // 4 20
   0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00, // 5 21
   0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00, // 6 22
   0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00, // 7 23
   0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00, // 8 24
   0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00, // 9 25
   0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00, // : 26
   0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00, // ; 27
   0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00, // < 28
   0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00, // = 29
   0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00, // > 30
   0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00, // ? 31
   0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00, // @ 32
   0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20, // A 33
   0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00, // B 34
   0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00, // C 35
   0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00, // D 36
   0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00, // E 37
   0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00, // F 38
   0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00, // G 39
   0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20, // H 40
   0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00, // I 41
   0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00, // J 42
   0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00, // K 43
   0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00, // L 44
   0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00, // M 45
   0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00, // N 46
   0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00, // O 47
   0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00, // P 48
   0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00, // Q 49
   0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20, // R 50
   0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00, // S 51
   0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00, // T 52
   0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00, // U 53
   0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00, // V 54
   0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00, // W 55
   0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20, // X 56
   0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00, // Y 57
   0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00, // Z 58
   0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00, // [ 59
   0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00, // \ 60
   0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00, // ] 61
   0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ^ 62
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80, // _ 63
   0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ` 64
   0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20, // a 65
   0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00, // b 66
   0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00, // c 67
   0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20, // d 68
   0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00, // e 69
   0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00, // f 70
   0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00, // g 71
   0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20, // h 72
   0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00, // i 73
   0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00, // j 74
   0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00, // k 75
   0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00, // l 76
   0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F, // m 77
   0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20, // n 78
   0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00, // o 79
   0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00, // p 80
   0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80, // q 81
   0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00, // r 82
   0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00, // s 83
   0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00, // t 84
   0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20, // u 85
   0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00, // v 86
   0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00, // w 87
   0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00, // x 88
   0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00, // y 89
   0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00, // z 90
   0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40, // { 91
   0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00, // | 92
   0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00, // } 93
   0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~ 94
};

/****************************************************************************
 - 功能描述：14列x16行矩阵大小的汉字编码
 - 参数说明：
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：Front_14x16_Idx[]中汉字的位置要与Front_14x16[]中汉字编码的位置一一对应
****************************************************************************/
const uint8 Front_14x16_Idx[] =
{
    "欢迎使用超音速号请将车放在赛道上阈值为中心左右线前瞻大小直其它调试参数退出按整模式十字发现进入正反转跪了时间速度设定路径起跑线舵机矫正界面弯最高低检测开启关闭系口状态点刹次方案全有无拐"
};
const uint8 Front_14x16[] = {
0x34,0x44,0x84,0x44,0x3C,0x20,0x10,0x0E,0xE8,0x08,0x28,0x18,0x00,0x00,
0x04,0x03,0x00,0x01,0x22,0x20,0x18,0x06,0x01,0x06,0x18,0x20,0x20,0x00,//欢0

0x42,0x44,0xC8,0x00,0xFC,0x04,0x02,0x82,0xFC,0x04,0x04,0x04,0xFC,0x00,
0x20,0x10,0x0F,0x10,0x27,0x22,0x21,0x20,0x2F,0x21,0x22,0x24,0x23,0x00,//迎1

0x20,0xF8,0x06,0xE8,0x28,0x28,0x28,0xFE,0x28,0x28,0x28,0xE8,0x08,0x00,
0x00,0x3F,0x00,0x21,0x23,0x15,0x0D,0x0B,0x11,0x11,0x21,0x23,0x20,0x00,//使2

0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
0x30,0x0F,0x02,0x02,0x02,0x02,0x3F,0x02,0x02,0x12,0x22,0x1F,0x00,0x00,//用3

0x40,0x48,0x48,0xFE,0x48,0x8A,0x42,0xBE,0x82,0xA2,0xC2,0xBE,0x00,0x00,
0x30,0x0F,0x08,0x1F,0x22,0x22,0x20,0x2F,0x28,0x28,0x28,0x2F,0x20,0x00,//超4

0x20,0x24,0xA4,0xAC,0xB4,0xA4,0xA6,0xA4,0xB4,0xAC,0xA4,0x24,0x20,0x00,
0x00,0x00,0x3F,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x3F,0x00,0x00,0x00,//音5

0x42,0x44,0xCC,0x00,0xE8,0x28,0x28,0xFE,0x28,0x28,0xE8,0x08,0x00,0x00,
0x20,0x10,0x0F,0x10,0x29,0x25,0x23,0x3F,0x23,0x25,0x2D,0x20,0x20,0x00,//速6

0x80,0x80,0xBE,0xA2,0xA2,0xA2,0xA2,0xA2,0xA2,0xA2,0xBE,0x80,0x80,0x00,
0x00,0x00,0x02,0x03,0x02,0x02,0x02,0x12,0x22,0x22,0x1E,0x00,0x00,0x00,//号7

0x20,0x22,0xEC,0x00,0x44,0x54,0x54,0x54,0x7E,0x54,0x54,0x54,0x44,0x00,
0x00,0x00,0x3F,0x10,0x08,0x3F,0x09,0x09,0x0F,0x09,0x29,0x3F,0x00,0x00,//请0

0x08,0x30,0xFE,0x00,0x90,0x88,0x54,0x66,0x24,0x14,0xCC,0x00,0x00,0x00,
0x06,0x01,0x3F,0x00,0x01,0x03,0x0D,0x01,0x21,0x21,0x1F,0x01,0x01,0x00,//将1

0x08,0xC8,0xA8,0x98,0x88,0x8C,0xEA,0x88,0x88,0x88,0x88,0x08,0x00,0x00,
0x04,0x04,0x04,0x04,0x04,0x04,0x3F,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//车2

0x10,0xF0,0x92,0x94,0x90,0x40,0x30,0xDE,0x10,0x90,0x70,0x10,0x10,0x00,
0x38,0x07,0x10,0x20,0x1F,0x20,0x10,0x0D,0x02,0x0D,0x10,0x20,0x20,0x00,//放3

0x08,0x08,0x88,0x48,0x38,0x8E,0x88,0x88,0xE8,0x88,0x88,0x88,0x08,0x00,
0x02,0x01,0x3F,0x00,0x10,0x10,0x10,0x10,0x1F,0x10,0x10,0x10,0x10,0x00,//在4

0x1C,0x04,0x54,0x54,0xFC,0x54,0x56,0x54,0xFC,0x54,0x54,0x04,0x1C,0x00,
0x05,0x05,0x23,0x2D,0x25,0x15,0x0D,0x15,0x25,0x2D,0x23,0x05,0x05,0x00,//赛5

0x42,0x44,0xCC,0x00,0x08,0xEA,0xAC,0xB8,0xA8,0xAC,0xEA,0x08,0x00,0x00,
0x20,0x10,0x0F,0x10,0x20,0x2F,0x2A,0x2A,0x2A,0x2A,0x2F,0x20,0x20,0x00,//道6

0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x20,0x20,0x20,0x20,0x00,0x00,0x00,
0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x00,//上7

0xF8,0x12,0xD4,0x50,0x52,0xD2,0x12,0xFE,0x12,0x9A,0x12,0xFE,0x00,0x00,
0x3F,0x08,0x0B,0x0A,0x0A,0x2B,0x10,0x0B,0x0C,0x13,0x2C,0x3F,0x00,0x00,//阈0

0x40,0x20,0xF8,0x06,0x04,0xF4,0x54,0x54,0x5E,0x54,0x54,0xF4,0x04,0x00,
0x00,0x00,0x3F,0x00,0x10,0x1F,0x15,0x15,0x15,0x15,0x15,0x1F,0x10,0x00,//值1

0x00,0x20,0x22,0x24,0x2C,0x20,0xE0,0x3E,0x20,0x20,0x20,0x20,0xE0,0x00,
0x00,0x20,0x10,0x08,0x04,0x03,0x00,0x01,0x02,0x16,0x20,0x20,0x1F,0x00,//为2

0x00,0xF8,0x08,0x08,0x08,0x08,0xFE,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,
0x00,0x03,0x01,0x01,0x01,0x01,0x3F,0x01,0x01,0x01,0x01,0x03,0x00,0x00,//中0

0x00,0xC0,0x00,0xF0,0x00,0x02,0x04,0x18,0x00,0x00,0x40,0x80,0x80,0x00,
0x03,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x20,0x1C,0x00,0x00,0x03,0x00,//心1

0x08,0x08,0x08,0x88,0xF8,0x8E,0x88,0x88,0x88,0x88,0x88,0x88,0x08,0x00,
0x08,0x14,0x13,0x10,0x10,0x10,0x10,0x1F,0x10,0x10,0x10,0x10,0x10,0x00,//左0

0x08,0x08,0x88,0xC8,0xB8,0x8E,0x88,0x88,0x88,0x88,0x88,0x08,0x08,0x00,
0x02,0x01,0x00,0x3F,0x10,0x10,0x10,0x10,0x10,0x10,0x3F,0x00,0x00,0x00,//右1

0x20,0x30,0xAC,0x62,0x10,0x80,0x90,0x90,0xFE,0x90,0x92,0x94,0x80,0x00,
0x12,0x13,0x0A,0x0A,0x0A,0x10,0x10,0x08,0x0F,0x14,0x22,0x22,0x30,0x00,//线2

0x08,0xE8,0xAA,0xAA,0xAE,0xE8,0x08,0x08,0xCC,0x0A,0x0A,0xE8,0x08,0x00,
0x00,0x3F,0x04,0x24,0x24,0x3F,0x00,0x00,0x07,0x10,0x20,0x1F,0x00,0x00,//前0

0xFC,0x24,0x24,0xFC,0x00,0xF8,0xD4,0xB6,0x94,0xDC,0x94,0xB0,0xD0,0x00,
0x3F,0x11,0x11,0x3F,0x20,0x1F,0x00,0x3A,0x2C,0x29,0x2A,0x38,0x00,0x00,//瞻1

0x20,0x20,0x20,0x20,0x20,0xA0,0x7E,0xA0,0x20,0x20,0x20,0x20,0x20,0x00,
0x20,0x20,0x10,0x08,0x06,0x01,0x00,0x01,0x06,0x08,0x10,0x30,0x10,0x00,//大0

0x00,0x80,0x40,0x60,0x00,0x00,0xFE,0x00,0x00,0x20,0x40,0xC0,0x80,0x00,
0x01,0x00,0x00,0x00,0x10,0x20,0x1F,0x00,0x00,0x00,0x00,0x00,0x01,0x00,//小1

0x04,0x04,0xF4,0x54,0x54,0x54,0x5E,0x54,0x54,0x54,0xF4,0x04,0x04,0x00,
0x10,0x10,0x1F,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x1F,0x10,0x10,0x00,//直0

0x00,0x04,0x04,0xFE,0xA4,0xA4,0xA4,0xA4,0xA4,0xFE,0x04,0x04,0x00,0x00,
0x04,0x24,0x24,0x17,0x04,0x04,0x04,0x04,0x04,0x17,0x24,0x24,0x04,0x00,//其1

0x38,0x08,0x08,0xE8,0x08,0x0A,0x0C,0x08,0x88,0xC8,0x08,0x08,0x38,0x00,
0x00,0x00,0x00,0x1F,0x22,0x22,0x21,0x21,0x20,0x20,0x20,0x1C,0x00,0x00,//它2

0x22,0xE6,0x00,0x00,0xFE,0x42,0x52,0x7E,0x52,0x52,0x42,0xFE,0x00,0x00,
0x00,0x0F,0x24,0x12,0x0F,0x00,0x0F,0x09,0x09,0x2F,0x20,0x1F,0x00,0x00,//调0

0x42,0xC4,0x08,0x10,0x90,0x90,0x90,0x90,0x3E,0xD0,0x12,0x14,0x10,0x00,
0x00,0x3F,0x10,0x08,0x10,0x10,0x1F,0x08,0x00,0x07,0x18,0x20,0x38,0x00,//试1

0x20,0x20,0xA8,0xA8,0x6C,0xBA,0xA8,0x68,0xAA,0xAC,0x28,0x20,0x20,0x00,
0x22,0x21,0x20,0x25,0x15,0x14,0x12,0x0A,0x08,0x04,0x01,0x03,0x01,0x00,//参2

0x92,0x54,0x30,0xFE,0x50,0x94,0x32,0xD8,0x16,0x10,0xF0,0x10,0x10,0x00,
0x22,0x26,0x1B,0x12,0x2A,0x26,0x10,0x0B,0x04,0x0B,0x10,0x20,0x20,0x00,//数3

0x42,0x44,0xCC,0x00,0x00,0xFE,0x4A,0xCA,0x4A,0x4A,0xFE,0x40,0x00,0x00,
0x20,0x10,0x0F,0x10,0x20,0x2F,0x24,0x22,0x21,0x23,0x24,0x2C,0x20,0x00,//退0

0x00,0x7C,0x40,0x40,0x40,0x40,0xFE,0x40,0x40,0x40,0x40,0x7C,0x00,0x00,
0x3F,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x3F,0x00,//出1

0x10,0x90,0xFE,0x50,0x00,0xB8,0x88,0x88,0xEE,0x88,0x88,0xB8,0x80,0x00,
0x11,0x20,0x1F,0x00,0x00,0x20,0x22,0x15,0x08,0x14,0x23,0x20,0x00,0x00,//按0

0x04,0x74,0xD4,0xFE,0xD4,0x74,0x14,0x08,0xB6,0x44,0xA4,0x1C,0x04,0x00,
0x20,0x23,0x22,0x3B,0x22,0x23,0x3E,0x2B,0x2A,0x2A,0x2A,0x23,0x21,0x00,//整0

0x10,0xD0,0xFE,0x50,0x94,0xF4,0x5E,0x54,0x54,0x54,0x5E,0xF4,0x04,0x00,
0x03,0x00,0x3F,0x00,0x24,0x25,0x15,0x0D,0x07,0x0D,0x15,0x25,0x24,0x00,//模0

0x10,0x90,0x90,0x90,0x90,0x90,0x10,0xFE,0x10,0x12,0x14,0x10,0x10,0x00,
0x10,0x10,0x10,0x0F,0x08,0x08,0x08,0x03,0x0C,0x10,0x20,0x20,0x18,0x00,//式1

0x40,0x40,0x40,0x40,0x40,0x40,0xFE,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//十0

0x00,0x1C,0x24,0x24,0x24,0x24,0x26,0xA4,0x64,0x24,0x04,0x1C,0x00,0x00,
0x01,0x01,0x01,0x01,0x11,0x21,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x00,//字1

0x00,0x18,0x16,0x10,0x90,0xF0,0x9E,0x90,0x90,0x92,0x94,0x10,0x10,0x00,
0x10,0x08,0x24,0x22,0x21,0x11,0x0A,0x04,0x0A,0x11,0x20,0x20,0x20,0x00,//发0

0x44,0x44,0xFC,0x44,0x44,0x00,0xFE,0x02,0xFA,0x02,0x02,0xFE,0x00,0x00,
0x08,0x08,0x0F,0x04,0x24,0x20,0x11,0x0C,0x03,0x1E,0x20,0x21,0x30,0x00,//现1

0x42,0xCC,0x00,0x88,0x88,0xFE,0x88,0x88,0x88,0xFE,0x88,0x88,0x80,0x00,
0x30,0x0F,0x10,0x20,0x28,0x27,0x20,0x20,0x20,0x2F,0x20,0x20,0x20,0x00,//进2

0x00,0x00,0x00,0x00,0x82,0x64,0x18,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
0x20,0x10,0x08,0x06,0x01,0x00,0x00,0x00,0x03,0x0C,0x10,0x20,0x20,0x00,//入3

0x00,0x02,0xC2,0x02,0x02,0x02,0xFE,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
0x20,0x20,0x3F,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x00,//正0

0x00,0x00,0xFC,0x24,0x64,0xA4,0x24,0x24,0x22,0xA2,0x62,0x20,0x00,0x00,
0x20,0x18,0x07,0x20,0x10,0x09,0x06,0x06,0x09,0x10,0x10,0x20,0x20,0x00,//反1

0xC8,0xB8,0x8E,0xE8,0x88,0x40,0x48,0xC8,0x7E,0x48,0x48,0x48,0x40,0x00,
0x04,0x04,0x02,0x3F,0x02,0x00,0x09,0x09,0x11,0x3D,0x23,0x01,0x00,0x00,//转2

0x00,0xBC,0x24,0xE4,0x3C,0x20,0xF0,0x2C,0xA6,0xB4,0xAC,0xA4,0x20,0x00,
0x10,0x1F,0x10,0x0F,0x29,0x10,0x0F,0x00,0x1F,0x24,0x28,0x27,0x18,0x00,//跪0

0x02,0x02,0x02,0x02,0x02,0x02,0xE2,0x12,0x0A,0x06,0x06,0x02,0x00,0x00,
0x00,0x00,0x00,0x10,0x20,0x20,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//了1

0xFC,0x44,0x44,0x44,0xFC,0x10,0x50,0x90,0x10,0x10,0xFE,0x10,0x10,0x00,
0x1F,0x08,0x08,0x08,0x1F,0x00,0x00,0x11,0x20,0x20,0x1F,0x00,0x00,0x00,//时0

0xF8,0x02,0x02,0x04,0xF0,0x92,0x92,0x92,0xF2,0x02,0x02,0x02,0xFE,0x00,
0x3F,0x00,0x00,0x00,0x1F,0x08,0x08,0x08,0x0F,0x10,0x20,0x20,0x1F,0x00,//间1

0x42,0x44,0xCC,0x00,0xE8,0x28,0x28,0xFE,0x28,0x28,0xE8,0x08,0x00,0x00,
0x20,0x10,0x0F,0x10,0x29,0x25,0x23,0x3F,0x23,0x25,0x2D,0x20,0x20,0x00,//速0

0x00,0xFC,0x24,0x24,0x24,0xFC,0xA6,0xA6,0xFC,0x24,0x24,0x24,0x04,0x00,
0x30,0x0F,0x20,0x22,0x26,0x2A,0x12,0x12,0x2A,0x26,0x22,0x20,0x20,0x00,//度1

0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x9E,0xA0,0xA0,0x20,0x00,
0x00,0x00,0x3F,0x10,0x28,0x20,0x11,0x0A,0x04,0x0A,0x11,0x20,0x20,0x00,//设2

0x38,0x08,0x48,0x48,0x48,0x48,0xCE,0x48,0x48,0x48,0x48,0x08,0x38,0x00,
0x20,0x10,0x0F,0x10,0x20,0x20,0x3F,0x22,0x22,0x22,0x20,0x20,0x20,0x00,//定3

0x3E,0x22,0xE2,0x22,0x3E,0x90,0x88,0x56,0x24,0x54,0x8C,0x84,0x80,0x00,
0x3F,0x20,0x1F,0x11,0x11,0x00,0x3E,0x12,0x12,0x12,0x12,0x3E,0x00,0x00,//路0

0x10,0x88,0xC4,0x22,0x40,0x42,0x22,0x12,0x0A,0x16,0x22,0x60,0xC0,0x00,
0x01,0x00,0x3F,0x00,0x20,0x21,0x21,0x21,0x3F,0x21,0x21,0x21,0x20,0x00,//径1

0x40,0x48,0x48,0xFE,0x48,0x48,0x00,0xC4,0x44,0x44,0x44,0x7C,0x00,0x00,
0x30,0x0F,0x10,0x1F,0x22,0x22,0x20,0x27,0x28,0x28,0x28,0x26,0x20,0x00,//起0

0xBE,0x22,0xE2,0x22,0x3E,0x20,0xF8,0x26,0x24,0xE4,0x04,0xFC,0x00,0x00,
0x1F,0x10,0x0F,0x09,0x09,0x00,0x1F,0x21,0x21,0x25,0x24,0x23,0x38,0x00,//跑1

0x20,0x30,0xAC,0x62,0x10,0x80,0x90,0x90,0xFE,0x90,0x92,0x94,0x80,0x00,
0x12,0x13,0x0A,0x0A,0x0A,0x10,0x10,0x08,0x0F,0x14,0x22,0x22,0x30,0x00,//线2

0x80,0xFC,0x96,0xA4,0xFC,0x00,0x38,0xC8,0x0A,0x8C,0x88,0x38,0x00,0x00,
0x30,0x0F,0x22,0x24,0x1F,0x00,0x00,0x1F,0x21,0x20,0x20,0x20,0x18,0x00,//舵0

0x10,0xD0,0xFE,0x90,0x10,0x00,0xFC,0x04,0x04,0xFC,0x00,0x00,0x00,0x00,
0x03,0x00,0x3F,0x20,0x21,0x10,0x0F,0x00,0x00,0x1F,0x20,0x20,0x18,0x00,//机1

0xB0,0x8E,0xF8,0x88,0xA8,0xA4,0x64,0x24,0x3C,0x62,0xA2,0xA0,0xA0,0x00,
0x30,0x0C,0x03,0x04,0x29,0x10,0x0F,0x00,0x00,0x3F,0x00,0x01,0x00,0x00,//矫2

0x00,0x02,0xC2,0x02,0x02,0x02,0xFE,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
0x20,0x20,0x3F,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x00,//正3

0x00,0x00,0xFE,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
0x08,0x04,0x24,0x12,0x0F,0x00,0x00,0x00,0x3F,0x02,0x04,0x0C,0x04,0x00,//界0

0xE2,0x22,0x22,0x32,0xEA,0xA6,0xA2,0xE2,0x22,0x22,0x22,0xE2,0x02,0x00,
0x3F,0x20,0x20,0x20,0x3F,0x24,0x24,0x3F,0x20,0x20,0x20,0x3F,0x00,0x00,//面1

0x24,0x54,0x5C,0x44,0x7C,0x44,0x46,0x44,0x7C,0x44,0xCC,0x14,0x34,0x00,
0x00,0x00,0x07,0x05,0x05,0x05,0x05,0x15,0x25,0x25,0x25,0x1C,0x00,0x00,//弯0

0x40,0xC0,0x5E,0x52,0x52,0xD6,0x5A,0x5A,0x52,0x52,0x5E,0x40,0x40,0x00,
0x10,0x1F,0x15,0x15,0x15,0x3F,0x21,0x17,0x09,0x15,0x23,0x21,0x20,0x00,//最0

0x04,0x04,0x04,0x74,0x54,0x54,0x56,0x54,0x54,0x74,0x04,0x04,0x04,0x00,
0x00,0x3F,0x01,0x01,0x1D,0x15,0x15,0x15,0x1D,0x01,0x21,0x3F,0x00,0x00,//高1

0x20,0xF8,0x06,0x00,0xFC,0x84,0x84,0x84,0xFE,0x82,0x82,0x82,0x80,0x00,
0x00,0x3F,0x00,0x20,0x3F,0x10,0x08,0x10,0x21,0x0E,0x10,0x20,0x18,0x00,//低2

0x10,0xD0,0xFE,0x90,0x50,0x20,0x50,0x4E,0x48,0x50,0x20,0xC0,0x40,0x00,
0x03,0x00,0x3F,0x00,0x21,0x22,0x2C,0x21,0x26,0x28,0x24,0x23,0x20,0x00,//检0

0x12,0x64,0x0C,0x80,0xFC,0x04,0xF4,0x04,0xFC,0x00,0xF8,0x00,0xFE,0x00,
0x02,0x3E,0x01,0x20,0x13,0x08,0x07,0x08,0x33,0x00,0x13,0x20,0x1F,0x00,//测1

0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
0x00,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,//开2

0x00,0x00,0xFC,0x44,0x44,0x44,0x46,0x44,0x44,0x44,0x44,0x7C,0x00,0x00,
0x30,0x0C,0x03,0x00,0x3E,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x3E,0x00,//启3

0x80,0x90,0x92,0x94,0x98,0x90,0xF0,0x90,0x98,0x94,0x92,0x90,0x80,0x00,
0x20,0x20,0x20,0x10,0x08,0x06,0x01,0x06,0x08,0x10,0x10,0x20,0x20,0x00,//关4

0xF8,0x02,0x22,0x24,0xA0,0x62,0x22,0xFA,0x22,0x22,0x02,0xFE,0x00,0x00,
0x3F,0x00,0x04,0x02,0x01,0x10,0x20,0x1F,0x00,0x20,0x20,0x1F,0x00,0x00,//闭5

0x00,0x22,0x22,0xB2,0xAA,0x66,0x22,0x22,0x12,0x4A,0x82,0x02,0x00,0x00,
0x00,0x11,0x09,0x05,0x11,0x21,0x1F,0x01,0x01,0x05,0x09,0x13,0x00,0x00,//系0

0x00,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x00,0x00,
0x00,0x3F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x3F,0x00,0x00,//口1

0x08,0x30,0x80,0xFE,0x20,0x20,0x20,0x20,0xFE,0x20,0x24,0x28,0x20,0x00,
0x02,0x01,0x00,0x3F,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x30,0x10,0x00,//状0

0x84,0x84,0x84,0x44,0x24,0x54,0x8E,0x14,0x24,0x44,0x84,0x84,0x84,0x00,
0x10,0x0E,0x00,0x1E,0x20,0x22,0x24,0x28,0x20,0x18,0x02,0x04,0x18,0x00,//态1

0x00,0xC0,0x40,0x40,0x40,0x7E,0x48,0x48,0x48,0x48,0xC8,0x08,0x00,0x00,
0x20,0x1B,0x02,0x02,0x0A,0x32,0x02,0x0A,0x32,0x02,0x0B,0x10,0x20,0x00,//点0

0x80,0xA0,0xA2,0x94,0xC8,0x94,0xA2,0x80,0x00,0xF8,0x00,0x00,0xFE,0x00,
0x10,0x08,0x26,0x20,0x1F,0x00,0x02,0x0C,0x00,0x13,0x20,0x20,0x1F,0x00,//刹1

0x82,0x84,0x4C,0x20,0x80,0x60,0x18,0xD6,0x10,0x10,0x50,0x30,0x00,0x00,
0x00,0x3F,0x00,0x00,0x20,0x20,0x18,0x07,0x06,0x08,0x30,0x20,0x20,0x00,//次2

0x10,0x10,0x10,0x10,0x10,0xF2,0x92,0x94,0x90,0x90,0x90,0x10,0x10,0x00,
0x20,0x10,0x08,0x04,0x03,0x00,0x00,0x10,0x20,0x20,0x1F,0x00,0x00,0x00,//方0

0x00,0x1C,0x04,0x54,0x54,0xB4,0x9E,0xD4,0x34,0x14,0x04,0x1C,0x00,0x00,
0x00,0x24,0x25,0x15,0x0D,0x04,0x3E,0x04,0x0D,0x15,0x35,0x14,0x00,0x00,//案1

0x80,0x40,0x20,0x50,0x48,0x44,0xC2,0x44,0x48,0x50,0x20,0xC0,0x40,0x00,
0x20,0x20,0x20,0x22,0x22,0x22,0x3F,0x22,0x22,0x22,0x20,0x20,0x20,0x00,//全0

0x04,0x84,0x44,0xF4,0x9C,0x96,0x94,0x94,0x94,0x94,0xF4,0x04,0x04,0x00,
0x01,0x00,0x00,0x3F,0x04,0x04,0x04,0x14,0x24,0x24,0x1F,0x00,0x00,0x00,//有0

0x40,0x42,0x42,0x42,0x42,0xC2,0x7E,0xC2,0x42,0x42,0x42,0x42,0x40,0x00,
0x20,0x20,0x10,0x0C,0x03,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x18,0x00,//无1

0x88,0x88,0xFE,0x48,0x28,0x80,0xBE,0xE2,0xA2,0xA2,0xBE,0x80,0x00,0x00,
0x10,0x20,0x1F,0x00,0x20,0x10,0x08,0x07,0x00,0x10,0x20,0x1F,0x00,0x00,//拐2
};

/****************************************************************************
 - 功能描述：开机画面的编码
 - 参数说明：
 - 返回说明： 			
 - 示例：
 - 修改记录：
 - 注意事项：
****************************************************************************/
const uint8 startLogo[768] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xE0,0xF0,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xF8,0xFC,0x0C,0x0E,
0x0E,0x0E,0x0C,0x0F,0x7F,0xFF,0xE0,0x00,0xF0,0xF8,0x1C,0x0E,0x06,0x06,
0x86,0xC6,0xFC,0x38,0x00,0x78,0xFC,0xEC,0xCE,0xCE,0xCE,0x8E,0x0E,0x0C,
0x3C,0x38,0x10,0x18,0xFD,0xFD,0x00,0xC0,0xF0,0x78,0x1C,0x0C,0x0E,0x0E,
0x0E,0x9E,0xFC,0xF8,0x04,0xFF,0xFE,0x0E,0x0E,0x0E,0x0F,0x0E,0xFE,0xFC,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,
0xFC,0x1C,0x0C,0x0E,0x0E,0x0E,0x0E,0x0E,0x3C,0xF8,0xE0,0x00,0x0E,0x1E,
0x38,0x70,0xE0,0xC0,0xC0,0x80,0xC0,0xC0,0xE0,0xE0,0x7C,0x38,0x10,0x00,
0x00,0x00,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,
0x0C,0x08,0x18,0x18,0x18,0x0C,0x0C,0x1F,0x1F,0x10,0x01,0x07,0x0F,0x0F,
0x1B,0x1B,0x19,0x1D,0x0E,0x06,0x00,0x04,0x04,0x04,0x0D,0x0D,0x19,0x1B,
0x1F,0x1E,0x04,0x00,0x00,0x00,0x3F,0x1F,0x0C,0x0B,0x07,0x0F,0x8C,0x8C,
0x8C,0xCE,0xC7,0xFB,0x7F,0x1F,0x00,0x01,0x1F,0x1F,0x00,0x00,0x00,0x00,
0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x03,0x1F,0x1E,0x0C,0x0C,0x18,0x18,0x18,0x08,0x0F,0x07,0x01,0x00,
0x70,0x70,0x38,0x18,0x0D,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x19,0x39,0x39,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,
0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0x60,0xF6,0xF7,
0x00,0xFF,0xFE,0x80,0xC0,0xC0,0x60,0x60,0xE0,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xB8,
0x9C,0xCC,0xCE,0xC7,0xC3,0x40,0x40,0x01,0x01,0x01,0x01,0x00,0xC0,0xFC,
0x7F,0x07,0x00,0x1F,0xFF,0xF3,0x01,0x00,0x00,0x00,0xFF,0xFF,0x60,0x30,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x03,
0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x03,0x03,
0x03,0x03,0x00,0x00,0x00,0x00,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

#endif