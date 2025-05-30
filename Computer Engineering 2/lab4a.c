/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 4
17/02/2025
Measuring the Speed of a Car

Program to measure the speed of a vehicle that passes over 2 sensors placed 100M apart.
Similar to Lab 3, however in this program Pin Change Interrupts are used to detect the switches being pressed.
The speed of the car is calculated and printed alongside the Car Number and time.
A speed limit has been introduced.

-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define START_SENSOR 2
#define STOP_SENSOR 3

uint32_t ms = 0, speed, carNum = 1;
uint16_t speedLimit;
bool startMeasuring = 0;

ISR(PCINT2_vect) {      //Port D pin change interrupt handler
	if (PORTD_get_pin_level(START_SENSOR) == 0) {
		ms = 0; //if start sensor is 0, ms = 0
		startMeasuring = 1;
	}
	
	else if (PORTD_get_pin_level(STOP_SENSOR) == 0)
	{
		if (startMeasuring == 1)
		{
			speed = 360000/ms;
			printf("The Speed of car %lu is: %lu km/h\n Time recorded: %lums\n", carNum, speed, ms); //else if stop sensor is 0; calculate and print speed
			if (speed > speedLimit) {
				printf("WARNING: Over Speed Limit!");
			}
			carNum++;
			startMeasuring = 0;
			
		}
		
	}
	
}

int main(void)
{
	bool limitSet = 0;
	
	uint8_t userInput[10], i = 0;
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	//user configures speed limit
	while(limitSet == 0) {
		//ask user to enter a limit terminated by *
		printf("Please enter a Speed limit between 30 and 100 terminated by '*'\n");
		i = 0;
		while(1) {
			userInput[i] = USART_0_read();
			
			
			
			if (userInput[i] == '*')   //check if input is '*'
			{
				speedLimit = atoi(userInput);    //if yes, convert string to integer using atoi()
				
				if (speedLimit < 30 || speedLimit > 100) {
					printf("ERROR: Limit is out of range.\n");
					break;  //else print error message and break
				}
				else {
					printf("Speed Limit has been set to %dkm/h\n", speedLimit);  //if limit in range set limitSet flag and break
					limitSet = 1;
					break;
					
					
				}
			}
			else {
				i++;  //if not '*' increment i
				
			}
		}
		
	}
	
	
	/* Replace GPIO and peripheral initialization code here */
	
	PCICR = 0x04; //Enable pin change interrupts for port D
	PCMSK2 = 0x0c; //Enable interrupts on PD3 and PD2
	sei();
	
	/* Replace with your application code */
	while (1) {
		_delay_ms(1);
		ms++;
	}
}