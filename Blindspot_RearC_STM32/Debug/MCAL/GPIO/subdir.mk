################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO/GPIO_Driver.c 

OBJS += \
./MCAL/GPIO/GPIO_Driver.o 

C_DEPS += \
./MCAL/GPIO/GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPIO/GPIO_Driver.o: ../MCAL/GPIO/GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DUSE_FULL_ASSERT -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/HAL/BlindSpot" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/HAL/PID" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/HAL/RearCollision" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/HAL/ULTRA-SONIC" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/HAL/LCD" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/MCAL/EXTI" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/MCAL/GPIO" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/MCAL/RCC" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/MCAL/TIM" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/MCAL/UART" -I"C:/Users/dell/STM32CubeIDE/workspace_1.4.0/ADAS_Features_GP/HAL/LCD" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/GPIO/GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

