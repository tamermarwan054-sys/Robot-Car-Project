#ifndef MOTOR_H
#define MOTOR_H

#include "Types.h"

void Motor_init(void);
void Motor_forward(void);
void Motor_backward(void);
void Motor_left(void);
void Motor_right(void);
void Motor_stop(void);
void Motor_setSpeedLeft(u8 speed);
void Motor_setSpeedRight(u8 speed);

#endif /* MOTOR_H */