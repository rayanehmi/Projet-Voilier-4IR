#include "../Include/Driver_GPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) { //page 112
	// Enable clock:
	if ( GPIOStructPtr->GPIO == GPIOA) RCC->APB2ENR |= (0x01 << 2);
	else if ( GPIOStructPtr->GPIO == GPIOB) RCC->APB2ENR |= (0x01 << 3);
	else if ( GPIOStructPtr->GPIO == GPIOC) RCC->APB2ENR |= (0x01 << 4);
	else if ( GPIOStructPtr->GPIO == GPIOD) RCC->APB2ENR |= (0x01 << 5);
	
	// Configure it (page 171):
	if (GPIOStructPtr->GPIO_Pin < 8) { //We use CRL in this case
		GPIOStructPtr->GPIO->CRL &=~ (0xF << (GPIOStructPtr->GPIO_Pin * 4) ); //Reset field
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4)); //Set field
	}
	else {
		GPIOStructPtr->GPIO->CRH &=~ (0xF << ((GPIOStructPtr ->GPIO_Pin - 8) * 4)); //Reset field
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr ->GPIO_Pin - 8) * 4)); //Set field
	}
}

int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) { // renvoie 0 ou autre chose different de 0
	return GPIO->ODR & (1 << GPIO_Pin); //page 172
} //Reads ODR of GPIO_Pin

void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ){ //page 172
	GPIO->BSRR = 0x1 << GPIO_Pin ; // 0x10 is the memory offset
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) { // page 172
	//if ( GPIO->BSRR & (1 << (GPIO_Pin) ) GPIO->BSRR &=~(1<<GPIO_Pin*0x10);  // disables the Set bit because Set has priority over Reset
	GPIO->BSRR = 0x1 << (GPIO_Pin + 16)  ;
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	/*
	if ( GPIO->ODR & (1 << (GPIO_Pin * 0xC)) ) GPIO->ODR &=~ (1 << (GPIO_Pin * 0xC) );
	// if ODR is set on 1, we set it back to 0
	else GPIO->ODR |= (1 << (GPIO_Pin * 0xC) );
	// else, we set it on 1
	*/
	GPIO->ODR = GPIO->ODR ^ (1 << GPIO_Pin); //bit flip using binary XOR
}
