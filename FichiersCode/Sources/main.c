#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "MyADC.h"
#define coefPont 2
#define BTV 1 
#define servoMIN 10
#define servoMAX 94

MyUART_Struct_TypeDef uart;
MyGPIO_Struct_TypeDef gpioPB8; //PWM plateau
MyTimer_Struct_TypeDef tim4_chan3;
MyGPIO_Struct_TypeDef gpioPB5; //sens plateau
MyGPIO_Struct_TypeDef gpioPB0; //PWM Servo
MyGPIO_Struct_TypeDef gpioPA2; //batterie (PA2)
MyTimer_Struct_TypeDef tim2_chan4;
MyTimer_Struct_TypeDef tim3_chan3; //Servo PWM

char controllerData;
int vitesseRotationPlateau =0;
int batterie; int compteurBatterie;
int compteur3s;
int servoPWM = 0;

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
	compteur3s++;
	if (compteur3s>=(5*3)){
		compteur3s=0;
		MyUART_PutStr(uart.UART, "3 secondes sont passees.\n");
	}
	
	//interruption ADC toutes les 30 secondes
	compteurBatterie++;
	if (compteurBatterie>=(5)){ //Verif batterie toutes les 30 secondes
		compteurBatterie = 0;
		batterie = MyADC_Get(ADC2) * 3.3 * coefPont / 1024; //see #define
		if (batterie < BTV * 100) { //Battery Voltage Threshold (see #define)
			MyUART_PutStr(uart.UART, "Alerte : Batterie faible.\n");
		}
	}
}

int girouetteToAngle (int a){
	return (a * 360) / 1440;
}

int angleToTheta (int a){
	if (a < 45) return 0;
	else return ( ( (a - 45) * 90 ) / 135 );
}

int thetaToPWM (int t){
	// f(x) = a x + b
	// a = (servoMIN - servoMAX) / 90 ; b = servoMAX
	return ( t * (servoMIN - servoMAX) / 90 ) + servoMAX;
}

int main(void){
	
	//UART1
	uart.UART = USART1;
	uart.UART_BaudRate = 9600;
	
	
	//PA2
	gpioPA2.GPIO = GPIOA;
	gpioPA2.GPIO_Pin = 2;
	gpioPA2.GPIO_Conf = In_Analog;
	
		//PB0
	gpioPB0.GPIO = GPIOB;
	gpioPB0.GPIO_Pin = 0;
	gpioPB0.GPIO_Conf = AltOut_Ppull;
	
	//PB8
	gpioPB8.GPIO = GPIOB;
	gpioPB8.GPIO_Pin = 8;
	gpioPB8.GPIO_Conf = AltOut_Ppull;
	
	//PB5
	gpioPB5.GPIO = GPIOB;
	gpioPB5.GPIO_Pin = 5;
	gpioPB5.GPIO_Conf = Out_Ppull;
	
	
	//ADC2 (PA2)
	MyADC_Init(ADC2,71.5,0);
	MyADC_Start(ADC2);
	
	
	//TIM4 channel 3
	tim4_chan3.TimId=TIM4;
	tim4_chan3.ARR=100-1;
	tim4_chan3.PSC=1-1;
	
	//TIM3 channel 3
	tim3_chan3.TimId=TIM3;
	tim3_chan3.ARR=1000-1;
	tim3_chan3.PSC=1440-1;//freq : 50Hz (période : 20ms)
	
	//TIM2 channel 4
	tim2_chan4.TimId=TIM2;
	tim2_chan4.ARR=3795-1;
	tim2_chan4.PSC=3795-1;//freq : 5Hz (1 toutes les 0.2 secondes)
	
	
	//Init
	MyUART_Init(&uart);
	MyUART_ActiveIT(uart.UART, 1, Callback); 
	MyGPIO_Init(&gpioPB8);
	MyGPIO_Init(&gpioPB5);
	MyGPIO_Init(&gpioPB0);
	
	//TIM4
	MyTimer_Base_Init(&tim4_chan3);
	MyTimer_PWM(TIM4,3);
	MyTimer_Base_Start(TIM4);
	
	//TIM3
	MyTimer_Base_Init(&tim3_chan3);
	MyTimer_PWM(TIM3,3);
	MyTimer_Base_Start(TIM3);
	
	//TIM2
	MyTimer_Base_Init(&tim2_chan4);
	MyTimer_ActiveIT(TIM2,5,interruptTimer); //5 = priority
	MyTimer_Base_Start(TIM2);

	
	while(1){
			setCycle1000_PWM(TIM3,3,servoPWM);
	}
	
}
