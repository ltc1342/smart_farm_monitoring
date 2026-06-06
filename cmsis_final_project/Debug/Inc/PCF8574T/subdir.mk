################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/PCF8574T/PCF8574T.c 

OBJS += \
./Inc/PCF8574T/PCF8574T.o 

C_DEPS += \
./Inc/PCF8574T/PCF8574T.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/PCF8574T/%.o Inc/PCF8574T/%.su Inc/PCF8574T/%.cyclo: ../Inc/PCF8574T/%.c Inc/PCF8574T/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-PCF8574T

clean-Inc-2f-PCF8574T:
	-$(RM) ./Inc/PCF8574T/PCF8574T.cyclo ./Inc/PCF8574T/PCF8574T.d ./Inc/PCF8574T/PCF8574T.o ./Inc/PCF8574T/PCF8574T.su

.PHONY: clean-Inc-2f-PCF8574T

