#include "main.h"
#include "gpio.h"
#include "lcd.h"
#include "lcd_gui.h"
#include "lcd_bitmap.h"
#include "stm32l4xx_hal.h"

extern uint16_t lcdColorGlobal;

void LCD_GUI_SleepIn(void)
{
  ADDR_CMD = ST7735_SLPIN;
}

void LCD_GUI_SleepOut(void)
{
  ADDR_CMD = ST7735_SLPOUT;
  HAL_Delay(120);
}

/**
  * @brief  Used to initialize the LCD
  * @retval None
  */
void LCD_GUI_Init(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

  DMA1_Channel4->CCR  |=  DMA_CCR_MEM2MEM;
  DMA1_Channel4->CPAR  =  (uint32_t)0;
  DMA1_Channel4->CMAR  =  (uint32_t)0x60010000;
  DMA1_Channel4->CCR  &= ~DMA_CCR_DIR;
  DMA1_Channel4->CCR  |=  DMA_CCR_PINC;
  DMA1_Channel4->CCR  &= ~DMA_CCR_MINC;
  DMA1_Channel4->CCR  &= ~DMA_CCR_PSIZE;
  DMA1_Channel4->CCR  &= ~DMA_CCR_MSIZE;
  DMA1_Channel4->CCR |=  DMA_CCR_PL;
  DMA1_Channel4->CCR  &= ~DMA_CCR_CIRC;
  DMA1->IFCR          |=  DMA_IFCR_CGIF4;

  LCD_st7735sInit();

  lcdColorGlobal = COLOR_BLACK;
  LCD_DrawPicture(0, 0, NUM_COLS, NUM_ROWS, &lcdColorGlobal, 0);
  HAL_Delay(50);
}

void LCD_GUI_Logo(void)
{
  uint8_t x_start = X_ADDRESS_START_BLACK_WINDOW;
  uint8_t y_start = Y_ADDRESS_START_BLACK_WINDOW;
  uint8_t x_end = X_ADDRESS_END_BLACK_WINDOW;
  uint8_t y_end = Y_ADDRESS_END_BLACK_WINDOW;
  lcdColorGlobal = COLOR_BLACK;

  LCD_DrawPicture(x_start, y_start, x_end, y_end, &lcdColorGlobal, 0);

  x_start = X_ADDRESS_LOGO_PICTURE;
  y_start = Y_ADDRESS_LOGO_PICTURE;
  x_end   = (X_ADDRESS_LOGO_PICTURE + bmLogo[0] - 1);
  y_end   = (Y_ADDRESS_LOGO_PICTURE + bmLogo[1] - 1);
  LCD_DrawPicture(x_start, y_start, x_end, y_end, &bmLogo[2], 1);
}

void LCD_GUI_MainUnitUpdating(void)
{
  uint8_t x_start = X_ADDRESS_START_BLACK_WINDOW;
  uint8_t y_start = Y_ADDRESS_START_BLACK_WINDOW;
  uint8_t x_end   = X_ADDRESS_END_BLACK_WINDOW;
  uint8_t y_end   = Y_ADDRESS_END_BLACK_WINDOW;
  uint8_t text0[] = "DFU";
  lcdColorGlobal  = COLOR_BLACK;

  LCD_DrawPicture(x_start, y_start, x_end, y_end, &lcdColorGlobal, 0);

  x_start = X_ADDRESS_START_MAIN_UNIT_UPDATING_PICTURE;
  y_start = Y_ADDRESS_START_MAIN_UNIT_UPDATING_PICTURE;
  x_end   = (X_ADDRESS_START_MAIN_UNIT_UPDATING_PICTURE + bmMainUnitUpdating[0] - 1);
  y_end   = (Y_ADDRESS_START_MAIN_UNIT_UPDATING_PICTURE + bmMainUnitUpdating[1] - 1);
  LCD_DrawPicture(x_start, y_start, x_end, y_end, &bmMainUnitUpdating[2], 1);

  x_start = X_ADDRESS_START_MAIN_UNIT_UPDATING_TEXT0;
  y_start = Y_ADDRESS_START_MAIN_UNIT_UPDATING_TEXT0;
  LCD_GUI_put_text_roboto_12_Light(x_start, y_start, sizeof(text0), text0, COLOR_WHITE);
}

void LCD_GUI_pictureToggle(void)
{
	static uint8_t toggle = 0;
  uint8_t x_start = X_ADDRESS_START_PICTURE_TOGGLE;
  uint8_t y_start = Y_ADDRESS_START_PICTURE_TOGGLE;
  uint8_t x_end   = X_ADDRESS_END_PICTURE_TOGGLE;
  uint8_t y_end   = Y_ADDRESS_END_PICTURE_TOGGLE;

  if(toggle)
  {
    lcdColorGlobal = COLOR_GREEN;
  }
  else
  {
  	lcdColorGlobal = COLOR_BLACK;
  }

  toggle ^= 0x01;

  LCD_DrawPicture(x_start, y_start, x_end, y_end, &lcdColorGlobal, 0);
}

/**
  * @brief  Used to put char
  * @retval None
  */

uint8_t LCD_GUI_PutChar(uint8_t c, uint16_t  x, uint16_t  y, FONT_INFO *pFont, uint16_t fColor, uint16_t bColor)
{
	uint8_t char_index = c - pFont->start_character;
	uint16_t char_offset = pFont->char_info_desc[char_index].bitmap_offset;
	uint8_t char_width = pFont->char_info_desc[char_index].char_width;
	uint8_t nCols = char_width;
	uint8_t nRows = pFont->character_height;
	const uint8_t *pChar = &(pFont->pchar_bitmaps[char_offset]);
	uint8_t	 i, j;
	uint16_t f_b_Colors[2] = {fColor, bColor};

	if(nCols <= 8)
	{
		nCols = 8;
	}
	else if((8 < nCols) && (nCols <= 16))
	{
		nCols = 16;
	}
	else
	{
		nCols = 24;
	}

	LCD_SetAddrWindow(x, y, (x + nCols - 1), (y + nRows - 1));
	ADDR_CMD = ST7735_RAMWR;
	uint8_t PixelRow = *pChar++;
	uint8_t Mask = 0x80;
	for(i = 0; i < nRows; i++)
	{
		for(j = 0; j < nCols; j++)
		{
			// if pixel bit set, use foreground color; else use the background color
			uint16_t b = f_b_Colors[!(PixelRow & Mask)];
			ADDR_DATA = (b >> 8);
			ADDR_DATA = (b);
			Mask >>= 1;
			if((j == 7) || (j == 15) || (j == 23))
			{
				PixelRow = *pChar++;
				Mask = 0x80;
			}
		}
	}
	ADDR_CMD = ST7735_NOP;

	return char_width;
}

void LCD_GUI_put_text_roboto_12_Light(uint8_t x0, uint8_t y0, uint8_t textSize, uint8_t* symb_12_Light, uint16_t textColor)
{
  if(DMA1_Channel4->CCR & DMA_CCR_EN)
  {
    while(!(DMA1->ISR & DMA_ISR_TCIF4)){
    };
    DMA1->IFCR |=  DMA_IFCR_CGIF4;
    DMA1_Channel4->CCR &=~ DMA_CCR_EN;
  }

  for(uint8_t i = 0; i < textSize; i++)
  {
	uint8_t x = x0;
	uint8_t y_local;
	uint8_t* font_bmp_ptr    = (uint8_t*)robotoLight_12ptBitmaps;
	uint8_t  font_bmp_width  = robotoLight_12ptDescriptors[2*(symb_12_Light[i] - ' ') + 0];
	uint16_t font_bmp_offset = robotoLight_12ptDescriptors[2*(symb_12_Light[i] - ' ') + 1];

	for(uint16_t x_local = 0; x_local <= font_bmp_width; x_local++)
	{
	  y_local = y0;

	  if(x_local == font_bmp_width)
	  {
		x0 +=2;
		break;
	  }

	  for(uint8_t y_mask = 0x01; y_mask != 0; y_mask <<= 1)
	  {
	    if(y_mask > 0x08)
	    {
	      LCD_SetPixel(x_local + x + 1, y_local + 1 + 0,  (font_bmp_ptr[font_bmp_offset + 2 + x_local * 3] & y_mask) ? textColor : COLOR_BLACK);
	    }

	    LCD_SetPixel(x_local + x + 1, y_local + 1 + 0, (font_bmp_ptr[font_bmp_offset + 1 + x_local * 3] & y_mask) ? textColor : COLOR_BLACK);
    	LCD_SetPixel(x_local + x + 1, y_local + 1 + 8, (font_bmp_ptr[font_bmp_offset + 0 + x_local * 3] & y_mask) ? textColor : COLOR_BLACK);
		y_local++;
	  }
		x0++;
	}
  }
}

void LCD_GUI_PutStr(const uint8_t *pString, uint16_t  x, uint16_t  y, FONT_INFO *pFont, uint16_t fColor, uint16_t bColor)
{
	// loop until null-terminator is seen
	while(*pString)
	{
		// draw the character
		x += LCD_GUI_PutChar(*pString++, x, y, (FONT_INFO*)pFont, fColor, bColor) + 2;
		if(x > NUM_COLS)
		break;
	}
}
