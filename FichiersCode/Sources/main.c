#include "stm32f10x.h"
#include "MyBordageAutomatique.h"

int main(void){
	MyBordageAutomatique_setup();
	MyBordageAutomatique_start();

	while(1);
}
