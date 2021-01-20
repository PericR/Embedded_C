################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/014i2c_slave_tx_string_big.c \
../Src/sysmem.c 

OBJS += \
./Src/014i2c_slave_tx_string_big.o \
./Src/sysmem.o 

C_DEPS += \
./Src/014i2c_slave_tx_string_big.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/014i2c_slave_tx_string_big.o: ../Src/014i2c_slave_tx_string_big.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"/home/robert/Projects/Embedded-C/MCU drivers/target/stm32f446_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/014i2c_slave_tx_string_big.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"/home/robert/Projects/Embedded-C/MCU drivers/target/stm32f446_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

