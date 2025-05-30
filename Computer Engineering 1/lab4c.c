/*
Daragh Kearney
07/10/2024

This code uses a switch to roll a dice and generate a random number between 1 and 6 on release

*/


#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7

int main(void)
{
	uint32_t x = 1;
	uint8_t display[6] = {0x06, 0x5b, 0x4F, 0x66, 0x6d, 0x7d };
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialization code here */
	//Configure PB6 to PB0 as output
	DDRB = 0x7F;      //0111 1111
	
	while(1){
		if(PORTB_get_pin_level(SW) == 0) //if switch is being pressed dice is rolling and displays random number on release
		{
			PORTB = display[x];
			x++;
			if(x == 7)
			{
				x=1;
			}
			
		}
	}
	
	
		
		
			
				
		
	
}
