/**********************************************************************************
Daragh Kearney
21/10/2024

Keyless Lock Door Entry System

3-digit password to open lock using keypad.
Door opens for 2 seconds.
LED is on when door is closed, off when door is open.
LED flashes 3 times when an incorrect password is entered.
The system locks out when 3 or more successine incorrect passwords are entered.
*********************************************************************************/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define LED 5

int main(void)
{
	uint8_t keyPosition, x, passwordCount = 0, lockCount = 0;
	uint8_t keypad[] = "123456789*0#";
	uint8_t password[] = "123", userInput[3];
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	lcd_init(LCD_DISP_ON_CURSOR);
	keypadConfigure();
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	/* Replace with your application code */
	while (1) {
		//Read user input
		PORTB_set_pin_level(LED, 1);
		lcd_puts("\nEnter 3-digit PIN to open door\n");
		passwordCount = 0;
		for(x=0; x<3; x++) {
			keyPosition = keypadScan();
			lcd_puts("*");
			userInput[x] = keypad[keyPosition];
			if(userInput[x] == password[x]) {
				passwordCount++;
			}
		}
		
		//check user entry vs password
		if(passwordCount == 3) {	//correct password
			lcd_puts("\nDoor Opening\n");
			PORTB_set_pin_level(LED, 0);
			_delay_ms(2000);
			lockCount = 0;
		}
		else {	//incorrect password
			lcd_puts("\nIncorrect PIN\n");
			for(x=0; x<6; x++) {
				PORTB_toggle_pin_level(LED);
				_delay_ms(500);
			}
			//System lockout for 3 or more successive incorrect passwords
			lockCount++;
			if(lockCount >= 3) {
				lcd_puts("*** Locking System Down ***\n");
				for(x=30; x>0; x--) {
					printf("System locked out for %d seconds\n", x);
					_delay_ms(1000);
				}				
			}
		}
	}
}