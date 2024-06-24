/*
 * THEC.c
 *
 *  Created on: Jun 15, 2024
 *      Author: DELL
 */
#include "SM_THEC.h"

u8 buff[10]= {0};
u8 rx_buff[15]={0};
u8 tx_buff[10]={0};

void GPIO_Config_RS485(void){
	gpio_set_func(PIN_RS485,AS_GPIO);
	gpio_set_output_en(PIN_RS485,1);
	gpio_set_input_en(PIN_RS485,0);

}

void TX_Enable(void){    // RS485 receive
	gpio_write(PIN_RS485,1);
}
void RX_Enable(void){    // RS485 trans
	gpio_write(PIN_RS485,0);
}

uint16_t CRC_check(uint8_t *buff, uint16_t buff_length){
	uint16_t CRC = 0xFFFF;
	u8 i=0;
	while(buff_length--){
		CRC ^= *buff++;
		for(i = 0; i<8;i++){
			if(CRC & 0x01){
				CRC>>=1;
				CRC ^= 0xA001;
			}else{
				CRC>>=1;
			}
		}
	}
	return CRC;
}

void EC_Trans_Get_Humi(void){
	TX_Enable();
	//uart_dma_enable(0,1);
	uint16_t CRC_value = 0;

	buff[0] = 0x01;
	buff[1] = FUNC_READ;
	buff[2] = REG_TEMP_EC>>8;
	buff[3] = REG_TEMP_EC;
	buff[4] = 0x00;
	buff[5] = 0x01;

	CRC_value = CRC_check(&buff[0],6);

	buff[6] = CRC_value;
	buff[7] = CRC_value>>8;

	uart_dma_enable(0,1);
	uart_Send(buff,8);
	sleep_ms(10);
	uart_dma_enable(0,0);

//	uart_ndma_send_byte(buff[0]);
//	uart_ndma_send_byte(buff[1]);
//	uart_ndma_send_byte(buff[2]);
//	uart_ndma_send_byte(buff[3]);
//	uart_ndma_send_byte(buff[4]);
//	uart_ndma_send_byte(buff[5]);
//	uart_ndma_send_byte(buff[6]);
//	uart_ndma_send_byte(buff[7]);



}

void EC_Read_Humi(void){




	RX_Enable();
	uart_recbuff_init(&rx_buff[0],240 , &tx_buff[0]);
	uart_dma_enable(1,0);

	sleep_ms(100);

	uart_dma_enable(0,1);
	uart_Send(&rx_buff[4],7);
}




