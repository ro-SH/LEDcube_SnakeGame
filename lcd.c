 /*******************************************************************************
 * @File: lcd.c
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 22.03.2017
 * @Purpose: Библиотека для работы с дисплеем MT-12864J
 *******************************************************************************/

// Подключение заголовочного файла
#include "lcd.h"

// Конфигурация портов для работы с дисплеем
void LCD_PortCfg(void)
{
	// Конфигурация линий PA0...PA5 в качестве двунаправленной шины данных (DB0...DB5)
	MDR_PORTA->OE     &= 0xFFFFFFC0;
	MDR_PORTA->PULL   &= 0xFFC0FFC0;
	MDR_PORTA->ANALOG |= 0x0000003F;
	MDR_PORTA->FUNC   &= 0xFFFFF000;
	MDR_PORTA->PD     &= 0xFFC0FFC0;
	MDR_PORTA->PWR    |= 0x00000FFF;
	MDR_PORTA->GFEN   &= 0xFFFFFFC0;

	// Конфигурация линий PF2 и PF3 в качестве двунаправленной шины данных (DB6, DB7)
	MDR_PORTF->OE     &= 0xFFFFFFF3;
	MDR_PORTF->PULL   &= 0xFFF3FFF3;
	MDR_PORTF->ANALOG |= 0x0000000C;
	MDR_PORTF->FUNC   &= 0xFFFFFF0F;
	MDR_PORTF->PD     &= 0xFFF3FFF3;
	MDR_PORTF->PWR    |= 0x000000F0;
	MDR_PORTF->GFEN   &= 0xFFFFFFF3;

	// Конфигурация линий PB7...PB10 в качестве цифровых выходов (E1, E2, RES, R/W)
	MDR_PORTB->OE     |= 0x00000780;
	MDR_PORTB->PULL   &= 0xF87FF87F;
	MDR_PORTB->ANALOG |= 0x00000780;
	MDR_PORTB->FUNC   &= 0xFFC03FFF;
	MDR_PORTB->PD     &= 0xF87FF87F;
	MDR_PORTB->PWR    |= 0x003FC000;
	MDR_PORTB->GFEN   &= 0xFFFFF87F;

	// Конфигурация линий PC0 и PC1 в качестве цифровых выходов (A0, E)
	MDR_PORTC->OE     |= 0x00000003;
	MDR_PORTC->PULL   &= 0xFFFCFFFC;
	MDR_PORTC->ANALOG |= 0x00000003;
	MDR_PORTC->FUNC   &= 0xFFFFFFF0;
	MDR_PORTC->PD     &= 0xFFFCFFFC;
	MDR_PORTC->PWR    |= 0x0000000F;
	MDR_PORTC->GFEN   &= 0xFFFFFFFC;
}

// Инициализация жидкокристаллического дисплея
void LCD_Init(void)
{
	// Включение тактирования требуемых портов
	MDR_RST_CLK->PER_CLOCK |= 0x20E00000;

	// Конфигурация портов для работы с дисплеем
	LCD_PortCfg();

	// Инициализация драйвера дисплея
	// Сброс линии RES
	LCD_ClearBit_RES;
	LCD_DELAY(5);

	// Установка линии RES
	LCD_SetBit_RES;
	LCD_DELAY(1);

	// Ожидание завершения инициализации
	while ((LCD_ReadStatus(1) & 0x90) && (LCD_ReadStatus(2) & 0x90));

	// Ожидание завершения операций и включение кристалла 1
	while (LCD_ReadStatus(1) & 0x80);
	LCD_Enable(1);

	// Ожидание завершения операций и включение кристалла 2
	while (LCD_ReadStatus(2) & 0x80);
	LCD_Enable(2);

	// Очистка памяти дисплея
	LCD_ClearScreen();

	// Отображение заголовочного элемента
	LCD_PutImage(header, 0, 0, 21, 2);
}

// Выбор направления шины данных
void LCD_DataBusDirection(uint8_t direction)
{
	// Передача
	if (direction == OUT)
	{
		MDR_PORTA->OE |= 0x0000003F;
		MDR_PORTF->OE |= 0x0000000C;
	}

	// Прием
	else
	{
		MDR_PORTA->OE &= 0xFFFFFFC0;
		MDR_PORTF->OE &= 0xFFFFFFF3;
	}
}

// Передача информации на шину данных
void LCD_SetDataBits(uint8_t data)
{
	MDR_PORTA->RXTX &= 0xFFC0;
	MDR_PORTA->RXTX |= (data & 0x3F); 
	MDR_PORTF->RXTX &= 0xFFF3;
	MDR_PORTF->RXTX |= ((data >> 4) & 0x0C); 
}

// Возврат линий в исходное состояние
void LCD_Reset(uint8_t chip)
{
	// Сброс линии E
	LCD_ClearBit_E;
	LCD_DELAY(1);

	// Сброс линии A0
	LCD_ClearBit_A0;

	// Сброс линии R/W
	LCD_ClearBit_RW;

	// Восстановление конфигурации шины данных
	LCD_DataBusDirection(IN);

	// Отмена выбора кристалла (сброс линии E1 или E2)
	if (chip == 1)
		LCD_ClearBit_E1;
	else
		LCD_ClearBit_E2;
}

// Включение дисплея
void LCD_Enable(uint8_t chip)
{
	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// Сброс линии А0 (служебные сигналы)
	LCD_ClearBit_A0;

	// Сброс линии R/W (передача данных)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для передачи
	LCD_DataBusDirection(OUT);

	// Передача данных
	LCD_SetDataBits(0x3F);
	LCD_DELAY(1);

	// Стробирование сигнала
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);
}

// Выключение дисплея
void LCD_Disable(uint8_t chip)
{
	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// Сброс линии А0 (служебные сигналы)
	LCD_ClearBit_A0;

	// Сброс линии R/W (передача данных)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для передачи
	LCD_DataBusDirection(OUT);

	// Передача данных
	LCD_SetDataBits(0x3E);
	LCD_DELAY(1);

	// Стробирования сигнала
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);
}

// Получение статуса операции
uint8_t LCD_ReadStatus(uint8_t chip)
{
	uint8_t data;

	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// Сброс линии A0 (служебные сигналы)
	LCD_ClearBit_A0;

	// Установка линии R/W (прием данных)
	LCD_SetBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для приема
	LCD_DataBusDirection(IN);

	// Установка линии E
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Чтение данных
	data = (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);

	return data;
}

// Выбор страницы
void LCD_SetPage(uint8_t chip, uint8_t page)
{
	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// Сброс линии А0 (служебные сигналы)
	LCD_ClearBit_A0;

	// Сброс линии R/W (передача данных)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для передачи
	LCD_DataBusDirection(OUT);

	// Передача данных
	LCD_SetDataBits(0xB8 | page);
	LCD_DELAY(1);

	// Стробирование сигнала
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);
}

// Выбор адреса столбца
void LCD_SetAddress(uint8_t chip, uint8_t address)
{
	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// Сброс линии А0 (служебные сигналы)
	LCD_ClearBit_A0;

	// Сброс линии R/W (передача данных)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для передачи
	LCD_DataBusDirection(OUT);

	// Передача данных
	LCD_SetDataBits(0x40 | address);
	LCD_DELAY(1);

	// Стробирование сигнала
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);
}

// Запись данных в память дисплея
void LCD_WriteData(uint8_t chip, uint8_t data)
{
	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
	LCD_SetBit_E1;

	else
	LCD_SetBit_E2;

	// Установка линии А0 (сигналы данных)
	LCD_SetBit_A0;

	// Сброс линии R/W (передача данных)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для передачи
	LCD_DataBusDirection(OUT);

	// Передача данных
	LCD_SetDataBits(data);
	LCD_DELAY(1);

	// Стробирования сигнала
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);
}

// Чтение данных из памяти дисплея
uint8_t LCD_ReadData(uint8_t chip)
{
	uint8_t data = 0;

	// Выбор кристалла (установка вывода E1 или E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// Установка линии А0 (сигналы данных)
	LCD_SetBit_A0;

	// Установка линии R/W (прием данных)
	LCD_SetBit_RW;
	LCD_DELAY(1);

	// Конфигурация шины данных для приема
	LCD_DataBusDirection(IN);

	// Передача данных
	LCD_SetDataBits(data);
	LCD_DELAY(1);

	// Стробирование сигнала
	LCD_SetBit_E;
	LCD_DELAY(1);

	// Чтение данных
	data = (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);
	LCD_DELAY(1);

	// Возврат в исходное состояние
	LCD_Reset(chip);

	return data;
}

// Очистка страницы
void LCD_ClearPage(uint8_t chip, uint8_t page)
{
	int32_t i;

	// Выбор страницы
	LCD_SetPage(chip, page);

	// Выбор адреса
	LCD_SetAddress(chip, 0x00);

	// Цикл очистки
	for (i = 0; i < 64; i++)
	{
		// Ожидание завершения операций с дисплеем
		while (LCD_ReadStatus(chip) & 0x80);

		// Сброс битов
		LCD_WriteData(chip, 0x00);
	}
}

// Очистка дисплея
void LCD_ClearScreen(void)
{
	int32_t i;

	// Очистка всех страниц первого кристалла
	for (i = 0; i < 8; i++)
		LCD_ClearPage(1, i);

	// Очистка всех страниц второго кристалла
	for (i = 0; i < 8; i++)
		LCD_ClearPage(2, i);
}

// Вывод символа
void LCD_PutSymbol(uint8_t symbol,  // ASCII-код символа
                   uint8_t x,       // Координата по оси абсцисс (0...20)
                   uint8_t y)       // Координата по оси ординат (0...7)
{
	uint8_t  chip, page, address;
	uint16_t index;                // Индекс начального элемента символа в массиве шрифта
	uint8_t  i;

	// Проверка пренадлежности символа к заданному диапазону кодировок
	if (symbol >= FONT_MIN_CODE && symbol <= FONT_MAX_CODE)
		index = (((uint32_t)symbol) - FONT_MIN_CODE) * 6;
	// Если заданный код находится вне диапазона,
	// то используется нулевой символ массива (пробел)
	else
		index = 0;

	// Процедура вывода символа по заданным координатам
	if (x != LCD_SCREEN_WIDTH / 2)
	{
		// Номер кристалла
		chip = (x / 11) + 1;

		// Номер страницы
		page = y;

		// Адрес столбца
		address = (x % 11) * 6 + (chip - 1) * 2 + 1;

		// Выбор страницы
		LCD_SetPage(chip, page);

		// Выбора адреса столбца
		LCD_SetAddress(chip, address);

		// Цикл вывода символа
		for (i = 0; i < 6; i++)
		{
			// Ожидание завершения операций с дисплеем
			while (LCD_ReadStatus(chip) & 0x80);

			// Запись в память дисплея
			LCD_WriteData(chip, font[index + i]);
		}
	}
	// Процедура вывода символа на середину дисплея
	else
	{
		// Номер старницы
		page = y;

		// Цикл вывода символа
		for (i = 0, address = 0x3D; i < 6; i++, address++)
		{
			// Номер кристалла
			chip = (address / 64) + 1;

			// Выбор страницы
			LCD_SetPage(chip, page);

			// Выбора адреса столбца
			LCD_SetAddress(chip, address);

			// Ожидание завершения операций с дисплеем
			while (LCD_ReadStatus(chip) & 0x80);

			// Запись в память дисплея
			LCD_WriteData(chip, font[index + i]);
		}
	}
}

// Вывод строки
void LCD_PutString(const char* string,  // Указатель на массив со строкой
                   uint8_t y)           // Номер строки (0...7)
{
	uint8_t i;

	// Цикл формирования строки
	for (i = 0; i < LCD_SCREEN_WIDTH; i++)
	{
		// Остановка цикла, если достигнут конец строки
		if (!string[i])
			break;

		// Вывод символа
		LCD_PutSymbol(string[i], i, y);
	}

	// Заполнение оставшейся части массива пробелами
	for (; i < LCD_SCREEN_WIDTH; i++)
		LCD_PutSymbol(' ', i, y);
}

// Очистка строки
void LCD_ClearString(uint8_t y)  // Номер строки (0...7)
{
	// Очистка страниц обоих кристаллов
	LCD_ClearPage(1, y);
	LCD_ClearPage(2, y);
}

// Горизонтальное перемещение строки
void LCD_ScrollString(const char* string,  // Указатель на массив со строкой
                      uint8_t y,           // Номер строки (0...7)
                      int8_t *shift,       // Указатель на сдвиговый счетчик
                      uint8_t direction)   // Направление сдвига
{
	uint8_t length;            // Длина исходной строки
	uint8_t temp;              // Переменная для хранения временных данных
	char scroll[LCD_STR_LEN];  // Строка, получаемая в результате сдвига
	uint8_t i, j;

	// Вычисление длины исходной строки
	length = strlen(string);

	// Остановка выполнения функции, если исходная строка пуста
	if (length == 0)
		return;

	// Цикл сдвига
	// Если длина исходной строки НЕ превышает размер дисплея...
	if (length < LCD_SCREEN_WIDTH)
	{
		for (i = 0; i < LCD_SCREEN_WIDTH; i++)
		{
			// Сдвиг элемента
			j = (i + *shift) % LCD_SCREEN_WIDTH;

			// Запись сдвинутого элемента в новую строку
			if (j < length)
				temp = string[j];
			// Если элементов не осталось, то строка заполняется пробелами
			else
				temp = ' ';

			scroll[i] = temp;
		}
	}

	// Если длина исходной строки превышает размер дисплея...
	else
	{
		for (i = 0; i < LCD_SCREEN_WIDTH; i++)
		{
			// Сдвиг элемента
			j = (i + *shift) % LCD_SCREEN_WIDTH;

			// Если достигнут конец строки, то элемент перемещается в ее начало
			if (j >= length)
				j %= length;

			scroll[i] = string[j];
		}
	}

	// Вывод сформированной строки на дисплей
	LCD_PutString(scroll, y);

	// Изменение сдвигового счетчика в соответствии с выбранным направлением
	if (direction == LCD_SCROLL_LEFT)
		*shift += 1;
	else
		*shift -= 1;

	// Проверка на переполнение сдвигового считчика при прямом счете
	if (*shift > (LCD_SCREEN_WIDTH - 1))
		*shift = 0;

	// Проверка на переполнение сдвигового считчика при обратном счете
	if (*shift < 0)
		*shift = (LCD_SCREEN_WIDTH - 1);
}

// Вывод изображения
// (координатами изображения считаются координаты его верхнего левого фрагмента)
void LCD_PutImage(const uint8_t* image,     // Указатель на массив с изображением
                        uint8_t  origin_x,  // Координата изображения по оси абсцисс
                        uint8_t  origin_y,  // Координата изображения по оси ординат
                        uint8_t  width,     // Ширина изображения
                        uint8_t  height)    // Высота изображения
{
	uint8_t chip, page, address;
	uint8_t x, y;
	uint8_t count = 0;
	uint8_t i;

	// Циклы формирования изображения
	for (y = origin_y; y < origin_y + height; y++)
	{
		for (x = origin_x; x < origin_x + width; x++)
		{
			// Процедура вывода фрагмента изображения по вычисленным координатам
			// (за исключением середины дисплея)
			if (x != LCD_SCREEN_WIDTH / 2)
			{
				chip    = (x / 11) + 1;                       // Номер кристалла
				page    = y;                                  // Номер страницы
				address = (x % 11) * 6 + (chip - 1) * 2 + 1;  // Адрес столбца

				// Выбор страницы
				LCD_SetPage(chip, page);

				// Выбора адреса колонки
				LCD_SetAddress(chip, address);

				// Цикл формирования элемента изображения
				for (i = 0; i < 6; i++)
				{
					// Ожидание завершения операций с дисплеем
					while (LCD_ReadStatus(chip) & 0x80);

					// Запись элемента изображения размером 8x8 в память дисплея
					LCD_WriteData(chip, image[count + i]);
				}
			}

			// Процедура вывода фрагмента изображения на середину дисплея
			else
			{
				// Номер старницы
				page = y;

				for (i = 0, address = 0x3D; i < 6; i++, address++)
				{
					// Номер кристалла
					chip = (address / 64) + 1;

					// Выбор страницы
					LCD_SetPage(chip, page);

					// Выбора адреса столбца
					LCD_SetAddress(chip, address);

					// Ожидание завершения операций с дисплеем
					while (LCD_ReadStatus(chip) & 0x80);

					// Запись в память дисплея
					LCD_WriteData(chip, image[count + i]);
				}
			}

			// Переход к следующему фрагменту изображения
			count += 6;
		}
	}
}
