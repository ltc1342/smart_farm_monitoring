################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/OLED/SH1106.c \
../Inc/OLED/fonts.c 

OBJS += \
./Inc/OLED/SH1106.o \
./Inc/OLED/fonts.o 

C_DEPS += \
./Inc/OLED/SH1106.d \
./Inc/OLED/fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/OLED/%.o Inc/OLED/%.su Inc/OLED/%.cyclo: ../Inc/OLED/%.c Inc/OLED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xB -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"D:/Personal/Studying/Embedded_Programming/STM32F411CEU6/cmsis_final_project/Inc/CMSIS/RTOS2/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-OLED

clean-Inc-2f-OLED:
	-$(RM) ./Inc/OLED/SH1106.cyclo ./Inc/OLED/SH1106.d ./Inc/OLED/SH1106.o ./Inc/OLED/SH1106.su ./Inc/OLED/fonts.cyclo ./Inc/OLED/fonts.d ./Inc/OLED/fonts.o ./Inc/OLED/fonts.su

.PHONY: clean-Inc-2f-OLED

