#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include "Types.h"

/* Hardware Register Addresses for ATmega32 ADC */
#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCH    *((volatile u8*)0x25)
#define ADCL    *((volatile u8*)0x24)

#endif /* ADC_PRIVATE_H */