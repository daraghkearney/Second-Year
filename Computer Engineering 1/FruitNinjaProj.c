/**********************************************************************************
Daragh Kearney
05/12/2024

This is a Fruit Ninja inspired Reaction Game with LCD, LEDs, Switch, and a Buzzer.
This program measures the user's reaction time to random LED activation.
All LED colors represent a fruit and the user must slice the fruit before the time runs out.
The Red LED is a bomb, if this is sliced then the game is over.

Features:
- Serial communication for feedback.
- LCD display for user instructions and reaction time.
- LED for visual cue.
- Switch for input.
- Buzzer for auditory feedback.
*********************************************************************************/

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "lcd_Start.h"


#define YELLOW_LED_PIN 5
#define GREEN_LED_PIN 4
#define RED_LED_PIN 3
#define BLUE_LED_PIN 2
#define SWITCH_PIN 7
#define BUZZER_PIN 6

// LED Colors (fruits)
#define YELLOW 0
#define GREEN 1
#define RED 2
#define BLUE 3

// Timing Definitions
#define LED_ON_TIME 1000       // 1 second for non-red LEDs
#define RED_LED_TIMEOUT 1500   // 1.5 seconds timeout for red LED

// Function for dynamic delays
void dynamic_delay_ms(uint32_t ms) {
	for (uint32_t i = 0; i < ms; i++) {
		_delay_ms(1); // 1ms delay in a loop
	}
}

// Function to turn off all LEDs
void turn_off_all_leds(void) {
	PORTB_set_pin_level(YELLOW_LED_PIN, 0);
	PORTB_set_pin_level(GREEN_LED_PIN, 0);
	PORTB_set_pin_level(RED_LED_PIN, 0);
	PORTB_set_pin_level(BLUE_LED_PIN, 0);
}

// Function to light up a specific LED
void light_led(uint8_t led_color) {
	turn_off_all_leds();
	switch (led_color) {
		case YELLOW:
		PORTB_set_pin_level(YELLOW_LED_PIN, 1);
		break;
		case GREEN:
		PORTB_set_pin_level(GREEN_LED_PIN, 1);
		break;
		case RED:
		PORTB_set_pin_level(RED_LED_PIN, 1);
		break;
		case BLUE:
		PORTB_set_pin_level(BLUE_LED_PIN, 1);
		break;
	}
	 
}

int main(void) {
	uint32_t reaction_time;
	uint8_t led_color;

	// Initialization
	atmel_start_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();

	// Configure I/O
	PORTB_set_pin_dir(YELLOW_LED_PIN, PORT_DIR_OUT);
	PORTB_set_pin_dir(GREEN_LED_PIN, PORT_DIR_OUT);
	PORTB_set_pin_dir(RED_LED_PIN, PORT_DIR_OUT);
	PORTB_set_pin_dir(BLUE_LED_PIN, PORT_DIR_OUT);
	PORTB_set_pin_dir(BUZZER_PIN, PORT_DIR_OUT);
	PORTB_set_pin_dir(SWITCH_PIN, PORT_DIR_IN);
	PORTB_set_pin_pull_mode(SWITCH_PIN, PORT_PULL_UP);

	while (1) {
		// Display start message
		lcd_clrscr();
		lcd_puts("Press Switch to\nStart Game");
		printf("Waiting for user to slice fruit...\n");

		// Wait for switch press and release
		while (PORTB_get_pin_level(SWITCH_PIN) == 1);
		while (PORTB_get_pin_level(SWITCH_PIN) == 0);

		// "Get Ready" message and delay
		lcd_clrscr();
		lcd_puts("Get Ready!");
		dynamic_delay_ms(1000 + (rand() % 2000)); // Random delay between 1-3 seconds

		// random LED color
		led_color = rand() % 4;

		if (led_color == RED) {
			lcd_clrscr();
			lcd_puts("BOMB!"); 
			light_led(RED); // Light up red LED

			uint32_t red_reaction_time = 0;

			// Wait for switch press or timeout
			while (PORTB_get_pin_level(SWITCH_PIN) == 1 && red_reaction_time < RED_LED_TIMEOUT) {
				dynamic_delay_ms(1);
				red_reaction_time++;
			}

			turn_off_all_leds(); // Turn off LEDs and buzzer

			if (red_reaction_time < RED_LED_TIMEOUT) {
				// User pressed the switch on red LED (bomb) => Game Over
				lcd_clrscr();
				lcd_puts("Game Over!");
				printf("Game Over\n");
				PORTB_set_pin_level(BUZZER_PIN, 1);
				dynamic_delay_ms(2000);
				PORTB_set_pin_level(BUZZER_PIN, 0);
				continue;
				} else {
				// Red LED timed out successfully => Continue
				lcd_clrscr();
				lcd_puts("Safe! Continue...");
				dynamic_delay_ms(1500);
				PORTB_set_pin_level(BUZZER_PIN, 0);
				continue;
			}
		}

		// Handle non-red LEDs
		light_led(led_color); // Light up the chosen LED
		reaction_time = 0;
		lcd_clrscr();
		lcd_puts("Slice The Fruit!");

		// Wait for user to press the switch
		while (PORTB_get_pin_level(SWITCH_PIN) == 1) {
			dynamic_delay_ms(1);
			reaction_time++;
			if (reaction_time > LED_ON_TIME) {
				break; // Timeout if user doesn't press within the allowed time
			}
		}

		turn_off_all_leds(); // Turn off LEDs and buzzer

		if (reaction_time > LED_ON_TIME) {
			// User failed to press the switch in time
			lcd_clrscr();
			lcd_puts("Too Slow!");
			dynamic_delay_ms(2000);
			continue;
		}

		// Display reaction time
		char message[16];
		sprintf(message, "Time: %lums", reaction_time);
		lcd_clrscr();
		lcd_puts(message);
		printf("Reaction Time: %lums\n", reaction_time);
		dynamic_delay_ms(2000);

		// Wait for switch release before restarting
		while (PORTB_get_pin_level(SWITCH_PIN) == 0);
	}
}

