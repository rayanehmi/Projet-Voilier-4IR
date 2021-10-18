#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
MyGPIO_Struct_TypeDef gpio;
MyUART_Struct_TypeDef uart;
char test;

void Callback(){
	test = MyUART_GetChar(uart.UART);
}

int main(void){
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback);
	
	MyUART_PutStr(uart.UART, "ssstringgg");
	while(1);
}
