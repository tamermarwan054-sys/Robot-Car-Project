/*
 * AVCC reference, right-adjusted, prescaler 128 for 16 MHz
 */

#include "adc.h"
#include "GPIO_private.h"


#define ADMUX   *((volatile u8*)0x27)   
#define ADCSRA  *((volatile u8*)0x26)   
#define ADCH    *((volatile u8*)0x25)   
#define ADCL    *((volatile u8*)0x24)   


void ADC_Init(void) {
    /* ADMUX: REFS1=0 REFS0=1 → AVCC reference | ADLAR=0 → right adjusted */
    ADMUX = 0x40;
    ADCSRA = (1 << 7) | 7;       
}


u16 ADC_Read(u8 channel) {
    
    ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
    ADCSRA |= (1 << 6);
    while (ADCSRA & (1 << 6));

    /* Read ADCL first */
    u8 low  = ADCL;     
    u8 high = ADCH;     

    return ((u16)high << 8) | low;
}