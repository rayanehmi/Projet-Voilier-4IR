#include "../Include/MyUART.h"
#include "MyGPIO.h"

// Pointeurs de l'UART
void (* pFuncUART1) (void);
void (* pFuncUART3) (void);

void MyUART_Init ( MyUART_Struct_TypeDef * UARTStructPtr ) 
{	
	MyGPIO_Struct_TypeDef gpio;
	
	// Enable Clock
	if(UARTStructPtr->UART == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //Clock Enable
		UARTStructPtr -> UART -> BRR |= (int) 72000000/(UARTStructPtr->UART_BaudRate); // Baud Rate 72 MHZ
		
		gpio.GPIO = GPIOA;
		gpio.GPIO_Pin = 9;

	}else if (UARTStructPtr->UART == USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN; //Clock Enable
		UARTStructPtr -> UART -> BRR |= (int) 36000000/(UARTStructPtr->UART_BaudRate); // Baud Rate 36 MHZ

		gpio.GPIO = GPIOC;
		gpio.GPIO_Pin = 10;
  }
	
	gpio.GPIO_Conf = AltOut_Ppull;
	MyGPIO_Init(&gpio);
	UARTStructPtr -> UART -> CR1 |= USART_CR1_UE ; //enable USART
	UARTStructPtr -> UART -> CR1 &=~ USART_CR1_M ; //set M bit to 0 -> parity disabled
	UARTStructPtr -> UART -> CR2 &=~ USART_CR2_STOP; //Set STOP to 00 -> 1 stop bit
	
	UARTStructPtr -> UART -> CR1 |= USART_CR1_TE; //send idle frame	
	UARTStructPtr -> UART -> CR1 |= USART_CR1_RE; //enable receiver
}

void MyUART_ActiveIT(USART_TypeDef * UART , char Prio , void (*IT_function)(void) ) {
	UART->CR1 |= USART_CR1_RXNEIE;
	if (UART == USART1){
		  NVIC_EnableIRQ(USART1_IRQn);
      NVIC_SetPriority(USART1_IRQn,Prio);
			pFuncUART1 = IT_function;
	}else if(UART == USART3){	
			NVIC_EnableIRQ(USART3_IRQn);
      NVIC_SetPriority(USART3_IRQn,Prio);
		  pFuncUART3 = IT_function;
	}
}


// Functions Handlers
void USART1_IRQHandler ( void ){
	//TIM1->SR &= ~(TIM_SR_UIF);
	if (pFuncUART1 != 0) (*pFuncUART1) (); /* appel indirect de la fonction */
}

void USART3_IRQHandler ( void ){
	//TIM2->SR &= ~(TIM_SR_UIF);
	if (pFuncUART3 != 0) (*pFuncUART3) (); /* appel indirect de la fonction */
}


void MyUART_PutStr ( USART_TypeDef * UART, char* String){
	// While in all the String
	while(*String != '\0'){
		while(!(UART->SR & USART_SR_TXE));

		UART->DR = *String; 
		String++;
	}
}

char MyUART_GetChar ( USART_TypeDef * UART ){
	return (signed char) UART->DR; 
}
