/*******************************************************************************
 * @File: btn.c
 * @Author: Roman Shadko
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: Initializing control buttons ports
 *******************************************************************************/

#include "btn.h"

void BTN_Init(void)
{
	MDR_RST_CLK->PER_CLOCK |= (1 << RST_CLK_PCLK_PORTB_Pos)		// Port B
							| (1 << RST_CLK_PCLK_PORTC_Pos)		// Port C
							| (1 << RST_CLK_PCLK_PORTE_Pos);	// Port E
	
	// PB5 Configuration (UP Button)
	MDR_PORTB->OE     &= ~(1 << 5);
	MDR_PORTB->FUNC   &= ~(3 << 10);
	MDR_PORTB->ANALOG |=  (1 << 5);
	MDR_PORTB->PULL   &= ~(1 << 5);
	MDR_PORTB->PULL   &= ~(1 << 21);
	MDR_PORTB->PD     &= ~(1 << 5);
	MDR_PORTB->PD     &= ~(1 << 21);
	MDR_PORTB->PWR    &= ~(3 << 10);
	MDR_PORTB->PWR    |=  (1 << 10);
	MDR_PORTB->GFEN   &= ~(1 << 5);
	
	// PB6 Configuration (RIGHT Button)
	MDR_PORTB->OE     &= ~(1 << 6);
	MDR_PORTB->FUNC   &= ~(3 << 12);
	MDR_PORTB->ANALOG |=  (1 << 6);
	MDR_PORTB->PULL   &= ~(1 << 6);
	MDR_PORTB->PULL   &= ~(1 << 22);
	MDR_PORTB->PD     &= ~(1 << 6);
	MDR_PORTB->PD     &= ~(1 << 22);
	MDR_PORTB->PWR    &= ~(3 << 12);
	MDR_PORTB->PWR    |=  (1 << 12);
	MDR_PORTB->GFEN   &= ~(1 << 6);

	// PE1 Configuration (DOWN Button)
	MDR_PORTE->OE     &= ~(1 << 1);
	MDR_PORTE->FUNC   &= ~(3 << 2);
	MDR_PORTE->ANALOG |=  (1 << 1);
	MDR_PORTE->PULL   &= ~(1 << 1);
	MDR_PORTE->PULL   &= ~(1 << 17);
	MDR_PORTE->PD     &= ~(1 << 1);
	MDR_PORTE->PD     &= ~(1 << 17);
	MDR_PORTE->PWR    &= ~(3 << 2);
	MDR_PORTE->PWR    |=  (1 << 2);
	MDR_PORTE->GFEN   &= ~(1 << 1);
	
	// PE3 Configuration (LEFT Button)
	MDR_PORTE->OE     &= ~(1 << 3);
	MDR_PORTE->FUNC   &= ~(3 << 6);
	MDR_PORTE->ANALOG |=  (1 << 3);
	MDR_PORTE->PULL   &= ~(1 << 3);
	MDR_PORTE->PULL   &= ~(1 << 19);
	MDR_PORTE->PD     &= ~(1 << 3);
	MDR_PORTE->PD     &= ~(1 << 19);
	MDR_PORTE->PWR    &= ~(3 << 6);
	MDR_PORTE->PWR    |=  (1 << 6);
	MDR_PORTE->GFEN   &= ~(1 << 3);
	
	// PC2 Configuration (SEL Button)
	MDR_PORTC->OE     &= ~(1 << 2);
	MDR_PORTC->FUNC   &= ~(3 << 4);
	MDR_PORTC->ANALOG |=  (1 << 2);
	MDR_PORTC->PULL   &= ~(1 << 2);
	MDR_PORTC->PULL   &= ~(1 << 18);
	MDR_PORTC->PD     &= ~(1 << 2);
	MDR_PORTC->PD     &= ~(1 << 18);
	MDR_PORTC->PWR    &= ~(3 << 4);
	MDR_PORTC->PWR    |=  (1 << 4);
	MDR_PORTC->GFEN   &= ~(1 << 2);
}

// Поток опроса кнопки DOWN
void Thread_DownButtonCheck(void *argument)
{
	// Цикл проверки
	while (1)
	{
		// Проверка нажатия
		if ((MDR_PORTE->RXTX & (1 << 1)) == 0 && is_playing)
		{
			// Задержка для защиты от дребезга контактов
			osDelay(10);

			// Подтверждение нажатия
			if ((MDR_PORTE->RXTX & (1 << 1)) == 0 && is_playing)
			{
				set_direction(&snake, DOWN_BUTTON);

				// Ожидание отпускания
				while ((MDR_PORTE->RXTX & (1 << 1)) == 0)
					osDelay(25);
			}
		}

		// Задержка перед началом следующей проверки
		osDelay(25);
	}
}

// Поток опроса кнопки UP
void Thread_UpButtonCheck(void *argument)
{
	// Цикл проверки
	while (1)
	{
		// Проверка нажатия
		if ((MDR_PORTB->RXTX & (1 << 5)) == 0 && is_playing)
		{
			// Задержка для защиты от дребезга контактов
			osDelay(10);

			// Подтверждение нажатия
			if ((MDR_PORTB->RXTX & (1 << 5)) == 0 && is_playing)
			{
				set_direction(&snake, UP_BUTTON);

				// Ожидание отпускания
				while ((MDR_PORTB->RXTX & (1 << 5)) == 0)
					osDelay(25);
			}
		}

		// Задержка перед началом следующей проверки
		osDelay(25);
	}
}

// Поток опроса кнопки SEL
void Thread_SelectButtonCheck(void *argument)
{
	// Цикл проверки
	while (1)
	{
		// Проверка нажатия
		if ((MDR_PORTC->RXTX & (1 << 2)) == 0 && !is_playing)
		{
			// Задержка для защиты от дребезга контактов
			osDelay(10);

			// Подтверждение нажатия
			if ((MDR_PORTC->RXTX & (1 << 2)) == 0 && !is_playing)
			{
				is_playing = true;
				// Clear LCD Screen
				LCD_ClearString(3);
				LCD_ClearString(5);

				// Start snake game
				last_score = play_snake();

				// Ожидание отпускания
				while ((MDR_PORTC->RXTX & (1 << 2)) == 0)
					osDelay(25);
			}

			// Задержка перед началом следующей проверки
			osDelay(25);
		}
	}
}

// Поток опроса кнопки LEFT
void Thread_LeftButtonCheck(void *argument)
{
	// Цикл проверки
	while (1)
	{
		// Проверка нажатия
		if ((MDR_PORTE->RXTX & (1 << 3)) == 0 && is_playing)
		{
			// Задержка для защиты от дребезга контактов
			osDelay(10);

			// Подтверждение нажатия
			if ((MDR_PORTE->RXTX & (1 << 3)) == 0 && is_playing)
			{
				set_direction(&snake, UP_BUTTON);

				// Ожидание отпускания
				while ((MDR_PORTE->RXTX & (1 << 3)) == 0)
					osDelay(25);
			}
		}

		// Задержка перед началом следующей проверки
		osDelay(25);
	}
}

// Поток опроса кнопки RIGHT
void Thread_RightButtonCheck(void *argument)
{
	// Цикл проверки
	while (1)
	{
		// Проверка нажатия
		if ((MDR_PORTB->RXTX & (1 << 6)) == 0 && is_playing)
		{
			// Задержка для защиты от дребезга контактов
			osDelay(10);

			// Подтверждение нажатия
			if ((MDR_PORTB->RXTX & (1 << 6)) == 0 && is_playing)
			{
				set_direction(&snake, RIGHT_BUTTON);

				// Ожидание отпускания
				while ((MDR_PORTB->RXTX & (1 << 6)) == 0)
					osDelay(25);
			}
		}

		// Задержка перед началом следующей проверки
		osDelay(25);
	}
}
