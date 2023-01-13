# simple-systick-arm4
One of my repositories for the 'Embedded Systems Object-Oriented Programming in C' course.

# about

I did some of the sections of the course 'Embedded Systems Object-Oriented Programming in C' and I am trying to put together all the valuable lessons learned in the course and in C language. I did not use keil IDE since using the 'ARM Compiler Version 5' was complex. Well, for the codes within this repositorie I don't think it would be a problem since we didn't use the *printf* function, but I rather to keep using the STM32CubeIDE. 

# lessons learned in the systick section

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

# lessons learned in the uart section

# lessons learned in gpio section
