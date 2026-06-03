#include <stdint.h>

#include <msp430.h>



void init_buttons (void);
uint8_t state_button_L (void); /* Return 1 if the button is pressed, 0 otherwise*/
uint8_t state_button_R (void); /* Return 1 if the button is pressed, 0 otherwise*/
void init_buttons_interrupt(void);

//uint8_t check_FLAG_L(void);
//uint8_t check_FLAG_R(void);
//void Init_rgb_led(void);
//void round_robin_led(void);
void init_buzzer_led(void);
void toggle_led(void);
void toggle_buzzer(void);
void init_joystick(void);
uint16_t read_x(void);
uint16_t read_y(void);

uint8_t read_sel(void);
