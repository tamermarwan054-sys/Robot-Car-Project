# 🤖 Robot Car with Wired Joystick Controller

## Overview
A four-wheel robot car controlled via a dual-axis X-Y joystick, built entirely in bare-metal C on an **ATmega32 microcontroller** running at 16 MHz. Every peripheral driver is written from scratch — no Arduino libraries, no HAL frameworks.

---

## 👥 Authors
| Name |
|------|
| Marwan Tamer |
| Maged Diyaa |
| Ibrahim Salah |
| Belal Barakat |
| Rodaina Hazem |
| Jana Mohamed |
| Mariam Emad |
| Masa Mostafa |

---

## 🔩 Hardware Components
| Component | Details |
|-----------|---------|
| Microcontroller | ATmega32 @ 16 MHz |
| Motor Driver | L298N (or similar) |
| Joystick | Dual Axis X-Y Module |
| Motors | 2x DC Motors |
| Chassis | 4-wheel robotic chassis |
| Battery LED | Red LED on PD0 |
| Battery Sense | Resistor voltage divider → PA3 |

---

## ✨ Features
- Full directional control: Forward, Backward, Left, Right, Stop
- Dead zone handling on joystick center to prevent motor jitter
- Real-time battery voltage monitoring via ADC
- Red LED warning turns **solid ON** when battery drops below ~9V
- Clean layered architecture with interface/private header pattern
- Consistent use of bit manipulation macros — no magic numbers

---

## 🏗️ Software Architecture
Application Layer  →  main.c
HAL Layer          →  motor | joystick | battery
MCAL Layer         →  GPIO  | ADC
Utilities          →  Types.h | Bit_manipulation.h

Every module follows this pattern:
- `module_private.h` — pin/register defines, hidden from outside, included **only in the `.c` file**
- `module_interface.h` — exposes function prototypes only, **no private includes**
- `module.c` — includes both interface and private headers

---

## 📁 File Structure
├── README.md
├── App/
│   └── main.c
├── MCAL/
│   ├── GPIO_private.h
│   ├── GPIO_interface.h
│   ├── GPIO.c
│   ├── adc.h
│   └── adc.c
├── HAL/
│   ├── motor_private.h
│   ├── motor_interface.h
│   ├── motor.c
│   ├── joystick_private.h
│   ├── joystick_interface.h
│   ├── joystick.c
│   ├── battery_private.h
│   ├── battery_interface.h
│   └── battery.c
└── Utilities/
├── Types.h
└── Bit_manipulation.h

---

## 📌 Pin Mapping
| Signal | MCU Pin | ADC Channel |
|--------|---------|-------------|
| Motor IN1 | PD2 | — |
| Motor IN2 | PD3 | — |
| Motor IN3 | PD4 | — |
| Motor IN4 | PD5 | — |
| Motor ENA | PD6 | — |
| Motor ENB | PD7 | — |
| Joystick X | PA0 | CH0 |
| Joystick Y | PA1 | CH1 |
| Battery Sense | PA3 | CH3 |
| Battery LED | PD0 | — |

---

## 🕹️ Joystick Direction Logic
| Y-Axis | X-Axis | Direction |
|--------|--------|-----------|
| > 700 | — | Forward |
| < 300 | — | Backward |
| center | > 700 | Right |
| center | < 300 | Left |
| center | center | Stop |

---

## 🔋 Battery Monitoring
| Setting | Value |
|---------|-------|
| ADC Channel | PA3 (CH3) |
| Threshold | 460 (~9V) |
| Warning | Red LED turns **solid ON** on PD0 |
| OK State | LED off |

---

## ⚙️ ADC Configuration
| Setting | Value |
|---------|-------|
| Reference | AVCC |
| Alignment | Right-adjusted |
| Prescaler | 128 |
| ADC Clock | 125 kHz |
| Trigger | Single conversion |

---

## 🔧 Motor Control Truth Table
| Direction | IN1 | IN2 | IN3 | IN4 |
|-----------|-----|-----|-----|-----|
| Forward   | H   | L   | H   | L   |
| Backward  | L   | H   | L   | H   |
| Left      | L   | H   | H   | L   |
| Right     | H   | L   | L   | H   |
| Stop      | L   | L   | L   | L   |

---

## 🛠️ Bit Manipulation Macros
| Macro | Operation |
|-------|-----------|
| `setBit(reg, bit)` | `reg \|= (1 << bit)` |
| `clearBit(reg, bit)` | `reg &= ~(1 << bit)` |
| `toggleBit(reg, bit)` | `reg ^= (1 << bit)` |
| `readBit(reg, bit)` | `(reg >> bit) & 1` |

---

## 🚀 How to Build and Flash

**1. Clone the repository**
```bash
git clone https://github.com/yourusername/Robot-Car-Project.git
cd Robot-Car-Project
```

**2. Compile with AVR-GCC**
```bash
avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -O2 -Wall \
  -o main.elf App/main.c MCAL/GPIO.c MCAL/adc.c \
  HAL/motor.c HAL/joystick.c HAL/battery.c
```

**3. Convert to hex**
```bash
avr-objcopy -O ihex main.elf main.hex
```

**4. Flash to ATmega32**
```bash
avrdude -c usbasp -p m32 -U flash:w:main.hex
```

---

## 📝 Notes
- `_private.h` files are **never included directly** from outside their own `.c` file
- `GPIO.c` switch-case fall-through bug fixed — all port cases now have proper `break` statements
- Register addresses are manually mapped from the ATmega32 datasheet
- `delay_ms()` is a software busy-wait loop calibrated for 16 MHz
- Joystick pins default to high-impedance input on reset — no extra GPIO init needed
- Battery LED is **solid ON** (not blinking) when voltage is below threshold
