/**********************************************************************************
Daragh Kearney
21/10/2024

Keyless Lock Door Entry System using LCD Display

3-digit password to open lock using keypad.
Door opens for 2 seconds.
LED is on when door is closed, off when door is open.
LED flashes 3 times when an incorrect password is entered.

Admin Mode opens when Admin PIN is entered.
User PIN can be changed in Admin.
Admin Mode is exited if incorrect User PIN is enetered.

The system locks out when 3 or more successive incorrect passwords are entered.
*********************************************************************************/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define LED 5

int main(void)
{
	uint8_t keyPosition, x, passwordCount = 0, lockCount = 0, adminCount = 0;
	uint8_t keypad[] = "123456789*0#";
	uint8_t password[] = "123", userInput[3], adminPIN[] = "000";
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Place GPIO and peripheral initialisation code here */
	lcd_init(LCD_DISP_ON_CURSOR); //Initialize LCD
	keypadConfigure();
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	
	/* Replace with your application code */
	while (1) {
		//Read user input
		PORTB_set_pin_level(LED, 1);
		lcd_clrscr(); //Clear screen before new message is displayed
		lcd_puts("Door Closed\n Enter PIN "); //Print message to LCD Display
		passwordCount = 0;
		adminCount = 0;
		for(x=0; x<3; x++) {
			keyPosition = keypadScan();
			//lcd_clrscr();
			lcd_puts("*");
			userInput[x] = keypad[keyPosition];
			if(userInput[x] == password[x]) {
				passwordCount++;
			}
			if (userInput[x] == adminPIN[x])
			{
				adminCount++;
			}
		}
		
		//check user entry vs password
		if(passwordCount == 3) {	//correct password
			lcd_clrscr();//Clear screen before new message is displayed
			lcd_puts("Door Open\n");
			PORTB_set_pin_level(LED, 0);
			_delay_ms(2000);
			lockCount = 0;
		}
		else if (adminCount == 3)
		{
			lcd_clrscr(); 
			lcd_puts("Admin Mode\nEnter User PIN"); //ask user to enter existing pin
			passwordCount = 0;
			for(x=0; x<3; x++) {
				keyPosition = keypadScan();
				
				lcd_puts("*");
				userInput[x] = keypad[keyPosition];
				if(userInput[x] == password[x]) {
					passwordCount++;
				}
			}
			if(passwordCount == 3) {
				lcd_clrscr();
				lcd_puts("Enter NEW PIN\n"); //if correct ask to enter new pin
				for(x=0; x<3; x++) {
					keyPosition = keypadScan();
					
					lcd_puts("*");
					password[x] = keypad[keyPosition];
				}
			}
			else {
				lcd_clrscr();
				lcd_puts("Incorrect PIN\nExiting Admin"); //if incorrect then exits admin mode
				_delay_ms(2000);
			}
		}
		else {	//incorrect password
			lcd_clrscr();//Clear screen before new message is displayed
			lcd_puts("Incorrect PIN\n");
			for(x=0; x<6; x++) {
				PORTB_toggle_pin_level(LED);
				_delay_ms(500);
			}
			//System lockout for 3 or more successive incorrect passwords
			lockCount++;
			if(lockCount >= 3) {
				for(x=30; x>0; x--) {
					char countString[33];
					lcd_clrscr();//Clear screen before new message is displayed
					sprintf(countString, "System Lockout\n%d seconds\n", x);
					lcd_puts(countString);
					_delay_ms(1000);
				}				
			}
		}
	}
}