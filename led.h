/*******************************************************************************
 * @File: led.h
 * @Author: Kristina Karmanova
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: LED managing
 *******************************************************************************/

#ifndef LED_H 
#define LED_H 

#include "link.h"

void switch_on(int, int, int); //��������� ��������� ���������� � ���������� ������������ �, �, z

void switch_off(int, int, int); //��������� ������� ���������� � ���������� ������������ �, �, z

void all_off(void); //��������� ������� ����� ����

void set_registers(void); //��������� �������� � ��������� ����� �������� �� ��������� ��������

int select_led(int); //������� ����������� ����������� �����, �������� ���������� �������� �������� ���������� � ���������� � �������� �����������

void delay(void);

void shiftOut(uint8_t, uint8_t, uint8_t, uint8_t); //��������� ����������������� ������ ����� ���������� �� ���� ������ (�������)

void ports_init(void); //��������� ������������� ������ ��� ����������� ��������


#endif
