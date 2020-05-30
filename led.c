/*******************************************************************************
 * @File: led.c
 * @Author: Kristina Karmanova
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: LED managing
 *******************************************************************************/



//����������� ������������� �����
#include "led.h"

/*����������, ������������ ���������� ��������� ������� Q0..Q5 �������������� ��������� ��������� 
(��������� �������� �� 0 �� 63 � ����� ������, ��������� �� ����������� ���� ������ 6 ������� ��������)
��������� �������� 0 - �.�. ���������� �� ����� - �.�. �� ��� ������ ������� 0 */
int register_1 = 0; 
int register_2 = 0;
int register_3 = 0;
int register_4 = 0;
int register_5 = 0;
int register_6 = 0;
int register_7 = 0;


//��������� ��������� ���������� � ���������� ������������ �, �, z
void switch_on(int x, int y, int z){	
	
	/*����� ��������, �� ������� ���������� �������� ������� (�������� �����������)
	� ���������� ������ ��������� ������� �� ��*/
	switch(x){
		case 0:
			register_1 += select_led(y); 
		case 1:
			register_2 += select_led(y); 
		case 2:
			register_3 += select_led(y); 
		case 3:
			register_4 += select_led(y); 
		case 4:
			register_5 += select_led(y);
		case 5:
			register_6 += select_led(y);
	}
	register_7 += select_led(z);			
	set_registers();
}



//��������� ������� ���������� � ���������� ������������ �, �, z
void switch_off(int x, int y, int z){
	
	/*����� ��������, �� ������� ���������� �������� ������� (�������� �����������)
	� ���������� ������ ��������� ������� �� ��*/
	switch(x){
		case 0:
			register_1 -= select_led(y);
		case 1:
			register_2 -= select_led(y); 
		case 2:
			register_3 -= select_led(y);
		case 3:
			register_4 -= select_led(y);
		case 4:
			register_5 -= select_led(y);
		case 5:
			register_6 -= select_led(y);
	}
	register_7 -= select_led(z);				
	set_registers();
}


//��������� ������� ����� ����
void all_off(){
	
	register_1 = 0; 
	register_2 = 0;
	register_3 = 0;
	register_4 = 0;
	register_5 = 0;
	register_6 = 0;
	register_7 = 0;
	
	set_registers();
}



//��������� �������� � ��������� ����� �������� �� ��������� ��������
void set_registers(){
	
	// ������������� ������������� "�������" 0
	MDR_PORTB->RXTX &= ~(1 << 2);
	
	shiftOut(0, 4, 1, register_7); //�������� �������� �� 7 ��������� �������			
	shiftOut(0, 4, 1, register_6); //�������� �������� �� 6 ��������� �������
	shiftOut(0, 4, 1, register_5); //�������� �������� �� 5 ��������� �������
	shiftOut(0, 4, 1, register_4); //�������� �������� �� 4 ��������� �������
	shiftOut(0, 4, 1, register_3); //�������� �������� �� 3 ��������� �������
	shiftOut(0, 4, 1, register_2); //�������� �������� �� 2 ��������� �������
	shiftOut(0, 4, 1, register_1); //�������� �������� �� 1 ��������� �������
	
	//"�����������" �������, ��� ����� ������������ �������� �� �������
	MDR_PORTB->RXTX |= (1 << 2);
}




//������� ����������� ����������� �����, �������� ���������� �������� �������� ���������� � ���������� � �������� �����������
int select_led(int i){
	int coordinates[6];
	
	//������ ����������� �������� ������������ ����� � ����������� ���������� � ������� Q0..Q5 (������ Q6, Q7  �� �������������)
	coordinates[0] = 1; 
	coordinates[1] = 2;
	coordinates[2] = 4;
	coordinates[3] = 8;
	coordinates[4] = 16;
	coordinates[5] = 32;
	
	return(coordinates[i]);
}




void delay(){
	    for(uint32_t i = 1000000; i!=0; i--){
			__NOP;//������ �������, ����� ���������� �� �������������� ����
		}
}




//��������� ����������������� ������ ����� ���������� �� ���� ������ (�������)
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val){
	
    uint8_t i;
    for (i = 0; i < 8; i++)  {
        if (bitOrder == 0){
						if (!!(val & (1 << i)))
								MDR_PORTB->RXTX |= (1 << dataPin);
						else
								MDR_PORTB->RXTX &= ~(1 << dataPin);
					}
        else{
						if (!!(val & (1 << (7 - i))))
								MDR_PORTB->RXTX |= (1 << dataPin);
						else 
								MDR_PORTB->RXTX &= ~(1 << dataPin);
				}
        MDR_PORTB->RXTX |= (1 << clockPin);
        MDR_PORTB->RXTX &= ~(1 << clockPin);        
    }
}



//��������� ������������� ������ ��� ����������� ��������
void ports_init(void){
	
	// ��������� ������������ ����� B
	MDR_RST_CLK->PER_CLOCK |= (1 << RST_CLK_PCLK_PORTB_Pos);
	
	// ������������ ����� PB4 � �������� ��������� ������
	MDR_PORTB->OE |= (1 << 4); // ����������� ������ (�����)
	MDR_PORTB->PULL &= ~(1 << 4); // �������� � ����� (���������)
	MDR_PORTB->PULL &= ~(1 << 20); // �������� � ������� (���������)
	MDR_PORTB->ANALOG |= (1 << 4); // ����� ������ ����� (��������)
	MDR_PORTB->FUNC &= ~(3 << 8); // ������� ����� (����-�����)
	MDR_PORTB->PD &= ~(1 << 4); // ���������� ������ (�������)
	MDR_PORTB->PD &= ~(1 << 20); // ������� ������ (�� ������������)
	MDR_PORTB->PWR &= ~(3 << 8); // ����� ����� �������� PWR
	MDR_PORTB->PWR |= (3 << 8); // �������� ������� (������)
	MDR_PORTB->GFEN &= ~(1 << 4); // �������� ������ (�� ������������)
	
	// ������������ ����� PB2 � �������� ��������� ������
	MDR_PORTB->OE |= (1 << 2); // ����������� ������ (�����)
	MDR_PORTB->PULL &= ~(1 << 2); // �������� � ����� (���������)
	MDR_PORTB->PULL &= ~(1 << 18); // �������� � ������� (���������)
	MDR_PORTB->ANALOG |= (1 << 2); // ����� ������ ����� (��������)
	MDR_PORTB->FUNC &= ~(3 << 4); // ������� ����� (����-�����)
	MDR_PORTB->PD &= ~(1 << 2); // ���������� ������ (�������)
	MDR_PORTB->PD &= ~(1 << 18); // ������� ������ (�� ������������)
	MDR_PORTB->PWR &= ~(3 << 4); // ����� ����� �������� PWR
	MDR_PORTB->PWR |= (3 << 4); // �������� ������� (������)
	MDR_PORTB->GFEN &= ~(1 << 2); // �������� ������ (�� ������������)
	
	// ������������ ����� PB0 � �������� ��������� ������
	MDR_PORTB->OE |= (1 << 0); // ����������� ������ (�����)
	MDR_PORTB->PULL &= ~(1 << 0); // �������� � ����� (���������)
	MDR_PORTB->PULL &= ~(1 << 16); // �������� � ������� (���������)
	MDR_PORTB->ANALOG |= (1 << 0); // ����� ������ ����� (��������)
	MDR_PORTB->FUNC &= ~(3 << 0); // ������� ����� (����-�����)
	MDR_PORTB->PD &= ~(1 << 0); // ���������� ������ (�������)
	MDR_PORTB->PD &= ~(1 << 16); // ������� ������ (�� ������������)
	MDR_PORTB->PWR &= ~(3 << 0); // ����� ����� �������� PWR
	MDR_PORTB->PWR |= (3 << 0); // �������� ������� (������)
	MDR_PORTB->GFEN &= ~(1 << 0); // �������� ������ (�� ������������)
}
