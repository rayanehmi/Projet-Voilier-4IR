#include "MyBordageAutomatique.h"
#include "stm32f10x.h"

MyTimer_Struct_TypeDef timer;
MyGPIO_Struct_TypeDef gpio;

void MyBordageAutomatique_setup(void){
	// Configuration of TIMER2
	timer.TimId = TIM2;
	timer.ARR = 1435;
	timer.PSC = 1;
	MyTimer_Base_Init(&timer);
	MyTimer_Enable_EncoderMode(timer.TimId);
		
	// Using Channel1 and Channel2 of TIMER2 (Channel1 = PA0, Channel1 = PA1)
	gpio.GPIO = GPIOA;
	gpio.GPIO_Conf = In_PullDown;
	
	gpio.GPIO_Pin = 0;
	MyGPIO_Init(&gpio);
	
	gpio.GPIO_Pin = 1;
	MyGPIO_Init(&gpio);
	
	// Configuration Encoder Mode in this two channels
	MyTimer_Set_EncoderMode(timer.TimId, 1);
	MyTimer_Set_EncoderMode(timer.TimId, 2);
}

void MyBordageAutomatique_start(void){
	MyTimer_Base_Start(TIM2);
}
