/*
 * SHT30.c
 *
 *  Created on: Jun 11, 2024
 *      Author: DELL
 */

#include"SHT30.h"



void get_temp_humi(void){
	u8 cmd_send_sht30[2]={0x2C, 0x06};
	u8 cmd_read_sht30[6]={0};

	i2c_write_series(CMD_SHT30,2,cmd_send_sht30,0);
	sleep_ms(1);

	i2c_read_series(ADDR_SHT30,0,cmd_read_sht30,6);

	uart_Send(cmd_read_sht30,6);
}

