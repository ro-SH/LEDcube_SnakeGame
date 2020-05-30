/*******************************************************************************
 * @File: snake.h
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Snake game
 *******************************************************************************/

#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include "link.h"
#define BOARD_SIZE 6

// Implementation of boolean type
typedef enum
{
	true, false
} bool;

typedef enum
{
	UP, DOWN, NORTH, EAST, SOUTH, WEST
} direction;

typedef enum
{
	UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON
} button;

typedef struct Position
{
	int x, y, z;
} Position;

typedef struct Food
{
	Position pos;
} Food;

typedef struct Snake 
{
	Position pos[BOARD_SIZE * BOARD_SIZE];
	Position *head;
	int length;
	direction dir;
} Snake;

void generate_food(Snake*, Food*);			// Generating new position for food
void init_snake(Snake*);					// Initializing snake with start position, start length, start direction
void set_direction(Snake*, button);			// Changing snake direction
bool move_snake(Snake*, Food*, int*);		// Moving snake
void draw_snake(Snake*);					// Light snake position light-emitting diods
void draw_food(Food*);						// Light food position light-emitting diod
int play_snake(void);						// Start new game

#endif
