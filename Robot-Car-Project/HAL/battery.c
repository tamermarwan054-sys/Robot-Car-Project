#include "battery_interface.h"
#include "battery_private.h"   
#include "adc_interface.h"


void Battery_Init(void) {
    pinMode(GPIOD, BAT_LED_PIN, OUTPUT);
    digitalWrite(GPIOD, BAT_LED_PIN, LOW);
}

void Battery_Update(void) {
    u16 adcValue = ADC_Read(BAT_ADC_CHANNEL);

    if (adcValue < BAT_ADC_THRESHOLD) {
        digitalWrite(GPIOD, BAT_LED_PIN, HIGH);
    } else {
        digitalWrite(GPIOD, BAT_LED_PIN, LOW);
    }
}