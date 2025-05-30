/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 2
27/01/2025
Keyless Lock Door Entry System

User enters a 3-digit PIN on keypad to open door.
LCD displays user feedback.
LED is on when door is closed.
LED goes off for 2 seconds when door is opened.
LED flashes 3 times when incorrect PIN is entered.
The system is locked out for 30 seconds when 3 or more incorrect PINs in a row are entered.

The code is implemented as a finite state machine. 
The state machine has 5 states: CLOSED, OPEN, INCORRECT, LOCKOUT, ADMIN.
The user must enter an administration password to enter the administration state. The user is then asked to enter the old user password before being asked to enter the new password.
-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define LED 5

int main(void)
{
	enum STATES {CLOSED, OPEN, INCORRECT, LOCKOUT, ADMIN};
	enum STATES currentState = CLOSED;
	uint8_t keypad[] = "123456789*0#", password[] = "123", userEntry[3], adminPIN[] = "000";
	uint8_t x, count = 0, lockCount = 0, keyPosition, adminCount = 0, passwordCount = 0;
	char lockString[32];
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	PORTB_set_pin_level(LED, 0);
	keypadConfigure();
	lcd_init(LCD_DISP_ON_CURSOR);

	while (1) {
		switch(currentState) {
			case CLOSED:
			
			PORTB_set_pin_level(LED, 1);
			lcd_clrscr();
			lcd_puts("Door Closed\nEnter PIN ");
			//Read keypad entry
			count = 0;
			adminCount = 0;
			for (x = 0; x<3; x++) {
				keyPosition = keypadScan();
				userEntry[x] = keypad[keyPosition];
				lcd_putc('*');
				if(userEntry[x] == password[x]) {
					count++;
				}
				if (userEntry[x] == adminPIN[x])
				{
					adminCount++;
				}
				
			}
			
			//Verify user entry //State Transition
			if(count == 3) {	//Correct PIN
				currentState = OPEN;
			}
			else if (adminCount == 3)
			{
				currentState = ADMIN;
			}
			else {	//Incorrect PIN
				currentState = INCORRECT;
				
				}
			break;
			
			case OPEN:
			PORTB_set_pin_level(LED, 0);
			lcd_clrscr();
			lcd_puts("Door Open");
			_delay_ms(2000);
			lockCount = 0;
			currentState = CLOSED; //return to beginning
			
			break;
			
			case INCORRECT:
			lcd_clrscr();
			lcd_puts("Incorrect PIN");
			for(x=0; x<6; x++) {
				PORTB_toggle_pin_level(LED);
				_delay_ms(300);
			}
			if(++lockCount >= 3) {	//3 or more incorrect PINs in a row
				currentState = LOCKOUT;
			}
			else {
				currentState = CLOSED;
			}
			break;
			
			case LOCKOUT:
			for(x=30; x>0; x--) {
				lcd_clrscr();
				sprintf(lockString, "Lockout Time\n%02d seconds", x);
				lcd_puts(lockString);
				_delay_ms(1000);
			}
			currentState = CLOSED;
			break;
			
			case ADMIN:
				lcd_clrscr();
				lcd_puts("Admin Mode\nEnter User PIN"); //ask user to enter existing pin
				passwordCount = 0;
				for(x=0; x<3; x++) {
					keyPosition = keypadScan();
					
					lcd_puts("*");
					userEntry[x] = keypad[keyPosition];
					if(userEntry[x] == password[x]) {
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
					
				currentState = CLOSED;
				break;
	
			default:
			currentState = CLOSED;
			break;
		}
		
		}
		
	}
