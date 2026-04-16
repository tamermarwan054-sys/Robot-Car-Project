#ifndef MOTOR_PRIVATE_H
#define MOTOR_PRIVATE_H

#include "Types.h"

/* Pin numbers on PORT D (PD2 to PD7) */
#define IN1_PIN     2
#define IN2_PIN     3
#define IN3_PIN     4
#define IN4_PIN     5
#define ENA_PIN     6
#define ENB_PIN     7

/* Bit masks for setting/clearing bits */
#define BIT(bit) (1 << (bit))

#endif /* MOTOR_PRIVATE_H */