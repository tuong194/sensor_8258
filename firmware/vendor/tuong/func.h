/*
 * func.h
 *
 *  Created on: Jun 5, 2024
 *      Author: DELL
 */


#ifndef FUNC_H_
#define FUNC_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

u32 nowtime;
u8 checkprovision;

#define MY_ADDR_FLASH 0xFE000

#define LED_RED 	GPIO_PB6
#define LED_GREEN   GPIO_PB4
#define SW          GPIO_PD4
#define MOTION  	GPIO_PB5

#define ON_LED_RED		gpio_write(LED_RED,0)
#define OFF_LED_RED		gpio_write(LED_RED,1)
#define ON_LED_GREEN	gpio_write(LED_GREEN,0)
#define OFF_LED_GREEN	gpio_write(LED_GREEN,1)

void init_value(void);
void start_init(void);
void Pin_Config(void);
void Blink_Led_Red(void);
void Blink_Led_Green(void);
void Provision(void);
u8 SW_press(void);
void SW_kick_out(void);
void motion(void);
void compare_lux(void);
void Write_Data_Flash(void);
void Read_Data_Flash(void);


#endif /* FUNC_H_ */
