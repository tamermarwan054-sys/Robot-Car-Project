#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "Bit_manipulation.h"


typedef enum {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD
} port_t;

typedef enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
} pin_t;

typedef enum {
    INPUT,
    INPUT_PULLUP,
    OUTPUT
} direction_t;

typedef enum {
    LOW,
    HIGH
} value_t;

void    GPIO_setPinDirections  (port_t port, pin_t pin, direction_t direction);
void    GPIO_setPinValue       (port_t port, pin_t pin, value_t value);
void    GPIO_togglePinValue    (port_t port, pin_t pin);
value_t GPIO_readPinValue      (port_t port, pin_t pin);


#endif /* GPIO_INTERFACE_H */