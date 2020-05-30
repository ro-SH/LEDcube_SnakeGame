/*******************************************************************************
 * @File: led.c
 * @Author: Kristina Karmanova
 * @Project: Snake game on LED cube
 * @Microcontroller: Milandr 1986VE92U
 * @Purpose: LED managing
 *******************************************************************************/



//Подключение заголовочного файла
#include "led.h"

/*переменные, запоминающие предыдущее состояние выходов Q0..Q5 соответсвующих сдвиговых регистров 
(принимают значения от 0 до 63 в нашем случае, поскольку мы задействуем лишь первые 6 выходов регистра)
начальное значение 0 - т.к. светодиоды не горят - т.е. на все выходы подаётся 0 */
int register_1 = 0; 
int register_2 = 0;
int register_3 = 0;
int register_4 = 0;
int register_5 = 0;
int register_6 = 0;
int register_7 = 0;


//процедура зажигания светодиода с выбранными координатами х, у, z
void switch_on(int x, int y, int z){	
	
	/*выбор регистра, на котором изменяется значение выходов (согласно подключению)
	и вычисление нового состояния выходов на нём*/
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



//процедура гашения светодиода с выбранными координатами х, у, z
void switch_off(int x, int y, int z){
	
	/*выбор регистра, на котором изменяется значение выходов (согласно подключению)
	и вычисление нового состояния выходов на нём*/
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


//процедура гашения всего куба
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



//процедура передачи и установки новых значений на сдвиговые регистры
void set_registers(){
	
	// устанавливаем синхронизацию "защелки" 0
	MDR_PORTB->RXTX &= ~(1 << 2);
	
	shiftOut(0, 4, 1, register_7); //передача значений на 7 сдвиговый регистр			
	shiftOut(0, 4, 1, register_6); //передача значений на 6 сдвиговый регистр
	shiftOut(0, 4, 1, register_5); //передача значений на 5 сдвиговый регистр
	shiftOut(0, 4, 1, register_4); //передача значений на 4 сдвиговый регистр
	shiftOut(0, 4, 1, register_3); //передача значений на 3 сдвиговый регистр
	shiftOut(0, 4, 1, register_2); //передача значений на 2 сдвиговый регистр
	shiftOut(0, 4, 1, register_1); //передача значений на 1 сдвиговый регистр
	
	//"защелкиваем" регистр, тем самым устанавливая значения на выходах
	MDR_PORTB->RXTX |= (1 << 2);
}




//функция определения десятичного числа, двоичный эквивалент которого позволит обратиться к светодиоду с заданной координатой
int select_led(int i){
	int coordinates[6];
	
	//массив заполняется согласно координатной сетке и подключению светододов к выходам Q0..Q5 (выходы Q6, Q7  не задействованы)
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
			__NOP;//пустая команда, чтобы компилятор не соптимизировал цикл
		}
}




//Процедура последовательного вывода байта информации на порт выхода (побитно)
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



//процедура инизиализации портов для подключения регистра
void ports_init(void){
	
	// Включение тактирования порта B
	MDR_RST_CLK->PER_CLOCK |= (1 << RST_CLK_PCLK_PORTB_Pos);
	
	// Конфигурация линии PB4 в качестве цифрового вывода
	MDR_PORTB->OE |= (1 << 4); // Направление данных (вывод)
	MDR_PORTB->PULL &= ~(1 << 4); // Подтяжка к земле (отключена)
	MDR_PORTB->PULL &= ~(1 << 20); // Подтяжка к питанию (отключена)
	MDR_PORTB->ANALOG |= (1 << 4); // Режим работы линии (цифровой)
	MDR_PORTB->FUNC &= ~(3 << 8); // Функция линии (ввод-вывод)
	MDR_PORTB->PD &= ~(1 << 4); // Управление линией (драйвер)
	MDR_PORTB->PD &= ~(1 << 20); // Триггер Шмитта (не используется)
	MDR_PORTB->PWR &= ~(3 << 8); // Сброс битов регистра PWR
	MDR_PORTB->PWR |= (3 << 8); // Крутизна фронтов (низкая)
	MDR_PORTB->GFEN &= ~(1 << 4); // Цифровой фильтр (не используется)
	
	// Конфигурация линии PB2 в качестве цифрового вывода
	MDR_PORTB->OE |= (1 << 2); // Направление данных (вывод)
	MDR_PORTB->PULL &= ~(1 << 2); // Подтяжка к земле (отключена)
	MDR_PORTB->PULL &= ~(1 << 18); // Подтяжка к питанию (отключена)
	MDR_PORTB->ANALOG |= (1 << 2); // Режим работы линии (цифровой)
	MDR_PORTB->FUNC &= ~(3 << 4); // Функция линии (ввод-вывод)
	MDR_PORTB->PD &= ~(1 << 2); // Управление линией (драйвер)
	MDR_PORTB->PD &= ~(1 << 18); // Триггер Шмитта (не используется)
	MDR_PORTB->PWR &= ~(3 << 4); // Сброс битов регистра PWR
	MDR_PORTB->PWR |= (3 << 4); // Крутизна фронтов (низкая)
	MDR_PORTB->GFEN &= ~(1 << 2); // Цифровой фильтр (не используется)
	
	// Конфигурация линии PB0 в качестве цифрового вывода
	MDR_PORTB->OE |= (1 << 0); // Направление данных (вывод)
	MDR_PORTB->PULL &= ~(1 << 0); // Подтяжка к земле (отключена)
	MDR_PORTB->PULL &= ~(1 << 16); // Подтяжка к питанию (отключена)
	MDR_PORTB->ANALOG |= (1 << 0); // Режим работы линии (цифровой)
	MDR_PORTB->FUNC &= ~(3 << 0); // Функция линии (ввод-вывод)
	MDR_PORTB->PD &= ~(1 << 0); // Управление линией (драйвер)
	MDR_PORTB->PD &= ~(1 << 16); // Триггер Шмитта (не используется)
	MDR_PORTB->PWR &= ~(3 << 0); // Сброс битов регистра PWR
	MDR_PORTB->PWR |= (3 << 0); // Крутизна фронтов (низкая)
	MDR_PORTB->GFEN &= ~(1 << 0); // Цифровой фильтр (не используется)
}
