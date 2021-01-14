################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/012i2c_master_rx_test_IT.c \
../Src/sysmem.c 

OBJS += \
./Src/012i2c_master_rx_test_IT.o \
./Src/sysmem.o 

C_DEPS += \
./Src/012i2c_master_rx_test_IT.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/012i2c_master_rx_test_IT.o: ../Src/012i2c_master_rx_test_IT.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"/home/robert/Projects/Embedded-C/MCU drivers/target/stm32f446_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/012i2c_master_rx_test_IT.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"/home/robert/Projects/Embedded-C/MCU drivers/target/stm32f446_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

