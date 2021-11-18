#include "MyBordageAutomatique.h"
#include "stm32f10x.h"

MyTimer_Struct_TypeDef timer;
MyGPIO_Struct_TypeDef gpio;

int count = 0;
void Callback(){
	count++;
}


void MyBordageAutomatique_setup(void){
	// Configuration of TIMER2
	timer.TimId = TIM1;
	timer.ARR = 1435;
	timer.PSC = 1;
	MyTimer_Base_Init(&timer);
	MyTimer_Enable_EncoderMode(timer.TimId);
	MyTimer_ActiveIT(TIM1, 0, Callback);
		
	// Using Channel1 and Channel2 of TIMER2 (Channel1 = PA0, Channel1 = PA1)
	gpio.GPIO = GPIOA;
	gpio.GPIO_Conf = In_PullDown;
	
	gpio.GPIO_Pin = 8;
	MyGPIO_Init(&gpio);
	
	gpio.GPIO_Pin = 9;
	MyGPIO_Init(&gpio);
	
	//gpio.GPIO_Pin = 2;
	//MyGPIO_Init(&gpio);
	
	// Configuration Encoder Mode in this two channels
	MyTimer_Set_EncoderMode(timer.TimId, 1);
	MyTimer_Set_EncoderMode(timer.TimId, 2);
}

void MyBordageAutomatique_start(void){
	MyTimer_Base_Start(TIM1);
}
