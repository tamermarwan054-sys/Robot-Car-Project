Robot Car with Wired Joystick Controller 🤖
Overview
A four-wheel robot car controlled via a dual-axis X-Y joystick, built entirely in bare-metal C on an ATmega32 microcontroller running at 16 MHz. Every peripheral driver is written from scratch — no Arduino libraries, no HAL frameworks. The project follows a strict layered software architecture with clean separation between application, hardware abstraction, and microcontroller abstraction layers.

Authors

Marwan Tamer
Maged Diyaa
Ibrahim Salah
Belal Barakat
Rodaina
Jana Mohamed
Mariam Emad
Masa Mostafa


Hardware Components
ComponentDetailsMicrocontrollerATmega32 @ 16 MHzMotor DriverL298N (or similar)JoystickDual Axis X-Y ModuleMotors2x DC MotorsChassis4-wheel robotic chassisBattery LEDRed LED on PD0Battery SenseResistor voltage divider → PA3

Features

Full directional control: Forward, Backward, Left, Right, Stop
Dead zone handling on joystick center to prevent motor jitter
Real-time battery voltage monitoring via ADC
Blinking red LED warning when battery drops below ~9V
Clean layered architecture with interface/private header pattern
Consistent use of bit manipulation macros throughout — no magic numbers


Software Architecture
┌─────────────────────────────────────┐
│         Application Layer           │
│              main.c                 │
├─────────────────────────────────────┤
│           HAL Layer                 │
│   motor  │  joystick  │  battery    │
├─────────────────────────────────────┤
│           MCAL Layer                │
│          GPIO  │  ADC               │
├─────────────────────────────────────┤
│           Utilities                 │
│    Types.h  │  Bit_manipulation.h   │
└─────────────────────────────────────┘
Every module follows this strict pattern:
module_private.h     ← register/pin defines, hidden from the outside world
module_interface.h   ← includes private, exposes only function prototypes
module.c             ← includes interface only, no direct private include
This means no .c file and no main.c ever touches a _private.h directly.

File Structure
├── main.c
│
├── MCAL/
│   ├── GPIO_private.h          ← register address defines (hidden)
│   ├── GPIO_interface.h        ← public GPIO header
│   ├── adc.h                   ← ADC register defines + prototypes
│   └── adc.c                   ← ADC init and read implementation
│
├── HAL/
│   ├── motor_private.h         ← pin number defines (PD2-PD7)
│   ├── motor_interface.h       ← public motor header
│   ├── motor.c                 ← motor direction logic
│   ├── joystick_private.h      ← threshold defines (300 / 700)
│   ├── joystick_interface.h    ← public joystick header + enum
│   ├── joystick.c              ← ADC read + direction logic
│   ├── battery_private.h       ← channel, threshold, LED pin defines
│   ├── battery_interface.h     ← public battery header
│   └── battery.c               ← voltage read + LED blink logic
│
└── Utilities/
    ├── Types.h                 ← standard type aliases (u8, u16, etc.)
    └── Bit_manipulation.h      ← setBit, clearBit, toggleBit, readBit

Pin Mapping
SignalMCU PinADC ChannelMotor IN1PD2—Motor IN2PD3—Motor IN3PD4—Motor IN4PD5—Motor ENAPD6—Motor ENBPD7—Joystick XPA0CH0Joystick YPA1CH1Battery sensePA3CH3Battery LEDPD0—

Joystick Direction Logic
Y-AxisX-AxisDirection> 700—Forward< 300—Backwardcenter> 700Rightcenter< 300LeftcentercenterStop
Y-axis has priority over X-axis. The dead zone (300–700) prevents false triggers at joystick center.

Battery Monitoring
A resistor voltage divider feeds the battery voltage into PA3 (ADC channel 3). The ADC threshold is set to 460 which corresponds to approximately 9V. When the reading drops below this value, the red LED on PD0 blinks every 100ms as a low battery warning. When voltage is restored above the threshold the LED turns off immediately.

ADC Configuration
SettingValueVoltage ReferenceAVCCResult AlignmentRight-adjustedPrescaler128ADC Clock125 kHz (for 16 MHz CPU)TriggerSingle conversion

Bit Manipulation Macros
All register operations use macros from Bit_manipulation.h instead of raw bit operations:
csetBit(reg, bit)      // reg |=  (1 << bit)
clearBit(reg, bit)    // reg &= ~(1 << bit)
toggleBit(reg, bit)   // reg ^=  (1 << bit)
readBit(reg, bit)     // (reg >> bit) & 1

How to Build and Flash
1. Clone the repository
bashgit clone https://github.com/yourusername/robot-car.git
cd robot-car
2. Compile with AVR-GCC
bashavr-gcc -mmcu=atmega32 -DF_CPU=16000000UL -O2 -Wall \
  -o main.elf main.c adc.c motor.c joystick.c battery.c
3. Convert to hex
bashavr-objcopy -O ihex main.elf main.hex
4. Flash to ATmega32
bashavrdude -c usbasp -p m32 -U flash:w:main.hex

Include Chain
FileDirectly IncludesGPIO_private.hTypes.hGPIO_interface.hGPIO_private.hadc.hTypes.hadc.cadc.h · Bit_manipulation.hmotor_private.hTypes.hmotor_interface.hmotor_private.hmotor.cmotor_interface.h · GPIO_interface.h · Bit_manipulation.hjoystick_private.hTypes.hjoystick_interface.hjoystick_private.hjoystick.cjoystick_interface.h · adc.hbattery_private.hTypes.hbattery_interface.hbattery_private.hbattery.cbattery_interface.h · adc.h · GPIO_interface.h · Bit_manipulation.hmain.cGPIO_interface.h · adc.h · motor_interface.h · joystick_interface.h · battery_interface.h

Notes

No _private.h file is ever included directly by main.c or any .c file — only through its interface header
Register addresses are mapped manually from the ATmega32 datasheet
delay_ms() is a software busy-wait loop calibrated for 16 MHz — sufficient for this application
The joystick requires no GPIO init since ADC input pins default to high-impedance input on reset
