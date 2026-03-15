################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/no-OS/platform/stm32/stm32_delay.c \
../Drivers/no-OS/platform/stm32/stm32_gpio.c \
../Drivers/no-OS/platform/stm32/stm32_gpio_irq.c \
../Drivers/no-OS/platform/stm32/stm32_i2c.c \
../Drivers/no-OS/platform/stm32/stm32_spi.c 

OBJS += \
./Drivers/no-OS/platform/stm32/stm32_delay.o \
./Drivers/no-OS/platform/stm32/stm32_gpio.o \
./Drivers/no-OS/platform/stm32/stm32_gpio_irq.o \
./Drivers/no-OS/platform/stm32/stm32_i2c.o \
./Drivers/no-OS/platform/stm32/stm32_spi.o 

C_DEPS += \
./Drivers/no-OS/platform/stm32/stm32_delay.d \
./Drivers/no-OS/platform/stm32/stm32_gpio.d \
./Drivers/no-OS/platform/stm32/stm32_gpio_irq.d \
./Drivers/no-OS/platform/stm32/stm32_i2c.d \
./Drivers/no-OS/platform/stm32/stm32_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/no-OS/platform/stm32/%.o Drivers/no-OS/platform/stm32/%.su Drivers/no-OS/platform/stm32/%.cyclo: ../Drivers/no-OS/platform/stm32/%.c Drivers/no-OS/platform/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../BSP/Sensors/Inc -I"C:/dev/monarch-payload-interface-board/sw/Main_PIB_Software/PIB_SOFTWARE/Drivers/no-OS/platform/stm32" -I"C:/dev/monarch-payload-interface-board/sw/Main_PIB_Software/PIB_SOFTWARE/Drivers/no-OS/include" -I../Core/Inc -I../BSP/Inc -I../App/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-no-2d-OS-2f-platform-2f-stm32

clean-Drivers-2f-no-2d-OS-2f-platform-2f-stm32:
	-$(RM) ./Drivers/no-OS/platform/stm32/stm32_delay.cyclo ./Drivers/no-OS/platform/stm32/stm32_delay.d ./Drivers/no-OS/platform/stm32/stm32_delay.o ./Drivers/no-OS/platform/stm32/stm32_delay.su ./Drivers/no-OS/platform/stm32/stm32_gpio.cyclo ./Drivers/no-OS/platform/stm32/stm32_gpio.d ./Drivers/no-OS/platform/stm32/stm32_gpio.o ./Drivers/no-OS/platform/stm32/stm32_gpio.su ./Drivers/no-OS/platform/stm32/stm32_gpio_irq.cyclo ./Drivers/no-OS/platform/stm32/stm32_gpio_irq.d ./Drivers/no-OS/platform/stm32/stm32_gpio_irq.o ./Drivers/no-OS/platform/stm32/stm32_gpio_irq.su ./Drivers/no-OS/platform/stm32/stm32_i2c.cyclo ./Drivers/no-OS/platform/stm32/stm32_i2c.d ./Drivers/no-OS/platform/stm32/stm32_i2c.o ./Drivers/no-OS/platform/stm32/stm32_i2c.su ./Drivers/no-OS/platform/stm32/stm32_spi.cyclo ./Drivers/no-OS/platform/stm32/stm32_spi.d ./Drivers/no-OS/platform/stm32/stm32_spi.o ./Drivers/no-OS/platform/stm32/stm32_spi.su

.PHONY: clean-Drivers-2f-no-2d-OS-2f-platform-2f-stm32

