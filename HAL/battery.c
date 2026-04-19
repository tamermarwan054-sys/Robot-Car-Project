#include "battery.h"
#include "../MCAL/adc.h"
#include "../MCAL/gpio_private.h"
#include "../MCAL/Bit_manipultion.h"

void Battery_init(void) {
    setBit(DDRD, BAT_LED_PIN);       /* LED pin = output */
    clearBit(PORTD, BAT_LED_PIN);    /* LED off initially */
}

u32 Battery_readVoltage_mV(void) {
    u16 adc_val   = ADC_read(BAT_ADC_CH);
    u32 vadc_mv   = ((u32)adc_val * BAT_VREF_MV) / BAT_ADC_RES;
    return vadc_mv * BAT_DIVIDER_RATIO;
}

u8 Battery_isLow(void) {
    return (Battery_readVoltage_mV() < BAT_LOW_THRESHOLD_MV) ? 1u : 0u;
}

void Battery_updateLED(void) {
    if (Battery_isLow())
        setBit(PORTD, BAT_LED_PIN);
    else
        clearBit(PORTD, BAT_LED_PIN);
}