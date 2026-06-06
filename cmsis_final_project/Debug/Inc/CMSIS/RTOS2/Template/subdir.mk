################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/CMSIS/RTOS2/Template/cmsis_os1.c 

OBJS += \
./Inc/CMSIS/RTOS2/Template/cmsis_os1.o 

C_DEPS += \
./Inc/CMSIS/RTOS2/Template/cmsis_os1.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/CMSIS/RTOS2/Template/%.o Inc/CMSIS/RTOS2/Template/%.su Inc/CMSIS/RTOS2/Template/%.cyclo: ../Inc/CMSIS/RTOS2/Template/%.c Inc/CMSIS/RTOS2/Template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-CMSIS-2f-RTOS2-2f-Template

clean-Inc-2f-CMSIS-2f-RTOS2-2f-Template:
	-$(RM) ./Inc/CMSIS/RTOS2/Template/cmsis_os1.cyclo ./Inc/CMSIS/RTOS2/Template/cmsis_os1.d ./Inc/CMSIS/RTOS2/Template/cmsis_os1.o ./Inc/CMSIS/RTOS2/Template/cmsis_os1.su

.PHONY: clean-Inc-2f-CMSIS-2f-RTOS2-2f-Template

