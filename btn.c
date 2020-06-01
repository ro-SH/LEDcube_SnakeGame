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
