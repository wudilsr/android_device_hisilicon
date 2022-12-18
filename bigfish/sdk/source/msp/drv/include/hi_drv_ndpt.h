/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : priv_ndpt.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/11
  Description   :
  History       :
  1.Date        : 2010/11/11
    Author      : f00172091
    Modification: Created file

******************************************************************************/

#ifndef __PRIV_NDPT_H__
#define __PRIV_NDPT_H__

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "hi_common.h"
#include "hi_module.h"
#include "hi_debug.h"

#define RTP_PKT_MINLEN 60
#define NDPT_MAX_CHANNEL_COUNT 20

#define IPV4_ADDR_LEN   4
#define IPV6_ADDR_LEN   16
#define NDPT_ETH_ALEN   6
#define NDPT_ETH_HLEN   14
#define NDPT_IP_TOS_DEFAULT     (46<<2)     //DSCP EF

/*extern interface*/
/*CNcomment:�ⲿ�ӿ�*/
typedef enum
{
    LOOPBACK_NONE   = 0,    
    SEND_BACK,	          /*send-circle,data is neither sent to remote nor received from remote*/ /*CNcomment:���ͻ��أ����ݲ����͵�Զ�ˣ�Ҳ������Զ�˵�����*/
    SEND_BACK_AND_OUT,    /*send-circle,data is sent to remote,but refuse data from remote*/ /*CNcomment:���ͻ��أ�ͬʱ���ݷ��͵�Զ�ˣ���������Զ�˵�����*/
    REV_BACK,             /*receive-circle,host neither send data to remote nor receive from remote*/ /*CNcomment:���ջ��أ�����������Զ�����ݣ�Ҳ����Զ�˷�������*/
    REV_BACK_AND_IN,      /*receive-circle,host receive data from remote , but will not send data to remote*/ /*CNcomment:���ջ��أ���������Զ�����ݣ�������Զ�˷�������*/
    ALL_BACK,             /*nocircle for both send and receive,REV_BACK and SEND_BACK will be executing at the same time*/ /*CNcomment:���ͺͽ��ն����أ���SEND_BACK ��REV_BACKͬʱִ��*/
    LOOPBACK_MAX,
}NDPT_LOOPBACK_MODE_E;

/*change-flags for net parameter struct*/
/*CNcomment:��������ṹ�����־λ */
typedef struct
{
   HI_U32   bit1SrcIP:1;    /*change-flag for source ip, 32SrcIPLen and u8SrcIP[16] have be changed*/ /*CNcomment:source ip������, 32SrcIPLen��u8SrcIP[16]�и���*/ 
   HI_U32   bit1DstIP:1;    /*change-flag for dest ip, u32DstIPLen and u8DstIP[16] have be changed*/ /*CNcomment:dest ip������, u32DstIPLen��u8DstIP[16]�и���*/ 
   HI_U32   bit1SrcPort:1;  /*change-flag for source port, u16SrcPort has be changed*/ /*CNcomment:source port ������,u16SrcPort�и���*/ 
   HI_U32   bit1DstPort:1;	/*change-flag for dest port, u16DstPort has be changed*/ /*CNcomment:dest port������,u16DstPort�и���*/ 
   HI_U32   bit1IPTos:1;	/*change-flag for IP service type,u32IPTos and u32Mask have be changed*/ /*CNcomment:IP�������ͱ�����,u32IPTos��u32Mask�и���*/ 
   HI_U32   bit1Vlan:1;		/*change-flag for Vlan, u32VlanEn,u32VlanPri,u32VlanPid have be changed, reserved*/ /*CNcomment:Vlan������,u32VlanEn,u32VlanPri,u32VlanPid�и��ģ�����*/ 
   HI_U32   bit1Protocol:1;	/*change-flag for protocol type, only support IPV4, reserved*/ /*CNcomment:Э�����ͱ����ǣ�Ŀǰֻ֧��IPV4,����*/ 
   HI_U32   bit25Resv:25;         
}NDPT_NET_CHANGE_FLAG_S;

/*net parameter config*/
/*CNcomment:����������� */
typedef struct
{
    HI_U32 sip_len;      /*length of source ip address, IPV4:4, IPV6:16, other length is invalid*/ /*CNcomment:ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
    HI_U8 sip[16];       /*source ip, IPV4:4 bytes, IPV6:16 bytes,ip can't be string, eg: 4 bytes order is 192,168,1,1 for source ip 192.168.1.1*/
                         /*CNcomment:source ip��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ�������192.168.1.1Ϊ����4�ֽ�����Ϊ192,168,1,1*/
    HI_U32 dip_len;      /*length of dest ip address, IPV4:4, IPV6:16, other length is invalid*/ /*CNcomment:ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
    HI_U8 dip[16];       /*dest ip, IPV4:4, IPV6:16, ip can't be string*/
                         /*CNcomment:dest ip��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ���*/
    HI_U16 sport;        /*port number of source RTP, it should be even, the releated RTCP port number is sport+1*/ /*CNcomment:source RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1 */
    HI_U16 dport;        /*port number of dest RTP, it should be even, the releated RTCP port number is dport+1*/ /*CNcomment:dest RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1 */

    HI_U32 mask;         /*bit0: u32IPTos valid;*/ /*CNcomment:bit0: u32IPTos valid;*/
    HI_U32 ip_tos;       /*8 bits for IP server type*/ /*CNcomment:IP��������,8bit*/
    HI_U32 vlan_en;      /*1:enable vlan, 0:disable vlan, reserved*/ /*CNcomment:vlanʹ��: 0--vlan ��Ч,1--vlan ��Ч,����*/
    HI_U32 vlan_pri;     /*3 bits for priority of vlan, valid when u32VlanEn==1, reserved*/ /*CNcomment:vlan���ȼ�,3bit, u32VlanEnΪ1ʱ��Ч������*/
    HI_U32 vlan_pid;     /*vlan pid, 12bit, valid when u32VlanEn==1, reserved*/ /*CNcomment:vlan pid, 12bit, u32VlanEnΪ1ʱ��Ч������*/
    HI_U32 protocol;     /*protocol type, 0x0800--IPV4, 0x86dd--IPV6, only support IPV4, reserved*/ /*CNcomment:Э������,0x0800--IPV4, 0x86dd--IPV6��Ŀǰֻ֧��IPV4������*/
}NDPT_NET_PARA_S;

/*config net parameter struct*/
/*CNcomment:������������ṹ */
typedef struct hiNDPT_NET_CONFIG_PARA_S
{
    NDPT_NET_CHANGE_FLAG_S stChange;  /*chang-flag*/ /*CNcomment:�����־λ */

    NDPT_NET_PARA_S stBody;           /*net parameter config*/ /*CNcomment:�������ò��� */ 
}NDPT_NET_CONFIG_PARA_S;

typedef struct
{
    HI_U32  handle;
    NDPT_LOOPBACK_MODE_E    eLoopback;
}NDPT_LOOPBACK_S;

#define CMD_NDPT_CREATE_LINK              _IOW(HI_ID_NDPT,  0x1, NDPT_NET_PARA_S)
#define CMD_NDPT_DESTROY_LINK             _IOW(HI_ID_NDPT,  0x2, HI_U32)
#define CMD_NDPT_SET_LOOPBACK             _IOW(HI_ID_NDPT,  0x3, NDPT_LOOPBACK_S)

//-----------------------------------------------------------------------------------------------------

#define HI_FATAL_NDPT(fmt...) \
            HI_FATAL_PRINT(HI_ID_NDPT, fmt)

#define HI_ERR_NDPT(fmt...) \
            HI_ERR_PRINT(HI_ID_NDPT, fmt)

#define HI_WARN_NDPT(fmt...) \
            HI_WARN_PRINT(HI_ID_NDPT, fmt)

#define HI_INFO_NDPT(fmt...) \
            HI_INFO_PRINT(HI_ID_NDPT, fmt)


//#define RTP_BUFF_OFFSET   1

/*format definition of IP packet*/
/*CNcomment:IP���ݰ���ʽ����*/
typedef struct _HDR_IP_
{   
    HI_U8  ihl:4;  /*IP Header length in 32-bit*/
    HI_U8  ver:4;  /*IP protocol version */
    HI_U8  tos;    /*type of service*/
    HI_U16  len;   /*Length of  header and data in byte*/

    HI_U16  id;    /*Used for fragmentation*/
//  HI_U16  frag_offset:13;  /*Used for fragmentation*/
//  HI_U16  flag:3;  /*Used for fragmentation*/
    HI_U16 frag;

    HI_U8  ttl;       /*time to live*/
    HI_U8  protocol;  /*0x6 = TCP, 0x11 = UDP*/
    HI_U16  check;    /*Checksum of header only*/

    HI_U32  S_IP;     /*source IP address*/
    HI_U32  D_IP;     /*destination IP address*/
}HDR_IP;


/*format definition of UDP packet*/
/*CNcomment:UDP����ʽ����*/
typedef struct _HDR_UDP_
{   
    HI_U16  S_Port;    /*UDP source port*/
    HI_U16  D_Port;    /*UDP destination port*/
    HI_U16  len;       /*length of UDP header and data in bytes*/
    HI_U16  checkSum;  /*Checksum of UDP header and data*/
}HDR_UDP;



typedef struct _HDR_RTP_     /*format definition of RTP packet header*/ /*CNcomment:RTP���ݰ�ͷ��ʽ����*/
{   
    HI_U8  cc:4;       /*CSRC count */
    HI_U8  x:1;        /*header extension flag */
    HI_U8  p:1;        /*padding flag */
    HI_U8  ver:2;      /*protocol version */

    HI_U8  pt:7;       /*payload type */
    HI_U8  m:1;        /*marker bit */

    HI_U16  usSeq;     /*sequence number */

    HI_U32  uiTs;      /*4:timestamp */
    HI_U32  uiSsrc;    /*8:synchronization source */
}HDR_RTP;

typedef struct _HDR_RTCP_        /*RTCP packet header*/ /*CNcomment:RTCP���ݰ�ͷ */
{
    HI_U8  RC:5;     /*numbers of received report or SDES struct*/ /*CNcomment:���ձ������SDES�ṹ����Ŀ */
    HI_U8  P:1;      /*extra data flag*/ /*CNcomment:�������ݱ�־ */
    HI_U8  ver:2;    /*protocol version*/ /*CNcomment:Э��汾 */

    HI_U8  pt;       /*type of RTCP packet*/ /*CNcomment:RTCP���ݰ����� */

    HI_U16  usLen;   /*length of message packet, unit: 32bit*/ /*CNcomment:��Ϣ���ĳ��ȣ���λΪ32bit*/
}HDR_RTCP;


/*format definition of ARP packet*/
/*CNcomment:ARP����ʽ����*/
typedef struct _HDR_IPV4_ARP_
{   
    HI_U16  hd_type;            /*hardware type*/
    HI_U16  protocol_type;      /*protocol type*/
    HI_U8   hd_adr_len;         /*hardware address length*/
    HI_U8   protocol_adr_len;   /*protocol address length*/
    HI_U16  op_type;            /*operation type*/
    HI_U8   s_mac[NDPT_ETH_ALEN];
    HI_U8   s_ip[4];
    HI_U8   d_mac[NDPT_ETH_ALEN];
    HI_U8   d_ip[4];
}HDR_IPV4_ARP;

/*Note: This structure must be same as RTP_NET_BUFFER_STRU in HME_NET_Device.h*/
#ifdef RTP_BUFF_OFFSET
typedef struct
{
    HI_U8    *pucBufferHdr;  /*start address of datagram header*/ /*CNcomment:����ͷ��ʼ��ַ*/
    HI_U32    uiBufferLen;   /*length of buffer*/ /*CNcomment:buffer�ĳ���*/
    HI_U32    uiOffset;      /*offset between datagram header and RTP header*/ /*CNcomment:����ͷ��RTPͷ��ƫ��*/
}RTP_NET_BUFFER_STRU;
#else
typedef struct
{
    HI_U8    *pucBufferHdr;  /*start address of RTP datagram header*/ /*CNcomment:RTP����ͷ��ʼ��ַ*/
    HI_U32    uiBufferLen;   /*length of RTP data*/ /*CNcomment:RTP���ݳ���*/
}RTP_NET_BUFFER_STRU;
#endif

/*Note: This enum must be same as PORT_MODE in HME_NET_Device.h*/
typedef enum
{
    PORT_EVEN   = 0,     /*wraped by even port of datalink config, carry RTP stream*/ /*CNcomment:ʹ����·���õ�ż���˿ڷ�װ������RTP��*/
    PORT_ODD    = 1,	 /*wraped by odd port of datalink config, carry RTP stream*/ /*CNcomment:ʹ����·�������˿ڷ�װ������RTCP��*/
    PORT_CONFIG = 2      /*wraped by port number of datalink config*/ /*CNcomment:ʹ����·���õĶ˿ںŷ�װ*/
}PORT_MOD;

typedef enum
{
    NDPT_PROC_CMD_LOOKBACK  = 0,    /*set cicle-mode, parameter set refer to NDPT_LOOPBACK_MODE_E*/ /*CNcomment:���û���ģʽ��������ο�NDPT_LOOPBACK_MODE_E*/
    NDPT_PROC_CMD_RESETCNT,	    /*statistic for RESET send and receive*/ /*CNcomment:RESET���ͺͽ���ͳ��*/
    NDPT_PROC_CMD_SETIPTOS,         /*set IP TOS*/ /*CNcomment:����IP TOS*/
}NDPT_PROC_CMD;

typedef struct _NDPT_SEND_ERR_CNT_S
{
   HI_U32   bit1DstIP:1;	/*unable to reach dest IP address*/ /*CNcomment:Ŀ��IP��ַ�޷�����*/
   HI_U32   bit1SameIP:1;       /*source and dest ip are the same*/ /*CNcomment:source ��dest ip��ͬ*/
   HI_U32   bit1Long:1;         /*extra-packet*/ /*CNcomment:������*/
   HI_U32   bit1Skb:1;	        /*malloc skb failure*/ /*CNcomment:����skbʧ��*/
   HI_U32   bit1MacHd:1;	/*create mac header failure*/ /*CNcomment:����macͷʧ��*/
   HI_U32   bit1Xmit:1;	        /*dev_queue_xmit failure*/ /*CNcomment:dev_queue_xmitʧ��*/
   HI_U32   bit1Para:1;         /*invalid parameter for ndpt_rtp_sendto()*/ /*CNcomment:HI_DRV_NDPT_SendRtp()������������*/
   HI_U32   bit1NotReady:1;     /*channel is not ready to receive and send data*/ /*CNcomment:ͨ��δ׼�����շ�����*/
}NDPT_SEND_ERR_FLAG_S;

#define NDPT_REV_INTERVAL_NUM   1000   /*statistic of received RTP packets gap*/ /*CNcomment:���յ���RTP�����ͳ�Ƹ���*/

typedef struct _NDPT_PACKET_INTERVAL_S
{
    struct _NDPT_PACKET_INTERVAL_S *next;
    HI_U32  u32Interval;                       /*gaps between received RTP packets, unit is us*/ /*CNcomment:���յ���RTP�����,usΪ��λ*/
}NDPT_PACKET_INTERVAL_S;

/*Note: This type define must be same as ndpt_rtp_revfrom in HME_NET_Device.h*/
typedef HI_S32 (*ndpt_rtp_revfrom)(HI_U32 TransId, PORT_MOD even_odd, RTP_NET_BUFFER_STRU *data_buffer);

/*module NDPT channel control struct*/ /*CNcomment:NDPTģ��ͨ�����ƽṹ*/
typedef struct _NDPT_CH_S
{
    struct _NDPT_CH_S *prev;
    struct _NDPT_CH_S *next;
    
    HI_U32  handle;	        /*handle of net adapter channel*/ /*CNcomment:��������ͨ�����*/
    NDPT_NET_PARA_S stNetPara;  /*net config parameter*/ /*CNcomment:�������ò���*/
    NDPT_NET_CHANGE_FLAG_S  stNetFlag;  /*flag of net parameter config*/ /*CNcomment:����������ñ��*/
    
    HI_U8 ucSrc_mac[NDPT_ETH_ALEN];
    struct net_device *dev;
    HI_U8 ucDst_mac[NDPT_ETH_ALEN];

    NDPT_LOOPBACK_MODE_E    eLoopback;

    HI_U32 TransId;      /*ID for AV module channel*/ /*CNcomment:����Ƶģ��ͨ��ID*/
    ndpt_rtp_revfrom revfunc;    /*RTP data received function pointer of AV module*/ /*CNcomment:����Ƶģ��RTP���ݽ��պ���ָ��*/
    
    NDPT_SEND_ERR_FLAG_S stSendErrFlag;
    HI_U32 uiSendTry;
    HI_U32 uiSendOkCnt;
    HI_U32 uiRevRtpCnt;
    HI_U16 usRtpSendSeq;
    HI_U16 usRevFlag;       /*0:not begin to count*/ /*CNcomment:0--δ��ʼ����*/
    HI_U32 uiRevSeqMin;
    HI_U32 uiRevSeqMax;
    HI_U32 uiRevSeqCnt;
    struct timeval stArriveLast;    /*previous RTP datagram arrived time*/ /*CNcomment:��һ��RTP���ĵ���ʱ��*/
    struct _NDPT_PACKET_INTERVAL_S  *pstRevInterval;    /*interval array pointer of received RTP packets*/ /*CNcomment:���յ���RTP���������ָ��*/
    struct _NDPT_PACKET_INTERVAL_S  *pstRevIntervalHead;
    struct _NDPT_PACKET_INTERVAL_S  *pstRevIntervalTail;
    HI_U32  u32RevIntervalCnt;
    HI_U32  u32RevIntervalTotal;
}NDPT_CH_S;

/*
set circle mode for net adapter layer CNcomment:�������������ͨ������ģʽ��
input parameter:
      handle:handle of net adapter layer channel CNcomment:���������ͨ�������
      eLoopbackMode:circle mode CNcomment:����ģʽ��
return:
      0:success CNcomment:�ɹ�
      other:failure CNcomment:���� ʧ��
*/    
extern HI_S32 ndpt_set_loopback(HI_U32 handle,NDPT_LOOPBACK_MODE_E eLoopback);

#endif

