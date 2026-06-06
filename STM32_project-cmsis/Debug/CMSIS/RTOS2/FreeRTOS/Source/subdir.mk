################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/RTOS2/FreeRTOS/Source/clib_os.c \
../CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.c \
../CMSIS/RTOS2/FreeRTOS/Source/croutine.c \
../CMSIS/RTOS2/FreeRTOS/Source/event_groups.c \
../CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.c \
../CMSIS/RTOS2/FreeRTOS/Source/handlers.c \
../CMSIS/RTOS2/FreeRTOS/Source/list.c \
../CMSIS/RTOS2/FreeRTOS/Source/port.c \
../CMSIS/RTOS2/FreeRTOS/Source/queue.c \
../CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.c \
../CMSIS/RTOS2/FreeRTOS/Source/tasks.c \
../CMSIS/RTOS2/FreeRTOS/Source/timers.c 

OBJS += \
./CMSIS/RTOS2/FreeRTOS/Source/clib_os.o \
./CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.o \
./CMSIS/RTOS2/FreeRTOS/Source/croutine.o \
./CMSIS/RTOS2/FreeRTOS/Source/event_groups.o \
./CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.o \
./CMSIS/RTOS2/FreeRTOS/Source/handlers.o \
./CMSIS/RTOS2/FreeRTOS/Source/list.o \
./CMSIS/RTOS2/FreeRTOS/Source/port.o \
./CMSIS/RTOS2/FreeRTOS/Source/queue.o \
./CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.o \
./CMSIS/RTOS2/FreeRTOS/Source/tasks.o \
./CMSIS/RTOS2/FreeRTOS/Source/timers.o 

C_DEPS += \
./CMSIS/RTOS2/FreeRTOS/Source/clib_os.d \
./CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.d \
./CMSIS/RTOS2/FreeRTOS/Source/croutine.d \
./CMSIS/RTOS2/FreeRTOS/Source/event_groups.d \
./CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.d \
./CMSIS/RTOS2/FreeRTOS/Source/handlers.d \
./CMSIS/RTOS2/FreeRTOS/Source/list.d \
./CMSIS/RTOS2/FreeRTOS/Source/port.d \
./CMSIS/RTOS2/FreeRTOS/Source/queue.d \
./CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.d \
./CMSIS/RTOS2/FreeRTOS/Source/tasks.d \
./CMSIS/RTOS2/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/RTOS2/FreeRTOS/Source/%.o CMSIS/RTOS2/FreeRTOS/Source/%.su CMSIS/RTOS2/FreeRTOS/Source/%.cyclo: ../CMSIS/RTOS2/FreeRTOS/Source/%.c CMSIS/RTOS2/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DCMSIS_device_header="stm32f4xx.h"' -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/STM32_project-cmsis/Library/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/STM32_project-cmsis/CMSIS/Core/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/STM32_project-cmsis/CMSIS/Device/Include" -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/STM32_project-cmsis/CMSIS/RTOS2/FreeRTOS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2f-RTOS2-2f-FreeRTOS-2f-Source

clean-CMSIS-2f-RTOS2-2f-FreeRTOS-2f-Source:
	-$(RM) ./CMSIS/RTOS2/FreeRTOS/Source/clib_os.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/clib_os.d ./CMSIS/RTOS2/FreeRTOS/Source/clib_os.o ./CMSIS/RTOS2/FreeRTOS/Source/clib_os.su ./CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.d ./CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.o ./CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.su ./CMSIS/RTOS2/FreeRTOS/Source/croutine.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/croutine.d ./CMSIS/RTOS2/FreeRTOS/Source/croutine.o ./CMSIS/RTOS2/FreeRTOS/Source/croutine.su ./CMSIS/RTOS2/FreeRTOS/Source/event_groups.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/event_groups.d ./CMSIS/RTOS2/FreeRTOS/Source/event_groups.o ./CMSIS/RTOS2/FreeRTOS/Source/event_groups.su ./CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.d ./CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.o ./CMSIS/RTOS2/FreeRTOS/Source/freertos_evr.su ./CMSIS/RTOS2/FreeRTOS/Source/handlers.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/handlers.d ./CMSIS/RTOS2/FreeRTOS/Source/handlers.o ./CMSIS/RTOS2/FreeRTOS/Source/handlers.su ./CMSIS/RTOS2/FreeRTOS/Source/list.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/list.d ./CMSIS/RTOS2/FreeRTOS/Source/list.o ./CMSIS/RTOS2/FreeRTOS/Source/list.su ./CMSIS/RTOS2/FreeRTOS/Source/port.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/port.d ./CMSIS/RTOS2/FreeRTOS/Source/port.o ./CMSIS/RTOS2/FreeRTOS/Source/port.su ./CMSIS/RTOS2/FreeRTOS/Source/queue.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/queue.d ./CMSIS/RTOS2/FreeRTOS/Source/queue.o ./CMSIS/RTOS2/FreeRTOS/Source/queue.su ./CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.d ./CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.o ./CMSIS/RTOS2/FreeRTOS/Source/stream_buffer.su ./CMSIS/RTOS2/FreeRTOS/Source/tasks.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/tasks.d ./CMSIS/RTOS2/FreeRTOS/Source/tasks.o ./CMSIS/RTOS2/FreeRTOS/Source/tasks.su ./CMSIS/RTOS2/FreeRTOS/Source/timers.cyclo ./CMSIS/RTOS2/FreeRTOS/Source/timers.d ./CMSIS/RTOS2/FreeRTOS/Source/timers.o ./CMSIS/RTOS2/FreeRTOS/Source/timers.su

.PHONY: clean-CMSIS-2f-RTOS2-2f-FreeRTOS-2f-Source

