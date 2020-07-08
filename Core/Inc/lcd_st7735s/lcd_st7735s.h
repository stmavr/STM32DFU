#ifndef _lcd_st7735s_h_
#define _lcd_st7735s_h_

#include "stdint.h"

#define ADDR_CMD            *(uint8_t*)0x60000000
#define ADDR_DATA           *(uint8_t*)0x60010000

#define ST7735_NOP		    0x00
#define ST7735_SWRESET	    0x01
#define ST7735_RDDID	    0x04
#define ST7735_RDDST	    0x09
#define ST7735_RDDMADCTL	0x0B

#define ST7735_SLPIN	    0x10
#define ST7735_SLPOUT	    0x11
#define ST7735_PTLON	    0x12
#define ST7735_NORON	    0x13

#define ST7735_INVOFF	    0x20
#define ST7735_INVON	    0x21
#define ST7735_DISPOFF      0x28
#define ST7735_DISPON	    0x29
#define ST7735_CASET	    0x2A
#define ST7735_RASET	    0x2B
#define ST7735_RAMWR	    0x2C
#define ST7735_RAMRD	    0x2E

#define ST7735_COLMOD	    0x3A
#define ST7735_MADCTL	    0x36

#define ST7735_FRMCTR1      0xB1
#define ST7735_FRMCTR2      0xB2
#define ST7735_FRMCTR3      0xB3
#define ST7735_INVCTR	    0xB4
#define ST7735_DISSET5      0xB6

#define ST7735_PWCTR1	    0xC0
#define ST7735_PWCTR2	    0xC1
#define ST7735_PWCTR3	    0xC2
#define ST7735_PWCTR4	    0xC3
#define ST7735_PWCTR5	    0xC4
#define ST7735_VMCTR1	    0xC5

#define ST7735_RDID1	    0xDA
#define ST7735_RDID2	    0xDB
#define ST7735_RDID3	    0xDC
#define ST7735_RDID4	    0xDD

#define ST7735_PWCTR6	    0xFC

#define ST7735_GMCTRP1	    0xE0
#define ST7735_GMCTRN1	    0xE1

#define ST7735_EXTCTRL	    0xF0

#define MADCTL_MY		    0x80
#define MADCTL_MX		    0x40
#define MADCTL_MV		    0x20
#define MADCTL_ML		    0x10
#define MADCTL_RGB	        0x00
#define MADCTL_BGR	        0x08
#define MADCTL_MH		    0x04

#define COLOR_RED 	        (0xF843)
#define COLOR_GREEN         (0x07E2)
#define COLOR_BLUE          (0x15FF)

#define COLOR_WHITE	        (0xFFFF)
#define COLOR_YELLOW        (0xFEA0)
#define COLOR_GRAY	        (0x636E)
#define COLOR_BLACK         (0x0000)

//#define LCD_ROTATE_GRAD_0
#define LCD_ROTATE_GRAD_90
//#define LCD_ROTATE_GRAD_180
//#define LCD_ROTATE_GRAD_270

#if defined(LCD_ROTATE_GRAD_0)

	#define	NUM_COLS       128
	#define NUM_ROWS       160
	#define MADCTL_ROTATE_MASK 0x00

#elif defined(LCD_ROTATE_GRAD_90)

	#define	NUM_COLS       159
	#define NUM_ROWS       127
	#define MADCTL_ROTATE_MASK (MADCTL_MV | MADCTL_MY)

#elif defined(LCD_ROTATE_GRAD_180)

	#define	NUM_COLS	   128
	#define NUM_ROWS	   160
	#define MADCTL_ROTATE_MASK (MADCTL_MX | MADCTL_MY)

#elif defined(LCD_ROTATE_GRAD_270)

	#define	NUM_COLS	   159
	#define NUM_ROWS	   127
	#define MADCTL_ROTATE_MASK (MADCTL_MV | MADCTL_MX)

#endif

void LCD_st7735sInit(void);
void LCD_SetAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

#endif
