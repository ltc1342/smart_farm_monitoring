################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/I2C/I2C.c 

OBJS += \
./Inc/I2C/I2C.o 

C_DEPS += \
./Inc/I2C/I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/I2C/%.o Inc/I2C/%.su Inc/I2C/%.cyclo: ../Inc/I2C/%.c Inc/I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-I2C

clean-Inc-2f-I2C:
	-$(RM) ./Inc/I2C/I2C.cyclo ./Inc/I2C/I2C.d ./Inc/I2C/I2C.o ./Inc/I2C/I2C.su

.PHONY: clean-Inc-2f-I2C

