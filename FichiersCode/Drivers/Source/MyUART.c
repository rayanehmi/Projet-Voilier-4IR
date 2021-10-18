#include "../Include/MyUART.h"

// Pointeurs de l'UART
void (* pFuncUART1) (void);
void (* pFuncUART3) (void);

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
		UART->DR = (int)*String; 
		String++;
	}
}
