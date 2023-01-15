#include "../driver/Inc/gpio.h"
#include "../driver/Inc/systick.h"
//#include "gpio.h"
//#include "systick.h"


GPIO_InitTypeDef myGPIO_InitStruct;

int main(void){
	__LIB_RCC_GPIOA_CLK_EN();

	myGPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	myGPIO_InitStruct.Pin = GPIO_PIN_5;
	myGPIO_InitStruct.Pull = GPIO_NOPULL;
	LIB_GPIO_Init(GPIOA, &myGPIO_InitStruct);

	while(1){
		SysTick_delay (2);
		LIB_GPIO_TooglePin(GPIOA, GPIO_PIN_5);
		SysTick_delay_ms (100);
		LIB_GPIO_TooglePin(GPIOA, GPIO_PIN_5);
	}
}
