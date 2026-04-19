/*
 * adc.c — ATmega32 ADC driver
 * AVCC reference, right-adjusted, prescaler 128 for 16 MHz
 */

#include "adc.h"
#include "GPIO_private.h"

/* ── ADC register definitions (memory-mapped addresses) ── */
#define ADMUX   *((volatile u8*)0x27)   /* Multiplexer + reference select */
#define ADCSRA  *((volatile u8*)0x26)   /* Control and status register    */
#define ADCH    *((volatile u8*)0x25)   /* ADC result high byte (bits 9:8)*/
#define ADCL    *((volatile u8*)0x24)   /* ADC result low  byte (bits 7:0)*/

/*
 * ADC_Init
 * Set AVCC as reference, right-adjusted result, prescaler=128.
 * DO NOT start a conversion here — let ADC_Read do that.
 */
void ADC_Init(void) {
    /* ADMUX: REFS1=0 REFS0=1 → AVCC reference | ADLAR=0 → right adjusted */
    ADMUX = 0x40;

    /* ADCSRA: ADEN=1 (enable) | prescaler bits = 111 = 128 */
    /* 16MHz / 128 = 125kHz ADC clock — within 50-200kHz spec */
    ADCSRA = (1 << 7) | 7;       /* ADEN + ADPS2:ADPS1:ADPS0 = 1:1:1 */
}

/*
 * ADC_Read
 * Select channel, start one conversion, wait, return 10-bit result.
 * ADCL MUST be read before ADCH — ATmega32 hardware requirement.
 *
 * @param channel  0 = PA0 (joystick X), 1 = PA1 (joystick Y)
 * @return         10-bit result, 0–1023
 */
u16 ADC_Read(u8 channel) {
    /* Select channel — keep upper bits (reference selection) unchanged */
    ADMUX = (ADMUX & 0xE0) | (channel & 0x07);

    /* Start conversion by setting ADSC (bit 6) */
    ADCSRA |= (1 << 6);

    /* Wait — hardware clears ADSC when conversion is complete */
    while (ADCSRA & (1 << 6));

    /* Read ADCL first — this locks ADCH until we read it */
    u8 low  = ADCL;     /* bits 7:0 of result — MUST be first */
    u8 high = ADCH;     /* bits 9:8 of result — unlocks after this */

    return ((u16)high << 8) | low;
}