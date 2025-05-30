/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 7
24/03/2025
PWM control of LED and DC Motor

Program to control an LED and a DC motor using PWM signals on Timer1.
The LED brightness is adjusted using Bright/Dim switches. 
Brightness level increases/decreases depending on pressed switch and result is printed.

The DC motor speed is controlled by Fast and Slow switches.
PWM duty cycle of OC1B increases or decreases by 10% respective of pressed switch.

External interrupts (INT0, INT1) handle LED brightness control.
Pin Change Interrupts (PCINT) handle motor speed control.

The duty cycle of both the LED and motor is printed to the serial terminal.

-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define LED 1
#define MOTOR 2
#define IN1 3
#define IN2 4
#define FAST 5
#define SLOW 6


uint8_t brightnessLevel = 0;
uint8_t motorSpeedLevel = 0;

ISR(INT0_vect) { //Bright switch
	//increment level but limit to 10
	if (brightnessLevel < 10) {
		brightnessLevel++;
	}
	//print new level
	OCR1A = ((ICR1 + 1)/10) * brightnessLevel;
	printf("LED Brightness Level: %d\n", brightnessLevel);
}

ISR(INT1_vect) { //Dim switch
	if (brightnessLevel > 0) {
		brightnessLevel--;
	}
	OCR1A = ((ICR1 + 1)/10) * brightnessLevel;
	printf("LED Brightness Level: %d\n", brightnessLevel);
}

ISR(PCINT2_vect) {
	if (PORTD_get_pin_level(FAST) == 0) {  // Fast Button Pressed
		if (motorSpeedLevel < 10) {
			motorSpeedLevel++;
		}
		OCR1B = ((ICR1 + 1) / 10) * motorSpeedLevel;
		printf("Motor Speed Level: %d%%\n", motorSpeedLevel * 10);
	}
	else if (PORTD_get_pin_level(SLOW) == 0) {  // Slow Button Pressed
		if (motorSpeedLevel > 0) {
			motorSpeedLevel--;
		}
		OCR1B = ((ICR1 + 1) / 10) * motorSpeedLevel;
		printf("Motor Speed Level: %d%%\n", motorSpeedLevel * 10);
	}
}



int main(void)
{
	//uint16_t x;
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	PORTB_set_pin_dir(MOTOR, PORT_DIR_OUT);
	PORTB_set_pin_dir(IN1, PORT_DIR_OUT);
	PORTB_set_pin_dir(IN2, PORT_DIR_OUT);
	PORTB_set_pin_level(IN1, 1);
	PORTB_set_pin_level(IN2, 0);
	
	PRR &= 0xF7;   //enable timer 1
	TCCR1A = 0xA2; //1010 0010
	OCR1A = 0; //LED duty cycle
	OCR1B = 0; //Motor duty cycle
	ICR1 = 1999;
	TCCR1B = 0x1A; //0001 1010
	
	//Configure INT0, INT1 for falling edge interrupts
	EICRA = 0x0A; // Falling edge triggers
	EIMSK = 0x03; // Enable INT0 and INT1
	
	//
	
	sei();
	
	while(1) {
		/*for(x=0; x<=(ICR1+1); x+=(ICR1+1)/10) {
		OCR1A = x;
		_delay_ms(500);
		} */
	}
}







