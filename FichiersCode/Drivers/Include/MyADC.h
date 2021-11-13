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


// Fonction d'initialisation -> Fonctionnement en mode continuous uniquement
// Valeurs possibles pour sample Time : 1.5, 7.5, 13.5, 28.5, 41.5, 55.5, 71.5, 239.5
void MyADC_Init(ADC_TypeDef * ADC, float sampleTime, char channel) ; 
int MyADC_Get(ADC_TypeDef * ADC);

// Macro start
#define MyADC_Start(ADC) (ADC->CR2 |= 0x1)

#endif 
