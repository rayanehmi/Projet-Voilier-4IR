#include "stm32f10x.h"
#include "MySPI.h"


////////// Configuring SPI in master mode //////////
void MySPI_Init(SPI_TypeDef * SPI) {
	// Clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; 
	
	// SPI_CR1 -> 3 4 5 bits pour d�finir serial clock baud rate 
	SPI->CR1 |= 0x100 << 3 ; 
	
	// Choisir bits CPOL et CPHA pour d�finir le mode de transfert de donn�es 
	// CPOL et CPHA laiss�s � 0
	
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
	
}
