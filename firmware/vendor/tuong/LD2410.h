/*
 * LD2410.h
 *
 *  Created on: Jun 5, 2024
 *      Author: DELL
 */

#ifndef LD2410_H_
#define LD2410_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"


#define RESET_CONFIG      0  // reset config
#define SET_SENSITIVITY   1  // set sensitivity full 40
#define SET_CONFIG   	  2  // config moving max 2, motionless max 3, delay 2

void set_up_config(u8 type_config);



#endif /* VENDOR_TUONG_LD2410_H_ */
