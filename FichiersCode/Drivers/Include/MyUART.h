#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"

typedef struct
{
	USART_TypeDef * UART ;
	int UART_BaudRate ; // BPS
} MyUART_Struct_TypeDef ;

void MyUART_Init ( MyUART_Struct_TypeDef * UARTStructPtr ) ;
void MyUART_ActiveIT(USART_TypeDef * UART , char Prio , void (*IT_function)(void) ) ;
void MyUART_PutStr ( USART_TypeDef * UART, char* String);
char MyUART_GetChar ( USART_TypeDef * UART );

#endif
