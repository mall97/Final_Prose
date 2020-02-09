################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/hsi.c \
../src/init.c \
../src/lcd.c \
../src/main.c \
../src/send.c \
../src/stm32f10x_it.c \
../src/syscalls.c 

OBJS += \
./src/adc.o \
./src/hsi.o \
./src/init.o \
./src/lcd.o \
./src/main.o \
./src/send.o \
./src/stm32f10x_it.o \
./src/syscalls.o 

C_DEPS += \
./src/adc.d \
./src/hsi.d \
./src/init.d \
./src/lcd.d \
./src/main.d \
./src/send.d \
./src/stm32f10x_it.d \
./src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"C:/Users/Miguel/workspace/3SO/inc" -I"C:/Users/Miguel/workspace/3SO/StdPeriph_Driver/inc" -I"C:/Users/Miguel/workspace/3SO/CMSIS/core" -I"C:/Users/Miguel/workspace/3SO/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


