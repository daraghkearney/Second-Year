/*
Daragh Kearney
23/09/2024

This code uses a switch to control the state of an LED

*/


#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5

int main(void)
{
	uint32_t randomNumber = 0, x;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	/* Replace with your application code */
	while (1) {
		//LED Off
		//Tell user to press switch to start game
		//Wait for press and switch release
		PORTB_set_pin_level(LED, 0);
		printf("Press The Switch to Start the Game\n");
		while(PORTB_get_pin_level(SW) == 1);
		while(PORTB_get_pin_level(SW) == 0);
		
		//Generate a random number
		randomNumber = 1000 + rand()%2001;
		
		//Tell user to press switch when LED lights
		//Wait for a random delay
		printf("Press Switch when LED lights...\n");
		for(x=0; x<randomNumber; x++) {
			_delay_ms(1);
		
		}
		//Light LED
		PORTB_set_pin_level(LED, 1);
		
		//Wait for switch press
		x = 0;
		while(PORTB_get_pin_level(SW) == 1) {
			_delay_ms(1);
			x++;
		}
		//print reaction time
		printf("Reaction Time: %lums\n\n\n", x);
		//Wait for switch release
		while(PORTB_get_pin_level(SW) == 0);
		
		
			
		}
		
		
}
