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
| Battery Sense | Resistor voltage divider (30kΩ/10kΩ) → PA3 |

---

## ✨ Features
- Full directional control: Forward, Backward, Left, Right, Stop
- Y-axis priority: diagonal joystick inputs resolve to Forward/Backward
- Dead zone handling on joystick center to prevent motor jitter
- Real-time battery voltage monitoring via ADC
- Red LED warning turns ON when battery drops below ~9V (ADC < 460)
- Clean layered architecture with interface/private header pattern
- Consistent use of bit manipulation macros — no magic numbers
- All register addresses manually mapped from ATmega32 datasheet

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
│   ├── adc_private.h
│   ├── adc_interface.h
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
| Battery LED | PD0 | — |
| Joystick X | PA0 | CH0 |
| Joystick Y | PA1 | CH1 |
| Battery Sense | PA3 | CH3 |

---

## 🕹️ Joystick Direction Logic
| Y-Axis | X-Axis | Direction |
|--------|--------|-----------|
| > 700 | — | Forward |
| < 300 | — | Backward |
| center | > 700 | Right |
| center | < 300 | Left |
| center | center | Stop |

> Y-axis is checked first — diagonal inputs always resolve to Forward or Backward. This is a deliberate design decision, not a bug.

---

## 🔋 Battery Monitoring
| Setting | Value |
|---------|-------|
| ADC Channel | PA3 (CH3) |
| Voltage Divider | R3=30kΩ, R4=10kΩ → scales by 0.25 |
| Threshold ADC Value | 460 |
| Threshold Voltage | ~9V (9 × 0.25 = 2.25V → 2.25/5 × 1023 ≈ 460) |
| Warning | Red LED ON on PD0 |
| OK State | LED OFF |

---

## ⚙️ ADC Configuration
| Setting | Value |
|---------|-------|
| Reference | AVCC (5V) |
| Alignment | Right-adjusted |
| Prescaler | 128 (ADPS2:ADPS1:ADPS0 = 1:1:1) |
| ADC Clock | 16MHz / 128 = 125kHz |
| Trigger | Single conversion (polling) |
| Result | ADCL read first (locks ADCH), then combined |

---

## 🔧 Motor Control Truth Table
| Direction | IN1 | IN2 | IN3 | IN4 | ENA | ENB |
|-----------|-----|-----|-----|-----|-----|-----|
| Forward   | H   | L   | H   | L   | H   | H   |
| Backward  | L   | H   | L   | H   | H   | H   |
| Left      | L   | H   | H   | L   | H   | H   |
| Right     | H   | L   | L   | H   | H   | H   |
| Stop      | L   | L   | L   | L   | L   | L   |

> In Motor_stop(), ENA and ENB are disabled FIRST to immediately disconnect motors and avoid active braking.

---

## 🛠️ Bit Manipulation Macros
| Macro | Operation |
|-------|-----------|
| `setBit(reg, bit)` | `reg \|= (1 << bit)` |
| `clearBit(reg, bit)` | `reg &= ~(1 << bit)` |
| `toggleBit(reg, bit)` | `reg ^= (1 << bit)` |
| `readBit(reg, bit)` | `(reg >> bit) & 1` |

---

## 🔌 Hardware Connections
| From | To | Purpose |
|------|----|---------|
| PD2–PD5 | L298N IN1–IN4 | Motor direction control |
| PD6 | L298N ENA | Enable Motor A |
| PD7 | L298N ENB | Enable Motor B |
| PA0 | Joystick VRX | X axis analog input |
| PA1 | Joystick VRY | Y axis analog input |
| PA3 | Voltage divider node | Battery sense |
| PD0 | 330Ω → LED → GND | Battery warning LED |
| XTAL1/XTAL2 | 16MHz Crystal + 22pF caps | Clock source |
| RESET | 10kΩ pullup + button to GND | Reset circuit |

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
  HAL/motor.c HAL/joystick.c HAL/battery.c \
  -IUtilities -IMCAL -IHAL
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
- `_private.h` files are **never included** from outside their own `.c` file
- Register addresses are manually mapped from the ATmega32 datasheet
- ADCL must be read before ADCH — reading ADCL locks ADCH to guarantee both bytes belong to the same conversion
- ADC prescaler 128 chosen to bring ADC clock to 125kHz (valid range: 50–200kHz)
- `delay_ms()` is a software busy-wait loop: 100 outer × 4000 inner NOPs ≈ 100ms at 16MHz
- Battery voltage divider scales 12V max → 3V max at PA3, safely within ADC 5V range
- Joystick pins are analog inputs on PORTA — the only port with ADC multiplexer access on ATmega32
- `digitalRead()` is implemented in GPIO driver for completeness and future extensibility