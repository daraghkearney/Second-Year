/*
Daragh Kearney
14/10/2024

This code uses for loops to control the behavior of an LED, depending on if the correct 3-digit unlock PIN is entered or not. If the wrong PIN is entered 3 times in a row the door locks for 30 seconds.

*/


#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"

#define LED 5

int main(void)
{
	uint8_t keyPosition;
	int x, y, count = 0;
	int incorrectAttempts = 0; //incorrect attempts counter
	char keypad[] = "123456789*0#";
	char PIN[] = "123", userInput[3];
	
	/* Initialises MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	keypadConfigure();
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	while (1) {
		//Door closed, tell user to enter PIN
		PORTB_set_pin_level(LED, 1);
		printf("Enter 3 digit PIN to open Door:\n ");
		
		//for loop to read 3 key presses
		count = 0;
		for (x=0;x<3;x++)
		{
			keyPosition = keypadScan();
			userInput[x] = keypad[keyPosition];
			if (userInput[x] == PIN[x]) {
					count++; 
			}
		}
		
		//Verify PIN
		if (count == 3) 
		{
			PORTB_set_pin_level(LED, 0);
			_delay_ms(1000);
			PORTB_set_pin_level(LED, 1); //LED off for 2 seconds if correct
			printf("Door Opening\n");
		}
					
					
				
				else{
					incorrectAttempts++;
					//LED flash 3 times if incorrect
					for (y=0;y<6;y++)
					{
						PORTB_toggle_pin_level(LED); _delay_ms(500);
					}
					
					
				
					 
					printf("Incorrect PIN\n");
				}
		
		if (incorrectAttempts >=3) {
			printf("Too Many Incorrect Attempts. Door Locked for 30 seconds.\n");
			PORTB_set_pin_level(LED, 0); //led off during lock
			_delay_ms(30000); // 30 second lock
			incorrectAttempts = 0; //reset
			
		}
		
		
		
		
		
		
		
		
		
	}
}
