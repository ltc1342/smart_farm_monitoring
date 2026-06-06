################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/Source/ADC.c \
../Library/Source/BH1750.c \
../Library/Source/DHT11.c \
../Library/Source/GPIO.c \
../Library/Source/I2C.c \
../Library/Source/SH1106.c \
../Library/Source/USART.c \
../Library/Source/control.c \
../Library/Source/delay.c \
../Library/Source/fonts.c \
../Library/Source/relay.c 

OBJS += \
./Library/Source/ADC.o \
./Library/Source/BH1750.o \
./Library/Source/DHT11.o \
./Library/Source/GPIO.o \
./Library/Source/I2C.o \
./Library/Source/SH1106.o \
./Library/Source/USART.o \
./Library/Source/control.o \
./Library/Source/delay.o \
./Library/Source/fonts.o \
./Library/Source/relay.o 

C_DEPS += \
./Library/Source/ADC.d \
./Library/Source/BH1750.d \
./Library/Source/DHT11.d \
./Library/Source/GPIO.d \
./Library/Source/I2C.d \
./Library/Source/SH1106.d \
./Library/Source/USART.d \
./Library/Source/control.d \
./Library/Source/delay.d \
./Library/Source/fonts.d \
./Library/Source/relay.d 


# Each subdirectory must supply rules for building sources it contributes
Library/Source/%.o Library/Source/%.su Library/Source/%.cyclo: ../Library/Source/%.c Library/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DCMSIS_device_header="stm32f4xx.h"' -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Library/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/Core/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/Device/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/RTOS2/FreeRTOS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library-2f-Source

clean-Library-2f-Source:
	-$(RM) ./Library/Source/ADC.cyclo ./Library/Source/ADC.d ./Library/Source/ADC.o ./Library/Source/ADC.su ./Library/Source/BH1750.cyclo ./Library/Source/BH1750.d ./Library/Source/BH1750.o ./Library/Source/BH1750.su ./Library/Source/DHT11.cyclo ./Library/Source/DHT11.d ./Library/Source/DHT11.o ./Library/Source/DHT11.su ./Library/Source/GPIO.cyclo ./Library/Source/GPIO.d ./Library/Source/GPIO.o ./Library/Source/GPIO.su ./Library/Source/I2C.cyclo ./Library/Source/I2C.d ./Library/Source/I2C.o ./Library/Source/I2C.su ./Library/Source/SH1106.cyclo ./Library/Source/SH1106.d ./Library/Source/SH1106.o ./Library/Source/SH1106.su ./Library/Source/USART.cyclo ./Library/Source/USART.d ./Library/Source/USART.o ./Library/Source/USART.su ./Library/Source/control.cyclo ./Library/Source/control.d ./Library/Source/control.o ./Library/Source/control.su ./Library/Source/delay.cyclo ./Library/Source/delay.d ./Library/Source/delay.o ./Library/Source/delay.su ./Library/Source/fonts.cyclo ./Library/Source/fonts.d ./Library/Source/fonts.o ./Library/Source/fonts.su ./Library/Source/relay.cyclo ./Library/Source/relay.d ./Library/Source/relay.o ./Library/Source/relay.su

.PHONY: clean-Library-2f-Source

