#include "stm32f10x.h"
#include "MyUART.h"

int main(void){
	MyUART_Struct_TypeDef uart;
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	MyUART_Init(&uart);
	while(1);
}
