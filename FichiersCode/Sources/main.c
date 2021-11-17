//à faire : meilleure conversion hexa->dec , tourner dans l'autre sens

#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"

MyGPIO_Struct_TypeDef gpioPB8;
MyGPIO_Struct_TypeDef gpioPB5;
MyGPIO_Struct_TypeDef gpioPB0;
MyTimer_Struct_TypeDef tim4_chan3;
MyTimer_Struct_TypeDef tim3_chan3;
MyUART_Struct_TypeDef uart;
char controllerData;
int cycleMAX = 0;
int vitesseRotationPlateau =0;

void Callback(){
	controllerData = MyUART_GetChar(uart.UART);
	
	
	/* Starts listening on USART1 and sends rotation commands */
	/* For the moment, PWM uses TIM4-chan3(PB8) and rotationDirection uses PB5 */

		//Traitement
			vitesseRotationPlateau = (int) ((signed char)controllerData);
			//Commande
			if ( vitesseRotationPlateau <= 0)  {
				MyGPIO_Set(GPIOB,5);
				setCycle_PWM(TIM4,3,(-1)*vitesseRotationPlateau);
			}
			else {
				MyGPIO_Reset(GPIOB,5);
				setCycle_PWM(TIM4,3,vitesseRotationPlateau);
			}
}

int converterTetha(int t){
	return 20 + ((t * 80)/90);
}


int main(void){
	
	//UART1
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	//PB8
	gpioPB8.GPIO = GPIOB;
	gpioPB8.GPIO_Pin = 8;
	gpioPB8.GPIO_Conf = AltOut_Ppull;
	
	//PB5
	gpioPB5.GPIO = GPIOB;
	gpioPB5.GPIO_Pin = 5;
	gpioPB5.GPIO_Conf = Out_Ppull;
	
	//PB0
	gpioPB0.GPIO = GPIOB;
	gpioPB0.GPIO_Pin = 0;
	gpioPB0.GPIO_Conf = AltOut_Ppull;
	
	
	//TIM4 channel 3
	tim4_chan3.TimId=TIM4;
	tim4_chan3.ARR=100-1;
	tim4_chan3.PSC=1-1;
			
	//TIM3 channel 3
	tim3_chan3.TimId=TIM3;
	tim3_chan3.ARR=1200-1;
	tim3_chan3.PSC=1200-1;
	
	//Init
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback); 
	//MyUART_PutStr(uart.UART, "ssstringgg");
	MyGPIO_Init(&gpioPB8);
	MyGPIO_Init(&gpioPB5);
	MyGPIO_Init(&gpioPB0);
	MyTimer_Base_Init(&tim4_chan3);
	MyTimer_Base_Init(&tim3_chan3);
	MyTimer_PWM(TIM3,3);
	MyTimer_PWM(TIM4,3);
	MyTimer_Base_Start(TIM3);
	MyTimer_Base_Start(TIM4);
	setCycle_PWM_1000(TIM3,3,converterTetha(cycleMAX));
	/* Partie rotation plateau*/
	

	while(1){
		int temp = converterTetha(cycleMAX);
		setCycle_PWM_1000(TIM3,3,temp);
	}
	
}
