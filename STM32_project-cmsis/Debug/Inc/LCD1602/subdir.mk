################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/LCD1602/lcd1602_i2c.c 

OBJS += \
./Inc/LCD1602/lcd1602_i2c.o 

C_DEPS += \
./Inc/LCD1602/lcd1602_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/LCD1602/%.o Inc/LCD1602/%.su Inc/LCD1602/%.cyclo: ../Inc/LCD1602/%.c Inc/LCD1602/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-LCD1602

clean-Inc-2f-LCD1602:
	-$(RM) ./Inc/LCD1602/lcd1602_i2c.cyclo ./Inc/LCD1602/lcd1602_i2c.d ./Inc/LCD1602/lcd1602_i2c.o ./Inc/LCD1602/lcd1602_i2c.su

.PHONY: clean-Inc-2f-LCD1602

