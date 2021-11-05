#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"

MyGPIO_Struct_TypeDef gpio;
MyUART_Struct_TypeDef uart;
char controllerData;
int vitesseRotationPlateau =0;

void Callback(){
	controllerData = MyUART_GetChar(uart.UART);
}

int main(void){
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback);
	//MyUART_PutStr(uart.UART, "ssstringgg");
	
	/* Partie rotation plateau*/
	
	MyTimer_PWM(TIM4,3);
	
	while(1){
		
		/* Starts listening on USART1 and sends rotation commands */
		/* For the moment, PWM uses TIM4-chan3(PB8) and rotationDirection uses PB5 */

		//Traitement
		//if ( (int)controllerData != vitesseRotationPlateau) { //If the command changed
			vitesseRotationPlateau = (int)controllerData;
			//Commande
			if (vitesseRotationPlateau<0) MyGPIO_Set(GPIOB,5);
			else MyGPIO_Reset(GPIOB,5);
			setCycle_PWM(TIM4,3,vitesseRotationPlateau);
		//}
		
	}
	
}
