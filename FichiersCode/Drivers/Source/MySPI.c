#include "stm32f10x.h"
#include "MySPI.h"


////////// Configuring SPI in master mode //////////
void MySPI_Init(SPI_TypeDef * SPI) {
	// Clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; 
	
	// SPI_CR1 -> 3 4 5 bits pour définir serial clock baud rate 
	SPI->CR1 |= 0x100 << 3 ; 
	
	// Choisir bits CPOL et CPHA pour définir le mode de transfert de données 
	// CPOL et CPHA laissés à 0
	
	// Set le bit DFF pour définir format (8bits ou 16 bits)
	// DFF laissé à 0 car format de 8 bits 
	
	// Configurer LSBFIRST dans SPI_CR1 pour définir le format de la trame
	// Bits de poids fort en premier donc LSBFIRST laissé à 0
	
	// Set des bits SSM et SSI pour mettre le CS en mode software => à manipuler pour début et fin de récupération/envoi des données 
	SPI->CR1 |= SPI_CR1_SSM ; 
	SPI->CR1 |= SPI_CR1_SSI ; 
	
	// Set des bits MSTR et SPE
	SPI->CR1 |= SPI_CR1_MSTR ; 
	SPI->CR1 |= SPI_CR1_SPE ; 
	
}
