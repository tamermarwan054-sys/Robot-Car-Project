/*
 * AVCC reference, right-adjusted, prescaler 128 for 16 MHz
 */

#include "adc.h"
#include "Bit_manipulation.h"

void ADC_Init(void) {
    setBit(ADMUX, 6);         /* REFS0 - AVCC reference  */
    setBit(ADCSRA, 7);        /* ADEN  - Enable ADC       */
    setBit(ADCSRA, 2);        /* ADPS2 - prescaler 128    */
    setBit(ADCSRA, 1);        /* ADPS1                    */
    setBit(ADCSRA, 0);        /* ADPS0                    */
}

u16 ADC_Read(u8 channel) {
    ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
    setBit(ADCSRA, 6);              /* ADSC - Start conversion */
    while (readBit(ADCSRA, 6));     /* Wait until ADSC clears  */

    u8 low  = ADCL;
    u8 high = ADCH;

    return ((u16)high << 8) | low;
}