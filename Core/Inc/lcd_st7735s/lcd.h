#ifndef _lcd_h_
#define _lcd_h_

#include "lcd_st7735s.h"
#include "lcd_roboto.h"

//#define USE_RECT_FUNCTIONS

void LCD_DrawFillCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color);
void LCD_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void LCD_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void LCD_FillCircleHelper(int16_t x0, int16_t y0, int16_t radius, uint8_t cornername, int16_t delta, uint16_t color);
void LCD_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
void LCD_SetLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_SetPixel(uint16_t  x, uint16_t  y, uint16_t  color);
void LCD_SetCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color);
void LCD_DrawPicture(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t *pBuf, uint8_t fillBm);

#ifdef USE_RECT_FUNCTIONS
void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void LCD_DrawFillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void LCD_SetRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t fill, uint16_t color);
#endif

#define NOFILL  0
#define FILL    1

#endif


