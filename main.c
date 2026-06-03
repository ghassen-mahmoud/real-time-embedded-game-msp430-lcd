#include <msp430.h>
#include "system.h"
#include "display.h"
#include "drawings.h"
#include <stdint.h>
#include <stdio.h>
#define UP      0
#define DOWN    1
#define LEFT    2
#define RIGHT   3

char msg[20];
uint8_t collision(uint8_t rx, uint8_t ry, uint8_t cx, uint8_t cy)
{
    return (cx >= rx && cx <= rx + 9 &&
            cy >= ry && cy <= ry + 9);
}

void delay_ms(uint16_t ms)
{
    while(ms--)
        __delay_cycles(8000); // 1 ms si 8 MHz
}

void generate_circle(uint8_t *cx, uint8_t *cy,
                     uint8_t radius,
                     int32_t *color,
                     uint16_t *seed,
                     uint16_t *timer,
                     uint8_t *is_red)
{
    *seed = (*seed * 11035) + 12345;

    *cx = radius + (*seed % (128 - 2 * radius));

    *seed = (*seed * 11035) + 12345;

    *cy = radius + (*seed % (128 - 2 * radius));

    *seed = (*seed * 11035) + 12345;

    if((*seed % 10) < 3)
    {
        *color = GRAPHICS_COLOR_RED;
        *timer = 200;      // 200 × 10ms = 2 secondes
        *is_red = 1;
    }
    else
    {
        *color = GRAPHICS_COLOR_YELLOW_GREEN;
        *timer = 0;        // pas de timer pour vert
        *is_red = 0;
    }
}

void main(void)
{
    uint8_t x = 0, y = 0;
    uint8_t circle_x = 20, circle_y = 20;
    uint8_t radius = 5;

    uint16_t seed = 1234;
    uint16_t score = 0;
    uint16_t speed = 10;

    uint16_t circle_timer = 0;
    uint8_t circle_is_red = 0;
    int32_t circle_color;

    uint8_t direction = DOWN;
    uint8_t game_over = 0;

    WDTCTL = WDTPW | WDTHOLD;

    Init_clock();
    Init_display();

    /* boutons */
    P1DIR &= ~BIT1; P1REN |= BIT1; P1OUT |= BIT1;
    P2DIR &= ~BIT1; P2REN |= BIT1; P2OUT |= BIT1;
    P3DIR &= ~BIT7; P3REN |= BIT7; P3OUT |= BIT7;
    P4DIR &= ~BIT0; P4REN |= BIT0; P4OUT |= BIT0;

    /* premier cercle */
    generate_circle(&circle_x, &circle_y,
                    radius,
                    &circle_color,
                    &seed,
                    &circle_timer,
                    &circle_is_red);

    Filled_circle(circle_x, circle_y, radius, circle_color);

    while(1)
    {
        if(game_over)
        {
            Filled_rectangle(0,127,0,127,GRAPHICS_COLOR_WHITE);
            write_string((uint8_t*)"GAME OVER  ", 30, 50, GRAPHICS_COLOR_RED);
            delay_ms(1000);
            sprintf(msg, "SCORE: %d ", score);

               write_string((uint8_t*)msg, 30, 50, GRAPHICS_COLOR_RED);
            while(1);
        }

        /* boutons */
        if(!(P1IN & BIT1)) direction = UP;
        if(!(P2IN & BIT1)) direction = DOWN;
        if(!(P3IN & BIT7)) direction = LEFT;
        if(!(P4IN & BIT0)) direction = RIGHT;

        /* effacer rectangle */
        Filled_rectangle(x, x+9, y, y+9, GRAPHICS_COLOR_WHITE);

        /* mouvement */
        if(direction == UP)    y = (y==0)?118:y-1;
        if(direction == DOWN)  y = (y>118)?0:y+1;
        if(direction == LEFT)  x = (x==0)?118:x-1;
        if(direction == RIGHT) x = (x>118)?0:x+1;

        /* collision */
        if(collision(x,y,circle_x,circle_y))
        {
            if(circle_color == GRAPHICS_COLOR_YELLOW_GREEN)
            {
                score++;

                if(score % 5 == 0 && speed > 5)
                    speed /= 2;

                Filled_circle(circle_x, circle_y, radius, GRAPHICS_COLOR_WHITE);

                generate_circle(&circle_x, &circle_y,
                                radius,
                                &circle_color,
                                &seed,
                                &circle_timer,
                                &circle_is_red);

                Filled_circle(circle_x, circle_y, radius, circle_color);
            }
            else
            {
                game_over = 1;
            }
        }

        /* gestion timer cercle rouge */
        if(circle_is_red)
        {
            if(circle_timer > 0)
            {
                circle_timer--;
            }

            if(circle_timer == 0)
            {
                /* supprimer cercle rouge non mangé */
                Filled_circle(circle_x, circle_y, radius, GRAPHICS_COLOR_WHITE);

                generate_circle(&circle_x, &circle_y,
                                radius,
                                &circle_color,
                                &seed,
                                &circle_timer,
                                &circle_is_red);

                Filled_circle(circle_x, circle_y, radius, circle_color);
            }
        }

        /* dessiner rectangle */
        Filled_rectangle(x, x+9, y, y+9, GRAPHICS_COLOR_BLACK);

        delay_ms(speed);
    }
}
