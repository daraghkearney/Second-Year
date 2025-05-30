#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	
	/* Replace with your application code */
	while (1) {
		//wait for switch press
		while(PORTB_get_pin_level(SW)== 1){}
			printf("Switch pressed\n");
			//wait for switch release
			while(PORTB_get_pin_level(SW)== 0){}
	}
}
