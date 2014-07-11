/*****************************************
文 件 名：LED.c
创建日期：2012/11/14
描    述：LED128x64显示屏底层驱动
*****************************************/
#include "OLED.h"

//======================================
const byte F6x8[][6] =
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
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
	{ 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [ 91
	{ 0x00, 0x02, 0x04 ,0x08, 0x10, 0x20 },    // \92
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
//中文字符串原字
const byte F14x16_Idx[] = 
{
	"信意电子科技"
};

//中文字符串编码
const byte F14x16[] = 
{ 
  

  
0x40,0x30,0xFC,0x03,0x04,0x54,0x54,0x55,0x56,0x54,0x54,0x54,0x04,0x00,0x00,0x00,0x1F,0x00,0x00,0x1F,0x09,0x09,0x09,0x09,0x09,0x1F,0x00,0x00,/*"信",0*/

0x08,0x0A,0xEA,0xAA,0xAE,0xAA,0xAB,0xAA,0xAE,0xAA,0xEA,0x0A,0x08,0x00,0x10,0x0C,0x03,0x0E,0x12,0x12,0x16,0x1A,0x12,0x1A,0x03,0x04,0x18,0x00,/*"意",1*/

0xF8,0x48,0x48,0x48,0x48,0xFF,0x48,0x48,0x48,0x48,0xF8,0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x0F,0x12,0x12,0x12,0x12,0x13,0x10,0x0C,0x00,/*"电",2*/

0x40,0x41,0x41,0x41,0x41,0x41,0xF1,0x49,0x45,0x43,0x41,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"子",3*/

0x12,0x92,0x52,0xFF,0x51,0x91,0x80,0x92,0xA4,0x80,0xFF,0x40,0x40,0x00,0x02,0x01,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,/*"科",4*/

0x08,0x88,0xFF,0x48,0x08,0x24,0xE4,0x24,0x3F,0x24,0xA4,0x64,0x04,0x00,0x09,0x10,0x0F,0x00,0x10,0x10,0x08,0x05,0x02,0x05,0x08,0x10,0x10,0x00,/*"技",5*/


};
  





//======================================================
// 128X64I液晶底层驱动[8X16]字体库
// 设计者: powerint
// 描  述: [8X16]西文字符的字模数据 (纵向取模,字节倒序)
// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
//======================================================
const byte F8X16[]=
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// 0
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//!1
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//"2
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//#3
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$4
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//%5
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//&6
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//'7
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//(8
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//)9
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//*10
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+11
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//,12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//-13
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//.14
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,///15
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//016
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//117
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//218
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//319
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//420
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//521
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//622
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//723
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//824
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//925
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//:26
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//;27
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//<28
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//=29
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//>30
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//?31
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@32
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A33
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B34
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C35
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D36
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E37
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F38
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G39
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H40
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I41
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J42
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K43
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L44
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M45
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N46
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O47
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P48
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q49
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R50
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S51
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T52
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U53
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V54
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W55
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X56
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y57
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z58
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[59
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\60
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//]61
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^62
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_63
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//`64
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a65
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b66
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c67
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d68
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e69
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f70
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g71
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h72
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i73
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j74
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k75
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l76
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m77
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n78
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o79
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p80
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q81
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r82
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s83
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t84
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u85
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v86
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w87
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x88
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y89
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z90
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{91
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//|92
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//}93
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~94

};

//------------------------------------------------------
//              	       LED底层函数
//------------------------------------------------------

void LEDPIN_Init(void)    //初始化引脚口，请在OLED进行修改你所对应的引脚，均为普通脚输出
{
  LED_SCL_Init;
  LED_SDA_Init;
  LED_RST_Init;
  LED_DC_Init;
}
void LED_WrDat(u8 data)   //写数据函数
{
	u8 i = 8;
	//LED_CS=0;
	LED_DCH;;;
	LED_SCLL;;;  
	while (i--)
	{
		if (data & 0x80)
		{
			LED_SDAH;;;
		}
		else
		{
			LED_SDAL;;;
		}
		LED_SCLH;;; 
		asm("nop");;;     
		LED_SCLL;;;    
		data <<= 1;    
	}
	//LED_CS=1;
}
void LED_WrCmd(u8 cmd) //写命令函数
{
	u8 i = 8;
	//LED_CS = 0;
	LED_DCL;;;
	LED_SCLL;;;
	while (i--)
	{
		if (cmd & 0x80)
		{
			LED_SDAH;;;
		}
		else
		{
			LED_SDAL;;;
		}
		LED_SCLH;;;
		asm("nop");;;           
		LED_SCLL;;;    
		cmd <<= 1;   
	} 	
	//LED_CS = 1;
}
void LED_Set_Pos(byte x, byte y)//设置坐标函数
{ 
	LED_WrCmd(0xb0+y);
	LED_WrCmd(((x&0xf0)>>4)|0x10);
	LED_WrCmd((x&0x0f)|0x00); 
} 

//------------------------------------------------------
//     对全屏写入同一个字符函数 
//     如 LED_Fill(0x01);    对于某一位0为不亮 1为亮
//-------------------------------------------------------	
//                 	          共128列
//
//
//		1			1		         1
//	共     	0      			0		         0
//	 8     	0      			0		         0
//	组     	0		……   0     …………        0
//	字     	0      			0		         0
//	符     	0      			0		         0
//	即     	0      			0		         0
//	8    	0     			0		         0
//	页	1			1
//	64	0			0
//	行	.			.
//		.			.
//		.			.
//		.			.
//		0			0
//------------------------------------------------------
void LED_Fill(byte bmp_data)
{
	byte y,x;
	
	for(y=0;y<8;y++)
	{
		LED_WrCmd(0xb0+y);   //0xb0+0~7表示页0~页7?
		LED_WrCmd(0x00);       //0x00+0~16表示将128列分成16组其地址在某组中的第几列
		LED_WrCmd(0x10);	     //0x10+0~16表示将128列分成16组其地址所在第几组
		for(x=0;x<128;x++)
			LED_WrDat(bmp_data);
	}
} 



void LED_CLS(void) //清屏函数
{
	byte y,x;	
	for(y=0;y<8;y++)
	{
		LED_WrCmd(0xb0+y);
		LED_WrCmd(0x00);
		LED_WrCmd(0x10); 
		for(x=0;x<128;x++)
			LED_WrDat(0);
	}
}

void LED_DLY_ms(uint ms)
{                         
  uint16 a;
  while(ms)
  {
    a=6675;
    while(a--);
    ms--;
  }
  return;
//  time_delay_ms(ms);
}

void SetStartColumn(unsigned char d)
{
	LED_WrCmd(0x00+d%16);	// Set Lower Column Start Address for Page Addressing Mode
							// Default => 0x00
	LED_WrCmd(0x10+d/16);	// Set Higher Column Start Address for Page Addressing Mode
							// Default => 0x10
}

void SetAddressingMode(unsigned char d)
{
	LED_WrCmd(0x20);			// Set Memory Addressing Mode
	LED_WrCmd(d);			// Default => 0x02
							// 0x00 => Horizontal Addressing Mode
							// 0x01 => Vertical Addressing Mode
							// 0x02 => Page Addressing Mode
}

void SetColumnAddress(unsigned char a, unsigned char b)
{
	LED_WrCmd(0x21);			// Set Column Address
	LED_WrCmd(a);			// Default => 0x00 (Column Start Address)
	LED_WrCmd(b);			// Default => 0x7F (Column End Address)
}

void SetPageAddress(unsigned char a, unsigned char b)
{
	LED_WrCmd(0x22);			// Set Page Address
	LED_WrCmd(a);			// Default => 0x00 (Page Start Address)
	LED_WrCmd(b);			// Default => 0x07 (Page End Address)
}

void SetStartLine(unsigned char d)
{
	LED_WrCmd(0x40|d);		// Set Display Start Line
							// Default => 0x40 (0x00)
}

void SetContrastControl(unsigned char d)
{
	LED_WrCmd(0x81);			// Set Contrast Control
	LED_WrCmd(d);			// Default => 0x7F
}

void Set_Charge_Pump(unsigned char d)
{
	LED_WrCmd(0x8D);			// Set Charge Pump
	LED_WrCmd(0x10|d);		// Default => 0x10
							// 0x10 (0x00) => Disable Charge Pump
							// 0x14 (0x04) => Enable Charge Pump
}

void Set_Segment_Remap(unsigned char d)
{
	LED_WrCmd(0xA0|d);		// Set Segment Re-Map
							// Default => 0xA0
							// 0xA0 (0x00) => Column Address 0 Mapped to SEG0
							// 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

void Set_Entire_Display(unsigned char d)
{
	LED_WrCmd(0xA4|d);		// Set Entire Display On / Off
							// Default => 0xA4
							// 0xA4 (0x00) => Normal Display
							// 0xA5 (0x01) => Entire Display On
}

void Set_Inverse_Display(unsigned char d)
{
	LED_WrCmd(0xA6|d);		// Set Inverse Display On/Off
							// Default => 0xA6
							// 0xA6 (0x00) => Normal Display
							// 0xA7 (0x01) => Inverse Display On
}

void Set_Multiplex_Ratio(unsigned char d)
{
	LED_WrCmd(0xA8);			// Set Multiplex Ratio
	LED_WrCmd(d);			// Default => 0x3F (1/64 Duty)
}

void Set_Display_On_Off(unsigned char d)
{
	LED_WrCmd(0xAE|d);		// Set Display On/Off
							// Default => 0xAE
							// 0xAE (0x00) => Display Off
							// 0xAF (0x01) => Display On
}

void SetStartPage(unsigned char d)
{
	LED_WrCmd(0xB0|d);		// Set Page Start Address for Page Addressing Mode
							// Default => 0xB0 (0x00)
}

void Set_Common_Remap(unsigned char d)
{
	LED_WrCmd(0xC0|d);		// Set COM Output Scan Direction
							// Default => 0xC0
							// 0xC0 (0x00) => Scan from COM0 to 63
							// 0xC8 (0x08) => Scan from COM63 to 0
}

void Set_Display_Offset(unsigned char d)
{
	LED_WrCmd(0xD3);			// Set Display Offset
	LED_WrCmd(d);			// Default => 0x00
}

void Set_Display_Clock(unsigned char d)
{
	LED_WrCmd(0xD5);			// Set Display Clock Divide Ratio / Oscillator Frequency
	LED_WrCmd(d);			// Default => 0x80
							// D[3:0] => Display Clock Divider
							// D[7:4] => Oscillator Frequency
}

void Set_Precharge_Period(unsigned char d)
{
	LED_WrCmd(0xD9);			// Set Pre-Charge Period
	LED_WrCmd(d);			// Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
							// D[3:0] => Phase 1 Period in 1~15 Display Clocks
							// D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

void Set_Common_Config(unsigned char d)
{
	LED_WrCmd(0xDA);			// Set COM Pins Hardware Configuration
	LED_WrCmd(0x02|d);		// Default => 0x12 (0x10)
							// Alternative COM Pin Configuration
							// Disable COM Left/Right Re-Map
}

void Set_VCOMH(unsigned char d)
{
	LED_WrCmd(0xDB);			// Set VCOMH Deselect Level
	LED_WrCmd(d);			// Default => 0x20 (0.77*VCC)
}

void Set_NOP(void)
{
	LED_WrCmd(0xE3);			// Command for No Operation
}

void LED_Init(void)        
{
	u8 i;
        LEDPIN_Init();
//	LED_PORT=0X0F;
	LED_SCLH;;;		
	LED_RSTL;;;
//	for(i=0;i<100;i++)asm("nop");     //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕	
        LED_DLY_ms(50);
	LED_RSTH;;;

	Set_Display_On_Off(0x00);		  // Display Off (0x00/0x01)
	Set_Display_Clock(0x80);		  // Set Clock as 100 Frames/Sec
	Set_Multiplex_Ratio(0x3F);	  // 1/64 Duty (0x0F~0x3F)
	Set_Display_Offset(0x00);		  // Shift Mapping RAM Counter (0x00~0x3F)
	SetStartLine(0x00);			  // Set Mapping RAM Display Start Line (0x00~0x3F)
	Set_Charge_Pump(0x04);		  // Enable Embedded DC/DC Converter (0x00/0x04)
	SetAddressingMode(0x02);	  // Set Page Addressing Mode (0x00/0x01/0x02)
	Set_Segment_Remap(0x01);	  // Set SEG/Column Mapping     0x00左右反置 0x01正常
	Set_Common_Remap(0x08);	  // Set COM/Row Scan Direction 0x00上下反置 0x08正常
	Set_Common_Config(0x10);	  // Set Sequential Configuration (0x00/0x10)
	SetContrastControl(0xCF); // Set SEG Output Current
	Set_Precharge_Period(0xF1);	  // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	Set_VCOMH(0x40);			  // Set VCOM Deselect Level
	Set_Entire_Display(0x00);		  // Disable Entire Display On (0x00/0x01)
	Set_Inverse_Display(0x00);	  // Disable Inverse Display On (0x00/0x01)  
	Set_Display_On_Off(0x01);		  // Display On (0x00/0x01)
	LED_Fill(0x00);                               //初始清屏
	LED_Set_Pos(0,0); 	
} 
 
//==============================================================
//函数名：void LED_P6x8Char(byte x,byte y,byte ch);
//功能描述：显示一个6x8标准ASCII字符
//参数：x为显示的横坐标0~122，y为页范围0～7，ch要显示的字符
//返回：无
//============================================================== 
void LED_P6x8Char(byte x,byte y,byte ch)
{
	 byte c=0,i=0,j=0;     
	   
	c =ch-32;
	if(x>122)
	{
		x=0;
		y++;
	}
	LED_Set_Pos(x,y);    
	for(i=0;i<6;i++)
	{     
		LED_WrDat(F6x8[c][i]);  
	}
}

//==============================================================
//函数名：LED_P6x8Str(byte x,byte y,byte *p)
//功能描述：写入一组6x8标准ASCII字符串
//参数：x为显示的横坐标0~122，y为页范围0～7，要显示的字符串
//返回：无
//==============================================================  
void LED_P6x8Str(byte x,byte y,byte ch[])
{
	byte c=0,i=0,j=0;      
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		if(x>126)
		{
			x=0;
			y++;
		}
		LED_Set_Pos(x,y);    
		for(i=0;i<6;i++)
		{     
			LED_WrDat(F6x8[c][i]);  
		}
		x+=6;
		j++;
	}
}
//==============================================================
//函数名：LED_P8x16Str(byte x,byte y,byte *p)
//功能描述：写入一组8x16标准ASCII字符串
//参数：x为显示的横坐标0~120，y为页范围0～3，要显示的字符串
//返回：无
//==============================================================  
void LED_P8x16Str(byte x,byte y,byte ch[])
{
	byte c=0,i=0,j=0;
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		if(x>120)
		{
			x=0;
			y++;
		}
		LED_Set_Pos(x,y);    
		for(i=0;i<8;i++) 
		{
			LED_WrDat(F8X16[(c<<4)+i]);
		}
		LED_Set_Pos(x,y+1);    
		for(i=0;i<8;i++) 
		{
			LED_WrDat(F8X16[(c<<4)+i+8]);
		}
		x+=8;
		j++;
	}
}
//==============================================================
//函数名：LED_P14x16Str(byte x,byte y,byte *p)
//功能描述：写入一组14x16的中文字符串（字符串表格中需含有此字）
//参数：x为显示的横坐标0~114，y为页范围0～3，要显示的中文字符串
//返回：无
//==============================================================  
void LED_P14x16Str(byte x,byte y,byte ch[])
{
	byte wm=0,ii = 0;
	u16 adder=1; 
	
	while(ch[ii] != '\0')
	{
	  	wm = 0;
	  	adder = 1;
	  	while(F14x16_Idx[wm] > 127)
	  	{
	  		if(F14x16_Idx[wm] == ch[ii])
	  		{
	  			if(F14x16_Idx[wm + 1] == ch[ii + 1])
	  			{
	  				adder = wm * 14;
	  				break;
	  			}
	  		}
	  		wm += 2;			
	  	}
	  	if(x>114)
	  	{
	  		x=0;
	  		y++;
	  	}
	  	if(adder != 1)// 显示汉字					
	  	{
	  		LED_Set_Pos(x , y);
	  		for(wm = 0;wm < 14;wm++)               
	  		{
	  			LED_WrDat(F14x16[adder]);	
	  			adder++;
	  		}      
	  		LED_Set_Pos(x,y + 1); 
	  		for(wm = 0;wm < 14;wm++)          
	  		{
	  			LED_WrDat(F14x16[adder]);
	  			adder++;
	  		}   
	  		ii += 2;		
	  	}
	  	else			  //显示空白字符			
	  	{
	  		LED_Set_Pos(x,y);
	  		for(wm = 0;wm < 14;wm++)
	  		{
	  			LED_WrDat(0);
	  		}
	  		LED_Set_Pos(x,y + 1);
	  		for(wm = 0;wm < 14;wm++)
	  		{   		
	  			LED_WrDat(0);	
	  		}
	  		ii++;
	  	}
	  	x += 14;

	}
}
//==============================================================
//函数名：LED_PXx16MixStr(byte x,byte y,byte *p)
//功能描述：输出14x16汉字和字符混合字符串 （字符串表格中需含有此字）?
//参数：x为显示的横坐标0~114，y为页范围0～3，要显示的中文字符串
//返回：无
//==============================================================  
void LED_PXx16MixStr(byte x, byte y, byte ch[])
{
	byte ch2[3];
	byte ii=0;        
	while(ch[ii] != '\0')
	{
		if(ch[ii] > 127)
		{
			ch2[0] = ch[ii];
	 		ch2[1] = ch[ii + 1];
			ch2[2] = '\0';			//汉字为两个字节
			LED_P14x16Str(x , y, ch2);	//显示汉字
			x += 14;
			ii += 2;
		}
		else
		{
			ch2[0] = ch[ii];	
			ch2[1] = '\0';			//字母占一个字节
			LED_P8x16Str(x , y , ch2);	//显示字母
			x += 8;
			ii+= 1;
		}
	}
} 

//==============================================================
//函数名：  void LED_PrintBMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
//功能描述：显示BMP图片  大小为(x1-x0+1) × ((y1-y0+1)*8)
//		       BMP图片先取页码y为0以8位(低位在上)为单位取满(x1-x0+1)列
//		      再取页码y为1以8位(低位在上)为单位取满(x1-x0+1)列以此类推
//参数：x的范围为0～127，y为页的范围0～7
//返回：无
//==============================================================
void LED_PrintBMP(byte x0,byte y0,byte x1,byte y1,byte bmp[])
{ 	
	u16 ii=0;
	byte x,y;
	for(y=y0;y<=y1;y++)
	{
		LED_Set_Pos(x0,y);				
		for(x=x0;x<x1;x++)
		{      
			LED_WrDat(bmp[ii++]);	    	
		}
	}
}
//==============================================================
//函数名：  void LED_PrintValue(uchar x, uchar y, char data);
//功能描述：将一个char型数转换成3位数进行显示
//参数：x的范围为0～122，y为页的范围0～7，data为需要转化显示的数值
//返回：无
//==============================================================
void LED_PrintValueC(u8 x, u8 y, char data)
{
	u8 i,j,k;
	if(data < 0)
	{
		LED_P6x8Char(x,y,'-');
		data = - data;	
	}
	else
	{
		LED_P6x8Char(x,y,'+');
	}
	i = data/100;
	j = (data%100)/10;
	k = data%10;
	LED_P6x8Char(x+6,y,i+48);
	LED_P6x8Char(x+12,y,j+48);
	LED_P6x8Char(x+18,y,k+48);		
}

//==============================================================
//函数名：  void LED_PrintValueI(uchar x, uchar y, int data);
//功能描述：将一个int型数转换成5位数进行显示
//参数：x的范围为0～120，y为页的范围0～7，data为需要转化显示的数值
//返回：无
//==============================================================
void LED_PrintValueI(u8 x, u8 y, int data)
{
	u8 i,j,k,l,m;  
	if(data < 0)
	{
		LED_P6x8Char(x,y,'-');
		data = - data;	
	}
	else
	{
		LED_P6x8Char(x,y,'+');
	}
	
	l  = data/10000;
	m= (data%10000)/1000;
	i = (data%1000)/100;
	j = (data%100)/10;
	k = data%10;
	LED_P6x8Char(x+6,y,l+48);
	LED_P6x8Char(x+12,y,m+48);
	LED_P6x8Char(x+18,y,i+48);
	LED_P6x8Char(x+24,y,j+48);
	LED_P6x8Char(x+30,y,k+48);		
}

 void LED_PrintValueFP(u8 x, u8 y, uint data, u8 num)
 {
 	u8 m,i,j,k;  	
 	LED_P6x8Char(x, y, '.');
	m= data/1000;
	i = (data%1000)/100;
	j = (data%100)/10;
	k = data%10;
	switch(num)
	{
		case 1:  	LED_P6x8Char(x+6,y,k+48);
				break;
		case 2:  	LED_P6x8Char(x+6,y,j+48);
				LED_P6x8Char(x+12,y,k+48);
				break;
		case 3:	LED_P6x8Char(x+6,y,i+48);
				LED_P6x8Char(x+12,y,j+48);
				LED_P6x8Char(x+18,y,k+48);
				break;
		case 4: 	LED_P6x8Char(x+6,y,m+48);
				LED_P6x8Char(x+12,y,i+48);
				LED_P6x8Char(x+18,y,j+48);
				LED_P6x8Char(x+24,y,k+48);
				break;	
	}
 }

//==============================================================
//函数名：   void LED_PrintValueF(uchar x, uchar y, float data, uchar num);
//功能描述：将一个float型数转换成整数部分5位带小数和符号的数据并进行显示
//参数：x的范围为0～62，y为页的范围0～7，data为需要转化显示的数值整数部分最多位5位  num表示保留的小数位0~4
//返回：无
//==============================================================
 void LED_PrintValueF(u8 x, u8 y, float data, u8 num)
 {
 	u8 l,m,i,j,k;  //万千百十个
 	u8 databiti = 6; //整数位数
 	uint tempdataui = 0;
  	int tempdataii = (int)data; //整数部分
 	long int tempdatalp = (long int)((data - (int)data)*10000); //取小数位后4位
 	
 	//整数部分显示
 	if(data < 0.0000001)  LED_P6x8Char(x, y,'-'); 
 	else LED_P6x8Char(x, y,'+');
	if(tempdataii < 0)tempdataii = - tempdataii;  //去掉整数部分负号
	tempdataui = tempdataii;
 	l  = tempdataui/10000;
	m= (tempdataui%10000)/1000;
	i = (tempdataui%1000)/100;
	j = (tempdataui%100)/10;
	k = tempdataui%10;
 	if (l != 0)  //五位
 	{
 		LED_P6x8Char(x+6,y,l+48);
 		LED_P6x8Char(x+12,y,m+48);
		LED_P6x8Char(x+18,y,i+48);
		LED_P6x8Char(x+24,y,j+48);
		LED_P6x8Char(x+30,y,k+48);
 	}
 	else if(m != 0) //四位
 	{
 		databiti = 5;
 		LED_P6x8Char(x+6,y,m+48);
 		LED_P6x8Char(x+12,y,i+48);
		LED_P6x8Char(x+18,y,j+48);
		LED_P6x8Char(x+24,y,k+48);
 	}
  	else if(i != 0) //三位
  	{
  		databiti = 4;
  	 	LED_P6x8Char(x+6,y,i+48);
 		LED_P6x8Char(x+12,y,j+48);
		LED_P6x8Char(x+18,y,k+48);
  	}
  	else if(j != 0) //两位
  	{
    		databiti = 3;	
  		LED_P6x8Char(x+6,y,j+48);
 		LED_P6x8Char(x+12,y,k+48);
  	}
	else 	
	{
		databiti = 2;
		LED_P6x8Char(x+6,y,k+48);
	}	
 	if(tempdatalp < 0)tempdatalp = - tempdatalp;	//去掉小数部分负号
	switch(num)
	{
		case 0: break;
		case 1:  LED_PrintValueFP(x + databiti * 6, y, (unsigned int)(tempdatalp / 1000),num);break;
		case 2:  LED_PrintValueFP(x + databiti * 6, y, (unsigned int)(tempdatalp / 100),num);break;
		case 3:  LED_PrintValueFP(x + databiti * 6, y, (unsigned int)(tempdatalp / 10),num);break;
		case 4:  LED_PrintValueFP(x + databiti * 6, y, (unsigned int)(tempdatalp),num);break;					
	}
 }

 void LED_Cursor(u8 cursor_column, u8 cursor_row)
 {	
 	if(cursor_row != 0) //光标出现
 	{
 		if(cursor_column == 1) LED_Set_Pos(0, cursor_row + 2);
 		else  LED_Set_Pos(80 + (cursor_column - 2)*6, cursor_row + 2);
 		LED_WrDat(0xFF);
 		LED_WrDat(0xFF);
 		LED_WrDat(0xFF);
 		LED_WrDat(0xFF);
 		LED_WrDat(0xFF);
 		LED_WrDat(0xFF);					 
 	}
 }
 
