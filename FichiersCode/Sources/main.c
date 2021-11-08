#include "stm32f10x.h"
#include "MyUART.h"
#include "MyGPIO.h"
#include "MyTimer.h"

MyTimer_Struct_TypeDef timer;
MyGPIO_Struct_TypeDef gpioA, gpioB;

int main(void){
	timer.TimId = TIM2;
	timer.ARR = 1435;
	timer.PSC = 1;
	MyTimer_Base_Init(&timer);
	
	// CC2S ET CC3S
	timer.TimId->CCMR1 |= TIM_CCMR1_CC1S;
	timer.TimId->CCMR2 |= TIM_CCMR1_CC2S;
	
	// IC2F ET IC3F
	timer.TimId->CCMR1 &=~ TIM_CCMR1_IC1F;
	timer.TimId->CCMR2 &=~ TIM_CCMR1_IC2F;
	
	// CC2P ET CC3P
	timer.TimId->CCER &=~ TIM_CCER_CC1P;
	timer.TimId->CCER &=~ TIM_CCER_CC2P;
	
	// CC2NP ET CC3NP
	timer.TimId->CCER &=~ TIM_CCER_CC1NP;
	timer.TimId->CCER &=~ TIM_CCER_CC2NP;
	
	// SMS
	timer.TimId->SMCR &=~ (TIM_SMCR_SMS);
	timer.TimId->SMCR |= TIM_SMCR_SMS_0;
	timer.TimId->SMCR |= TIM_SMCR_SMS_1;
	
	
	gpioA.GPIO = GPIOA;
	gpioA.GPIO_Pin = 0;
	gpioA.GPIO_Conf = In_PullDown;
	
	gpioB.GPIO = GPIOA;
	gpioB.GPIO_Pin = 1;
	gpioB.GPIO_Conf = In_PullDown;
	
	MyGPIO_Init(&gpioA);
	MyGPIO_Init(&gpioB);
	
	MyTimer_Base_Start(timer.TimId);
	
	while(1);
}
