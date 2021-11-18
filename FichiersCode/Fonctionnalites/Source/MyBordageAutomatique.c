#include "MyBordageAutomatique.h"
#include "stm32f10x.h"

MyTimer_Struct_TypeDef timer1, timer2;
MyGPIO_Struct_TypeDef gpio, led;

int count = 0;
void Callback(){

}


void MyBordageAutomatique_setup(void){
	// Configuration of TIMER1
	timer1.TimId = TIM1;
	timer1.ARR = 7200-1;
	timer1.PSC = 1000-1;
	MyTimer_Base_Init(&timer1);
	MyTimer_ActiveIT(timer1.TimId, 0, Callback);
	
	// Configuration of TIMER2
	timer2.TimId = TIM2;
	timer2.ARR = 1440;
	timer2.PSC = 0;
	MyTimer_Base_Init(&timer2);

	MyTimer_Enable_EncoderMode(timer2.TimId);
	
	// Using Channel1 and Channel2 of TIMER2 (Channel1 = PA0, Channel1 = PA1)
	gpio.GPIO = GPIOA;
	gpio.GPIO_Conf = In_PullDown;
	
	gpio.GPIO_Pin = 0;
	MyGPIO_Init(&gpio);
	
	gpio.GPIO_Pin = 1;
	MyGPIO_Init(&gpio);
	
	//gpio.GPIO_Pin = 2;
	//MyGPIO_Init(&gpio);
	
	// Configuration Encoder Mode in this two channels
	MyTimer_Set_EncoderMode(timer2.TimId, 1);
	MyTimer_Set_EncoderMode(timer2.TimId, 2);
}

void MyBordageAutomatique_start(void){
	MyTimer_Base_Start(TIM1);
}
