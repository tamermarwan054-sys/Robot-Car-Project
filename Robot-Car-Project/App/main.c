/*
 * main.c — Robot Car: Joystick + Battery Monitoring (16 MHz)
 * Authors:
 * Marwan Tamer
 * Maged Diyaa
 * Ibrahim Salah
 * Belal Barakat
 * Rodaina
 * Jana Mohamed,
 * Mariam Emad
 * Masa Mostafa
 */

#define F_CPU 16000000UL

#include "Types.h"
#include "GPIO_interface.h"
#include "Bit_manipulation.h"
#include "adc.h"
#include "motor_interface.h"
#include "joystick_interface.h"
#include "battery_interface.h"

static void delay_ms(u16 ms) {
    u16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4000; j++)
            asm volatile ("nop");
}

int main(void) {
    ADC_Init();
    Motor_init();
    Joystick_Init();
    Battery_Init();

    while (1) {
        Joystick_Direction dir = Joystick_GetDirection();

        switch (dir) {
            case JOY_FORWARD:   Motor_forward();   break;
            case JOY_BACKWARD:  Motor_backward();  break;
            case JOY_LEFT:      Motor_left();      break;
            case JOY_RIGHT:     Motor_right();     break;
            case JOY_STOP:      Motor_stop();      break;
        }

        Battery_Update();
        delay_ms(100);
    }
}