#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct{
	TIM_TypeDef * TimId; // TIM1 a TIM4
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef;



/*
*************************************************************************
				* @brief
				*				@param -> Parametre sous forme d'une structure (son adresse) contenant les
								informations de base
				*				@Note -> Fonction ? lancer syst?matiquement avant d'aller plus en d?tail dans les
								conf plus fines (PWM,codeurs inc...)
*/

void MyTimer_Base_Init( MyTimer_Struct_TypeDef * MyTimer ) ;


/**************************************************************************
		* @brief
		*				@param -> - TIM_TypeDef * Timer : Timer concerne
											- char Prio : de 0 a 15
		*				@Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************/

void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function)(void)) ; 



#define MyTimer_Base_Start(Timer) (Timer->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer)	(Timer->CR1 |= 0x0)

/***************************************************************************
	*	@brief
	*	@param	....
	*	@Note		Active le channel specifie suTimerr le timer specifie ???
	*					la gestion de la configuration I/O n'est pas faite dans cette fonction
	*					ni le reglage de la periode de la PWM (ARR, PSC)
**************************************************************************/
void MyTimer_PWM(TIM_TypeDef * Timer, char Channel);

void setCycle_PWM(TIM_TypeDef * Timer, char Channel, int cycle) ;

#endif

