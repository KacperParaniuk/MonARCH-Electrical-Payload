################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c 

OBJS += \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.o \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.o 

C_DEPS += \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.d \
./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/%.o Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/%.su Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/%.cyclo: ../Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/%.c Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../BSP/Sensors/Inc -I../Core/Inc -I../BSP/Inc -I../App/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src

clean-Core-2f-Src-2f-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src:
	-$(RM) ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.su ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.cyclo ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.d ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.o ./Core/Src/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.su

.PHONY: clean-Core-2f-Src-2f-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src

