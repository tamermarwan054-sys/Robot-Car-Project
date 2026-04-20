// /*
//  * main.c - Robot Car with Joystick Control (16 MHz)
//  * Author: MARWAN
//  */

// #define F_CPU 16000000UL

// #include "Types.h"
// #include "gpio_private.h"
// #include "motor.h"
// #include "joystick.h"
// #include "adc.h"

// static void delay_ms(u16 ms) {
//     u16 i, j;
//     for (i = 0; i < ms; i++)
//         for (j = 0; j < 4000; j++)
//             asm volatile ("nop");
// }

// int main(void) {
//     // Initialize everything
//     DDRC |= (1 << 0);           // PC0 heartbeat LED
//     Motor_init();
//     ADC_Init();                 // Initialize ADC (we need to create this)
//     Joystick_Init();

//     while (1) {
//         PORTC ^= (1 << 0);      // LED blink

//         Joystick_Direction dir = Joystick_GetDirection();

//         switch (dir) {
//             case JOY_FORWARD:
//                 Motor_forward();
//                 break;
//             case JOY_BACKWARD:
//                 Motor_backward();
//                 break;
//             case JOY_LEFT:
//                 Motor_left();
//                 break;
//             case JOY_RIGHT:
//                 Motor_right();
//                 break;
//             case JOY_STOP:
//                 Motor_stop();
//                 break;
//         }

//         delay_ms(100);   // Small delay for smooth response
//     }
// }
/*
 * main.c — Robot Car: Joystick + Battery Monitoring (16 MHz)
 * Author: MARWAN
 */

#define F_CPU 16000000UL

#include "Types.h"
#include "GPIO_private.h"
#include "Bit_manipulation.h"
#include "adc.h"
#include "motor.h"
#include "joystick.h"
#include "battery.h"          /* added */


static void delay_ms(u16 ms) {
    u16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4000; j++)
            asm volatile ("nop");
}


int main(void) {

    /* Configure heartbeat LED */
    setBit(DDRC, 0);          /* PC0 = output */

    /* Initialize all modules — ADC must be first */
    ADC_Init();               /* joystick + battery both use ADC */
    Motor_init();             /* PD2–PD7 = outputs */
    Joystick_Init();
    Battery_Init();           /* PD0 = output, LED off */

    while (1) {

        /* Heartbeat — proves MCU is alive */
        toggleBit(PORTC, 0);

        /* Read joystick → drive motors */
        Joystick_Direction dir = Joystick_GetDirection();

        switch (dir) {
            case JOY_FORWARD:   Motor_forward();   break;
            case JOY_BACKWARD:  Motor_backward();  break;
            case JOY_LEFT:      Motor_left();      break;
            case JOY_RIGHT:     Motor_right();     break;
            case JOY_STOP:      Motor_stop();      break;
        }

        /* Check battery → blink red LED if below 11V */
        Battery_Update();     /* added */

        delay_ms(100);
    }
}