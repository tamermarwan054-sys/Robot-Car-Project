#include "battery_interface.h"
#include "battery_private.h"   
#include "adc.h"

void Battery_Init(void) {
    GPIO_setPinDirections(GPIOD, BAT_LED_PIN, OUTPUT);
    GPIO_setPinValue(GPIOD, BAT_LED_PIN, LOW);
}

void Battery_Update(void) {
    u16 adcValue = ADC_Read(BAT_ADC_CHANNEL);

    if (adcValue < BAT_ADC_THRESHOLD) {
        GPIO_setPinValue(GPIOD, BAT_LED_PIN, HIGH);
    } else {
        GPIO_setPinValue(GPIOD, BAT_LED_PIN, LOW);
    }
}