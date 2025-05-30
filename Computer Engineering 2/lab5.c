/*----------------------------------------------------------------------------------------------
Daragh Kearney
Semester 2
Lab 5
03/03/2025
Real Time Clock

Program to implement a Real Time Clock (RTC). The RTC uses a
_delay_ms() function call to display the time every second on an LCD.
HOUR and MINUTE switches increase both values by 1 when pressed (falling edge).

Clock is slow by 2.7seconds per minute, 162seconds per hour, 3888seconds per day.
This has been fixed by reducing delay from 1000ms (1 second) to 995ms.

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
		sec = 0;   //reset time to 0
		min = 0;
		hr = 0;
	}
	lcd_clrscr();
	sprintf(rtcTime, "%02d:%02d:%02d\n", hr, min, sec);
	lcd_puts(rtcTime);
}

ISR(INT1_vect) {
	min++;
	if (min > 59) {
		hr++;   //increment time by 1 hour
		min = 0;
	}
	lcd_clrscr();
	sprintf(rtcTime, "%02d:%02d:%02d\n", hr, min, sec);
	lcd_puts(rtcTime);
}




int main(void)
{
	
	/* Initializes MCU, DRivers and middleware */
	atmel_start_init();
	
	/* Replace GPIO and peripheral initialization code here */
	EICRA = 0x0A;
	EIMSK = 0x03;
	sei();
	
	lcd_init(LCD_DISP_ON_CURSOR);
	sprintf(rtcTime, "%02d:%02d:%02d\n", hr, min, sec);
	lcd_puts(rtcTime);
	
	
	/* Replace with your application code */
	while (1) {
		//delay 1 second
		_delay_ms(955);
		sec++;   //increment time by 1 second
		
		if (sec > 59) {
			min++;   //increment time by 1 minute
			sec = 0;
		}
		if (min > 59) {
			hr++;   //increment time by 1 hour
			min = 0;
		}
		if (hr > 23) {
			sec = 0;   //reset time to 0
			min = 0;
			hr = 0;
		}
		//display time
		lcd_clrscr();
		sprintf(rtcTime, "%02d:%02d:%02d\n", hr, min, sec);
		lcd_puts(rtcTime);
		
		
		
	}
	
}