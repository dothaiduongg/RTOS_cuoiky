#ifndef _FONT_H_
#define _FONT_H_

#include "avr/pgmspace.h"
#include "types.h"

//Constants
#define FONT_OFFSET_WIDTH 2
#define FONT_OFFSET_HEIGHT 3
#define FONT_OFFSET_FIRSTCHAR 4
#define FONT_OFFSET_CHARCOUNT 5
#define FONT_OFFSET_WTABLE 6

//Main Selected Font
const uint8_t *font;

//Functions
void __GFXInitFont();

UINT8 GFXGetFontHeight();

UINT8 __GFXReadFontData(UINT16 add);

UINT8 __GFXReadPGM(const uint8_t *ptr);

void GFXSetFont(const uint8_t *new_font);

int8_t GFXPutCharXY(int8_t x, int8_t y,char c,uint8_t color);

#endif
