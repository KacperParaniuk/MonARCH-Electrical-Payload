################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Src/gpio_driver.c \
../BSP/Src/iic_driver.c \
../BSP/Src/mosfet_ctrl.c \
../BSP/Src/spi_driver.c \
../BSP/Src/uart_handler.c 

OBJS += \
./BSP/Src/gpio_driver.o \
./BSP/Src/iic_driver.o \
./BSP/Src/mosfet_ctrl.o \
./BSP/Src/spi_driver.o \
./BSP/Src/uart_handler.o 

C_DEPS += \
./BSP/Src/gpio_driver.d \
./BSP/Src/iic_driver.d \
./BSP/Src/mosfet_ctrl.d \
./BSP/Src/spi_driver.d \
./BSP/Src/uart_handler.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Src/%.o BSP/Src/%.su BSP/Src/%.cyclo: ../BSP/Src/%.c BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../BSP/Sensors/Inc -I../Core/Inc -I../BSP/Inc -I../App/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Src

clean-BSP-2f-Src:
	-$(RM) ./BSP/Src/gpio_driver.cyclo ./BSP/Src/gpio_driver.d ./BSP/Src/gpio_driver.o ./BSP/Src/gpio_driver.su ./BSP/Src/iic_driver.cyclo ./BSP/Src/iic_driver.d ./BSP/Src/iic_driver.o ./BSP/Src/iic_driver.su ./BSP/Src/mosfet_ctrl.cyclo ./BSP/Src/mosfet_ctrl.d ./BSP/Src/mosfet_ctrl.o ./BSP/Src/mosfet_ctrl.su ./BSP/Src/spi_driver.cyclo ./BSP/Src/spi_driver.d ./BSP/Src/spi_driver.o ./BSP/Src/spi_driver.su ./BSP/Src/uart_handler.cyclo ./BSP/Src/uart_handler.d ./BSP/Src/uart_handler.o ./BSP/Src/uart_handler.su

.PHONY: clean-BSP-2f-Src

