 #include <stdint.h>
#include "drawings.h"
#include "digital.h"
#include <msp430.h>


void init_joystick(void)
{
    // SEL bouton (P1.6)
    P1DIR &= ~BIT6;
    P1REN |= BIT6;
    P1OUT |= BIT6;

    // P6.3 (Y) et P6.5 (X) en analog
    P6SEL |= BIT3 | BIT5;

    // ADC12 config
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
    ADC12CTL1 = ADC12SHP;

    ADC12CTL0 |= ADC12ENC;
}

uint16_t read_x(void)
{
    ADC12CTL0 &= ~ADC12ENC;
    ADC12MCTL0 = ADC12INCH_5;
    ADC12CTL0 |= ADC12ENC | ADC12SC;
    while(!(ADC12IFG & BIT0));
    return ADC12MEM0;
}

uint16_t read_y(void)
{
    ADC12CTL0 &= ~ADC12ENC;
    ADC12MCTL0 = ADC12INCH_3;
    ADC12CTL0 |= ADC12ENC | ADC12SC;
    while(!(ADC12IFG & BIT0));
    return ADC12MEM0;
}

uint8_t read_sel(void)
{
    return (P1IN & BIT6) == 0;
}
