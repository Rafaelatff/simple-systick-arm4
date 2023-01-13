/*
 * gpio.c
 *
 *  Created on: Jan 12, 2023
 *      Author: r.freitas
 */
#include "../drivers/Inc/gpio.h"
//#include "gpio.h"

#define GPIO_NUMBER			16U
#define GPIO_MODER_MODE0	0x3U<<0
#define GPIO_MODE			0x03U
#define GPIO_PUPDR_PUPDR0	0x3U<<0

void LIB_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init){
	// Local variables
	uint32_t position;
	uint32_t ioposition = 0x00U;
	uint32_t iocurrent = 0x00U;
	uint32_t temp = 0x00U;

	/* Configure the port pins */
	for(position = 0U; position < GPIO_NUMBER; position++){
		/* Get the IO position */
		ioposition = 0x01U << position;

		/* Get the current IO position */
		iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;
		if(iocurrent == ioposition){

		// AF combined with OP or PP (OTYPER)
		if((GPIO_Init->Mode == GPIO_MODE_AF_PP) || (GPIO_Init->Mode ==	GPIO_MODE_AF_OD)){
			temp = GPIOx->AFR[position >>3];
			temp &= ~(0xFU << ((uint32_t)(position & 0x07)* 4U));
			temp |= ((uint32_t)(GPIO_Init->Alternate <<((uint32_t)position & 0x07U)*4U));
			GPIOx->AFR[position>>3U] = temp;
		}

		/* Configure IO Direction mode (Input, Output) */
		temp = GPIOx->MODER;
		temp &= ~(GPIO_MODER_MODE0 << (position * 2U));
		temp |= ((GPIO_Init->Mode & GPIO_MODE) << (position * 2U));
		GPIOx->MODER = temp;

		// HERE THE SAME MUST BE IMPLEMENT WITH OUTPUT_OD and OUTPUT_PP
		// 8_Gpio_driver_lib_c_extended

		/* Activate the Pull-up or Pull down resistor for the current IO */
		temp = GPIOx->PUPDR;
		temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));
		temp |= ((GPIO_Init->Pull) << (position * 2U));
		GPIOx->PUPDR = temp;
		}
	}
}

GPIO_PinState LIB_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_PinState bitStatus;
	if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET){
		bitStatus = GPIO_PIN_SET;
	} else {
		bitStatus = GPIO_PIN_RESET;
	}
	return bitStatus;
}
void LIB_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){
	if(PinState != GPIO_PIN_RESET){
		GPIOx->BSRR = GPIO_Pin;
	} else{
		//32 bit register being:
		//fields 0 to 15 set bits
		//fields 16 to 31 reset bits
		GPIOx->BSRR = (uint32_t)GPIO_Pin<<16;
	}
}

void LIB_GPIO_TooglePin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIOx->ODR ^= GPIO_Pin;
}

void __LIB_RCC_GPIOA_CLK_EN(void){
	RCC->AHB1ENR |= GPIOA_EN;
}
void __LIB_RCC_GPIOB_CLK_EN(void){
	RCC->AHB1ENR |= GPIOB_EN;
}
void __LIB_RCC_GPIOC_CLK_EN(void){
	RCC->AHB1ENR |= GPIOC_EN;
}
void __LIB_RCC_GPIOD_CLK_EN(void){
	RCC->AHB1ENR |= GPIOD_EN;
}
void __LIB_RCC_GPIOE_CLK_EN(void){
	RCC->AHB1ENR |= GPIOE_EN;
}
void __LIB_RCC_GPIOH_CLK_EN(void){
	RCC->AHB1ENR |= GPIOH_EN;
}
