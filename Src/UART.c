/*
 * UART.c
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */

#include "uart.h"


/*
 * Initialize USART2 peripheral.
 *
 * Configures GPIO pins PA2 (TX) and PA3 (RX) for USART2 in alternate function mode.
 * Sets the baud rate and enables transmission (TE), reception (RE), and the USART peripheral (UE).
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */

void USART2_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;    // Enable GPIOA clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock

    GPIOA->MODER |= (GPIO_AF_MODE  << (TX * GPIO_PIN_MODE_SHIFT )) | (GPIO_AF_MODE  << (RX * GPIO_PIN_MODE_SHIFT )); // Alternate function
    GPIOA->AFR[0] |= (GPIO_AF_USART2  << (TX * GPIO_AF_SHIFT )) | (GPIO_AF_USART2  << (RX * GPIO_AF_SHIFT )); // AF1 for USART2

    USART2->BRR = SYS_CLOCK / Baud_rate;
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}


/*
 * Transmit a null-terminated string over USART2.
 *
 * Waits for the transmit data register to be empty before sending each character.
 *
 * Parameters:
 *   s - Pointer to the string to transmit.
 *
 * Returns:
 *   None
 */
void putstr(const char *s) {
    while (*s) {
        while (!(USART2->ISR & USART_ISR_TXE));
        USART2->TDR = *s++;
    }
}


/*
 * Transmit a hexadecimal representation of an 8-bit value over USART2.
 *
 * Converts a byte into its hexadecimal equivalent and sends it as a string prefixed by "0x".
 *
 * Parameters:
 *   value - The 8-bit value to transmit.
 *
 * Returns:
 *   None
 */
void puthex(uint8_t value) {
    char hex_chars[] = HEX_CHARS;
    char buffer[HEX_BUFFER_SIZE   ] = "0x00";
    buffer[HEX_PREFIX_LENGTH] = hex_chars[(value >> HEX_HIGH_NIBBLE_SHIFT) & 0x0F];
    buffer[HEX_PREFIX_LENGTH + 1] = hex_chars[value &  HEX_MASK ];
    putstr(buffer);
}

