################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proj/mcu_spec/adc_8263.c \
../proj/mcu_spec/adc_8266.c \
../proj/mcu_spec/adc_8267.c \
../proj/mcu_spec/gpio_8263.c \
../proj/mcu_spec/gpio_8266.c \
../proj/mcu_spec/gpio_8267.c \
../proj/mcu_spec/pwm_8263.c \
../proj/mcu_spec/pwm_8266.c \
../proj/mcu_spec/pwm_8267.c 

S_UPPER_SRCS += \
../proj/mcu_spec/cstartup_8261.S \
../proj/mcu_spec/cstartup_8263.S \
../proj/mcu_spec/cstartup_8263_ram.S \
../proj/mcu_spec/cstartup_8266.S \
../proj/mcu_spec/cstartup_8266_ram.S \
../proj/mcu_spec/cstartup_8267.S \
../proj/mcu_spec/cstartup_8267_ram.S \
../proj/mcu_spec/cstartup_8269.S \
../proj/mcu_spec/cstartup_8269_ram.S 

OBJS += \
./proj/mcu_spec/adc_8263.o \
./proj/mcu_spec/adc_8266.o \
./proj/mcu_spec/adc_8267.o \
./proj/mcu_spec/cstartup_8261.o \
./proj/mcu_spec/cstartup_8263.o \
./proj/mcu_spec/cstartup_8263_ram.o \
./proj/mcu_spec/cstartup_8266.o \
./proj/mcu_spec/cstartup_8266_ram.o \
./proj/mcu_spec/cstartup_8267.o \
./proj/mcu_spec/cstartup_8267_ram.o \
./proj/mcu_spec/cstartup_8269.o \
./proj/mcu_spec/cstartup_8269_ram.o \
./proj/mcu_spec/gpio_8263.o \
./proj/mcu_spec/gpio_8266.o \
./proj/mcu_spec/gpio_8267.o \
./proj/mcu_spec/pwm_8263.o \
./proj/mcu_spec/pwm_8266.o \
./proj/mcu_spec/pwm_8267.o 


# Each subdirectory must supply rules for building sources it contributes
proj/mcu_spec/%.o: ../proj/mcu_spec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Telink\code\sig_mesh_sdk\firmware" -D__PROJECT_8267_MASTER_KMA_DONGLE__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8269 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

proj/mcu_spec/%.o: ../proj/mcu_spec/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 CC/Assembler'
	tc32-elf-gcc -Xassembler"C:\Telink\code\sig_mesh_sdk\firmware" -DMCU_STARTUP_8267 -D__LOAD_RAM_SIZE__=0x12 -D__PROJECT_8267_MASTER_KMA_DONGLE__=1 -DCHIP_TYPE=CHIP_TYPE_8269 -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


