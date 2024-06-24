/********************************************************************************************************
 * @file	app_config_8258.h
 *
 * @brief	for TLSR chips
 *
 * @author	telink
 * @date	Sep. 30, 2010
 *
 * @par     Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#include "vendor/common/version.h"    // include mesh_config.h inside.
//////////////////board sel/////////////////////////////////////
#define PCBA_8258_DONGLE_48PIN          1
#define PCBA_8258_C1T139A30_V1_0        2
#define PCBA_8258_C1T139A30_V1_2        3
#define PCBA_8258_C1T140A3_V1_1         4   // 32pin

#ifndef PCBA_8258_SEL // user can define in user_app_config.h
#if (MESH_USER_DEFINE_MODE == MESH_IRONMAN_MENLO_ENABLE)
#define PCBA_8258_SEL			PCBA_8258_C1T140A3_V1_1  // PCBA_8258_DONGLE_48PIN   //
#else
#define PCBA_8258_SEL			PCBA_8258_DONGLE_48PIN
#endif
#endif


#define _USER_CONFIG_DEFINED_	1	// must define this macro to make others known
#define	__LOG_RT_ENABLE__		0
//#define	__DEBUG_PRINT__			0

#if (DUAL_MESH_ZB_BL_EN || DUAL_MESH_SIG_PVT_EN)
#define FLASH_1M_ENABLE         1
#elif DUAL_VENDOR_EN
#define FLASH_1M_ENABLE         0
#else
	#if MI_API_ENABLE
#define FLASH_1M_ENABLE        	1
	#else
#define FLASH_1M_ENABLE        	0	
	#endif
#endif

#if FLASH_1M_ENABLE
#if (DUAL_MESH_ZB_BL_EN || DUAL_MESH_SIG_PVT_EN)
#define PINGPONG_OTA_DISABLE    1 // it can disable only when 1M flash.
#else
#define PINGPONG_OTA_DISABLE    0 // it can disable only when 1M flash.
#endif
#if	PINGPONG_OTA_DISABLE
#define SWITCH_FW_ENABLE		0 // set to 0, just for particular customer 
#endif
#endif

//////////// product  Information  //////////////////////////////
#define ID_VENDOR				0x248a			// for report
#define ID_PRODUCT_BASE			0x880C
#define STRING_VENDOR			L"Telink"
#define STRING_PRODUCT			L"BLE Mesh"
#define STRING_SERIAL			L"TLSR825X"

#define DEV_NAME                "SigMesh"

#define APPLICATION_DONGLE		0					// or else APPLICATION_DEVICE
#define	USB_PRINTER				1
#define	FLOW_NO_OS				1

/////////////////////HCI ACCESS OPTIONS///////////////////////////////////////
#define HCI_USE_NONE	0
#define HCI_USE_UART	1
#define HCI_USE_USB		2

#ifndef HCI_ACCESS
#if (WIN32 || PTS_TEST_EN || TESTCASE_FLAG_ENABLE)
#define HCI_ACCESS		HCI_USE_USB
#elif MESH_MONITOR_EN
#define HCI_ACCESS		HCI_USE_UART
#else
	#if GATT_RP_EN
#define HCI_ACCESS		HCI_USE_UART
	#else
#define HCI_ACCESS		HCI_USE_UART
	#endif
#endif 

#if (HCI_ACCESS==HCI_USE_UART)
#define UART_TX_PIN		UART_TX_PD7
#define UART_RX_PIN		UART_RX_PA0
#endif
#endif

#ifndef HCI_LOG_FW_EN
#define HCI_LOG_FW_EN   (0 || DEBUG_LOG_SETTING_DEVELOP_MODE_EN)
#if HCI_LOG_FW_EN
	#if (MESH_USER_DEFINE_MODE == MESH_IRONMAN_MENLO_ENABLE)
#define DEBUG_INFO_TX_PIN           		(PCBA_8258_SEL == PCBA_8258_C1T140A3_V1_1 ? GPIO_PB6 : GPIO_PD7)
	#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_2)
#define DEBUG_INFO_TX_PIN           		GPIO_PD0	
	#else
#define DEBUG_INFO_TX_PIN           		GPIO_PB2
	#endif
#define PRINT_DEBUG_INFO                    1
#endif
#endif

#define BATT_CHECK_ENABLE       			1   //must enable
#if (BATT_CHECK_ENABLE)
//telink device: you must choose one gpio with adc function to output high level(voltage will equal to vbat), then use adc to measure high level voltage
	//use PC5 output high level, then adc measure this high level voltage
	#define GPIO_VBAT_DETECT				GPIO_PC5
	#define PC5_FUNC						AS_GPIO
	#define PC5_INPUT_ENABLE				0
	#define ADC_INPUT_PCHN					C5P    //corresponding  ADC_InputPchTypeDef in adc.h
#endif

#define ADC_ENABLE		0
#if ADC_ENABLE
#define ADC_BASE_MODE	1	//GPIO voltage
#define ADC_VBAT_MODE	2	//Battery Voltage

#define ADC_MODE		ADC_VBAT_MODE
#define ADC_CHNM_ANA_INPUT 		GPIO_PB3 // one of ADC_GPIO_tab[]
#define ADC_PRESCALER	ADC_PRESCALER_1F8
#endif

#define ONLINE_STATUS_EN        0

#if (DUAL_MESH_ZB_BL_EN || DUAL_MESH_SIG_PVT_EN)
#define DUAL_MODE_ADAPT_EN 			1   // dual mode as master with Zigbee
#else
#define DUAL_MODE_ADAPT_EN 			0   // dual mode as master with Zigbee
#endif
#if (0 == DUAL_MODE_ADAPT_EN)
#define DUAL_MODE_WITH_TLK_MESH_EN  0   // dual mode as slave with Telink mesh
#endif

/////////////////// mesh project config /////////////////////////////////
#ifndef TRANSITION_TIME_DEFAULT_VAL
#if (MESH_RX_TEST || (!MD_DEF_TRANSIT_TIME_EN))
#define TRANSITION_TIME_DEFAULT_VAL (0)
#else
	#if MI_API_ENABLE
#define TRANSITION_TIME_DEFAULT_VAL	0
	#elif LPN_CONTROL_EN
#define TRANSITION_TIME_DEFAULT_VAL	0
	#else
#define TRANSITION_TIME_DEFAULT_VAL (GET_TRANSITION_TIME_WITH_STEP(1, TRANSITION_STEP_RES_1S)) // (0x41)  // 0x41: 1 second // 0x00: means no default transition time
	#endif
#endif
#endif

#if MI_API_ENABLE
#define MESH_DLE_MODE               MESH_DLE_MODE_GATT
#define DLE_LEN_MAX_RX              (136)
#define DLE_LEN_MAX_TX              (40)
#elif GATT_LPN_EN
#define MESH_DLE_MODE               MESH_DLE_MODE_EXTEND_BEAR
#define DLE_LEN_MAX_RX              (MAX_OCTETS_DATA_LEN_EXTENSION)
#define DLE_LEN_MAX_TX              (80)
#elif DEBUG_CFG_CMD_GROUP_AK_EN
#define MESH_DLE_MODE               0   // because not enough RAM
#elif EXTENDED_ADV_ENABLE
#define MESH_DLE_MODE               MESH_DLE_MODE_EXTEND_BEAR
#define DLE_LEN_MAX_RX              (MAX_OCTETS_DATA_LEN_EXTENSION) // must MAX_OCTETS_DATA_LEN_EXTENSION
#define DLE_LEN_MAX_TX              (40)
#elif NMW_ENABLE
#define MESH_DLE_MODE               MESH_DLE_MODE_GATT
#define DLE_LEN_MAX_RX              (88)
#define DLE_LEN_MAX_TX              (40)
#else
#define MESH_DLE_MODE               MESH_DLE_MODE_GATT
#define DLE_LEN_MAX_RX              (56)
#define DLE_LEN_MAX_TX              (40)
#endif

/////////////////// MODULE /////////////////////////////////
#if (MI_SWITCH_LPN_EN || GATT_LPN_EN||DU_LPN_EN)
#define BLE_REMOTE_PM_ENABLE			1
#else
#define BLE_REMOTE_PM_ENABLE			0
#endif
#if BLE_REMOTE_PM_ENABLE
#define PM_DEEPSLEEP_RETENTION_ENABLE   1   // must
#else
#define PM_DEEPSLEEP_RETENTION_ENABLE   0
#endif
#define BLE_REMOTE_SECURITY_ENABLE      0
#define BLE_IR_ENABLE					0
#define BLE_SIG_MESH_CERTIFY_ENABLE 	0
#define BLE_GATT_2M_PHY_ENABLE			0 // only GATT, not for ADV

#if GATT_LPN_EN
#define BLT_SOFTWARE_TIMER_ENABLE		1
#endif

#ifndef BLT_SOFTWARE_TIMER_ENABLE
#define BLT_SOFTWARE_TIMER_ENABLE		0
#endif

#if ((0 == PM_DEEPSLEEP_RETENTION_ENABLE) && DUAL_VENDOR_EN)
#define SLEEP_FUNCTION_DISABLE          1
#endif

//----------------------- GPIO for UI --------------------------------
#if (GATT_LPN_EN || DF_TEST_MODE_EN || IV_UPDATE_TEST_EN)
#define	UI_KEYBOARD_ENABLE 				1
#endif

#ifndef UI_KEYBOARD_ENABLE
#define UI_KEYBOARD_ENABLE				0
#endif

#if UI_KEYBOARD_ENABLE
#define	MATRIX_ROW_PULL					PM_PIN_PULLDOWN_100K // drive pin pull
#define	MATRIX_COL_PULL					PM_PIN_PULLUP_10K    // scan pin pull

#define	KB_LINE_HIGH_VALID				0   // dirve pin output 0 when keyscan(no drive pin in KB_LINE_MODE=1), scanpin read 0 is valid
#define DEEPBACK_FAST_KEYSCAN_ENABLE	1   //proc fast scan when deepsleep back triggered by key press, in case key loss
#define KEYSCAN_IRQ_TRIGGER_MODE		0
#define LONG_PRESS_KEY_POWER_OPTIMIZE	1   //lower power when pressing key without release

#define	KB_MAP_NUM				KB_MAP_NORMAL
#define	KB_MAP_FN				KB_MAP_NORMAL

#if (PCBA_8258_SEL == PCBA_8258_DONGLE_48PIN)
// key mode, KB_LINE_MODE default 0(key matrix), set to 1 in button mode.
#define KB_LINE_MODE			1 			

// keymap
#define KEY_SW1		1
#define KEY_SW2		2
#define KB_MAP_NORMAL			{{KEY_SW1},	{KEY_SW2}}

#define KB_DRIVE_PINS			{GPIO_PD6} 	// just for compile, not driver pin in KB_LINE_MODE=1.
#define KB_SCAN_PINS			{GPIO_PD6, GPIO_PD5}

#define	SW1_GPIO				GPIO_PD6
#define	SW2_GPIO				GPIO_PD5

// scan pin as gpio
#define PD5_FUNC				AS_GPIO
#define PD6_FUNC				AS_GPIO

//scan  pin pullup
#define PULL_WAKEUP_SRC_PD6     PM_PIN_PULLUP_1M	//btn
#define PULL_WAKEUP_SRC_PD5     PM_PIN_PULLUP_1M	//btn

//scan pin open input to read gpio level
#define PD6_INPUT_ENABLE		1
#define PD5_INPUT_ENABLE		1
#elif (PCBA_8258_SEL == PCBA_8258_C1T140A3_V1_1)
// key mode, KB_LINE_MODE default 0(key matrix), set to 1 in button mode.
#define KB_LINE_MODE			1 			

// keymap
#define KEY_SW1		1
#define KEY_SW2		2
#define KB_MAP_NORMAL			{{KEY_SW1},	{KEY_SW2}}

#define KB_DRIVE_PINS			{GPIO_PD7} 	// just for compile, not driver pin in KB_LINE_MODE=1.
#define KB_SCAN_PINS			{GPIO_PD7, GPIO_PA1}

#define	SW1_GPIO				GPIO_PD7
#define	SW2_GPIO				GPIO_PA1

// scan pin as gpio
#define PD7_FUNC				AS_GPIO
#define PA1_FUNC				AS_GPIO

//scan  pin pullup
#define PULL_WAKEUP_SRC_PD7     PM_PIN_PULLUP_1M	//btn
#define PULL_WAKEUP_SRC_PA1     PM_PIN_PULLUP_1M	//btn

//scan pin open input to read gpio level
#define PD7_INPUT_ENABLE		1
#define PA1_INPUT_ENABLE		1
#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_2)
// keymap
#define KEY_SW1		1
#define KEY_SW2		2
#define KEY_SW3		3
#define KEY_SW4		4
#define	KB_MAP_NORMAL			{\
								{KEY_SW1,	KEY_SW2},	 \
								{KEY_SW3,	KEY_SW4},	 }

#define KB_DRIVE_PINS 		 	{GPIO_PB4, GPIO_PB5}
#define KB_SCAN_PINS   			{GPIO_PB2, GPIO_PB3}

#define	SW1_GPIO				GPIO_PB2
#define	SW2_GPIO				GPIO_PB3

//drive pin as gpio
#define	PB4_FUNC				AS_GPIO
#define	PB5_FUNC				AS_GPIO

//drive pin need 100K pulldown
#define	PULL_WAKEUP_SRC_PB4		MATRIX_ROW_PULL
#define	PULL_WAKEUP_SRC_PB5		MATRIX_ROW_PULL

//drive pin open input to read gpio wakeup level
#define PB4_INPUT_ENABLE		1
#define PB5_INPUT_ENABLE		1

//scan pin as gpio
#define	PB2_FUNC				AS_GPIO
#define	PB3_FUNC				AS_GPIO

//scan  pin need 10K pullup
#define	PULL_WAKEUP_SRC_PB2		MATRIX_COL_PULL
#define	PULL_WAKEUP_SRC_PB3		MATRIX_COL_PULL

//scan pin open input to read gpio level
#define PB2_INPUT_ENABLE		1
#define PB3_INPUT_ENABLE		1
#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_0)    // PCBA_8258_C1T139A30_V1_0
// key mode, KB_LINE_MODE default 0(key matrix), set to 1 in button mode.
#define KB_LINE_MODE			1 			

// keymap
#define KEY_SW1		1
#define KEY_SW2		2
#define KB_MAP_NORMAL			{{KEY_SW1},	{KEY_SW2}}

#define KB_DRIVE_PINS			{GPIO_PD2} 	// just for compile, not driver pin in KB_LINE_MODE=1.
#define KB_SCAN_PINS			{GPIO_PD2, GPIO_PD1}

#define	SW1_GPIO				GPIO_PD2
#define	SW2_GPIO				GPIO_PD1

// scan pin as gpio
#define PD2_FUNC				AS_GPIO
#define PD1_FUNC				AS_GPIO

//scan  pin pullup
#define PULL_WAKEUP_SRC_PD2     PM_PIN_PULLUP_1M	//btn
#define PULL_WAKEUP_SRC_PD1     PM_PIN_PULLUP_1M	//btn

//scan pin open input to read gpio level
#define PD2_INPUT_ENABLE		1
#define PD1_INPUT_ENABLE		1
#else
	#error "Current board do not support keyboard !"
#endif
#endif

#define XIAOMI_MODULE_ENABLE	MI_API_ENABLE
#define XIAOMI_TEST_CODE_ENABLE 	0

//---------------  LED / PWM
#if(PCBA_8258_SEL == PCBA_8258_DONGLE_48PIN)
#define PWM_R       GPIO_PWM1A3		//red
#define PWM_G       GPIO_PWM0A2		//green
#define PWM_B       GPIO_PWM3B0		//blue
#define PWM_W       GPIO_PWM4B1		//white
#elif(PCBA_8258_SEL == PCBA_8258_C1T140A3_V1_1)
#define PWM_R       GPIO_PWM2ND4    //red
#define PWM_G       GPIO_PWM0NA0    //green
#define PWM_B       GPIO_PWM1ND3    //blue
#define PWM_W       GPIO_PWM3D2		//yellow as white
#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_0)   // PCBA_8258_DEVELOPMENT_BOARD
#define PWM_R       GPIO_PWM1ND3	//red
#define PWM_G       GPIO_PWM2ND4	//green
#define PWM_B       GPIO_PD5		//blue
#define PWM_W       GPIO_PWM3D2		//white
#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_2)
#define PWM_R       GPIO_PD5	//red
#define PWM_G       GPIO_PWM1ND3	//green
#define PWM_B       GPIO_PWM3D2		//blue
#define PWM_W       GPIO_PWM2ND4		//white

#endif

#define PWM_FUNC_R  AS_PWM  // AS_PWM_SECOND
#define PWM_FUNC_G  AS_PWM  // AS_PWM_SECOND
#define PWM_FUNC_B  AS_PWM  // AS_PWM_SECOND
#define PWM_FUNC_W  AS_PWM  // AS_PWM_SECOND

#define PWMID_R     (GET_PWMID(PWM_R, PWM_FUNC_R))
#define PWMID_G     (GET_PWMID(PWM_G, PWM_FUNC_G))
#define PWMID_B     (GET_PWMID(PWM_B, PWM_FUNC_B))
#define PWMID_W     (GET_PWMID(PWM_W, PWM_FUNC_W))
                    
#define PWM_INV_R   (GET_PWM_INVERT_VAL(PWM_R, PWM_FUNC_R))
#define PWM_INV_G   (GET_PWM_INVERT_VAL(PWM_G, PWM_FUNC_G))
#define PWM_INV_B   (GET_PWM_INVERT_VAL(PWM_B, PWM_FUNC_B))
#define PWM_INV_W   (GET_PWM_INVERT_VAL(PWM_W, PWM_FUNC_W))

#ifndef GPIO_LED
#define GPIO_LED	PWM_R
#endif

/////////////open SWS digital pullup to prevent MCU err, this is must ////////////
#define PA7_DATA_OUT			1

//save suspend current
#if BLE_REMOTE_PM_ENABLE
#define PA5_FUNC 	AS_GPIO     // USB DM
#define PA6_FUNC 	AS_GPIO     // USB DP
#elif(HCI_ACCESS == HCI_USE_USB)
#define PA5_FUNC			AS_USB
#define PA5_INPUT_ENABLE	1
#define PA6_FUNC			AS_USB
#define PA6_INPUT_ENABLE	1
#endif

/////////////////// Clock  /////////////////////////////////
#define	USE_SYS_TICK_PER_US
#define CLOCK_SYS_TYPE  		CLOCK_TYPE_PLL	//  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC

#if DUAL_MESH_ZB_BL_EN // keep same with zb
#define CLOCK_SYS_CLOCK_HZ  	32000000
#elif EXTENDED_ADV_ENABLE
#define CLOCK_SYS_CLOCK_HZ  	48000000		// need to process rx buffer quickly
#elif (MI_API_ENABLE)
#define CLOCK_SYS_CLOCK_HZ  	48000000
#else
#define CLOCK_SYS_CLOCK_HZ  	24000000
#endif
//////////////////Extern Crystal Type///////////////////////
#define CRYSTAL_TYPE			XTAL_12M		//  extern 12M crystal

/////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE		1
#if (MI_API_ENABLE)
#define WATCHDOG_INIT_TIMEOUT		20000  //in mi mode the watchdog timeout is 20s
#else
#define WATCHDOG_INIT_TIMEOUT		2000  //in mi mode the watchdog timeout is 20s
#endif

#if MI_API_ENABLE && (MSC_TYPE != MSC_NONE)
/////////////////// MSC //////////////////////////////////
#define PULL_WAKEUP_SRC_PB4             PM_PIN_PULLUP_10K
#define GPIO_MSC_RESET                  GPIO_PB4
#define PB4_FUNC                        AS_GPIO

#define PULL_WAKEUP_SRC_PC2             PM_PIN_PULLUP_10K
#define GPIO_MSC_SDA                    GPIO_PC2

#define PULL_WAKEUP_SRC_PC3             PM_PIN_PULLUP_10K
#define GPIO_MSC_SCL                    GPIO_PC3    

//i2c clock = system_clock/(4*DivClock)
#define I2C_CLOCK_100K                  (CLOCK_SYS_CLOCK_HZ/(4*100000))
#define I2C_CLOCK_400K                  (CLOCK_SYS_CLOCK_HZ/(4*400000))
#define I2C_MSC_FREQ                    I2C_CLOCK_400K 
#endif

#if MI_API_ENABLE
#include "mi_config.h"
#endif
/////////////////// set default   ////////////////

#include "../common/default_config.h"

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
