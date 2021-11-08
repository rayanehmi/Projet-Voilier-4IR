#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"
#define BTV 1 //Battery Voltage Threshold
#define coefPont 13 //a changer?

MyUART_Struct_TypeDef uart;
MyGPIO_Struct_TypeDef gpioPB8; //PWM plateau
MyTimer_Struct_TypeDef tim4_chan3;
MyGPIO_Struct_TypeDef gpioPB5; //sens plateau
MyGPIO_Struct_TypeDef gpioPA2; //batterie
MyGPIO_Struct_TypeDef gpioPA3; //////////////////////////////batterie AFAC
MyTimer_Struct_TypeDef tim4_chan4;

char controllerData;
int vitesseRotationPlateau =0;
int batterie; int compteurBatterie;

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

void interruptTimer(){ 
	
	//envoi message toutes les 3 secondes
	MyUART_PutStr(uart.UART, "3 secondes sont passees.\n");
	
	//interruption ADC toutes les 30 secondes
	compteurBatterie++;
	if (compteurBatterie>=2){ //Verif batterie toutes les 3 * 10 = 30 secondes
		compteurBatterie = 0;
		batterie = MyADC_Get(ADC2) * 3.3 * coefPont / 1024; //see #define
		if (batterie < BTV * 100) { //Battery Voltage Threshold (see #define)
			MyUART_PutStr(uart.UART, "Alerte : Batterie faible.\n");
		}
	}
}

int main(void){
	
	//UART1
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	//PA1
	gpioPA2.GPIO = GPIOA;
	gpioPA2.GPIO_Pin = 2;
	gpioPA2.GPIO_Conf = In_Analog;
	
	/////////////////////////////////////PA3 : AFAC (partie tests batterie)
	gpioPA3.GPIO = GPIOA;
	gpioPA3.GPIO_Pin = 3;
	gpioPA3.GPIO_Conf = Out_Ppull;
	
	//PB8
	gpioPB8.GPIO = GPIOB;
	gpioPB8.GPIO_Pin = 8;
	gpioPB8.GPIO_Conf = AltOut_Ppull;
	
	//PB5
	gpioPB5.GPIO = GPIOB;
	gpioPB5.GPIO_Pin = 5;
	gpioPB5.GPIO_Conf = Out_Ppull;
	
	//ADC2
	MyADC_Init(ADC2,71.5,0);
	MyADC_Start(ADC2);
	
	//TIM4 channel 3
	tim4_chan3.TimId=TIM4;
	tim4_chan3.ARR=100-1;
	tim4_chan3.PSC=1-1;
	
	//TIM4 channel 4
	tim4_chan3.TimId=TIM4;
	tim4_chan3.ARR=14697-1;
	tim4_chan3.PSC=14697-1;//freq : 0.333Hz (1 toutes les 3 secondes)
	
	//Init
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback); 
	MyGPIO_Init(&gpioPB8);
	MyGPIO_Init(&gpioPB5);
	MyGPIO_Init(&gpioPA3);
	MyGPIO_Set(GPIOA, 3); ////////////////////////////AFAC
	
	//TIM4
	MyTimer_Base_Init(&tim4_chan3);
	MyTimer_PWM(TIM4,3);

	MyTimer_Base_Init(&tim4_chan4);
	MyTimer_ActiveIT(TIM4,5,interruptTimer);
	MyTimer_Base_Start(TIM4);
	
	while(1){
			
	}
	
}
