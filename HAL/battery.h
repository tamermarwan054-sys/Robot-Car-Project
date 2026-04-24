/*
 * battery.h — Battery Monitoring HAL
 * Threshold: 9V → ADC = 460
 *   Below 460  → battery LOW  → LED blinks
 *   Above 460  → battery OK   → LED off
 */
#ifndef BATTERY_H
#define BATTERY_H
#include "Types.h"
/* ADC channel — PA3 = channel 3 */
#define BAT_ADC_CHANNEL     3

#define BAT_ADC_THRESHOLD   460u
/* Red LED pin — PD0, physical pin 14 */
#define BAT_LED_PIN         0
void Battery_Init   (void);  /* set PD0 as output, LED off  */
void Battery_Update (void);  /* read PA3, blink if below 9V */
#endif /* BATTERY_H */