#include "stm32f10x.h"
#include "MySPI.h"
#include "MyGPIO.h"


void MySPI_Config(SPI_TypeDef * SPI) {
	
	////////// Configuring SPI in master mode //////////
	// Clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; 
	
	// SPI_CR1 -> 3 4 5 bits pour d�finir serial clock baud rate 
	// fSCLK/16 pour avoir inferieur a 5Mhz limite du ADXL345
	SPI->CR1 |= 0x011 << 3 ; 
	
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
	
	////////// Configuring ADXL345 in slave mode //////////
	
}
