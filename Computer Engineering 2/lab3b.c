/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 3b
10/02/2025
Measuring the Speed of a Car

Program to measure the speed of a vehicle that passes over 2 sensors placed 100M apart.
Similar to 3a, however in this program External Interrupts are used to detect the switches being pressed.
The speed of the car is calculated and printed alongside the Car Number and time.

-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

uint32_t ms, speed;
uint8_t carNum = 1;

ISR(INT0_vect) { //start sensor interrupt handler
	//ms = 0
	ms = 0;
}


ISR(INT1_vect) { //stop sensor interrupt handler
	//calculate and print speed
	speed = 360000/ms;
	printf("The Speed of car %d is: %lu km/h\n Time recorded: %lums\n", carNum, speed, ms);
	carNum++;
}

int main(void)
{
	
	
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	
	EICRA = 0x0A; //INT0, INT1 falling edge interrupts
	EIMSK = 0x03; //Enable INT0, INT1
	sei();
	
	/* Replace with your application code */
	
	
	while (1) {
		_delay_ms(1);
		ms++;
	}
}