#include "motor_interface.h"
#include "motor_private.h"   

void Motor_init(void) {
    GPIO_setPinDirections(GPIOD, IN1_PIN, OUTPUT);
    GPIO_setPinDirections(GPIOD, IN2_PIN, OUTPUT);
    GPIO_setPinDirections(GPIOD, IN3_PIN, OUTPUT);
    GPIO_setPinDirections(GPIOD, IN4_PIN, OUTPUT);
    GPIO_setPinDirections(GPIOD, ENA_PIN, OUTPUT);
    GPIO_setPinDirections(GPIOD, ENB_PIN, OUTPUT);

    GPIO_setPinValue(GPIOD, ENA_PIN, HIGH);
    GPIO_setPinValue(GPIOD, ENB_PIN, HIGH);

    Motor_stop();
}

void Motor_forward(void) {
    GPIO_setPinValue(GPIOD, ENA_PIN, HIGH);
    GPIO_setPinValue(GPIOD, ENB_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN1_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN2_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN3_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN4_PIN, LOW);
}

void Motor_backward(void) {
    GPIO_setPinValue(GPIOD, ENA_PIN, HIGH);
    GPIO_setPinValue(GPIOD, ENB_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN1_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN2_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN3_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN4_PIN, HIGH);
}

void Motor_left(void) {
    GPIO_setPinValue(GPIOD, ENA_PIN, HIGH);
    GPIO_setPinValue(GPIOD, ENB_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN1_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN2_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN3_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN4_PIN, LOW);
}

void Motor_right(void) {
    GPIO_setPinValue(GPIOD, ENA_PIN, HIGH);
    GPIO_setPinValue(GPIOD, ENB_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN1_PIN, HIGH);
    GPIO_setPinValue(GPIOD, IN2_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN3_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN4_PIN, HIGH);
}

void Motor_stop(void) {
    GPIO_setPinValue(GPIOD, ENA_PIN, LOW);
    GPIO_setPinValue(GPIOD, ENB_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN1_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN2_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN3_PIN, LOW);
    GPIO_setPinValue(GPIOD, IN4_PIN, LOW);
}