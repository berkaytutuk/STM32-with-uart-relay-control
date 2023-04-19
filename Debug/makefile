################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
sade_otomasyon.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
sade_otomasyon.list \

OBJCOPY_BIN += \
sade_otomasyon.bin \


# All Target
all: sade_otomasyon.elf secondary-outputs

# Tool invocations
sade_otomasyon.elf: $(OBJS) $(USER_OBJS) C:\Users\tekno\Desktop\sade_otomasyon\STM32F030C8TX_FLASH.ld
	arm-none-eabi-gcc -o "sade_otomasyon.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\tekno\Desktop\sade_otomasyon\STM32F030C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="sade_otomasyon.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

sade_otomasyon.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "sade_otomasyon.list"
	@echo 'Finished building: $@'
	@echo ' '

sade_otomasyon.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "sade_otomasyon.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
