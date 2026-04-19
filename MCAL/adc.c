#include "adc.h"
#include "gpio_private.h"   // we reuse the same style

// ADC Registers (ATmega32)
#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCH    *((volatile u8*)0x25)
#define ADCL    *((volatile u8*)0x24)

void ADC_Init(void) {
    // AVCC reference, right adjusted result
    ADMUX = 0x40;
    
    // Enable ADC + prescaler 128 (for 16 MHz)
    ADCSRA = (1<<7) | (1<<6) | 7;   // ADEN=1, ADSC=1 (first conversion), prescaler=128
}

u16 ADC_Read(u8 channel) {
    // Select channel (0-7)
    ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
    
    // Start conversion
    ADCSRA |= (1<<6);
    
    // Wait until conversion complete
    while (ADCSRA & (1<<6));
    
    // Return 10-bit result
    return (ADCH << 8) | ADCL;
}