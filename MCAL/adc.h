#ifndef ADC_H
#define ADC_H

#include "Types.h"

void ADC_Init(void);
u16 ADC_Read(u8 channel);

#endif /* ADC_H */