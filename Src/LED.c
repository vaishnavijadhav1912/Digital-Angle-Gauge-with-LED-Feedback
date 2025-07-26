/*
 * LED.c
 *
 *  Created on: Dec 12, 2024
 *      Author: Vaishnavi Jadhav
 */


#include "LED.h"
#include "timer.h"

#define LED_PIN 1



/*
 * Description : This function controls the LED state based on the provided `LED_State`.
 *               It handles turning the LED ON or OFF and blinking the LED at different
 *               intervals (fast, medium, or slow). The function uses the system timer
 *               (`timer_ticks`) to manage blinking intervals.
 *
 * Parameters  : state - The desired state of the LED, specified as an `LED_State` enum.
 *                        - LED_OFF: Turn the LED off
 *                        - LED_ON: Turn the LED on
 *                        - BLINK_FAST: Blink the LED at a fast interval
 *                        - BLINK_MEDIUM: Blink the LED at a medium interval
 *                        - BLINK_SLOW: Blink the LED at a slow interval
 *
 * Return      : None

 */

void LED_Control(LED_State state) {
    static uint32_t last_blink_time = 0;

    switch (state) {
    case LED_OFF:
        GPIOB->ODR &= ~(BIT_SHIFT_BASE << LED_PIN); // Turn LED OFF
        break;
    case LED_ON:
        GPIOB->ODR |= (BIT_SHIFT_BASE << LED_PIN); // Turn LED ON
        break;
    case BLINK_FAST:
        if ((timer_ticks - last_blink_time) >= BLINK_FAST_INTERVAL) { // Blink every 25 ms (very fast)
            GPIOB->ODR ^= (BIT_SHIFT_BASE << LED_PIN);
            last_blink_time = timer_ticks;
        }
        break;
    case BLINK_MEDIUM:
        if ((timer_ticks - last_blink_time) >= BLINK_MEDIUM_INTERVAL) { // Blink every 150 ms (moderate)
            GPIOB->ODR ^= (BIT_SHIFT_BASE << LED_PIN);
            last_blink_time = timer_ticks;
        }
        break;
    case BLINK_SLOW:
        if ((timer_ticks - last_blink_time) >= BLINK_SLOW_INTERVAL) { // Blink every 500 ms (slow)
            GPIOB->ODR ^= (BIT_SHIFT_BASE << LED_PIN);
            last_blink_time = timer_ticks;
        }
        break;
    }
}
