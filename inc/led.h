#ifndef LED_H_
#define LED_H_

#ifdef STM32F103xB
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>
#else
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#endif

//For DWM1000DISCOVERY Board -- Justin Add
typedef enum {
  ledRanging = GPIO_PIN_10,
  ledSync = GPIO_PIN_11,
  ledMode = GPIO_PIN_12
} Led;

void ledInit(void);

void ledOn(Led led);

void ledOff(Led led);

#endif /* LED_H_ */

