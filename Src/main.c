#include "../drivers/Inc/gpio.h"
//#include "gpio.h"

GPIO_InitTypeDef myGPIO_InitStruct;

int main(void){
	__LIB_RCC_GPIOA_CLK_EN();

	myGPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	myGPIO_InitStruct.Pin = GPIO_PIN_5;
	myGPIO_InitStruct.Pull = GPIO_NOPULL;
	LIB_GPIO_Init(GPIOA, &myGPIO_InitStruct);

	while(1){
		for(int i=0;i<900000;i++){}
		LIB_GPIO_TooglePin(GPIOA, GPIO_PIN_5);
	}
}
