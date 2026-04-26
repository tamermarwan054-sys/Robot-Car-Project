# Robot Car with Wired Joystick Controller 🤖

## Overview
A four-wheel robot car controlled via a dual-axis X-Y joystick, built entirely in bare-metal C on an **ATmega32 microcontroller** running at 16 MHz. Every peripheral driver is written from scratch — no Arduino libraries, no HAL frameworks.

---

## Authors
| Name |
|------|
| Marwan Tamer |
| Maged Diyaa |
| Ibrahim Salah |
| Belal Barakat |
| Rodaina |
| Jana Mohamed |
| Mariam Emad |
| Masa Mostafa |

---

## Hardware Components
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

## Features
- Full directional control: Forward, Backward, Left, Right, Stop
- Dead zone handling on joystick center to prevent motor jitter
- Real-time battery voltage monitoring via ADC
- Blinking red LED warning when battery drops below ~9V
- Clean layered architecture with interface/private header pattern
- Consistent use of bit manipulation macros — no magic numbers

---

## Software Architecture
Application Layer  →  main.c
HAL Layer          →  motor | joystick | battery
MCAL Layer         →  GPIO  | ADC
Utilities          →  Types.h | Bit_manipulation.h

Every module follows this pattern:
- `module_private.h` — pin/register defines, hidden from outside
- `module_interface.h` — includes private, exposes function prototypes only
- `module.c` — includes interface only

---

## File Structure
├── README.md
├── App/
│   └── main.c
├── MCAL/
│   ├── GPIO_private.h
│   ├── GPIO_interface.h
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

## Pin Mapping
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

## Joystick Direction Logic
| Y-Axis | X-Axis | Direction |
|--------|--------|-----------|
| > 700 | — | Forward |
| < 300 | — | Backward |
| center | > 700 | Right |
| center | < 300 | Left |
| center | center | Stop |

---

## Battery Monitoring
| Setting | Value |
|---------|-------|
| ADC Channel | PA3 (CH3) |
| Threshold | 460 (~9V) |
| Warning | Red LED blinks on PD0 |
| OK State | LED off |

---

## ADC Configuration
| Setting | Value |
|---------|-------|
| Reference | AVCC |
| Alignment | Right-adjusted |
| Prescaler | 128 |
| ADC Clock | 125 kHz |
| Trigger | Single conversion |

---

## Bit Manipulation Macros
| Macro | Operation |
|-------|-----------|
| `setBit(reg, bit)` | `reg \|= (1 << bit)` |
| `clearBit(reg, bit)` | `reg &= ~(1 << bit)` |
| `toggleBit(reg, bit)` | `reg ^= (1 << bit)` |
| `readBit(reg, bit)` | `(reg >> bit) & 1` |

---

## How to Build and Flash

**1. Clone the repository**
```bash
git clone https://github.com/yourusername/Robot-Car-Project.git
cd Robot-Car-Project
```

**2. Compile with AVR-GCC**
```bash
avr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -O2 -Wall \
  -o main.elf App/main.c MCAL/adc.c HAL/motor.c HAL/joystick.c HAL/battery.c
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

## Notes
- No `_private.h` is ever included directly — only through its interface header
- Register addresses are manually mapped from the ATmega32 datasheet
- `delay_ms()` is a software busy-wait loop calibrated for 16 MHz
- Joystick pins default to high-impedance input on reset — no GPIO init needed
