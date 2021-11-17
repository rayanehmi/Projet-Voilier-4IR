#ifndef MYSPI_H
#define MYSPI_H

#include "stm32f10x.h"
#include "MyGPIO.h" 

// Fonction d'initialisation
void MySPI_Config(SPI_TypeDef * SPI) ; 

//Fonction d'écriture 
char MySPI_ReadWrite(SPI_TypeDef * SPI, char val) ; 

// Fonctions de gestion du Chip Select 
void MySPI_CS_On(void) ; 

void MySPI_CS_Off(void) ; 

#endif
