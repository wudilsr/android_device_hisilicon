#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include <sys/times.h>
#ifndef ANDROID
#include <ifaddrs.h>
#else
#include <cutils/properties.h>
#include <sys/system_properties.h>
#endif

#ifndef ANDROID
#define DBG(fmt, args...) \
	printf("%s:%d "fmt, __func__, __LINE__, ##args)
#else
#define LOG_TAG "ipconflict"
#include <utils/Log.h>
#define DBG(args...)\
	android_printLog(ANDROID_LOG_INFO, LOG_TAG, args)
#endif

#define ARP_LEN  \
	(sizeof(struct arphdr) + (2 * sizeof(uint32_t)) + (2 * ETH_ALEN) + 10 )

#define DETECT_GAP 2.0

struct interface {
	char name[IFNAMSIZ];
	char hwaddr[ETH_ALEN];
	int protocol;
	int arpsock;
	size_t hwlen;
	unsigned int ifindex;
	struct in_addr addr;
};

static int getmac(char * mac, int size)
{
	struct ifreq ifreq;
	int sock;

	if (!mac || size < ETH_ALEN)
		return -1;

	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		DBG("socket:%m\n");
		return -1;
	}

	strncpy (ifreq.ifr_name, "eth0", sizeof(ifreq.ifr_name));

	if (ioctl(sock, SIOCGIFHWADDR, &ifreq) < 0) {
		DBG("ioctl SIOCGIFHWADDR:%m\n");
		close(sock);
		return -1;
	}

	close(sock);
	memcpy(mac, ifreq.ifr_hwaddr.sa_data, ETH_ALEN);

	return 0;
}

#ifndef ANDROID
static int getifip(const char *ifname, struct in_addr *addr)
{
	struct ifaddrs *if_addr, *tmp;
	struct sockaddr_in *inaddr;
	int flag_get_ip = 0;

	if (getifaddrs(&if_addr) != 0) {
		DBG("getifaddrs:%m\n");
		return -1;
	}

	tmp = if_addr;
	while (if_addr) {
		if (if_addr->ifa_addr->sa_family != AF_INET) {
			if_addr = if_addr->ifa_next;
			continue;
		}

		if (!flag_get_ip) {
			inaddr = (struct sockaddr_in *)(if_addr->ifa_addr);
			memcpy(addr, &(inaddr->sin_addr), sizeof(struct in_addr));
			flag_get_ip = 1;
		}

		if_addr = if_addr->ifa_next;
	}

	freeifaddrs(tmp);
	return flag_get_ip?0:-1;
}

#else
static int getifip(const char *ifname, struct in_addr *addr)
{
	int sock;
	struct sockaddr_in *inaddr;
	struct ifreq ifr;

	if (!ifname || !addr)
		return -1;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		DBG("socket:%m\n");
		return -1;
	}

	strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;
	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
		DBG("ioctl:%m\n");
		close(sock);
		return -1;
	}

	close(sock);
	inaddr = (struct sockaddr_in*)&(ifr.ifr_addr);
	memcpy(addr, &(inaddr->sin_addr), sizeof(struct in_addr));
	return 0;
}  
#endif

static int if_nametoindex(const char *iface, unsigned int *ifindex)
{
	struct ifreq ifr;
	int sock;

	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", iface);

	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        DBG("socket:%m\n");
        return -1;
    }

	if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
		DBG("ioctl SIOCGIFINDEX:%m\n");
		close(sock);
		return -1;
    }

	close(sock);
	if (ifindex)
		*ifindex = ifr.ifr_ifindex;
	return ifr.ifr_ifindex;
}

static void dump_arp_packet(int dir, char *hw_s, char *hw_t,
	in_addr_t *ip_s, in_addr_t *ip_t)
{
	char ip[16];
#ifndef ANDROID
	printf(
#else
	android_printLog(ANDROID_LOG_WARN, LOG_TAG, 
#endif
	"\n%s:\n\t%-10s: %02x:%02x:%02x:%02x:%02x:%02x"
		"\n\t%-10s: %s"
		"\n\t%-10s: %02x:%02x:%02x:%02x:%02x:%02x"
		"\n\t%-10s: %s\n",
		dir?"SEND":"RECV",
		"Source MAC",
		hw_s[0], hw_s[1],hw_s[2],hw_s[3],hw_s[4],hw_s[5],
		"Source IP",
		inet_ntop(AF_INET, (void *)ip_s, ip, sizeof(ip)),
		"Target MAC",
		hw_t[0], hw_t[1],hw_t[2],hw_t[3],hw_t[4],hw_t[5],
		"Target IP",
		inet_ntop(AF_INET, (void *)ip_t, ip, sizeof(ip)));
}

int open_socket(struct interface *iface)
{
	int s;
	union sockunion {
		struct sockaddr sa;
		struct sockaddr_in sin;
		struct sockaddr_ll sll;
		struct sockaddr_storage ss;
	} su;
	int flags, ret = 0;


	if ((s = socket(PF_PACKET, SOCK_DGRAM, htons(iface->protocol))) == -1) {
		DBG("socket: %m");
		return -1;
	}

	memset(&su, 0, sizeof(su));
	su.sll.sll_family = PF_PACKET;
	su.sll.sll_protocol = htons(iface->protocol);
	if (!(su.sll.sll_ifindex = if_nametoindex(iface->name, NULL))) {
		errno = ENOENT;
		DBG("if_nametoindex:%m\n");
		goto exit;
	}

	if ((flags = fcntl(s, F_GETFD, 0)) == -1 ||
	    fcntl(s, F_SETFD, flags | O_NONBLOCK ) == -1) {
		DBG( "fcntl O_NONBLOCK: %m");
		ret = -1;
		goto exit;
	}
	
	if ((flags = fcntl(s, F_GETFD, 0)) == -1 ||
	    fcntl(s, F_SETFD, flags | FD_CLOEXEC) == -1) {
		DBG( "fcntl FD_CLOEXEC: %m");
		ret = -1;
		goto exit;
	}

	if (bind(s, &su.sa, sizeof(su)) == -1) {
		DBG( "bind: %m");
		ret = -1;
		goto exit;
	}
	ret = s;
	iface->arpsock = s;

exit:
	return ret;
}

ssize_t send_raw_packet(struct interface *iface, const void *data, ssize_t len)
{
	union sockunion {
		struct sockaddr sa;
		struct sockaddr_ll sll;
		struct sockaddr_storage ss;
	} su;

	memset(&su, 0, sizeof(su));
	su.sll.sll_family = AF_PACKET;
	su.sll.sll_protocol = htons(iface->protocol);

	if (!(su.sll.sll_ifindex = if_nametoindex(iface->name, NULL))) {
		errno = ENOENT;
		DBG("invalid ifindex:%m\n");
		return -1;
	}

	su.sll.sll_hatype = htons(ARPHRD_ETHER);
	su.sll.sll_halen = ETH_ALEN;
	memset(&su.sll.sll_addr, 0xff, ETH_ALEN);

	return sendto(iface->arpsock, data, len, 0, &su.sa, sizeof(su));
}

int send_arp_probe(struct interface *iface, int arp_op)
{
	char arp_buffer[ARP_LEN];
	struct arphdr *arp;
	size_t len;
	char *p;
	int retval;
	char *hw_s = arp_buffer + sizeof(*arp);
	char *hw_t = (hw_s + ETH_ALEN + sizeof(iface->addr));
	in_addr_t *ip_s = (in_addr_t *)(hw_s + ETH_ALEN);
	in_addr_t *ip_t = (in_addr_t *)(hw_t + ETH_ALEN);

	arp = (struct arphdr *)arp_buffer;
	arp->ar_hrd = htons(ARPHRD_ETHER);
	arp->ar_pro = htons(ETHERTYPE_IP);
	arp->ar_hln = ETH_ALEN;
	arp->ar_pln = 4;
	arp->ar_op = htons(arp_op);
	p = arp_buffer + sizeof(*arp);

	getmac(p, ETH_ALEN);
	p += ETH_ALEN;

	memcpy(p, &(iface->addr), sizeof(iface->addr));
	p += sizeof(iface->addr);

	/* ARP requests should ignore this */
	memset(p, 0, ETH_ALEN);
	p += ETH_ALEN;

	memcpy(p, &(iface->addr), sizeof(iface->addr));
	p += sizeof(iface->addr);
	
	len = p - arp_buffer;
	retval = send_raw_packet(iface, arp_buffer, len);
	if (retval > 0)
		dump_arp_packet(1, hw_s, hw_t, ip_s,ip_t);

	return retval;
}


ssize_t rcv_raw_packet(int fd, void *data, ssize_t len)
{
	struct iovec iov = {
		.iov_base = data,
		.iov_len = len,
	};
	struct msghdr msg = {
		.msg_iov = &iov,
		.msg_iovlen = 1,
	};
	ssize_t bytes;

	bytes = recvmsg(fd, &msg, MSG_DONTWAIT);
	if (bytes == -1)
		return errno == EAGAIN ? 0 : -1;

	return bytes;
}

int handle_arp_packet(struct interface *iface)
{
	char arp_buffer[ARP_LEN];
	struct arphdr arph;
	uint32_t reply_s;
	uint32_t reply_t;
	char *hw_s, *hw_t;
	ssize_t bytes;
	char ip[32];

	int sc_clk_tck;
	clock_t begin, end;
	double gap;
    sc_clk_tck = sysconf(_SC_CLK_TCK);

#ifdef ANDROID
	char property[PROPERTY_VALUE_MAX];
#endif
    begin = times(NULL);
	for(;;) {
		end = times(NULL);
		gap = (end - begin)/(double)sc_clk_tck;
		if (gap >= DETECT_GAP) {
			DBG("no arp response in %fs, no ip conflict\n", DETECT_GAP);
			return 0;
		}

		bytes = rcv_raw_packet(iface->arpsock, arp_buffer, sizeof(arp_buffer));
		if ( bytes == -1)
			return -1;

		if ( bytes == 0 || (size_t)bytes < sizeof(arph)) {
			usleep(100000);
			continue;
		}

		memcpy(&arph, arp_buffer, sizeof(arph));
		/* Protocol must be IP. */
		if ((arph.ar_pro != htons(ETHERTYPE_IP)) ||
			(arph.ar_pln != sizeof(reply_s)))
			continue;

		/* Only these types are recognised */
		if (arph.ar_op != htons(ARPOP_REPLY) &&
		    arph.ar_op != htons(ARPOP_REQUEST))
			continue;

		/* Get pointers to the hardware addreses */
		hw_s = arp_buffer + sizeof(arph);
		hw_t = hw_s + arph.ar_hln + arph.ar_pln;

		/* Ensure we got all the data */
		if ((hw_t + arph.ar_hln + arph.ar_pln) - arp_buffer > bytes)
			continue;

		/* Ignore messages from ourself */
		if (arph.ar_hln == iface->hwlen &&
		    memcmp(hw_s, iface->hwaddr, iface->hwlen) == 0)
			continue;

		/* Copy out the IP addresses */
		memcpy(&reply_s, hw_s + arph.ar_hln, arph.ar_pln);
		memcpy(&reply_t, hw_t + arph.ar_hln, arph.ar_pln);
		dump_arp_packet(0, hw_s, hw_t, &reply_s, &reply_t);

		/* Handle IPv4LL conflicts */
		if ((reply_s == iface->addr.s_addr ||
			(reply_s == 0 && reply_t == iface->addr.s_addr))) {
			DBG("ip conflict:%s\n", 
				inet_ntop(AF_INET, (void *)&(iface->addr.s_addr), ip, sizeof(ip)));
#ifdef ANDROID
			snprintf(property, sizeof(property), "dhcp.ipconflict.%s.result", iface->name);
			property_set(property, 
				inet_ntop(AF_INET, (void *)&(iface->addr.s_addr), ip, sizeof(ip)));
#endif
			return 1;
		} else {
			DBG("no ip conflict happened\n");
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int retry = 2, ret = 0;
	struct interface iface;
#ifdef ANDROID
	char property[PROPERTY_VALUE_MAX];
#endif

	if (argc < 2) {
		DBG("Usgae: ipconflict iface [ipaddr]");
		return 0;
	}

	snprintf(iface.name, sizeof(iface.name), "%s", argv[1]);
	if (getmac(iface.hwaddr, sizeof(iface.hwaddr)) < 0) {
		DBG("get_mac failed\n");
		return -1;
	}
	iface.hwlen = ETH_ALEN;
	iface.protocol = ETHERTYPE_ARP;

	if ((argc == 3) && 
		inet_pton(AF_INET, argv[2], &iface.addr)) {
		DBG("start check ip conflict:%s\n", argv[2]);
	} else if (getifip(iface.name, &iface.addr) < 0) {
		DBG("get_ip failed\n");
		return -1;
	}

	if (if_nametoindex(iface.name, &iface.ifindex) < 0) {
		DBG("if_nametoindex failed\n");
		return -1;
	}

	open_socket(&iface);

#ifdef ANDROID
		snprintf(property, sizeof(property), "dhcp.ipconflict.%s.result", iface.name);
		property_set(property, "");
#endif
	do {
		send_arp_probe(&iface, ARPOP_REQUEST);
		ret = handle_arp_packet(&iface);
	}while(retry-- && ret != 1);
#ifdef ANDROID
	if (ret != 1) {
		snprintf(property, sizeof(property), "dhcp.ipconflict.%s.result", iface.name);
		property_set(property, "no ip conflict");
	}
#endif
	close(iface.arpsock);
	return 0;
}