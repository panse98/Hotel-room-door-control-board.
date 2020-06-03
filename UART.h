#include "C:/Keil_v5/Labware/tm4c123gh6pm.h"
#include "GPIO_interface.h"
#include "Keypad.h"


void UART_init()
{
	// hndy l clk lel uart rkm 0 
	SYSCTL_RCGCUART_R|=0x0001;
	SYSCTL_RCGCGPIO_R|=0x0001;//portA
	//diasble abl ma n3ml configuration
	UART0_CTL_R=0X0;
  UART0_IBRD_R=27;// bode rate(integer)
	UART0_FBRD_R=8;
	UART0_LCRH_R=0x0070;
	UART0_CC_R=0x05;
	// enable 
	UART0_CTL_R=0x0301;
	GPIO_PORTA_AFSEL_R |=0x03 ;// alternativ
	GPIO_PORTA_PCTL_R=((GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011);
	GPIO_PORTA_DEN_R|=0x03;
  GPIO_PORTA_AMSEL_R&=~0x03;
	// direction and value for portA
}
void UART_send(uint32_t data)
{
	// wait until the transmission register empty
	while((UART0_FR_R&0x20)!=0x0){}
	 UART0_DR_R=data;
}

uint32_t UART_recieve(void)
	{
		uint32_t result;
	while((UART0_FR_R&0x10)!=0x0){}
		result= UART0_DR_R;
		// mch l mfrod a set el flag b3d ma aret
 	   return result;
	}
	
	
	
