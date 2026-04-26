#include "motor_interface.h"
#include "GPIO_interface.h"
#include "Bit_manipulation.h"

void Motor_init(void) {
    setBit(DDRD, IN1_PIN);
    setBit(DDRD, IN2_PIN);
    setBit(DDRD, IN3_PIN);
    setBit(DDRD, IN4_PIN);
    setBit(DDRD, ENA_PIN);
    setBit(DDRD, ENB_PIN);

    setBit(PORTD, ENA_PIN);
    setBit(PORTD, ENB_PIN);

    Motor_stop();
}

void Motor_forward(void) {
    setBit(PORTD, ENA_PIN);    setBit(PORTD, ENB_PIN);
    setBit(PORTD, IN1_PIN);    clearBit(PORTD, IN2_PIN);
    setBit(PORTD, IN3_PIN);    clearBit(PORTD, IN4_PIN);
}

void Motor_backward(void) {
    setBit(PORTD, ENA_PIN);    setBit(PORTD, ENB_PIN);
    clearBit(PORTD, IN1_PIN);  setBit(PORTD, IN2_PIN);
    clearBit(PORTD, IN3_PIN);  setBit(PORTD, IN4_PIN);
}

void Motor_left(void) {
    setBit(PORTD, ENA_PIN);    setBit(PORTD, ENB_PIN);
    clearBit(PORTD, IN1_PIN);  setBit(PORTD, IN2_PIN);
    setBit(PORTD, IN3_PIN);    clearBit(PORTD, IN4_PIN);
}

void Motor_right(void) {
    setBit(PORTD, ENA_PIN);    setBit(PORTD, ENB_PIN);
    setBit(PORTD, IN1_PIN);    clearBit(PORTD, IN2_PIN);
    clearBit(PORTD, IN3_PIN);  setBit(PORTD, IN4_PIN);
}

void Motor_stop(void) {
    clearBit(PORTD, ENA_PIN);  clearBit(PORTD, ENB_PIN);
    clearBit(PORTD, IN1_PIN);  clearBit(PORTD, IN2_PIN);
    clearBit(PORTD, IN3_PIN);  clearBit(PORTD, IN4_PIN);
}