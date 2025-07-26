/*
 * gpio_init.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Vaishnavi Jadhav
 */


#include "gpio_init.h"


/*
 * Description : This function initializes the GPIOB port and configures the
 *               specified pin as an output for controlling an LED. It enables
 *               the GPIOB clock, clears the mode register for the pin, and
 *               sets it to output mode.
 *
 * Parameter   : None
 * Return      : None
 */
void GPIO_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable GPIOB clock
    GPIOB->MODER &= ~(GPIO_MODE_MASK << (LED_PIN * GPIO_PIN_SHIFT));
    GPIOB->MODER |= (GPIO_MODE_OUTPUT   << (LED_PIN * GPIO_PIN_SHIFT)); // Set PB1 to output
}

/*
 * Description : This function initializes the GPIOC port and configures the
 *               specified pin (PC13) as an input with a pull-up resistor. It
 *               enables the GPIOC clock, clears the mode and pull-up/pull-down
 *               bits for the pin, and sets the pull-up resistor to ensure a
 *               default high state when the button is not pressed.
 *
 * Parameters  : None
 * Return      : None
 */


void PushButton_PC13_Init_new(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Enable GPIOC clock
    GPIOC->MODER &= ~(GPIO_MODE_MASK << (BUTTON_PIN * 2)); // Configure PC13 as input
    GPIOC->PUPDR &= ~(GPIO_MODE_MASK << (BUTTON_PIN * 2)); // Clear pull-up/down bits
    GPIOC->PUPDR |= (GPIO_MODE_OUTPUT   << (BUTTON_PIN * 2));  // Enable pull-up resistor
}


/*
 * Description : This function checks the state of the button connected to the
 *               specified pin (PC13) and returns whether it is pressed. The
 *               button is configured as active-low, so the function returns
 *               true (1) when the button is pressed and false (0) otherwise.
 *
 * Parameters  : None
 * Return      : int - Returns 1 if the button is pressed, 0 otherwise.
 */

int isButtonPressed_new(void) {
    return !(GPIOC->IDR & (1U << BUTTON_PIN));
}
