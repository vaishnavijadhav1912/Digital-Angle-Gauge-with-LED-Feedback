/*
 * timers.c
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */


#include "timer.h"
#include "stm32f091xc.h"

volatile uint32_t timer_ticks = 0;

/*
 * SysTick interrupt handler
 * Increments the timer_ticks variable every time the SysTick interrupt is triggered.
 */
void SysTick_Handler(void) {
    timer_ticks++; // Increment the timer tick counter.
}

/*
 * Initialize SysTick for 1 ms ticks.
 *
 * Parameters:
 *   ticks_per_second - Number of ticks per second to configure the SysTick timer.
 *                      For 1 ms ticks, this value should be 1000.
 *
 * Configures the SysTick timer to generate an interrupt at the desired frequency.
 */
void SysTick_Init(uint32_t ticks_per_second) {
    uint32_t reload_value = SystemCoreClock / ticks_per_second - 1; // Calculate reload value for desired tick rate.

    // Configure SysTick
    SysTick->LOAD = reload_value;
    SysTick->VAL = 0; // Clear current value
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | // Use processor clock
                    SysTick_CTRL_TICKINT_Msk |   // Enable SysTick interrupt
                    SysTick_CTRL_ENABLE_Msk;     // Enable SysTick
}

/*
 * Delay in milliseconds.
 *
 * Parameters:
 *   ms - The number of milliseconds to delay.
 *
 * Uses the timer_ticks variable to create a delay by waiting until the specified duration has elapsed.
 */

void Delay_ms(uint32_t ms) {
    uint32_t start_ticks = timer_ticks; // Record the current tick count.
    while ((timer_ticks - start_ticks) < ms); // Wait until the elapsed ticks match the requested delay.
}

/*
 * Get the current value of timer_ticks.
 *
 * Returns:
 *   The number of ticks that have elapsed since SysTick was enabled.
 *
 * Provides the current value of the global timer_ticks variable for use in timing or delay calculations.
 */
uint32_t Timer_GetTicks(void) {
    return timer_ticks; // Return the current tick count.
}
