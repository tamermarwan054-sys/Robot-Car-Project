#ifndef BATTERY_H
#define BATTERY_H
#include "Types.h"
/* ADC channel — PA3 = channel 3 */
#define BAT_ADC_CHANNEL     3

#define BAT_ADC_THRESHOLD   460u
#define BAT_LED_PIN         0
void Battery_Init   (void);  /* LED off  */
void Battery_Update (void);  /* blink if below 9V */
#endif /* BATTERY_H */