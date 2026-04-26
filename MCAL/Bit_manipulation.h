#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#define setBit(reg,bit)    (reg |=  (1 << bit))
#define clearBit(reg,bit)  (reg &= ~(1 << bit))
#define toggleBit(reg,bit) (reg ^=  (1 << bit))
#define readBit(reg,bit)   ((reg >> bit) & 1)

#endif /* BIT_MANIPULATION_H */