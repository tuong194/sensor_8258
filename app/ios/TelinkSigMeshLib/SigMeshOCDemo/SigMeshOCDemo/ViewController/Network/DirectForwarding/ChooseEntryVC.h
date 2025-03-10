/********************************************************************************************************
 * @file     ChooseEntryVC.h
 *
 * @brief    A concise description.
 *
 * @author   Telink, 梁家誌
 * @date     2022/3/24
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 *******************************************************************************************************/

#import "BaseViewController.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : UInt8 {
    EntryType_tableEntry,
    EntryType_originRange,
    EntryType_targetRange,
} EntryType;

typedef void(^BackAddress)(NSMutableArray <NSNumber *>*addresses);

@interface ChooseEntryVC : BaseViewController

@property (nonatomic,strong) NSMutableArray <NSNumber *>*oldAddresses;
@property (nonatomic,assign) EntryType entryType;
@property (nonatomic,copy) BackAddress backAddressCallback;

@end

NS_ASSUME_NONNULL_END
