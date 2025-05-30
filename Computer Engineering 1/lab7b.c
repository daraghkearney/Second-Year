/**********************************************************************************
Daragh Kearney
04/11/2024

DC Motor Controlled using XMINI board switch.
This program uses a Switch to allow the user to control the direction and speed of a motor.
*********************************************************************************/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define EN 1
#define IN1 2
#define IN2 3
#define SW 7


int main(void)
{
	uint8_t x=0, onTime = 0, ch;
	
	atmel_start_init();
	
	PORTB_set_pin_dir(EN, PORT_DIR_OUT);
	PORTB_set_pin_dir(IN1, PORT_DIR_OUT);
	PORTB_set_pin_dir(IN2, PORT_DIR_OUT);
	
	PORTB_set_pin_level(EN, 0);
	PORTB_set_pin_level(IN1, 0);
	PORTB_set_pin_level(IN2, 1);
	
	//Menu for user interface
	printf("DC Motor Control\n");
	printf("'s': Stop\n");
	printf("'f': Forward\n");
	printf("'r': Reverse\n");
	printf("'+': Increase Speed\n");
	printf("'-': Decrease Speed\n");
	
	while (1) {
		if(USART_0_is_rx_ready()){
			ch = USART_0_read();
			switch(ch) {
				case 's': 
				onTime = 0;
				break; //stop motor
				
				case 'f':
				onTime = 1;
				PORTB_set_pin_level(IN2, 1); //set forward pin
				PORTB_set_pin_level(IN1, 0);
				break;
				
				case 'r':
				onTime = 1;
				PORTB_set_pin_level(IN1, 1); //set reverse pin
				PORTB_set_pin_level(IN2, 0);
				break;
				
				case '+':
				onTime++;
				break; //increase motor speed
				
				case '-':
				onTime--;
				break; //decrease motor speed
				
				default:
				break;
				
			}
		}
		
		//Motor Speed Control
		for(x=0; x<onTime; x++) {
				PORTB_set_pin_level(EN, 1); //motor on
				_delay_ms(1);
				}
		for(x=onTime; x<10; x++) {
				PORTB_set_pin_level(EN, 0); //motor off
				_delay_ms(1);
				}
		
	}
}