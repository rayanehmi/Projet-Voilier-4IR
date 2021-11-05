#ifndef MYSPI_H
#define MYSPI_H

#include "stm32f10x.h"

// Fonction d'initialisation
void MySPI_Init(SPI_TypeDef * SPI) ; 

//Fonction d'écriture 
void MySPI_Write(SPI_TypeDef * SPI, uint8_t setup) ; 

// Fonction de lecture 
uint16_t MySPI_Read() ; 

#endif
