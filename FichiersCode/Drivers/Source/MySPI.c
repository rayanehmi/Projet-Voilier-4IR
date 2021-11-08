#include "stm32f10x.h"
#include "MySPI.h"
#include "MyGPIO.h"

// Structures des pin utilis�es 
MyGPIO_Struct_TypeDef GPIO_PA4_NSS = {GPIOA, 4, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_PA5_SCK = {GPIOA, 5, AltOut_Ppull} ;
MyGPIO_Struct_TypeDef GPIO_PA6_MISO = {GPIOA, 6, In_PullDown} ;
MyGPIO_Struct_TypeDef GPIO_PA7_MOSI = {GPIOA, 7, AltOut_Ppull} ;


void MySPI_Config(SPI_TypeDef * SPI) {
	
	////////// Configuring SPI in master mode //////////
	// Clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; 
	
	// SPI_CR1 -> 3 4 5 bits pour d�finir serial clock baud rate 
	// fSCLK/16 pour avoir inferieur a 5Mhz limite du ADXL345
	SPI->CR1 |= 0x1 << 3 ; 
	SPI->CR1 |= 0x1 << 4 ; 
	SPI->CR1 |= 0x0 << 5 ; 
	
	// Choisir bits CPOL et CPHA pour d�finir le mode de transfert de donn�es 
	// Fonctionnement de l'ADXL en CPOL=1 et CPHA=1
	SPI->CR1 |= SPI_CR1_CPOL ; 
	SPI->CR1 |= SPI_CR1_CPHA ; 
	
	// Set le bit DFF pour d�finir format (8bits ou 16 bits)
	// DFF laiss� � 0 car format de 8 bits 
	
	// Configurer LSBFIRST dans SPI_CR1 pour d�finir le format de la trame
	// Bits de poids fort en premier donc LSBFIRST laiss� � 0
	
	// Set des bits SSM et SSI pour mettre le CS en mode software => � manipuler pour d�but et fin de r�cup�ration/envoi des donn�es 
	SPI->CR1 |= SPI_CR1_SSM ; 
	SPI->CR1 |= SPI_CR1_SSI ; 
	
	// Set des bits MSTR et SPE
	SPI->CR1 |= SPI_CR1_MSTR ; 
	SPI->CR1 |= SPI_CR1_SPE ; 
	
	
	// Initialisation des pins utilis�es //
	MyGPIO_Init(& GPIO_PA4_NSS) ; 
	MyGPIO_Init(& GPIO_PA5_SCK) ; 
	MyGPIO_Init(& GPIO_PA6_MISO) ; 
	MyGPIO_Init(& GPIO_PA7_MOSI) ; 
	
	
}


char MySPI_ReadWrite(SPI_TypeDef * SPI, char data) {
	int a ; // Return value
	
	// Write //
	while ((SPI->SR&SPI_SR_TXE)== 0) {
		// Tant que que le registre TXE est plein alors on attend avant 
	}
	SPI->DR = data ; 
	
	// Read //
	while ((SPI->SR&SPI_SR_RXNE)== 0) {
		// Tant qu'il n'y a rien � lire, on attend
	}
	a=SPI_DR_DR ; 
	
	return a ; 
}
