/*
 * LED.h
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */

#include "stm32f091xc.h"

#ifndef LED_H
#define LED_H

#define BLINK_FAST_INTERVAL   25   // Blink interval for fast blinking (25 ms)
#define BLINK_MEDIUM_INTERVAL 150  // Blink interval for medium blinking (150 ms)
#define BLINK_SLOW_INTERVAL   500  // Blink interval for slow blinking (500 ms)
#define BIT_SHIFT_BASE 1U



typedef enum { LED_OFF, LED_ON, BLINK_FAST, BLINK_MEDIUM, BLINK_SLOW } LED_State;

void LED_Control(LED_State state);

#endif // LED_H
