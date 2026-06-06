################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/RTOS2/Source/os_systick.c \
../CMSIS/RTOS2/Source/os_tick_gtim.c \
../CMSIS/RTOS2/Source/os_tick_ptim.c 

OBJS += \
./CMSIS/RTOS2/Source/os_systick.o \
./CMSIS/RTOS2/Source/os_tick_gtim.o \
./CMSIS/RTOS2/Source/os_tick_ptim.o 

C_DEPS += \
./CMSIS/RTOS2/Source/os_systick.d \
./CMSIS/RTOS2/Source/os_tick_gtim.d \
./CMSIS/RTOS2/Source/os_tick_ptim.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/RTOS2/Source/%.o CMSIS/RTOS2/Source/%.su CMSIS/RTOS2/Source/%.cyclo: ../CMSIS/RTOS2/Source/%.c CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Library/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/Core/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/Device/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2f-RTOS2-2f-Source

clean-CMSIS-2f-RTOS2-2f-Source:
	-$(RM) ./CMSIS/RTOS2/Source/os_systick.cyclo ./CMSIS/RTOS2/Source/os_systick.d ./CMSIS/RTOS2/Source/os_systick.o ./CMSIS/RTOS2/Source/os_systick.su ./CMSIS/RTOS2/Source/os_tick_gtim.cyclo ./CMSIS/RTOS2/Source/os_tick_gtim.d ./CMSIS/RTOS2/Source/os_tick_gtim.o ./CMSIS/RTOS2/Source/os_tick_gtim.su ./CMSIS/RTOS2/Source/os_tick_ptim.cyclo ./CMSIS/RTOS2/Source/os_tick_ptim.d ./CMSIS/RTOS2/Source/os_tick_ptim.o ./CMSIS/RTOS2/Source/os_tick_ptim.su

.PHONY: clean-CMSIS-2f-RTOS2-2f-Source

