// Copyright [2017] [Beijing Xiaomi Mobile Software Co., Ltd]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mible_api.h"
#include "mible_port.h"
#include "mible_type.h"
#include "../i2c_msc.h"
#ifndef MIBLE_MAX_USERS
#define MIBLE_MAX_USERS 4
#endif

/* GAP, GATTS, GATTC event callback function */
static uint8_t m_gap_users, m_gattc_users, m_gatts_users, m_arch_users;
static mible_gap_callback_t m_gap_cb_table[MIBLE_MAX_USERS];
static mible_gatts_callback_t m_gatts_cb_table[MIBLE_MAX_USERS];
static mible_gattc_callback_t m_gattc_cb_table[MIBLE_MAX_USERS];
static mible_arch_callback_t m_arch_cb_table[MIBLE_MAX_USERS];

int mible_gap_register(mible_gap_callback_t cb)
{
    int ret;

    CRITICAL_SECTION_ENTER();
    if (m_gap_users == MIBLE_MAX_USERS) {
        ret = MI_ERR_RESOURCES;
    } else {
        m_gap_cb_table[m_gap_users] = cb;
        m_gap_users++;

        ret = MI_SUCCESS;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}

int mible_gattc_register(mible_gattc_callback_t cb)
{
    int ret;

    CRITICAL_SECTION_ENTER();
    if (m_gattc_users == MIBLE_MAX_USERS) {
        ret = MI_ERR_RESOURCES;
    } else {
        m_gattc_cb_table[m_gattc_users] = cb;
        m_gattc_users++;

        ret = MI_SUCCESS;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}

int mible_gatts_register(mible_gatts_callback_t cb)
{
    int ret;

    CRITICAL_SECTION_ENTER();
    if (m_gatts_users == MIBLE_MAX_USERS) {
        ret = MI_ERR_RESOURCES;
    } else {
        m_gatts_cb_table[m_gatts_users] = cb;
        m_gatts_users++;

        ret = MI_SUCCESS;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}

int mible_arch_register(mible_arch_callback_t cb)
{
    int ret;

    CRITICAL_SECTION_ENTER();
    if (m_arch_users == MIBLE_MAX_USERS) {
        ret = MI_ERR_RESOURCES;
    } else {
        m_arch_cb_table[m_arch_users] = cb;
        m_arch_users++;

        ret = MI_SUCCESS;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}

/**
 *@brief    This function is MIBLE GAP related event callback function.
 *@param    [in] evt : GAP EVENT
 *          [in] param : callback parameters corresponding to evt
 *@return   Void
 *@note     You should support this function in your own ble stack .
 *          Make sure when the corresponding event occurs, be able to call this
 *function
 *          and pass in the corresponding parameters.
 */

void mible_gap_event_callback(mible_gap_evt_t evt, mible_gap_evt_param_t* param)
{
    for (int user = 0; user < MIBLE_MAX_USERS; user++) {
        if (m_gap_cb_table[user] != NULL) {
            m_gap_cb_table[user](evt, param);
        }
    }
}

/**
 *@brief    This function is MIBLE GATTS related event callback function.
 *@param    [in] evt : GATTS EVENT
 *          [in] param : callback parameters corresponding to evt
 *@return   Void
 *@note     You should support this function in your own ble stack .
 Make sure when the corresponding event occurs, be able to call this
 function and pass in the corresponding parameters.
 */
void mible_gatts_event_callback(mible_gatts_evt_t evt,
        mible_gatts_evt_param_t* param)
{
    for (int user = 0; user < MIBLE_MAX_USERS; user++) {
        if (m_gatts_cb_table[user] != NULL) {
            m_gatts_cb_table[user](evt, param);
        }
    }
}

/**
 *@brief    This function is MIBLE GATTC related event callback function.
 *@param    [in] evt : GATTC EVENT
 *          [in] param : callback parameters corresponding to evt
 *@return   Void
 *@note     You should support this function in your own ble stack .
 Make sure when the corresponding event occurs, be able to call this
 function and pass in the corresponding parameters.
 */
void mible_gattc_event_callback(mible_gattc_evt_t evt,
        mible_gattc_evt_param_t* param)
{
    for (int user = 0; user < MIBLE_MAX_USERS; user++) {
        if (m_gattc_cb_table[user] != NULL) {
            m_gattc_cb_table[user](evt, param);
        }
    }
}

/*
 *@brief    This function is mible_arch api related event callback function.
 *@param    [in] evt: asynchronous function complete event 
 *          [in] param: the return of asynchronous function 
 *@note     You should support this function in corresponding asynchronous function. 
 *          For now, mible_gatts_service_int and mible_record_write is asynchronous. 
 * */
void mible_arch_event_callback(mible_arch_event_t evt,
        mible_arch_evt_param_t* param)
{
    for (int user = 0; user < MIBLE_MAX_USERS; user++) {
        if (m_arch_cb_table[user] != NULL) {
            m_arch_cb_table[user](evt, param);
        }
    }
}

/**
 *        GAP APIs
 */

/**
 * @brief   Get BLE mac address.
 * @param   [out] mac: pointer to data
 * @return  MI_SUCCESS          The requested mac address were written to mac
 *          MI_ERR_INTERNAL     No mac address found.
 * @note:   You should copy gap mac to mac[6]  
 * */
__WEAK mible_status_t mible_gap_address_get(mible_addr_t mac)
{
    return telink_ble_mi_get_gap_address(mac);
}

/**
 * @brief   Start scanning
 * @param   [in] scan_type: passive or active scanning
 *          [in] scan_param: scan parameters including interval, windows
 * and timeout
 * @return  MI_SUCCESS             Successfully initiated scanning procedure.
 *          MI_ERR_INVALID_STATE   Has initiated scanning procedure.
 *          MI_ERR_INVALID_PARAM   Invalid parameter(s) supplied.
 *          MI_ERR_BUSY            The stack is busy, process pending
 * events and retry.
 * @note    Other default scanning parameters : public address, no
 * whitelist.
 *          The scan response is given through
 * MIBLE_GAP_EVT_ADV_REPORT event
 */
__WEAK mible_status_t mible_gap_scan_start(mible_gap_scan_type_t scan_type,
        mible_gap_scan_param_t scan_param)
{
    return MI_SUCCESS;
}

/**
 * @brief   Stop scanning
 * @param   void
 * @return  MI_SUCCESS             Successfully stopped scanning procedure.
 *          MI_ERR_INVALID_STATE   Not in scanning state.
 * */
__WEAK mible_status_t mible_gap_scan_stop(void)
{
    return MI_SUCCESS;
}

/**
 * @brief   Get scan param
 * @param   [out] scan_param: scan interval and window
 * @return  MI_SUCCESS             Successfully stopped scanning procedure.
 *          MI_ERR_INVALID_STATE   Not in scanning state.
 * */
__WEAK mible_status_t mible_gap_scan_param_get(mible_gap_scan_param_t *scan_param)
{
    return MI_SUCCESS;
}

/**
 * @brief   Start advertising
 * @param   [in] p_adv_param : pointer to advertising parameters, see
 * mible_gap_adv_param_t for details
 * @return  MI_SUCCESS             Successfully initiated advertising procedure.
 *          MI_ERR_INVALID_STATE   Initiated connectable advertising procedure
 * when connected.
 *          MI_ERR_INVALID_PARAM   Invalid parameter(s) supplied.
 *          MI_ERR_BUSY            The stack is busy, process pending events and
 * retry.
 *          MI_ERR_RESOURCES       Stop one or more currently active roles
 * (Central, Peripheral or Observer) and try again.
 * @note    Other default advertising parameters: local public address , no
 * filter policy
 * */
__WEAK mible_status_t mible_gap_adv_start(mible_gap_adv_param_t *p_param)
{
    return telink_ble_mi_adv_start(p_param);
}

/**
 * @brief   Config advertising data
 * @param   [in] p_data : Raw data to be placed in advertising packet. If NULL, no changes are made to the current advertising packet.
 * @param   [in] dlen   : Data length for p_data. Max size: 31 octets. Should be 0 if p_data is NULL, can be 0 if p_data is not NULL.
 * @param   [in] p_sr_data : Raw data to be placed in scan response packet. If NULL, no changes are made to the current scan response packet data.
 * @param   [in] srdlen : Data length for p_sr_data. Max size: BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if p_sr_data is NULL, can be 0 if p_data is not NULL.
 * @return  MI_SUCCESS             Successfully set advertising data.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_PARAM   Invalid parameter(s) supplied.
 * */
__WEAK mible_status_t mible_gap_adv_data_set(uint8_t const * p_data,
        uint8_t dlen, uint8_t const *p_sr_data, uint8_t srdlen)
{
	telink_ble_mi_gap_adv_data_set(p_data,dlen,p_sr_data,srdlen);
    return MI_SUCCESS;
}

/**
 * @brief   Stop advertising
 * @param   void
 * @return  MI_SUCCESS             Successfully stopped advertising procedure.
 *          MI_ERR_INVALID_STATE   Not in advertising state.
 * */
__WEAK mible_status_t mible_gap_adv_stop(void)
{
    return telink_ble_mi_adv_stop();
}

/**
 * @brief   Create a Direct connection
 * @param   [in] scan_param : scanning parameters, see TYPE
 * mible_gap_scan_param_t for details.
 *          [in] conn_param : connection parameters, see TYPE
 * mible_gap_connect_t for details.
 * @return  MI_SUCCESS             Successfully initiated connection procedure.
 *          MI_ERR_INVALID_STATE   Initiated connection procedure in connected state.
 *          MI_ERR_INVALID_PARAM   Invalid parameter(s) supplied.
 *          MI_ERR_BUSY            The stack is busy, process pending events and retry.
 *          MI_ERR_RESOURCES       Stop one or more currently active roles
 * (Central, Peripheral or Observer) and try again
 *          MIBLE_ERR_GAP_INVALID_BLE_ADDR    Invalid Bluetooth address
 * supplied.
 * @note    Own and peer address are both public.
 *          The connection result is given by MIBLE_GAP_EVT_CONNECTED
 * event
 * */
__WEAK mible_status_t mible_gap_connect(mible_gap_scan_param_t scan_param,
        mible_gap_connect_t conn_param)
{
    return MI_SUCCESS;
}

/**
 * @brief   Disconnect from peer
 * @param   [in] conn_handle: the connection handle
 * @return  MI_SUCCESS             Successfully disconnected.
 *          MI_ERR_INVALID_STATE   Not in connection.
 *          MIBLE_ERR_INVALID_CONN_HANDLE
 * @note    This function can be used by both central role and periphral
 * role.
 * */
__WEAK mible_status_t mible_gap_disconnect(uint16_t conn_handle)
{
	bls_ll_terminateConnection (0x13);
    return MI_SUCCESS;
}

/**
 * @brief   Update the connection parameters.
 * @param   [in] conn_handle: the connection handle.
 *          [in] conn_params: the connection parameters.
 * @return  MI_SUCCESS             The Connection Update procedure has been
 *started successfully.
 *          MI_ERR_INVALID_STATE   Initiated this procedure in disconnected
 *state.
 *          MI_ERR_INVALID_PARAM   Invalid parameter(s) supplied.
 *          MI_ERR_BUSY            The stack is busy, process pending events and
 *retry.
 *          MIBLE_ERR_INVALID_CONN_HANDLE
 * @note    This function can be used by both central role and peripheral
 *role.
 * */
__WEAK mible_status_t mible_gap_update_conn_params(uint16_t conn_handle,
        mible_gap_conn_param_t conn_params)
{
    return telink_ble_mi_update_conn_params(conn_handle,conn_params);
}

/**
 *        GATT Server APIs
 */

/**
 * @brief   Add a Service to a GATT server
 * @param   [in|out] p_server_db: pointer to mible service data type 
 * of mible_gatts_db_t, see TYPE mible_gatts_db_t for details. 
 * @return  MI_SUCCESS             Successfully added a service declaration.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_PARAM   Invalid parameter(s) supplied.
 *          MI_ERR_NO_MEM          Not enough memory to complete operation.
 * @note    This function can be implemented asynchronous. When service inition complete, call mible_arch_event_callback function and pass in MIBLE_ARCH_EVT_GATTS_SRV_INIT_CMP event and result.
 * */
__WEAK mible_status_t mible_gatts_service_init(mible_gatts_db_t *p_server_db)
{
    mible_arch_evt_param_t param;
	param.srv_init_cmp.status = telink_ble_mi_gatts_service_init(p_server_db);
	param.srv_init_cmp.p_gatts_db = p_server_db;
	mible_arch_event_callback(MIBLE_ARCH_EVT_GATTS_SRV_INIT_CMP, &param);
	return param.srv_init_cmp.status;
}

/**
 * @brief   Set characteristic value
 * @param   [in] srv_handle: service handle
 *          [in] value_handle: characteristic value handle
 *          [in] offset: the offset from which the attribute value has
 *to be updated
 *          [in] p_value: pointer to data
 *          [in] len: data length
 * @return  MI_SUCCESS             Successfully retrieved the value of the
 *attribute.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_PARAM   Invalid parameter (offset) supplied.
 *          MI_ERR_INVALID_LENGTH   Invalid length supplied.
 *          MIBLE_ERR_ATT_INVALID_HANDLE     Attribute not found.
 *          MIBLE_ERR_GATT_INVALID_ATT_TYPE  Attributes are not modifiable by
 *the application.
 * */
__WEAK mible_status_t mible_gatts_value_set(uint16_t srv_handle,
        uint16_t value_handle, uint8_t offset, uint8_t* p_value, uint8_t len)
{
    return telink_ble_mi_gatts_value_set(srv_handle,value_handle,offset,p_value,len);
}

/**
 * @brief   Get charicteristic value as a GATTS.
 * @param   [in] srv_handle: service handle
 *          [in] value_handle: characteristic value handle
 *          [out] p_value: pointer to data which stores characteristic value
 *          [out] p_len: pointer to data length.
 * @return  MI_SUCCESS             Successfully get the value of the attribute.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_PARAM   Invalid parameter (offset) supplied.
 *          MI_ERR_INVALID_LENGTH   Invalid length supplied.
 *          MIBLE_ERR_ATT_INVALID_HANDLE     Attribute not found.
 **/
__WEAK mible_status_t mible_gatts_value_get(uint16_t srv_handle,
        uint16_t value_handle, uint8_t* p_value, uint8_t *p_len)
{
    return telink_ble_mi_gatts_value_get(srv_handle,value_handle,p_value,p_len);
}

/**
 * @brief   Set characteristic value and notify it to client.
 * @param   [in] conn_handle: conn handle
 *          [in] srv_handle: service handle
 *          [in] char_value_handle: characteristic  value handle
 *          [in] offset: the offset from which the attribute value has to
 * be updated
 *          [in] p_value: pointer to data
 *          [in] len: data length
 *          [in] type : notification = 1; indication = 2;
 *
 * @return  MI_SUCCESS             Successfully queued a notification or
 * indication for transmission,
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_PARAM   Invalid parameter (offset) supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State or notifications
 * and/or indications not enabled in the CCCD.
 *          MI_ERR_INVALID_LENGTH   Invalid length supplied.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_ATT_INVALID_HANDLE     Attribute not found.
 *          MIBLE_ERR_GATT_INVALID_ATT_TYPE   //Attributes are not modifiable by
 * the application.
 * @note    This function checks for the relevant Client Characteristic
 * Configuration descriptor value to verify that the relevant operation (notification or
 * indication) has been enabled by the client.
 * */
__WEAK mible_status_t mible_gatts_notify_or_indicate(uint16_t conn_handle,
        uint16_t srv_handle, uint16_t char_value_handle, uint8_t offset,
        uint8_t* p_value, uint8_t len, uint8_t type)
{
    return telink_ble_mi_gatts_notify_or_indicate(conn_handle,srv_handle,
    char_value_handle,offset,p_value,len,type);
}

/**
 * @brief   Respond to a Read/Write user authorization request.
 * @param   [in] conn_handle: conn handle
 *          [in] status:  1: permit to change value ; 0: reject to change value 
 *          [in] char_value_handle: characteristic handle
 *          [in] offset: the offset from which the attribute value has to
 * be updated
 *          [in] p_value: Pointer to new value used to update the attribute value.
 *          [in] len: data length
 *          [in] type : read response = 1; write response = 2;
 *
 * @return  MI_SUCCESS             Successfully queued a response to the peer, and in the case of a write operation, GATT updated.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_PARAM   Invalid parameter (offset) supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State or no authorization request pending.
 *          MI_ERR_INVALID_LENGTH  Invalid length supplied.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_ATT_INVALID_HANDLE     Attribute not found.
 * @note    This call should only be used as a response to a MIBLE_GATTS_EVT_READ/WRITE_PERMIT_REQ
 * event issued to the application.
 * */
__WEAK mible_status_t mible_gatts_rw_auth_reply(uint16_t conn_handle,
        uint8_t status, uint16_t char_value_handle, uint8_t offset,
        uint8_t* p_value, uint8_t len, uint8_t type)
{
    return MI_SUCCESS;
}

/**
 *        GATT Client APIs
 */

/**
 * @brief   Discover primary service by service UUID.
 * @param   [in] conn_handle: connect handle
 *          [in] handle_range: search range for primary service
 *discovery procedure
 *          [in] p_srv_uuid: pointer to service uuid
 * @return  MI_SUCCESS             Successfully started or resumed the Primary
 *Service Discovery procedure.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @note    The response is given through
 *MIBLE_GATTC_EVT_PRIMARY_SERVICE_DISCOVER_RESP event
 * */
__WEAK mible_status_t mible_gattc_primary_service_discover_by_uuid(
        uint16_t conn_handle, mible_handle_range_t handle_range,
        mible_uuid_t* p_srv_uuid)
{

    return MI_SUCCESS;
}

/**
 * @brief   Discover characteristic by characteristic UUID.
 * @param   [in] conn_handle: connect handle
 *          [in] handle_range: search range for characteristic discovery
 * procedure
 *          [in] p_char_uuid: pointer to characteristic uuid
 * @return  MI_SUCCESS             Successfully started or resumed the
 * Characteristic Discovery procedure.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_INVALID_CONN_HANDLE   Invalid connection handle.
 * @note    The response is given through
 * MIBLE_GATTC_CHR_DISCOVER_BY_UUID_RESP event
 * */
__WEAK mible_status_t mible_gattc_char_discover_by_uuid(uint16_t conn_handle,
        mible_handle_range_t handle_range, mible_uuid_t* p_char_uuid)
{
    return MI_SUCCESS;
}

/**
 * @brief   Discover characteristic client configuration descriptor
 * @param   [in] conn_handle: connection handle
 *          [in] handle_range: search range
 * @return  MI_SUCCESS             Successfully started Clien Config Descriptor
 * Discovery procedure.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_INVALID_CONN_HANDLE   Invalid connection handle.
 * @note    Maybe run the charicteristic descriptor discover procedure firstly,
 * then pick up the client configuration descriptor which att type is 0x2092
 *          The response is given through MIBLE_GATTC_CCCD_DISCOVER_RESP
 * event
 *          Only return the first cccd handle within the specified
 * range.
 * */
__WEAK mible_status_t mible_gattc_clt_cfg_descriptor_discover(
        uint16_t conn_handle, mible_handle_range_t handle_range)
{
    return MI_SUCCESS;
}

/**
 * @brief   Read characteristic value by UUID
 * @param   [in] conn_handle: connection handle
 *          [in] handle_range: search range
 *          [in] p_char_uuid: pointer to characteristic uuid
 * @return  MI_SUCCESS             Successfully started or resumed the Read
 * using Characteristic UUID procedure.
 *          MI_ERR_INVALID_STATE   Invalid Connection State.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_INVALID_CONN_HANDLE   Invalid connection handle.
 * @note    The response is given through
 * MIBLE_GATTC_EVT_READ_CHR_VALUE_BY_UUID_RESP event
 * */
__WEAK mible_status_t mible_gattc_read_char_value_by_uuid(uint16_t conn_handle,
        mible_handle_range_t handle_range, mible_uuid_t *p_char_uuid)
{
    return MI_SUCCESS;
}

/**
 * @brief   Write value by handle with response
 * @param   [in] conn_handle: connection handle
 *          [in] handle: handle to the attribute to be written.
 *          [in] p_value: pointer to data
 *          [in] len: data length
 * @return  MI_SUCCESS             Successfully started the Write with response
 * procedure.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State.
 *          MI_ERR_INVALID_LENGTH   Invalid length supplied.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_INVALID_CONN_HANDLE   Invalid connection handle.
 * @note    The response is given through MIBLE_GATTC_EVT_WRITE_RESP event
 *
 * */
__WEAK mible_status_t mible_gattc_write_with_rsp(uint16_t conn_handle,
        uint16_t att_handle, uint8_t* p_value, uint8_t len)
{
    return MI_SUCCESS;
}

/**
 * @brief   Write value by handle without response
 * @param   [in] conn_handle: connection handle
 *          [in] att_handle: handle to the attribute to be written.
 *          [in] p_value: pointer to data
 *          [in] len: data length
 * @return  MI_SUCCESS             Successfully started the Write Cmd procedure.
 *          MI_ERR_INVALID_ADDR    Invalid pointer supplied.
 *          MI_ERR_INVALID_STATE   Invalid Connection State.
 *          MI_ERR_INVALID_LENGTH   Invalid length supplied.
 *          MI_ERR_BUSY            Procedure already in progress.
 *          MIBLE_ERR_INVALID_CONN_HANDLE  Invalid connection handle.
 * @note    no response
 * */
__WEAK mible_status_t mible_gattc_write_cmd(uint16_t conn_handle,
        uint16_t att_handle, uint8_t* p_value, uint8_t len)
{
    return MI_SUCCESS;
}

/**
 *        SOFT TIMER APIs
 */

/**
 * @brief   Create a timer.
 * @param   [out] p_timer_id: a pointer to timer id address which can uniquely identify the timer.
 *          [in] timeout_handler: a pointer to a function which can be
 * called when the timer expires.
 *          [in] mode: repeated or single shot.
 * @return  MI_SUCCESS             If the timer was successfully created.
 *          MI_ERR_INVALID_PARAM   Invalid timer id supplied.
 *          MI_ERR_INVALID_STATE   timer module has not been initialized or the
 * timer is running.
 *          MI_ERR_NO_MEM          timer pool is full.
 *
 * */
__WEAK mible_status_t mible_timer_create(void** p_timer_id,
        mible_timer_handler timeout_handler, mible_timer_mode mode)
{
    return telink_mi_timer_create(p_timer_id,timeout_handler,mode);
}

/**
 * @brief   Create a timer.
 * @param   [out] p_timer_id: a pointer to timer id address which can uniquely identify the timer.
 *          [in] timeout_handler: a pointer to a function which can be
 * called when the timer expires.
 *          [in] mode: repeated or single shot.
 * @return  MI_SUCCESS             If the timer was successfully created.
 *          MI_ERR_INVALID_PARAM   Invalid timer id supplied.
 *          MI_ERR_INVALID_STATE   timer module has not been initialized or the
 * timer is running.
 *          MI_ERR_NO_MEM          timer pool is full.
 *
 * */
__WEAK mible_status_t mible_user_timer_create(void** p_timer_id,
        mible_timer_handler timeout_handler, mible_timer_mode mode)
{
    return telink_mi_timer_create(p_timer_id,timeout_handler,mode);
}

/**
 * @brief   Delete a timer.
 * @param   [in] timer_id: timer id
 * @return  MI_SUCCESS             If the timer was successfully deleted.
 *          MI_ERR_INVALID_PARAM   Invalid timer id supplied..
 * */
__WEAK mible_status_t mible_timer_delete(void* timer_id)
{
    return  telink_mi_timer_delete(timer_id); 
}

/**
 * @brief   Start a timer.
 * @param   [in] timer_id: timer id
 *          [in] timeout_value: Number of milliseconds to time-out event
 * (minimum 10 ms).
 *          [in] p_context: parameters that can be passed to
 * timeout_handler
 *
 * @return  MI_SUCCESS             If the timer was successfully started.
 *          MI_ERR_INVALID_PARAM   Invalid timer id supplied.
 *          MI_ERR_INVALID_STATE   If the application timer module has not been
 * initialized or the timer has not been created.
 *          MI_ERR_NO_MEM          If the timer operations queue was full.
 * @note    If the timer has already started, it will start counting again.
 * */
__WEAK mible_status_t mible_timer_start(void* timer_id, uint32_t timeout_value,
        void* p_context)
{
    return telink_mi_timer_start(timer_id,timeout_value*1000,p_context);
}

/**
 * @brief   Stop a timer.
 * @param   [in] timer_id: timer id
 * @return  MI_SUCCESS             If the timer was successfully stopped.
 *          MI_ERR_INVALID_PARAM   Invalid timer id supplied.
 *
 * */
__WEAK mible_status_t mible_timer_stop(void* timer_id)
{
    return telink_mi_timer_stop(timer_id);
}

/**
 *        NVM APIs
 */

/**
 * @brief   Create a record in flash 
 * @param   [in] record_id: identify a record in flash 
 *          [in] len: record length
 * @return  MI_SUCCESS              Create successfully.
 *          MI_ERR_INVALID_LENGTH   Size was 0, or higher than the maximum
 *allowed size.
 *          MI_ERR_NO_MEM,          Not enough flash memory to be assigned 
 *              
 * */
__WEAK mible_status_t mible_record_create(uint16_t record_id, uint8_t len)
{
    return  telink_record_create(record_id, len);
}

/**
 * @brief   Delete a record in flash
 * @param   [in] record_id: identify a record in flash  
 * @return  MI_SUCCESS              Delete successfully. 
 *          MI_ERR_INVALID_PARAMS   Invalid record id supplied.
 * */
__WEAK mible_status_t mible_record_delete(uint16_t record_id)
{
    return telink_record_delete(record_id);
}

/**
 * @brief   Restore data to flash
 * @param   [in] record_id: identify an area in flash
 *          [out] p_data: pointer to data
 *          [in] len: data length
 * @return  MI_SUCCESS              The command was accepted.
 *          MI_ERR_INVALID_LENGTH   Size was 0, or higher than the maximum
 *allowed size.
 *          MI_ERR_INVALID_PARAMS   Invalid record id supplied.
 *          MI_ERR_INVALID_ADDR     Invalid pointer supplied.
 * */
__WEAK mible_status_t mible_record_read(uint16_t record_id, uint8_t* p_data,
        uint8_t len)
{
    return telink_record_read(record_id, p_data,len);
}

/**
 * @brief   Store data to flash
 * @param   [in] record_id: identify an area in flash
 *          [in] p_data: pointer to data
 *          [in] len: data length
 * @return  MI_SUCCESS              The command was accepted.
 *          MI_ERR_INVALID_LENGTH   Size was 0, or higher than the maximum
 * allowed size.
 *          MI_ERR_INVALID_PARAMS   p_data is not aligned to a 4 byte boundary.
 * @note    Should use asynchronous mode to implement this function.
 *          The data to be written to flash has to be kept in memory until the
 * operation has terminated, i.e., an event is received.
 *          When record writing complete , call mible_arch_event_callback function and pass MIBLE_ARCH_EVT_RECORD_WRITE_CMP event and result. 
 * */
__WEAK mible_status_t mible_record_write(uint16_t record_id, const uint8_t* p_data,
        uint8_t len)
{
    return telink_record_write(record_id,(uint8_t*)p_data,len);
}

/**
 *        MISC APIs
 */

/**
 * @brief   Get true random bytes .
 * @param   [out] p_buf: pointer to data
 *          [in] len: Number of bytes to take from pool and place in
 * p_buff
 * @return  MI_SUCCESS          The requested bytes were written to
 * p_buff
 *          MI_ERR_NO_MEM       No bytes were written to the buffer, because
 * there were not enough random bytes available.
 * @note    SHOULD use TRUE random num generator
 * */
__WEAK mible_status_t mible_rand_num_generator(uint8_t* p_buf, uint8_t len)
{
	extern int telink_rand_num_generator(uint8_t* p_buf, uint8_t len);
    telink_rand_num_generator(p_buf,len);
    return MI_SUCCESS;
}

/**
 * @brief   Encrypts a block according to the specified parameters. 128-bit
 * AES encryption. (zero padding)
 * @param   [in] key: encryption key
 *          [in] plaintext: pointer to plain text
 *          [in] plen: plain text length
 *          [out] ciphertext: pointer to cipher text
 * @return  MI_SUCCESS              The encryption operation completed.
 *          MI_ERR_INVALID_ADDR     Invalid pointer supplied.
 *          MI_ERR_INVALID_STATE    Encryption module is not initialized.
 *          MI_ERR_INVALID_LENGTH   Length bigger than 16.
 *          MI_ERR_BUSY             Encryption module already in progress.
 * @note    SHOULD use synchronous mode to implement this function
 * */
__WEAK mible_status_t mible_aes128_encrypt(const uint8_t* key,
        const uint8_t* plaintext, uint8_t plen, uint8_t* ciphertext)
{
    return telink_ble_mi_aes128_encrypt(key,plaintext,plen,ciphertext)	;
}

/**
 * @brief   Post a task to a task quene, which can be executed in a right place 
 * (maybe a task in RTOS or while(1) in the main function).
 * @param   [in] handler: a pointer to function 
 *          [in] param: function parameters 
 * @return  MI_SUCCESS              Successfully put the handler to quene.
 *          MI_ERR_NO_MEM           The task quene is full. 
 *          MI_ERR_INVALID_PARAM    Handler is NULL
 * */
__WEAK mible_status_t mible_task_post(mible_handler_t handler, void *arg)
{
    return telink_mi_task_post(handler,arg);
}

/**
 * @brief   Function for executing all enqueued tasks.
 *
 * @note    This function must be called from within the main loop. It will 
 * execute all events scheduled since the last time it was called.
 * */
__WEAK void mible_tasks_exec(void)
{
	telink_mi_task_exec();
}

#if HAVE_MSC
static mible_handler_t handler_iic_callback = 0;

//i2c need init,after wakeup form deepsleep mode
_attribute_no_retention_bss_ uint8_t  i2c_init_flag = 0;

static uint8_t        msc_addr;
I2C_GPIO_GroupTypeDef msc_iic_group;
static uint16_t       msc_iic_freq;
void msc_iic_init(void)
{
    if(i2c_init_flag == 0){
        i2c_master_init(msc_addr,msc_iic_freq); 
        i2c_gpio_set(msc_iic_group);
      
        i2c_init_flag = 1;
    }
}

/**
 * @brief   Function for initializing the IIC driver instance.
 * @param   [in] p_config: Pointer to the initial configuration.
 *          [in] handler: Event handler provided by the user. 
 * @return  MI_SUCCESS              Initialized successfully.
 *          MI_ERR_INVALID_PARAM    p_config or handler is a NULL pointer.
 *              
 * */
__WEAK mible_status_t mible_iic_init(const iic_config_t * p_config,
        mible_handler_t handler)
{
    u8 ret = IIC_EVT_XFER_DONE;

    handler_iic_callback = handler;
    
    msc_iic_freq = p_config->freq;
    if((p_config->scl_pin == GPIO_PA4)&&(p_config->sda_pin == GPIO_PA3)){
        msc_iic_group = I2C_GPIO_GROUP_A3A4;
    }
    else if((p_config->scl_pin == GPIO_PD7)&&(p_config->sda_pin == GPIO_PB6)){
        msc_iic_group = I2C_GPIO_GROUP_B6D7;
    }    
    else if((p_config->scl_pin == GPIO_PC1)&&(p_config->sda_pin == GPIO_PC0)){
        msc_iic_group = I2C_GPIO_GROUP_C0C1;
    } 
    else if((p_config->scl_pin == GPIO_PC3)&&(p_config->sda_pin == GPIO_PC2)){
        msc_iic_group = I2C_GPIO_GROUP_C2C3;
    }    
    msc_iic_init();
   
    return ret;
}
#endif

/**
 * @brief   Function for uninitializing the IIC driver instance.
 * 
 *              
 * */
__WEAK void mible_iic_uninit(void)
{

}

/**
 * @brief   Function for sending data to a IIC slave.
 * @param   [in] addr:   Address of a specific slave device (only 7 LSB).
 *          [in] p_out:  Pointer to tx data
 *          [in] len:    Data length
 *          [in] no_stop: If set, the stop condition is not generated on the bus
 *          after the transfer has completed successfully (allowing for a repeated start in the next transfer).
 * @return  MI_SUCCESS              The command was accepted.
 *          MI_ERR_BUSY             If a transfer is ongoing.
 *          MI_ERR_INVALID_PARAM    p_out is not valid address.
 * @note    This function should be implemented in non-blocking mode.
 *          When tx procedure complete, the handler provided by mible_iic_init() should be called,
 * and the iic event should be passed as a argument. 
 * */
__WEAK mible_status_t mible_iic_tx(uint8_t addr, uint8_t * p_out, uint16_t len,
bool no_stop)
{
	#if HAVE_MSC
    u8 ret = IIC_EVT_XFER_DONE;
    u32 r = irq_disable();
    
    msc_addr = addr;

    msc_iic_init();
        
    ret = i2c_write_series_for_msc(msc_addr,0,0,p_out,len,no_stop);
    
    if(handler_iic_callback != NULL){
        handler_iic_callback(&ret);
    }
    irq_restore(r);

    return ret;
	#else
	return 0;
	#endif
}

/**
 * @brief   Function for receiving data from a IIC slave.
 * @param   [in] addr:   Address of a specific slave device (only 7 LSB).
 *          [out] p_in:  Pointer to rx data
 *          [in] len:    Data length
 * @return  MI_SUCCESS              The command was accepted.
 *          MI_ERR_BUSY             If a transfer is ongoing.
 *          MI_ERR_INVALID_PARAM    p_in is not valid address.
 * @note    This function should be implemented in non-blocking mode.
 *          When rx procedure complete, the handler provided by mible_iic_init() should be called,
 * and the iic event should be passed as a argument. 
 * */
__WEAK mible_status_t mible_iic_rx(uint8_t addr, uint8_t * p_in, uint16_t len)
{
	#if HAVE_MSC
    u8 ret = IIC_EVT_XFER_DONE;
    u32 r = irq_disable();

    msc_addr = addr;

    msc_iic_init();
         
    ret = i2c_read_series_msc(msc_addr,0,0,p_in,len);

    if(handler_iic_callback != NULL){
        handler_iic_callback(&ret);
    }
    irq_restore(r);

    return ret;
	#else
	return 0;
	#endif
}

/**
 * @brief   Function for checking IIC SCL pin.
 * @param   [in] port:   SCL port
 *          [in] pin :   SCL pin
 * @return  1: High (Idle)
 *          0: Low (Busy)
 * */
__WEAK int mible_iic_scl_pin_read(uint8_t port, uint8_t pin)
{
    return MI_SUCCESS;
}

extern u32		ota_program_offset;

__WEAK mible_status_t mible_nvm_init(void)
{
    return MI_SUCCESS;
}

/**
 * @brief   Function for reading data from Non-Volatile Memory.
 * @param   [out] p_data:  Pointer to data to be restored.
 *          [in] length:   Data size in bytes.
 *          [in] address:  Address in Non-Volatile Memory to read.
 * @return  MI_ERR_INTERNAL:  invalid NVM address.
 *          MI_SUCCESS
 * */
__WEAK mible_status_t mible_nvm_read(void * p_data, uint32_t length, uint32_t address)
{
	if(NULL == p_data){
       return MI_ERR_INVALID_PARAM;
    }
   	
    flash_read_page(address,length,(u8 *)p_data);
    if(address == ota_program_offset){
		u8 *p_buf = (u8 *)(p_data);
		p_buf[8]=0x4b; // if the ota flag is unbusy ,it will use 4b to caulate the crc 
	}
    return MI_SUCCESS;
}

/**
 * @brief   Writes data to Non-Volatile Memory.
 * @param   [in] p_data:   Pointer to data to be stored.
 *          [in] length:   Data size in bytes.
 *          [in] address:  Start address used to store data.
 * @return  MI_ERR_INTERNAL:  invalid NVM address.
 *          MI_SUCCESS
 * */
#define LEN_CHECK_DATA      16

_attribute_ram_code_  u32 flash_adr_is_empty(u32 adr,u32 idx)
{
	u8 read_data[LEN_CHECK_DATA] = {0};
	const u8 flash_empty_data[LEN_CHECK_DATA]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
											   0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	flash_read_page(adr+idx, LEN_CHECK_DATA, read_data);
	if(!memcmp(flash_empty_data, read_data,LEN_CHECK_DATA)){
		return 1;
	}else{
		return 0;
	}
}
_attribute_ram_code_ u8 flash_sector_is_empty_t(u32 adr)
{
	if( flash_adr_is_empty(adr,0)&&
		flash_adr_is_empty(adr,0x800-LEN_CHECK_DATA)&&
		flash_adr_is_empty(adr,0x800)&&
		flash_adr_is_empty(adr,0x1000-LEN_CHECK_DATA)){
		return 1;
	}else{
		return 0;
	}
}

__WEAK mible_status_t mible_nvm_write(void * p_data, uint32_t length, uint32_t address)
{
    if(NULL == p_data){
       return MI_ERR_INVALID_PARAM;
    }
	u8 *p_buf = (u8 *)(p_data);
	// if the address is the sector start (4k size align ),we need to erase first 
	
	if(address %0x1000 == 0){ // wait for test ,and add mainly for test when power off ,and continue to test 
		if(!flash_sector_is_empty_t(address)){
			flash_erase_sector(address);
		}
	}
	if(address == ota_program_offset){
		p_buf[8]=0xff;// change it to invalid flag
	}
	telink_mible_nvm_write((u8 *)p_data,length,address);
    if(address == ota_program_offset){
		p_buf[8]=0x4b;// rooback the value 
	}
    return MI_SUCCESS;
}

__WEAK mible_status_t mible_upgrade_firmware(void)
{
    telink_mible_upgrade_firmware();
	return MI_SUCCESS;
}

/**
 *@brief    reboot device.
 *@return   0: success, negetive value: failure
 */
__WEAK mible_status_t mible_reboot(void)
{
	start_reboot();
    return MI_ERR_BUSY;
}

/**
 *@brief    set node tx power.
 *@param    [in] power : TX power in 0.1 dBm steps.
 *@return   0: success, negetive value: failure
 */
__WEAK mible_status_t mible_set_tx_power(int16_t power)
{
#if (CHIP_TYPE != CHIP_TYPE_8269)
	uint8_t tx_gain;
	if(power <= -200){//-20dbm
		#if (CHIP_TYPE == CHIP_TYPE_8258)
		tx_gain = RF_POWER_N19p27dBm;  
		#else
		tx_gain = RF_POWER_N18p40dBm; 
		#endif
	}else if (power <= 0){//0dbm
		#if (CHIP_TYPE == CHIP_TYPE_8258)
		tx_gain = RF_POWER_P0p04dBm;  
		#else
		tx_gain = RF_POWER_N0p28dBm; 
		#endif
	}else if (power <= 30){//3dbm
		#if (CHIP_TYPE == CHIP_TYPE_8258)
			tx_gain = RF_POWER_P3p01dBm;  
		#else
			tx_gain = RF_POWER_P3p13dBm; 
		#endif
	}else if (power <= 40){//4dbm
		#if (CHIP_TYPE == CHIP_TYPE_8258)
			tx_gain = RF_POWER_P3p94dBm;  
		#else
			tx_gain = RF_POWER_P3p99dBm; 
		#endif
	}else {//7.5dbm
		#if (CHIP_TYPE == CHIP_TYPE_8258)
			tx_gain = RF_POWER_P7p41dBm;  
		#else
			tx_gain = RF_POWER_P7p80dBm; 
		#endif
	}
	rf_set_power_level_index(tx_gain);
#endif
    return MI_SUCCESS;
}

__WEAK int mible_log_printf(const char * sFormat, ...)
{	
	va_list list;
	va_start( list, sFormat );
	my_printf_uart(sFormat,list);
    return MI_SUCCESS;
}

__WEAK int mible_log_hexdump(void* array_base, uint16_t array_size)
{
	my_printf_uart_hexdump(array_base, array_size);
	return MI_SUCCESS;
}

