/*
 * AVCC reference, right-adjusted, prescaler 128 for 16 MHz
 */
#include "adc_private.h"
#include "adc_interface.h"
#include "Bit_manipulation.h"

void ADC_Init(void) {
    setBit(ADMUX, 6);         
    setBit(ADCSRA, 7);        
    setBit(ADCSRA, 2);        
    setBit(ADCSRA, 1);        
    setBit(ADCSRA, 0);        
}

u16 ADC_Read(u8 channel) {
    ADMUX = (ADMUX & 11100000) | (channel & 00000111);
    setBit(ADCSRA, 6);              
    while (readBit(ADCSRA, 6));     

    u8 low  = ADCL;
    u8 high = ADCH;

    return ((u16)high << 8) | low;
}