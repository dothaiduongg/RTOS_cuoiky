

/*
 *
 * Comic24
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Comic24.h
 * Date                : 25.12.2010
 * Font size in bytes  : 32031
 * Font width          : 10
 * Font height         : 29
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef so_20_h
#define so_20_h

#define COMIC24_WIDTH 10
#define COMIC24_HEIGHT 29

const uint8_t so_20[] PROGMEM = {
    0x7D, 0x1F, // size
    0x0A, // width
    0x1D, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 3, 13, 13/*1*/, 13, 13, 
    13, 13, 13, 13, 0x0D, 0x0D, 0x04, 0x05, 0x08, 0x0A, 
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
    0x38,0x38,0x38,0xC0,0xC0,0xC0,0x01,0x01,0x01, 0x00, 0x00, 0x00, // 47
	                                                     //10                kt                                        20                                  kt                     30                                                          40                                                          50           52
    0xF8,0xFC,0xFE,0x0F,0x07,0x07,0x07,0x07,0x07,0x0F,0xFE,0xFC,0xF8,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x01,0x03,0x07,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x07,0x03,0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x00,0x70,0x78,0x3C,0x1E,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0E,0x0E,0x0E,0x0F,0x0F,0x0F,0x0E,0x0E,0x0E,0x0E,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0x38,0x3E,0x3E,0x0F,0x07,0x07,0x07,0x07,0x07,0x8F,0xFF,0xFE,0xFC,0x00,0x80,0xC0,0xE0,0xF0,0x78,0x3C,0x1E,0x0F,0x07,0x03,0x01,0x00,0x0F,0x0F,0x0F,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50 2
    0x38,0x3C,0x3E,0x0F,0x07,0x07,0x07,0x07,0x07,0x8F,0xFE,0xFC,0xF8,0x80,0x80,0x80,0x00,0x00,0x00,0x07,0x07,0x0F,0x1F,0xFF,0xF9,0xF0,0x01,0x03,0x07,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x07,0x03,0x01,      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x00,0x80,0xC0,0xE0,0xF0,0x78,0x3C,0x1E,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0x7F,0x7F,0x71,0x70,0x70,0x70,0x70,0xFF,0xFF,0xFF,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x00,0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0xFF,0xFF,0xFF,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0x87,0x07,0x07,0x81,0x81,0x81,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0xFF,0xFF,0xFE,0x01,0x03,0x07,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x07,0x03,0x01,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0xF8,0xFC,0xFE,0x0F,0x07,0x07,0x07,0x07,0x07,0x0F,0x1E,0x1C,0x18,0xFF,0xFF,0xFF,0x0E,0x07,0x07,0x07,0x07,0x07,0x0F,0xFE,0xFC,0xF8,0x01,0x03,0x07,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x07,0x03,0x01,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x87,0xE7,0xF7,0x7F,0x3F,0x1F,0x00,0x00,0x00,0x00,0xE0,0xF8,0xFE,0x1F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// 55
    0xF8,0xFC,0xFE,0x8F,0x07,0x07,0x07,0x07,0x07,0x8F,0xFE,0xFC,0xF8,0xF8,0xFD,0xFF,0x0F,0x07,0x07,0x07,0x07,0x07,0x0F,0xFF,0xFD,0xF8,0x01,0x03,0x07,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x07,0x03,0x01,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0xF8,0xFC,0xFE,0x0F,0x07,0x07,0x07,0x07,0x07,0x0F,0xFE,0xFC,0xF8,0x81,0x83,0x87,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x07,0xFF,0xFF,0xFF,0x01,0x03,0x07,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0F,0x07,0x03,0x01,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
};

#endif
