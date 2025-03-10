/********************************************************************************************************
 * @file	cmd_interface.h
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

#if WIN32
#include "proj_lib/sig_mesh/app_mesh.h"
#endif


//---------------
typedef struct{
	int op;
	u16 ele_adr;
}mesh_cfg_cmd_sub_set_par_t;
extern mesh_cfg_cmd_sub_set_par_t mesh_cfg_cmd_sub_set_par;

/**************************SendOpParaDebug**************************
function : the basic function of the send cmd by the opcode ,use the op(reflect to the mode )
		  to operation all the models 
para:
	adr_dst: the dst unicast addr. 
	rsp_max: means after sending the parameter,it will how many different packets back 
	op: the opcode to operation the models ,this can reflect to the model
	par: the par buf to control the model 
	len : the len of the buf 
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int SendOpParaDebug(u16 adr_dst, u8 rsp_max, u16 op, u8 *par, int len);

/**************************SendOpByINI**************************
function : the basic function of the send cmd by ini format .
para:
	ini_buf[0:1]: meas ini flag, please set to 0xa3 0xff as default. 
	ini_buf[2...]: please refer to  struct "mesh_bulk_cmd_par_t" and struct "mesh_vendor_par_ini_t"
	len : the len of the buf 
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int SendOpByINI(u8 *ini_buf, u32 len);




/**************************access_cmd_get_level**************************
function : access_cmd_get_level,to get the nodes in the net ,online status 
para:
	adr: the adr to operate 
	rsp_max: means after sending the parameter,it will how many different packets back 
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int access_cmd_get_level(u16 adr,u32 rsp_max);



/************************** access_cmd_set_level **************************
function : set the level of the light   
para:
	adr: set the node's adr 
	rsp_max: means after sending the parameter,it will how many different packets back 
	level: -32768 ~ 32767
	ack: 1 means send reliable cmd ,and the node will send rsp ,0 means unreliable ,will not send 
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int access_cmd_set_level(u16 adr, u8 rsp_max, s16 level, int ack, transition_par_t *trs_par);



/************************** access_cmd_set_delta **************************
function : set the delta of the light   
para:
	adr: set the node's adr 
	rsp_max: means after sending the parameter,it will how many different packets back 
	level: -32768 ~ 32767
	ack: 1 means send reliable cmd ,and the node will send rsp ,0 means unreliable ,will not send 
	trs_par: the trans par to control the changes of the level
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int access_cmd_set_delta(u16 adr, u8 rsp_max, s32 level, int ack, transition_par_t *trs_par);


/************************** access_cmd_set_level **************************
function : move the level to level max or level min under speed of "level/(transition time)"   
para:
	adr: set the node's adr 
	rsp_max: means after sending the parameter,it will how many different packets back 
	level: -32768 ~ 32767
	ack: 1 means send reliable cmd ,and the node will send rsp ,0 means unreliable ,will not send 
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int access_cmd_set_level_move(u16 adr, u8 rsp_max, s16 level, int ack, transition_par_t *trs_par);


/************************** access_set_lum **************************
function : set the lum of the light   
para:
	adr: set the node's adr 
	rsp_max: means after sending the parameter,it will how many different packets back 
	level: 0 ~ 100
	ack: 1 means send reliable cmd ,and the node will send rsp ,0 means unreliable ,will not send 
ret: 0  means OK 
	-1 or other value means err 
****************************************************************************/
int access_set_lum(u16 adr, u8 rsp_max, u8 lum, int ack);
int access_get_lum(u16 adr, u8 rsp_max);


/**************************access_cmd_onoff**************************
function : access_cmd_onoff,turn on or turn off the lights part 
para:
	adr_dst: the src adr you will send to the cmd .
	rsp_max: means after sending the parameter,it will how many different packets back 
	onff: 1 means on ,and 0 means off 
	ack: 1 means send reliable cmd ,and the node will send rsp ,0 means unreliable ,will not send 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/


int access_cmd_onoff(u16 adr_dst, u8 rsp_max, u8 onoff, int ack, transition_par_t *trs_par);



/**************************access_cmd_onoff_get**************************
function : access_cmd_onoff_get,get the status of the on off state  
para:
	adr: the unicast or the group adr to operate 
	rsp: the onoff states cnt rsp back 
	
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int access_cmd_onoff_get(u16 adr, u8 rsp_max);
int access_cmd_get_light_ctl(u16 adr,u32 rsp_max);
int access_cmd_set_light_ctl_100(u16 adr, u8 rsp_max, u8 lum, u8 temp100, int ack);
int access_cmd_get_light_ctl_temp(u16 adr,u32 rsp_max);
int access_cmd_set_light_ctl_temp_100(u16 adr, u8 rsp_max, u8 temp100, int ack);




/**************************cfg_cmd_sub_get**************************
function : cfg_cmd_sub_get,get the model's subscription list addr part 
para:
	node_adr: the dst adr of the node ,element_primary part 
	ele_adr:  model adr of the node 
	md_id: the model id part 
	
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sub_get(u16 node_adr, u16 ele_adr, u16 md_id);




/**************************cfg_cmd_sub_set**************************
function : cfg_cmd_sub_set,set the model's subscription list addr part 
para:
	op: the opcode to operate the subscription list addr part ,such as CFG_MODEL_SUB_ADD,CFG_MODEL_SUB_DEL
	node_adr: the node's element addr .
	ele_adr: the model's adr part 
	sub_adr: the adr used to add the remove for the addr list 
	md_id: the special model id 
	sig_model: it is bool, 1 means "md_id" is a SIG model, 0 means "md_id" is a vendor model.
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sub_set(u16 op, u16 node_adr, u16 ele_adr, u16 sub_adr, u32 md_id, bool4 sig_model);




/**************************cfg_cmd_pub_get**************************
function : cfg_cmd_pub_get,get the model 's pub addr  
para:
	node_adr: the node's element addr .
	ele_adr: the model's adr part 
	md_id: the special model id 
	sig_model: it is bool, 1 means "md_id" is a SIG model, 0 means "md_id" is a vendor model.
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_pub_get(u16 node_adr, u16 ele_adr, u32 md_id, bool4 sig_model);





/**************************cfg_cmd_pub_set**************************
function : cfg_cmd_pub_set,set the model 's pub addr  
para:
	node_adr: the node's element addr .
	ele_adr: the model's adr part 
	pub_adr: the adr used to set for the pub addr 
	md_id: the special model id 
	sig_model: it is bool, 1 means "md_id" is a SIG model, 0 means "md_id" is a vendor model.
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_pub_set(u16 node_adr, u16 ele_adr, u16 pub_adr, mesh_model_pub_par_t *pub_par, u32 md_id, bool4 sig_model);


/**************************cfg_cmd_sec_nw_bc_get**************************
function :get the current Secure Network Beacon state of a node 
para:
	node_adr: the node's element addr .
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/

int cfg_cmd_sec_nw_bc_get(u16 node_adr);



/**************************cfg_cmd_sec_nw_bc_set**************************
function :set the Secure Network Beacon state of a node 
para:
	node_adr: the node's element addr .
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sec_nw_bc_set(u16 node_adr, u8 val);



/**************************cfg_cmd_ttl_get**************************
function :used to get the current Default TTL state of a node 
para:
	node_adr: the node's element addr .
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_ttl_get(u16 node_adr);



/**************************cfg_cmd_ttl_set**************************
function :used to set the Default TTL state of a node 
para:
	node_adr: the node's element addr .
	val : the val will set to the ttl value 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_ttl_set(u16 node_adr, u8 val);



/**************************cfg_cmd_nw_transmit_get**************************
function :get the current Network Transmit state of a node 
para:
	node_adr: the node's element addr . 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_nw_transmit_get(u16 node_adr);



/**************************cfg_cmd_nw_transmit_set**************************
function :set the Network Transmit state of a node
para:
	node_adr: the node's element addr . 
	cnt:Number of transmissions for each Network PDU originating from the node
	invl_10ms:Number of 10-millisecond steps between transmissions
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_nw_transmit_set(u16 node_adr, u8 cnt, u8 invl_10ms);



/**************************cfg_cmd_relay_get**************************
function :get the current Relay
para:
	node_adr: the node's element addr . 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_relay_get(u16 node_adr);



/**************************cfg_cmd_relay_set**************************
function :get the current Relay
para:
	node_adr: the node's element addr . 
	val:set the Relayand and Relay Retransmit
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_relay_set(u16 node_adr, mesh_cfg_model_relay_set_t relay_set);



/**************************cfg_cmd_friend_get**************************
function :used to set the Friend state of a node
para:
	node_adr: the node's element addr . 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_friend_get(u16 node_adr);




/**************************cfg_cmd_friend_set**************************
function :used to set the Friend state of a node
para:
	node_adr: the node's element addr . 
	val:set the sts to the friend part 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_friend_set(u16 node_adr, u8 val);



/**************************cfg_cmd_proxy_get**************************
function :used to get the current GATT Proxy state of a node
para:
	node_adr: the node's element addr . 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_proxy_get(u16 node_adr);



/**************************cfg_cmd_proxy_set**************************
function :used to set the GATT Proxy state of a node
para:
	node_adr: the node's element addr . 
	val: the val of the New GATT Proxy state
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_proxy_set(u16 node_adr, u8 val);




/**************************cfg_cmd_cps_get**************************
function :an acknowledged message used to read one page of the Composition Data
para:
	node_adr: the node's element addr . 
	page: the page of the element,initial is 0
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_cps_get(u16 node_adr, u8 page);

/**************************cfg_cmd_large_cps_data_get**************************
function :read a portion of a page of the composition Data
para:
	node_adr: the node's element addr . 
	page: page number of the composition Data
	offset:offset within the page
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_large_cps_data_get(u16 node_adr, u8 page, u16 offset);

/**************************cfg_cmd_models_metadata_get**************************
function :used to read a portion of a page of the models metadata state
para:
	node_adr: the node's element addr . 
	page: page number of the composition Data
	offset:offset within the page
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_models_metadata_get(u16 node_adr, u8 page, u16 offset);

/**************************cfg_cmd_reset_node**************************
function :used to reset a node (other than a Provisioner) and remove it from the network.
para:
	node_adr: the node's element addr . 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_reset_node(u16 node_adr);



/**************************cfg_cmd_sig_model_app_get**************************
function :used to request report of all AppKeys bound to the SIG Model
para:
	node_adr: the node's element addr . 
	ele_adr : the ele adr of the node 
	model_id: the id of the model 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sig_model_app_get(u16 node_adr, u16 ele_adr, u16 model_id);



/**************************cfg_cmd_sig_model_app_set**************************
function :used to add an AppKey to the AppKey List on a node
para:
	node_adr: the node's element addr . 
	p_app_idx : Index of the NetKey and index of the AppKey
	p_app_key: the content of the app key ,the length is 16 bytes 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sig_model_app_set(u16 node_adr ,u8 *p_app_idx,u8 *p_app_key);



/**************************cfg_cmd_vd_model_app_get**************************
function :used to request report of all AppKeys bound to the model
para:
	node_adr: the node's element addr . 
	ele_adr : the ele adr of the node 
	model_id: the id of the model 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_vd_model_app_get(u16 node_adr, u16 ele_adr, u32 model_id);



/**************************cfg_cmd_key_phase_get**************************
function :used to get the current Key Refresh Phase state of the identified network key
para:
	node_adr: the node's element addr . 
	nk_idx: the index of the network key
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_key_phase_get(u16 node_adr, u16 nk_idx);



/**************************cfg_cmd_key_phase_set**************************
function :used to set the Key Refresh Phase state of the identified network key
para:
	node_adr: the node's element addr . 
	nk_idx: the index of the network key
	transition:the netkeyindex and the transition 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_key_phase_set(u16 node_adr, u16 nk_idx, u8 transition);




/**************************cfg_cmd_node_identity_set**************************
function :used to set the current Node Identity state
para:
	node_adr: the node's element addr . 
	nk_idx: the index of the network key
	identity: the identity value of the network 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_node_identity_set(u16 node_adr, u16 nk_idx, u8 identity);



/**************************cfg_cmd_node_identity_get**************************
function :used to get the current Node Identity state for a subnet
para:
	node_adr: the node's element addr . 
	nk_idx: the index of the network key
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_node_identity_get(u16 node_adr, u16 nk_idx);




/**************************cfg_cmd_lpn_poll_timeout_get**************************
function :used to get the current value of PollTimeout timer of the Low Power node within a Friend node
para:
	node_adr: the node's element addr . 
	adr_lpn: the lowpower adr of the node 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_lpn_poll_timeout_get(u16 node_adr, u16 adr_lpn);




/**************************cfg_cmd_nk_add**************************
function :used to add a NetKey to a NetKey List on a node
para:
	node_adr: the node's element addr . 
	nk_idx: the idx of the network 
	key: the pointer of the network key 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_nk_add(u16 node_adr, u16 nk_idx, u8 *key);




/**************************cfg_cmd_nk_update**************************
function :used to update a NetKey on a node
para:
	node_adr: the node's element addr . 
	nk_idx: the idx of the network 
	key: the pointer of the network key 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_nk_update(u16 node_adr, u16 nk_idx, u8 *key);



/**************************cfg_cmd_nk_del**************************
function :delete a NetKey on a NetKey List from a node
para:
	node_adr: the node's element addr . 
	nk_idx: the idx of the network 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_nk_del(u16 node_adr, u16 nk_idx);



/**************************cfg_cmd_ak_add**************************
function :add an AppKey to the AppKey List on a node
para:
	node_adr: the node's element addr . 
	nk_idx: the idx of the network
	ak_idx: the appkey idx of the network 
	key: the appkey 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_ak_add(u16 node_adr, u16 nk_idx, u16 ak_idx, u8 *key);




/**************************cfg_cmd_ak_update**************************
function :update an AppKey value on the AppKey List on a node
para:
	node_adr: the node's element addr . 
	nk_idx: the idx of the network
	ak_idx: the appkey idx of the network 
	key: the appkey 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_ak_update(u16 node_adr, u16 nk_idx, u16 ak_idx, u8 *key);



/**************************cfg_cmd_ak_del**************************
function :used to delete an AppKey from the AppKey List on a node
para:
	node_adr: the node's element addr . 
	nk_idx: the idx of the network
	ak_idx: the appkey idx of the network 
	key: the appkey 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_ak_del(u16 node_adr, u16 nk_idx, u16 ak_idx);





/**************************cfg_cmd_ak_bind**************************
function :App Bind is an acknowledged message used to bind an AppKey to a model	
para:
	node_adr: the node's element addr . 
	ele_adr: the element adr of the node 
	ak_idx: the appkey idx of the network 
	md_id: the model id 
	sig_model: the mode is sigmodel or not 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_ak_bind(u16 node_adr, u16 ele_adr, u16 ak_idx, u32 md_id, bool4 sig_model);



/**************************mesh_proxy_set_filter_type**************************
function :set the proxy filter type
para:
	filter_type: 0 is white list ,1 is black list 
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int mesh_proxy_set_filter_type(u8 filter_type);



/**************************mesh_proxy_filter_add_adr**************************
function :add the adr into the filter 
para:
	adr: the adr can be group or unicast adr  
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int mesh_proxy_filter_add_adr(u16 adr);

/**************************cfg_cmd_subnet_bridge_get**************************
function :send subnet bridge get message 
para:
	dst_addr: address of the destination  
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_subnet_bridge_get(u16 dst_addr);

/**************************cfg_cmd_subnet_bridge_set**************************
function :send subnet bridge set message 
para:
	dst_addr: address of the destination  
	en:0 disable, 1 enable
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_subnet_bridge_set(u16 dst_addr, u8 en);

/**************************cfg_cmd_bridge_table_get**************************
function :get bridge table 
para:
	dst_addr: address of the destination
	key_idx1:netKey index of first subnet
	key_idx2:netKey index of second subnet
	start_idx:start offset to read bridging table
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_bridge_table_get(u16 dst_addr, u16 key_idx1, u16 key_idx2, u16 start_idx);

/**************************cfg_cmd_bridge_table_add**************************
function :add bridge table 
para:
	dst_addr: address of the destination
	direction:allowed directions for the bridged traffic
	key_idx1:netKey index of first subnet
	key_idx2:netKey index of second subnet
	addr1:address of the node in the first subnet
	addr2:address of the node in the second subnet
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_bridge_table_add(u16 dst_addr, u8 direction, u16 key_idx1, u16 key_idx2, u16 addr1, u16 addr2);

/**************************cfg_cmd_bridge_table_remove**************************
function :remove bridge table 
para:
	dst_addr: address of the destination
	key_idx1:netKey index of first subnet
	key_idx2:netKey index of second subnet
	addr1:address of the node in the first subnet
	addr2:address of the node in the second subnet
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_bridge_table_remove(u16 dst_addr, u16 key_idx1, u16 key_idx2, u16 addr1, u16 addr2);

/**************************cfg_cmd_bridge_subnet_get**************************
function :bridge subnet get 
para:
	dst_addr: address of the destination
	filter:filter to be applied when reporting the set of pairs of netKey indexes
	netkey_idx:netKey index of second subnet
	start_idx:start offset to read
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_bridge_subnet_get(u16 dst_addr, u8 filter, u16 netkey_idx, u16 start_idx);

/**************************cfg_cmd_bridge_tbl_size_get**************************
function :bridge table size get 
para:
	dst_addr: address of the destination
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_bridge_tbl_size_get(u16 dst_addr);

/**************************cfg_cmd_on_demand_private_proxy_get**************************
function :get the current on-demand private GATT proxy state 
para:
	dst_addr: address of the destination
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_on_demand_private_proxy_get(u16 dst_addr);

/**************************cfg_cmd_on_demand_private_proxy_set**************************
function :get the current on-demand private GATT proxy state 
para:
	dst_addr: address of the destination
	en:1 for enable private proxy state
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_on_demand_private_proxy_set(u16 dst_addr, u8 en);

/**************************cfg_cmd_sar_transmitter_get**************************
function :get the current SAR transmitter state of a node
para:
	dst_addr: address of the destination
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sar_transmitter_get(u16 dst_addr);

/**************************cfg_cmd_sar_transmitter_set**************************
function :set the SAR transmitter state
para:
	dst_addr: address of the destination
	seg_invl_step:new SAR segment interval step state
	unicast_retran_cnt:new SAR unicast Retransmissions count state
	unicast_retran_cnt_noack:new SAR unicast retransmissions without progress count state
	unicast_retran_invl_step:new SAR unicast retransmissions interval step state
	unicast_retran_invl_inc:new SAR unicast retransmissions interval increment state
	multicast_retran_cnt:new SAR multicast retransmissions count state
	multicast_retran_invl:new SAR multicast retransmissions interval state
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sar_transmitter_set(u16 dst_addr, u8 seg_invl_step, u8 unicast_retran_cnt, u8 unicast_retran_cnt_noack, u8 unicast_retran_invl_step, u8 unicast_retran_invl_inc, u8 multicast_retran_cnt, u8 multicast_retran_invl);

/**************************cfg_cmd_sar_receiver_get**************************
function :get the current SAR transmitter state of a node
para:
	dst_addr: address of the destination
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sar_receiver_get(u16 dst_addr);

/**************************cfg_cmd_sar_receiver_set**************************
function :get the current SAR transmitter state of a node
para:
	dst_addr: address of the destination
	seg_threshold:new SAR segments threshold state
	ack_delay_inc:new SAR scknowledgment delay increment state
	discard_timeout:new SAR discard timeout state
	rcv_seg_invl_step:new SAR receiver segment interval step state
	ack_retrans_cnt:new SAR acknowledgment retransmissions count state
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_sar_receiver_set(u16 dst_addr, u8 seg_threshold, u8 ack_delay_inc, u8 discard_timeout, u8 rcv_seg_invl_step, u8 ack_retrans_cnt);

/**************************cfg_cmd_soli_pdu_rpl_clear**************************
function :remove one or more items from the solicitation replay protection list of a node
para:
	dst_addr: address of the destination
	start_addr:range start address or unicast address
	range_len:address range length
	ack:1 means SOLICITATION_PDU_RPL_ITEMS_CLEAR, 0 means SOLICITATION_PDU_RPL_ITEMS_CLEAR_UNACKNOWLEDGED
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_soli_pdu_rpl_clear(u16 dst_addr, u16 start_addr, u8 range_len, int ack);

/**************************cfg_cmd_op_agg_sequence**************************
function : encapsulate a sequence of access messages
para:
	dst_addr: address of the destination
	para:element address and items
	len:para len
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_op_agg_sequence(u16 dst_addr, u8 *para, int len);

/**************************cfg_cmd_op_agg_sequence**************************
function : set the current heartbeat publication state
para:
	dst_addr: address of the destination
	count_log:number of heartbeat messages to be sent
	period_log:period for sending heartbeat messages
	ttl:TTL to be used when sending heartbeat messages
	features:bit field indicating features that trigger heartbeat messages when changed
	netkey_index:netKey index
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_heartbeat_pub_set(u16 dst_addr, u16 pub_addr, u8 count_log, u8 period_log, u8 ttl, u16 features, u16 netkey_index);

/**************************mesh_proxy_filter_remove_adr**************************
function :remove the adr into the filter 
para:
	adr: the adr can be group or unicast adr  
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int mesh_proxy_filter_remove_adr(u16 adr);


// basic interface ,not need to notice this ,status handle(reference only)
int cfg_cmd_nk_set(u16 op, u16 node_adr, u16 nk_idx, u8 *key);
int mesh_proxy_set_filter_cmd(u8 opcode,u8 filter_type, u8 * dat,u8 len );
int mesh_proxy_set_filter_init(u16 self_adr);
/**************************mesh_directed_proxy_control_set**************************
function :set whether or not the Directed Proxy Server uses directed forwarding for Directed Proxy Client messages for a specified
			range of unicast addresses 
para:
	use_directed: use directed or not   
	range_start: unicast addresses to use directed
	range_len:element count of the unicast addresses
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int mesh_directed_proxy_control_set(u8 use_directed, u16 range_start, u8 range_len);

/**************************mesh_send_proxy_solicitation_pdu**************************
function :set the solicitation pdu message, it will be send in function set_adv_solicitation() called by gatt_adv_prepare_handler()
para:
	adr_dst: destination address  
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int mesh_send_proxy_solicitation_pdu(u16 adr_dst);

/**************************cfg_cmd_send_path_solicitation**************************
function :solicit the discovery of paths from other directed forwarding nodes
para:
	addr_list:list of destination addresses
	num:number of destination addresses
ret: 0  means OK 
	-1 or other value means err
****************************************************************************/
int cfg_cmd_send_path_solicitation(u16 netkey_offset, u16 *addr_list, int num);

#if WIN32
/*******************json_get_net_info****************************
use to get the provision information form the stack ,it can call in the provision end callback fun
p_netkey_val:network key 16 bytes 
p_netkey_idx: network key index 
p_ivi: 4 bytes of the provision ivi index 
ivi_key_flag: 1bytes
unicast: unicast adr
**************************************************************/
void json_get_net_info(u8 *p_netkey_val,u16 *p_netkey_idx,u8 *p_ivi,u8 *ivi_key_flag,u16 *unicast);

/*******************json_get_dev_key_info****************************
use to get the devicekey from the stack ,and the length is 16 bytes ,,it can call in the provision end callback fun
dev_key: the pointer of the devkey ,16 bytes
**************************************************************/
void json_get_dev_key_info(u8 * dev_key);


/*******************json_get_appkey_info****************************
use to get the devicekey from the stack ,and the length is 16 bytes ,it can call when appkey bind endcallback 
dev_key: the pointer of the devkey ,16 bytes
**************************************************************/
void json_get_appkey_info(u8 *appkey_val,u16 *appkey_idx);

#endif

