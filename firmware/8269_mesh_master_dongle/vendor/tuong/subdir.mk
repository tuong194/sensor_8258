################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/tuong/LD2410.c \
../vendor/tuong/OPT3001.c \
../vendor/tuong/func.c 

OBJS += \
./vendor/tuong/LD2410.o \
./vendor/tuong/OPT3001.o \
./vendor/tuong/func.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/tuong/%.o: ../vendor/tuong/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Telink\code\sig_mesh_sdk\firmware" -D__PROJECT_8267_MASTER_KMA_DONGLE__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8269 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


