/*
 * mpu6050.c
 *
 *  Created on: Dec 12, 2024
 *      Author: vaish
 */


#include "mpu6050.h"

#define FRACTIONAL_SCALING_FACTOR 100  // Scaling factor for fractional part
#define ASCII_ZERO                 '0' // ASCII value of '0'
#define MAX_DECIMAL_PLACES           2 // Number of decimal places in output
#define FRACTIONAL_DIVISOR 10 // Divisor to extract fractional digits
#define BYTE_SHIFT 8 // Number of bits to shift a byte to the higher position




float pitch_buffer[AVG_SAMPLES] = {0};
float roll_buffer[AVG_SAMPLES] = {0};
int avg_index = 0;
float pitch_sum = 0;
float roll_sum = 0;


/*
 * Description : Calculates the pitch and roll angles from the accelerometer data.
 *               The angles are derived using trigonometric calculations (atan2).
 *
 * Parameters  : accel_x - The X-axis accelerometer data (16-bit signed integer).
 *               accel_y - The Y-axis accelerometer data (16-bit signed integer).
 *               accel_z - The Z-axis accelerometer data (16-bit signed integer).
 *               pitch - Pointer to store the calculated pitch angle (in degrees).
 *               roll - Pointer to store the calculated roll angle (in degrees).
 *
 * Return      : None
 */

void calculateAngles(int16_t accel_x, int16_t accel_y, int16_t accel_z, float *pitch, float *roll) {
    *pitch = atan2(accel_y, sqrt(accel_x * accel_x + accel_z * accel_z)) * RAD_TO_DEG;  // Calculate pitch angle
    *roll = atan2(accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * RAD_TO_DEG;   // Calculate roll angle
}


/*
 * Description : Updates the moving average of pitch and roll values using a circular buffer.
 *
 * Parameters  : new_pitch - The latest pitch angle to add to the moving average.
 *               new_roll - The latest roll angle to add to the moving average.
 *               smoothed_pitch - Pointer to store the calculated moving average of pitch.
 *               smoothed_roll - Pointer to store the calculated moving average of roll.
 *
 * Return      : None

 */

void updateMovingAverage(float new_pitch, float new_roll, float *smoothed_pitch, float *smoothed_roll) {
    pitch_sum -= pitch_buffer[avg_index]; // Subtract the oldest pitch value from the sum
    roll_sum -= roll_buffer[avg_index];  // Subtract the oldest pitch value from the sum

    pitch_buffer[avg_index] = new_pitch; // Subtract the oldest pitch value from the buffer
    roll_buffer[avg_index] = new_roll;  // Subtract the oldest pitch value from the buffer

    pitch_sum += new_pitch; // Add the new pitch value to the sum
    roll_sum += new_roll; // Add the new roll value to the sum

    avg_index = (avg_index + 1) % AVG_SAMPLES; // Update the index circularly

    *smoothed_pitch = pitch_sum / AVG_SAMPLES; // Calculate the average pitch
    *smoothed_roll = roll_sum / AVG_SAMPLES; // Calculate the average pitch
}


/*
 * Description : Converts a floating-point number into a string representation with 2 decimal places.
 *
 * Parameters  : value - The floating-point number to convert.
 *               buffer - Pointer to a character buffer to store the string representation.
 *
 * Return      : None
 */

void floatToStr(float value, char *buffer) {
    int int_part = (int)value; // Extract the integer part of the float.
    int frac_part = (int)((value - int_part) * FRACTIONAL_SCALING_FACTOR); // Compute the fractional part scaled to two decimal places.

    if (value < 0) { // Check if the value is negative.
        *buffer++ = '-'; // Add a negative sign to the buffer.
        int_part = -int_part; // Convert the integer part to positive.
        frac_part = -frac_part; // Convert the fractional part to positive.
    }

    int idx = 0, temp = int_part; // Initialize index and temporary variable for integer part.
    do {
        buffer[idx++] = (temp % 10) + ASCII_ZERO; // Extract the last digit and convert to ASCII.
        temp /= 10; // Remove the last digit.
    } while (temp); // Repeat until all digits are processed.

    for (int i = 0; i < idx / MAX_DECIMAL_PLACES; i++) { // Reverse the digits in the buffer to get the correct order.
        char tmp = buffer[i];
        buffer[i] = buffer[idx - 1 - i];
        buffer[idx - 1 - i] = tmp;
    }
    buffer += idx; // Move the buffer pointer to the next position.

    *buffer++ = '.'; // Add the decimal point.

    buffer[0] = (frac_part / FRACTIONAL_DIVISOR) + ASCII_ZERO; // Extract the first fractional digit and convert to ASCII.
    buffer[1] = (frac_part % FRACTIONAL_DIVISOR) + ASCII_ZERO; // Extract the second fractional digit and convert to ASCII.
    buffer[2] = '\0'; // Null-terminate the string.
}


/*
 * Description : Combines two 8-bit bytes (MSB and LSB) into a 16-bit signed integer.
 *
 * Parameters  : msb - The most significant byte.
 *               lsb - The least significant byte.
 *
 * Return      : int16_t - The combined 16-bit signed integer.
 */
int16_t combineBytes(uint8_t msb, uint8_t lsb) {
    return (int16_t)((msb << BYTE_SHIFT) | lsb); // Shift the msb to the upper 8 bits, combine it with lsb using bitwise OR, and cast to 16-bit signed integer.
}

