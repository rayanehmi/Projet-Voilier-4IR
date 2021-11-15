#include "MyBordageAutomatique.h"
#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MySPI.h"
#include "serviceADXL.h"

// Declaration d'une structure SPI 
SPI_TypeDef * SPI1 ; 

// Configuration du SPI et de l'ADXLa
MySPI_Config(SPI1) ; 
MyADXL_Config(SPI1) ;

// 

