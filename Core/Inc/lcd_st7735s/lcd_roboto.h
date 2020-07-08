#ifndef _lcd_roboto_h_
#define _lcd_roboto_h_

#include "stdint.h"

typedef struct
{
  uint8_t char_width;			// Char width in bits
  uint16_t bitmap_offset;		// Offset into bitmap array in bytes
} FONT_CHAR_INFO;

typedef struct
{
  uint8_t character_height;				// Character height
  uint8_t start_character;				// Start character
  uint8_t end_character;					// End character
  const FONT_CHAR_INFO* char_info_desc;	// Character descriptor array
  const uint8_t* pchar_bitmaps;			// Character bitmap array
} FONT_INFO;

extern const uint8_t roboto_8ptBitmaps[];
extern const uint16_t roboto_8ptDescriptors[];

extern const uint8_t robotoLight_12ptBitmaps[];
extern const uint16_t robotoLight_12ptDescriptors[];

extern const uint8_t robotoMedium_26ptBitmaps[];
extern const uint16_t robotoMedium_26ptDescriptors[];

#endif
