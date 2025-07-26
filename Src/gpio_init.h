/*
 * gpio_init.h
 *
 *  Created on: Dec 11, 2024
 *      Author: vaish
 */
#include "stm32f091xc.h"

#ifndef GPIO_INIT_H_
#define GPIO_INIT_H_


#define GPIO_MODE_MASK          3U   // Mask for 2 bits of GPIO mode
#define GPIO_MODE_OUTPUT        1U   // Output mode configuration
#define GPIO_PIN_SHIFT          2U   // Shift for GPIO pin mode and pull-up/down configuration

#define BUTTON_PIN 13
#define LED_PIN 1
#define push_button 5

void GPIO_Init(void);
void PushButton_PC13_Init_new(void);
int isButtonPressed_new(void);

#endif

