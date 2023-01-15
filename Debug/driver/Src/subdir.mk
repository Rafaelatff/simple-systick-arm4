################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Src/gpio.c \
../driver/Src/systick.c 

OBJS += \
./driver/Src/gpio.o \
./driver/Src/systick.o 

C_DEPS += \
./driver/Src/gpio.d \
./driver/Src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Src/%.o driver/Src/%.su: ../driver/Src/%.c driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/Estudos/Udemy/My_workspace/target/simple-systick-arm4/driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-driver-2f-Src

clean-driver-2f-Src:
	-$(RM) ./driver/Src/gpio.d ./driver/Src/gpio.o ./driver/Src/gpio.su ./driver/Src/systick.d ./driver/Src/systick.o ./driver/Src/systick.su

.PHONY: clean-driver-2f-Src

