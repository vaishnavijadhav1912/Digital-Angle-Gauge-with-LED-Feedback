/*
 * timer.h
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */

#include <stdint.h>

#ifndef TIMER_H_
#define TIMER_H_

extern volatile uint32_t timer_ticks;



// Initialize SysTick timer
void SysTick_Init(uint32_t ticks_per_second);

// Delay in milliseconds
void Delay_ms(uint32_t ms);

// Get the current value of the timer in milliseconds
uint32_t Timer_GetTicks(void);


#endif /* TIMER_H_ */
