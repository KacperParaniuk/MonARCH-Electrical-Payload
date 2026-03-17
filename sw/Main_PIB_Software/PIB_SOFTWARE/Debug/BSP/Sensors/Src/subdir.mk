################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Sensors/Src/ad7124.c \
../BSP/Sensors/Src/ad7124_regs.c \
../BSP/Sensors/Src/ad7124_sensor.c \
../BSP/Sensors/Src/driver_ina226.c \
../BSP/Sensors/Src/max31856.c 

OBJS += \
./BSP/Sensors/Src/ad7124.o \
./BSP/Sensors/Src/ad7124_regs.o \
./BSP/Sensors/Src/ad7124_sensor.o \
./BSP/Sensors/Src/driver_ina226.o \
./BSP/Sensors/Src/max31856.o 

C_DEPS += \
./BSP/Sensors/Src/ad7124.d \
./BSP/Sensors/Src/ad7124_regs.d \
./BSP/Sensors/Src/ad7124_sensor.d \
./BSP/Sensors/Src/driver_ina226.d \
./BSP/Sensors/Src/max31856.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Sensors/Src/%.o BSP/Sensors/Src/%.su BSP/Sensors/Src/%.cyclo: ../BSP/Sensors/Src/%.c BSP/Sensors/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../BSP/Sensors/Inc -I../Core/Inc -I../BSP/Inc -I../App/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Sensors-2f-Src

clean-BSP-2f-Sensors-2f-Src:
	-$(RM) ./BSP/Sensors/Src/ad7124.cyclo ./BSP/Sensors/Src/ad7124.d ./BSP/Sensors/Src/ad7124.o ./BSP/Sensors/Src/ad7124.su ./BSP/Sensors/Src/ad7124_regs.cyclo ./BSP/Sensors/Src/ad7124_regs.d ./BSP/Sensors/Src/ad7124_regs.o ./BSP/Sensors/Src/ad7124_regs.su ./BSP/Sensors/Src/ad7124_sensor.cyclo ./BSP/Sensors/Src/ad7124_sensor.d ./BSP/Sensors/Src/ad7124_sensor.o ./BSP/Sensors/Src/ad7124_sensor.su ./BSP/Sensors/Src/driver_ina226.cyclo ./BSP/Sensors/Src/driver_ina226.d ./BSP/Sensors/Src/driver_ina226.o ./BSP/Sensors/Src/driver_ina226.su ./BSP/Sensors/Src/max31856.cyclo ./BSP/Sensors/Src/max31856.d ./BSP/Sensors/Src/max31856.o ./BSP/Sensors/Src/max31856.su

.PHONY: clean-BSP-2f-Sensors-2f-Src

