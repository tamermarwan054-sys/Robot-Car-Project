#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "Types.h"

/* Function Prototypes */
void ADC_Init(void);
u16  ADC_Read(u8 channel);

#endif /* ADC_INTERFACE_H */