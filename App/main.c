/*
 * main.c - Motor Direction Test (16 MHz)
 * Author: MARWAN
 */

#define F_CPU 16000000UL

#include "Types.h"
#include "gpio_private.h"
#include "motor.h"

/* ============================================= */
/* Delay function - MUST be BEFORE main()       */
/* ============================================= */
static void delay_ms(u16 ms) {
    u16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4000; j++)        // 4000 = real hardware
            asm volatile ("nop");         // change to 100 only for fast Proteus
}

/* ============================================= */
int main(void) {
    DDRC |= (1 << 0);      // PC0 heartbeat LED
    Motor_init();

    while (1) {
        PORTC ^= (1 << 0); // LED blinks to prove code is running

        /* ================== TEST ONE DIRECTION AT A TIME ================== */
        Motor_forward();      // ← change this to test others
        delay_ms(2000);

        // Motor_backward();
        // delay_ms(2000);

        // Motor_left();
        // delay_ms(2000);

        // Motor_right();
        // delay_ms(2000);

        // Motor_stop();
        // delay_ms(2000);
        /* ================================================================ */
    }
}