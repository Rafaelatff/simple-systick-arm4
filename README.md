# simple-systick-arm4
One of my repositories for the 'Embedded Systems Object-Oriented Programming in C' course.

# about

I did some of the sections of the course 'Embedded Systems Object-Oriented Programming in C' and I am trying to put together all the valuable lessons learned in the course and in C language. I did not use keil IDE since using the 'ARM Compiler Version 5' was complex. Well, for the codes within this repositorie I don't think it would be a problem since we didn't use the *printf* function, but I rather to keep using the STM32CubeIDE. 

# lessons learned in the systick section

**Important: the folder driver cannot be named drivers.**

The SysTick is a peripheral from ARM modules, so all the microcontrollers from all manufactures will have it assembled. To check the information about SysTick, the 'Cortex M4 Devices - Generic User Guide' (DUI0553) must be consulted.

SysTick can be very complex, but in this course it's in implemented in the most simple way. In the header file of SysTick (systick.h), a typedef struct was created with all the registers of SysTick.  

Here we can see the registers: 

![image](https://user-images.githubusercontent.com/58916022/212354006-b79e6914-6b7c-419f-8824-186f40257a6e.png)

And the code implemented for the structure that holds the SysTick registers:

```c
typedef struct{
__IOM uint32_t CSR;   	// Control and Status Register 	- 0x00 offset: 0xE000E010 + 0x0
__IOM uint32_t RVR;   	// Reload Value Register 	- 0x04 offset: 0xE000E010 + 0x4  
__IOM uint32_t CVR;   	// Current Value Register	- 0x08 offset: 0xE000E010 + 0x8    
__IM  uint32_t CALIB;	// Calibration Value Register	- 0x0C offset: 0xE000E010 + 0xC
}SysTick_TypeDef;
```

We also added macros for the 'volatile' type qualifier according to the 'Cortex M4 Devices - Generic User Guide'.

![image](https://user-images.githubusercontent.com/58916022/212356119-09076ecb-0ec4-48da-bd7f-64cd934956dd.png)

```c
#define __IOM volatile /*Read/Write structure member permission*/
#define __OM volatile /* Write only structure member permission*/
#define __IM volatile /*Read only structure member permission*/
```

And we added macros for the register addresses.

![image](https://user-images.githubusercontent.com/58916022/212356323-51566b99-a080-4f51-adbc-9601f27aa523.png)

```c
#define 		SCB_BASEADDR			    0xE000E008UL  /*System Control Base Address*/
#define 		SysTick_BASEADDR		  0xE000E010UL  /*SysTick Base Address*/
```

And finally, to use the arrow operator instead of the dot, we added the macro for the SysTick base address typecasted to the typedef struct. Just a different way of setting the registers. More informations and examples can be found in the 'lessons learned in gpio section' of this readme file.

```c
#define SysTick ((SysTick_Type *)SysTick_BASEADDR) /*SysTick configuration structure*/
```

In the source file of the driver (systick.c), que create the functions *SysTick_delay* (with delay in the house of seconds) and *SysTick_delay_ms* (delay of milliseconds).

First we configure the SysTick, by loading the value 16 M - 1 at RVR register. SysClk isn't configured, so SysClk is by default 16Mhz (16M cycles per second), so, for a 1 second delay, just run 16M cycles. SysTick is 24-bit timer, so, value cannot pass 0xFFFFFF (dec: 16777215).

![image](https://user-images.githubusercontent.com/58916022/212539069-399b966b-4f25-420b-abf4-dcea0a5bff42.png)

```c
void SysTick_delay(uint32_t sec){
/*Configure SysTick*/
SysTick->RVR =  16000000 -1;
```

After that, we clear the current value register (CVR), this clear the current value of SysTick counter. After write in the CVR, also clears the SYST_CSR COUNTFLAG bit to 0.

![image](https://user-images.githubusercontent.com/58916022/212539095-baca9dee-b8df-46ee-8d90-188a1a66ea4b.png)

```c
SysTick->CVR = 0; 
```

Then, we enable the systick, with no interrupt. By loading t (0b101) to register CSR, we enable the counter (bit field 0 with value 1), we configure to counting down to zero and to does not assert the SysTick exception request (bit field 0 with value 0) and configure to use processor clock (bit field 2 with value 1).

![image](https://user-images.githubusercontent.com/58916022/212539330-94754191-29d5-482e-be76-b3b170900a93.png)

```c
SysTick->CSR = 5;
```

And at last, we create a *for* loop to hold the time (by pooling) that the function receives (*sec*). The *while* loop holds the function only 1 second.
At the end of the time, we disble the counter.

```c
	for(uint32_t i=0;i<sec;i++){
	  while((SysTick->CSR &0x10000)== 0){} /*Wait until the COUNTFLAG is set*/
	}
	SysTick->CSR =0;  /*Stop the timer (En =0)*/
}
```

For the millisecond function, we do the same, but we configure the RV Register to 16000 -1.

Then, in the main, we just call the function and ask to toggle the LD2.

```c
	while(1){
		SysTick_delay (2);
		LIB_GPIO_TooglePin(GPIOA, GPIO_PIN_5);
		SysTick_delay_ms (100);
		LIB_GPIO_TooglePin(GPIOA, GPIO_PIN_5);
	}
```

# lessons learned in the uart section

Tera term = 9600 baud rate
---

uart.h

To use the 'arrow operator':

```c
#define		__IO			volatile
#define APB1PERIPH_BASE			(PERIPH_BASE +  0x00000000U)
#define USART2_BASE			    (APB1PERIPH_BASE + 0x4400U)

typedef struct
{
	__IO uint32_t SR;    /*USART Status Register*/
	__IO uint32_t DR;	 	/*USART Data Register*/
	__IO uint32_t BRR;   /*USART Buad rate register*/
	__IO uint32_t CR1;    /*USART Control Register 1*/
	__IO uint32_t CR2;    /*USART Control Register 2*/
	__IO uint32_t CR3;    /*USART Control Register 3*/

}USART_TypeDef;

#define	USART2	((USART_TypeDef *)USART2_BASE)
```
Then just type: USART2->SR

uart.c 

Simplifield lib codes (only send characteres):

```c
char LIB_UART_Read(void){
	while(!(USART2->SR & 0x0020)){}//Wait till character arrives
	return USART2->DR;
}

void LIB_UART_Write(int ch){
	while(!(USART2->SR & 0x0080)){} // Wait until Tx buffer empty
	USART2->DR = (ch & 0xFF);
}
```

# lessons learned in gpio section

For the GPIO config, the instructor used some functions together, like ALTERNATE_FUNCTION_OD and then ALTERNATE_FUNCTION_PP, OUTPUT_OD and then OUTPUT_PP. I still prefer the way seen before (by FastBit Academy).
