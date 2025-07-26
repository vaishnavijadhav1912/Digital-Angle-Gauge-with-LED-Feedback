/*
 * UART.h
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */


#include "stm32f091xc.h"

#ifndef UART_H_
#define UART_H_


#define HEX_CHARS            "0123456789ABCDEF"                  // Hexadecimal characters
#define HEX_PREFIX           "0x"                                // Hexadecimal prefix
#define HEX_BUFFER_SIZE      5                                   // Buffer size for hexadecimal

#define GPIO_AF_MODE         2U                                   // Alternate Function Mode
#define GPIO_AF_USART2       1U                                   // AF1 for USART2

#define GPIO_PIN_MODE_SHIFT     2U  // Shift for pin mode configuration
#define GPIO_AF_SHIFT           4U  // Shift for alternate function configuration


#define TX 2       // UART TX pin
#define RX 3       // UART RX pin
#define SYS_CLOCK 24000000 // System clock
#define Baud_rate 9600     // UART baud rate

#define HEX_PREFIX_LENGTH 2      // Number of characters in the "0x" prefix
#define HEX_HIGH_NIBBLE_SHIFT 4  // Number of bits to shift for the high nibble
#define HEX_MASK 0x0F            // Mask to isolate a nibble

void USART2_Init(void);
void putstr(const char *s);
void puthex(uint8_t value);




#endif /* UART_H_ */
