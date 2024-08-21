################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIM/subdir.mk
-include MCAL/RCC/subdir.mk
-include MCAL/GPIO/subdir.mk
-include MCAL/EXTI/subdir.mk
-include HAL/ULTRA-SONIC/subdir.mk
-include HAL/RearCollision/subdir.mk
-include HAL/PID/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/BlindSpot/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ADAS_Features_GP.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ADAS_Features_GP.list \

OBJCOPY_HEX += \
ADAS_Features_GP.hex \

OBJCOPY_BIN += \
ADAS_Features_GP.bin \


# All Target
all: ADAS_Features_GP.elf secondary-outputs

# Tool invocations
ADAS_Features_GP.elf: $(OBJS) $(USER_OBJS) C:\Users\dell\STM32CubeIDE\workspace_1.4.0\ADAS_Features_GP\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "ADAS_Features_GP.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\dell\STM32CubeIDE\workspace_1.4.0\ADAS_Features_GP\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ADAS_Features_GP.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	arm-none-eabi-objdump -D ADAS_Features_GP.elf > ADAS_Features_GP.s 
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ADAS_Features_GP.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ADAS_Features_GP.list"
	@echo 'Finished building: $@'
	@echo ' '

ADAS_Features_GP.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "ADAS_Features_GP.hex"
	
	@echo 'Finished building: $@'
	@echo ' '

ADAS_Features_GP.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ADAS_Features_GP.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
