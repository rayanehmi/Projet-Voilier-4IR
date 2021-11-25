#include "MyBordageAutomatique.h"
#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MySPI.h"
#include "serviceADXL.h"


char compare(SPI_TypeDef * SPI){


	// Recupere les donnees
	// Creation des messages pour recuperer les bons registres
	uint8_t req = 0;
	req = 1<<7; // Mode Read
	req = 1<<6; // Multiple bits
	req |= 0x34; // Adresse registre Y 0x34->0x37 a recuperer

	char res[4];

	/* To read or write multiple bytes in a single transmission, the 
	multiple-byte bit, located after the R/W bit in the first byte transfer 
	(MB in Figure 37 to Figure 39), must be set. After the register 
	addressing and the first byte of data, each subsequent set of clock 
	pulses (eight clock pulses) causes the ADXL345 to point to the 
	next register for a read or write. This shifting continues until the 
	clock pulses cease and CS is deasserted.
	*/
	
	MySPI_CS_On();
	for(int i=0;i<4;i++) {
		res[i]=MySPI_ReadWrite(SPI,req);
	}
	MySPI_CS_Off();

	// Y le premier -> bit poid faible
	int Y = (res[1]<<8) | res[0];
	// idem pour Z
	int Z = (res[3]<<8) | res[2];

	// Borner entre la valeur de tan de 40 et -40 °
	return -839<=(-1*(100 * Y)/(100*Z)) & 839>=(-1*(100 * Y)/(100*Z));
}


void antiChavirement(SPI_TypeDef * SPI){
	
	if (compare(SPI)){
		// lacher les voiles
	}
	
}



