#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include "Types.h"

void Motor_init(void);
void Motor_forward(void);
void Motor_backward(void);
void Motor_left(void);
void Motor_right(void);
void Motor_stop(void);

#endif /* MOTOR_INTERFACE_H */