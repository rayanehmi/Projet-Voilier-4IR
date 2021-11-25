#include "MyBordageAutomatique.h"
#include "stm32f10x.h"

#define servoMIN 10
#define servoMAX 94

MyTimer_Struct_TypeDef timer1, timer2;
MyGPIO_Struct_TypeDef gpio, led;

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

void CallbackGirouette(){
		int girouette = (int) TIM2->CNT;
		int alpha = (girouette*360)/1440;
		int servoPWM = thetaToPWM (angleToTheta(alpha));
	
		if(MyGPIO_Read(GPIOA, 8)){
			TIM2->CNT &=~ (TIM_CNT_CNT);
		}
		setCycle1000_PWM(TIM3,3,servoPWM);
	
		
}


void MyBordageAutomatique_setup(void){
	// Configuration of TIMER1
	timer1.TimId = TIM1;
	timer1.ARR = 1440-1;
	timer1.PSC = 100-1;
	MyTimer_Base_Init(&timer1);
	MyTimer_ActiveIT(timer1.TimId, 0, CallbackGirouette);
	
	// Configuration of TIMER2
	timer2.TimId = TIM2;
	timer2.ARR = 1440;
	timer2.PSC = 1;
	MyTimer_Base_Init(&timer2);

	MyTimer_Enable_EncoderMode(timer2.TimId);
	
	// Using Channel1 and Channel2 of TIMER2 (Channel1 = PA0, Channel1 = PA1)
	gpio.GPIO = GPIOA;
	gpio.GPIO_Conf = In_PullDown;
	
	gpio.GPIO_Pin = 0;
	MyGPIO_Init(&gpio);
	
	gpio.GPIO_Pin = 1;
	MyGPIO_Init(&gpio);
	
	gpio.GPIO_Pin = 8;
	gpio.GPIO_Conf = Out_Ppull;
	MyGPIO_Init(&gpio);
	
	// Configuration Encoder Mode in this two channels
	MyTimer_Set_EncoderMode(timer2.TimId, 1);
	MyTimer_Set_EncoderMode(timer2.TimId, 2);
}

void MyBordageAutomatique_start(void){
	MyTimer_Base_Start(TIM1);
	MyTimer_Base_Start(TIM2);
}
