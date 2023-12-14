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
    0x04, 0x10, // 58
    0x04, 0x70, // 59
    0x10, 0x28, 0x28, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x44, 0x28, 0x28, 0x28, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x06, 0x01, 0x61, 0x11, 0x0E, 0x00, 0x00, 0x10, 0x00, 0x00, // 63
    0xF0, 0x0C, 0xE2, 0x12, 0x09, 0x09, 0xF1, 0x19, 0x02, 0x86, 0x78, 0x10, 0x20, 0x40, 0x90, 0x90, 0x90, 0x90, 0x90, 0x50, 0x40, 0x20, // 64
    0x80, 0x70, 0x2E, 0x21, 0x2E, 0x70, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // 65
    0xFF, 0x11, 0x11, 0x11, 0x11, 0xEE, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, // 66
    0x7C, 0x82, 0x01, 0x01, 0x01, 0x82, 0x44, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, // 67
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x82, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, // 68
    0xFF, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // 69
    0xFF, 0x11, 0x11, 0x11, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, // 70
    0x7C, 0x82, 0x01, 0x01, 0x11, 0x92, 0x74, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, // 71
    0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // 72
    0xFF, 0x10, // 73
    0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x10, 0x10, 0x10, 0x00, // 74
    0xFF, 0x20, 0x10, 0x28, 0x44, 0x82, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // 75
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // 76
    0xFF, 0x06, 0x78, 0x80, 0x78, 0x06, 0xFF, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, // 77
    0xFF, 0x02, 0x0C, 0x10, 0x60, 0x80, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // 78
    0x7C, 0x82, 0x01, 0x01, 0x01, 0x82, 0x7C, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, // 79
    0xFF, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0x7C, 0x82, 0x01, 0x41, 0x41, 0x82, 0x7C, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x10, // 81
    0xFF, 0x11, 0x11, 0x11, 0x31, 0xD1, 0x0E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // 82
    0xCE, 0x11, 0x11, 0x11, 0x11, 0xE6, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, // 83
    0x01, 0x01, 0x01, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, // 84
    0x7F, 0x80, 0x00, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, // 85
    0x03, 0x1C, 0x60, 0x80, 0x60, 0x1C, 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, // 86
    0x07, 0x78, 0x80, 0x70, 0x0E, 0x01, 0x0E, 0x70, 0x80, 0x7C, 0x03, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // 87
    0x01, 0xC6, 0x28, 0x10, 0x6C, 0x82, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // 88
    0x01, 0x06, 0x08, 0xF0, 0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, // 89
    0x00, 0x81, 0x61, 0x11, 0x0D, 0x03, 0x01, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // 90
    0xFF, 0x01, 0x70, 0x40, // 91
    0x03, 0x7C, 0x80, 0x00, 0x00, 0x10, // 92
    0x01, 0xFF, 0x40, 0x70, // 93
    0x10, 0x0E, 0x01, 0x0E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 95
    0x01, 0x02, 0x00, 0x00, // 96
    0xC8, 0x24, 0x24, 0xA4, 0xF8, 0x00, 0x10, 0x10, 0x00, 0x10, // 97
    0xFF, 0x88, 0x04, 0x04, 0xF8, 0x10, 0x00, 0x10, 0x10, 0x00, // 98
    0xF8, 0x04, 0x04, 0x88, 0x00, 0x10, 0x10, 0x00, // 99
    0xF8, 0x04, 0x04, 0x88, 0xFF, 0x00, 0x10, 0x10, 0x00, 0x10, // 100
    0xF8, 0x24, 0x24, 0x24, 0xB8, 0x00, 0x10, 0x10, 0x10, 0x00, // 101
    0x04, 0xFE, 0x05, 0x00, 0x10, 0x00, // 102
    0xF8, 0x04, 0x04, 0x88, 0xFC, 0x40, 0x50, 0x50, 0x40, 0x30, // 103
    0xFF, 0x08, 0x04, 0x04, 0xF8, 0x10, 0x00, 0x00, 0x00, 0x10, // 104
    0xFD, 0x10, // 105
    0x00, 0xFD, 0x40, 0x30, // 106
    0xFF, 0x20, 0x30, 0xC8, 0x04, 0x10, 0x00, 0x00, 0x00, 0x10, // 107
    0xFF, 0x10, // 108
    0xFC, 0x08, 0x04, 0x04, 0xF8, 0x08, 0x04, 0x04, 0xF8, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, // 109
    0xFC, 0x08, 0x04, 0x04, 0xF8, 0x10, 0x00, 0x00, 0x00, 0x10, // 110
    0xF8, 0x04, 0x04, 0x04, 0xF8, 0x00, 0x10, 0x10, 0x10, 0x00, // 111
    0xFC, 0x88, 0x04, 0x04, 0xF8, 0x70, 0x00, 0x10, 0x10, 0x00, // 112
    0xF8, 0x04, 0x04, 0x88, 0xFC, 0x00, 0x10, 0x10, 0x00, 0x70, // 113
    0xFC, 0x08, 0x04, 0x10, 0x00, 0x00, // 114
    0x98, 0x24, 0x24, 0x24, 0xC8, 0x00, 0x10, 0x10, 0x10, 0x00, // 115
    0x04, 0xFF, 0x04, 0x00, 0x10, 0x10, // 116
    0xFC, 0x00, 0x00, 0x80, 0xFC, 0x00, 0x10, 0x10, 0x00, 0x10, // 117
    0x0C, 0x70, 0x80, 0x70, 0x0C, 0x00, 0x00, 0x10, 0x00, 0x00, // 118
    0x0C, 0x70, 0x80, 0x70, 0x0C, 0x70, 0x80, 0x70, 0x0C, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // 119
    0x04, 0xD8, 0x60, 0x98, 0x04, 0x10, 0x00, 0x00, 0x00, 0x10, // 120
    0x0C, 0x70, 0x80, 0x70, 0x0C, 0x00, 0x40, 0x30, 0x00, 0x00, // 121
    0x04, 0xC4, 0x24, 0x1C, 0x04, 0x10, 0x10, 0x10, 0x10, 0x10, // 122
    0x20, 0xDE, 0x01, 0x00, 0x30, 0x40, // 123
    0xFF, 0x70, // 124
    0x01, 0xDE, 0x20, 0x40, 0x30, 0x00, // 125
    0x20, 0x10, 0x10, 0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFE, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 // 127
    
};

#endif