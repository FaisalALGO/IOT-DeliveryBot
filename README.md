# SmartCar Semi-Autonomous Delivery Robot

This project showcases a semi-autonomous delivery robot built using the **ELEGOO Smart Car Kit V4**.  
It combines real-time control, wireless communication, and sensor-based decision-making to simulate a small-scale delivery robot suitable for factory or restaurant applications.

The robot receives commands via **Wi-Fi** (through an ESP module) from a mobile app, and then executes tasks such as **line following**, **obstacle detection**, and **loading/unloading** using custom firmware written in **C** for the **ATmega328P** microcontroller.

---

## 📦 Components Used
- **ELEGOO Smart Car Kit V4**
  - Motors and Motor Driver
  - Ultrasonic Sensor (Obstacle detection)
  - Infrared (IR) Sensors (Line following)
  - ESP8266 Wi-Fi Module (Receiving user commands via Wi-Fi)
- **Additional Servo Motor** (for loading/unloading mechanism)

---

## ⚙️ Peripherals and Communication Protocols

**Peripherals:**
- **Timer0** → PWM generation to control motor speed
- **Timer1** → Timer interrupt (every 50 microseconds) for ultrasonic distance measurement
- **Timer2** → PWM generation for servo control (~61 Hz)
- **ADC** → Analog readings from the IR line-following sensors

**Communication:**
- **UART** (with interrupt) → Handles real-time communication between the ESP module and ATmega328P

---

## 📂 File Structure

| File | Description |
|------|-------------|
| `main.c` | Contains the main state machine logic: IDLE, moving to stations, loading, unloading |
| `motor.c/h` | Sets up Timer0 PWM to control motor speed and direction |
| `LineFollowing.c/h` | Sets up ADC for IR sensors and basic line-following algorithm |
| `ultrasonic.c/h` | Configures Timer1 and calculates distance with the ultrasonic sensor |
| `Servo.c/h` | Configures Timer2 to control servo position (loading/unloading) |
| `EspData.c/h` | Initializes UART communication and processes received Wi-Fi data |

---

## 🛠 How the System Works
1. The user connects their smartphone to the robot over Wi-Fi using the **ELEGOO Kit App**.
2. When a button is pressed, the app sends data to the **ESP8266** module.
3. The ESP forwards this data via **UART** to the **ATmega328P**.
4. Based on the received command, the robot:
   - Drives to the next station.
   - Follows a white line on the ground.
   - Stops at black markers (stations).
   - Loads or unloads objects using the servo motor.
   - Continuously monitors obstacles using the ultrasonic sensor.

The robot is **capable of multitasking**:  
It can move, follow lines, detect obstacles, and operate the servo simultaneously — achieving a real-time, responsive system.

---

## 📈 Project Highlights
- **Semi-autonomous behavior** with user command flexibility
- **Real-time obstacle detection** and stopping
- **Wireless remote control** 
- **Multitasking system** with integrated sensors and actuators

---

## 📷 Video
Watch the demonstration here: [YouTube Demo](https://youtu.be/v_hY2M6B0GM)  

