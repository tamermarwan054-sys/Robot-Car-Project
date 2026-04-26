// joystick.c
#include "joystick_interface.h"
#include "joystick_private.h" 
#include "adc.h"

void Joystick_Init(void) {
}

Joystick_Direction Joystick_GetDirection(void) {
    u16 x = ADC_Read(0);   /* PA0 = X axis */
    u16 y = ADC_Read(1);   /* PA1 = Y axis */

    if (y > JOY_THRESHOLD_HIGH) return JOY_FORWARD;
    if (y < JOY_THRESHOLD_LOW)  return JOY_BACKWARD;
    if (x > JOY_THRESHOLD_HIGH) return JOY_RIGHT;
    if (x < JOY_THRESHOLD_LOW)  return JOY_LEFT;

    return JOY_STOP;
}