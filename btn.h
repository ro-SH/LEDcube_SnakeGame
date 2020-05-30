/*******************************************************************************
 * @File: btn.h
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Initializing control buttons ports
 *******************************************************************************/

#ifndef BTN_H
#define BTN_H

#include "link.h"

void BTN_Init(void);							// Button ports initialization
void Thread_DownButtonCheck(void *argument);    // DOWN
void Thread_UpButtonCheck(void *argument);      // UP
void Thread_SelectButtonCheck(void *argument);  // SELECT
void Thread_LeftButtonCheck(void *argument);    // LEFT
void Thread_RightButtonCheck(void *argument);   // RIGHT

#endif
