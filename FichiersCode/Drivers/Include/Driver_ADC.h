#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"
#include "core_cm3.h" 

/*
<!> INUTILE POUR LE MOMENT <!>

// Structure enum 
typedef enum {CONT, SINGLE} T_CONFIG ;

// STRUCTURE 
typedef struct 
{
	ADC_TypeDef * ADC ; 
	T_CONFIG config ;
} MyADC_Struct_TypeDef ; 
*/ 

// Fonction d'initialisation 
void MyADC_Init(ADC_TypeDef * ADC) ;

// Fonction de configuration -> Fonctionnement en mode continuous uniquement
void MyADC_Config(ADC_TypeDef * ADC, unsigned char sampleTime, char channel) ; 

// Macro start
#define MyADC_Start(ADC) (ADC->CR2 |= 0x1)

#endif 