/*
 * battery.h — Battery Monitoring HAL
 *
 * Hardware:
 *   Voltage divider on PA3 (ADC channel 3):
 *     12V battery → R1(30kΩ) → PA3(pin 39) → R2(10kΩ) → GND
 *     Vout = Vbat / 4  →  max 3.0V at 12V, safely within ADC range
 *
 *   Red LED on PD0 (pin 14):
 *     PD0 → 330Ω → LED(+) → LED(-) → GND
 *
 * Threshold: 11V → ADC = 563
 *   Below 563  → battery LOW  → LED blinks
 *   Above 563  → battery OK   → LED off
 */
#ifndef BATTERY_H
#define BATTERY_H
#include "Types.h"
/* ADC channel — PA3 = channel 3 */
#define BAT_ADC_CHANNEL     3
/* ADC threshold for 11V low battery
 * = (11V / 4) / 5V * 1024 = 563 */
#define BAT_ADC_THRESHOLD   460u
/* Red LED pin — PD0, physical pin 14 */
#define BAT_LED_PIN         0
void Battery_Init   (void);  /* set PD0 as output, LED off  */
void Battery_Update (void);  /* read PA3, blink if below 11V */
#endif /* BATTERY_H */