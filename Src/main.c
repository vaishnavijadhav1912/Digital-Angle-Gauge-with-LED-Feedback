#include <stdint.h>
#include <stdio.h>
#include "stm32f091xc.h"
#include "stm32f0xx.h"
#include <math.h>

#include "gpio_init.h"
#include "uart.h"
#include "i2c.h"
#include "mpu6050.h"
#include "led.h"
#include "timer.h"


#define SINGLE_BYTE              1      // Single-byte I2C reads

#define LOOP_DELAY_MS            50     // Main loop delay in milliseconds

// MPU6050 I2C address
#define MPU6050_ADDR 0x68
 // Using PB1 for LED

#define MPU6050_WAKEUP_COMMAND          0x00   // Command to wake up MPU6050
#define MPU6050_ACCEL_SENSITIVITY       0x10   // Accelerometer sensitivity setting

// MPU6050 Registers
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_1 0x6B
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG  0x1B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43
#define RAD_TO_DEG 57.2957795131
#define ACCEL_DATA_SIZE 6
#define STRING_BUFFER_SIZE 16
#define expected_id  0x68


#define ANGLE_THRESHOLD        1.0   // Threshold for steady ON (in degrees)
#define ANGLE_FAST_BLINK_LOW   35.0  // Lower limit for fast blink
#define ANGLE_FAST_BLINK_HIGH  55.0  // Upper limit for fast blink
#define ANGLE_MEDIUM_BLINK_LOW 20.0  // Lower limit for medium blink
#define ANGLE_MEDIUM_BLINK_HIGH 75.0 // Upper limit for medium blink
#define ANGLE_SLOW_BLINK_LOW   5.0   // Lower limit for slow blink
#define LED_ON_ANGLE 45.0  // Angle at which the LED remains steady ON
#define LED_FAST_BLINK_UPPER_LIMIT 46.0  // Upper limit for fast blink angle

#define BUTTON_DEBOUNCE_MS     500

#define ACCEL_X_HIGH_INDEX  0  // Index for high byte of X-axis acceleration
#define ACCEL_X_LOW_INDEX   1  // Index for low byte of X-axis acceleration
#define ACCEL_Y_HIGH_INDEX  2  // Index for high byte of Y-axis acceleration
#define ACCEL_Y_LOW_INDEX   3  // Index for low byte of Y-axis acceleration
#define ACCEL_Z_HIGH_INDEX  4  // Index for high byte of Z-axis acceleration
#define ACCEL_Z_LOW_INDEX   5  // Index for low byte of Z-axis acceleration

#define DISPLAY_INTERVAL        10    // Number of readings before display
#define AVERAGE_SAMPLE_COUNT    10    // Number of samples for averaging
#define DEGREE_SCALING_FACTOR  10.0f  // Factor for averaging pitch and roll
#define RESET_BUTTON_PIN 13 // PC13 is the reset button




// Add reference variables
float ref_pitch = 0.0;
float ref_roll = 0.0;
// Global variables
float smoothed_pitch = 0.0, smoothed_roll = 0.0;







int main(void) {
    // Initialize system and peripherals
    SystemInit();
    GPIO_Init(); // Initialize GPIO for LED
    USART2_Init(); // Initialize UART
    I2C_Init(); // Initialize I2C
    PushButton_PC13_Init_new(); // Initialize pushbutton GPIO
    SysTick_Config(48000); // Configure SysTick for 3 ms ticks

    // Display initialization messages
    putstr("\r\n==============================\r\n");
    putstr("   MPU6050 Sensor Interface\r\n");
    putstr("==============================\r\n");
    putstr("Checking MPU6050 connection...\r\n");

    uint8_t who_am_i = 0;

    // Verify MPU6050 communication
    I2C_ReadMultiple(MPU6050_ADDR, MPU6050_WHO_AM_I, &who_am_i, SINGLE_BYTE);

    if (who_am_i == expected_id) {
        putstr("MPU6050 connected successfully. WHO_AM_I = ");
        puthex(who_am_i);
        putstr("\r\n");
    } else {
        putstr("MPU6050 connection failed. WHO_AM_I = ");
        puthex(who_am_i);
        putstr("\r\n");
        while (1); // Halt execution if MPU6050 is not connected
    }

    // Configure MPU6050
    I2C_Write(MPU6050_ADDR, MPU6050_PWR_MGMT_1, MPU6050_WAKEUP_COMMAND); // Wake up MPU6050
    I2C_Write(MPU6050_ADDR, ACCEL_CONFIG, MPU6050_ACCEL_SENSITIVITY); // Set accelerometer sensitivity

    uint8_t accel_data[ACCEL_DATA_SIZE];
    float pitch = 0.0, roll = 0.0;
    float smoothed_pitch = 0.0, smoothed_roll = 0.0;
    char pitch_str[STRING_BUFFER_SIZE], roll_str[STRING_BUFFER_SIZE];
    LED_State led_state = LED_OFF;

    int reading_count = 0;

    while (1) {
        // Check if button is pressed and reset pitch and roll
    	if (isButtonPressed_new()) {
    	    ref_pitch = smoothed_pitch; // Store current smoothed pitch
    	    ref_roll = smoothed_roll;  // Store current smoothed roll
    	    putstr("\r\n Calibration: Pitch and Roll set to 0.\r\n");
    	    Delay_ms(BUTTON_DEBOUNCE_MS);  // Debounce delay
    	}


        // Read accelerometer data
        I2C_ReadMultiple(MPU6050_ADDR, ACCEL_XOUT_H, accel_data, ACCEL_DATA_SIZE);

        int16_t accel_x = combineBytes(accel_data[ACCEL_X_HIGH_INDEX], accel_data[ACCEL_X_LOW_INDEX]);
        int16_t accel_y = combineBytes(accel_data[ACCEL_Y_HIGH_INDEX], accel_data[ACCEL_Y_LOW_INDEX]);
        int16_t accel_z = combineBytes(accel_data[ACCEL_Z_HIGH_INDEX], accel_data[ACCEL_Z_LOW_INDEX]);

        // Calculate pitch and roll
        calculateAngles(accel_x, accel_y, accel_z, &pitch, &roll);

        // Update moving average
        updateMovingAverage(pitch, roll, &smoothed_pitch, &smoothed_roll);

        // Increment the reading counter
        reading_count++;

        // Display readings at regular intervals
        if (reading_count >= DISPLAY_INTERVAL) {
            float display_pitch = 0.0, display_roll = 0.0;

            // Calculate averages for display
            for (int i = 0; i < AVERAGE_SAMPLE_COUNT; i++) {
                int index = (avg_index - i - 1 + AVG_SAMPLES) % AVG_SAMPLES;
                display_pitch += pitch_buffer[index];
                display_roll += roll_buffer[index];
            }
            display_pitch /= DEGREE_SCALING_FACTOR;
            display_roll /= DEGREE_SCALING_FACTOR;

            // Convert to strings and display
            floatToStr(display_pitch, pitch_str);
            floatToStr(display_roll, roll_str);

            putstr("\r\n------------------------------\r\n");
            putstr("|    Pitch   |     Roll      |\r\n");
            putstr("------------------------------\r\n");
            putstr("|    ");
            putstr(pitch_str);
            putstr("°    |     ");
            putstr(roll_str);
            putstr("°   |\r\n");
            putstr("------------------------------\r\n");

            // Reset reading counter
            reading_count = 0;
        }

        // Determine LED state based on pitch
        if (fabs(smoothed_pitch - LED_ON_ANGLE) <= ANGLE_THRESHOLD) {
            led_state = LED_ON;
        } else if ((smoothed_pitch >= ANGLE_FAST_BLINK_LOW && smoothed_pitch < LED_ON_ANGLE) ||
                   (smoothed_pitch > LED_FAST_BLINK_UPPER_LIMIT && smoothed_pitch <= ANGLE_FAST_BLINK_HIGH)) {
            led_state = BLINK_FAST;
        } else if ((smoothed_pitch >= ANGLE_MEDIUM_BLINK_LOW && smoothed_pitch < ANGLE_FAST_BLINK_LOW) ||
                   (smoothed_pitch > ANGLE_FAST_BLINK_HIGH && smoothed_pitch <= ANGLE_MEDIUM_BLINK_HIGH)) {
            led_state = BLINK_MEDIUM;
        } else if ((smoothed_pitch >= ANGLE_SLOW_BLINK_LOW && smoothed_pitch < ANGLE_MEDIUM_BLINK_LOW) ||
                   (smoothed_pitch > ANGLE_MEDIUM_BLINK_HIGH)) {
            led_state = BLINK_SLOW;
        } else {
            led_state = LED_OFF;
        }

        // Update LED state
        LED_Control(led_state);

        // Add delay for loop timing
        Delay_ms(LOOP_DELAY_MS);
    }
}
