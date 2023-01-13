/*
 * gpio.h
 *
 *  Created on: Jan 12, 2023
 *      Author: r.freitas
 */
// Note from class: to add implemented functions here at .h file, write 'inline':
//		static inline uint32_t cmpt_eff(Led_type me){ (*me->vptr->cmpt_eff)(me); }
// or:
// #define LED_GET_EFFI_VCALL(me) (*(me)->vptr->cmpt_eff)(me)
#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <stdint.h>

#define	PERIPH_BASE			0x40000000UL
#define AHB1PERIPH_BASE 	(PERIPH_BASE + 0x00020000UL)
#define RCC_BASE			(AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE			AHB1PERIPH_BASE
#define GPIOB_BASE			(AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE			(AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE			(AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE			(AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE			(AHB1PERIPH_BASE + 0x1C00UL)

#define __IO				volatile

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];
}GPIO_TypeDef;

typedef struct{
	__IO uint32_t CR;
	__IO uint32_t PLLCFGR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t AHB1RSTR;
	__IO uint32_t AHB2RSTR;
	     uint32_t RESERVED1;
	     uint32_t RESERVED2;
	__IO uint32_t APB1RSTR;
	__IO uint32_t APB2RSTR;
	     uint32_t RESERVED3[2];
	__IO uint32_t AHB1ENR;
	__IO uint32_t AHB2ENR;
	     uint32_t RESERVED4;
	     uint32_t RESERVED5;
	__IO uint32_t APB1ENR;
	__IO uint32_t APB2ENR;
	     uint32_t RESERVED6[2];
	__IO uint32_t AHB1LPENR;
	__IO uint32_t AHB2LPENR;
	     uint32_t RESERVED7[2];
	__IO uint32_t APB1LPENR;
	__IO uint32_t APB2LPENR;
	     uint32_t RESERVED8[2];
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	     uint32_t RESERVED9[2];
	__IO uint32_t SSCGR;
	__IO uint32_t PLLI2SCFGR;
	__IO uint32_t RESERVED10;
	__IO uint32_t DCKCFGR;
}RCC_TypeDef;

#define RCC		((RCC_TypeDef*)RCC_BASE) 		//Typecasted to the struct type
#define GPIOA	((GPIO_TypeDef*)GPIOA_BASE)		//This way I can use arrow operator
#define GPIOB	((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC	((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD	((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE	((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOH	((GPIO_TypeDef*)GPIOH_BASE)

#define GPIOA_EN	1<<0
#define GPIOB_EN	1<<1
#define GPIOC_EN	1<<2
#define GPIOD_EN	1<<3
#define GPIOE_EN	1<<4
#define GPIOH_EN	1<<7

#define GPIO_PIN_0		((uint16_t)0x0001)
#define GPIO_PIN_1		((uint16_t)0x0002)
#define GPIO_PIN_2		((uint16_t)0x0004)
#define GPIO_PIN_3		((uint16_t)0x0008)
#define GPIO_PIN_4		((uint16_t)0x0010)
#define GPIO_PIN_5		((uint16_t)0x0020)
#define GPIO_PIN_6		((uint16_t)0x0040)
#define GPIO_PIN_7		((uint16_t)0x0080)
#define GPIO_PIN_8		((uint16_t)0x0100)
#define GPIO_PIN_9		((uint16_t)0x0200)
#define GPIO_PIN_10		((uint16_t)0x0400)
#define GPIO_PIN_11		((uint16_t)0x0800)
#define GPIO_PIN_12		((uint16_t)0x1000)
#define GPIO_PIN_13		((uint16_t)0x2000)
#define GPIO_PIN_14		((uint16_t)0x4000)
#define GPIO_PIN_15		((uint16_t)0x8000)
#define GPIO_PIN_ALL	((uint16_t)0xFFFF)

#define GPIO_MODE_INPUT			0x00U
#define GPIO_MODE_OUTPUT_PP		0x01U
#define GPIO_MODE_OUTPUT_OP		0x11U
#define GPIO_MODE_AF_PP			0x02U // AF combined with PP
#define GPIO_MODE_AF_OD			0x12U // AF combined with OP

#define GPIO_NOPULL				0x00U
#define GPIO_PULLUP				0x01U
#define GPIO_PULLDOWN			0x02U

typedef struct{
	uint32_t Pin;
	uint32_t Mode;
	uint32_t Pull;
	uint32_t Speed;
	uint32_t Alternate;
}GPIO_InitTypeDef;

typedef enum{
	GPIO_PIN_RESET =0,
	GPIO_PIN_SET
}GPIO_PinState;


void LIB_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
GPIO_PinState LIB_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void LIB_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void LIB_GPIO_TooglePin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void __LIB_RCC_GPIOA_CLK_EN(void);
void __LIB_RCC_GPIOB_CLK_EN(void);
void __LIB_RCC_GPIOC_CLK_EN(void);
void __LIB_RCC_GPIOD_CLK_EN(void);
void __LIB_RCC_GPIOE_CLK_EN(void);
void __LIB_RCC_GPIOH_CLK_EN(void);

// LD2 is connected to PA5
#define MODER_5_OUT		(1<<10)
#define LED_PIN			(1<<5)

#endif /* INC_GPIO_H_ */
