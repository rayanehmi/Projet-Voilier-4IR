#include "../Include/MyUART.h"

void MyUART_Init ( MyUART_Struct_TypeDef * UARTStructPtr ) 
{
	UARTStructPtr -> UART -> CR1 |= USART_CR1_UE ; //enable USART
	UARTStructPtr -> UART -> CR1 &=~ USART_CR1_M ; //set M bit to 0 -> parity disabled
	UARTStructPtr -> UART -> CR2 &=~ USART_CR2_STOP; //Set STOP to 00 -> 1 stop bit
	//Set baud rate
	if (UARTStructPtr -> UART == USART1) { //f = 72MHz
		UARTStructPtr -> UART -> BRR |= (int) 72000000/(UARTStructPtr->UART_BaudRate);
	}
	else if (UARTStructPtr -> UART == USART3) { //f = 36MHz
		UARTStructPtr -> UART -> BRR |= (int) 36000000/(UARTStructPtr->UART_BaudRate);
	}
	UARTStructPtr -> UART -> CR1 |= USART_CR1_TE; //send idle frame
	UARTStructPtr -> UART -> CR1 |= USART_CR1_RE; //enable receiver
	
}

void MyUART_ActiveIT(USART_TypeDef * UART , char Prio , void (*IT_function)(void) ) {
	if (UART == USART1){
		//NVIC_EnableIRQ();
}
}

