################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/llsync/sdk_src/utils/ble_qiot_utils_base64.c \
../vendor/common/llsync/sdk_src/utils/ble_qiot_utils_hmac256.c \
../vendor/common/llsync/sdk_src/utils/ble_qiot_utils_log.c \
../vendor/common/llsync/sdk_src/utils/ble_qiot_utils_sha256.c 

OBJS += \
./vendor/common/llsync/sdk_src/utils/ble_qiot_utils_base64.o \
./vendor/common/llsync/sdk_src/utils/ble_qiot_utils_hmac256.o \
./vendor/common/llsync/sdk_src/utils/ble_qiot_utils_log.o \
./vendor/common/llsync/sdk_src/utils/ble_qiot_utils_sha256.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/llsync/sdk_src/utils/%.o: ../vendor/common/llsync/sdk_src/utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Telink\code\sig_mesh_sdk\firmware" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\mi_api\mijia_ble_api" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\mi_api\libs" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\sdk_src\include" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\include" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\cfg" -I"C:\Telink\code\sig_mesh_sdk\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


