/*
 * mpu6050.h
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */

#include <math.h>
#include <stdint.h>


#ifndef MPU6050_H
#define MPU6050_H

#define AVG_SAMPLES 10

extern float pitch_buffer[AVG_SAMPLES];
extern float roll_buffer[AVG_SAMPLES];
extern int avg_index;

extern float pitch_sum;
extern float roll_sum;


#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_1 0x6B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define RAD_TO_DEG 57.2957795131

void calculateAngles(int16_t accel_x, int16_t accel_y, int16_t accel_z, float *pitch, float *roll);

void updateMovingAverage(float new_pitch, float new_roll, float *smoothed_pitch, float *smoothed_roll);

void floatToStr(float value, char *buffer);

int16_t combineBytes(uint8_t msb, uint8_t lsb);

#endif // MPU6050_H



