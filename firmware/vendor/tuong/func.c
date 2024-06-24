/*
 * func.c
 *
 *  Created on: Jun 5, 2024
 *      Author: DELL
 */

#include "OPT3001.h"
#include"LD2410.h"
#include "func.h"

extern u8 get_fw_ota_value();

u8 check_OTA;
u8 flag_busy;
u8 buff_flash[10];

u8 check_press;
u8 start_init_flag = 0;


u8 blink_led_flag = 0;;
u32 time_motion;
u32 time_light_sensor;
u32 start_time_init;

unsigned int luxa;


void init_value(void){
	start_time_init = pm_get_32k_tick();
	OFF_LED_GREEN;
	Read_Data_Flash();
}

void start_init(void){
	if(!start_init_flag){
		if(pm_get_32k_tick() - start_time_init >= 32000*10){
			set_up_config(SET_CONFIG);
			start_init_flag = 1;
		}
	}
}
void Write_Data_Flash(void){
	flash_erase_sector(MY_ADDR_FLASH);
	buff_flash[0] = checkprovision;
	flash_write_page(MY_ADDR_FLASH, 1, buff_flash);

}
void Read_Data_Flash(void){
	flash_read_page(MY_ADDR_FLASH, 1, buff_flash);
	checkprovision = buff_flash[0];
}

void Pin_Config(void){
	gpio_set_func(LED_RED,AS_GPIO);
	gpio_set_output_en(LED_RED,1);

	gpio_set_func(LED_GREEN,AS_GPIO);
	gpio_set_output_en(LED_GREEN,1);

	gpio_set_func(SW,AS_GPIO);
	gpio_set_input_en(SW,1);
	gpio_setup_up_down_resistor(SW,PM_PIN_PULLUP_1M);

	gpio_set_func(MOTION,AS_GPIO);
	gpio_set_input_en(MOTION,1);
	gpio_setup_up_down_resistor(MOTION,PM_PIN_PULLUP_10K);
}



void Blink_Led_Red(void){
	ON_LED_RED;
	sleep_ms(200);
	wd_clear();
	OFF_LED_RED;
	sleep_ms(200);
	wd_clear();
}

void Blink_Led_Green(void){
	ON_LED_GREEN;
	sleep_ms(200);
	wd_clear();
	OFF_LED_GREEN;
	sleep_ms(200);
	wd_clear();
}

void Provision(void){
	if(get_provision_state() == STATE_DEV_PROVING){
		flag_busy = 1;
		ON_LED_RED;
		ON_LED_GREEN;
	}else if(get_provision_state() == STATE_DEV_PROVED){

		if(!checkprovision){
			checkprovision = 1;
			OFF_LED_RED;
			OFF_LED_GREEN;
			Write_Data_Flash();
		}
		flag_busy = 0;
	}
}

u8 SW_press(void){
	if(!gpio_read(SW)){
		flag_busy = 1;
		check_press = 1;
	}
	else if(gpio_read(SW)){
		if(check_press){
			check_press = 0;
			flag_busy = 0;
			OFF_LED_GREEN;
			return 1;
		}
	}
	return 0;
}

void SW_kick_out(void){

	if(!gpio_read(SW)){ // reset
		if(checkprovision){
			ON_LED_GREEN;
			if(pm_get_32k_tick() - nowtime >= 32000*5){
				kick_out(0);
			}
		}else if(checkprovision == 0){

			if(pm_get_32k_tick() - nowtime >= 32000*5){
				kick_out(0);
			}
		}
	}else {
		nowtime = pm_get_32k_tick();

	}
}



void motion(void){
	if(!flag_busy){
		u8 stt_sensor;
		stt_sensor = gpio_read(MOTION);

		if(stt_sensor != 0){
			if(blink_led_flag == 0){
				if(checkprovision == 1){
					Blink_Led_Green();
				}else if(checkprovision == 0){
					Blink_Led_Red();
				}
			    blink_led_flag = 1;
			}
			time_motion = pm_get_32k_tick();

		}else if(!stt_sensor){
			if(blink_led_flag){
				if(pm_get_32k_tick() - time_motion >= 32000*6){
					if(checkprovision == 1){
						Blink_Led_Green();
					}else if(checkprovision == 0){
						Blink_Led_Red();
					}
					blink_led_flag = 0;
				}

			}

		}
	}

}

void compare_lux(void){
	if((pm_get_32k_tick() - time_light_sensor > 20000) && flag_busy == 0){
		unsigned int sub = 0;
		unsigned int rsp_lux = get_lux();
		unsigned int lux = caculate_lux(rsp_lux);
		if(lux > luxa){
			sub = lux - luxa;
		}else{
			sub = luxa - lux;
		}
		if(sub > 30){
			luxa = lux;
			Blink_Led_Green();
		}
		wd_clear();
		time_light_sensor = pm_get_32k_tick();
	}
}
void Blink_Led(u32 Led){
	for(u8 i=0; i<5; i++){
		gpio_write(Led,1);
		sleep_ms(500);
		wd_clear();
		gpio_write(Led,0);
		sleep_ms(500);
		wd_clear();
	}
}

void OTA_device(u8 OTA_result){
	if(OTA_result == 0){
		Blink_Led(LED_RED);
	}else{
		Blink_Led(LED_GREEN);
	}
}



