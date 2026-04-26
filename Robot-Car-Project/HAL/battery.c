#include "battery_interface.h"
#include "adc.h"
#include "GPIO_interface.h"
#include "Bit_manipulation.h"

void Battery_Init(void) {
    setBit(DDRD, BAT_LED_PIN);
    clearBit(PORTD, BAT_LED_PIN);
}

void Battery_Update(void) {
    static u8 toggle = 0u;

    u16 adcValue = ADC_Read(BAT_ADC_CHANNEL);

    if (adcValue < BAT_ADC_THRESHOLD) {
        toggle ^= 1u;
        if (toggle)
            setBit(PORTD, BAT_LED_PIN);
        else
            clearBit(PORTD, BAT_LED_PIN);
    } else {
        clearBit(PORTD, BAT_LED_PIN);
        toggle = 0u;
    }
}