#include "motor_interface.h"
#include "motor_private.h" 

void Motor_init(void) {
    pinMode(GPIOD, IN1_PIN, OUTPUT);
    pinMode(GPIOD, IN2_PIN, OUTPUT);
    pinMode(GPIOD, IN3_PIN, OUTPUT);
    pinMode(GPIOD, IN4_PIN, OUTPUT);
    pinMode(GPIOD, ENA_PIN, OUTPUT);
    pinMode(GPIOD, ENB_PIN, OUTPUT);

    digitalWrite(GPIOD, ENA_PIN, HIGH);
    digitalWrite(GPIOD, ENB_PIN, HIGH);

    Motor_stop();
}

void Motor_forward(void) {
    digitalWrite(GPIOD, ENA_PIN, HIGH);
    digitalWrite(GPIOD, ENB_PIN, HIGH);
    digitalWrite(GPIOD, IN1_PIN, HIGH);
    digitalWrite(GPIOD, IN2_PIN, LOW);
    digitalWrite(GPIOD, IN3_PIN, HIGH);
    digitalWrite(GPIOD, IN4_PIN, LOW);
}

void Motor_backward(void) {
    digitalWrite(GPIOD, ENA_PIN, HIGH);
    digitalWrite(GPIOD, ENB_PIN, HIGH);
    digitalWrite(GPIOD, IN1_PIN, LOW);
    digitalWrite(GPIOD, IN2_PIN, HIGH);
    digitalWrite(GPIOD, IN3_PIN, LOW);
    digitalWrite(GPIOD, IN4_PIN, HIGH);
}

void Motor_left(void) {
    digitalWrite(GPIOD, ENA_PIN, HIGH);
    digitalWrite(GPIOD, ENB_PIN, HIGH);
    digitalWrite(GPIOD, IN1_PIN, LOW);
    digitalWrite(GPIOD, IN2_PIN, HIGH);
    digitalWrite(GPIOD, IN3_PIN, HIGH);
    digitalWrite(GPIOD, IN4_PIN, LOW);
}

void Motor_right(void) {
    digitalWrite(GPIOD, ENA_PIN, HIGH);
    digitalWrite(GPIOD, ENB_PIN, HIGH);
    digitalWrite(GPIOD, IN1_PIN, HIGH);
    digitalWrite(GPIOD, IN2_PIN, LOW);
    digitalWrite(GPIOD, IN3_PIN, LOW);
    digitalWrite(GPIOD, IN4_PIN, HIGH);
}

void Motor_stop(void) {
    digitalWrite(GPIOD, ENA_PIN, LOW);
    digitalWrite(GPIOD, ENB_PIN, LOW);
    digitalWrite(GPIOD, IN1_PIN, LOW);
    digitalWrite(GPIOD, IN2_PIN, LOW);
    digitalWrite(GPIOD, IN3_PIN, LOW);
    digitalWrite(GPIOD, IN4_PIN, LOW);
}