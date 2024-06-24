/*
 * BH1750.c
 *
 *  Created on: Jun 11, 2024
 *      Author: DELL
 */

#include "BH1750.h"


u8 buff[20];
unsigned int get_lux_BH1750(void){
	unsigned int lux;
	unsigned int caculate_lux;
	u16 lux_value;

	u8 Send_I2C[1]={0x20};   // One Time H-Resolution Mode (1lx)
	u8 Read_I2C[2]={0};

	i2c_write_series(ADDR_WRITE,1,Send_I2C,1);
	sleep_ms(120);
	i2c_read_series(ADDR_READ,1,Read_I2C,2);

	lux_value = (Read_I2C[0] << 8) | Read_I2C[1];
	lux = lux_value / 1.2;

	caculate_lux = 3.831*lux+45.669;
	sprintf(buff, "lux: %d lx\n", lux);
	uart_Send(buff,13);

	return caculate_lux;
}
