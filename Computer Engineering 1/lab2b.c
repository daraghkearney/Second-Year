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
	uint8_t count = 0;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	/* Replace with your application code */
	while (1) {
		//check for switch press
		if(PORTB_get_pin_level(SW)== 0){
			count++;
			printf("Switch pressed, Count = %d\n", count);
			//wait for switch release
			while(PORTB_get_pin_level(SW)== 0){}
		}
				
			//control LED
			switch(count){
				case 0: PORTB_set_pin_level(LED, 0);     //LED off
				break;
				
				case 1: PORTB_set_pin_level(LED, 1);     //LED on
				break;
				
				case 2: PORTB_toggle_pin_level(LED); _delay_ms(500);     //1Hz Flash
				break;
				
				case 3: PORTB_toggle_pin_level(LED); _delay_ms(100);     //5Hz Flash
				break;
				
				default: count = 0;
				break;
			}
	}
}
