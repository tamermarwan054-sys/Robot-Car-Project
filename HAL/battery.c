#include "battery.h"
#include "adc.h"              
#include "GPIO_private.h"     
#include "Bit_manipulation.h" 


void Battery_Init(void) {
    setBit(DDRD, BAT_LED_PIN);     /* PD0 = output */
    clearBit(PORTD, BAT_LED_PIN);  /* LED off */
}

/*
 * blink LED if battery is below 9V.
 * Battery LOW  (ADC < 460) → LED blinks 
 * Battery OK   (ADC >= 460) → LED stays off
 */
void Battery_Update(void) {
    static u8 toggle = 0u;   /* keeps blink state */

    u16 adcValue = ADC_Read(BAT_ADC_CHANNEL);  /* PA3 = channel 3 */

    if (adcValue < BAT_ADC_THRESHOLD) {
        /* Battery toggle LED */
        toggle ^= 1u;
        if (toggle)
            setBit(PORTD, BAT_LED_PIN);
        else
            clearBit(PORTD, BAT_LED_PIN);
    } else {
        /* Battery OK — LED stays off */
        clearBit(PORTD, BAT_LED_PIN);
        toggle = 0u;
    }
}