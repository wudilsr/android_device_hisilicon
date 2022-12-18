#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
//#include "tee_socket_debug.h"
#include "agent_socket_buffer.h"
#include "agent_socket_listener.h"
#ifdef AGENT_SOCKET_ENABLE
#define LOG_NDEBUG 0
#define LOG_TAG "teecd"
#include <cutils/log.h>
#include "tee_client_type.h"
#include "../tc_ns_client.h"
#define LOGE ALOGE
#define LOGV
#else
#define LOGV printf
#define LOGE printf
#endif

int socket_agent_fd = -1;
static struct socket_buffer_pool_t *g_socket_pool = NULL;

/* All these macros value from SecureOS */
#define IP_VERSION_4 1
#define IP_VERSION_6 2
#define TEE_ISOCKET_PROTOCOLID_TCP_IP 0x65
#define TEE_ISOCKET_PROTOCOLID_UDP 0x66
#define TEE_ISOCKET_ERROR_PROTOCOL 0xF1007001
#define TEE_ISOCKET_ERROR_REMOTE_CLOSED 0xF1007002
#define TEE_ISOCKET_ERROR_TIMEOUT 0xF1007003
#define TEE_ISOCKET_ERROR_OUT_OF_RESOURCES 0xF1007004
#define TEE_ISOCKET_ERROR_LARGE_BUFFER 0xF1007005
#define TEE_ERROR_COMMUNICATION 0xFFFF000E
#define TEE_TIMEOUT_INFINITE (0xFFFFFFFF)
/* macros value from SecureOS over */

enum SOCKET_CMD_TYPE {
    SOCKET_SEND = 1,
    SOCKET_RECV,
    SOCKET_IOCTL,
};

struct buffer_ctx {
    uint8_t *buffer;
    uint32_t length;
    uint32_t pos;
    uint32_t real_len;
};
static struct buffer_ctx gs_tmp_buffer = {0};

static void socket_gethostip_work(struct socket_ctrl_t *trans_ctrl) {
    struct hostent *he;
    struct in_addr **addr_list;
    char *hostname;
    char *hostip = NULL;

    hostname = trans_ctrl->args.gethostip.hostname;
    if ((he = gethostbyname(hostname)) == NULL) {
        LOGE("gethostbyname %s failed\n", hostname);
        trans_ctrl->ret = AGENT_CMD_GETHOSTIP_ERR;
        return;
    }

    //h_addrtype: The type of address; always AF_INET or AF_INET6 at present.
    if (he->h_addrtype == AF_INET) {
        trans_ctrl->args.gethostip.domain = IP_VERSION_4;
    } else if(he->h_addrtype == AF_INET6) {
        trans_ctrl->args.gethostip.domain = IP_VERSION_6;
    } else {
        trans_ctrl->ret = AGENT_CMD_GETHOSTIP_ERR;
        return;
    }

    addr_list = (struct in_addr **)he->h_addr_list;
    hostip = inet_ntoa(*addr_list[0]);
    if (hostip == NULL) {
        trans_ctrl->ret = AGENT_CMD_GETHOSTIP_ERR;
        return;
    }
    memcpy(trans_ctrl->args.gethostip.host_ip, hostip, SERVER_ADDR_MAX_LEN);
    LOGV("%s resolved to %s, domain=%d\n",
        hostname,
        trans_ctrl->args.gethostip.host_ip,
        trans_ctrl->args.gethostip.domain);
    trans_ctrl->ret = AGENT_CMD_SUCCESS;
}

static void socket_open_work(struct socket_ctrl_t *trans_ctrl) {
    int sockfd = -1;
    int domain, type, protocol;
    struct sockaddr_in server_addr;

    /* verify the communication domain */
    if (trans_ctrl->args.open.domain == IP_VERSION_4) {
        domain = AF_INET;
    } else if(trans_ctrl->args.open.domain == IP_VERSION_6) {
        domain = AF_INET6;
    } else {
        trans_ctrl->ret = AGENT_CMD_OPEN_DOMAIN_ERR;
        goto cleanup;
    }

    /* verify the communication protocol */
    if (trans_ctrl->args.open.protocol == TEE_ISOCKET_PROTOCOLID_TCP_IP) {
        type = SOCK_STREAM;
        protocol = IPPROTO_TCP;
    } else if(trans_ctrl->args.open.protocol == TEE_ISOCKET_PROTOCOLID_UDP) {
        type = SOCK_DGRAM;
        protocol = IPPROTO_UDP;
    } else {
        trans_ctrl->ret = AGENT_CMD_OPEN_PROTOCOL_ERR;
        goto cleanup;
    }

    /* 1. create an endpoint for communication */
    if ((sockfd = socket(domain, type, protocol)) == -1) {
        LOGE("socket(%d %d %d) failed: %d\n",
            domain, type, protocol, errno);
        trans_ctrl->ret = AGENT_CMD_OPEN_SOCKET_FAIL;
        trans_ctrl->err = TEE_ISOCKET_ERROR_OUT_OF_RESOURCES;
        goto cleanup;
    }

    //UDP dont need to connect server
    if (protocol == IPPROTO_UDP)
        goto out;

    /* convert address from text to binary form */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = domain;
    server_addr.sin_port = htons(trans_ctrl->args.open.server_port);
    if (inet_pton(domain, trans_ctrl->args.open.server_addr, &server_addr.sin_addr) != 1) {
        LOGE("inet_pton failed: af=%d, src=%s\n",
            domain, trans_ctrl->args.open.server_addr);
        trans_ctrl->ret = AGENT_CMD_OPEN_INET_FAIL;
        goto cleanup;
    }

    /* 2. initiate a connection on a socket */
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        LOGE("connect to server(%s:%d) failed: %d\n",
            trans_ctrl->args.open.server_addr, trans_ctrl->args.open.server_port, errno);
        trans_ctrl->ret = AGENT_CMD_OPEN_SOCKET_FAIL;
        if (errno == ENETUNREACH || errno == ECONNREFUSED || errno == EHOSTDOWN)
            trans_ctrl->err = TEE_ERROR_COMMUNICATION;
        else // (errno == ETIMEDOUT)
            trans_ctrl->err = TEE_ISOCKET_ERROR_TIMEOUT;
        goto cleanup;
    }

out:
    trans_ctrl->ret = AGENT_CMD_SUCCESS;
    trans_ctrl->ret2 = sockfd;
    return;

cleanup:
    if (sockfd != -1)
        close(sockfd);
}

static void socket_close_work(struct socket_ctrl_t *trans_ctrl) {
    if (close(trans_ctrl->args.close.sockfd) == 0) {
        trans_ctrl->ret = AGENT_CMD_SUCCESS;
    } else {
        trans_ctrl->ret = AGENT_CMD_CLOSE_FAIL;
        LOGE("close socket failed: %d\n", errno);
    }
}

static void socket_send_work(struct socket_ctrl_t *trans_ctrl) {
    ssize_t ret;
    uint32_t length_whole, length_part;
    TEEC_UUID uuid;
    uint32_t ssid;

    /* Get the parameters from share memory */
    memcpy(&uuid, &trans_ctrl->service_id, sizeof(TEEC_UUID));
    ssid = trans_ctrl->session_id;
    length_whole = trans_ctrl->args.send.length_whole;
    length_part = trans_ctrl->args.send.length_part;

    // Store buffer to uuid-pool
    ret = socket_store_buffer(g_socket_pool,
        uuid, ssid,
        trans_ctrl->args.send.buffer,
        length_part, length_whole);

    if (ret == 0)
        trans_ctrl->ret = AGENT_CMD_SUCCESS;
    else
        trans_ctrl->ret = AGENT_GENERIC_OUT_OF_MEMORY;
}

static void socket_write_work(struct socket_ctrl_t *trans_ctrl) {
    ssize_t ret = -1;
    struct timeval timeout;
    int sockfd;
    uint32_t tee_timeout;
    int flags;
    TEEC_UUID uuid;
    uint32_t ssid;
    uint8_t *buf = NULL;
    uint32_t buf_len = 0;
    struct sockaddr_in server_addr;

    /* Get the parameters from share memory */
    memcpy(&uuid, &trans_ctrl->service_id, sizeof(TEEC_UUID));
    ssid = trans_ctrl->session_id;
    sockfd = trans_ctrl->args.write.sockfd;
    tee_timeout = trans_ctrl->args.write.timeout;

    if (tee_timeout != TEE_TIMEOUT_INFINITE) {
        timeout.tv_sec = tee_timeout / 1000;
        timeout.tv_usec = (tee_timeout - timeout.tv_sec * 1000) * 1000;
        ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        flags = 0;
    } else {
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        flags = MSG_WAITALL;
    }
    if (ret != 0) {
        LOGE("setsockopt failed: %d\n", errno);
        trans_ctrl->ret = AGENT_CMD_RECV_FAIL;
        return;
    }

    // Get the buffer from pool
    buf = socket_get_whole_buffer(g_socket_pool, uuid, ssid, &buf_len);

    // Transmit a message to another socket
    if (trans_ctrl->args.write.protocol == TEE_ISOCKET_PROTOCOLID_TCP_IP) {
        ret = send(sockfd, buf, buf_len, flags);
    } else if (trans_ctrl->args.write.protocol == TEE_ISOCKET_PROTOCOLID_UDP) {
        memset(&server_addr, 0, sizeof(server_addr));
        if (trans_ctrl->args.write.server.domain == IP_VERSION_4) {
            server_addr.sin_family = AF_INET;
        } else if(trans_ctrl->args.write.server.domain == IP_VERSION_6) {
            server_addr.sin_family = AF_INET6;
        }
        server_addr.sin_port = htons(trans_ctrl->args.write.server.server_port);
        ret = inet_pton(server_addr.sin_family,
                trans_ctrl->args.write.server.server_addr,
                &server_addr.sin_addr);
        if (ret != 1) {
		    LOGE("AGENT_CMD_SEND_FAIL ret=%d\n", ret);
            trans_ctrl->ret = AGENT_CMD_SEND_FAIL;
            return;
        }
        ret = sendto(sockfd, buf, buf_len, flags, (struct sockaddr*)&server_addr,sizeof(server_addr));
    }

    // Clear the buffer after send
    socket_clear_buffer(g_socket_pool, uuid, ssid);

    // Update the result
    if (ret != -1) {
        trans_ctrl->ret = AGENT_CMD_SUCCESS;
        trans_ctrl->ret2 = ret;
    } else {
        LOGE("send data to server failed: %d\n", errno);
        trans_ctrl->ret = AGENT_CMD_SEND_FAIL;
        if (errno == EPIPE || errno == ECONNRESET)
            trans_ctrl->err = TEE_ISOCKET_ERROR_REMOTE_CLOSED;
        else if (errno == EAGAIN || errno == ETIMEDOUT)
            trans_ctrl->err = TEE_ISOCKET_ERROR_TIMEOUT;
        else // errno: ECONNREFUSED, ECONNRESET, EHOSTDOWN, ENETDOWN, ENETRESET
            trans_ctrl->err = TEE_ERROR_COMMUNICATION;
    }
}

static void socket_read_work(struct socket_ctrl_t *trans_ctrl) {
    ssize_t ret;
    struct timeval timeout;
    int sockfd;
    uint32_t tee_timeout;
    int flags;
    TEEC_UUID uuid;
    uint32_t ssid;
    uint32_t length_whole;
    uint8_t *buf = NULL;
    uint32_t buf_len = 0;
    struct sockaddr_in server_addr;
    socklen_t server_addr_length = sizeof(server_addr);
    char s_addr[SERVER_ADDR_MAX_LEN];
    int s_port;

    /* Get the parameters from share memory */
    memcpy(&uuid, &trans_ctrl->service_id, sizeof(TEEC_UUID));
    ssid = trans_ctrl->session_id;
    sockfd = trans_ctrl->args.read.sockfd;
    tee_timeout = trans_ctrl->args.read.timeout;
    length_whole = trans_ctrl->args.read.length;

    if (tee_timeout != TEE_TIMEOUT_INFINITE) {
        timeout.tv_sec = tee_timeout / 1000;
        timeout.tv_usec = (tee_timeout - timeout.tv_sec * 1000) * 1000;
        ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        flags = 0;
    } else {
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        flags = MSG_WAITALL;
    }
    if (ret != 0) {
        LOGE("setsockopt failed: %d\n", errno);
        trans_ctrl->ret = AGENT_CMD_RECV_FAIL;
        return;
    }

    // Store buffer to uuid-pool
    ret = socket_store_buffer(g_socket_pool,
        uuid, ssid,
        NULL, 0, length_whole);

    // Get the buffer from pool
    buf = socket_get_whole_buffer(g_socket_pool, uuid, ssid, &buf_len);

    // Receive messages from a socket
    if (trans_ctrl->args.read.protocol == TEE_ISOCKET_PROTOCOLID_TCP_IP) {
        ret = recv(sockfd, buf, buf_len, flags);
    } else if (trans_ctrl->args.read.protocol == TEE_ISOCKET_PROTOCOLID_UDP) {
        ret = recvfrom(sockfd, buf, buf_len, flags, (struct sockaddr*)&server_addr, &server_addr_length);
    }

    if (ret == -1 || ret == 0) {
        LOGE("recv data from server failed: %d\n", errno);
        trans_ctrl->ret = AGENT_CMD_RECV_FAIL;
        if (errno == EPIPE || errno == ECONNRESET)
            trans_ctrl->err = TEE_ISOCKET_ERROR_REMOTE_CLOSED;
        else if (errno == EAGAIN || errno == ETIMEDOUT)
            trans_ctrl->err = TEE_ISOCKET_ERROR_TIMEOUT;
        else // errno: ECONNREFUSED, ECONNRESET, EHOSTDOWN, ENETDOWN, ENETRESET
            trans_ctrl->err = TEE_ERROR_COMMUNICATION;
        // Clear the buffer
        socket_clear_buffer(g_socket_pool, uuid, ssid);
    } else {
        trans_ctrl->ret = AGENT_CMD_SUCCESS;
        trans_ctrl->ret2 = ret;
        if (trans_ctrl->args.read.protocol == TEE_ISOCKET_PROTOCOLID_UDP) {
            inet_ntop(server_addr.sin_family, &server_addr.sin_addr, s_addr, sizeof(s_addr));
            s_port = ntohs(server_addr.sin_port);
            memcpy(trans_ctrl->args.read.server.server_addr, s_addr,
                sizeof(trans_ctrl->args.read.server.server_addr));
            trans_ctrl->args.read.server.server_port = s_port;
        }
        socket_update_buffer_length(g_socket_pool, uuid, ssid, ret);
    }
}

static void socket_recv_work(struct socket_ctrl_t *trans_ctrl) {
    TEEC_UUID uuid;
    uint32_t ssid;
    uint8_t *buf = NULL;
    uint32_t buf_len = 0;
    uint32_t last_frm;

    /* Get the parameters from share memory */
    memcpy(&uuid, &trans_ctrl->service_id, sizeof(TEEC_UUID));
    ssid = trans_ctrl->session_id;
    buf_len = trans_ctrl->args.recv.length_part;
    last_frm = trans_ctrl->args.recv.last_frame;

    // Get the buffer from pool
    buf = socket_get_part_buffer(g_socket_pool, uuid, ssid, &buf_len);
    memcpy(trans_ctrl->args.recv.buffer, buf, buf_len);
    trans_ctrl->ret = AGENT_CMD_SUCCESS;

    // Clear the buffer receive all data
    if (last_frm)
        socket_clear_buffer(g_socket_pool, uuid, ssid);
}

static void socket_ioctl_work(struct socket_ctrl_t *trans_ctrl) {
    int32_t sockfd, value = 0;
    uint32_t cmd;
    int ret = -1;

    /* Get the parameters from share memory */
    sockfd = trans_ctrl->args.ioctl.sockfd;
    cmd = trans_ctrl->args.ioctl.cmd;

    if (cmd == SOCKET_GET_AMOUNT_OF_UNREAD_DATA) {
        ret = ioctl(sockfd, FIONREAD, &value);
        trans_ctrl->ret2 = value;
    }

    if (ret < 0)
        trans_ctrl->ret = AGENT_CMD_IOCTL_FAIL;
    else
        trans_ctrl->ret = AGENT_CMD_SUCCESS;
}

struct socket_work_table {
    socket_cmd_t cmd;
    void (*socket_work)(struct socket_ctrl_t *trans_ctrl);
};
static struct socket_work_table socket_work_t[] = {
    {sec_socket_gethostip, socket_gethostip_work},
    {sec_socket_open, socket_open_work},
    {sec_socket_close, socket_close_work},
    {sec_socket_send, socket_send_work},
    {sec_socket_write, socket_write_work},
    {sec_socket_recv, socket_recv_work},
    {sec_socket_read, socket_read_work},
    {sec_socket_ioctl, socket_ioctl_work},
};
#define number_of_cmd(x) (sizeof(x)/sizeof(x[0]))

void* thread_socket_work(void *ctrl) {
    struct socket_ctrl_t *trans_ctrl = (struct socket_ctrl_t *)ctrl;
    int ret;
    int i, found = 0;

#ifdef AGENT_SOCKET_ENABLE
    while (1) {
        LOGV(" ++ socket agent loop ++ \n");
        ret = ioctl(socket_agent_fd, TC_NS_CLIENT_IOCTL_WAIT_EVENT, AGENT_SOCKET_ID);
        if(ret) {
            LOGE("socket agent wait event failed\n");
            break;
        }

        LOGV("socket agent wake up and working!! \n");
#endif

        for (i=0;i<number_of_cmd(socket_work_t);i++) {
            if (trans_ctrl->cmd == socket_work_t[i].cmd) {
                found = 1;
                socket_work_t[i].socket_work(ctrl);
            }
        }
        if (!found)
            trans_ctrl->ret = AGENT_CMD_NOT_SUPPORT;

#ifdef AGENT_SOCKET_ENABLE
        trans_ctrl->magic = AGENT_SOCKET_ID;
        ret = ioctl(socket_agent_fd, TC_NS_CLIENT_IOCTL_SEND_EVENT_RESPONSE, AGENT_SOCKET_ID);
        if(ret){
            LOGE("socket agent send reponse failed\n");
            break;
        }
        LOGV(" -- socket agent loop -- \n");
    }
#endif

    return NULL;
}

int socket_agent_init() {
    g_socket_pool = socket_pool_init();
    if (g_socket_pool)
        return 0;
    else
        return -1;
}
int socket_agent_exit() {
    if (g_socket_pool) {
        //TODO: free the socket pool
    }
    return 0;
}
