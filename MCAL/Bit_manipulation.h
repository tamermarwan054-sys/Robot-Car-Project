#define setBit(reg,bit) (reg |= (1<<bit))
#define clearBit(reg,bit) (reg &= ~(1<<bit))
#define toggleBit(reg,bit) (reg ^= (1<<bit))
#define readBit(reg,bit) ((reg>>bit)&1)