/*******************************************************************************
 * @File: snake.c
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Snake game
 *******************************************************************************/

#include "snake.h"

// Function to generate new position for food.
// Position is random on the board but not engaged with the snake
void generate_food(Snake *snake, Food *food)
{
	bool success = false;			// Indicates whether food coordinates and snake coordinates matches
	while (success == false) 
	{
		food->pos.x = rand() % BOARD_SIZE;
		food->pos.y = rand() % BOARD_SIZE;
		food->pos.z = rand() % BOARD_SIZE;
		
		success = true;
		for (int i = 0; i < snake->length; ++i)
		{
			if (snake->pos[i].x == food->pos.x && snake->pos[i].y == food->pos.y && snake->pos[i].z == food->pos.z)
			{
				success = false;
				break;
			}
		}
	}

}


// Fuction to initialize snake with start position, start length, start direction
void init_snake(Snake *snake)
{
	snake->pos[0].x = rand() % BOARD_SIZE;
	snake->pos[0].y = rand() % BOARD_SIZE;
	snake->pos[0].z = rand() % BOARD_SIZE;
	snake->head = &snake->pos[0];
	snake->length = 1;
	snake->dir = WEST;
}

// Function to change snake direction based on the pressed button/
// If snake is on horizontal surface then
// pressing UP makes snake go up, pressing DOWN makes snake go down,
// pressing LEFT makes snake turn counterclock-wise, pressing RIGHT - clock-wise.
// If snake is on vertical surface then
// pressing UP makes snake go along reverse X axis, pressing DOWN makes snake go along X axis.
// If snake goes along Z axis (UP) then
// pressing LEFT makes snake go along Y axis, pressing RIGHT makes snake go along reverse Y axis.
// If snake goes along reverse Z axis (DOWN) then
// pressing LEFT makes snake go along reverse Y axis, pressing RIGHT makes snake go along Y axis.
void set_direction(Snake *snake, button btn)
{
	switch (btn)
	{
		// UP button pressed
		case UP_BUTTON:
			switch (snake->dir)
			{
			case NORTH:
			case SOUTH:
			case WEST:
			case EAST:
				snake->dir = UP;
				break;
			case DOWN:
			case UP:
				snake->dir = WEST;
				break;
			}
			break;
			
		// DOWN button pressed
		case DOWN_BUTTON:
			switch (snake->dir) 
			{
			case NORTH:
			case SOUTH:
			case WEST:
			case EAST:
				snake->dir = DOWN;
				break;
			case UP:
			case DOWN:
				snake->dir = EAST;
			}
			break;
			
		// LEFT button pressed
		case LEFT_BUTTON:
			switch (snake->dir) 
			{
			case NORTH:
				snake->dir = EAST;
				break;
			case EAST:
			case DOWN:
				snake->dir = SOUTH;
				break;
			case SOUTH:
				snake->dir = WEST;
				break;
			case WEST:
			case UP:
				snake->dir = NORTH;
				break;
			}
			break;
			
		// RIGHT button pressed
		case RIGHT_BUTTON:
			switch (snake->dir) 
			{
			case NORTH:
				snake->dir = WEST;
				break;
			case EAST:
			case DOWN:
				snake->dir = NORTH;
				break;
			case SOUTH:
				snake->dir = EAST;
				break;
			case WEST:
			case UP:
				snake->dir = SOUTH;
				break;
			}
	}
}

// Function to move snake.
// Eating food, wall hit and self hit are alse handled here.
bool move_snake(Snake *snake, Food *food, int *score) 
{
	// Move snake according to its direction
	Position next_pos = {0, 0, 0};
	switch (snake->dir)
	{
		case UP:
			next_pos.z = 1;
			break;
		case DOWN:
			next_pos.z = -1;
			break;
		case NORTH:
			next_pos.y = 1;
			break;
		case SOUTH:
			next_pos.y = -1;
			break;
		case EAST:
			next_pos.x = 1;
			break;
		case WEST:
			next_pos.x = -1;
	}
	
	Position last_pos = snake->pos[snake->length - 1];
	for (int i = snake->length - 1; i > 0; --i)
		snake->pos[i] = snake->pos[i - 1];
	snake->head->x += next_pos.x;
	snake->head->y += next_pos.y;
	snake->head->z += next_pos.z;
	
	// Wall hit check
	if (snake->head->x < 0 || snake->head->x >= BOARD_SIZE || snake->head->y < 0 || \
		snake->head->y >= BOARD_SIZE || snake->head->z < 0 || snake->head->z >= BOARD_SIZE)

		return false;
	
	// Self hit check
	for (int i = 1; i < snake->length; ++i) 
	{
		if (snake->head->x == snake->pos[i].x && snake->head->y == snake->pos[i].y && snake->head->z == snake->pos[i].z) 
			return false;
	}
	// Check if head coordinates match food coordiantes then increase and generate new food
	if (snake->head->x == food->pos.x && snake->head->y == food->pos.y && snake->head->z == food->pos.z)
	{
		// Increase snake length
		snake->pos[snake->length] = last_pos;
		snake->length += 1;
		
		// Initialize new food
		generate_food(snake, food);
		draw_food(food);
		
		// Update score
		*score += 1;
		
		// Clear LCD Screen
		LCD_ClearString(5);
		LCD_ClearString(6);
		
		// Fill LCD Screen with current score message
		sprintf(score_str, "               %d", *score);
		LCD_PutString(curr_help_message, 5);
		LCD_PutString(score_str, 6);
	}
	else
	{
		switch_off(last_pos.x, last_pos.y, last_pos.z);
		switch_on(snake->head->x, snake->head->y, last_pos.z);
	}
	return true;
}

// Function to light snake position light-emitting diods
void draw_snake(Snake *snake)
{
	for (int i = 0; i < snake->length; ++i)
	{
		switch_on(snake->pos[i].x, snake->pos[i].y, snake->pos[i].z);
	}
}

// Function to light food position light-emitting diods
void draw_food(Food *food)
{
	switch_on(food->pos.x, food->pos.y, food->pos.z);
}

void check_buttons(Snake *snake)
{
	// Check DOWN button press
	if ((MDR_PORTE->RXTX & (1 << 1)) == 0)
	{
		set_direction(snake, DOWN_BUTTON);

		while ((MDR_PORTE->RXTX & (1 << 1)) == 0);
	}
	// Check UP button press
	else if ((MDR_PORTB->RXTX & (1 << 5)) == 0)
	{
		set_direction(snake, UP_BUTTON);

		while ((MDR_PORTB->RXTX & (1 << 5)) == 0);
	}
	// Check RIGHT button press
	else if ((MDR_PORTB->RXTX & (1 << 6)) == 0)
	{
		set_direction(snake, RIGHT_BUTTON);

		while ((MDR_PORTB->RXTX & (1 << 6)) == 0);
	}
	// Check LEFT button press
	else if ((MDR_PORTE->RXTX & (1 << 3)) == 0)
	{
		set_direction(snake, LEFT_BUTTON);

		while ((MDR_PORTE->RXTX & (1 << 3)) == 0);
	}
}

// Function to start new snake game
int play_snake() 
{
	// clear cube
	all_off();
	
	// Initializing snake
	Snake snake;
	init_snake(&snake);
	
	// Initializing food
	Food food;
	generate_food(&snake, &food);
	
	draw_snake(&snake);
	draw_food(&food);

	int curr_score = 1;
	
	// Fill LCD Screen with current score message
	sprintf(score_str, "               %d", curr_score);
	LCD_PutString(curr_help_message, 5);
	LCD_PutString(score_str, 6);
	
	// Main game loop
	while (is_playing == true) 
	{	
		// Check buttons pressing
		delay();	
		check_buttons(&snake);
		delay();
		check_buttons(&snake);
		delay();
		check_buttons(&snake);
		
		// Move the snake according to its direction
		is_playing = move_snake(&snake, &food, &curr_score);
		
		if (is_playing == false)
		{
			// Clear cube
			all_off();
			
			return curr_score;
		}
	}
	
	return -1;			// Never happens
}

void delay() {
	    for(uint32_t i = 500000; i!=0; i--){
			__NOP;//пустая команда, чтобы компилятор не соптимизировал цикл
		}
}

bool is_playing = false;
