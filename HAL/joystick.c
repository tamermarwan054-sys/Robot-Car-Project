#include "joystick.h"
#include "joystick_private.h"
#include "adc.h"          // We will create this in MCAL

void Joystick_Init(void) {
    // ADC will be initialized in main or in MCAL init
}

Joystick_Direction Joystick_GetDirection(void) {
    u16 x = ADC_Read(0);   // PA0 = X axis
    u16 y = ADC_Read(1);   // PA1 = Y axis

    // Y axis has priority (forward/backward)
    if (y > JOY_THRESHOLD_HIGH) {
        return JOY_FORWARD;
    }
    if (y < JOY_THRESHOLD_LOW) {
        return JOY_BACKWARD;
    }

    // X axis for left/right when Y is in center
    if (x > JOY_THRESHOLD_HIGH) {
        return JOY_RIGHT;
    }
    if (x < JOY_THRESHOLD_LOW) {
        return JOY_LEFT;
    }

    // Dead zone in center
    return JOY_STOP;
}