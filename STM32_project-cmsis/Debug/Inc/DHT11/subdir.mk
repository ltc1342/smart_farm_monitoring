################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/DHT11/DHT11.c 

OBJS += \
./Inc/DHT11/DHT11.o 

C_DEPS += \
./Inc/DHT11/DHT11.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/DHT11/%.o Inc/DHT11/%.su Inc/DHT11/%.cyclo: ../Inc/DHT11/%.c Inc/DHT11/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-DHT11

clean-Inc-2f-DHT11:
	-$(RM) ./Inc/DHT11/DHT11.cyclo ./Inc/DHT11/DHT11.d ./Inc/DHT11/DHT11.o ./Inc/DHT11/DHT11.su

.PHONY: clean-Inc-2f-DHT11

