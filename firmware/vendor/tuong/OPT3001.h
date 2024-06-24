/*
 * OPT3001.h
 *
 *  Created on: Jun 4, 2024
 *      Author: DELL
 */

#ifndef OPT3001_H_
#define OPT3001_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"




#define I2C_OPT3001_CLOCK 200000
#define SLAVE_ID          0x88         // ADDR - GND 1000 100 1(R)
#define RESULT_REGISTER          0x00
#define CONFIG_REGISTER          0x01


unsigned int get_lux(void);
unsigned int caculate_lux(uint32_t get_lux);

#endif /* OPT3001_H_ */
