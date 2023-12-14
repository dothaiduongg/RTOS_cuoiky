#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef so_10_16_H
#define so_10_16_H

//#define COMIC24_WIDTH 15
//#define COMIC24_HEIGHT 28
const uint8_t so_10_16[] PROGMEM = {
    0x7D, 0x1F, // size
    20,//6, // width
    16, // height
    0x20, // first char
    0x60, // char count
    
    // char widths 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 10, 10/*1*/, 10, 10, 
    10, 10, 10,10, 10, 10,10, 10,10, 10, 
    0x09, 0x0B, 0x14, 0x0F, 0x0D, 0x0E, 0x0E, 0x0C, 0x0C, 0x10, 
    0x0F, 0x0B, 0x0F, 0x0D, 0x0C, 0x12, 0x12, 0x11, 0x0B, 0x15, 
    0x0E, 0x10, 0x11, 0x10, 0x0E, 0x15, 0x10, 0x0F, 0x10, 0x06, 
    0x0B, 0x06, 0x0B, 0x0F, 0x06, 0x0B, 0x0C, 0x0B, 0x0C, 0x0B, 
    0x0B, 0x0C, 0x0A, 0x03, 0x08, 0x0B, 0x03, 0x0F, 0x0B, 0x0B, 
    0x0B, 0x0B, 0x0A, 0x0A, 0x0B, 0x0A, 0x0B, 0x0F, 0x0D, 0x0D, 
    0x0C, 0x09, 0x03, 0x08, 0x0D, 0x0A, 
    
    // font data
    //0xFC, 0xFC, 0xFC, 0xFF, // 33
    //0xFC, 0xFC, 0x00, 0x00, // 34
    //0x00, 0xC0, 0xC0, 0xC0, // 35
//     0x80, 0xE0, 0xF0, 0x70, // 36
//     0xE0, 0xF0, 0xF8, 0x38, // 37
//     0x00, 0x00, 0x00, 0x00, // 38
//     0xFC, 0xFC, 0x03, 0x03, // 39
//     0x00, 0x80, 0xE0, 0xF0,  // 40
//     0x1C, 0x3C, 0x78, 0xF0, // 41
//     0x70, 0x70, 0xF0, 0xE0,  // 42
//     0x00, 0x00, 0x00, 0x00,// 43
//     0x00, 0x00, 0x00, 0x00, // 44
//     0x00, 0x00, 0x00, 0x00, // 45
//     0x00, 0x00, 0x00, 0x00,// 46
//    0x38,0x38,0x38,0xC0,0xC0,0xC0,0x01,0x01,0x01,0x00,0x00,0x00, // 47
	                                                     //10                kt                                        20                                  kt                     30                                                          40                                                          50           52
	0xFE,0xFF,0x03,0x01,0x01,0x01,0x01,0x03,0xFF,0xFE,0x7F,0xFF,0xC0,0x80,0x80,0x80,0x80,0xC0,0xFF,0x7F, // 0 ok
    0x00,0x00,0x04,0x06,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xFF,0xFF,0x80,0x80,0x80,0x00, // 1 ok
    0x0E,0x0F,0x03,0x01,0x01,0x01,0x81,0xC3,0x7F,0x3E,0xE0,0xF0,0x98,0x8C,0x86,0x83,0x81,0x80,0x80,0x80, // 2 ok
    0x06,0x07,0x03,0x01,0x01,0x01,0x81,0xC3,0x7F,0x3E,0x70,0xF0,0xC0,0x80,0x80,0x80,0x80,0xC1,0xFF,0x7E, // 3 ok
	0x00,0x00,0x80,0xE0,0x78,0x1E,0xFF,0xFF,0x00,0x00,0x18,0x1E,0x17,0x11,0x10,0x10,0xFF,0xFF,0x10,0x10, // 4 ok
    0x7F,0x7F,0x41,0x41,0x41,0x41,0x41,0xC1,0xC1,0x81,0x70,0xF0,0xC0,0x80,0x80,0x80,0x80,0xC0,0xFF,0x7F, // 5 ok
	0xFE,0xFF,0x83,0x81,0x81,0x81,0x81,0x83,0x8F,0x0E,0x7F,0xFF,0xC1,0x80,0x80,0x80,0x80,0xC1,0xFF,0x7F, // 6 ok
	0x01,0x01,0x01,0x01,0x81,0xC1,0x61,0x31,0x1F,0x0F,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00, // 7 ok
    0x3E,0x7F,0xC3,0x81,0x81,0x81,0x81,0xC3,0x7F,0x3E,0x7E,0xFF,0xC1,0x80,0x80,0x80,0x80,0xC1,0xFF,0x7E, // 8 
    0xFE,0xFF,0x83,0x01,0x01,0x01,0x01,0x83,0xFF,0xFE,0x70,0xF1,0xC1,0x81,0x81,0x81,0x81,0xC1,0xFF,0x7F, // 9 ok
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

#endif