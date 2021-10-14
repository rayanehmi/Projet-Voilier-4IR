#include "../Include/MyGPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) { //page 112
	// Enable clock (HERE NOT):
	//if ( GPIOStructPtr->GPIO == GPIOA) RCC->APB2ENR |= (0x01 << 2);
	//else if ( GPIOStructPtr->GPIO == GPIOB) RCC->APB2ENR |= (0x01 << 3);
	//else if ( GPIOStructPtr->GPIO == GPIOC) RCC->APB2ENR |= (0x01 << 4);
	//else if ( GPIOStructPtr->GPIO == GPIOD) RCC->APB2ENR |= (0x01 << 5);
	
	// Configure it (page 171):
	if (GPIOStructPtr->GPIO_Pin < 8) { //We use CRL in this case
		GPIOStructPtr->GPIO->CRL &=~ (0xF << (GPIOStructPtr->GPIO_Pin * 4) ); //Reset field
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4)); //Set field
	}
	else {
		GPIOStructPtr->GPIO->CRH &=~ (0xF << ((GPIOStructPtr ->GPIO_Pin - 8) * 4)); //Reset field
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr ->GPIO_Pin - 8) * 4)); //Set field
	}
	
	// If we use Pull Up or Pull Down we have to initialize the ODR bit
	if(GPIOStructPtr->GPIO_Conf == In_PullUp){
		GPIOStructPtr->GPIO->ODR |= 0x1 << GPIOStructPtr->GPIO_Pin;
	}else if(GPIOStructPtr -> GPIO_Conf == In_PullDown){
		GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);
	}
}

// Reads IDR of GPIO_Pin
int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	return GPIO->IDR & (1 << GPIO_Pin); //page 172
} 

// Set Bit of ODR (page 172)
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->ODR |= 0x1 << GPIO_Pin;
}

// Reset Bit of ODR (page 172)
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR &= ~(0x1 << GPIO_Pin);
}

// Toggle Bit of ODR with XOR
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= 0x1 << GPIO_Pin;
}
