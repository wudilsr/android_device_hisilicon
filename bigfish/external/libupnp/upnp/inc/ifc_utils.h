/*
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _IFC_UTILS_H_
#define _IFC_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    IFC_UTILS_ACTIVE_NETWORK_ETH =  1,
    IFC_UTILS_ACTIVE_NETWORK_WIFI,
    IFC_UTILS_ACTIVE_NETWORK_UNKNOWN,
    IFC_UTILS_ACTIVE_NETWORK_BUTTOM
} IFC_E_UTILS_ACTIVE_NETWORK;

typedef enum
{
    IFC_UTILS_NETWORK_TYPE_IPTV = 1,
    IFC_UTILS_NETWORK_TYPE_HOST,
    IFC_UTILS_NETWORK_TYPE_BOTTOM
} IFC_UTILS_NETWORK_TYPE;

int ifc_init(void);

int ifc_get_ifindex(const char *name, int *if_indexp);
int ifc_get_hwaddr(const char *name, void *ptr);

int ifc_up(const char *name);
int ifc_down(const char *name);

int ifc_set_addr(const char *name, unsigned addr);
int ifc_set_mask(const char *name, unsigned mask);

int ifc_create_default_route(const char *name, unsigned addr);

int ifc_get_info(const char *name, unsigned *addr, unsigned *mask, unsigned *flags);

const char *ifc_get_ipaddr(const char *ifname);

const char *ifc_get_netmask(const char *ifname);

int ifc_get_netlink_status(const char *ifname);

const char *ifc_get_mac(const char *ifname);

const IFC_E_UTILS_ACTIVE_NETWORK ifc_get_active_network();
const char* ifc_get_ipaddr_by_type(IFC_E_UTILS_ACTIVE_NETWORK enActiveNetwork,
                                   IFC_UTILS_NETWORK_TYPE enNetworkType);
const char* ifc_get_macaddr_by_type(IFC_E_UTILS_ACTIVE_NETWORK enType);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
