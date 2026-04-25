#include "motor.h"
#include "motor_private.h"
#include "gpio_private.h"

/* Helper: set a pin high or low on PORT D */
static void setPin(u8 pin, u8 value) {
    if (value)
        PORTD |= BIT(pin);
    else
        PORTD &= ~BIT(pin);
}

/* Initialize motor pins as outputs, enable both motors */
void Motor_init(void) {
    // Set PD2-PD7 as outputs
    DDRD |= BIT(IN1_PIN) | BIT(IN2_PIN) | BIT(IN3_PIN) | BIT(IN4_PIN)
          | BIT(ENA_PIN) | BIT(ENB_PIN);
    
    // Enable both motors (set ENA, ENB high)
    setPin(ENA_PIN, 1);
    setPin(ENB_PIN, 1);
    
    // Stop motors initially
    Motor_stop();
}

void Motor_forward(void) {
    /* Re-enable both motors */
    setPin(ENA_PIN, 1);
    setPin(ENB_PIN, 1);

    setPin(IN1_PIN, 1);
    setPin(IN2_PIN, 0);
    setPin(IN3_PIN, 1);
    setPin(IN4_PIN, 0);
}

void Motor_backward(void) {
    setPin(ENA_PIN, 1);
    setPin(ENB_PIN, 1);

    setPin(IN1_PIN, 0);
    setPin(IN2_PIN, 1);
    setPin(IN3_PIN, 0);
    setPin(IN4_PIN, 1);
}

void Motor_left(void) {
    setPin(ENA_PIN, 1);
    setPin(ENB_PIN, 1);

    setPin(IN1_PIN, 0);
    setPin(IN2_PIN, 1);
    setPin(IN3_PIN, 1);
    setPin(IN4_PIN, 0);
}

void Motor_right(void) {
    setPin(ENA_PIN, 1);
    setPin(ENB_PIN, 1);

    setPin(IN1_PIN, 1);
    setPin(IN2_PIN, 0);
    setPin(IN3_PIN, 0);
    setPin(IN4_PIN, 1);
}

void Motor_stop(void) {
    /* Disable enable pins */
    setPin(ENA_PIN, 0);   /* Left  motor OFF */
    setPin(ENB_PIN, 0);   /* Right motor OFF */

    /* clear direction pins */
    setPin(IN1_PIN, 0);
    setPin(IN2_PIN, 0);
    setPin(IN3_PIN, 0);
    setPin(IN4_PIN, 0);
}

