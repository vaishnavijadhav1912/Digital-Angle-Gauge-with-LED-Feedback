/*
 * I2C.c
 *
 *  Created on: Dec 12, 2024
 *      Author: Viahsnvi Jadhav
 */

#include "I2C.h"

#ifndef I2C_C_
#define I2C_C_


/*
 * Description : This function initializes the I2C1 peripheral and its associated GPIO pins
 *               for communication. It configures GPIOB pins for alternate function mode,
 *               sets open-drain and high-speed configurations, and enables the I2C1 clock.
 *               Additionally, it resets the I2C1 peripheral and configures timing for
 *               100 kHz communication speed with an 8 MHz PCLK.
 *
 * Parameters  : None
 * Return      : None
 */

void I2C_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock

    GPIOB->MODER &= ~((GPIO_MODE_MASK   << (SCL * 2)) | (GPIO_MODE_MASK   << (SDA * 2))); // Clear mode
    GPIOB->MODER |= (GPIO_MODE_AF   << (SCL * 2)) | (GPIO_MODE_AF   << (SDA * 2));    // Set to AF mode
    GPIOB->OTYPER |= (GPIO_MODE_AF   << SCL) | (GPIO_MODE_AF   << SDA);              // Open-drain
    GPIOB->OSPEEDR |= (GPIO_SPEED_HIGH    << (SCL * GPIO_PIN_SHIFT    )) | (GPIO_SPEED_HIGH    << (SDA * GPIO_PIN_SHIFT    )); // High speed
    GPIOB->AFR[1] |= (1 << ((SCL - GPIO_AF_INDEX_OFFSET ) * GPIO_AF_SHIFT)) | (1 << ((SDA - GPIO_AF_INDEX_OFFSET ) * GPIO_AF_SHIFT)); // AF1 for I2C1

    RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;

    I2C1->TIMINGR = I2C_TIMINGR_100KHZ_8MHZ; // Configure timing for 100kHz with 8MHz PCLK

    I2C1->CR1 |= I2C_CR1_PE; // Enable I2C1
}


/*
 * Description : This function performs a write operation to an I2C slave device. It sends
 *               the specified register address and data byte to the given I2C address.
 *
 * Parameters  : addr - I2C slave device address
 *               reg  - Register address to write to
 *               data - Data byte to write
 * Return      : None
 */

void I2C_Write(uint8_t addr, uint8_t reg, uint8_t data) {
    while (I2C1->ISR & I2C_ISR_BUSY); // Wait for I2C to be free

    I2C1->CR2 = (addr << 1) | (2 << I2C_CR2_NBYTES_Pos); // Set address and number of bytes
    I2C1->CR2 |= I2C_CR2_START; // Generate START condition

    while (!(I2C1->ISR & I2C_ISR_TXIS)); // Wait for TXIS
    I2C1->TXDR = reg; //send address for register

    while (!(I2C1->ISR & I2C_ISR_TXIS)); // wait for transfer complete
    I2C1->TXDR = data; //send data byte

    while (!(I2C1->ISR & I2C_ISR_TC));
    I2C1->CR2 |= I2C_CR2_STOP;  //  STOP condition
    while (!(I2C1->ISR & I2C_ISR_STOPF));
    I2C1->ICR |= I2C_ICR_STOPCF;  // clear stop flag
}


/*
 * Description : This function performs a read operation from an I2C slave device.
 *               It sends the specified register address and reads a specified number
 *               of bytes into the provided buffer.
 *
 * Parameters  : addr   - I2C slave device address
 *               reg    - Register address to read from
 *               buffer - Pointer to the buffer where read data will be stored
 *               size   - Number of bytes to read
 * Return      : None
 */
void I2C_ReadMultiple(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t size) {
    while (I2C1->ISR & I2C_ISR_BUSY); // Wait for I2C to be free

    I2C1->CR2 = (addr << 1) | (1 << I2C_CR2_NBYTES_Pos); // Set address and number of bytes
    I2C1->CR2 |= I2C_CR2_START; //start condition

    while (!(I2C1->ISR & I2C_ISR_TXIS)); // Wait for TXIS
    I2C1->TXDR = reg; // register address

    while (!(I2C1->ISR & I2C_ISR_TC)); // Wait for transfer complete
    I2C1->CR2 = (addr << 1) | I2C_CR2_RD_WRN | (size << I2C_CR2_NBYTES_Pos);  // request read operation
    I2C1->CR2 |= I2C_CR2_START | I2C_CR2_AUTOEND; // Generate START condition and AUTOEND

    for (uint8_t i = 0; i < size; i++) {
        while (!(I2C1->ISR & I2C_ISR_RXNE)); //wait for data
        buffer[i] = I2C1->RXDR; //read data
    }

    while (!(I2C1->ISR & I2C_ISR_STOPF)); //wait for stop flag
    I2C1->ICR |= I2C_ICR_STOPCF; //clear stop flag
}


#endif
