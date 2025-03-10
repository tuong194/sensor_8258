/********************************************************************************************************
 * @file Opcode.java
 *
 * @brief for TLSR chips
 *
 * @author telink
 * @date Sep. 30, 2017
 *
 * @par Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
package com.telink.ble.mesh.core.message;


import androidx.annotation.Nullable;

/**
 * This is an enum class that represents different opcodes (operation codes) used in a communication protocol.
 * Each opcode has a unique value and an optional information string.
 * Some opcodes also have a reliability value, indicating whether the command is reliable or unreliable.
 */
public enum Opcode {

    APPKEY_ADD(0x00, "Add Application key"),
    APPKEY_UPDATE(0x01),
    COMPOSITION_DATA_STATUS(0x02),
    CFG_MODEL_PUB_SET(0x03),
    HEALTH_CURRENT_STATUS(0x04),
    HEALTH_FAULT_STATUS(0x05),
    HEARTBEAT_PUB_STATUS(0x06),

    // config
    APPKEY_DEL(0x0080),
    APPKEY_GET(0x0180),
    APPKEY_LIST(0x0280),
    APPKEY_STATUS(0x0380),

    // attenttion timer
    HEALTH_ATTENTION_GET(0x0480),
    HEALTH_ATTENTION_SET(0x0580),
    HEALTH_ATTENTION_SET_NOACK(0x0680),
    HEALTH_ATTENTION_STATUS(0x0780),

    COMPOSITION_DATA_GET(0x0880),
    CFG_BEACON_GET(0x0980),
    CFG_BEACON_SET(0x0A80),
    CFG_BEACON_STATUS(0x0B80),
    CFG_DEFAULT_TTL_GET(0x0C80),
    CFG_DEFAULT_TTL_SET(0x0D80),
    CFG_DEFAULT_TTL_STATUS(0x0E80),
    CFG_FRIEND_GET(0x0F80),
    CFG_FRIEND_SET(0x1080),
    CFG_FRIEND_STATUS(0x1180),
    CFG_GATT_PROXY_GET(0x1280),
    CFG_GATT_PROXY_SET(0x1380),
    CFG_GATT_PROXY_STATUS(0x1480),
    CFG_KEY_REFRESH_PHASE_GET(0x1580),
    CFG_KEY_REFRESH_PHASE_SET(0x1680),
    CFG_KEY_REFRESH_PHASE_STATUS(0x1780),
    CFG_MODEL_PUB_GET(0x1880),
    CFG_MODEL_PUB_STATUS(0x1980),
    CFG_MODEL_PUB_VIRTUAL_ADR_SET(0x1A80),
    CFG_MODEL_SUB_ADD(0x1B80),
    CFG_MODEL_SUB_DEL(0x1C80),
    CFG_MODEL_SUB_DEL_ALL(0x1D80),
    CFG_MODEL_SUB_OVER_WRITE(0x1E80),
    CFG_MODEL_SUB_STATUS(0x1F80),
    CFG_MODEL_SUB_VIRTUAL_ADR_ADD(0x2080),
    CFG_MODEL_SUB_VIRTUAL_ADR_DEL(0x2180),
    CFG_MODEL_SUB_VIRTUAL_ADR_OVER_WRITE(0x2280),
    CFG_NW_TRANSMIT_GET(0x2380),
    CFG_NW_TRANSMIT_SET(0x2480),
    CFG_NW_TRANSMIT_STATUS(0x2580),
    CFG_RELAY_GET(0x2680),
    CFG_RELAY_SET(0x2780),
    CFG_RELAY_STATUS(0x2880),
    CFG_SIG_MODEL_SUB_GET(0x2980),
    CFG_SIG_MODEL_SUB_LIST(0x2A80),
    CFG_VENDOR_MODEL_SUB_GET(0x2B80),
    CFG_VENDOR_MODEL_SUB_LIST(0x2C80),
    CFG_LPN_POLL_TIMEOUT_GET(0x2D80),
    CFG_LPN_POLL_TIMEOUT_STATUS(0x2E80),

    //    private beacon
    PRIVATE_BEACON_GET(0x6080),
    PRIVATE_BEACON_SET(0x6180),
    PRIVATE_BEACON_STATUS(0x6280),
    PRIVATE_GATT_PROXY_GET(0x6380),
    PRIVATE_GATT_PROXY_SET(0x6480),
    PRIVATE_GATT_PROXY_STATUS(0x6580),
    PRIVATE_NODE_IDENTITY_GET(0x6680),
    PRIVATE_NODE_IDENTITY_SET(0x6780),
    PRIVATE_NODE_IDENTITY_STATUS(0x6880),

    HEALTH_FAULT_CLEAR(0x2F80),
    HEALTH_FAULT_CLEAR_NOACK(0x3080),
    HEALTH_FAULT_GET(0x3180),
    HEALTH_FAULT_TEST(0x3280),
    HEALTH_FAULT_TEST_NOACK(0x3380),

    HEALTH_PERIOD_GET(0x3480),
    HEALTH_PERIOD_SET(0x3580),
    HEALTH_PERIOD_SET_NOACK(0x3680),
    HEALTH_PERIOD_STATUS(0x3780),

    HEARTBEAT_PUB_GET(0x3880),
    HEARTBEAT_PUB_SET(0x3980),
    HEARTBEAT_SUB_GET(0x3A80),
    HEARTBEAT_SUB_SET(0x3B80),
    HEARTBEAT_SUB_STATUS(0x3C80),

    MODE_APP_BIND(0x3D80),
    MODE_APP_STATUS(0x3E80),
    MODE_APP_UNBIND(0x3F80),
    NETKEY_ADD(0x4080),
    NETKEY_DEL(0x4180),
    NETKEY_GET(0x4280),
    NETKEY_LIST(0x4380),
    NETKEY_STATUS(0x4480),
    NETKEY_UPDATE(0x4580),
    NODE_ID_GET(0x4680),
    NODE_ID_SET(0x4780),
    NODE_ID_STATUS(0x4880),
    NODE_RESET(0x4980),
    NODE_RESET_STATUS(0x4A80),
    SIG_MODEL_APP_GET(0x4B80),
    SIG_MODEL_APP_LIST(0x4C80),
    VENDOR_MODEL_APP_GET(0x4D80),
    VENDOR_MODEL_APP_LIST(0x4E80),

    // subnet bridge
    SUBNET_BRIDGE_GET(0xB180),
    SUBNET_BRIDGE_SET(0xB280),
    SUBNET_BRIDGE_STATUS(0xB380),
    BRIDGING_TABLE_ADD(0xB480),
    BRIDGING_TABLE_REMOVE(0xB580),
    BRIDGING_TABLE_STATUS(0xB680),
    BRIDGED_SUBNETS_GET(0xB780),
    BRIDGED_SUBNETS_LIST(0xB880),
    BRIDGING_TABLE_GET(0xB980),
    BRIDGING_TABLE_LIST(0xBA80),
    BRIDGE_TABLE_SIZE_GET(0xBB80),
    BRIDGE_TABLE_SIZE_STATUS(0xBC80),


    // generic
    G_ONOFF_GET(0x0182),
    G_ONOFF_SET(0x0282),
    G_ONOFF_SET_NOACK(0x0382),
    G_ONOFF_STATUS(0x0482),

    G_LEVEL_GET(0x0582),
    G_LEVEL_SET(0x0682),
    G_LEVEL_SET_NOACK(0x0782),
    G_LEVEL_STATUS(0x0882),
    G_DELTA_SET(0x0982),
    G_DELTA_SET_NOACK(0x0A82),
    G_MOVE_SET(0x0B82),
    G_MOVE_SET_NOACK(0x0C82),

    G_DEF_TRANS_TIME_GET(0x0D82),
    G_DEF_TRANS_TIME_SET(0x0E82),
    G_DEF_TRANS_TIME_SET_NOACK(0x0F82),
    G_DEF_TRANS_TIME_STATUS(0x1082),

    G_ON_POWER_UP_GET(0x1182),
    G_ON_POWER_UP_STATUS(0x1282),
    G_ON_POWER_UP_SET(0x1382),
    G_ON_POWER_UP_SET_NOACK(0x1482),

    G_POWER_LEVEL_GET(0x1582),
    G_POWER_LEVEL_SET(0x1682),
    G_POWER_LEVEL_SET_NOACK(0x1782),
    G_POWER_LEVEL_STATUS(0x1882),
    G_POWER_LEVEL_LAST_GET(0x1982),
    G_POWER_LEVEL_LAST_STATUS(0x1A82),
    G_POWER_DEF_GET(0x1B82),
    G_POWER_DEF_STATUS(0x1C82),
    G_POWER_LEVEL_RANGE_GET(0x1D82),
    G_POWER_LEVEL_RANGE_STATUS(0x1E82),
    G_POWER_DEF_SET(0x1F82),
    G_POWER_DEF_SET_NOACK(0x2082),
    G_POWER_LEVEL_RANGE_SET(0x2182),
    G_POWER_LEVEL_RANGE_SET_NOACK(0x2282),

    G_BATTERY_GET(0x2382),
    G_BATTERY_STATUS(0x2482),

    G_LOCATION_GLOBAL_GET(0x2582),
    G_LOCATION_GLOBAL_STATUS(0x40),
    G_LOCATION_LOCAL_GET(0x2682),
    G_LOCATION_LOCAL_STATUS(0x2782),
    G_LOCATION_GLOBAL_SET(0x41),
    G_LOCATION_GLOBAL_SET_NOACK(0x42),
    G_LOCATION_LOCAL_SET(0x2882),
    G_LOCATION_LOCAL_SET_NOACK(0x2982),

    // lighting
    LIGHTNESS_GET(0x4B82),
    LIGHTNESS_SET(0x4C82),
    LIGHTNESS_SET_NOACK(0x4D82),
    LIGHTNESS_STATUS(0x4E82),
    LIGHTNESS_LINEAR_GET(0x4F82),
    LIGHTNESS_LINEAR_SET(0x5082),
    LIGHTNESS_LINEAR_SET_NOACK(0x5182),
    LIGHTNESS_LINEAR_STATUS(0x5282),
    LIGHTNESS_LAST_GET(0x5382),
    LIGHTNESS_LAST_STATUS(0x5482),
    LIGHTNESS_DEFAULT_GET(0x5582),
    LIGHTNESS_DEFAULT_STATUS(0x5682),
    LIGHTNESS_RANGE_GET(0x5782),
    LIGHTNESS_RANGE_STATUS(0x5882),
    LIGHTNESS_DEFAULT_SET(0x5982),
    LIGHTNESS_DEFAULT_SET_NOACK(0x5A82),
    LIGHTNESS_RANGE_SET(0x5B82),
    LIGHTNESS_RANGE_SET_NOACK(0x5C82),
    LIGHT_CTL_GET(0x5D82),
    LIGHT_CTL_SET(0x5E82),
    LIGHT_CTL_SET_NOACK(0x5F82),
    LIGHT_CTL_STATUS(0x6082),
    LIGHT_CTL_TEMP_GET(0x6182),
    LIGHT_CTL_TEMP_RANGE_GET(0x6282),
    LIGHT_CTL_TEMP_RANGE_STATUS(0x6382),
    LIGHT_CTL_TEMP_SET(0x6482),
    LIGHT_CTL_TEMP_SET_NOACK(0x6582),
    LIGHT_CTL_TEMP_STATUS(0x6682),
    LIGHT_CTL_DEFAULT_GET(0x6782),
    LIGHT_CTL_DEFAULT_STATUS(0x6882),
    LIGHT_CTL_DEFAULT_SET(0x6982),
    LIGHT_CTL_DEFAULT_SET_NOACK(0x6A82),
    LIGHT_CTL_TEMP_RANGE_SET(0x6B82),
    LIGHT_CTL_TEMP_RANGE_SET_NOACK(0x6C82),

    // HSL
    LIGHT_HSL_GET(0x6D82),
    LIGHT_HSL_HUE_GET(0x6E82),
    LIGHT_HSL_HUE_SET(0x6F82),
    LIGHT_HSL_HUE_SET_NOACK(0x7082),
    LIGHT_HSL_HUE_STATUS(0x7182),
    LIGHT_HSL_SAT_GET(0x7282),
    LIGHT_HSL_SAT_SET(0x7382),
    LIGHT_HSL_SAT_SET_NOACK(0x7482),
    LIGHT_HSL_SAT_STATUS(0x7582),
    LIGHT_HSL_SET(0x7682),
    LIGHT_HSL_SET_NOACK(0x7782),
    LIGHT_HSL_STATUS(0x7882),
    LIGHT_HSL_TARGET_GET(0x7982),
    LIGHT_HSL_TARGET_STATUS(0x7A82),
    LIGHT_HSL_DEF_GET(0x7B82),
    LIGHT_HSL_DEF_STATUS(0x7C82),
    LIGHT_HSL_RANGE_GET(0x7D82),
    LIGHT_HSL_RANGE_STATUS(0x7E82),
    LIGHT_HSL_DEF_SET(0x7F82),
    LIGHT_HSL_DEF_SET_NOACK(0x8082),
    LIGHT_HSL_RANGE_SET(0x8182),
    LIGHT_HSL_RANGE_SET_NOACK(0x8282),

    // time
    TIME_GET(0x3782),
    TIME_SET(0x5C),
    TIME_STATUS(0x5D),
    TIME_ROLE_GET(0x3882),
    TIME_ROLE_SET(0x3982),
    TIME_ROLE_STATUS(0x3A82),
    TIME_ZONE_GET(0x3B82),
    TIME_ZONE_SET(0x3C82),
    TIME_ZONE_STATUS(0x3D82),
    TAI_UTC_DELTA_GET(0x3E82),
    TAI_UTC_DELTA_SET(0x3F82),
    TAI_UTC_DELTA_STATUS(0x4082),

    // scheduler
    SCHD_ACTION_GET(0x4882),
    SCHD_ACTION_STATUS(0x5F),
    SCHD_GET(0x4982),
    SCHD_STATUS(0x4A82),
    SCHD_ACTION_SET(0x60),
    SCHD_ACTION_SET_NOACK(0x61),

    // scene
    SCENE_GET(0x4182),
    SCENE_RECALL(0x4282),
    SCENE_RECALL_NOACK(0x4382),
    SCENE_STATUS(0x5E),
    SCENE_REG_GET(0x4482),
    SCENE_REG_STATUS(0x4582),
    SCENE_STORE(0x4682),
    SCENE_STORE_NOACK(0x4782),
    SCENE_DEL(0x9E82),
    SCENE_DEL_NOACK(0x9F82),

    // remote provision
    REMOTE_PROV_SCAN_CAPA_GET(0x4F80),
    REMOTE_PROV_SCAN_CAPA_STS(0x5080),
    REMOTE_PROV_SCAN_GET(0x5180),
    REMOTE_PROV_SCAN_START(0x5280),
    REMOTE_PROV_SCAN_STOP(0x5380),
    REMOTE_PROV_SCAN_STS(0x5480),
    REMOTE_PROV_SCAN_REPORT(0x5580),
    REMOTE_PROV_EXTEND_SCAN_START(0x5680),
    REMOTE_PROV_EXTEND_SCAN_REPORT(0x5780),
    REMOTE_PROV_LINK_GET(0x5880),
    REMOTE_PROV_LINK_OPEN(0x5980),
    REMOTE_PROV_LINK_CLOSE(0x5A80),
    REMOTE_PROV_LINK_STS(0x5B80),
    REMOTE_PROV_LINK_REPORT(0x5C80),
    REMOTE_PROV_PDU_SEND(0x5D80),
    REMOTE_PROV_PDU_OUTBOUND_REPORT(0x5E80),
    REMOTE_PROV_PDU_REPORT(0x5F80),

    // mesh OTA

    /**
     * BLOB Transfer
     */
    BLOB_TRANSFER_GET(0x0083),
    BLOB_TRANSFER_START(0x0183),
    BLOB_TRANSFER_CANCEL(0x0283),
    BLOB_TRANSFER_STATUS(0x0383),
    BLOB_BLOCK_GET(0x0583),
    BLOB_BLOCK_START(0x0483),
    BLOB_BLOCK_STATUS(0x67),
    BLOB_PARTIAL_BLOCK_REPORT(0x68),
    BLOB_CHUNK_TRANSFER(0x66),
    BLOB_INFORMATION_GET(0x0683),
    BLOB_INFORMATION_STATUS(0x0783),


    /**
     * Firmware Update
     */
    FIRMWARE_UPDATE_INFORMATION_GET(0x0883),
    FIRMWARE_UPDATE_INFORMATION_STATUS(0x0983),
    FIRMWARE_UPDATE_FIRMWARE_METADATA_CHECK(0x0A83),
    FIRMWARE_UPDATE_FIRMWARE_METADATA_STATUS(0x0B83),
    FIRMWARE_UPDATE_GET(0x0C83),
    FIRMWARE_UPDATE_START(0x0D83),
    FIRMWARE_UPDATE_CANCEL(0x0E83),
    FIRMWARE_UPDATE_APPLY(0x0F83),
    FIRMWARE_UPDATE_STATUS(0x1083),


    /**
     * Firmware Distribution
     */

    FD_GET(0x1883),
    FD_START(0x1983),
    FD_SUSPEND(0x1A83),
    FD_CANCEL(0x1B83),
    FD_APPLY(0x1C83),
    FD_STATUS(0x1D83),
    FD_RECEIVERS_GET(0x1483),
    FD_RECEIVERS_LIST(0x1583),
    FD_RECEIVERS_ADD(0x1183),
    FD_RECEIVERS_DELETE_ALL(0x1283),
    FD_RECEIVERS_STATUS(0x1383),
    FD_CAPABILITIES_GET(0x1683),
    FD_CAPABILITIES_STATUS(0x1783),
    FD_UPLOAD_GET(0x1E83),
    FD_UPLOAD_START(0x1F83),
    FD_UPLOAD_OOB_START(0x2083),
    FD_UPLOAD_CANCEL(0x2183),
    FD_UPLOAD_STATUS(0x2283),
    FD_FIRMWARE_GET(0x2383),
    FD_FIRMWARE_STATUS(0x2783),
    FD_FIRMWARE_GET_BY_INDEX(0x2483),
    FD_FIRMWARE_DELETE(0x2583),
    FD_FIRMWARE_DELETE_ALL(0x2683),

    /**
     * fast provision, telink private [vendor command]
     */
    VD_MESH_RESET_NETWORK(0x0211C5),
    VD_MESH_ADDR_GET(0x0211C6),
    VD_MESH_ADDR_GET_STS(0x0211C7),
    VD_MESH_ADDR_SET(0x0211C8),
    VD_MESH_ADDR_SET_STS(0x0211C9),
    VD_MESH_PROV_DATA_SET(0x0211CA),
    VD_MESH_PROV_CONFIRM(0x0211CB),
    VD_MESH_PROV_CONFIRM_STS(0x0211CC),
    VD_MESH_PROV_COMPLETE(0x0211CD),

    // direct control
    DIRECTED_CONTROL_GET(0x7B80),
    DIRECTED_CONTROL_SET(0x7C80),
    //    DIRECTED_CONTROL_SET(0xbf31),
    DIRECTED_CONTROL_STATUS(0x7D80),
    PATH_METRIC_GET(0x7E80),
    PATH_METRIC_SET(0x7F80),
    PATH_METRIC_STATUS(0x8080),
    DISCOVERY_TABLE_CAPABILITIES_GET(0x8180),
    DISCOVERY_TABLE_CAPABILITIES_SET(0x8280),
    DISCOVERY_TABLE_CAPABILITIES_STATUS(0x8380),
    FORWARDING_TABLE_ADD(0x8480),
    FORWARDING_TABLE_DELETE(0x8580),
    FORWARDING_TABLE_STATUS(0x8680),
    FORWARDING_TABLE_DEPENDENTS_ADD(0x8780),
    FORWARDING_TABLE_DEPENDENTS_DELETE(0x8880),
    FORWARDING_TABLE_DEPENDENTS_STATUS(0x8980),
    FORWARDING_TABLE_DEPENDENTS_GET(0x8A80),
    FORWARDING_TABLE_DEPENDENTS_GET_STATUS(0x8B80),
    FORWARDING_TABLE_ENTRIES_COUNT_GET(0x8C80),
    FORWARDING_TABLE_ENTRIES_COUNT_STATUS(0x8D80),
    FORWARDING_TABLE_ENTRIES_GET(0x8E80),
    FORWARDING_TABLE_ENTRIES_STATUS(0x8F80),
    WANTED_LANES_GET(0x9080),
    WANTED_LANES_SET(0x9180),
    WANTED_LANES_STATUS(0x9280),
    TWO_WAY_PATH_GET(0x9380),
    TWO_WAY_PATH_SET(0x9480),
    TWO_WAY_PATH_STATUS(0x9580),
    PATH_ECHO_INTERVAL_GET(0x9680),
    PATH_ECHO_INTERVAL_SET(0x9780),
    PATH_ECHO_INTERVAL_STATUS(0x9880),
    DIRECTED_NETWORK_TRANSMIT_GET(0x9980),
    DIRECTED_NETWORK_TRANSMIT_SET(0x9A80),
    DIRECTED_NETWORK_TRANSMIT_STATUS(0x9B80),
    DIRECTED_RELAY_RETRANSMIT_GET(0x9C80),
    DIRECTED_RELAY_RETRANSMIT_SET(0x9D80),
    DIRECTED_RELAY_RETRANSMIT_STATUS(0x9E80),
    RSSI_THRESHOLD_GET(0x9F80),
    RSSI_THRESHOLD_SET(0xA080),
    RSSI_THRESHOLD_STATUS(0xA180),
    DIRECTED_PATHS_GET(0xA280),
    DIRECTED_PATHS_STATUS(0xA380),
    DIRECTED_PUBLISH_POLICY_GET(0xA480),
    DIRECTED_PUBLISH_POLICY_SET(0xA580),
    DIRECTED_PUBLISH_POLICY_STATUS(0xA680),
    PATH_DISCOVERY_TIMING_CONTROL_GET(0xA780),
    PATH_DISCOVERY_TIMING_CONTROL_SET(0xA880),
    PATH_DISCOVERY_TIMING_CONTROL_STATUS(0xA980),
    DIRECTED_CONTROL_NETWORK_TRANSMIT_GET(0xAB80),
    DIRECTED_CONTROL_NETWORK_TRANSMIT_SET(0xAC80),
    DIRECTED_CONTROL_NETWORK_TRANSMIT_STATUS(0xAD80),
    DIRECTED_CONTROL_RELAY_RETRANSMIT_GET(0xAE80),
    DIRECTED_CONTROL_RELAY_RETRANSMIT_SET(0xAF80),
    DIRECTED_CONTROL_RELAY_RETRANSMIT_STATUS(0xB080),

    CFG_SAR_TRANSMITTER_GET(0x6C80),
    CFG_SAR_TRANSMITTER_SET(0x6D80),
    CFG_SAR_TRANSMITTER_STATUS(0x6E80),
    CFG_SAR_RECEIVER_GET(0x6F80),
    CFG_SAR_RECEIVER_SET(0x7080),
    CFG_SAR_RECEIVER_STATUS(0x7180),

    CFG_ON_DEMAND_PROXY_GET(0x6980),
    CFG_ON_DEMAND_PROXY_SET(0x6A80),
    CFG_ON_DEMAND_PROXY_STATUS(0x6B80),

    // opcode aggregator
    CFG_OP_AGG_SEQ(0x7280),
    CFG_OP_AGG_STATUS(0x7380),

    // large composition data message
    LARGE_CPS_GET(0x7480),
    LARGE_CPS_STATUS(0x7580),
    MODELS_METADATA_GET(0x7680),
    MODELS_METADATA_STATUS(0x7780),

    SOLI_PDU_RPL_ITEM_CLEAR(0x7880),
    SOLI_PDU_RPL_ITEM_CLEAR_NACK(0x7980),
    SOLI_PDU_RPL_ITEM_STATUS(0x7A80),
    ;

    public final int value;
    public final String info;

    /**
     * if command is reliable
     * -1 unknown default
     * 0 unreliable
     * 1 reliable
     */
    private final int reliable;

    Opcode(int value) {
        this.value = value;
        this.info = "";
        this.reliable = -1;
    }

    Opcode(int value, @Nullable String info) {
        this.value = value;
        this.info = info;
        this.reliable = -1;
    }

    Opcode(int value, String info, int reliable) {
        this.value = value;
        this.info = info;
        this.reliable = reliable;
    }

    public static Opcode valueOf(int value) {
        for (Opcode op :
                values()) {
            if (op.value == value) {
                return op;
            }
        }
        return null;
    }


    public int getReliable() {
        return reliable;
    }


}
