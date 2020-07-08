#include "flash.h"
#include "stm32l4xx_hal.h"

void FLASH_Unlock(void)
{
  if(FLASH->CR & FLASH_CR_LOCK)
  {
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
  }

  FLASH->SR |= FLASH_SR_OPTVERR;
}

void FLASH_Lock(void)
{
  if(!(FLASH->CR & FLASH_CR_LOCK))
  {
    FLASH->CR |= FLASH_CR_LOCK;
  }
}

/**
  * @brief  Used to erase flash of the MCU
  * @param  page: page to erase and start page  : 0...255
  *         numberPages: number pages to earase : 1...256
  *         bank: bank number to erase          : 1,2
  * @retval 0 - OK, 1 - ERROR
  */
uint8_t FLASH_Erase(uint8_t page, uint16_t numberPages, uint8_t bank)
{
  if((bank == 1) || (bank == 2))
  {
    while(FLASH->SR & FLASH_SR_BSY){
    };

    FLASH->SR |= FLASH_SR_PGSERR;

    FLASH->ACR &= ~FLASH_ACR_ICEN;
    FLASH->ACR &= ~FLASH_ACR_DCEN;

    for(uint16_t i = 0; i < numberPages; i++, page++)
    {
      FLASH->CR |= FLASH_CR_PER;
      FLASH->CR |= (page << FLASH_CR_PNB_Pos);

      if(bank == 1)
      {
        FLASH->CR &= ~FLASH_CR_BKER;
      }

      if(bank == 2)
      {
        FLASH->CR |= FLASH_CR_BKER;
      }

      FLASH->CR |= FLASH_CR_STRT;
      while(FLASH->SR & FLASH_SR_BSY){
      };
    }

	 //only after erase all pages which you did want
	 FLASH->CR &= ~FLASH_CR_PER;
	 FLASH->CR &= ~FLASH_CR_PNB;
	 FLASH->CR &= ~FLASH_CR_BKER;

	 FLASH->ACR |=  FLASH_ACR_ICRST;
	 FLASH->ACR &= ~FLASH_ACR_ICRST;
	 FLASH->ACR |=  FLASH_ACR_ICEN;

	 FLASH->ACR |=  FLASH_ACR_DCRST;
	 FLASH->ACR &= ~FLASH_ACR_DCRST;
	 FLASH->ACR |=  FLASH_ACR_DCEN;

	 if(FLASH->SR == 0)
	 {
		 return 0;
	 }
  }
	  return 1;
}

uint8_t FLASH_ProgramData(uint32_t address, uint8_t* data)
{
  if((address < 0x080FFFF8) || (address > 0x08000000))
  {
    while(FLASH->SR & FLASH_SR_BSY){
    };

    FLASH->SR |= FLASH_SR_PGSERR;

    FLASH->ACR &= ~FLASH_ACR_DCEN;

    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint32_t*)(address) = *(uint32_t*)(data);
    __ISB();
    *(__IO uint32_t*)(address + 4) = *(uint32_t*)(data + 4);
    while(FLASH->SR & FLASH_SR_BSY){
    };

    FLASH->CR &= ~FLASH_CR_PG;

    FLASH->ACR |=  FLASH_ACR_DCRST;
    FLASH->ACR &= ~FLASH_ACR_DCRST;
    FLASH->ACR |=  FLASH_ACR_DCEN;

    if(FLASH->SR == 0)
    {
	  return 0;
    }
  }

  return 1;
}
