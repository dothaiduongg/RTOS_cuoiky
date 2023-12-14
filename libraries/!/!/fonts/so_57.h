#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef so_57_h
#define so_57_h

#define ARIAL12_WIDTH 5
#define ARIAL12_HEIGHT 7

const uint8_t so_57[] PROGMEM = {
    0x16, 0x7A, // size
    0x08, // width
    0x0c, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x01, 0x03, 0x07, 0x05, 0x09, 0x07, 0x01, 0x03, 0x03, 
    0x05, 0x05, 0x01, 0x03, 0x01, 0x03, 0x05, 0x05/*1*/, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x01, 0x01, 0x05, 0x06, 
    0x05, 0x05, 0x0B, 0x07, 0x06, 0x07, 0x07, 0x06, 0x05, 0x07, 
    0x07, 0x01, 0x05, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 
    0x07, 0x06, 0x07, 0x07, 0x07, 0x0B, 0x07, 0x07, 0x07, 0x02, 
    0x03, 0x02, 0x05, 0x07, 0x02, 0x05, 0x05, 0x04, 0x05, 0x05, 
    0x03, 0x05, 0x05, 0x01, 0x02, 0x05, 0x01, 0x09, 0x05, 0x05, 
    0x05, 0x05, 0x03, 0x05, 0x03, 0x05, 0x05, 0x09, 0x05, 0x05, 
    0x05, 0x03, 0x01, 0x03, 0x06, 0x07, 
    
    // font data
    0x7F, 0x10, // 33
    0x07, 0x00, 0x07, 0x00, 0x00, 0x00, // 34
    0x24, 0xE4, 0x3C, 0xE7, 0x3C, 0x27, 0x24, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, // 35
    0xCE, 0x11, 0xFF, 0x11, 0xE2, 0x00, 0x10, 0x30, 0x10, 0x00, // 36
    0x0E, 0x11, 0x11, 0xCE, 0x38, 0xE6, 0x11, 0x10, 0xE0, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, // 37
    0xE0, 0x1E, 0x11, 0x29, 0xC6, 0xA0, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, // 38
    0x07, 0x00, // 39
    0xF8, 0x06, 0x01, 0x00, 0x30, 0x40, // 40
    0x01, 0x06, 0xF8, 0x40, 0x30, 0x00, // 41
    0x02, 0x0A, 0x07, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x70, // 44
    0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // 45
    0x00, 0x10, // 46
    0x80, 0x7C, 0x03, 0x10, 0x00, 0x00, // 47
    0x3E, 0x41, 0x41, 0x41, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, // 48 // 0
    0x00,0x42,0x7f,0x40,0x00,0x00,0x00,0x00,0x00, 0x00, // 49
    0x42, 0x61, 0x51, 0x49, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, // 50 //2
    0x22,0x41,0x49,0x49,0x36, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x18,0x14,0x12,0x7F,0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 52 // 4
    0x27,0x45,0x45,0x45,0x39,0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x3E,0x49,0x49,0x49,0x32,0x00, 0x00, 0x00, 0x00, 0x00, // 54 6
    0x01,0x71,0x09,0x05,0x03,0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x3A,0x45,0x45,0x45,0x3A,0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x26,0x49,0x49,0x49,0x3E,0x00, 0x00, 0x00, 0x00, 0x00, // 57
};

#endif
