/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 8
31/03/2025
Part A: Electronic Gate

A servo motor arm position is controlled by a PWM waveform. The motor arm may be
positioned in a range of 0 to 180 degrees by varying the width of the on pulse.

The PWM signal is used to control an electronic gate.
The gate position is controlled by serial characters. The character ‘o’ opens the gate,
the character ‘c’ closes the gate.

-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define PW_0_DEGREE 1000
#define PW_180_DEGREE 2000
#define PERIOD 20000

#define MOTOR 1


uint8_t motorAngle = 90;
volatile bool updateMotor = 0;

ISR(USART_RX_vect) {
	uint8_t ch = UDR0;
	
	switch(ch) {
		case 'o': //open
		printf("Gate Open\n\n");
		motorAngle = 0;
		updateMotor = 1;
		break;
		
		case 'c': //closed
		printf("Gate Close\n\n");
		motorAngle = 90;
		updateMotor = 1;
		break;
		
		default: //invalid entry
		printf("Invalid Entry\n\n");
		break;
	}
}

int main(void)
{
	uint32_t pulseWidth;
	
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	PORTB_set_pin_dir(MOTOR, PORT_DIR_OUT); //configure PB1 as an output
	
	//Timer1 Config, Fast PWM, Prescaler = 8
	PRR &= 0xF7;
	TCCR1A = 0x82; //1000 0010
	ICR1 = 39999; //50Hz
	pulseWidth = PW_0_DEGREE + ((uint32_t)(PW_180_DEGREE - PW_0_DEGREE)*motorAngle/180);
	OCR1A = ((uint32_t)ICR1 + 1)*pulseWidth/PERIOD;
	TCCR1B = 0x1A; //0001 1010
	
	UCSR0B |= 0x80; //enable UART receive interrupt
	sei();
	
	
	while(1) {
		if(updateMotor == 1) {
			updateMotor = 0;
			pulseWidth = PW_0_DEGREE + ((uint32_t)(PW_180_DEGREE - PW_0_DEGREE)*motorAngle/180);
			OCR1A = ((uint32_t)ICR1 + 1)*pulseWidth/PERIOD;
			printf("Pulse Width: %luus, OCR1A: %d\n", pulseWidth, OCR1A);
		}

	}
}







