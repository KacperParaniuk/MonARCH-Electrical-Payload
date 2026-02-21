################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CPP/Src/main.cpp 

OBJS += \
./CPP/Src/main.o 

CPP_DEPS += \
./CPP/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
CPP/Src/%.o CPP/Src/%.su CPP/Src/%.cyclo: ../CPP/Src/%.cpp CPP/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"C:/dev/MonARCH_Payload_Electronics/Software/Test_PIB_Software/Dev_Code_STM32H745ZI-Q/CM7/CPP/Inc" -I"C:/dev/MonARCH_Payload_Electronics/Software/Test_PIB_Software/Dev_Code_STM32H745ZI-Q/CM7/CPP" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CPP-2f-Src

clean-CPP-2f-Src:
	-$(RM) ./CPP/Src/main.cyclo ./CPP/Src/main.d ./CPP/Src/main.o ./CPP/Src/main.su

.PHONY: clean-CPP-2f-Src

