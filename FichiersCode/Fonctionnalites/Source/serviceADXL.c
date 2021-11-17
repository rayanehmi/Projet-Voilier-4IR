#include "serviceADXL.h"
#include "stm32f10x.h"
#include "MySPI.h"

uint8_t reg ; 
uint8_t data ; 

void MyADXL_SendData(uint8_t reg, uint8_t data) {
	
	// Mise � 1 du Chip Select 
	MySPI_CS_On() ; 
	
	// Envoi du register  
	MySPI_ReadWrite(SPI1, reg) ;
	
	// Envoi des donn�es 
	MySPI_ReadWrite(SPI1, data) ;
	
	// Mise � 0 du Chip Select 
	MySPI_CS_Off() ; 
}


	
void MyADXL_Config(SPI_TypeDef * SPI) {
	
	// Construction de la trame � envoyer 
	// 1er bit � 0 car mode Write 
	// 2eme bit � 0 car bit MB � 0 pour lire une seule donn�e 
	// Adresse du POWER_CTL 
	reg = 0x2d ; 
	
	// Data � envoyer 
	data = 0x0 ; 
	
	// Envoi des donn�es 
	MyADXL_SendData(reg, data) ; 
	
	
	
	// Modification du format des donn�es 
	
	// Construction de la trame � envoyer 
	// 1er bit � 0 car mode Write 
	// 2eme bit � 0 car bit MB � 0 pour lire une seule donn�e 
	// Adresse du POWER_CTL 
	reg = 0x31 ; 
	
	// Data � envoyer 
	data = 0x1 ; 
	
	// Envoi des donn�es 
	MyADXL_SendData(reg, data) ; 
}

