#ifndef BATTERY_H
#define BATTERY_H

#include "Types.h"

/*
 * Voltage divider → PA2 (channel 2)
 *
 * 12V battery:  R1=30kΩ, R2=10kΩ  → ratio=4
 * 7.4V battery: R1=10kΩ, R2=10kΩ  → ratio=2
 *
 * عدّل الـ RATIO والـ THRESHOLD حسب بطاريتك
 */
#define BAT_ADC_CH           2
#define BAT_DIVIDER_RATIO    4
#define BAT_VREF_MV          5000U
#define BAT_ADC_RES          1024U
#define BAT_LOW_THRESHOLD_MV 11000U

/* Red LED → PD0 */
#define BAT_LED_PIN  0

void Battery_init(void);
u32  Battery_readVoltage_mV(void);
u8   Battery_isLow(void);
void Battery_updateLED(void);

#endif /* BATTERY_H */