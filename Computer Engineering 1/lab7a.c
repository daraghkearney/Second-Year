/**********************************************************************************
Daragh Kearney
04/11/2024

DC Motor Controlled using XMINI board switch.
*********************************************************************************/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define EN 1
#define IN1 2
#define IN2 3
#define SW 7


int main(void)
{
	atmel_start_init();
	PORTB_set_pin_dir(EN, PORT_DIR_OUT);
	PORTB_set_pin_dir(IN1, PORT_DIR_OUT);
	PORTB_set_pin_dir(IN2, PORT_DIR_OUT);
	PORTB_set_pin_level(EN, 0);
	PORTB_set_pin_level(IN1, 1);
	PORTB_set_pin_level(IN2, 0);
	
	while (1) {
				if(PORTB_get_pin_level(SW) ==0){
					PORTB_set_pin_level(EN, 1);
				}
				else{
					PORTB_set_pin_level(EN, 0);
				}
		
	}
}