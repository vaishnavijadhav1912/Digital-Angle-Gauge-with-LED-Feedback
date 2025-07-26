



PROJECT DESCRIPTION

The aim of this project is to design a user-friendly digital angle gauge that helps accurately set the angle of a saw blade in relation to the table. By connecting an external accelerometer through I2C, the system will measure the blade's tilt and provide immediate feedback using LED indicators. This makes it easy for users to fine-tune the blade to precise angles, like 45°, with confidence.
To ensure accuracy, the gauge will feature a simple calibration process. Users can easily set a 0° reference point either by pressing a button or entering a command. This ensures the angle measurements are reliable and tailored to each specific setup, making tasks like adjusting saw blades not only more accurate but also more intuitive and stress-free.

**NOTE: IF THE GITHUB REPOSITORY DOES NOT WORK PLEASE DOWNLOAD THE PROJECT ZIP FILE FROM GOOGLE DRIVE: it has date and time - video file is there in google drive**

VIDEO LINK:https://drive.google.com/drive/folders/1gup3x-PBJEwLIrNxCCjq_NjcMKizOY0r?usp=sharing
LINK:https://drive.google.com/drive/folders/1BEyj4-c5zV7lXzIflYL2-4EpiHESNHAA?usp=sharing

Features:

Real-Time Angle Measurement: Measures pitch and roll angles in real-time.

Calibration: Enables the current orientation to be set as the 0° reference point.

LED Feedback: Visual indications for angle thresholds using steady or blinking LEDs.

UART Interface: Displays calibrated pitch and roll values via a serial terminal.




## What are Pitch and Roll?

Pitch: Refers to the rotation around the X-axis (forward-backward tilt).
Roll: Refers to the rotation around the Y-axis (side-to-side tilt).

Both angles are calculated using the acceleration data obtained from the MPU6050 sensor.

### Formula Used to Calculate Angles:

These formulas are used to compute the tilt angles from accelerometer data:

1. Pitch Calculation:

    pitch = atan2(accel_y, sqrt(accel_x * accel_x + accel_z * accel_z)) * 180/3.14

2. Roll Calculation :
   roll = atan2(accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * 180/3.14



Hardware Setup:
MPU6050 to STM32F0:

SCL -> I2C Clock Pin (PB8)

SDA -> I2C Data Pin (PB9)

VCC -> 3.3V

GND -> GND

AD0 -> GND

Push Button:
Connect to PC13 

LED:
Connected to PB1


How to Use:

Monitor the Output Using UART:
Open a serial terminal (PuTTY) with the following settings:

Baud Rate: 9600

Data Bits: 8

Parity: None

Stop Bits: 1


Do all the hardware connections


Tilt the Board :
   - Adjust the board to a specific angle (e.g., 45°).
   - The pitch and roll values on the terminal will update in real-time.

Check LED Feedback:
   - Based on the pitch angle, observe the following LED behaviors:
     - **Steady ON**: Pitch is approximately 45°.
     - **Fast Blink**: Pitch is near 45° 
     - **Slow Blink**: Pitch is far from 45°
    
Re-Calibrate (Optional):
   - Press the calibration button again to set a new 0° reference point based on the current orientation.


LED Feedback

Steady ON: Pitch is close to 45°.

Fast Blink: Pitch is in the range 35° - 44° or 44° - 55°

Medium Blink: Pitch is in the range 20° - 35° or 55° - 75°

Slow Blink: Pitch is in the range 5° - 20°

                

OUTPUT VIDEO:
I have added the video of the output. For better quality, please watch it on a mobile phone.
I have also added hardware setup pictures.

   

   

   
