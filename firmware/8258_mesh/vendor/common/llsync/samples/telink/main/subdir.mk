################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/llsync/samples/telink/main/ble_qiot_template_vendor.c \
../vendor/common/llsync/samples/telink/main/ll_app_mesh.c 

OBJS += \
./vendor/common/llsync/samples/telink/main/ble_qiot_template_vendor.o \
./vendor/common/llsync/samples/telink/main/ll_app_mesh.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/llsync/samples/telink/main/%.o: ../vendor/common/llsync/samples/telink/main/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Telink\code\sig_mesh_sdk\firmware" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\mi_api\mijia_ble_api" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\mi_api\libs" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\sdk_src\include" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\include" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\cfg" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


