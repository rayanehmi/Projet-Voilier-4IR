#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#define ACCELMAX 10

MyGPIO_Struct_TypeDef gpioPB8;
MyGPIO_Struct_TypeDef gpioPB5;
MyTimer_Struct_TypeDef tim4_chan3;
MyUART_Struct_TypeDef uart;
char controllerData;
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

int diff;
void Callback2(){ //EXPERIMENTAL : Empeche des gros appels de courant
	controllerData = MyUART_GetChar(uart.UART);
	
	controllerData = (int) ((signed char) controllerData);
	diff = controllerData - vitesseRotationPlateau;
	if (diff > ACCELMAX) vitesseRotationPlateau=ACCELMAX; //si il veut accelerer trop vite //see #define
	else if (diff < -ACCELMAX) vitesseRotationPlateau=-ACCELMAX;
	else vitesseRotationPlateau = diff;
			//Commande
			if ( vitesseRotationPlateau <= 0)  {
				MyGPIO_Set(GPIOB,5);
				setCycle_PWM(TIM4,3,vitesseRotationPlateau);
			}
			else {
				MyGPIO_Reset(GPIOB,5);
				setCycle_PWM(TIM4,3,vitesseRotationPlateau);
			}
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
	
	//TIM4 channel 3
	tim4_chan3.TimId=TIM4;
		tim4_chan3.ARR=100-1;
			tim4_chan3.PSC=1-1;
	
	//Init
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback2); 
	//MyUART_PutStr(uart.UART, "ssstringgg");
	MyGPIO_Init(&gpioPB8);
	MyGPIO_Init(&gpioPB5);
	MyTimer_Base_Init(&tim4_chan3);
	MyTimer_PWM(TIM4,3);

	MyTimer_Base_Start(TIM4);

	while(1){
			
	}
	
}
