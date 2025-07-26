/*
 * I2C.h
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */

#include "stm32f091xc.h"

#ifndef I2C_H_
#define I2C_H_

#define LED_PIN 1
#define MPU6050_ADDR 0x68 // MPU6050 I2C address
#define SCL 8
#define SDA 9
#define I2C_TIMINGR_100KHZ_8MHZ  (0x10805E89U)

#define GPIO_MODE_MASK          3U   // Mask for clearing mode bits (00, 01, 10, 11)
#define GPIO_MODE_AF            2U   // Alternate function mode
#define GPIO_OUTPUT_OPEN_DRAIN  1U   // Open-drain output configuration
#define GPIO_SPEED_HIGH         3U   // High-speed GPIO configuration
#define GPIO_AF_SHIFT           4U   // Shift for alternate function selection
#define GPIO_PIN_SHIFT          2U   // Shift for GPIO pin mode configuration
#define GPIO_AF_INDEX_OFFSET    8U   // Offset for alternate function index (AFR[1] handling for SCL, SDA)



void I2C_Init(void);
void I2C_Write(uint8_t addr, uint8_t reg, uint8_t data);
void I2C_ReadMultiple(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t size);

#endif // I2C_H



