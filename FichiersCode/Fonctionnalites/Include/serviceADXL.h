#ifndef SERVICEADXL_H
#define SERVICEADXL_H

#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"

// Fonction de configuration de l'ADXL345
void MyADXL_Config(SPI_TypeDef * SPI) ; 

#endif
