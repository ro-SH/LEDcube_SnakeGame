 /*******************************************************************************
 * @File: lcd.c
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 22.03.2017
 * @Purpose: ���������� ��� ������ � �������� MT-12864J
 *******************************************************************************/

// ����������� ������������� �����
#include "lcd.h"

// ������������ ������ ��� ������ � ��������
void LCD_PortCfg(void)
{
	// ������������ ����� PA0...PA5 � �������� ��������������� ���� ������ (DB0...DB5)
	MDR_PORTA->OE     &= 0xFFFFFFC0;
	MDR_PORTA->PULL   &= 0xFFC0FFC0;
	MDR_PORTA->ANALOG |= 0x0000003F;
	MDR_PORTA->FUNC   &= 0xFFFFF000;
	MDR_PORTA->PD     &= 0xFFC0FFC0;
	MDR_PORTA->PWR    |= 0x00000FFF;
	MDR_PORTA->GFEN   &= 0xFFFFFFC0;

	// ������������ ����� PF2 � PF3 � �������� ��������������� ���� ������ (DB6, DB7)
	MDR_PORTF->OE     &= 0xFFFFFFF3;
	MDR_PORTF->PULL   &= 0xFFF3FFF3;
	MDR_PORTF->ANALOG |= 0x0000000C;
	MDR_PORTF->FUNC   &= 0xFFFFFF0F;
	MDR_PORTF->PD     &= 0xFFF3FFF3;
	MDR_PORTF->PWR    |= 0x000000F0;
	MDR_PORTF->GFEN   &= 0xFFFFFFF3;

	// ������������ ����� PB7...PB10 � �������� �������� ������� (E1, E2, RES, R/W)
	MDR_PORTB->OE     |= 0x00000780;
	MDR_PORTB->PULL   &= 0xF87FF87F;
	MDR_PORTB->ANALOG |= 0x00000780;
	MDR_PORTB->FUNC   &= 0xFFC03FFF;
	MDR_PORTB->PD     &= 0xF87FF87F;
	MDR_PORTB->PWR    |= 0x003FC000;
	MDR_PORTB->GFEN   &= 0xFFFFF87F;

	// ������������ ����� PC0 � PC1 � �������� �������� ������� (A0, E)
	MDR_PORTC->OE     |= 0x00000003;
	MDR_PORTC->PULL   &= 0xFFFCFFFC;
	MDR_PORTC->ANALOG |= 0x00000003;
	MDR_PORTC->FUNC   &= 0xFFFFFFF0;
	MDR_PORTC->PD     &= 0xFFFCFFFC;
	MDR_PORTC->PWR    |= 0x0000000F;
	MDR_PORTC->GFEN   &= 0xFFFFFFFC;
}

// ������������� ��������������������� �������
void LCD_Init(void)
{
	// ��������� ������������ ��������� ������
	MDR_RST_CLK->PER_CLOCK |= 0x20E00000;

	// ������������ ������ ��� ������ � ��������
	LCD_PortCfg();

	// ������������� �������� �������
	// ����� ����� RES
	LCD_ClearBit_RES;
	LCD_DELAY(5);

	// ��������� ����� RES
	LCD_SetBit_RES;
	LCD_DELAY(1);

	// �������� ���������� �������������
	while ((LCD_ReadStatus(1) & 0x90) && (LCD_ReadStatus(2) & 0x90));

	// �������� ���������� �������� � ��������� ��������� 1
	while (LCD_ReadStatus(1) & 0x80);
	LCD_Enable(1);

	// �������� ���������� �������� � ��������� ��������� 2
	while (LCD_ReadStatus(2) & 0x80);
	LCD_Enable(2);

	// ������� ������ �������
	LCD_ClearScreen();

	// ����������� ������������� ��������
	LCD_PutImage(header, 0, 0, 21, 2);
}

// ����� ����������� ���� ������
void LCD_DataBusDirection(uint8_t direction)
{
	// ��������
	if (direction == OUT)
	{
		MDR_PORTA->OE |= 0x0000003F;
		MDR_PORTF->OE |= 0x0000000C;
	}

	// �����
	else
	{
		MDR_PORTA->OE &= 0xFFFFFFC0;
		MDR_PORTF->OE &= 0xFFFFFFF3;
	}
}

// �������� ���������� �� ���� ������
void LCD_SetDataBits(uint8_t data)
{
	MDR_PORTA->RXTX &= 0xFFC0;
	MDR_PORTA->RXTX |= (data & 0x3F); 
	MDR_PORTF->RXTX &= 0xFFF3;
	MDR_PORTF->RXTX |= ((data >> 4) & 0x0C); 
}

// ������� ����� � �������� ���������
void LCD_Reset(uint8_t chip)
{
	// ����� ����� E
	LCD_ClearBit_E;
	LCD_DELAY(1);

	// ����� ����� A0
	LCD_ClearBit_A0;

	// ����� ����� R/W
	LCD_ClearBit_RW;

	// �������������� ������������ ���� ������
	LCD_DataBusDirection(IN);

	// ������ ������ ��������� (����� ����� E1 ��� E2)
	if (chip == 1)
		LCD_ClearBit_E1;
	else
		LCD_ClearBit_E2;
}

// ��������� �������
void LCD_Enable(uint8_t chip)
{
	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// ����� ����� �0 (��������� �������)
	LCD_ClearBit_A0;

	// ����� ����� R/W (�������� ������)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ��������
	LCD_DataBusDirection(OUT);

	// �������� ������
	LCD_SetDataBits(0x3F);
	LCD_DELAY(1);

	// ������������� �������
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);
}

// ���������� �������
void LCD_Disable(uint8_t chip)
{
	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// ����� ����� �0 (��������� �������)
	LCD_ClearBit_A0;

	// ����� ����� R/W (�������� ������)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ��������
	LCD_DataBusDirection(OUT);

	// �������� ������
	LCD_SetDataBits(0x3E);
	LCD_DELAY(1);

	// ������������� �������
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);
}

// ��������� ������� ��������
uint8_t LCD_ReadStatus(uint8_t chip)
{
	uint8_t data;

	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// ����� ����� A0 (��������� �������)
	LCD_ClearBit_A0;

	// ��������� ����� R/W (����� ������)
	LCD_SetBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ������
	LCD_DataBusDirection(IN);

	// ��������� ����� E
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������ ������
	data = (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);

	return data;
}

// ����� ��������
void LCD_SetPage(uint8_t chip, uint8_t page)
{
	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// ����� ����� �0 (��������� �������)
	LCD_ClearBit_A0;

	// ����� ����� R/W (�������� ������)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ��������
	LCD_DataBusDirection(OUT);

	// �������� ������
	LCD_SetDataBits(0xB8 | page);
	LCD_DELAY(1);

	// ������������� �������
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);
}

// ����� ������ �������
void LCD_SetAddress(uint8_t chip, uint8_t address)
{
	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// ����� ����� �0 (��������� �������)
	LCD_ClearBit_A0;

	// ����� ����� R/W (�������� ������)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ��������
	LCD_DataBusDirection(OUT);

	// �������� ������
	LCD_SetDataBits(0x40 | address);
	LCD_DELAY(1);

	// ������������� �������
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);
}

// ������ ������ � ������ �������
void LCD_WriteData(uint8_t chip, uint8_t data)
{
	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
	LCD_SetBit_E1;

	else
	LCD_SetBit_E2;

	// ��������� ����� �0 (������� ������)
	LCD_SetBit_A0;

	// ����� ����� R/W (�������� ������)
	LCD_ClearBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ��������
	LCD_DataBusDirection(OUT);

	// �������� ������
	LCD_SetDataBits(data);
	LCD_DELAY(1);

	// ������������� �������
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);
}

// ������ ������ �� ������ �������
uint8_t LCD_ReadData(uint8_t chip)
{
	uint8_t data = 0;

	// ����� ��������� (��������� ������ E1 ��� E2)
	if (chip == 1)
		LCD_SetBit_E1;
	else
		LCD_SetBit_E2;

	// ��������� ����� �0 (������� ������)
	LCD_SetBit_A0;

	// ��������� ����� R/W (����� ������)
	LCD_SetBit_RW;
	LCD_DELAY(1);

	// ������������ ���� ������ ��� ������
	LCD_DataBusDirection(IN);

	// �������� ������
	LCD_SetDataBits(data);
	LCD_DELAY(1);

	// ������������� �������
	LCD_SetBit_E;
	LCD_DELAY(1);

	// ������ ������
	data = (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);
	LCD_DELAY(1);

	// ������� � �������� ���������
	LCD_Reset(chip);

	return data;
}

// ������� ��������
void LCD_ClearPage(uint8_t chip, uint8_t page)
{
	int32_t i;

	// ����� ��������
	LCD_SetPage(chip, page);

	// ����� ������
	LCD_SetAddress(chip, 0x00);

	// ���� �������
	for (i = 0; i < 64; i++)
	{
		// �������� ���������� �������� � ��������
		while (LCD_ReadStatus(chip) & 0x80);

		// ����� �����
		LCD_WriteData(chip, 0x00);
	}
}

// ������� �������
void LCD_ClearScreen(void)
{
	int32_t i;

	// ������� ���� ������� ������� ���������
	for (i = 0; i < 8; i++)
		LCD_ClearPage(1, i);

	// ������� ���� ������� ������� ���������
	for (i = 0; i < 8; i++)
		LCD_ClearPage(2, i);
}

// ����� �������
void LCD_PutSymbol(uint8_t symbol,  // ASCII-��� �������
                   uint8_t x,       // ���������� �� ��� ������� (0...20)
                   uint8_t y)       // ���������� �� ��� ������� (0...7)
{
	uint8_t  chip, page, address;
	uint16_t index;                // ������ ���������� �������� ������� � ������� ������
	uint8_t  i;

	// �������� �������������� ������� � ��������� ��������� ���������
	if (symbol >= FONT_MIN_CODE && symbol <= FONT_MAX_CODE)
		index = (((uint32_t)symbol) - FONT_MIN_CODE) * 6;
	// ���� �������� ��� ��������� ��� ���������,
	// �� ������������ ������� ������ ������� (������)
	else
		index = 0;

	// ��������� ������ ������� �� �������� �����������
	if (x != LCD_SCREEN_WIDTH / 2)
	{
		// ����� ���������
		chip = (x / 11) + 1;

		// ����� ��������
		page = y;

		// ����� �������
		address = (x % 11) * 6 + (chip - 1) * 2 + 1;

		// ����� ��������
		LCD_SetPage(chip, page);

		// ������ ������ �������
		LCD_SetAddress(chip, address);

		// ���� ������ �������
		for (i = 0; i < 6; i++)
		{
			// �������� ���������� �������� � ��������
			while (LCD_ReadStatus(chip) & 0x80);

			// ������ � ������ �������
			LCD_WriteData(chip, font[index + i]);
		}
	}
	// ��������� ������ ������� �� �������� �������
	else
	{
		// ����� ��������
		page = y;

		// ���� ������ �������
		for (i = 0, address = 0x3D; i < 6; i++, address++)
		{
			// ����� ���������
			chip = (address / 64) + 1;

			// ����� ��������
			LCD_SetPage(chip, page);

			// ������ ������ �������
			LCD_SetAddress(chip, address);

			// �������� ���������� �������� � ��������
			while (LCD_ReadStatus(chip) & 0x80);

			// ������ � ������ �������
			LCD_WriteData(chip, font[index + i]);
		}
	}
}

// ����� ������
void LCD_PutString(const char* string,  // ��������� �� ������ �� �������
                   uint8_t y)           // ����� ������ (0...7)
{
	uint8_t i;

	// ���� ������������ ������
	for (i = 0; i < LCD_SCREEN_WIDTH; i++)
	{
		// ��������� �����, ���� ��������� ����� ������
		if (!string[i])
			break;

		// ����� �������
		LCD_PutSymbol(string[i], i, y);
	}

	// ���������� ���������� ����� ������� ���������
	for (; i < LCD_SCREEN_WIDTH; i++)
		LCD_PutSymbol(' ', i, y);
}

// ������� ������
void LCD_ClearString(uint8_t y)  // ����� ������ (0...7)
{
	// ������� ������� ����� ����������
	LCD_ClearPage(1, y);
	LCD_ClearPage(2, y);
}

// �������������� ����������� ������
void LCD_ScrollString(const char* string,  // ��������� �� ������ �� �������
                      uint8_t y,           // ����� ������ (0...7)
                      int8_t *shift,       // ��������� �� ��������� �������
                      uint8_t direction)   // ����������� ������
{
	uint8_t length;            // ����� �������� ������
	uint8_t temp;              // ���������� ��� �������� ��������� ������
	char scroll[LCD_STR_LEN];  // ������, ���������� � ���������� ������
	uint8_t i, j;

	// ���������� ����� �������� ������
	length = strlen(string);

	// ��������� ���������� �������, ���� �������� ������ �����
	if (length == 0)
		return;

	// ���� ������
	// ���� ����� �������� ������ �� ��������� ������ �������...
	if (length < LCD_SCREEN_WIDTH)
	{
		for (i = 0; i < LCD_SCREEN_WIDTH; i++)
		{
			// ����� ��������
			j = (i + *shift) % LCD_SCREEN_WIDTH;

			// ������ ���������� �������� � ����� ������
			if (j < length)
				temp = string[j];
			// ���� ��������� �� ��������, �� ������ ����������� ���������
			else
				temp = ' ';

			scroll[i] = temp;
		}
	}

	// ���� ����� �������� ������ ��������� ������ �������...
	else
	{
		for (i = 0; i < LCD_SCREEN_WIDTH; i++)
		{
			// ����� ��������
			j = (i + *shift) % LCD_SCREEN_WIDTH;

			// ���� ��������� ����� ������, �� ������� ������������ � �� ������
			if (j >= length)
				j %= length;

			scroll[i] = string[j];
		}
	}

	// ����� �������������� ������ �� �������
	LCD_PutString(scroll, y);

	// ��������� ���������� �������� � ������������ � ��������� ������������
	if (direction == LCD_SCROLL_LEFT)
		*shift += 1;
	else
		*shift -= 1;

	// �������� �� ������������ ���������� �������� ��� ������ �����
	if (*shift > (LCD_SCREEN_WIDTH - 1))
		*shift = 0;

	// �������� �� ������������ ���������� �������� ��� �������� �����
	if (*shift < 0)
		*shift = (LCD_SCREEN_WIDTH - 1);
}

// ����� �����������
// (������������ ����������� ��������� ���������� ��� �������� ������ ���������)
void LCD_PutImage(const uint8_t* image,     // ��������� �� ������ � ������������
                        uint8_t  origin_x,  // ���������� ����������� �� ��� �������
                        uint8_t  origin_y,  // ���������� ����������� �� ��� �������
                        uint8_t  width,     // ������ �����������
                        uint8_t  height)    // ������ �����������
{
	uint8_t chip, page, address;
	uint8_t x, y;
	uint8_t count = 0;
	uint8_t i;

	// ����� ������������ �����������
	for (y = origin_y; y < origin_y + height; y++)
	{
		for (x = origin_x; x < origin_x + width; x++)
		{
			// ��������� ������ ��������� ����������� �� ����������� �����������
			// (�� ����������� �������� �������)
			if (x != LCD_SCREEN_WIDTH / 2)
			{
				chip    = (x / 11) + 1;                       // ����� ���������
				page    = y;                                  // ����� ��������
				address = (x % 11) * 6 + (chip - 1) * 2 + 1;  // ����� �������

				// ����� ��������
				LCD_SetPage(chip, page);

				// ������ ������ �������
				LCD_SetAddress(chip, address);

				// ���� ������������ �������� �����������
				for (i = 0; i < 6; i++)
				{
					// �������� ���������� �������� � ��������
					while (LCD_ReadStatus(chip) & 0x80);

					// ������ �������� ����������� �������� 8x8 � ������ �������
					LCD_WriteData(chip, image[count + i]);
				}
			}

			// ��������� ������ ��������� ����������� �� �������� �������
			else
			{
				// ����� ��������
				page = y;

				for (i = 0, address = 0x3D; i < 6; i++, address++)
				{
					// ����� ���������
					chip = (address / 64) + 1;

					// ����� ��������
					LCD_SetPage(chip, page);

					// ������ ������ �������
					LCD_SetAddress(chip, address);

					// �������� ���������� �������� � ��������
					while (LCD_ReadStatus(chip) & 0x80);

					// ������ � ������ �������
					LCD_WriteData(chip, image[count + i]);
				}
			}

			// ������� � ���������� ��������� �����������
			count += 6;
		}
	}
}
