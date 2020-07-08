#include "lcd_st7735s.h"
#include "stm32l4xx_hal.h"
#include "gpio.h"

static void delay(uint32_t delay);

void LCD_st7735sInit(void)
{
	LCD_RST_SET();
	delay(1);
	LCD_RST_RESET();
	delay(1);
	LCD_RST_SET();
	delay(1);
	LCD_RST_RESET();
	delay(1);
	LCD_RST_SET();

	ADDR_CMD = ST7735_SWRESET; // software reset
	HAL_Delay(10);
	ADDR_CMD = ST7735_SLPOUT;  // out of sleep mode
	HAL_Delay(120);

	ADDR_CMD = ST7735_FRMCTR1;  // frame rate control - normal mode
	ADDR_DATA = 0x05;  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
	ADDR_DATA = 0x3C;
	ADDR_DATA = 0x3C;

	ADDR_CMD = ST7735_FRMCTR2;  // frame rate control - idle mode
	ADDR_DATA = 0x05;  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
	ADDR_DATA = 0x3C;
	ADDR_DATA = 0x3C;

	ADDR_CMD = ST7735_FRMCTR3;  // frame rate control - partial mode
	ADDR_DATA = 0x01; // dot inversion mode
	ADDR_DATA = 0x3C;
	ADDR_DATA = 0x3C;
	ADDR_DATA = 0x05; // line inversion mode
	ADDR_DATA = 0x3C;
	ADDR_DATA = 0x3C;

	ADDR_CMD = ST7735_INVCTR;  // display inversion control
	ADDR_DATA = 0x07;  // no inversion

	ADDR_CMD = 0xB6;
	ADDR_DATA = 0x84;
	ADDR_DATA = 0xF0;
	ADDR_DATA = 0x20;

	ADDR_CMD = ST7735_PWCTR1;  // power control
	ADDR_DATA = 0xB4;
	ADDR_DATA = 0x14;      // -4.6V
	ADDR_DATA = 0x04;      // AUTO mode

	ADDR_CMD = ST7735_PWCTR2;  // power control
	ADDR_DATA = 0xC0;      // VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD

	ADDR_CMD = ST7735_PWCTR3;  // power control
	ADDR_DATA = 0x0A;      // Opamp current small
	ADDR_DATA = 0x00;      // Boost frequency

	ADDR_CMD = ST7735_PWCTR4;  // power control
	ADDR_DATA = 0x8A;      // BCLK/2, Opamp current small & Medium low
	ADDR_DATA = 0x2A;

	ADDR_CMD = ST7735_PWCTR5;  // power control
	ADDR_DATA = 0x8A;
	ADDR_DATA = 0xAA;

	ADDR_CMD = ST7735_VMCTR1;  // power control
	ADDR_DATA = 0x00;

	ADDR_CMD = ST7735_INVOFF;    // don't invert display

	ADDR_CMD = ST7735_MADCTL;	// memory access control (directions)
	ADDR_DATA = (MADCTL_ROTATE_MASK | MADCTL_BGR);	// row address/col address, top to bottom refresh

	ADDR_CMD = ST7735_COLMOD;  // set color mode
	ADDR_DATA = 0x05;        // 16-bit color

	ADDR_CMD = ST7735_GMCTRP1;
	ADDR_DATA = 0x02;
	ADDR_DATA = 0x1c;
	ADDR_DATA = 0x07;
	ADDR_DATA = 0x12;
	ADDR_DATA = 0x37;
	ADDR_DATA = 0x32;
	ADDR_DATA = 0x29;
	ADDR_DATA = 0x2d;
	ADDR_DATA = 0x29;
	ADDR_DATA = 0x25;
	ADDR_DATA = 0x2B;
	ADDR_DATA = 0x39;
	ADDR_DATA = 0x00;
	ADDR_DATA = 0x01;
	ADDR_DATA = 0x03;
	ADDR_DATA = 0x10;
	ADDR_CMD  = ST7735_GMCTRN1;
	ADDR_DATA = 0x03;
	ADDR_DATA = 0x1d;
	ADDR_DATA = 0x07;
	ADDR_DATA = 0x06;
	ADDR_DATA = 0x2E;
	ADDR_DATA = 0x2C;
	ADDR_DATA = 0x29;
	ADDR_DATA = 0x2D;
	ADDR_DATA = 0x2E;
	ADDR_DATA = 0x2E;
	ADDR_DATA = 0x37;
	ADDR_DATA = 0x3F;
	ADDR_DATA = 0x00;
	ADDR_DATA = 0x00;
	ADDR_DATA = 0x02;
	ADDR_DATA = 0x10;

	ADDR_CMD = ST7735_NORON;  // normal display on
    HAL_Delay(10);
	ADDR_CMD = ST7735_DISPON;
}

void LCD_SetAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	ADDR_CMD = ST7735_CASET;	// column addr set
#if (defined(LCD_ROTATE_GRAD_0) || defined(LCD_ROTATE_GRAD_180))

	ADDR_DATA = 0x00;
	ADDR_DATA = x0;	// XSTART
	ADDR_DATA = 0x00;
	ADDR_DATA = x1;	// XEND

#elif (defined(LCD_ROTATE_GRAD_90) || defined(LCD_ROTATE_GRAD_270))

	ADDR_DATA = 0x00;
	ADDR_DATA = x0;	// XSTART
	ADDR_DATA = 0x00;
	ADDR_DATA = x1;	// XEND

#endif

	ADDR_CMD = ST7735_RASET;	// row addr set
#if (defined(LCD_ROTATE_GRAD_0) || defined(LCD_ROTATE_GRAD_180))

	ADDR_DATA = 0x00;
	ADDR_DATA = y0;	// YSTART
	ADDR_DATA = 0x00;
	ADDR_DATA = y1;	// YEND

#elif (defined(LCD_ROTATE_GRAD_90) || defined(LCD_ROTATE_GRAD_270))

	ADDR_DATA = 0x00;
	ADDR_DATA = y0;	// YSTART
	ADDR_DATA = 0x00;
	ADDR_DATA = y1;	// YEND

#endif
}

static void delay(volatile uint32_t delay)
{
	while(delay--){
    };
}
