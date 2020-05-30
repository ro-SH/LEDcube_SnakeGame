/*******************************************************************************
 * @File: rtos.c
 * @Author: Milandr, L.
 * @Project: Sample 2.3
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 11.05.2017
 * @Purpose: Управление операционной системой реального времени
 *******************************************************************************/

// Подключение заголовочного файла
#include "rtos.h"

// Инициализация операционной системы реального времени
void RTOS_Init(void)
{
	// Инициализация ядра ОСРВ
	osKernelInitialize();

	// Создание потока проверки нажатия кнопки DOWN
	osThreadNew(Thread_DownButtonCheck, NULL, &(osThreadAttr_t){.priority = osPriorityNormal, .stack_size = 136});

	// Создание потока проверки нажатия кнопки UP
	osThreadNew(Thread_UpButtonCheck, NULL, &(osThreadAttr_t){.priority = osPriorityNormal, .stack_size = 136});

	// Создание потока проверки нажатия кнопки SELECT
	osThreadNew(Thread_SelectButtonCheck, NULL, &(osThreadAttr_t){.priority = osPriorityNormal, .stack_size = 136});

	// Создание потока проверки нажатия кнопки LEFT
	osThreadNew(Thread_LeftButtonCheck, NULL, &(osThreadAttr_t){.priority = osPriorityNormal, .stack_size = 136});

	// Создание потока проверки нажатия кнопки RIGHT
	osThreadNew(Thread_RightButtonCheck, NULL, &(osThreadAttr_t){.priority = osPriorityNormal, .stack_size = 136});

	// Запуск ядра ОСРВ
	osKernelStart();
}
