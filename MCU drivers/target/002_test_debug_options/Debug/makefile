################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
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
002_test_debug_options.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
002_test_debug_options.list \

OBJCOPY_BIN += \
002_test_debug_options.bin \


# All Target
all: 002_test_debug_options.elf secondary-outputs

# Tool invocations
002_test_debug_options.elf: $(OBJS) $(USER_OBJS) /home/robert/Projects/Embedded-C/MCU\ drivers/target/002_test_debug_options/STM32F446RETX_FLASH.ld
	arm-none-eabi-gcc -o "002_test_debug_options.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/robert/Projects/Embedded-C/MCU drivers/target/002_test_debug_options/STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="002_test_debug_options.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

002_test_debug_options.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "002_test_debug_options.list"
	@echo 'Finished building: $@'
	@echo ' '

002_test_debug_options.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "002_test_debug_options.bin"
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
