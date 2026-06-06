################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/Core/Source/irq_ctrl_gic.c 

OBJS += \
./CMSIS/Core/Source/irq_ctrl_gic.o 

C_DEPS += \
./CMSIS/Core/Source/irq_ctrl_gic.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/Core/Source/%.o CMSIS/Core/Source/%.su CMSIS/Core/Source/%.cyclo: ../CMSIS/Core/Source/%.c CMSIS/Core/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Library/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/Core/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/Device/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2f-Core-2f-Source

clean-CMSIS-2f-Core-2f-Source:
	-$(RM) ./CMSIS/Core/Source/irq_ctrl_gic.cyclo ./CMSIS/Core/Source/irq_ctrl_gic.d ./CMSIS/Core/Source/irq_ctrl_gic.o ./CMSIS/Core/Source/irq_ctrl_gic.su

.PHONY: clean-CMSIS-2f-Core-2f-Source

