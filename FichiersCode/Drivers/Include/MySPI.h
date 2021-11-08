#ifndef MYSPI_H
#define MYSPI_H

#include "stm32f10x.h"
#include "MyGPIO.h" 

// Fonction d'initialisation
void MySPI_Config(SPI_TypeDef * SPI) ; 

//Fonction d'�criture 
char MySPI_ReadWrite(SPI_TypeDef * SPI, char val) ; 





// Macro de gestion du Chip Select 
#define MySPI_CS_On(SPI) ()

#endif
