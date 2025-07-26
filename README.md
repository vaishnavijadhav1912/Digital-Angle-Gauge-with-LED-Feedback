# 📐 Digital Angle Gauge with LED Feedback

This project implements a digital angle gauge using an STM32 microcontroller and an MPU6050 accelerometer. It provides real-time tilt measurements and intuitive LED feedback for setting angles like 45°, along with UART monitoring and push-button calibration.

---

## 📟 Features

- 📡 Real-time angle measurement using MPU6050  
- 🔄 Button-based 0° calibration for custom reference  
- 💡 LED feedback for quick angle assessment:
  - **Steady ON**: ~45°
  - **Fast Blink**: near 45°
  - **Slow Blink**: far from 45°
- 🖥️ UART serial output (PuTTY/RealTerm)
- 🧠 Embedded C with I²C, GPIO, UART, and Timer peripherals

---

## 📚 Hardware Setup

| Component    | Connection     |
|--------------|----------------|
| MPU6050      | SCL → PB8      |
|              | SDA → PB9      |
|              | VCC → 3.3V     |
|              | GND → GND      |
|              | AD0 → GND      |
| Push Button  | PC13           |
| LED          | PB1            |

---

## 💻 UART Terminal Settings

- **Baud Rate:** 9600  
- **Data Bits:** 8  
- **Stop Bits:** 1  
- **Parity:** None

---

## ▶️ Usage Instructions

1. **Power on** the system (STM32 + MPU6050).
2. **Open a serial terminal** like PuTTY or RealTerm using the UART settings above.
3. **Tilt the board** to observe live pitch/roll readings and LED feedback.
4. **Press the button** to recalibrate and set current orientation as 0° reference.

---

## 💡 LED Blink Pattern

| Pitch Range             | LED Behavior  |
|-------------------------|---------------|
| ≈ 45°                   | Steady ON     |
| 35°–44° or 46°–55°      | Fast Blink    |
| 20°–34° or 56°–75°      | Medium Blink  |
| 5°–19° or >75°          | Slow Blink    |



