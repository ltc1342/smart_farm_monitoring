################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/CMSIS/RTOS2/Source/os_systick.c \
../Inc/CMSIS/RTOS2/Source/os_tick_gtim.c \
../Inc/CMSIS/RTOS2/Source/os_tick_ptim.c 

OBJS += \
./Inc/CMSIS/RTOS2/Source/os_systick.o \
./Inc/CMSIS/RTOS2/Source/os_tick_gtim.o \
./Inc/CMSIS/RTOS2/Source/os_tick_ptim.o 

C_DEPS += \
./Inc/CMSIS/RTOS2/Source/os_systick.d \
./Inc/CMSIS/RTOS2/Source/os_tick_gtim.d \
./Inc/CMSIS/RTOS2/Source/os_tick_ptim.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/CMSIS/RTOS2/Source/%.o Inc/CMSIS/RTOS2/Source/%.su Inc/CMSIS/RTOS2/Source/%.cyclo: ../Inc/CMSIS/RTOS2/Source/%.c Inc/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-CMSIS-2f-RTOS2-2f-Source

clean-Inc-2f-CMSIS-2f-RTOS2-2f-Source:
	-$(RM) ./Inc/CMSIS/RTOS2/Source/os_systick.cyclo ./Inc/CMSIS/RTOS2/Source/os_systick.d ./Inc/CMSIS/RTOS2/Source/os_systick.o ./Inc/CMSIS/RTOS2/Source/os_systick.su ./Inc/CMSIS/RTOS2/Source/os_tick_gtim.cyclo ./Inc/CMSIS/RTOS2/Source/os_tick_gtim.d ./Inc/CMSIS/RTOS2/Source/os_tick_gtim.o ./Inc/CMSIS/RTOS2/Source/os_tick_gtim.su ./Inc/CMSIS/RTOS2/Source/os_tick_ptim.cyclo ./Inc/CMSIS/RTOS2/Source/os_tick_ptim.d ./Inc/CMSIS/RTOS2/Source/os_tick_ptim.o ./Inc/CMSIS/RTOS2/Source/os_tick_ptim.su

.PHONY: clean-Inc-2f-CMSIS-2f-RTOS2-2f-Source

