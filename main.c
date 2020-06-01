/*******************************************************************************
 * @File: main.c
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Main module
 *******************************************************************************/

#include "main.h"

int last_score = -1;
const char *start_message = "  Press SEL to start";
const char *last_help_message = "    Last score:";
const char *curr_help_message = "      Score:";
char score_str[22];

// Main function
int main(void)
{
	// Inititalizing led ports
	ports_init();
	all_off();
	
	// Initializing control buttons ports
	BTN_Init();
	
	// Initializing LCD Screen
	LCD_Init();
	
	// Fill LCD Screen with start message
    LCD_PutString(start_message, 3);

	while (1)
	{	
		// Press SEL check
		if ((MDR_PORTC->RXTX & (1 << 2)) == 0 && is_playing == false)
		{
			is_playing = true;

			// Unpress waiting
			while ((MDR_PORTC->RXTX & (1 << 2)) == 0);
		}
		
		if (is_playing == true)
		{
			// Clear LCD Screen
			LCD_ClearString(3);
			LCD_ClearString(5);
			LCD_ClearString(6);

			// Start snake game
			last_score = play_snake();
			
			// Fill LCD Screen with start message
			LCD_PutString(start_message, 3);

			// Fill LCD Screen with last score message
			if (last_score != -1)
			{
				sprintf(score_str, "               %d", last_score);
				LCD_PutString(last_help_message, 5);
				LCD_PutString(score_str, 6);
			}
		}
	}
}
