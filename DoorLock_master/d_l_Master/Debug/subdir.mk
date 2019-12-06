################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../delay.c \
../keypad.c \
../lcd.c \
../main.c \
../master.c \
../timer.c \
../uart.c 

OBJS += \
./delay.o \
./keypad.o \
./lcd.o \
./main.o \
./master.o \
./timer.o \
./uart.o 

C_DEPS += \
./delay.d \
./keypad.d \
./lcd.d \
./main.d \
./master.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


