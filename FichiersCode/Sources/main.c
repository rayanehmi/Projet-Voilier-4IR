#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"

MyUART_Struct_TypeDef uart;
MyGPIO_Struct_TypeDef gpioPB8; //PWM plateau
MyTimer_Struct_TypeDef tim4_chan3;
MyGPIO_Struct_TypeDef gpioPB5; //sens plateau
MyGPIO_Struct_TypeDef gpioPA2; //batterie
MyTimer_Struct_TypeDef tim4_chan4;

char controllerData;
int vitesseRotationPlateau =0;
int batterie;

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

void echantillonADC(){ //interruption ADC
	batterie = MyADC_Get(ADC2); //rajouter coef pont etc
}

int main(void){
	
	//UART1
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	//PA1
	gpioPA2.GPIO = GPIOA;
	gpioPA2.GPIO_Pin = 2;
	gpioPA2.GPIO_Conf = In_Analog;
	
	//PB8
	gpioPB8.GPIO = GPIOB;
	gpioPB8.GPIO_Pin = 8;
	gpioPB8.GPIO_Conf = AltOut_Ppull;
	
	//PB5
	gpioPB5.GPIO = GPIOB;
	gpioPB5.GPIO_Pin = 5;
	gpioPB5.GPIO_Conf = Out_Ppull;
	
	//ADC10
	MyADC_Init(ADC1,71.5,2);
	MyADC_Start(ADC1);
	
	//TIM4 channel 3
	tim4_chan3.TimId=TIM4;
	tim4_chan3.ARR=100-1;
	tim4_chan3.PSC=1-1;
	
	//TIM4 channel 4
	tim4_chan3.TimId=TIM4;
	tim4_chan3.ARR=25000-1;
	tim4_chan3.PSC=28800-1;//freq : 0.1Hz (1 toutes les 10 secondes)
	
	//Init
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback); 
	//MyUART_PutStr(uart.UART, "ssstringgg");
	MyGPIO_Init(&gpioPB8);
	MyGPIO_Init(&gpioPB5);
	
	//TIM4
	MyTimer_Base_Init(&tim4_chan3);
	MyTimer_PWM(TIM4,3);

	MyTimer_Base_Init(&tim4_chan4);
	MyTimer_ActiveIT(TIM4,5,echantillonADC);
	MyTimer_Base_Start(TIM4);
	
	while(1){
			
	}
	
}
