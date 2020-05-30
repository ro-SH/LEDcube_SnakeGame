/*******************************************************************************
 * @File: lcd.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 22.03.2017
 * @Purpose: ���������� ��� ������ � �������� MT-12864J
 *******************************************************************************/

// Standart Peripheral Libraries
#include "1986VE9x.h"

// ����������� ����������� ��������� ����� ��
#include <stdio.h>
#include <string.h>

// ����������� ����� � ���������� ��������
#include "font.h"

// ������ ������� (� �������� 6x8)
#define LCD_SCREEN_WIDTH 21

// ���������� ����� ������
// (� ������ �������������� ����)
#define LCD_STR_LEN  LCD_SCREEN_WIDTH + 1

// ��������� ��� ������ � �������� �������
// ����� E1 (����� ��������� 1)
#define LCD_ClearBit_E1   MDR_PORTB->RXTX &= ~(1 << 7)
#define LCD_SetBit_E1     MDR_PORTB->RXTX |= (1 << 7)

// ����� E2 (����� ��������� 2)
#define LCD_ClearBit_E2   MDR_PORTB->RXTX &= ~(1 << 8)
#define LCD_SetBit_E2     MDR_PORTB->RXTX |= (1 << 8)

// ����� RES (�����)
#define LCD_ClearBit_RES  MDR_PORTB->RXTX &= ~(1 << 9)
#define LCD_SetBit_RES    MDR_PORTB->RXTX |= (1 << 9)

// ����� R/W (������/������)
#define LCD_ClearBit_RW   MDR_PORTB->RXTX &= ~(1 << 10)
#define LCD_SetBit_RW     MDR_PORTB->RXTX |= (1 << 10)

// ����� A0 (�������/������)
#define LCD_ClearBit_A0   MDR_PORTC->RXTX &= ~1
#define LCD_SetBit_A0     MDR_PORTC->RXTX |= 1

// ����� E (������������� ������)
#define LCD_ClearBit_E    MDR_PORTC->RXTX &= ~(1 << 1)
#define LCD_SetBit_E      MDR_PORTC->RXTX |= (1 << 1)

// �������� (� �������������)
#define LCD_DELAY(VALUE)  for (uint32_t i = (VALUE) * SystemCoreClock / (4 * 1000000); \
                                        i != 0;                                        \
                                        i--)

// ����������� ���� ������
enum
{
	OUT = 0,
	IN  = !OUT
};

// ����������� ����������� ������
enum
{
	LCD_SCROLL_LEFT  = 0,
	LCD_SCROLL_RIGHT = !LCD_SCROLL_LEFT
};

// ��������� �������
void LCD_PortCfg(void);                                                      // ������������ ����� �����-������ ��� ������ � ��������
void LCD_Init(void);                                                         // ������������� �������
void LCD_DataBusDirection(uint8_t direction);                                // ����� ����������� ���� ������
void LCD_SetDataBits(uint8_t value);                                         // �������� ���������� �� ���� ������
void LCD_Reset(uint8_t chip);                                                // ������� ������� � �������� ���������
void LCD_Enable(uint8_t chip);                                               // ��������� �������
void LCD_Disable(uint8_t chip);                                              // ���������� �������
uint8_t LCD_ReadStatus(uint8_t chip);                                        // ��������� ������� ��������
void LCD_SetPage(uint8_t chip, uint8_t page);                                // ����� ��������
void LCD_SetAddress(uint8_t chip, uint8_t address);                          // ����� ������ �������
void LCD_WriteData(uint8_t chip, uint8_t data);                              // ������ ������ � ��� �������
uint8_t LCD_ReadData(uint8_t chip);                                          // ������ ������ �� ��� �������
void LCD_ClearPage(uint8_t chip, uint8_t page);                              // ������� ��������
void LCD_ClearScreen(void);                                                  // ������� �������
void LCD_PutSymbol(uint8_t symbol, uint8_t x, uint8_t y);                    // ����� �������
void LCD_PutString(const char* string, uint8_t y);                           // ����� ������
void LCD_ClearString(uint8_t y);                                             // ������� ������
void LCD_ScrollString(const char* string,  uint8_t y,                        // �������������� ����������� ������
                            int8_t *shift, uint8_t direction);
void LCD_PutImage(const uint8_t* image, uint8_t origin_x, uint8_t origin_y,  // ����� �����������
                                        uint8_t width,    uint8_t height);
