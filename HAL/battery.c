// #include "battery.h"
// #include "../MCAL/adc.h"
// #include "../MCAL/gpio_private.h"
// #include "../MCAL/Bit_manipultion.h"

// void Battery_init(void) {
//     setBit(DDRD, BAT_LED_PIN);       /* LED pin = output */
//     clearBit(PORTD, BAT_LED_PIN);    /* LED off initially */
// }

// u32 Battery_readVoltage_mV(void) {
//     u16 adc_val   = ADC_read(BAT_ADC_CH);
//     u32 vadc_mv   = (float)((u32)adc_val * BAT_VREF_MV) / BAT_ADC_RES;
//     return vadc_mv * BAT_DIVIDER_RATIO;
// }

// u8 Battery_isLow(void) {
//     return (Battery_readVoltage_mV() < BAT_LOW_THRESHOLD_MV) ? 1u : 0u;
// }

// void Battery_updateLED(void) {
//     if (Battery_isLow())
//         setBit(PORTD, BAT_LED_PIN);
//     else
//         clearBit(PORTD, BAT_LED_PIN);
// }
/*
 * battery.c — Battery Monitoring HAL
 *
 * Reads voltage divider on PA2 every main loop iteration.
 * Blinks red LED on PD0 when battery drops below 11V.
 */

#include "battery.h"
#include "adc.h"              /* ADC_Read() — flat include, no relative path */
#include "GPIO_private.h"     /* DDRD, PORTD — flat include, correct filename */
#include "Bit_manipulation.h" /* setBit, clearBit — flat include, correct spelling */


/*
 * Battery_Init
 * Configure PD0 as output and turn LED off.
 * Call once in main AFTER ADC_Init().
 */
void Battery_Init(void) {
    setBit(DDRD, BAT_LED_PIN);     /* PD0 = output */
    clearBit(PORTD, BAT_LED_PIN);  /* LED off      */
}


/*
 * Battery_Update
 * Read ADC on PA2, blink LED if battery is below 11V.
 * Call every main loop iteration (every ~100ms).
 *
 * Battery LOW  (ADC < 563) → LED blinks at ~5Hz
 * Battery OK   (ADC >= 563) → LED stays off
 */
void Battery_Update(void) {
    static u8 toggle = 0u;   /* keeps blink state between calls */

    u16 adcValue = ADC_Read(BAT_ADC_CHANNEL);  /* capital R — matches adc.h */

    if (adcValue < BAT_ADC_THRESHOLD) {
        /* Battery LOW — toggle LED every call = blink at 5Hz */
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