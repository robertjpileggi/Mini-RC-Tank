# Mini Tank RC Car Project Overview

Designed and built a custom Bluetooth-controlled RC vehicle using an ESP32 microcontroller as a personal engineering project. The project integrates mechanical design, electrical systems, embedded programming, and motor control to create a modular platform that can be expanded with additional actuators and mechanisms. Development focused on designing reliable hardware, programming responsive controls, troubleshooting electrical systems, and iteratively improving performance through testing.

Key Features & Responsibilities
Designed and assembled the electrical and mechanical systems for a four-wheel drive RC vehicle using DC gear motors and an L298N motor driver.
Programmed an ESP32 in C++ using the Arduino IDE to communicate wirelessly with an Xbox controller through Bluetooth.
Developed custom control software to provide proportional steering, acceleration, braking, and motor control with joystick dead-zone compensation.
Integrated additional motion systems including a servo motor and stepper motor for auxiliary functions controlled independently from vehicle movement.
Designed a modular architecture that allows future expansion with flywheel motors, additional sensors, and custom 3D-printed components.
Selected and integrated electronic components including motor drivers, voltage regulation, power distribution, and battery systems while considering current draw, voltage requirements, and electrical safety.
Debugged hardware and software issues involving motor synchronization, controller connectivity, wiring, power delivery, and embedded code.
Applied engineering principles related to embedded systems, electromechanical design, circuit design, power management, and rapid prototyping throughout development.

# Electronic Components

## Microcontroller
- **ESP32 Development Board**
  - Acts as the central controller for the entire system.
  - Receives Bluetooth input from an Xbox controller.
  - Processes user inputs and controls all motors and actuators.

---

## Drive System
### DC Drive Motors
- **4x DC Gear Motors**
  - Configured as a four-wheel drive platform.
  - Left-side motors are wired together.
  - Right-side motors are wired together.

### Motor Driver
- **1x L298N Motor Driver**
  - Controls the left and right drive motors.
  - Receives direction commands from the ESP32.
  - Powered by a dedicated 6V battery pack.

---

## Turret / Launcher System

### Flywheel Motors
- **2x DC Flywheel Motors**
  - Provide the launching force for Nerf darts.
  - Operate simultaneously when the launcher is activated.

### Motor Driver
- **1x L298N Motor Driver**
  - Controls both flywheel motors.
  - Receives activation commands from the ESP32.
  - Powered by the same 6V battery pack.

### Loading Mechanism
- **1x Servo Motor**
  - Pushes darts into the spinning flywheels.
  - Controlled directly by the ESP32.

### Turret Rotation
- **1x Stepper Motor**
  - Provides 360° horizontal rotation of the launcher.
  - Controlled by the ESP32 for precise positioning.

---

# Power System

### ESP32 Power
- **Portable USB Power Bank (5V)**
  - Powers only the ESP32 through its USB connection.
  - Provides stable regulated 5V power for the controller.

### Motor Power
- **4x AA Battery Pack (6V)**
  - Powers both L298N motor drivers.
  - Supplies power to:
    - Drive motors
    - Flywheel motors
    - Servo
    - Stepper motor

---

# System Overview

```
             Xbox Controller
                    │
            Bluetooth Connection
                    │
                 ESP32
      ┌─────────────┼──────────────┐
      │             │              │
      │             │              │
  L298N #1      L298N #2        Servo
      │             │              │
  4 Drive      2 Flywheel      Loading
   Motors         Motors      Mechanism
                    │
               Stepper Motor
              (360° Turret)
```
