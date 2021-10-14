#include "stm32f10x.h"
#include "Driver_ADC.h"

// Fonction d'initialisation 
void MyADC_Init(ADC_TypeDef * ADC) {
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ; 
	}
}



// Fonction de configuration -> Fonctionnement en mode continuous uniquement
void MyADC_Config(ADC_TypeDef * ADC, unsigned char sampleTime, char channel) {


}	


