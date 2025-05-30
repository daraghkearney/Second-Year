/*
Daragh Kearney
30/09/2024

This code uses a switch to toggle between LED on, off, or flashing at 5Hz depending on one of 3 letters inputted, monitors switch via cereal port

*/


#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define LED 5
#define SW 7

int main(void)
{
	uint8_t ch = 'o', temp;
	uint8_t switchCurrent = 1, switchPrevious = 1;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	
	
	/* inclusion of temporary character to prevent infinite error loop */
	while(1) {
		//check for a character received
		if(USART_0_is_rx_ready()) {
			temp = USART_0_read();
			printf("Character received: %c\n", temp);
			if(temp == 'o' || temp == 'f' || temp == 'l') {
				ch = temp;
			}
			else{
				printf("Invalid input, try again...\n");
			}
		}
		//control LED
		switch(ch) {
			case 'o': PORTB_set_pin_level(LED, 0); // turns LED off
			break;
			
			case 'l': PORTB_set_pin_level(LED, 1); // turns LED on
			break;
			
			case 'f': PORTB_toggle_pin_level(LED); _delay_ms(100); // flashes LED at a frequency of 5Hz
			break;
			
			default: printf("Invalid input, try again...\n"); // displays error message if incorrect character is entered
			break;
			
		}
		
		//Check switch status
		switchCurrent = PORTB_get_pin_level(SW);
		//check if different from previous reading
		if (switchCurrent != switchPrevious) { 
			if (switchCurrent == 0) {
			printf("Switch Press \n");
			}
			else {
				printf("Switch Release \n"); //if different print switch status based on logic level
				
				
			}
		}
		
		switchPrevious = switchCurrent; //update previous reading to current reading
		
		
	}
		
	
}
