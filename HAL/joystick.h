#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Types.h"

typedef enum {
    JOY_FORWARD,
    JOY_BACKWARD,
    JOY_LEFT,
    JOY_RIGHT,
    JOY_STOP
} Joystick_Direction;

void Joystick_Init(void);
Joystick_Direction Joystick_GetDirection(void);

#endif /* JOYSTICK_H */