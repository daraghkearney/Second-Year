/**********************************************************************************
Daragh Kearney
11/11/2024

Voltage and Temperature Monitor.
This program reads the voltage from the POT and prints the digital sample along with the corresponding analog voltage in mV.
The program also prints the temperature that is read from the LM35.

The program asks the user to enter low and high thresholds, with an alarm generated if the POT voltage is outside of the threshold range.


*********************************************************************************/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "adc_Start.h"




int main(void)
{
	uint16_t sample, voltage;
	char userInput[5] = "0";
	uint8_t x;
	uint16_t lowT, highT;
	
	
	atmel_start_init();
	
	while(1) {
			//ask user to enter threshold
			printf("Enter a 4-digit high threshold\n");
			
			//for loop to read 4 serial characters
			for(x=0; x<4; x++) {
				userInput[x] = USART_0_read();
			}
			//use atoi() to convert from string to integer
			highT = atoi(userInput);
			printf("High Threshold: %d\n", highT);
			
			//repeat for low threshold
			printf("Enter a 4-digit low threshold\n");
			
			for(x=0; x<4; x++) {
				userInput[x] = USART_0_read();
			}
			
			lowT = atoi(userInput);
			printf("Low Threshold: %d\n", lowT);
			
			//error check the user inputs
			if (lowT >= highT || highT > 5000) {
				printf("ERROR: Entered thresholds out of range, Try again\n");
			} else {
				printf("Thresholds set, High: %lumV, Low: %lumV\n", highT, lowT);
				break;
				
			}
			
		}

	

	
	while (1) {
		sample = read_ADC(0);
		voltage = (uint32_t)sample *5000/1024; 
		printf("Sample: %d, VIN: %dmV\n", sample, voltage);
		sample = read_ADC(4);
		printf("Sample: %d, Temperature: %luC\n\n", sample, (uint32_t)sample *500/1024);
		
		// checking for voltage outside of set thresholds
		if (voltage > highT)
		{
			printf("WARNING: Voltage too high\n");
		} else if (voltage < lowT)
		{
			printf("WARNING: Voltage too low\n");
		}
		_delay_ms(1000);
		
		
	}
		
}