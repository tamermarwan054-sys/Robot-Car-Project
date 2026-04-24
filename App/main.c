/*
 * main.c — Robot Car: Joystick + Battery Monitoring (16 MHz)
 * Authors: 
 * MARWAN Tamer
 * Maged Diyaa
 * Ibrahim Salah
 * Belal Barakat
 * Rodaina 
 * Jana mohamed
 * Mariam Emad
 * Masa Mostafa
 */

#define F_CPU 16000000UL

#include "Types.h"
#include "GPIO_private.h"
#include "Bit_manipulation.h"
#include "adc.h"
#include "motor.h"
#include "joystick.h"
#include "battery.h"          


static void delay_ms(u16 ms) {
    u16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4000; j++)
            asm volatile ("nop");
}


int main(void) {

    
    /* Initialize all modules — ADC must be first */
    ADC_Init();               /* joystick + battery both use ADC */
    Motor_init();             /* PD2–PD7 = outputs */
    Joystick_Init();
    Battery_Init();           /* PD0 = output, LED off */

    while (1) {

        /* Read joystick → drive motors */
        Joystick_Direction dir = Joystick_GetDirection();

        switch (dir) {
            case JOY_FORWARD:   Motor_forward();   break;
            case JOY_BACKWARD:  Motor_backward();  break;
            case JOY_LEFT:      Motor_left();      break;
            case JOY_RIGHT:     Motor_right();     break;
            case JOY_STOP:      Motor_stop();      break;
        }

        /* Check battery → blink red LED if below 9V */
        Battery_Update();     

        delay_ms(100);
    }
}