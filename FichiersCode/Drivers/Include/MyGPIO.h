#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

typedef struct
{
GPIO_TypeDef * GPIO ;
char GPIO_Pin ; //numero de 0 a 15
char GPIO_Conf ; // voir ci dessous
} MyGPIO_Struct_TypeDef ;

#define In_Floating 0x7 // 0100
#define In_PullDown 0x8 // 1000 and PxODR register = 0
#define In_PullUp 0x8 // 1000 and PxODR register = 0
#define In_Analog 0x0 // 0000
#define Out_Ppull 0x1 // 00-01 (or 00-10 or 00-11 depending on max speed)
#define Out_OD 0x5 // 01-01 (or 01-10 or 01-11 depending on max speed)
#define AltOut_Ppull 0x9 // 10-01 (or 10-10 or 10-11 depending on max speed)
#define AltOut_OD 0x13 // 11-01 (or 11-10 or 11-11 depending on max speed)

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) ;
int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // renvoie 0 ou autre chose d i f f e r e n t de 0
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
#endif
