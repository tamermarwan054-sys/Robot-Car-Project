#include "GPIO_Interface.h"
#include "GPIO_Private.h"

void GPIO_setPinDirections(port_t port, pin_t pin, direction_t direction) {
    switch (port) {
        case GPIOA:
            switch (direction) {
                case INPUT:        clearBit(DDRA, pin);                    break;
                case INPUT_PULLUP: clearBit(DDRA, pin); setBit(PORTA,pin); break;
                case OUTPUT:       setBit(DDRA, pin);                      break;
            }
            break;  

        case GPIOB:
            switch (direction) {
                case INPUT:        clearBit(DDRB, pin);                    break;
                case INPUT_PULLUP: clearBit(DDRB, pin); setBit(PORTB,pin); break;
                case OUTPUT:       setBit(DDRB, pin);                      break;
            }
            break;  

        case GPIOC:
            switch (direction) {
                case INPUT:        clearBit(DDRC, pin);                    break;
                case INPUT_PULLUP: clearBit(DDRC, pin); setBit(PORTC,pin); break;
                case OUTPUT:       setBit(DDRC, pin);                      break;
            }
            break;  

        case GPIOD:
            switch (direction) {
                case INPUT:        clearBit(DDRD, pin);                    break;
                case INPUT_PULLUP: clearBit(DDRD, pin); setBit(PORTD,pin); break;
                case OUTPUT:       setBit(DDRD, pin);                      break;
            }
            break;
    }
}

void GPIO_setPinValue(port_t port, pin_t pin, value_t value) {
    switch (port) {
        case GPIOA:
            switch (value) {
                case LOW:  clearBit(PORTA, pin); break;
                case HIGH: setBit(PORTA, pin);   break;
            }
            break; 

        case GPIOB:
            switch (value) {
                case LOW:  clearBit(PORTB, pin); break;
                case HIGH: setBit(PORTB, pin);   break;
            }
            break;  

        case GPIOC:
            switch (value) {
                case LOW:  clearBit(PORTC, pin); break;
                case HIGH: setBit(PORTC, pin);   break;
            }
            break;  

        case GPIOD:
            switch (value) {
                case LOW:  clearBit(PORTD, pin); break;
                case HIGH: setBit(PORTD, pin);   break;
            }
            break;
    }
}

void GPIO_togglePinValue(port_t port, pin_t pin) {
    switch (port) {
        case GPIOA: toggleBit(PORTA, pin); break;
        case GPIOB: toggleBit(PORTB, pin); break;
        case GPIOC: toggleBit(PORTC, pin); break;
        case GPIOD: toggleBit(PORTD, pin); break;
    }
}

value_t GPIO_readPinValue(port_t port, pin_t pin) {
    value_t value = LOW;
    switch (port) {
        case GPIOA: value = (value_t)readBit(PINA, pin); break;
        case GPIOB: value = (value_t)readBit(PINB, pin); break;
        case GPIOC: value = (value_t)readBit(PINC, pin); break;
        case GPIOD: value = (value_t)readBit(PIND, pin); break;
    }
    return value;
}