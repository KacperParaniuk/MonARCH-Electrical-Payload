################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Src/gpio_driver.c \
../BSP/Src/iic_driver.c \
../BSP/Src/mosfet_ctrl.c \
../BSP/Src/no_os_alloc.c \
../BSP/Src/no_os_dma.c \
../BSP/Src/no_os_eeprom.c \
../BSP/Src/no_os_gnss.c \
../BSP/Src/no_os_gpio.c \
../BSP/Src/no_os_i2c.c \
../BSP/Src/no_os_i3c.c \
../BSP/Src/no_os_irq.c \
../BSP/Src/no_os_mdio.c \
../BSP/Src/no_os_mutex.c \
../BSP/Src/no_os_pwm.c \
../BSP/Src/no_os_spi.c \
../BSP/Src/no_os_tdm.c \
../BSP/Src/no_os_timer.c \
../BSP/Src/no_os_trng.c \
../BSP/Src/no_os_uart.c \
../BSP/Src/no_os_util.c \
../BSP/Src/platform_support.c \
../BSP/Src/spi_support.c \
../BSP/Src/stm32_delay.c \
../BSP/Src/stm32_dma.c \
../BSP/Src/stm32_gpio.c \
../BSP/Src/stm32_gpio_irq.c \
../BSP/Src/stm32_i2c.c \
../BSP/Src/stm32_pwm.c \
../BSP/Src/stm32_spi.c \
../BSP/Src/stm32_timer.c \
../BSP/Src/stm32_uart.c \
../BSP/Src/uart_handler.c 

OBJS += \
./BSP/Src/gpio_driver.o \
./BSP/Src/iic_driver.o \
./BSP/Src/mosfet_ctrl.o \
./BSP/Src/no_os_alloc.o \
./BSP/Src/no_os_dma.o \
./BSP/Src/no_os_eeprom.o \
./BSP/Src/no_os_gnss.o \
./BSP/Src/no_os_gpio.o \
./BSP/Src/no_os_i2c.o \
./BSP/Src/no_os_i3c.o \
./BSP/Src/no_os_irq.o \
./BSP/Src/no_os_mdio.o \
./BSP/Src/no_os_mutex.o \
./BSP/Src/no_os_pwm.o \
./BSP/Src/no_os_spi.o \
./BSP/Src/no_os_tdm.o \
./BSP/Src/no_os_timer.o \
./BSP/Src/no_os_trng.o \
./BSP/Src/no_os_uart.o \
./BSP/Src/no_os_util.o \
./BSP/Src/platform_support.o \
./BSP/Src/spi_support.o \
./BSP/Src/stm32_delay.o \
./BSP/Src/stm32_dma.o \
./BSP/Src/stm32_gpio.o \
./BSP/Src/stm32_gpio_irq.o \
./BSP/Src/stm32_i2c.o \
./BSP/Src/stm32_pwm.o \
./BSP/Src/stm32_spi.o \
./BSP/Src/stm32_timer.o \
./BSP/Src/stm32_uart.o \
./BSP/Src/uart_handler.o 

C_DEPS += \
./BSP/Src/gpio_driver.d \
./BSP/Src/iic_driver.d \
./BSP/Src/mosfet_ctrl.d \
./BSP/Src/no_os_alloc.d \
./BSP/Src/no_os_dma.d \
./BSP/Src/no_os_eeprom.d \
./BSP/Src/no_os_gnss.d \
./BSP/Src/no_os_gpio.d \
./BSP/Src/no_os_i2c.d \
./BSP/Src/no_os_i3c.d \
./BSP/Src/no_os_irq.d \
./BSP/Src/no_os_mdio.d \
./BSP/Src/no_os_mutex.d \
./BSP/Src/no_os_pwm.d \
./BSP/Src/no_os_spi.d \
./BSP/Src/no_os_tdm.d \
./BSP/Src/no_os_timer.d \
./BSP/Src/no_os_trng.d \
./BSP/Src/no_os_uart.d \
./BSP/Src/no_os_util.d \
./BSP/Src/platform_support.d \
./BSP/Src/spi_support.d \
./BSP/Src/stm32_delay.d \
./BSP/Src/stm32_dma.d \
./BSP/Src/stm32_gpio.d \
./BSP/Src/stm32_gpio_irq.d \
./BSP/Src/stm32_i2c.d \
./BSP/Src/stm32_pwm.d \
./BSP/Src/stm32_spi.d \
./BSP/Src/stm32_timer.d \
./BSP/Src/stm32_uart.d \
./BSP/Src/uart_handler.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Src/%.o BSP/Src/%.su BSP/Src/%.cyclo: ../BSP/Src/%.c BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../BSP/Sensors/Inc -I../Core/Inc -I../BSP/Inc -I../App/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Src

clean-BSP-2f-Src:
	-$(RM) ./BSP/Src/gpio_driver.cyclo ./BSP/Src/gpio_driver.d ./BSP/Src/gpio_driver.o ./BSP/Src/gpio_driver.su ./BSP/Src/iic_driver.cyclo ./BSP/Src/iic_driver.d ./BSP/Src/iic_driver.o ./BSP/Src/iic_driver.su ./BSP/Src/mosfet_ctrl.cyclo ./BSP/Src/mosfet_ctrl.d ./BSP/Src/mosfet_ctrl.o ./BSP/Src/mosfet_ctrl.su ./BSP/Src/no_os_alloc.cyclo ./BSP/Src/no_os_alloc.d ./BSP/Src/no_os_alloc.o ./BSP/Src/no_os_alloc.su ./BSP/Src/no_os_dma.cyclo ./BSP/Src/no_os_dma.d ./BSP/Src/no_os_dma.o ./BSP/Src/no_os_dma.su ./BSP/Src/no_os_eeprom.cyclo ./BSP/Src/no_os_eeprom.d ./BSP/Src/no_os_eeprom.o ./BSP/Src/no_os_eeprom.su ./BSP/Src/no_os_gnss.cyclo ./BSP/Src/no_os_gnss.d ./BSP/Src/no_os_gnss.o ./BSP/Src/no_os_gnss.su ./BSP/Src/no_os_gpio.cyclo ./BSP/Src/no_os_gpio.d ./BSP/Src/no_os_gpio.o ./BSP/Src/no_os_gpio.su ./BSP/Src/no_os_i2c.cyclo ./BSP/Src/no_os_i2c.d ./BSP/Src/no_os_i2c.o ./BSP/Src/no_os_i2c.su ./BSP/Src/no_os_i3c.cyclo ./BSP/Src/no_os_i3c.d ./BSP/Src/no_os_i3c.o ./BSP/Src/no_os_i3c.su ./BSP/Src/no_os_irq.cyclo ./BSP/Src/no_os_irq.d ./BSP/Src/no_os_irq.o ./BSP/Src/no_os_irq.su ./BSP/Src/no_os_mdio.cyclo ./BSP/Src/no_os_mdio.d ./BSP/Src/no_os_mdio.o ./BSP/Src/no_os_mdio.su ./BSP/Src/no_os_mutex.cyclo ./BSP/Src/no_os_mutex.d ./BSP/Src/no_os_mutex.o ./BSP/Src/no_os_mutex.su ./BSP/Src/no_os_pwm.cyclo ./BSP/Src/no_os_pwm.d ./BSP/Src/no_os_pwm.o ./BSP/Src/no_os_pwm.su ./BSP/Src/no_os_spi.cyclo ./BSP/Src/no_os_spi.d ./BSP/Src/no_os_spi.o ./BSP/Src/no_os_spi.su ./BSP/Src/no_os_tdm.cyclo ./BSP/Src/no_os_tdm.d ./BSP/Src/no_os_tdm.o ./BSP/Src/no_os_tdm.su ./BSP/Src/no_os_timer.cyclo ./BSP/Src/no_os_timer.d ./BSP/Src/no_os_timer.o ./BSP/Src/no_os_timer.su ./BSP/Src/no_os_trng.cyclo ./BSP/Src/no_os_trng.d ./BSP/Src/no_os_trng.o ./BSP/Src/no_os_trng.su ./BSP/Src/no_os_uart.cyclo ./BSP/Src/no_os_uart.d ./BSP/Src/no_os_uart.o ./BSP/Src/no_os_uart.su ./BSP/Src/no_os_util.cyclo ./BSP/Src/no_os_util.d ./BSP/Src/no_os_util.o ./BSP/Src/no_os_util.su ./BSP/Src/platform_support.cyclo ./BSP/Src/platform_support.d ./BSP/Src/platform_support.o ./BSP/Src/platform_support.su ./BSP/Src/spi_support.cyclo ./BSP/Src/spi_support.d ./BSP/Src/spi_support.o ./BSP/Src/spi_support.su ./BSP/Src/stm32_delay.cyclo ./BSP/Src/stm32_delay.d ./BSP/Src/stm32_delay.o ./BSP/Src/stm32_delay.su ./BSP/Src/stm32_dma.cyclo ./BSP/Src/stm32_dma.d ./BSP/Src/stm32_dma.o ./BSP/Src/stm32_dma.su ./BSP/Src/stm32_gpio.cyclo ./BSP/Src/stm32_gpio.d ./BSP/Src/stm32_gpio.o ./BSP/Src/stm32_gpio.su ./BSP/Src/stm32_gpio_irq.cyclo ./BSP/Src/stm32_gpio_irq.d ./BSP/Src/stm32_gpio_irq.o ./BSP/Src/stm32_gpio_irq.su ./BSP/Src/stm32_i2c.cyclo ./BSP/Src/stm32_i2c.d ./BSP/Src/stm32_i2c.o ./BSP/Src/stm32_i2c.su ./BSP/Src/stm32_pwm.cyclo ./BSP/Src/stm32_pwm.d ./BSP/Src/stm32_pwm.o ./BSP/Src/stm32_pwm.su ./BSP/Src/stm32_spi.cyclo ./BSP/Src/stm32_spi.d ./BSP/Src/stm32_spi.o ./BSP/Src/stm32_spi.su ./BSP/Src/stm32_timer.cyclo ./BSP/Src/stm32_timer.d ./BSP/Src/stm32_timer.o ./BSP/Src/stm32_timer.su ./BSP/Src/stm32_uart.cyclo ./BSP/Src/stm32_uart.d ./BSP/Src/stm32_uart.o ./BSP/Src/stm32_uart.su ./BSP/Src/uart_handler.cyclo ./BSP/Src/uart_handler.d ./BSP/Src/uart_handler.o ./BSP/Src/uart_handler.su

.PHONY: clean-BSP-2f-Src

