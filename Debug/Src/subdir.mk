################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/I2C.c \
../Src/LED.c \
../Src/UART.c \
../Src/gpio_init.c \
../Src/main.c \
../Src/mpu6050.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer.c 

OBJS += \
./Src/I2C.o \
./Src/LED.o \
./Src/UART.o \
./Src/gpio_init.o \
./Src/main.o \
./Src/mpu6050.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer.o 

C_DEPS += \
./Src/I2C.d \
./Src/LED.d \
./Src/UART.d \
./Src/gpio_init.d \
./Src/main.d \
./Src/mpu6050.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DNUCLEO_F091RC -DSTM32F091RCTx -DSTM32F091xC -c -I../Inc -I../CMSIS -O0 -ffunction-sections -fdata-sections -Wall -Werror -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/LED.cyclo ./Src/LED.d ./Src/LED.o ./Src/LED.su ./Src/UART.cyclo ./Src/UART.d ./Src/UART.o ./Src/UART.su ./Src/gpio_init.cyclo ./Src/gpio_init.d ./Src/gpio_init.o ./Src/gpio_init.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/mpu6050.cyclo ./Src/mpu6050.d ./Src/mpu6050.o ./Src/mpu6050.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src

