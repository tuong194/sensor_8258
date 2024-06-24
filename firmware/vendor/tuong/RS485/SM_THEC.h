/*
 * SM_THEC.h
 *
 *  Created on: Jun 15, 2024
 *      Author: DELL
 */

#ifndef SM_THEC_H_
#define SM_THEC_H_

#include "tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"


#define PIN_RS485 GPIO_PC0


#define FUNC_READ  0x03
#define FUNC_WRITE 0x06

#define REG_HUMI_EC      0x0000
#define REG_TEMP_EC		 0x0001
#define REG_EC			 0x0002
#define REG_ID_EC		 0x07D0
#define REG_BAUDRATE_EC	 0x07D1

void GPIO_Config_RS485(void);
void TX_Enable(void);
void RX_Enable(void);
void EC_Trans_Get_Humi(void);
void EC_Read_Humi(void);

#endif /* SM_THEC_H_ */
