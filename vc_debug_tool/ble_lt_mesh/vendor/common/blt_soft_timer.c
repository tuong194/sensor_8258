/********************************************************************************************************
 * @file	blt_soft_timer.c
 *
 * @brief	for TLSR chips
 *
 * @author	public@telink-semi.com;
 * @date	Sep. 18, 2015
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
/*
 * blt_soft_timer.c
 *
 *  Created on: 2016-10-28
 *      Author: Administrator
 */


#include "tl_common.h"
#if (BLT_SOFTWARE_TIMER_ENABLE && (MCU_CORE_TYPE != MCU_CORE_8269))
#if(MCU_CORE_TYPE == MCU_CORE_8258)
#include "stack/ble/ble.h"
#elif(MCU_CORE_TYPE == MCU_CORE_8278)
#include "stack/ble_8278/ble.h"
#endif
#include "blt_soft_timer.h"
#include "proj_lib/sig_mesh/app_mesh.h"

STATIC_ASSERT(BLT_TIMER_SAFE_MARGIN_POST >= GET_ADV_INTERVAL_MS(ADV_INTERVAL_MAX)*1000*sys_tick_per_us); // BLT_TIMER_SAFE_MARGIN_POST should set to larger than ADV_INTERVAL_MAX

_attribute_data_retention_	blt_soft_timer_t	blt_timer;


//按照定时时间将timer排序，便于process时 依次触发timer
int  blt_soft_timer_sort(void)
{
	if(blt_timer.currentNum < 1 || blt_timer.currentNum > MAX_TIMER_NUM){
		write_reg32(0x40000, 0x11111120); while(1); //debug ERR
		return 0;
	}
	else{
		// 冒泡排序  BubbleSort
		int n = blt_timer.currentNum;
		u8 temp[sizeof(blt_time_event_t)];

		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-i-1;j++)
			{
				if(TIME_COMPARE_BIG(blt_timer.timer[j].t, blt_timer.timer[j+1].t))
				{
					//swap
					memcpy(temp, &blt_timer.timer[j], sizeof(blt_time_event_t));
					memcpy(&blt_timer.timer[j], &blt_timer.timer[j+1], sizeof(blt_time_event_t));
					memcpy(&blt_timer.timer[j+1], temp, sizeof(blt_time_event_t));
				}
			}
		}
	}

	return 1;
}



//user add timer
int blt_soft_timer_add(blt_timer_callback_t func, u32 interval_us)
{
//	int i;
	u32 now = clock_time();

	if(blt_timer.currentNum >= MAX_TIMER_NUM){  //timer full
		return 	0;
	}
	else{
		blt_timer.timer[blt_timer.currentNum].cb = func;
		blt_timer.timer[blt_timer.currentNum].interval = interval_us * CLOCK_16M_SYS_TIMER_CLK_1US;
		blt_timer.timer[blt_timer.currentNum].t = now + blt_timer.timer[blt_timer.currentNum].interval;
		blt_timer.currentNum ++;

		blt_soft_timer_sort();
		bls_pm_setAppWakeupLowPower(blt_timer.timer[0].t,  1);
		
		return  1;
	}
}


//timer 本来就是有序的，删除的时候，采用往前覆盖，所以不会破坏顺序，不需要重新排序
int  blt_soft_timer_delete_by_index(u8 index)
{
	if(index >= blt_timer.currentNum){
		write_reg32(0x40000, 0x11111121); while(1); //debug ERR
		return 0;
	}


	for(int i=index; i<blt_timer.currentNum - 1; i++){
		memcpy(&blt_timer.timer[i], &blt_timer.timer[i+1], sizeof(blt_time_event_t));
	}

	blt_timer.currentNum --;

	return 1;
}


int 	blt_soft_timer_delete(blt_timer_callback_t func)
{


	for(int i=0; i<blt_timer.currentNum; i++){
		if(blt_timer.timer[i].cb == func){
			blt_soft_timer_delete_by_index(i);

			if(i == 0){  //删除的是最近的timer，需要更新时间

				if(blt_timer.currentNum && ((u32)(blt_timer.timer[0].t - clock_time()) < BLT_TIMER_SAFE_MARGIN_POST)){
					bls_pm_setAppWakeupLowPower(blt_timer.timer[0].t,  1);
				}
				else{
					bls_pm_setAppWakeupLowPower(0, 0);  //disable
				}

			}

			return 1;
		}
	}

	return 0;
}

int 	blt_soft_timer_update(blt_timer_callback_t func, u32 interval_us)
{
	blt_soft_timer_delete(func);
	return blt_soft_timer_add(func, interval_us);
}

int is_soft_timer_exist(blt_timer_callback_t func)
{
	for(int i=0; i<blt_timer.currentNum; i++){
		if(func == blt_timer.timer[i].cb){
			return 1;
		}
	}
	return 0;
}

u8 blt_soft_timer_cur_num()
{
	return blt_timer.currentNum;
}

void  	blt_soft_timer_process(int type)
{
	if(type == CALLBACK_ENTRY){ //callback trigger
	}

	u32 now = clock_time();
	if(!blt_timer.currentNum){
		bls_pm_setAppWakeupLowPower(0, 0);  //disable
		return;
	}

	if( !blt_is_timer_expired(blt_timer.timer[0].t, now) ){
		return;
	}

	int change_flg = 0;
	int result;
	for(int i=0; i<blt_timer.currentNum; i++){
		if(blt_is_timer_expired(blt_timer.timer[i].t ,now) ){ //timer trigger

			if(blt_timer.timer[i].cb == NULL){
				write_reg32(0x40000, 0x11111122); while(1); //debug ERR
			}
			else{
				#if LLSYNC_ENABLE
				if(blt_timer.timer[i].cb){
					blt_timer.timer[i].cb(NULL);
				}
				result = 0;	// always continue.
				#else
				result = blt_timer.timer[i].cb();
				#endif

				if(result < 0){
					blt_soft_timer_delete_by_index(i);
				}
				else if(result == 0){
					change_flg = 1;
					blt_timer.timer[i].t = now + blt_timer.timer[i].interval;
				}
				else{  //set new timer interval
					change_flg = 1;
					blt_timer.timer[i].interval = result * CLOCK_16M_SYS_TIMER_CLK_1US;
					blt_timer.timer[i].t = now + blt_timer.timer[i].interval;
				}
			}
		}
	}


	if(blt_timer.currentNum ){ //timer table not empty
		if(change_flg){
			blt_soft_timer_sort();
		}

		if( (u32)(blt_timer.timer[0].t - now) < BLT_TIMER_SAFE_MARGIN_POST){
			bls_pm_setAppWakeupLowPower(blt_timer.timer[0].t,  1);
		}
		else{
			bls_pm_setAppWakeupLowPower(0, 0);  //disable
		}

	}
	else{
		bls_pm_setAppWakeupLowPower(0, 0);  //disable
	}

}


void 	blt_soft_timer_init(void)
{
	bls_pm_registerAppWakeupLowPowerCb(blt_soft_timer_process);
}


#endif  //end of  BLT_SOFTWARE_TIMER_ENABLE

