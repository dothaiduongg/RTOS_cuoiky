
/*
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

#ifndef so_20_10_H
#define so_20_10_H

#define COMIC24_WIDTH 15
#define COMIC24_HEIGHT 28
const uint8_t so_20_10[] PROGMEM = {
    0x7D, 0x1F, // size
    10,//6, // width
    24, // height
    0x20, // first char
    0x60, // char count
    
    // char widths 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 10, 10/*1*/, 10, 10, 
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
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
	0xFC,0xFE,0x07,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03, // 48
    0x00,0x08,0x0C,0x06,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x0C,0x0C,0x0C,0x0C,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,
    0x1C,0x1E,0x07,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01,0x0F,0x0F,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C, // 49
    0x1C,0x1E,0x07,0x03,0x03,0x03,0x03,0x87,0xFE,0xFC,0x00,0x00,0x00,0x00,0x00,0x02,0x07,0x0F,0xFD,0xF8,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03, // 50 2
	0x00,0x00,0x00,0xC0,0xF0,0x3C,0xFF,0xFF,0x00,0x00,0x70,0x7C,0x6F,0x63,0x60,0x60,0xFF,0xFF,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00, // 51
    0xFF,0xFF,0x03,0x83,0x83,0x83,0x83,0x83,0x03,0x03,0x87,0x87,0x03,0x01,0x01,0x01,0x01,0x03,0xFF,0xFE,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03, // 5
	0xFC,0xFE,0x07,0x03,0x03,0x03,0x03,0x07,0x0E,0x0C,0xFF,0xFF,0x06,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03, // 52
	0x03,0x03,0x03,0x03,0x03,0x83,0xE3,0x7B,0x1F,0x0F,0x00,0x00,0xE0,0xF8,0x1E,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00, // 54
    0x7C,0xFE,0x87,0x03,0x03,0x03,0x03,0x87,0xFE,0x7C,0xFC,0xFE,0x07,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03, // 56
    0xFC,0xFE,0x07,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x06,0xFF,0xFF,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03, // 57
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
const uint8_t so_24_12030[] PROGMEM = {
    0x7D, 0x1F, // size
    0x0A, // width
    0x1D, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x03, 0x06, 0x13, 0x0E, 0x12, 0x10, 0x02, 0x07, 0x07, 
    0x0B, 0x0A, 0x04, 0x09, 0x03, 0x0B, 0x0D, 0x09, 0x0B, 0x0B, 
    0x0F, 0x0D, 0x0D, 0x0E, 0x0D, 0x0D, 0x04, 0x05, 0x08, 0x0A, 
    0x09, 0x0B, 0x14, 0x0F, 0x0D, 0x0E, 0x0E, 0x0C, 0x0C, 0x10, 
    0x0F, 0x0B, 0x0F, 0x0D, 0x0C, 0x12, 0x12, 0x11, 0x0B, 0x15, 
    0x0E, 0x10, 0x11, 0x10, 0x0E, 0x15, 0x10, 0x0F, 0x10, 0x06, 
    0x0B, 0x06, 0x0B, 0x0F, 0x06, 0x0B, 0x0C, 0x0B, 0x0C, 0x0B, 
    0x0B, 0x0C, 0x0A, 0x03, 0x08, 0x0B, 0x03, 0x0F, 0x0B, 0x0B, 
    0x0B, 0x0B, 0x0A, 0x0A, 0x0B, 0x0A, 0x0B, 0x0F, 0x0D, 0x0D, 
    0x0C, 0x09, 0x03, 0x08, 0x0D, 0x0A, 
    
    // font data
    0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0x0D, 0x1D, 0x19, 0x00, 0x00, 0x00, // 33
    0xFC, 0xFC, 0x00, 0x00, 0xFC, 0xFC, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xF8, 0xFC, 0xFC, 0xC0, 0xC0, 0xC0, 0xE0, 0xFC, 0xFC, 0xDC, 0xC0, 0xC0, 0xC0, 0xC1, 0xC1, 0xC1, 0xF9, 0xFF, 0xFF, 0xCF, 0xC1, 0xC1, 0xC1, 0xF1, 0xFF, 0xFF, 0xCF, 0xC1, 0xC1, 0xC1, 0x01, 0x01, 0x19, 0x1F, 0x1F, 0x07, 0x01, 0x01, 0x01, 0x01, 0x1D, 0x1F, 0x1F, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x80, 0xE0, 0xF0, 0x70, 0x38, 0xFF, 0xFF, 0xFF, 0x38, 0x38, 0x38, 0x30, 0x30, 0x00, 0x07, 0x0F, 0x0F, 0x1E, 0x1C, 0xFF, 0xFF, 0xFF, 0x1C, 0x1C, 0x38, 0xF8, 0xF0, 0xE0, 0x1C, 0x3C, 0x3C, 0x38, 0x38, 0xFF, 0xFF, 0xFF, 0x38, 0x3C, 0x1E, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0xE0, 0xF0, 0xF8, 0x38, 0x38, 0xF8, 0xF0, 0xE0, 0x00, 0x80, 0xE0, 0xF8, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0xC7, 0xE3, 0xF9, 0x7E, 0xDF, 0xE7, 0xF1, 0x70, 0x70, 0x70, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x01, 0x00, 0x07, 0x0F, 0x1F, 0x1C, 0x1C, 0x1C, 0x0F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x38, 0x38, 0xF8, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x70, 0x7B, 0x3F, 0x3F, 0xFE, 0xFF, 0xE7, 0xC3, 0xF9, 0xF8, 0xF0, 0x00, 0x0F, 0x1F, 0x3F, 0x38, 0x70, 0x70, 0x70, 0x70, 0x78, 0x3D, 0x3F, 0x1F, 0x3F, 0xFF, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0xFC, 0xFC, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, // 39
    0x00, 0x80, 0xE0, 0xF0, 0x78, 0x3C, 0x1C, 0xFC, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x07, 0x3F, 0xFF, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x18, 0x18, // 40
    0x1C, 0x3C, 0x78, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFC, 0x80, 0x80, 0xE0, 0xF8, 0xFF, 0x3F, 0x07, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, // 41
    0x70, 0x70, 0xF0, 0xE0, 0xFC, 0xFC, 0xFC, 0xF0, 0x70, 0x70, 0x70, 0x00, 0x0E, 0x0F, 0x0F, 0x07, 0x03, 0x07, 0x0F, 0x0F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0xFE, 0xFE, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x38, 0x08, 0x08, 0x00, 0x00, // 44
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, // 46
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0x38, 0x00, 0x00, 0x80, 0xC0, 0xF0, 0xFC, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x38, 0x3E, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0x00, 0xC0, 0xE0, 0xF0, 0x78, 0x38, 0x38, 0x38, 0x78, 0xF0, 0xF0, 0xC0, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x3C, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0xC0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x1F, 0x1F, 0x1F, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0xC0, 0xE0, 0xF0, 0x78, 0x38, 0x38, 0x38, 0x78, 0xF0, 0xF0, 0xE0, 0x00, 0xC0, 0xE0, 0xF0, 0x70, 0x78, 0x3C, 0x1E, 0x0F, 0x07, 0x03, 0x0F, 0x1F, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x00, 0x60, 0x70, 0x78, 0x38, 0x38, 0x38, 0x78, 0xF0, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x3E, 0x7E, 0xFF, 0xF7, 0xE3, 0x0E, 0x1E, 0x1E, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x60, 0xF0, 0xF8, 0xFC, 0xFE, 0xEF, 0xE7, 0xE3, 0xE1, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0x00, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x18, 0x00, 0x3C, 0x3F, 0x3F, 0x1E, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x0F, 0xFE, 0xFC, 0xF0, 0x0E, 0x1E, 0x1E, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1E, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x78, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFF, 0x1F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x1C, 0xFC, 0xF8, 0xF0, 0x03, 0x0F, 0x1F, 0x1E, 0x3C, 0x38, 0x38, 0x38, 0x3C, 0x1E, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xB8, 0xF8, 0xF8, 0xF8, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFC, 0x7F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x00, 0xC0, 0xE0, 0xF0, 0x78, 0x38, 0x38, 0x38, 0x38, 0xF0, 0xF0, 0xC0, 0x00, 0xC0, 0xE3, 0xF7, 0x7F, 0x3E, 0x1C, 0x1C, 0x1C, 0x3E, 0x7F, 0xF7, 0xF3, 0xC0, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x38, 0x1C, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x80, 0xE0, 0xF0, 0x70, 0x38, 0x38, 0x38, 0x38, 0x78, 0xF0, 0xF0, 0xE0, 0x80, 0x0F, 0x1F, 0x3F, 0x38, 0x70, 0x70, 0x70, 0x70, 0xF8, 0xF8, 0xFF, 0x7F, 0x1F, 0x00, 0x1C, 0x1C, 0x1C, 0x1E, 0x0E, 0x0E, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0x00, 0x00, 0x00, 0x00, 0x0C, 0x1E, 0x1E, 0x1C, 0x0E, 0x1E, 0x1E, 0x1C, 0x00, 0x00, 0x00, 0x00, // 58
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1E, 0x1E, 0x00, 0xC0, 0xF0, 0xF8, 0x78, 0x38, 0x08, 0x08, 0x08, 0x00, 0x00, // 59
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xE0, 0xF0, 0xF8, 0xDC, 0x8E, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0E, 0x1E, 0xBC, 0xF8, 0xF0, 0xE0, 0x60, 0x0C, 0x0E, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x60, 0x70, 0x78, 0x38, 0x38, 0x38, 0x78, 0x70, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0xE0, 0xE0, 0xF0, 0x78, 0x38, 0x1C, 0x1F, 0x0F, 0x07, 0x00, 0x0C, 0x1E, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 63
    0x00, 0x80, 0xE0, 0xF0, 0xF0, 0x78, 0x38, 0x1C, 0x9C, 0x9C, 0x9C, 0x1C, 0x1C, 0x38, 0x38, 0x78, 0xF0, 0xE0, 0xC0, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0x78, 0xFE, 0xFF, 0xC7, 0xC3, 0xE3, 0xF9, 0xFC, 0xFC, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0x7F, 0x3F, 0x00, 0x07, 0x0F, 0x1F, 0x1E, 0x3C, 0x39, 0x71, 0x71, 0x71, 0x70, 0x70, 0x71, 0x39, 0x39, 0x39, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 64
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xF0, 0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF8, 0xFE, 0xFF, 0xE7, 0xE3, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x38, 0x3F, 0x3F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1F, 0x3F, 0x3F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xF0, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x38, 0x78, 0x70, 0xF0, 0xE0, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0x38, 0x38, 0x38, 0x38, 0x38, 0x7C, 0xFF, 0xFF, 0xE7, 0x80, 0x1F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1C, 0x1E, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0x00, 0x00, 0x00, 0x80, 0xE0, 0xE0, 0xF0, 0x78, 0x38, 0x38, 0x38, 0xF8, 0xF8, 0xF0, 0xF0, 0xFC, 0xFF, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x1E, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1E, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xF0, 0xF8, 0xF8, 0x30, 0x70, 0x60, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xFF, 0xFE, 0xF8, 0x1F, 0x1F, 0x1F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xF8, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0xFF, 0xFF, 0xFF, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x0F, 0x1F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xF8, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x30, 0x10, 0xFF, 0xFF, 0xFF, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x08, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0x70, 0x38, 0x38, 0x38, 0x38, 0x70, 0x70, 0x60, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0x0F, 0x63, 0x70, 0x70, 0x70, 0x38, 0x38, 0x38, 0xB8, 0xF8, 0xF8, 0xF8, 0x38, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1E, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xF0, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0xF0, 0xFF, 0xFF, 0xFF, 0x70, 0x70, 0x70, 0x70, 0x38, 0x38, 0x38, 0x38, 0x38, 0xFF, 0xFF, 0xFF, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0x10, 0x38, 0x38, 0x38, 0xF8, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x3F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 73
    0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0xF8, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x10, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x1F, 0x1C, 0x3C, 0x38, 0x38, 0x3F, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 74
    0xF0, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x78, 0x30, 0x00, 0xFF, 0xFF, 0xFF, 0xFC, 0xFE, 0xDF, 0x8F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0x3F, 0x01, 0x03, 0x07, 0x07, 0x0F, 0x1E, 0x1C, 0x3C, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xF0, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1C, 0x1C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 76
    0x00, 0x00, 0x80, 0xF0, 0xF8, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x7F, 0xFF, 0xF8, 0x80, 0xE0, 0xFC, 0xFF, 0x3F, 0x1F, 0xFF, 0xFF, 0xC0, 0x00, 0x3E, 0x3F, 0x1F, 0x01, 0x00, 0x00, 0x07, 0x3F, 0x3F, 0x3F, 0x0F, 0x01, 0x00, 0x00, 0x03, 0x1F, 0x3F, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xF0, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0x03, 0x07, 0x1F, 0x3E, 0x7C, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0x00, 0x00, 0x80, 0xE0, 0xE0, 0xF0, 0x78, 0x38, 0x38, 0x38, 0x38, 0x38, 0x78, 0xF0, 0xF0, 0xE0, 0x80, 0xF8, 0xFF, 0xFF, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x01, 0x07, 0x0F, 0x1F, 0x1C, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1E, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xF0, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x78, 0x70, 0xF0, 0xE0, 0xC0, 0xFF, 0xFF, 0xFF, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1F, 0x0F, 0x03, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x70, 0x70, 0x38, 0x38, 0x38, 0x38, 0x38, 0x78, 0x70, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x1E, 0x38, 0x38, 0x70, 0x77, 0x7F, 0x7F, 0x7E, 0x7C, 0x38, 0x78, 0xFC, 0xFE, 0xCF, 0x87, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x38, 0x38, 0x18, // 81
    0xF0, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x78, 0x70, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF9, 0x3F, 0x3F, 0x0F, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x0F, 0x1E, 0x1E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0x70, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x30, 0x30, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x1E, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x38, 0xF8, 0xF0, 0xE0, 0x07, 0x1F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1C, 0x1C, 0x1E, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0xF8, 0xF8, 0xF8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0xF0, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x1F, 0x01, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x38, 0x1C, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x78, 0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0xF8, 0x38, 0x00, 0x03, 0x3F, 0xFF, 0xFC, 0xC0, 0x80, 0xF0, 0xFE, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x3F, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0x38, 0xF8, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xF8, 0x38, 0x00, 0x03, 0x1F, 0xFF, 0xF0, 0xC0, 0xFC, 0xFF, 0x7F, 0x07, 0xFF, 0xFF, 0xC0, 0x80, 0xE0, 0xF8, 0xFF, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3F, 0x3F, 0x3F, 0x03, 0x00, 0x00, 0x03, 0x3F, 0x3F, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x00, 0x38, 0x78, 0xF8, 0xF0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0xF8, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 0x83, 0xE7, 0xFF, 0xFF, 0x7C, 0xFF, 0xFF, 0xC7, 0x83, 0x00, 0x00, 0x00, 0x18, 0x3C, 0x3E, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3E, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x38, 0xF8, 0xF8, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xF8, 0x38, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x3F, 0x7C, 0xF8, 0xF0, 0xFC, 0x7F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x3E, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xB8, 0xF8, 0xF8, 0xF8, 0xF8, 0x78, 0x38, 0x10, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF8, 0x7C, 0x3E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x3C, 0x3F, 0x3F, 0x3B, 0x39, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xFC, 0xFC, 0xFC, 0x1C, 0x1C, 0x1C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, // 91
    0x38, 0xF8, 0xF8, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x3F, 0xFF, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x7F, 0x7C, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 92
    0x1C, 0x1C, 0x1C, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, // 93
    0x60, 0x70, 0x78, 0x3C, 0x1E, 0x0E, 0x1E, 0x3C, 0x78, 0x70, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 95
    0x06, 0x0E, 0x1E, 0x7C, 0x78, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0x3C, 0x1E, 0x0E, 0x0E, 0xFE, 0xFC, 0xFC, 0x00, 0x07, 0x1F, 0x1F, 0x3C, 0x38, 0x38, 0x3C, 0x1F, 0x1F, 0x3F, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xF8, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x1C, 0x1E, 0x0E, 0x0E, 0x0E, 0x3C, 0xFC, 0xF8, 0xE0, 0x7F, 0x7F, 0x7F, 0x78, 0x70, 0x70, 0x70, 0x78, 0x3C, 0x3F, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x7C, 0x1E, 0x0E, 0x0E, 0x0E, 0x1E, 0x1C, 0x18, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x1C, 0x1C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 99
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFC, 0xF8, 0xE0, 0xF8, 0xFC, 0x3C, 0x0E, 0x0E, 0x0E, 0x0E, 0x1E, 0xFF, 0xFF, 0xFF, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0xBC, 0xDE, 0xCE, 0xEE, 0xEE, 0x7E, 0x7C, 0x38, 0x07, 0x0F, 0x1F, 0x3F, 0x39, 0x39, 0x38, 0x38, 0x3C, 0x1C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x3C, 0x1C, 0x1C, 0x1C, 0x08, 0x04, 0x0E, 0x0E, 0xFF, 0xFF, 0xFF, 0x0E, 0x0E, 0x0E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 102
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0x3C, 0x1E, 0x0E, 0x0E, 0x0E, 0x0E, 0xFE, 0xFC, 0x78, 0x07, 0x1F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x9C, 0xFF, 0xFF, 0xFF, 0x00, 0x30, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x38, 0x38, 0x18, 0x00, 0x00, // 103
    0xF8, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x7C, 0x1C, 0x0E, 0x0E, 0xFE, 0xFE, 0xFC, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0x70, 0x70, 0x70, 0xFC, 0xFE, 0xFC, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, // 105
    0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFC, 0x00, 0xC0, 0xC0, 0x80, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x18, 0x38, 0x78, 0x70, 0x70, 0x78, 0x38, 0x18, // 106
    0xF8, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xC0, 0xE0, 0xF0, 0xF8, 0xBC, 0x1E, 0x0E, 0x06, 0x1F, 0x3F, 0x1F, 0x01, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x3E, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0xF8, 0xFC, 0xF8, 0xFF, 0xFF, 0xFF, 0x3F, 0x7F, 0x3F, 0x00, 0x00, 0x00, // 108
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFE, 0x3C, 0x1C, 0x0E, 0xFE, 0xFE, 0xFC, 0x1C, 0x0E, 0x0E, 0xFE, 0xFE, 0xFC, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFC, 0x3C, 0x1E, 0x0E, 0x0E, 0xFE, 0xFC, 0xF8, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0x3C, 0x0E, 0x0E, 0x0E, 0x1E, 0xFC, 0xF8, 0xF0, 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x38, 0x3C, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFE, 0x1C, 0x0E, 0x0E, 0x0E, 0x1E, 0xFC, 0xFC, 0xF0, 0xFF, 0xFF, 0xFF, 0x38, 0x38, 0x38, 0x38, 0x3C, 0x1F, 0x0F, 0x03, 0x78, 0xF8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 112
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x3C, 0x1E, 0x0E, 0x0E, 0x0E, 0xFE, 0xFE, 0xFE, 0x07, 0x0F, 0x1F, 0x1C, 0x38, 0x38, 0x38, 0x38, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xF8, 0x78, // 113
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x3C, 0x1C, 0x0E, 0x0E, 0x7E, 0x7E, 0x7C, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 114
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7C, 0xFE, 0xEE, 0xCE, 0xCE, 0x9E, 0x1E, 0x1E, 0x1C, 0x1C, 0x3C, 0x38, 0x38, 0x39, 0x39, 0x1F, 0x1F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 115
    0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x0E, 0x0E, 0xFF, 0xFF, 0xFF, 0x0E, 0x0E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 116
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFC, 0x07, 0x1F, 0x3F, 0x38, 0x38, 0x38, 0x38, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x7E, 0xFE, 0xF8, 0xC0, 0x00, 0xC0, 0xF8, 0xFE, 0x7E, 0x0E, 0x00, 0x00, 0x01, 0x07, 0x3F, 0x3E, 0x3F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xFE, 0xFE, 0xC0, 0x80, 0xF0, 0xFC, 0xFE, 0xFE, 0xE0, 0x00, 0xF0, 0xFE, 0xFE, 0x1E, 0x00, 0x0F, 0x3F, 0x3F, 0x3F, 0x0F, 0x01, 0x01, 0x0F, 0x3F, 0x3F, 0x3F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x1E, 0xFC, 0xF8, 0xF0, 0xF0, 0xF8, 0x7C, 0x3E, 0x1E, 0x0E, 0x18, 0x1C, 0x1E, 0x0F, 0x07, 0x03, 0x01, 0x03, 0x07, 0x1F, 0x3E, 0x3C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x1E, 0x7E, 0xFC, 0xF0, 0xE0, 0x80, 0x80, 0xE0, 0xF8, 0xFE, 0x3E, 0x0E, 0x00, 0x00, 0x00, 0x01, 0xC3, 0xFF, 0xFF, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x78, 0x78, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 121
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x0E, 0x0E, 0x8E, 0xCE, 0xEE, 0xFE, 0xFE, 0x3E, 0x1E, 0x0E, 0x38, 0x38, 0x3C, 0x3E, 0x3F, 0x3F, 0x3B, 0x39, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x00, 0x00, 0xE0, 0xF8, 0xFC, 0x1C, 0x1C, 0x1C, 0x18, 0xE0, 0xF0, 0xFF, 0xBF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3F, 0xFF, 0xFF, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x18, 0x18, 0x18, // 123
    0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0x08, // 124
    0x1C, 0x1C, 0x1C, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xBF, 0xFF, 0xF0, 0xE0, 0x80, 0x80, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, // 125
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x70, 0x38, 0x38, 0x78, 0x78, 0xF0, 0xE0, 0xE0, 0xF8, 0x78, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif
