#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"

MyTimer_Struct_TypeDef timer;

int main(void){
	timer.TimId = TIM2;
	timer.ARR = 1435;
	timer.PSC = 1;
	
	TIM2->SMCR &=~ (TIM_SMCR_SMS);
	TIM2->SMCR |= TIM_SMCR_SMS_0;
	TIM2->SMCR |= TIM_SMCR_SMS_1;
	
	MyTimer_Base_Init(&timer);
	MyTimer_Base_Start(timer.TimId);
	while(1);
}
