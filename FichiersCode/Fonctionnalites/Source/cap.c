#include "cap.h"
#include "MyTimer.h"
#include "MyGPIO.h"

void cap(){
	MyTimer_PWM(TIM3,1);
	// Sort sur un pin par defaut
	setCycle_PWM(TIM3,1,10);
	//rotation
	MyGPIO_Set(GPIOB,5);
	
}
