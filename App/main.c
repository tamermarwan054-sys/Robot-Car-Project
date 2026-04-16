/*
 * main.c
 * Author: MARWAN
 */

#define F_CPU 1000000UL

#include "Types.h"
#include "gpio_private.h"
#include "motor.h"

/*
    Manual delay calibrated for 1MHz internal RC
    At 1MHz: 1 cycle = 1us
    Inner loop = ~4 cycles (nop + loop overhead) x 250 = ~1ms per outer iteration
*/
static void delay_ms(u16 ms) {
    u16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 250; j++)
            asm volatile ("nop");
}

int main(void) {
    DDRC |= (1 << 0);       // PC0 heartbeat LED
    Motor_init();

    while (1) {
        PORTC ^= (1 << 0);  // blink

        Motor_forward();
        delay_ms(2000);

        Motor_stop();
        delay_ms(1000);

        Motor_left();
        delay_ms(1000);

        Motor_stop();
        delay_ms(1000);

        Motor_backward();
        delay_ms(2000);

        Motor_stop();
        delay_ms(1000);

        Motor_right();
        delay_ms(1000);

        Motor_stop();
        delay_ms(1000);
    }
}