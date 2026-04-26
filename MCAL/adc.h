#ifndef ADC_H
#define ADC_H

#include "Types.h"

#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCH    *((volatile u8*)0x25)
#define ADCL    *((volatile u8*)0x24)

void ADC_Init(void);
u16  ADC_Read(u8 channel);

#endif /* ADC_H */