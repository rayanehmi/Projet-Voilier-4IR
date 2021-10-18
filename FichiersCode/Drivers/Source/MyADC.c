#include "stm32f10x.h"
#include "Driver_ADC.h"

// Fonction d'initialisation 
void MyADC_Init(ADC_TypeDef * ADC, float sampleTime, char channel) {
	if (ADC == ADC1) {
		// Clock = 
		RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6 ; 
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
	} else if (ADC == ADC2) {
		RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6 ; 
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ; 
	}
	
	// ADON 
	ADC->CR2 |= 0x1 ; 
	
		// Channel 
	ADC->SQR1 &= 0 ;
	ADC->SQR3 |= channel ; // Channel 13
	
	// Configuration sample time
	if (channel>9){
		if (sampleTime == 1.5) {
			// valeur par défaut 
		} else if (sampleTime == 7.5) {
			ADC->SMPR1 |= 1 <<(channel-10)*3 ;  
		} else if (sampleTime == 13.5) {
			ADC->SMPR1 |= 2 <<(channel-10)*3;  
		} else if (sampleTime == 28.5) {
			ADC->SMPR1 |= 3 <<(channel-10)*3;  
		} else if (sampleTime == 41.5) {
			ADC->SMPR1 |= 4 <<(channel-10)*3;  
		} else if (sampleTime == 55.5) {
			ADC->SMPR1 |= 5 <<(channel-10)*3;  
		} else if (sampleTime == 71.5) {
			ADC->SMPR1 |= 6 <<(channel-10)*3;  
		} else if (sampleTime == 239.5) {
			ADC->SMPR1 |= 7 <<(channel-10)*3;  
		}
	}else{
		if (sampleTime == 1.5) {
		// valeur par défaut 
	} else if (sampleTime == 7.5) {
		ADC->SMPR2 |= 1 <<channel*3;  
	} else if (sampleTime == 13.5) {
		ADC->SMPR2 |= 2 <<channel*3;  
	} else if (sampleTime == 28.5) {
		ADC->SMPR2 |= 3 <<channel*3;  
	} else if (sampleTime == 41.5) {
		ADC->SMPR2 |= 4 <<channel*3;  
	} else if (sampleTime == 55.5) {
		ADC->SMPR2 |= 5 <<channel*3;  
	} else if (sampleTime == 71.5) {
		ADC->SMPR2 |= 6 <<channel*3;  
	} else if (sampleTime == 239.5) {
		ADC->SMPR2 |= 7 <<channel*3;  
	}
	}
	
	// Configuration mode continu
	// Continuous mode set
	ADC->CR2 |= 0x1 << 1;
}



