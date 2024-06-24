/*
 * SHT30.h
 *
 *  Created on: Jun 11, 2024
 *      Author: DELL
 */

#ifndef SHT30_H_
#define SHT30_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define I2C_CLOCK_SHT30   100000

#define ADDR_SHT30_SLAVE_ID 0x88  // 0x44<<1
#define CMD_SHT30   		0x2C06
#define ADDR_SHT30 			0x44

void get_temp_humi(void);

#endif /* SHT30_H_ */
