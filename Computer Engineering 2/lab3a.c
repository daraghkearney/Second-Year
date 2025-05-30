/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 3a
10/02/2025
Measuring the Speed of a Car

Program to measure the speed of a vehicle that passes over 2 sensors placed 100M apart.
Software polling is used to detect the switches being pressed.
The speed of the car is calculated and printed alongside the Car Number and time.

-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define START_SW 2
#define STOP_SW 3

int main(void)
{
	uint32_t ms = 0, speed, car = 1;
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	
	while (1)
	{
		//wait for start pin to go low
		while(PORTD_get_pin_level(START_SW) == 1)
		{} //while start pin is high, nothing happens
		
		
		ms = 0;
		
		//increment ms variable every ms while the stop pin is high
		while(PORTD_get_pin_level(STOP_SW) == 1)
		{
			_delay_ms(1);
			ms++;
		}
		
		
		//calculate and print speed
		speed = 360000/ms;
		printf("The Speed of car %lu is: %lu km/h\n Time recorded: %lums\n", car, speed, ms);
		car++;
		
		//wait for stop pin to go high
		while(PORTD_get_pin_level(STOP_SW) == 0)
		{}
		//wait for start pin to go high
		while(PORTD_get_pin_level(START_SW) == 0)
		{}
		
		
	}
}