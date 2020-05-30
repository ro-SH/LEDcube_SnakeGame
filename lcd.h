/*******************************************************************************
 * @File: lcd.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 22.03.2017
 * @Purpose: Библиотека для работы с дисплеем MT-12864J
 *******************************************************************************/

// Standart Peripheral Libraries
#include "1986VE9x.h"

// Подключение стандартных библиотек языка Си
#include <stdio.h>
#include <string.h>

// Подключение файла с кодировкой символов
#include "font.h"

// Ширина дисплея (в символах 6x8)
#define LCD_SCREEN_WIDTH 21

// Допустимая длина строки
// (с учетом терминирующего нуля)
#define LCD_STR_LEN  LCD_SCREEN_WIDTH + 1

// Директивы для работы с выводами дисплея
// Линия E1 (выбор кристалла 1)
#define LCD_ClearBit_E1   MDR_PORTB->RXTX &= ~(1 << 7)
#define LCD_SetBit_E1     MDR_PORTB->RXTX |= (1 << 7)

// Линия E2 (выбор кристалла 2)
#define LCD_ClearBit_E2   MDR_PORTB->RXTX &= ~(1 << 8)
#define LCD_SetBit_E2     MDR_PORTB->RXTX |= (1 << 8)

// Линия RES (сброс)
#define LCD_ClearBit_RES  MDR_PORTB->RXTX &= ~(1 << 9)
#define LCD_SetBit_RES    MDR_PORTB->RXTX |= (1 << 9)

// Линия R/W (чтение/запись)
#define LCD_ClearBit_RW   MDR_PORTB->RXTX &= ~(1 << 10)
#define LCD_SetBit_RW     MDR_PORTB->RXTX |= (1 << 10)

// Линия A0 (команды/данные)
#define LCD_ClearBit_A0   MDR_PORTC->RXTX &= ~1
#define LCD_SetBit_A0     MDR_PORTC->RXTX |= 1

// Линия E (стробирование данных)
#define LCD_ClearBit_E    MDR_PORTC->RXTX &= ~(1 << 1)
#define LCD_SetBit_E      MDR_PORTC->RXTX |= (1 << 1)

// Задержка (в микросекундах)
#define LCD_DELAY(VALUE)  for (uint32_t i = (VALUE) * SystemCoreClock / (4 * 1000000); \
                                        i != 0;                                        \
                                        i--)

// Направления шины данных
enum
{
	OUT = 0,
	IN  = !OUT
};

// Направления перемещения строки
enum
{
	LCD_SCROLL_LEFT  = 0,
	LCD_SCROLL_RIGHT = !LCD_SCROLL_LEFT
};

// Прототипы функций
void LCD_PortCfg(void);                                                      // Конфигурация линий ввода-вывода для работы с дисплеем
void LCD_Init(void);                                                         // Инициализация дисплея
void LCD_DataBusDirection(uint8_t direction);                                // Выбор направления шины данных
void LCD_SetDataBits(uint8_t value);                                         // Передача информации на шину данных
void LCD_Reset(uint8_t chip);                                                // Возврат выводов в исходное состояние
void LCD_Enable(uint8_t chip);                                               // Включение дисплея
void LCD_Disable(uint8_t chip);                                              // Выключение дисплея
uint8_t LCD_ReadStatus(uint8_t chip);                                        // Получение статуса операции
void LCD_SetPage(uint8_t chip, uint8_t page);                                // Выбор страницы
void LCD_SetAddress(uint8_t chip, uint8_t address);                          // Выбор адреса колонки
void LCD_WriteData(uint8_t chip, uint8_t data);                              // Запись данных в ОЗУ дисплея
uint8_t LCD_ReadData(uint8_t chip);                                          // Чтение данных из ОЗУ дисплея
void LCD_ClearPage(uint8_t chip, uint8_t page);                              // Очистка страницы
void LCD_ClearScreen(void);                                                  // Очистка дисплея
void LCD_PutSymbol(uint8_t symbol, uint8_t x, uint8_t y);                    // Вывод символа
void LCD_PutString(const char* string, uint8_t y);                           // Вывод строки
void LCD_ClearString(uint8_t y);                                             // Очистка строки
void LCD_ScrollString(const char* string,  uint8_t y,                        // Горизонтальное перемещение строки
                            int8_t *shift, uint8_t direction);
void LCD_PutImage(const uint8_t* image, uint8_t origin_x, uint8_t origin_y,  // Вывод изображения
                                        uint8_t width,    uint8_t height);
