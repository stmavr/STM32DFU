#include "gpio.h"
#include "main.h"

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /************************************************************************/
  /********************************USB DETECTED****************************/
  /************************************************************************/

  GPIO_InitStruct.Pin   = USB_DETECTED_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_DETECTED_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /******************************USER BUTTON*******************************/
  /************************************************************************/

  GPIO_InitStruct.Pin   = USER_BUTTON_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USER_BUTTON_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /******************************SENSER TYPE*******************************/
  /************************************************************************/

  GPIO_InitStruct.Pin   = OEM_SENSTYPE_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OEM_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /********************************DC/DC CONVERTER*************************/
  /************************************************************************/

  GPIO_InitStruct.Pin   = DC_ENABLE_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DC_ENABLE_PORT, &GPIO_InitStruct);

#ifndef DEBUG_MODE
  if(!(USB_DETECTED_PORT->IDR & USB_DETECTED_PIN))
  {
	if(!(USER_BUTTON_PORT->IDR & USER_BUTTON_PIN) || !(OEM_PORT->IDR & OEM_SENSTYPE_PIN))
	{
	  DC_POWER_ON();
	}
	else
	{
	  DC_POWER_OFF();
	  while(1){
	  };
	}
  }

  HAL_Delay(300); // waiting for read all the sensors of this device
#endif

  /************************************************************************/
  /*************************************OEM MODULE*************************/
  /************************************************************************/

  OEM_POWER_OFF();
  OEM_RST_RESET();

  GPIO_InitStruct.Pin   = (OEM_TX_PIN|OEM_RX_PIN);
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(OEM_TX_RX_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = (OEM_MOUDULE_ID_PIN);
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OEM_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = (OEM_RST_PIN|OEM_PWR_PIN|OEM_CONTROL_PIN);
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OEM_PORT, &GPIO_InitStruct);

 // OEM_POWER_ON();

  /************************************************************************/
  /*******************************EXTERNAL UNIT****************************/
  /************************************************************************/

  GPIO_InitStruct.Pin   = (EXTERNAL_UNIT_TX_PIN|EXTERNAL_UNIT_RX_PIN);
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(EXTERNAL_UNIT_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /*******************************ACCELEROMETER****************************/
  /************************************************************************/

  ADXL_CS_SET();

  GPIO_InitStruct.Pin 	= ADXL_CS_PIN;
  GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull 	= GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(ADXL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = (ADXL_SCK_PIN|ADXL_MOSI_PIN|ADXL_MISO_PIN);
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(ADXL_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /*************************************LCD********************************/
  /************************************************************************/

  LCD_POWER_OFF();
  LCD_RST_RESET();
  LCD_LIGHT_OFF();

  GPIO_InitStruct.Pin 	= (LCD_PWR_PIN|LCD_LIGHT_PIN);
  GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull 	= GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = LCD_RST_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RST_PORT, &GPIO_InitStruct);

  LCD_POWER_ON();
  LCD_RST_SET();

  /*All other pins of the LCD configure in FSMC module*/

  /************************************************************************/
  /*************************************SD_CARD****************************/
  /************************************************************************/

  SD_POWER_OFF();

  GPIO_InitStruct.Pin   = SD_CD_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_CD_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = SD_PWR_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_PWR_PORT, &GPIO_InitStruct);

  SD_POWER_ON();

  /*All other pins of the SD_CARD configure in SDIO module*/

  /************************************************************************/
  /*************************************MULTIPLEXER************************/
  /************************************************************************/

  /*
   * S pin is SET   -> sd_card connecting to STM32
   * S pin is RESET -> sd_card connecting to HUB
   */

  MUX_S_SET();

  GPIO_InitStruct.Pin   = MUX_S_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MUX_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /*************************************HUB********************************/
  /************************************************************************/

  HUB_POWER_OFF();
  HUB_RST_RESET();

  GPIO_InitStruct.Pin   = HUB_PWR_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HUB_PWR_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = HUB_RST_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HUB_RST_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /******************************BATTERY***********************************/
  /************************************************************************/

  BATTERY_MEASURE_ON();

  GPIO_InitStruct.Pin   = BATTERY_MEASURE_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BATTERY_MEASURE_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = BATTERY_MEASURE_POWER_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BATTERY_MEASURE_POWER_PORT, &GPIO_InitStruct);

  /************************************************************************/
  /******************************BREATH************************************/
  /************************************************************************/

  GPIO_InitStruct.Pin   = BREATH_MEASURE_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BREATH_MEASURE_PORT, &GPIO_InitStruct);
}
