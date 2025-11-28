// buttons.h

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "stm32f3xx_hal.h"

// Define the pins used for the buttons (configured as GPIO_Input)
#define BUTTON_SELECT_PIN   GPIO_PIN_13 // PC13 (Blue Button)
#define BUTTON_SELECT_PORT  GPIOC

#define BUTTON_CYCLE_PIN    GPIO_PIN_0  // PA0 (Black Button)
#define BUTTON_CYCLE_PORT   GPIOA

// Function Prototypes
void BUTTONS_HandleInput(void);

#endif // __BUTTONS_H
