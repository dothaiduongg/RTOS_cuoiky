/*****************************************************************/
/*           LCD12864-ST7920-Demo with ATMega32                  */
/*  ************************************************************ */
/*  Mikrocontroller:  ATMEL AVR ATmega32, 8 MHz                  */
/*                                                               */
/*  Compiler:         GCC (GNU AVR C-Compiler)                   */
/*  Author:           Peter Rachow (DK7IH)                       */
/*  Letzte Aenderung: 2018-12-25                                 */
/*****************************************************************/

// O U T P U T for LCD 

//Connection LCD to uC:
//LCD-Data: PD0..PD7
//RS:       PC0
//RW:       PC1
//E:        PC2
//RST       PC3

//#define F_CPU 8000000

u8 lx,ly;
#define FONTHEIGHT 8
#define font_rong 5
#define font_cao 7

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <util/delay.h>

static const char Alpha1[] = {
	0x00,0x00,0x00,0x00,0x00,  // 20 space
	0x00,0x00,0x5f,0x00,0x00,  // 21 !
	0x00,0x07,0x00,0x07,0x00,  // 22 "
	0x14,0x7f,0x14,0x7f,0x14,  // 23 #
	0x24,0x2a,0x7f,0x2a,0x12,  // 24 $
	0x23,0x13,0x08,0x64,0x62,  // 25 %
	0x36,0x49,0x55,0x22,0x50,  // 26 &
	0x00,0x05,0x03,0x00,0x00,  // 27 '
	0x00,0x1c,0x22,0x41,0x00,  // 28 (
	0x00,0x41,0x22,0x1c,0x00,  // 29 )
	0x14,0x08,0x3e,0x08,0x14,  // 2a *
	0x08,0x08,0x3e,0x08,0x08,  // 2b +
	0x00,0x50,0x30,0x00,0x00,  // 2c ,
	0x08,0x08,0x08,0x08,0x08,  // 2d -
	0x00,0x60,0x60,0x00,0x00,  // 2e .
	0x20,0x10,0x08,0x04,0x02,  // 2f /
	0x3e,0x51,0x49,0x45,0x3e,  // 30 0
	0x00,0x42,0x7f,0x40,0x00,  // 31 1
	0x42,0x61,0x51,0x49,0x46,  // 32 2
	0x21,0x41,0x45,0x4b,0x31,  // 33 3
	0x18,0x14,0x12,0x7f,0x10,  // 34 4
	0x27,0x45,0x45,0x45,0x39,  // 35 5
	0x3c,0x4a,0x49,0x49,0x30,  // 36 6
	0x01,0x71,0x09,0x05,0x03,  // 37 7
	0x36,0x49,0x49,0x49,0x36,  // 38 8
	0x06,0x49,0x49,0x29,0x1e,  // 39 9
	0x00,0x36,0x36,0x00,0x00,  // 3a :
	0x00,0x56,0x36,0x00,0x00,  // 3b ;
	0x08,0x14,0x22,0x41,0x00,  // 3c <
	0x14,0x14,0x14,0x14,0x14,  // 3d =
	0x00,0x41,0x22,0x14,0x08,  // 3e >
	0x02,0x01,0x51,0x09,0x06,  // 3f ?
	0x32,0x49,0x79,0x41,0x3e,  // 40 @
	0x7e,0x11,0x11,0x11,0x7e,  // 41 A
	0x7f,0x49,0x49,0x49,0x36,  // 42 B
	0x3e,0x41,0x41,0x41,0x22,  // 43 C
	0x7f,0x41,0x41,0x22,0x1c,  // 44 D
	0x7f,0x49,0x49,0x49,0x41,  // 45 E
	0x7f,0x09,0x09,0x09,0x01,  // 46 F
	0x3e,0x41,0x49,0x49,0x7a,  // 47 G
	0x7f,0x08,0x08,0x08,0x7f,  // 48 H
	0x00,0x41,0x7f,0x41,0x00,  // 49 I
	0x20,0x40,0x41,0x3f,0x01,  // 4a J
	0x7f,0x08,0x14,0x22,0x41,  // 4b K
	0x7f,0x40,0x40,0x40,0x40,  // 4c L
	0x7f,0x02,0x0c,0x02,0x7f,  // 4d M
	0x7f,0x04,0x08,0x10,0x7f,  // 4e N
	0x3e,0x41,0x41,0x41,0x3e,  // 4f O
	0x7f,0x09,0x09,0x09,0x06,  // 50 P
0x3e,0x41,0x51,0x21,0x5e}; // 51 Q

static const char Alpha2[] = {
	0x7f,0x09,0x19,0x29,0x46,
	0x46,0x49,0x49,0x49,0x31,  // 53 S
	0x01,0x01,0x7f,0x01,0x01,  // 54 T
	0x3f,0x40,0x40,0x40,0x3f,  // 55 U
	0x1f,0x20,0x40,0x20,0x1f,  // 56 V
	0x3f,0x40,0x38,0x40,0x3f,  // 57 W
	0x63,0x14,0x08,0x14,0x63,  // 58 X
	0x07,0x08,0x70,0x08,0x07,  // 59 Y
	0x61,0x51,0x49,0x45,0x43,  // 5a Z
	0x00,0x7f,0x41,0x41,0x00,  // 5b [
	0x02,0x04,0x08,0x10,0x20,  // 5c 55
	0x00,0x41,0x41,0x7f,0x00,  // 5d ]
	0x04,0x02,0x01,0x02,0x04,  // 5e ^
	0x40,0x40,0x40,0x40,0x40,  // 5f _
	0x00,0x01,0x02,0x04,0x00,  // 60 `
	0x20,0x54,0x54,0x54,0x78,  // 61 a
	0x7f,0x48,0x44,0x44,0x38,  // 62 b
	0x38,0x44,0x44,0x44,0x20,  // 63 c
	0x38,0x44,0x44,0x48,0x7f,  // 64 d
	0x38,0x54,0x54,0x54,0x18,  // 65 e
	0x08,0x7e,0x09,0x01,0x02,  // 66 f
	0x0c,0x52,0x52,0x52,0x3e,  // 67 g
	0x7f,0x08,0x04,0x04,0x78,  // 68 h
	0x00,0x44,0x7d,0x40,0x00,  // 69 i
	0x20,0x40,0x44,0x3d,0x00,  // 6a j
	0x7f,0x10,0x28,0x44,0x00,  // 6b k
	0x00,0x41,0x7f,0x40,0x00,  // 6c l
	0x7c,0x04,0x18,0x04,0x78,  // 6d m
	0x7c,0x08,0x04,0x04,0x78,  // 6e n
	0x38,0x44,0x44,0x44,0x38,  // 6f o
	0x7c,0x14,0x14,0x14,0x08,  // 70 p
	0x08,0x14,0x14,0x18,0x7c,  // 71 q
	0x7c,0x08,0x04,0x04,0x08,  // 72 r
	0x48,0x54,0x54,0x54,0x20,  // 73 s
	0x04,0x3f,0x44,0x40,0x20,  // 74 t
	0x3c,0x40,0x40,0x20,0x7c,  // 75 u
	0x1c,0x20,0x40,0x20,0x1c,  // 76 v
	0x3c,0x40,0x30,0x40,0x3c,  // 77 w
	0x44,0x28,0x10,0x28,0x44,  // 78 x
	0x0c,0x50,0x50,0x50,0x3c,  // 79 y
	0x44,0x64,0x54,0x4c,0x44,  // 7a z
	0x00,0x08,0x36,0x41,0x00,  // 7b {
		0x00,0x00,0x7f,0x00,0x00,  // 7c |
	0x00,0x41,0x36,0x08,0x00,  // 7d }
	0x10,0x08,0x08,0x10,0x08,  // 7e ~
0x78,0x46,0x41,0x46,0x78}; // 7f &brvbar;

//Font for graphics LCD 5x8
u8 font[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x00
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x01
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x02
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x03
0x00,0x04,0x0E,0x1F,0x1F,0x0E,0x04,0x00,	// 0x04
0x04,0x0E,0x0E,0x04,0x1F,0x1F,0x04,0x00,	// 0x05
0x00,0x04,0x0E,0x1F,0x1F,0x04,0x0E,0x00,	// 0x06
0x0E,0x1F,0x15,0x1F,0x11,0x1F,0x0E,0x00,	// 0x07
0x0E,0x11,0x1B,0x11,0x15,0x11,0x0E,0x00,	// 0x08
0x00,0x0A,0x1F,0x1F,0x1F,0x0E,0x04,0x00,	// 0x09
0x0E,0x11,0x1B,0x11,0x15,0x11,0x0E,0x00,	// 0x0A
0x00,0x07,0x03,0x0D,0x12,0x12,0x0C,0x00,	// 0x0B
0x0E,0x11,0x11,0x0E,0x04,0x0E,0x04,0x00,	// 0x0C
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x0D
0x03,0x0D,0x0B,0x0D,0x0B,0x1B,0x18,0x00,	// 0x0E
0x00,0x15,0x0E,0x1B,0x0E,0x15,0x00,0x00,	// 0x0F
0x08,0x0C,0x0E,0x0F,0x0E,0x0C,0x08,0x00,	// 0x10
0x02,0x06,0x0E,0x1E,0x0E,0x06,0x02,0x00,	// 0x11
0x04,0x0E,0x1F,0x04,0x1F,0x0E,0x04,0x00,	// 0x12
0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0x0A,0x00,	// 0x13
0x0F,0x15,0x15,0x0D,0x05,0x05,0x05,0x00,	// 0x14
0x0E,0x11,0x0C,0x0A,0x06,0x11,0x0E,0x00,	// 0x15
0x00,0x00,0x00,0x00,0x00,0x1E,0x1E,0x00,	// 0x16
0x04,0x0E,0x1F,0x04,0x1F,0x0E,0x04,0x0E,	// 0x17
0x04,0x0E,0x1F,0x04,0x04,0x04,0x04,0x00,	// 0x18
0x04,0x04,0x04,0x04,0x1F,0x0E,0x04,0x00,	// 0x19
0x00,0x04,0x06,0x1F,0x06,0x04,0x00,0x00,	// 0x1A
0x00,0x04,0x0C,0x1F,0x0C,0x04,0x00,0x00,	// 0x1B
0x00,0x00,0x00,0x10,0x10,0x10,0x1F,0x00,	// 0x1C
0x00,0x0A,0x0A,0x1F,0x0A,0x0A,0x00,0x00,	// 0x1D
0x04,0x04,0x0E,0x0E,0x1F,0x1F,0x00,0x00,	// 0x1E
0x1F,0x1F,0x0E,0x0E,0x04,0x04,0x00,0x00,	// 0x1F
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x20
0x04,0x0E,0x0E,0x04,0x04,0x00,0x04,0x00,	// 0x21
0x1B,0x1B,0x12,0x00,0x00,0x00,0x00,0x00,	// 0x22
0x00,0x0A,0x1F,0x0A,0x0A,0x1F,0x0A,0x00,	// 0x23
0x08,0x0E,0x10,0x0C,0x02,0x1C,0x04,0x00,	// 0x24
0x19,0x19,0x02,0x04,0x08,0x13,0x13,0x00,	// 0x25
0x08,0x14,0x14,0x08,0x15,0x12,0x0D,0x00,	// 0x26
0x0C,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,	// 0x27
0x04,0x08,0x08,0x08,0x08,0x08,0x04,0x00,	// 0x28
0x08,0x04,0x04,0x04,0x04,0x04,0x08,0x00,	// 0x29
0x00,0x0A,0x0E,0x1F,0x0E,0x0A,0x00,0x00,	// 0x2A
0x00,0x04,0x04,0x1F,0x04,0x04,0x00,0x00,	// 0x2B
0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x08,	// 0x2C
0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,	// 0x2D
0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,	// 0x2E
0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00,	// 0x2F
0x0E,0x11,0x13,0x15,0x19,0x11,0x0E,0x00,	// 0x30
0x04,0x0C,0x04,0x04,0x04,0x04,0x0E,0x00,	// 0x31
0x0E,0x11,0x01,0x06,0x08,0x10,0x1F,0x00,	// 0x32
0x0E,0x11,0x01,0x0E,0x01,0x11,0x0E,0x00,	// 0x33
0x02,0x06,0x0A,0x12,0x1F,0x02,0x02,0x00,	// 0x34
0x1F,0x10,0x10,0x1E,0x01,0x11,0x0E,0x00,	// 0x35
0x06,0x08,0x10,0x1E,0x11,0x11,0x0E,0x00,	// 0x36
0x1F,0x01,0x02,0x04,0x08,0x08,0x08,0x00,	// 0x37
0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E,0x00,	// 0x38
0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C,0x00,	// 0x39
0x00,0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,	// 0x3A
0x00,0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x08,	// 0x3B
0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00,	// 0x3C
0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,	// 0x3D
0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00,	// 0x3E
0x0E,0x11,0x01,0x06,0x04,0x00,0x04,0x00,	// 0x3F
0x0E,0x11,0x17,0x15,0x17,0x10,0x0E,0x00,	// 0x40
0x0E,0x11,0x11,0x11,0x1F,0x11,0x11,0x00,	// 0x41
0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E,0x00,	// 0x42
0x0E,0x11,0x10,0x10,0x10,0x11,0x0E,0x00,	// 0x43
0x1E,0x11,0x11,0x11,0x11,0x11,0x1E,0x00,	// 0x44
0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F,0x00,	// 0x45
0x1F,0x10,0x10,0x1E,0x10,0x10,0x10,0x00,	// 0x46
0x0E,0x11,0x10,0x17,0x11,0x11,0x0F,0x00,	// 0x47
0x11,0x11,0x11,0x1F,0x11,0x11,0x11,0x00,	// 0x48
0x0E,0x04,0x04,0x04,0x04,0x04,0x0E,0x00,	// 0x49
0x01,0x01,0x01,0x01,0x11,0x11,0x0E,0x00,	// 0x4A
0x11,0x12,0x14,0x18,0x14,0x12,0x11,0x00,	// 0x4B
0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x00,	// 0x4C
0x11,0x1B,0x15,0x11,0x11,0x11,0x11,0x00,	// 0x4D
0x11,0x19,0x15,0x13,0x11,0x11,0x11,0x00,	// 0x4E
0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,0x00,	// 0x4F
0x1E,0x11,0x11,0x1E,0x10,0x10,0x10,0x00,	// 0x50
0x0E,0x11,0x11,0x11,0x15,0x12,0x0D,0x00,	// 0x51
0x1E,0x11,0x11,0x1E,0x12,0x11,0x11,0x00,	// 0x52
0x0E,0x11,0x10,0x0E,0x01,0x11,0x0E,0x00,	// 0x53
0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x00,	// 0x54
0x11,0x11,0x11,0x11,0x11,0x11,0x0E,0x00,	// 0x55
0x11,0x11,0x11,0x11,0x11,0x0A,0x04,0x00,	// 0x56
0x11,0x11,0x15,0x15,0x15,0x15,0x0A,0x00,	// 0x57
0x11,0x11,0x0A,0x04,0x0A,0x11,0x11,0x00,	// 0x58
0x11,0x11,0x11,0x0A,0x04,0x04,0x04,0x00,	// 0x59
0x1E,0x02,0x04,0x08,0x10,0x10,0x1E,0x00,	// 0x5A
0x0E,0x08,0x08,0x08,0x08,0x08,0x0E,0x00,	// 0x5B
0x00,0x10,0x08,0x04,0x02,0x01,0x00,0x00,	// 0x5C
0x0E,0x02,0x02,0x02,0x02,0x02,0x0E,0x00,	// 0x5D
0x04,0x0A,0x11,0x00,0x00,0x00,0x00,0x00,	// 0x5E
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,	// 0x5F
0x0C,0x0C,0x04,0x00,0x00,0x00,0x00,0x00,	// 0x60
0x00,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0x61
0x10,0x10,0x1E,0x11,0x11,0x11,0x1E,0x00,	// 0x62
0x00,0x00,0x0E,0x11,0x10,0x11,0x0E,0x00,	// 0x63
0x01,0x01,0x0F,0x11,0x11,0x11,0x0F,0x00,	// 0x64
0x00,0x00,0x0E,0x11,0x1E,0x10,0x0E,0x00,	// 0x65
0x06,0x08,0x08,0x1E,0x08,0x08,0x08,0x00,	// 0x66
0x00,0x00,0x0F,0x11,0x11,0x0F,0x01,0x0E,	// 0x67
0x10,0x10,0x1C,0x12,0x12,0x12,0x12,0x00,	// 0x68
0x04,0x00,0x04,0x04,0x04,0x04,0x06,0x00,	// 0x69
0x02,0x00,0x06,0x02,0x02,0x02,0x12,0x0C,	// 0x6A
0x10,0x10,0x12,0x14,0x18,0x14,0x12,0x00,	// 0x6B
0x04,0x04,0x04,0x04,0x04,0x04,0x06,0x00,	// 0x6C
0x00,0x00,0x1A,0x15,0x15,0x11,0x11,0x00,	// 0x6D
0x00,0x00,0x1C,0x12,0x12,0x12,0x12,0x00,	// 0x6E
0x00,0x00,0x0E,0x11,0x11,0x11,0x0E,0x00,	// 0x6F
0x00,0x00,0x1E,0x11,0x11,0x11,0x1E,0x10,	// 0x70
0x00,0x00,0x0F,0x11,0x11,0x11,0x0F,0x01,	// 0x71
0x00,0x00,0x16,0x09,0x08,0x08,0x1C,0x00,	// 0x72
0x00,0x00,0x0E,0x10,0x0E,0x01,0x0E,0x00,	// 0x73
0x00,0x08,0x1E,0x08,0x08,0x0A,0x04,0x00,	// 0x74
0x00,0x00,0x12,0x12,0x12,0x16,0x0A,0x00,	// 0x75
0x00,0x00,0x11,0x11,0x11,0x0A,0x04,0x00,	// 0x76
0x00,0x00,0x11,0x11,0x15,0x1F,0x0A,0x00,	// 0x77
0x00,0x00,0x12,0x12,0x0C,0x12,0x12,0x00,	// 0x78
0x00,0x00,0x12,0x12,0x12,0x0E,0x04,0x18,	// 0x79
0x00,0x00,0x1E,0x02,0x0C,0x10,0x1E,0x00,	// 0x7A
0x06,0x08,0x08,0x18,0x08,0x08,0x06,0x00,	// 0x7B
0x04,0x04,0x04,0x00,0x04,0x04,0x04,0x00,	// 0x7C
0x0C,0x02,0x02,0x03,0x02,0x02,0x0C,0x00,	// 0x7D
0x0A,0x14,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x7E
0x04,0x0E,0x1B,0x11,0x11,0x1F,0x00,0x00,	// 0x7F
0x0E,0x11,0x10,0x10,0x11,0x0E,0x04,0x0C,	// 0x80
/* 

//If you operate a microcontroller with more memory space 
//than an ATmega32 you can also use the following 127 characters!

0x12,0x00,0x12,0x12,0x12,0x16,0x0A,0x00,	// 0x81
0x03,0x00,0x0E,0x11,0x1E,0x10,0x0E,0x00,	// 0x82
0x0E,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0x83
0x0A,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0x84
0x0C,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0x85
0x0E,0x0A,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0x86
0x00,0x0E,0x11,0x10,0x11,0x0E,0x04,0x0C,	// 0x87
0x0E,0x00,0x0E,0x11,0x1E,0x10,0x0E,0x00,	// 0x88
0x0A,0x00,0x0E,0x11,0x1E,0x10,0x0E,0x00,	// 0x89
0x0C,0x00,0x0E,0x11,0x1E,0x10,0x0E,0x00,	// 0x8A
0x0A,0x00,0x04,0x04,0x04,0x04,0x06,0x00,	// 0x8B
0x0E,0x00,0x04,0x04,0x04,0x04,0x06,0x00,	// 0x8C
0x08,0x00,0x04,0x04,0x04,0x04,0x06,0x00,	// 0x8D
0x0A,0x00,0x04,0x0A,0x11,0x1F,0x11,0x00,	// 0x8E
0x0E,0x0A,0x0E,0x1B,0x11,0x1F,0x11,0x00,	// 0x8F
0x03,0x00,0x1F,0x10,0x1E,0x10,0x1F,0x00,	// 0x90
0x00,0x00,0x1E,0x05,0x1F,0x14,0x0F,0x00,	// 0x91
0x0F,0x14,0x14,0x1F,0x14,0x14,0x17,0x00,	// 0x92
0x0E,0x00,0x0C,0x12,0x12,0x12,0x0C,0x00,	// 0x93
0x0A,0x00,0x0C,0x12,0x12,0x12,0x0C,0x00,	// 0x94
0x18,0x00,0x0C,0x12,0x12,0x12,0x0C,0x00,	// 0x95
0x0E,0x00,0x12,0x12,0x12,0x16,0x0A,0x00,	// 0x96
0x18,0x00,0x12,0x12,0x12,0x16,0x0A,0x00,	// 0x97
0x0A,0x00,0x12,0x12,0x12,0x0E,0x04,0x18,	// 0x98
0x12,0x0C,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0x99
0x0A,0x00,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0x9A
0x00,0x00,0x01,0x0E,0x16,0x1A,0x1C,0x20,	// 0x9B
0x06,0x09,0x08,0x1E,0x08,0x09,0x17,0x00,	// 0x9C
0x0F,0x13,0x15,0x15,0x15,0x19,0x1E,0x00,	// 0x9D
0x00,0x11,0x0A,0x04,0x0A,0x11,0x00,0x00,	// 0x9E
0x02,0x05,0x04,0x0E,0x04,0x04,0x14,0x08,	// 0x9F
0x06,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0xA0
0x06,0x00,0x04,0x04,0x04,0x04,0x06,0x00,	// 0xA1
0x06,0x00,0x0C,0x12,0x12,0x12,0x0C,0x00,	// 0xA2
0x06,0x00,0x12,0x12,0x12,0x16,0x0A,0x00,	// 0xA3
0x0A,0x14,0x00,0x1C,0x12,0x12,0x12,0x00,	// 0xA4
0x0A,0x14,0x00,0x12,0x1A,0x16,0x12,0x00,	// 0xA5
0x0E,0x01,0x0F,0x11,0x0F,0x00,0x0F,0x00,	// 0xA6
0x0C,0x12,0x12,0x12,0x0C,0x00,0x1E,0x00,	// 0xA7
0x04,0x00,0x04,0x0C,0x10,0x11,0x0E,0x00,	// 0xA8
0x1E,0x25,0x2B,0x2D,0x2B,0x21,0x1E,0x00,	// 0xA9
0x00,0x00,0x3F,0x01,0x01,0x00,0x00,0x00,	// 0xAA
0x10,0x12,0x14,0x0E,0x11,0x02,0x07,0x00,	// 0xAB
0x10,0x12,0x14,0x0B,0x15,0x07,0x01,0x00,	// 0xAC
0x04,0x00,0x04,0x04,0x0E,0x0E,0x04,0x00,	// 0xAD
0x00,0x00,0x09,0x12,0x09,0x00,0x00,0x00,	// 0xAE
0x00,0x00,0x12,0x09,0x12,0x00,0x00,0x00,	// 0xAF
0x15,0x00,0x2A,0x00,0x15,0x00,0x2A,0x00,	// 0xB0
0x15,0x2A,0x15,0x2A,0x15,0x2A,0x15,0x2A,	// 0xB1
0x2A,0x3F,0x15,0x3F,0x2A,0x3F,0x15,0x3F,	// 0xB2
0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,	// 0xB3
0x04,0x04,0x04,0x3C,0x04,0x04,0x04,0x04,	// 0xB4
0x06,0x00,0x04,0x0A,0x11,0x1F,0x11,0x00,	// 0xB5
0x0E,0x00,0x04,0x0A,0x11,0x1F,0x11,0x00,	// 0xB6
0x0C,0x00,0x04,0x0A,0x11,0x1F,0x11,0x00,	// 0xB7
0x1E,0x21,0x2D,0x29,0x2D,0x21,0x1E,0x00,	// 0xB8
0x14,0x34,0x04,0x34,0x14,0x14,0x14,0x14,	// 0xB9
0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,	// 0xBA
0x00,0x3C,0x04,0x34,0x14,0x14,0x14,0x14,	// 0xBB
0x14,0x34,0x04,0x3C,0x00,0x00,0x00,0x00,	// 0xBC
0x00,0x04,0x0E,0x10,0x10,0x0E,0x04,0x00,	// 0xBD
0x11,0x0A,0x04,0x1F,0x04,0x1F,0x04,0x00,	// 0xBE
0x00,0x00,0x00,0x3C,0x04,0x04,0x04,0x04,	// 0xBF
0x04,0x04,0x04,0x07,0x00,0x00,0x00,0x00,	// 0xC0
0x04,0x04,0x04,0x3F,0x00,0x00,0x00,0x00,	// 0xC1
0x00,0x00,0x00,0x3F,0x04,0x04,0x04,0x04,	// 0xC2
0x04,0x04,0x04,0x07,0x04,0x04,0x04,0x04,	// 0xC3
0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,	// 0xC4
0x04,0x04,0x04,0x3F,0x04,0x04,0x04,0x04,	// 0xC5
0x05,0x0A,0x0E,0x01,0x0F,0x11,0x0F,0x00,	// 0xC6
0x05,0x0A,0x04,0x0A,0x11,0x1F,0x11,0x00,	// 0xC7
0x14,0x17,0x10,0x1F,0x00,0x00,0x00,0x00,	// 0xC8
0x00,0x1F,0x10,0x17,0x14,0x14,0x14,0x14,	// 0xC9
0x14,0x37,0x00,0x3F,0x00,0x00,0x00,0x00,	// 0xCA
0x00,0x3F,0x00,0x37,0x14,0x14,0x14,0x14,	// 0xCB
0x14,0x17,0x10,0x17,0x14,0x14,0x14,0x14,	// 0xCC
0x00,0x3F,0x00,0x3F,0x00,0x00,0x00,0x00,	// 0xCD
0x14,0x37,0x00,0x37,0x14,0x14,0x14,0x14,	// 0xCE
0x11,0x0E,0x11,0x11,0x11,0x0E,0x11,0x00,	// 0xCF
0x0C,0x10,0x08,0x04,0x0E,0x12,0x0C,0x00,	// 0xD0
0x0E,0x09,0x09,0x1D,0x09,0x09,0x0E,0x00,	// 0xD1
0x0E,0x00,0x1F,0x10,0x1E,0x10,0x1F,0x00,	// 0xD2
0x0A,0x00,0x1F,0x10,0x1E,0x10,0x1F,0x00,	// 0xD3
0x0C,0x00,0x1F,0x10,0x1E,0x10,0x1F,0x00,	// 0xD4
0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,	// 0xD5
0x06,0x00,0x0E,0x04,0x04,0x04,0x0E,0x00,	// 0xD6
0x0E,0x00,0x0E,0x04,0x04,0x04,0x0E,0x00,	// 0xD7
0x0A,0x00,0x0E,0x04,0x04,0x04,0x0E,0x00,	// 0xD8
0x04,0x04,0x04,0x3C,0x00,0x00,0x00,0x00,	// 0xD9
0x00,0x00,0x00,0x07,0x04,0x04,0x04,0x04,	// 0xDA
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,	// 0xDB
0x00,0x00,0x00,0x00,0x3F,0x3F,0x3F,0x3F,	// 0xDC
0x04,0x04,0x04,0x00,0x04,0x04,0x04,0x00,	// 0xDD
0x0C,0x00,0x0E,0x04,0x04,0x04,0x0E,0x00,	// 0xDE
0x3F,0x3F,0x3F,0x3F,0x00,0x00,0x00,0x00,	// 0xDF
0x06,0x0C,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0xE0
0x00,0x1C,0x12,0x1C,0x12,0x12,0x1C,0x10,	// 0xE1
0x0E,0x0C,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0xE2
0x18,0x0C,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0xE3
0x0A,0x14,0x00,0x0C,0x12,0x12,0x0C,0x00,	// 0xE4
0x0A,0x14,0x0C,0x12,0x12,0x12,0x0C,0x00,	// 0xE5
0x00,0x00,0x12,0x12,0x12,0x1C,0x10,0x10,	// 0xE6
0x00,0x18,0x10,0x1C,0x12,0x1C,0x10,0x18,	// 0xE7
0x18,0x10,0x1C,0x12,0x12,0x1C,0x10,0x18,	// 0xE8
0x06,0x00,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0xE9
0x0E,0x00,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0xEA
0x18,0x00,0x12,0x12,0x12,0x12,0x0C,0x00,	// 0xEB
0x06,0x00,0x12,0x12,0x12,0x0E,0x04,0x18,	// 0xEC
0x06,0x00,0x11,0x0A,0x04,0x04,0x04,0x00,	// 0xED
0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xEE
0x0C,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,	// 0xEF
0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,	// 0xF0
0x00,0x04,0x0E,0x04,0x00,0x0E,0x00,0x00,	// 0xF1
0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,	// 0xF2
0x30,0x1A,0x34,0x0B,0x15,0x07,0x01,0x00,	// 0xF3
0x0F,0x15,0x15,0x0D,0x05,0x05,0x05,0x00,	// 0xF4
0x0E,0x11,0x0C,0x0A,0x06,0x11,0x0E,0x00,	// 0xF5
0x00,0x04,0x00,0x1F,0x00,0x04,0x00,0x00,	// 0xF6
0x00,0x00,0x00,0x0E,0x06,0x00,0x00,0x00,	// 0xF7
0x0C,0x12,0x12,0x0C,0x00,0x00,0x00,0x00,	// 0xF8
0x00,0x00,0x00,0x0A,0x00,0x00,0x00,0x00,	// 0xF9
0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,	// 0xFA
0x08,0x18,0x08,0x08,0x00,0x00,0x00,0x00,	// 0xFB
0x1C,0x08,0x0C,0x18,0x00,0x00,0x00,0x00,	// 0xFC
0x18,0x04,0x08,0x1C,0x00,0x00,0x00,0x00,	// 0xFD
0x00,0x00,0x1E,0x1E,0x1E,0x1E,0x00,0x00,	// 0xFE
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 	// 0xFF
*/
};
	
//#ifndef d0
//#define d0 dk_bit(PORTB,1)
//#define d0_d dk_bit(DDRB,1)
//#define d0_i dk_bit(PINB,1)
//#define d1 dk_bit(PORTB,2)
//#define d1_d dk_bit(DDRB,2)
//#define d1_i dk_bit(PINB,2)
//#define d2 dk_bit(PORTB,3)
//#define d2_d dk_bit(DDRB,3)
//#define d2_i dk_bit(PINB,3)
//#define d3 dk_bit(PORTB,4)
//#define d3_d dk_bit(DDRB,4)
//#define d3_i dk_bit(PINB,4)
//#define d4 dk_bit(PORTB,5)
//#define d4_d dk_bit(DDRB,5)
//#define d4_i dk_bit(PINB,5)
//#define d5 dk_bit(PORTD,7)
//#define d5_d dk_bit(DDRD,7)
//#define d5_i dk_bit(PIND,7)
//#define d6 dk_bit(PORTD,6)
//#define d6_d dk_bit(DDRD,6)
//#define d6_i dk_bit(PIND,6)
//#define d7 dk_bit(PORTB,0)
//#define d7_d dk_bit(DDRB,0)
//#define d7_i dk_bit(PINB,0)
//
//#define rsl dk_bit(PORTB,1)
//#define rsl_d dk_bit(DDRB,1)
//#define rwl dk_bit(PORTB,2)
//#define rwl_d dk_bit(DDRB,2)
//#define enl dk_bit(PORTB,3)
//#define enl_d dk_bit(DDRB,3)
//#define rstl dk_bit(PORTB,3)
//#define rstl_d dk_bit(DDRB,3)
////RS:       PC0
////RW:       PC1
////E:        PC2
////RST       PC3
//
//#endif

u8 is_lcd_busy();

void xuat_dl_lcd(u8 ma)
{
	d0=(ma&0x1);
	ma>>=1;
	d1=(ma&0x1);
	ma>>=1;
	d2=(ma&0x1);
	ma>>=1;
	d3=(ma&0x1);
	ma>>=1;
	d4=(ma&0x1);
	ma>>=1;
	d5=(ma&0x1);
	ma>>=1;
	d6=(ma&0x1);
	ma>>=1;
	d7=(ma&0x1);
	//delay_us(1);
}
u8 doc_dl_lcd()
{
	u8 dl=0;
	//delay_us(1);
	dl|=d7_i;
	dl<<=1;
	dl|=d6_i;
	dl<<=1;
	dl|=d5_i;
	dl<<=1;
	dl|=d4_i;
	dl<<=1;
	dl|=d3_i;
	dl<<=1;
	dl|=d2_i;
	dl<<=1;
	dl|=d1_i;
	dl<<=1;
	dl|=d0_i;
	return dl;
}
void dl_xuat_nhap(u8 kieu)
{
	d0_d=d1_d=d2_d=d3_d=d4_d=d5_d=d6_d=d7_d=kieu;
}

  /////////////////////////////////////
 // Functions for LCD12864 control  //
/////////////////////////////////////
//Write instruction (code==0) or data (code==1) to LCD
void lcd_write(u8 lcdmode, u8 value)
{
	//while (is_lcd_busy())
	//{
	//}
	dl_xuat_nhap(ra);
	set_rw(0);	     //Write operation
	set_rs(lcdmode); //0 for instruction, 1 for data
	xuat_dl_lcd(value);
    set_e(1);
    delay_us(20);
	set_e(0);	
		
	set_rs(0);
}    

//Read data from LCD
u8 lcd_read(u8 lcdmode)
{
	u8 value;
	dl_xuat_nhap(vao);
    
    set_rw(1);	       //Read operation
	set_rs(lcdmode);   //Get value 0: for busy flag, 1 for other data
	
	set_e(1);          //Read data
    delay_us(10);       
	value = doc_dl_lcd();
    set_e(0);	
	
	//set_rs(0);
	
	return value;
}    

//Set RW line
void set_rw(u8 status)  
{
	rwl=status;
	delay_us(1);
}

//Set RS line
void set_rs(u8 status) 
{
	rsl=status;
	delay_us(1);
}

//Set E line
void set_e(u8 status)  
{
	enl=status;
	delay_us(1);
}

//Check for busy flag (BF)
u8 is_lcd_busy()
{
	u8 v = lcd_read(0);
	//delay_us(20);
	//v = lcd_read(0);
			
	if(v & 0x80)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//========================================
void ghi_byte_kep(u8 b0,u8 b1)
{
	lcd_write(1, b0);
	lcd_write(1, b1);
}
//Send one character to LCD (Normal size)
//
void lcd_putchar_ldn(u8 ch0, int inv)
{
	u8 b,b2;
	
	u8 o_doc; // o doc chi co 2 gia tri, 0 hoac 1, 0 la nua tren man hinh, 1 la nua giuoi man hinh
	int t1;
	int odd = 0;
	u8 v1, v2;
	int o_ngan = 0;//lx/8;// / 2; // 0-1
	int row = ly;// * font_cao;
	u8 ch;
	//u8 x=lx
	
	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
		row &= ~0x20;
		o_ngan |= 8;
	}
	
	if(o_ngan & 1) //Detect odd coloumn
	{
		odd = 1;
	}
	
	for(t1 = 0; t1 < font_cao; t1++)
	{
		//Set address
		lcd_write(0, 0x80 + row + t1);
		lcd_write(0, 0x80 + o_ngan);
		//Get old values of 2 GDRAM bytes
		v1 = lcd_read(1);
		v1 = lcd_read(1);
		v2 = lcd_read(1);

		//Set address
		//lcd_write(0, 0x80 + row + t1);
		//lcd_write(0, 0x80 + o_ngan);
		
		b=b2=font[ch0 * FONTHEIGHT + t1];
		b<<=2;
		b>>=lx;
		b|=v1;
		
		//if(!inv)
		//{
			//ch = b;
		//}
		//else
		//{
			//ch = ~b;
		//}
		
		//if(odd)
		//{
			////Write data on RIGHT side of existing character
			//lcd_write(1, v1);
			//lcd_write(1, ch);
		//}
		//else
		//{
			////Write data on LEFT side of existing character
			//lcd_write(1, ch);
			//lcd_write(1, v2);
		//}
		//b2<<=7;
		
		//ch=b2;
		//ch<<=7;
		lcd_write(0, 0x80 + row + t1);
		lcd_write(0, 0x80 + o_ngan);
		
		if(lx >= 8-font_rong)
		{
			b2<<=(7+(8-font_rong)-lx);
			b2|=v2;
		}
		else
		{
			b2=v2;
		}
		ghi_byte_kep(b,b2);
	}
}
void lcd_putstring_ldn(u8 *s, int inv)
{
	u8 t1;

	for(t1 = 0; *(s); t1++)
	{
		lcd_putchar_ldn(*(s++), inv);
		delay_ms(1000);
		lx+=font_rong+1;
	}
}

void lcd_putchar(int row0, int col0, u8 ch0, int inv)
{
	int t1;
	int odd = 0;
	u8 v1, v2;
	int col = col0 / 2;
	int row = row0 * FONTHEIGHT;
	u8 ch;
		
	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
        row &= ~0x20;
        col |= 8;
    }
        
	if(col0 & 1) //Detect odd coloumn
	{
		odd = 1;
	}
		
	for(t1 = 0; t1 < FONTHEIGHT; t1++)
    {
	    //Set address
        lcd_write(0, 0x80 + row + t1);
        lcd_write(0, 0x80 + col);
             
        //Get old values of 2 GDRAM bytes	
	    v1 = lcd_read(1);                
        v1 = lcd_read(1);
        v2 = lcd_read(1);

        //Set address
        lcd_write(0, 0x80 + row + t1);
        lcd_write(0, 0x80 + col);
        
        if(!inv)
        {
			ch = font[ch0 * FONTHEIGHT + t1];
		}
		else	
        {
			ch = ~font[ch0 * FONTHEIGHT + t1];
		}
		     
        if(odd)
        {     
            //Write data on RIGHT side of existing character
            lcd_write(1, v1);
            lcd_write(1, ch);
        }
        else    
        {   
			//Write data on LEFT side of existing character
            lcd_write(1, ch);
            lcd_write(1, v2);
        }
    }    
}   

//Send one character to LCD (DOUBLE size and normal width)
//
void lcd_putchar2(int row0, int col0, u8 ch0, int inv)
{
	int t1, t2;
	int odd = 0;
	u8 v1, v2;
	int col = col0 >> 1;
	int row = row0 * FONTHEIGHT;
	u8 ch;
		
	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
        row &= ~0x20;
        col |= 8;
    }
        
	if(col0 & 1) //Detect odd coloumn
	{
		odd = 1;
	}
		
	for(t1 = 0; t1 < FONTHEIGHT; t1++)
    {
		if(!inv) //Calculate character position in array and xor invert number if needed
        {
			ch = (font[ch0 * FONTHEIGHT + t1]);
		}
		else	
        {
			ch = (~font[ch0 * FONTHEIGHT + t1]);
		}
		
		for(t2 = 0; t2 < 2; t2++)
		{
	        //Set address
            lcd_write(0, 0x80 + row + t1 * 2 + t2);
            lcd_write(0, 0x80 + col);
             
            //Get old values of 2 GDRAM bytes	
	        v1 = lcd_read(1);                
            v1 = lcd_read(1);
            v2 = lcd_read(1);

            //Set address
            lcd_write(0, 0x80 + row + t1 * 2 + t2);
            lcd_write(0, 0x80 + col);
        		     
            if(odd)
            {     
                //Write data on RIGHT side of existing character
                lcd_write(1, v1);
                lcd_write(1, ch);
            }
            else    
            {   
			    //Write data on LEFT side of existing character
                lcd_write(1, ch);
                lcd_write(1, v2);
            }    
        }
    }    
}   

//Send one character to LCD (DOUBLE size and DOUBLE width)
//
void lcd_putchar3(int row0, int col0, u8 ch0, int inv)
{
	int t1, t2;
	u8 ch;
	//unsigned int i[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int i[FONTHEIGHT] = {0, 0, 0, 0, 0, 0, 0, 0};
	int col = col0 >> 1;
	int row = row0 * FONTHEIGHT;
	
	if(row & 0x20)  //Enter lower part of screen => go to next page
	{
        row &= ~0x20;
        col |= 8;
    }
        
		
	for(t1 = 0; t1 < FONTHEIGHT; t1++)
    {
		if(!inv) //Calculate character position in array and xor invert number if needed
        {
			ch = (font[ch0 * FONTHEIGHT + t1]);
		}
		else	
        {
			ch = (~font[ch0 * FONTHEIGHT + t1]);
		}
		
		//Double 8 to 16 bits
	    i[t1] = 0;
		for(t2 = 7; t2 > -1; t2--)
		{
			if(ch & (1 << t2))
			{
				i[t1] += (1 << ((t2 << 1) + 1)) + (1 << (t2 << 1)); //Double bit pattern 2 by 1
			}
		}
	}
	
	t2 = 0;
	for(t1 = 0; t1 < FONTHEIGHT; t1++)
	{
		for(t2 = 0; t2 < 2; t2++)
		{
	        //Set address
            lcd_write(0, 0x80 + row + t1 * 2 + t2);
            lcd_write(0, 0x80 + col);
                       
            lcd_write(1, ((i[t1] >> 8) & 0xFF));
            lcd_write(1, i[t1] & 0xFF); 
            //lcd_putnumber(t1, 0, i[t1] , -1, 0, 0);
        }    
    }    
		
}	





//Send string (\0 terminated) to LCD normal or double height
void lcd_putstring_a(int row, int col, u8 *s, int size, int inv)
{
    u8 t1;

    for(t1 = col; *(s); t1++)
	{
		if(!size)
		{
            lcd_putchar(row, t1, *(s++), inv);
        }
        else    
        {
            lcd_putchar2(row, t1, *(s++), inv);
        }
	}	
}

//String in DOUBLE height and DOUBLE width
void lcd_putstring_b(int row, int col, u8 *s, int inv)
{
    u8 t1;

    for(t1 = col; *(s); t1++)
	{
	    lcd_putchar3(row, t1 * 2, *(s++), inv);
	}	
}

//Clear LCD
void lcd_cls(void)
{
	int x, y;
    for(x = 0; x < 16; x++)
    {
		for(y = 0; y < 64; y++)
		{
			//Set address
            lcd_write(0, 0x80 + y);
            lcd_write(0, 0x80 + x);
             
            //Write data
            lcd_write(1, 0);
            lcd_write(1, 0);
        }
    }    
}

//Convert a number to a string and print it
//col, row: Coordinates, Num: int or long to be displayed
//dec: Set position of decimal separator
//
//inv: Set to 1 if inverted charactor is required
void lcd_putnumber(int col, int row, long num, int dec, int lsize, int inv)
{
    u8 *s = malloc(16);
	if(s != NULL)
	{
	    int2asc(num, dec, s, 16);
	    lcd_putstring_a(col, row, s, lsize, inv);
	    free(s);
	}	
	else
	{
		lcd_putstring_a(col, row, "Error", 0, 0);
	}	
}


//Init LCD
void lcd_khoi_tao(void)
{            
    rsl_d=rwl_d=enl_d=rstl_d=ra;
	dl_xuat_nhap(ra);
	rstl=0;
    delay_ms(2);
    rstl=1;
    delay_ms(80);
    
    lcd_write(0, 0x30);	//Use 8-bit mode parallel
    delay_ms(2);
         
    lcd_write(0, 0x0C); //All on Cursor on, Blink on , Display on
    delay_ms(2);
        
    lcd_write(0, 0x01); //Perform CLS in text mode to eliminate random chars from screen
    delay_ms(40);
    
    lcd_write(0, 0x34); //Switch to extended mode, redefine function set
    delay_us(200);
    
    lcd_write(0, 0x36); //Add graphic mode
    delay_us(200);
                   
    lcd_write(0, 0x12); //Display control and display ON
    delay_us(200);
}

//////////////////////
// STRING FUNCTIONS //
//////////////////////
//INT 2 ASC
int int2asc(long num, int dec, u8 *buf, int buflen)
{
    int i, c, xp = 0, neg = 0;
    long n, dd = 1E09;

    if(!num)
	{
	    *buf++ = '0';
		*buf = 0;
		return 1;
	}	
		
    if(num < 0)
    {
     	neg = 1;
	    n = num * -1;
    }
    else
    {
	    n = num;
    }

    //Fill buffer with \0
    for(i = 0; i < 12; i++)
    {
	    *(buf + i) = 0;
    }

    c = 9; //Max. number of displayable digits
    while(dd)
    {
	    i = n / dd;
	    n = n - i * dd;
	
	    *(buf + 9 - c + xp) = i + 48;
	    dd /= 10;
	    if(c == dec && dec)
	    {
	        *(buf + 9 - c + ++xp) = '.';
	    }
	    c--;
    }

    //Search for 1st char different from '0'
    i = 0;
    while(*(buf + i) == 48)
    {
	    *(buf + i++) = 32;
    }

    //Add minus-sign if neccessary
    if(neg)
    {
	    *(buf + --i) = '-';
    }

    //Eleminate leading spaces
    c = 0;
    while(*(buf + i))
    {
	    *(buf + c++) = *(buf + i++);
    }
    *(buf + c) = 0;
	
	return c;
}


// int main(void)
//{
    //// Set ports for LCD output and input data
    //DDRC = 0x0F; //LCD RS, RW, E and RST at PC0:PC3
	//DDRD = 0xFF; //LCD data on PD0:PD7
   	                 		//
	////Display init
	//_delay_ms(100);
    //lcd_init();
	//_delay_ms(100);
	//
    //lcd_cls();
        //
    //lcd_putstring_a(0, 0, "LCD 12864 ST7920", 0, 0);
    //lcd_putstring_a(1, 0, "   DK7IH 2018   ", 0, 1);
    //lcd_putstring_a(2, 0, "Graphical Fonts:", 0, 0);
    //lcd_putstring_a(3, 0, "8x8px.", 0, 0);
    //lcd_putnumber(4, 0, 1234, 1, 0, 0);    
       //
	//lcd_putstring_a(4, 0, "16x8px.", 1, 0);
	//
	//lcd_putstring_b(6, 0, "16x16px.", 0);
			    //
    //for(;;) 
	//{
    //
    //
	//}
	//return 0;
//}










void LCD_Write_Byte_4_bit(u8 command)
{
	enl = 1;
	delay_us(20);
	// Move higher nibble first
	d4 = (command & (1 << 4)) >> 4;
	d5 = (command & (1 << 5)) >> 5;
	d6 = (command & (1 << 6)) >> 6;
	d7 = (command & (1 << 7)) >> 7;
	delay_us(20);
	enl = 0;

	enl = 1;
	delay_us(20);
	// Then move the lower nibble
	d4 = (command & (1 << 0)) >> 0;
	d5 = (command & (1 << 1)) >> 1;
	d6 = (command & (1 << 2)) >> 2;
	d7 = (command & (1 << 3)) >> 3;
	delay_us(20);
	enl = 0;

	delay_us(20);					// Please increase this delay if the screen is not showing things correctly.
}

void LCD_WriteData(unsigned char data) //write data
{
	rsl=1;
	dl_xuat_nhap(ra);
	set_rw(0);	     //Write operation
	LCD_Write_Byte_4_bit(data);
}

void LCD_WriteCommand(unsigned char command) //write command
{
	rsl=0;
	dl_xuat_nhap(ra);
	set_rw(0);	     //Write operation
	LCD_Write_Byte_4_bit(command);
}

void LCD_ClearGraphics(void)
{
	// This function performs similar to the LCD_FillScreenGraphics but
	// only zeros are sent into the screen instead of data from an array.
	unsigned char x, y;
	for(y = 0; y < 64; y++)
	{
		if(y < 32)
		{
			LCD_WriteCommand(0x80 | y);
			LCD_WriteCommand(0x80);
		}
		else
		{
			LCD_WriteCommand(0x80 | (y-32));
			LCD_WriteCommand(0x88);
		}
		for(x = 0; x < 8; x++)
		{
			LCD_WriteData(0x00);
			LCD_WriteData(0x00);
		}
	}
}

void LCD_Init(void)
{
	rsl_d=rwl_d=enl_d=rstl_d=ra;
	dl_xuat_nhap(ra);
	rstl=1;
	rstl=0;
	delay_ms(5);
	rstl=1;

	delay_ms(50);

	LCD_WriteCommand(0b00100000); // function set, 4 bit mode
	delay_ms(5);

	LCD_WriteCommand(0b00100000); // 4 bit mode again
	delay_ms(5);
	
	LCD_WriteCommand(0b00001100); // display on, cursor off, blink off
	delay_ms(5);

	LCD_WriteCommand(0x01); 	  // display clear
	delay_ms(5);

	LCD_WriteCommand(0x06); 	  // Cursor moves right, no display shift.
	delay_ms(5);

	LCD_WriteCommand(0b00000010); // Returns to home. Cursor moves to starting point.
	delay_ms(5);
}

void LCD_TextDisplayString(unsigned char line, char* string)
{
	unsigned char addr,i;
	if(line==1)
	addr=0x80; //The first line address
	else if(line==2)
	addr=0x90; //The second line address
	else if(line==3)
	addr=0x88;   //The third line address
	else if(line==4)
	addr=0x98;    //The fourth line address

	LCD_WriteCommand(addr);

	for(i=0;i<16;i++)
	LCD_WriteData(*string++);
}

void LCD_EnableGraphics(void)
{
	LCD_WriteCommand(0x20);
	delay_ms(1);
	LCD_WriteCommand(0x24);			// Switch to extended instruction mode.
	delay_ms(1);
	LCD_WriteCommand(0x26);			// Enable graphics mode.
	delay_ms(1);
}

void LCD_DisableGraphics(void)
{
	LCD_WriteCommand(0x20);			// Graphics and extended instruction mode turned off.
	delay_ms(1);
}

void LCD_FillScreenGraphics(const unsigned char* graphic)
{
	unsigned char x, y;
	for(y = 0; y < 64; y++)
	{
		if(y < 32)
		{
			for(x = 0; x < 8; x++)							// Draws top half of the screen.
			{												// In extended instruction mode, vertical and horizontal coordinates must be specified before sending data in.
				LCD_WriteCommand(0x80 | y);					// Vertical coordinate of the screen is specified first. (0-31)
				LCD_WriteCommand(0x80 | x);					// Then horizontal coordinate of the screen is specified. (0-8)
				LCD_WriteData(graphic[2*x + 16*y]);			// Data to the upper byte is sent to the coordinate.
				LCD_WriteData(graphic[2*x+1 + 16*y]);		// Data to the lower byte is sent to the coordinate.
			}
		}
		else
		{
			for(x = 0; x < 8; x++)							// Draws bottom half of the screen.
			{												// Actions performed as same as the upper half screen.
				LCD_WriteCommand(0x80 | (y-32));			// Vertical coordinate must be scaled back to 0-31 as it is dealing with another half of the screen.
				LCD_WriteCommand(0x88 | x);
				LCD_WriteData(graphic[2*x + 16*y]);
				LCD_WriteData(graphic[2*x+1 + 16*y]);
			}
		}
		
	}
}

void LCD_GraphicsDisplayString(unsigned char line, char* str)
{
	// Output text to the LCD in graphics mode using a 5x7 font
	// Each char occupies 6 cols, 8 lines, including of space to next char
	unsigned char row;
	unsigned char colInd;
	unsigned char shouldContinue = 1;
	unsigned char count = 0;

	while(*str && shouldContinue)
	{
		unsigned char letterA = *str++;
		if (letterA == 0)
		{
			letterA = 32;
			shouldContinue = 0;
		}

		// if string length is odd, last letter does not come in pair, append space
		unsigned char letterB = *str++;
		if (letterB == 0)
		{
			letterB = 32; // odd number of characters in a string, replace NULL with space
			shouldContinue = 0;
		}

		unsigned char indA = letterA < 0x52 ? letterA - 0x20 : letterA - 0x52;
		unsigned char indB = letterB < 0x52 ? letterB - 0x20 : letterB - 0x52;
		unsigned char colListA[5];
		unsigned char colListB[5];
		
		if(letterA < 0x52){
			colListA[4] = Alpha1[(indA*5)];
			colListA[3] = Alpha1[(indA*5)+1];
			colListA[2] = Alpha1[(indA*5)+2];
			colListA[1] = Alpha1[(indA*5)+3];
			colListA[0] = Alpha1[(indA*5)+4];
		}
		else
		{
			colListA[4] = Alpha2[(indA*5)];
			colListA[3] = Alpha2[(indA*5)+1];
			colListA[2] = Alpha2[(indA*5)+2];
			colListA[1] = Alpha2[(indA*5)+3];
			colListA[0] = Alpha2[(indA*5)+4];
		}
		
		if(letterB < 0x52){
			colListB[4] = Alpha1[(indB*5)];
			colListB[3] = Alpha1[(indB*5)+1];
			colListB[2] = Alpha1[(indB*5)+2];
			colListB[1] = Alpha1[(indB*5)+3];
			colListB[0] = Alpha1[(indB*5)+4];
		}
		else
		{
			colListB[4] = Alpha2[(indB*5)];
			colListB[3] = Alpha2[(indB*5)+1];
			colListB[2] = Alpha2[(indB*5)+2];
			colListB[1] = Alpha2[(indB*5)+3];
			colListB[0] = Alpha2[(indB*5)+4];
		}

		for (row=0;row<8;row++)
		{
			if (line < 4)	// first half
			{
				LCD_WriteCommand(0x80 | (line * 8 + row));
				LCD_WriteCommand(0x80 | count);
			}
			else
			{
				LCD_WriteCommand(0x80 | ( (line-4) * 8 + row));
				LCD_WriteCommand(0x88 | count);
			}
			
			unsigned char dataA = 0x00;
			for (colInd=0;colInd<5;colInd++)
			{
				if (colListA[colInd] & (1 << row))
				{
					dataA = dataA | (1 << (colInd+3));
				}
			}

			unsigned char dataB = 0x00;
			for (colInd=0;colInd<5;colInd++)
			{
				if (colListB[colInd] & (1 << row))
				{
					dataB = dataB | (1 << (colInd+3));
				}
			}
			
			LCD_WriteData(dataA);
			LCD_WriteData(dataB);
		}

		count++;
	}
}