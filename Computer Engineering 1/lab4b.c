/*
Daragh Kearney
07/10/2024

This code uses a switch to toggle between upwards or downwards counting of numbers 0 to 10 on an LED Display depending on the logic level of the switch

*/


#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7

int main(void)
{
	int8_t x;
	uint8_t display[10] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6d, 0x7d, 0x07, 0x7F, 0x6F };
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialization code here */
	//Configure PB6 to PB0 as output
	DDRB = 0x7F;      //0111 1111
	
	while (1) {
		PORTB = display[x];
		_delay_ms(1000);
		
		if(PORTB_get_pin_level(SW)){ // when switch is released numbers count up
			x++;
			if(x==10){
				x=1;
			}
		}else { // when switch is pressed and held numbers count down
			x--;
			if(x==-1){
			x=9;
			
			}
		
			
		}
	}
}
