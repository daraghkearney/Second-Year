/**********************************************************************************
Daragh Kearney
Semester 2
Lab 1
20/01/2025

This is a state machine program to control an LED using a keypad.
LED switches between states OFF, Flashing at 1Hz, and Flashing at 2Hz depending on what number is pressed on the keypad.
0 turns the LED off, 1 flashes the LED at 1Hz, 2 flashes the LED at 2Hz.
LCD displays current state of program with instructions on how to switch between them.


*********************************************************************************/

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define LED 5

int main(void)
{
	uint8_t key, keypad[] = "123456789*0#";
	enum STATES {OFF, F1HZ, F2HZ};
	enum STATES currentState = OFF;
	bool updateLCD = 1;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();
	
	/* Place GPIO and peripheral initialisation code here */
	keypadConfigure();
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	/* Replace with your application code */
	while (1) {
		switch(currentState)
		{
			case OFF:
			PORTB_set_pin_level(LED, 0); //state action 
			
			if (updateLCD == 1) {
				lcd_clrscr(); // clears lcd screen before new messsage is displayed
				lcd_puts("LED OFF\nSelect 1 or 2");
				updateLCD = 0;
			}
			
			//state transition
			if(keyPressed()) {
				key = keypad[keypadScan()];
				if(key == '1') {
					currentState = F1HZ;
					updateLCD = 1; //lcd state must be updated when LED state is changed
				}
				else if(key == '2') {
					currentState = F2HZ;
					updateLCD = 1;
				}
			}
			break;
			
			case F1HZ:
			PORTB_toggle_pin_level(LED); // toggles LED off and on 
			_delay_ms(500); //sets the delay for LED flash
			
			if (updateLCD == 1) {
				lcd_clrscr();
				lcd_puts("LED 1Hz\nSelect 0 or 2");
				updateLCD = 0;
			}
			
			//state transition
			if(keyPressed()) {
				key = keypad[keypadScan()];
				if(key == '0') {
					currentState = OFF;
					updateLCD = 1;
				}
				else if(key == '2') {
					currentState = F2HZ;
					updateLCD = 1;
				}
			}
			break;
			
			case F2HZ:
			PORTB_toggle_pin_level(LED);
			_delay_ms(500); //state action
			
			if (updateLCD == 1) {
				lcd_clrscr();
				lcd_puts("LED 2Hz\nSelect 0 or 1");
				updateLCD = 0;
			}
			
			//state transition
			if(keyPressed()) {
				key = keypad[keypadScan()];
				if(key == '1') {
					currentState = F1HZ;
					updateLCD = 1;
				}
				else if(key == '0') {
					currentState = OFF;
					updateLCD = 1;
				}
			}
			break;
			
			default:
			currentState = OFF;
			break;
		}
	}
}
