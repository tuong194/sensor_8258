/*
 * BH1750.h
 *
 *  Created on: Jun 11, 2024
 *      Author: DELL
 */

#ifndef BH1750_H_
#define BH1750_H_
#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"

#define I2C_CLOCK   250000

#define ADDR_BH1750FVI 0x46  //0x23<<1
#define ADDR_WRITE  0x23
#define ADDR_READ   0x23



unsigned int get_lux_BH1750(void);
#endif /* BH1750_H_ */
