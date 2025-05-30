/**********************************************************************************
Daragh Kearney
11/11/2024


*********************************************************************************/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "adc_Start.h"




int main(void)
{
	uint16_t sample;
	char userInput[5] = "0";
	uint8_t x;
	
	atmel_start_init();
	

	

	
	while (1) {
		sample = read_ADC(0);
		printf("Sample: %d, VIN: %lumVn\n", sample, (uint32_t)sample *5000/1024);
		sample = read_ADC(4);
		printf("Sample: %d, Temperature: %luC\n\n", sample, (uint32_t)sample *500/1024);
		_delay_ms(1000);
	}
		
}