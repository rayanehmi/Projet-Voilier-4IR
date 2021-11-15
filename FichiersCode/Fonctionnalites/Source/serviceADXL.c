#include "serviceADXL.h"
#include "stm32f10x.h"
#include "MySPI.h"

uint8_t reg ; 
uint8_t data ; 

void MyADXL_SendData(uint8_t reg, uint8_t data) {
	
	// Mise à 1 du Chip Select 
	MySPI_CS_On() ; 
	
	// Envoi du register  
	MySPI_ReadWrite(SPI1, reg) ;
	
	// Envoi des données 
	MySPI_ReadWrite(SPI1, data) ;
	
	// Mise à 0 du Chip Select 
	MySPI_CS_Off() ; 
}


	
void MyADXL_Config(SPI_TypeDef * SPI) {
	
	// Construction de la trame à envoyer 
	// 1er bit à 0 car mode Write 
	// 2eme bit à 0 car bit MB à 0 pour lire une seule donnée 
	// Adresse du POWER_CTL 
	reg = 0x2d ; 
	
	// Data à envoyer 
	data = 0x0 ; 
	
	// Envoi des données 
	MyADXL_SendData(reg, data) ; 
	
	
	
	// Modification du format des données 
	
	// Construction de la trame à envoyer 
	// 1er bit à 0 car mode Write 
	// 2eme bit à 0 car bit MB à 0 pour lire une seule donnée 
	// Adresse du POWER_CTL 
	reg = 0x31 ; 
	
	// Data à envoyer 
	data = 0x1 ; 
	
	// Envoi des données 
	MyADXL_SendData(reg, data) ; 
}

