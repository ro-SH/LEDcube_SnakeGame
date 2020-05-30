/*******************************************************************************
 * @File: main.c
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Main module
 *******************************************************************************/

#include "main.h"

int last_score = -1;
int curr_score = -1;
const char *start_message = "Press SEL to start";
const char *last_help_message = "Last score:";
const char *curr_help_message = "Current score:";
char *score_message;

// Main function
int main(void)
{
	// Inititalizing led ports
	ports_init();
	
	// Initializing control buttons ports
	BTN_Init();
	
	// Initializing LCD Screen
	LCD_Init();
	
	// Fill LCD Screen with start message
    LCD_PutString(start_message, 3);

    // Fill LCD Screen with last score message
    if (last_score != -1)
    {
    	snprintf(score_message, 22, "%s %d", last_help_message, last_score);
		LCD_PutString(score_message, 5);
    }
	
	// Initializing OCPB
	RTOS_Init();
}
