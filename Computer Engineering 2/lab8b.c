/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 8
31/03/2025
Part B: Servo Motor Control via USART Receive Interrupt

This Program controls the position of a servo motor arm by sending a 3-digit
angle between 000 and 180 degrees to the USART. The USART receive interrupt is
used to receive the characters before configuring the Timer 1 OCR1A register to
change the motor arm position.

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
uint8_t x=0, buffer[4] = "0";
uint32_t pulseWidth;
uint8_t temp = 90;

ISR(USART_RX_vect) {
	
	buffer[x] = UDR0;
	x++;
	if(x == 3) {
		temp = atoi(buffer);
		//error check temp
		if (temp >= 0 && temp <= 180) {
			updateMotor = 1; //if ok, update motor position
			pulseWidth = PW_0_DEGREE + ((uint32_t)(PW_180_DEGREE - PW_0_DEGREE)*temp/180);
			OCR1A = ((uint32_t)ICR1 + 1)*pulseWidth/PERIOD;
			printf("Pulse Width: %luus, OCR1A: %d\n", pulseWidth, OCR1A);
		}
		
		//if invalid, error message
		else {
			printf("ERROR, Invalid Input\n\n");
		}
		x = 0;
	}
}

int main(void)
{
	
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	PORTB_set_pin_dir(MOTOR, PORT_DIR_OUT); //configure PB1 as an output
	
	//Timer1 Config, Fast PWM, Prescaler = 8
	PRR &= 0xF7;
	TCCR1A = 0x82; //1000 0010
	ICR1 = 39999; //50Hz
	pulseWidth = PW_0_DEGREE + ((uint32_t)(PW_180_DEGREE - PW_0_DEGREE)*temp/180);
	OCR1A = ((uint32_t)ICR1 + 1)*pulseWidth/PERIOD;
	TCCR1B = 0x1A; //0001 1010
	
	UCSR0B |= 0x80; //enable UART receive interrupt
	sei();
	
	
	while(1) {
	}
}







