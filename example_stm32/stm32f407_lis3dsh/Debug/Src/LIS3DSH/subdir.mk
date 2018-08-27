################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LIS3DSH/LIS3DSH.c 

OBJS += \
./Src/LIS3DSH/LIS3DSH.o 

C_DEPS += \
./Src/LIS3DSH/LIS3DSH.d 


# Each subdirectory must supply rules for building sources it contributes
Src/LIS3DSH/%.o: ../Src/LIS3DSH/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/neptunex/Documents/st_workspace/stm32f407_lis3dsh/Inc" -I"/Users/neptunex/Documents/st_workspace/stm32f407_lis3dsh/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/neptunex/Documents/st_workspace/stm32f407_lis3dsh/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/neptunex/Documents/st_workspace/stm32f407_lis3dsh/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/neptunex/Documents/st_workspace/stm32f407_lis3dsh/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


