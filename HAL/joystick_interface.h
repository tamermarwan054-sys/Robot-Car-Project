#ifndef JOYSTICK_INTERFACE_H
#define JOYSTICK_INTERFACE_H

#include "Types.h"
#include "joystick_private.h"

typedef enum {
    JOY_FORWARD,
    JOY_BACKWARD,
    JOY_LEFT,
    JOY_RIGHT,
    JOY_STOP
} Joystick_Direction;

void Joystick_Init(void);
Joystick_Direction Joystick_GetDirection(void);

#endif /* JOYSTICK_INTERFACE_H */