#include "lcd.h"
#include "stm32l4xx_hal.h"

uint16_t lcdColorGlobal;

/**
  * @brief  Used to set a pixel
  * @retval None
  */
void LCD_SetPixel(uint16_t  x, uint16_t  y, uint16_t  color)
{
	LCD_SetAddrWindow(x, y, x, y);

	ADDR_CMD  = ST7735_RAMWR;
    ADDR_DATA = (color >> 8);
    ADDR_DATA = (color);
}

/**
  * @brief  Used to fill a block by some color or draw a picture
  * @param  x1 - start address horizontal (0...159)
  *         y1 - start adress vertical    (0...127)
  *         x2 - end address horizontal   (0...159)
  *         y2 - end address vertical     (0...127)
  * @retval None
  */
void LCD_DrawPicture(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t *pBuf, uint8_t fillBm)
{
	if(DMA1_Channel4->CCR & DMA_CCR_EN)
	{
	  while(!(DMA1->ISR & DMA_ISR_TCIF4)){
      };
	  DMA1->IFCR |=  DMA_IFCR_CGIF4;
	  DMA1_Channel4->CCR &=~ DMA_CCR_EN;
	}

	LCD_SetAddrWindow(x1, y1, x2, y2);
	ADDR_CMD = ST7735_RAMWR;

	if(fillBm)
	{
	  DMA1_Channel4->CCR  |= DMA_CCR_PINC;
	  DMA1_Channel4->CPAR  = (uint32_t)(pBuf);
	  DMA1_Channel4->CNDTR = ((((x2 - x1) + 1)  * ((y2 - y1) + 1)) << 1); // the << 1 operation for multiplication by 2
	  DMA1_Channel4->CCR |= DMA_CCR_EN;
	}
	else
	{
	  for (uint8_t y = y1; y <= y2; y++)
	  {
	    for (uint8_t x = x1; x <= x2; x++)
		{
	    	ADDR_DATA = (*pBuf >> 8);
	    	ADDR_DATA = (*pBuf);
		}
	  }
	}
}

/**
  * @brief  Draws a line in the specified color from (x0,y0) to (x1,y1)
  *         Rectangle can be filled with a color if desired
  * @retval None
  */
void LCD_SetLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	if((x0 != x1) || (y0 != y1))
	{
		// ��������� �����
		int16_t dy = y1 - y0;
		int16_t dx = x1 - x0;
		int16_t stepx, stepy;

		if(dy < 0)
		{
			dy = -dy;
			stepy = -1;
		}
		else
		{
			stepy = 1;
		}
		if (dx < 0)
		{
			dx = -dx;
			stepx = -1;
		}
		else
		{
			stepx = 1;
		}
		dy <<= 1;        /* dy is now 2*dy */
		dx <<= 1;        /* dx is now 2*dx */
		LCD_SetPixel(x0, y0, color);
		if(dx > dy)
		{
			int fraction = dy - (dx >> 1);  // same as 2*dy - dx
			while(x0 != x1)
			{
				if(fraction >= 0)
				{
					y0 += stepy;
					fraction -= dx;    // same as fraction -= 2*dx
				}
			x0 += stepx;
			fraction += dy;    // same as fraction -= 2*dy
			LCD_SetPixel(x0, y0, color);
			}
		}
		else
		{
			int16_t fraction = dx - (dy >> 1);
			while(y0 != y1)
			{
				if(fraction >= 0)
				{
					x0 += stepx;
					fraction -= dy;
				}
				y0 += stepy;
				fraction += dx;
				LCD_SetPixel(x0, y0, color);
			}
		}
	}
}

/**
  * @brief  Used to do circles and roundrects
  * @retval None
  */
void LCD_FillCircleHelper(int16_t x0, int16_t y0, int16_t radius, uint8_t cornername, int16_t delta, uint16_t color)
{
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t r = radius;

	while (x < r)
	{
		if(f >= 0)
		{
			r--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if(cornername & 0x1)
		{
			LCD_SetLine(x0 + x, y0 - r, x0 + x, y0 + r + delta, color);
			LCD_SetLine(x0 + r, y0 - x, x0 + r, y0 + x + delta, color);
		}
		if(cornername & 0x2)
		{
			LCD_SetLine(x0 - x, y0 - r, x0 - x, y0 + r + delta, color);
			LCD_SetLine(x0 - r, y0 - x, x0 - r, y0 + x + delta, color);
		}
	}
}

/**
  * @brief  Used to do vertical line
  * @retval None
  */
void LCD_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	LCD_SetLine(x, y, x, y+h-1, color);
}

/**
  * @brief  Used to do horizontal line
  * @retval None
  */
void LCD_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	LCD_SetLine(x, y, x+w-1, y, color);
}

/**
  * @brief  Used to draw four corners of the Round Rect
  * @retval None
  */
void LCD_DrawCircleHelper(int16_t x0, int16_t y0, int16_t radius, uint8_t cornername, uint16_t color)
{
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t r = radius;

	while(x < r)
	{
		if(f >= 0)
		{
			r--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if(cornername & 0x4)
		{
			LCD_SetPixel(x0 + x, y0 + r, color);
			LCD_SetPixel(x0 + r, y0 + x, color);
		}
		if(cornername & 0x2)
		{
			LCD_SetPixel(x0 + x, y0 - r, color);
			LCD_SetPixel(x0 + r, y0 - x, color);
		}
		if(cornername & 0x8)
		{
			LCD_SetPixel(x0 - r, y0 + x, color);
			LCD_SetPixel(x0 - x, y0 + r, color);
		}
		if(cornername & 0x1)
		{
			LCD_SetPixel(x0 - r, y0 - x, color);
			LCD_SetPixel(x0 - x, y0 - r, color);
		}
	}
}


/**
  * @brief  Used to draw fill circle
  * @retval None
  */
void LCD_DrawFillCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color)
{
	LCD_SetLine(x0, y0 - radius, x0, y0 + radius, color);
	LCD_FillCircleHelper(x0, y0, radius, 3, 0, color);
}

#if USE_RECT_FUNCTIONS

/**
  * @brief  Used to draw a rounded rectangle
  * @param  x     = column address
  *         y     = row address
  *         w     = width
  *         h     = height
  *         r     = radius
  *         color = color
  * @retval None
  */
void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
	// smarter version
	LCD_DrawFastHLine(x+r, y, w-2*r, color);		// Top
	LCD_DrawFastHLine(x+r, y+h-1, w-2*r, color);	// Bottom
	LCD_DrawFastVLine(x, y+r, h-2*r, color);		// Left
	LCD_DrawFastVLine(x+w-1, y+r, h-2*r, color);	// Right
	// draw four corners
	LCD_DrawCircleHelper(x+r, y+r, r, 1, color);
	LCD_DrawCircleHelper(x+w-r-1, y+r, r, 2, color);
	LCD_DrawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	LCD_DrawCircleHelper(x+r, y+h-r-1, r, 8, color);
}

/**
  * @brief  Used to fill a rounded rectangle
  * @retval None
  */
void LCD_DrawFillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
//	LCD_DrawPicture(x+r, y, x+w-r, y+h-1, (uint16_t*)0);

	/* draw four corners*/
	LCD_FillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	LCD_FillCircleHelper(x+r, y+r, r, 2, h-2*r-1, color);
}

/**
  * @brief  Draws a rectangle in the specified color from (x1,y1) to (x2,y2)
  *         Rectangle can be filled with a color if desired
  * @retval None
  */
void LCD_SetRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t fill, uint16_t color)
{
  // check if the rectangle is to be filled
  if(fill == FILL)
  {
    // best way to create a filled rectangle is to define a drawing box
    // and loop two pixels at a time
	  LCD_DrawPicture(x0, y0, x1, y1, (uint16_t*)0);
  }
  else
  {
       // best way to draw un unfilled rectangle is to draw four lines
//	  LCD_DrawPicture(x0, y0, x1, y0, (uint16_t*)0);
//	  LCD_DrawPicture(x0, y1, x1, y1, (uint16_t*)0);
//	  LCD_DrawPicture(x0, y0, x0, y1, (uint16_t*)0);
//	  LCD_DrawPicture(x1, y0, x1, y1, (uint16_t*)0);
  }
}

#endif

/**
  * @brief  Draws a line in the specified color at center (x0,y0) with radius
  * @retval None
  */
void LCD_SetCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color)
{
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	uint16_t x = 0;
	uint16_t r = radius;

	LCD_SetPixel(x0, y0 + radius, color);
	LCD_SetPixel(x0, y0 - radius, color);
	LCD_SetPixel(x0 + radius, y0, color);
	LCD_SetPixel(x0 - radius, y0, color);

	while(x < r)
	{
		if(f >= 0)
		{
			r--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		LCD_SetPixel(x0 + x, y0 + r, color);
		LCD_SetPixel(x0 - x, y0 + r, color);
		LCD_SetPixel(x0 + x, y0 - r, color);
		LCD_SetPixel(x0 - x, y0 - r, color);
		LCD_SetPixel(x0 + r, y0 + x, color);
		LCD_SetPixel(x0 - r, y0 + x, color);
		LCD_SetPixel(x0 + r, y0 - x, color);
		LCD_SetPixel(x0 - r, y0 - x, color);
	}
}
