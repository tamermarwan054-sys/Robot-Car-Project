// #ifndef BATTERY_H
// #define BATTERY_H

// #include "Types.h"

// /*
//  * Voltage divider → PA2 (channel 2)
//  *
//  * 12V battery:  R1=30kΩ, R2=10kΩ  → ratio=4
//  * 7.4V battery: R1=10kΩ, R2=10kΩ  → ratio=2
//  *
//  * عدّل الـ RATIO والـ THRESHOLD حسب بطاريتك
//  */
// #define BAT_ADC_CH           2
// #define BAT_DIVIDER_RATIO    4
// #define BAT_VREF_MV          5000U
// #define BAT_ADC_RES          1024U
// #define BAT_LOW_THRESHOLD_MV 11000U

// /* Red LED → PD0 */
// #define BAT_LED_PIN  0

// void Battery_init(void);
// u32  Battery_readVoltage_mV(void);
// u8   Battery_isLow(void);
// void Battery_updateLED(void);

// #endif /* BATTERY_H */
/*
 * battery.h — Battery Monitoring HAL
 *
 * Hardware:
 *   Voltage divider on PA2 (ADC channel 2):
 *     12V battery → R1(30kΩ) → PA2(pin 38) → R2(10kΩ) → GND
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

<<<<<<< HEAD
/*
 * Voltage divider → PA2 (channel 2)
 *
 * 12V battery:  R1=30kΩ, R2=10kΩ  → ratio=4
 * 7.4V battery: R1=10kΩ, R2=10kΩ  → ratio=2
 *
 * عدّل الـ RATIO والـ THRESHOLD حسب بطاريتك
 */
#define BAT_ADC_CH           3
#define BAT_DIVIDER_RATIO    3
#define BAT_VREF_MV          5000U
#define BAT_ADC_RES          1024U
#define BAT_LOW_THRESHOLD_MV 9000U
=======
/* ADC channel — PA2 = channel 2 */
#define BAT_ADC_CHANNEL     2
>>>>>>> 189fe2c985cbf7ea6ee7dea03581954109885eb4

/* ADC threshold for 11V low battery
 * = (11V / 4) / 5V * 1024 = 563 */
#define BAT_ADC_THRESHOLD   563u

/* Red LED pin — PD0, physical pin 14 */
#define BAT_LED_PIN         0

void Battery_Init   (void);  /* set PD0 as output, LED off  */
void Battery_Update (void);  /* read PA2, blink if below 11V */

#endif /* BATTERY_H */