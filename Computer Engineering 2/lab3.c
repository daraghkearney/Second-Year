/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 2
27/01/2025
Keyless Lock Door Entry System

User enters a 3-digit PIN on keypad to open door.
LCD displays user feedback.
LED is on when door is closed.
LED goes off for 2 seconds when door is opened.
LED flashes 3 times when incorrect PIN is entered.
The system is locked out for 30 seconds when 3 or more incorrect PINs in a row are entered.

The code is implemented as a finite state machine. 
The state machine has 5 states: CLOSED, OPEN, INCORRECT, LOCKOUT, ADMIN.
The user must enter an administration password to enter the administration state. The user is then asked to enter the old user password before being asked to enter the new password.
-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define START_SW 2
#define STOP_SW 3

int main(void)
{
	uint32_t ms = 0, speed; 
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	
	/* Replace with your application code */
	
	
	while (1) 
	{
		//wait for start pin to go low
		while(PORTD_get_pin_level(START_SW) == 1)
		{} //while start pin is high do nothing
		
		
		ms = 0;
		
		//increment ms variable every ms while the stop pin is high
		while(PORTD_get_pin_level(STOP_SW) == 1)
		{
			_delay_ms(1);
			ms++;
		}
		
		
		//calculate and print speed
		speed = 360000/ms;
		printf("The Speed of the car is %lu km/h\n", speed);
		
		//wait for stop pin to go high
		while(PORTD_get_pin_level(STOP_SW) == 0)
		{}
		//wait for start pin to go high
		while(PORTD_get_pin_level(START_SW) == 0)
		{}
		
		
	}
		}