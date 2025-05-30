/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 6
10/03/2025
Real Time Clock

The Program from lab 5 has been altered to use the Timer 1 CTC interrupt as the time base for
the real time clock.
HOUR and MINUTE switches increase both values by 1 when pressed (falling edge).
User can manually change the time by entering it in, as long as time entered is within range.

Clock is no longer slow by 2.7seconds per minute, 162seconds per hour, 3888seconds per day.
This has been fixed due to an interrupt occurring every second, meaning the LCD is written to every second exactly.

-----------------------------------------------------------------------------------------------*/
#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "lcd_Start.h"

#define HOUR 2
#define MINUTE 3

//globally declared
uint8_t hr=0, min=0, sec=0;
char rtcTime[9] = "0";

ISR(INT0_vect) {
	hr++;
	if (hr > 23) {
		hr = 0;
	}
	
}

ISR(INT1_vect) {
	min++;
	if (min > 59) {
		min = 0;
	}
	
}

ISR(TIMER1_COMPA_vect) {
	sec++;   //increment time by 1 second
	
	if (sec > 59) {
		
		sec = 0;
		min++;
	}
	if (min > 59) {
		
		min = 0;
		hr++;
	}
	if (hr > 23) {
		
		hr = 0;
	}
	
	//display time
	sprintf(rtcTime, "%02d:%02d:%02d\n", hr, min, sec);
	lcd_clrscr();
	lcd_puts(rtcTime);
}




int main(void)
{
	uint8_t ch, i, hrT, minT, secT;
	char newTime[9] = "0";
	
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	EICRA = 0x0A; //falling edge
	EIMSK = 0x03; //enable INT0, INT1
	//Timer 1, CTC mode, 1-second periodic interrupt
	TCCR1A = 0x00; //0000 0000
	OCR1A = 15624;
	TCCR1B = 0x0D; //0000 1101
	TIMSK1 = 0x02; //0000 0010
	sei(); //global enabler
	
	lcd_init(LCD_DISP_ON_CURSOR);
	sprintf(rtcTime, "%02d:%02d:%02d\n", hr, min, sec);
	lcd_puts(rtcTime);
	
	
	/* Replace with your application code */
	while (1) {
		if (USART_0_is_rx_ready()) {
			ch = USART_0_read();
			if (ch == 't') {
				printf("Enter new time in format hh:mm:ss\n");
				for (i=0; i<8; i++) {
					newTime[i] = USART_0_read();
				}
				printf("String entered: %s\n\n", newTime);
				hrT = atoi(newTime);
				minT = atoi(&newTime[3]);
				secT = atoi(&newTime[6]);
				
				//error check 3 integers
				if (hrT <= 24 && minT <= 60 && secT <= 60) {
					hr = hrT; //update time variables if correct
					min = minT;
					sec = secT;
					
					
					} else {
					printf("Out of Range. Type 't' to enter a new time\n"); //error message if out of range
				}
			}
			else {
				printf("Invalid Entry, enter 't' to change time\n\n");
			}
		}
	}
}







