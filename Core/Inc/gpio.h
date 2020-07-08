#ifndef _gpio_h_
#define _gpio_h_

#include "stm32l4xx_hal.h"
#include "stdint.h"

#define EXTERNAL_UNIT_TX_PIN                      (GPIO_PIN_2)
#define EXTERNAL_UNIT_RX_PIN                      (GPIO_PIN_3)
#define EXTERNAL_UNIT_PORT                        (GPIOA)

#define ADXL_CS_PIN			                      (GPIO_PIN_4)
#define ADXL_SCK_PIN		                      (GPIO_PIN_5)
#define ADXL_MISO_PIN		                      (GPIO_PIN_6)
#define ADXL_MOSI_PIN		                      (GPIO_PIN_7)
#define ADXL_PORT	                              (GPIOA)
#define ADXL_CS_SET()	                          (ADXL_PORT->BSRR = GPIO_BSRR_BS_4)
#define ADXL_CS_RESET()		                      (ADXL_PORT->BSRR = GPIO_BSRR_BR_4)

#define SD_CD_PIN                                 (GPIO_PIN_8)
#define SD_CD_PORT                                (GPIOA)
#define SD_PWR_PIN                                (GPIO_PIN_5)
#define SD_PWR_PORT                               (GPIOB)
#define SD_POWER_ON()	                          (SD_PWR_PORT->BSRR = GPIO_BSRR_BR_5)
#define SD_POWER_OFF()		                      (SD_PWR_PORT->BSRR = GPIO_BSRR_BS_5)

#define OEM_TX_PIN                                (GPIO_PIN_9)
#define OEM_RX_PIN                                (GPIO_PIN_10)
#define OEM_TX_RX_PORT                            (GPIOA)
#define OEM_MOUDULE_ID_PIN                        (GPIO_PIN_6)
#define OEM_RST_PIN                               (GPIO_PIN_7)
#define OEM_SENSTYPE_PIN                          (GPIO_PIN_8)
#define OEM_PWR_PIN                               (GPIO_PIN_9)
#define OEM_CONTROL_PIN                           (GPIO_PIN_10)
#define OEM_PORT                                  (GPIOB)

#define OEM_POWER_OFF()                           (OEM_PORT->BSRR = GPIO_BSRR_BS_9)

#define OEM_RST_SET()                             (OEM_PORT->BSRR = GPIO_BSRR_BS_7)
#define OEM_RST_RESET()                           (OEM_PORT->BSRR = GPIO_BSRR_BR_7)

#define LCD_PWR_PIN                               (GPIO_PIN_0)
#define LCD_LIGHT_PIN                             (GPIO_PIN_2)
#define LCD_PORT                                  (GPIOB)
#define LCD_RST_PIN                               (GPIO_PIN_6)
#define LCD_RST_PORT                              (GPIOD)
#define LCD_POWER_ON()                            (LCD_PORT->BSRR = GPIO_BSRR_BR_0)
#define LCD_POWER_OFF()                           (LCD_PORT->BSRR = GPIO_BSRR_BS_0)
#define LCD_LIGHT_ON()                            (LCD_PORT->BSRR = GPIO_BSRR_BR_2)
#define LCD_LIGHT_OFF()                           (LCD_PORT->BSRR = GPIO_BSRR_BS_2)
#define LCD_RST_SET()                             (LCD_RST_PORT->BSRR = GPIO_BSRR_BS_6)
#define LCD_RST_RESET()                           (LCD_RST_PORT->BSRR = GPIO_BSRR_BR_6)

#define MUX_S_PIN                                 (GPIO_PIN_3)
#define MUX_PORT                                  (GPIOB)
#define MUX_S_SET()                               (MUX_PORT->BSRR = GPIO_BSRR_BS_3)
#define MUX_S_RESET()                             (MUX_PORT->BSRR = GPIO_BSRR_BR_3)

#define HUB_PWR_PIN                               (GPIO_PIN_4)
#define HUB_PWR_PORT                              (GPIOB)
#define HUB_RST_PIN                               (GPIO_PIN_7)
#define HUB_RST_PORT                              (GPIOC)
#define HUB_POWER_ON()                            (HUB_PWR_PORT->BSRR = GPIO_BSRR_BR_4)
#define HUB_POWER_OFF()                           (HUB_PWR_PORT->BSRR = GPIO_BSRR_BS_4)
#define HUB_RST_SET()                             (HUB_RST_PORT->BSRR = GPIO_BSRR_BS_7)
#define HUB_RST_RESET()                           (HUB_RST_PORT->BSRR = GPIO_BSRR_BR_7)

#define BATTERY_MEASURE_PIN                       (GPIO_PIN_0)
#define BATTERY_MEASURE_PORT                      (GPIOC)
#define BATTERY_MEASURE_POWER_PIN                 (GPIO_PIN_2)
#define BATTERY_MEASURE_POWER_PORT                (GPIOE)
#define BATTERY_MEASURE_ON()                      (BATTERY_MEASURE_POWER_PORT->BSRR = GPIO_BSRR_BR_2)
#define BATTERY_MEASURE_OFF()                     (BATTERY_MEASURE_POWER_PORT->BSRR = GPIO_BSRR_BS_2)

#define BREATH_MEASURE_PIN                        (GPIO_PIN_1)
#define BREATH_MEASURE_PORT                       (GPIOC)

#define USER_BUTTON_PIN                           (GPIO_PIN_0)
#define USER_BUTTON_PORT                          (GPIOE)

#define DC_ENABLE_PIN                             (GPIO_PIN_1)
#define DC_ENABLE_PORT                            (GPIOE)
#define DC_POWER_ON()                             (DC_ENABLE_PORT->BSRR = GPIO_BSRR_BS_1)
#define DC_POWER_OFF()                            (DC_ENABLE_PORT->BSRR = GPIO_BSRR_BR_1)

#define USB_DETECTED_PIN                          (GPIO_PIN_3)
#define USB_DETECTED_PORT                         (GPIOE)

void GPIO_Init(void);

#endif
