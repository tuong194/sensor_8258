/*
 * OPT3001.c
 *
 *  Created on: Jun 4, 2024
 *      Author: DELL
 */

#include "OPT3001.h"
#include "func.h"
#include "proj/common/printf.h"
u8 buff[20];
u8 buff1[20];



unsigned int get_lux(void){
	u16 lux_value;
	u8 i2c_tx_buff[2] = {0xC4, 0x10};
	u8 i2c_rx_buff[2] = {0};

	i2c_write_series(CONFIG_REGISTER,1,i2c_tx_buff,2); // config
	i2c_read_series(RESULT_REGISTER,1,i2c_rx_buff,2); // result

	lux_value = (i2c_rx_buff[0]<<8) | i2c_rx_buff[1];

	return lux_value;
}

unsigned int caculate_lux(uint32_t get_lux){
	unsigned int  lux = 0;
	unsigned int pow = 1;
	u8 lux_MSB = (get_lux>>12)&0x0F;      // R[3:0]
	unsigned lux_LSB = get_lux & 0xFFF;	  // R[11:0]
	for(u8 i =0; i<lux_MSB; i++){
		pow = pow*2;
	}
	lux = 0.01*pow*lux_LSB;
	sprintf(buff, "lux: %d bf\n", lux);
	uart_Send(buff,12);
	sleep_ms(5);
	unsigned int caculate = 2.205*lux - 44.573;

	sprintf(buff1, "lux: %d af\n", caculate);
	uart_Send(buff1,12);
	sleep_ms(5);
	if(caculate <=0) caculate = 0;
	else if(caculate > 10000) caculate = 9999;

	lux = caculate;

	return lux;
}









