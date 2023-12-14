

/*
 *
 * font_10x16
 *
 *
 * File Name           : deniz7x16.h
 * Date                : 13.01.2019
 * Font size in bytes  : 2534
 * Font width          : 10
 * Font height         : 16
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * by aziz kurosaki
 *
 */

#ifndef DENIZ_7X16_H
#define DENIZ_7X16_H

#define FONT_7X16_WIDTH 10
#define FONT_7X16_HEIGHT 16

const static uint8_t deniz7x16[] PROGMEM  = {
    0x09, 0xE6, // size
    0x0A, // width
    0x10, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x05, 
    0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x04, 0x08, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x00, 0x0A, 0x09, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    
    
    // font data
    0x3E, 0x7F, 0x63, 0x63, 0x63, 0x7F, 0x3E, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x7C, 0xFE, 0xC6, 0xC6, 0xC6, 0xFE, 0x7C, // 37
    0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 39
    0x80, 0x80, 0xE0, 0x80, 0x80, 0x01, 0x01, 0x07, 0x01, 0x01, // 43
    0x80, 0x80, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x01, 0x01, // 45
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, // 46
    0x00, 0x00, 0x00, 0x80, 0xE0, 0x78, 0x1E, 0x07, 0xE0, 0x78, 0x1E, 0x07, 0x01, 0x00, 0x00, 0x00, // 47
    0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, // 48
    0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, // 49
    0x01, 0x83, 0x83, 0x83, 0x83, 0xFF, 0xFE, 0x7F, 0xFF, 0xC1, 0xC1, 0xC1, 0xC1, 0x80, // 50
    0x01, 0x83, 0x83, 0x83, 0x83, 0xFF, 0xFE, 0x80, 0xC1, 0xC1, 0xC1, 0xC1, 0xFF, 0x7F, // 51
    0xFF, 0xFE, 0x80, 0x80, 0x80, 0xFE, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7F, 0xFF, // 52
    0xFE, 0xFF, 0x83, 0x83, 0x83, 0x83, 0x01, 0x80, 0xC1, 0xC1, 0xC1, 0xC1, 0xFF, 0x7F, // 53
    0xFE, 0xFF, 0x83, 0x83, 0x83, 0x83, 0x01, 0x7F, 0xFF, 0xC1, 0xC1, 0xC1, 0xFF, 0x7F, // 54
    0x01, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, // 55
    0xFE, 0xFF, 0x83, 0x83, 0x83, 0xFF, 0xFE, 0x7F, 0xFF, 0xC1, 0xC1, 0xC1, 0xFF, 0x7F, // 56
    0xFE, 0xFF, 0x83, 0x83, 0x83, 0xFF, 0xFE, 0x80, 0xC1, 0xC1, 0xC1, 0xC1, 0xFF, 0x7F, // 57
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //0x0C, 0x1E, 0x3F, 0x1E, 0x0C, 0x30, 0x78, 0xFC, 0x78, 0x30, // 58
    0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0x70, 0x70, 0x78, 0x38, 0x38, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x0E, 0x0E, // 60
    0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, // 61
    0x00, 0x00, 0x00, 0xF8, 0xFC, 0x0C, 0x0C, 0x0C, 0x1C, 0x18, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    
};

#endif
