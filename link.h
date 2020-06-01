/*******************************************************************************
 * @File: link.h
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Including project modules
 *******************************************************************************/

#ifndef LINK_H
#define LINK_H

// Standart Peripheral Libraries
#include "1986VE9x.h"

// Project modules
#include "btn.h"
#include "snake.h"
#include "led.h"
#include "lcd.h"

extern const char *start_message;
extern const char *last_help_message;
extern const char *curr_help_message;
extern char score_str[22];

#endif
