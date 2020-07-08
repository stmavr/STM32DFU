#ifndef _flash_h_
#define _flash_h_

#include "stdint.h"

void FLASH_Unlock(void);
void FLASH_Lock(void);
uint8_t FLASH_Erase(uint8_t page, uint16_t numberPages, uint8_t bank);
uint8_t FLASH_ProgramData(uint32_t address, uint8_t* data);

#endif
