#ifndef MYSPI_H
#define MYSPI_H

#include "stm32f10x.h"
#include "MyGPIO.h" 

// Fonction d'initialisation
void MySPI_Config(SPI_TypeDef * SPI) ; 

//Fonction d'écriture 
void MySPI_Write(SPI_TypeDef * SPI, uint8_t setup) ; 

// Fonction de lecture 
uint16_t MySPI_Read(SPI_TypeDef * SPI) ; 



// Structures des pin utilisées 
MyGPIO_Struct_TypeDef GPIO_PA4_NSS = {GPIOA, 4, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_PA5_SCK = {GPIOA, 5, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_PA6_MISO = {GPIOA, 6, In_PullDown} ;
MyGPIO_Struct_TypeDef GPIO_PA7_MOSI = {GPIOA, 7, AltOut_Ppull} ;


// Macro de gestion du Chip Select 
#define MySPI_CS_On(SPI) ()

#endif
