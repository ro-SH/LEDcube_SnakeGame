/*******************************************************************************
 * @File: main.c
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Main module
 *******************************************************************************/

#include "main.h"

// Main function
int main(void)
{
	// Initializing control buttons ports
	BTN_Init();
	
	// Initializing LCD Screen
	LCD_Init();
	
	int last_score = -1;
	const char *start_message = "Press SEL to start";
	const char *help_message = "Last score:";
	char *score_message;
	
	// Main loop
	while (1)
	{
		// Clear LCD Screen
		LCD_ClearString(3);
		LCD_ClearString(5);
		
		// Fill LCD Screen with start message
		LCD_PutString(start_message, 3);
		
		// Fill LCD Screen with last score message
		if (last_score != -1)
		{
			snprintf(score_message, 22, "%s %d", help_message, last_score);
			LCD_PutString(score_message, 5);
		}
		
		// Check SEL button (PC2)
		if (MDR_PORTC->RXTX & (1 << 2) == 0)
		{
			// Clear LCD Screen
			LCD_ClearString(3);
			LCD_ClearString(5);
			
			// Start snake game
			last_score = play_snake();
			
			// Waiting till SEL button is unpressed (PC2)
			while (MDR_PORTC->RXTX & (1 << 2) == 0);
		}
	}
}
