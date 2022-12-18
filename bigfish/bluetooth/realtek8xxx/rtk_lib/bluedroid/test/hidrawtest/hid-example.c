/*
 * Hidraw Userspace Example
 *
 * Copyright (c) 2010 Alan Ott <alan@signal11.us>
 * Copyright (c) 2010 Signal 11 Software
 *
 * The code may be used by anyone for any purpose,
 * and can serve as a starting point for developing
 * applications using hidraw.
 */

/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

/*
 * Ugly hack to work around failing compilation on systems that don't
 * yet populate new version of hidraw.h to userspace.
 *
 * If you need this, please have your distro update the kernel headers.
 */
#ifndef HIDIOCSFEATURE
#define HIDIOCSFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x06, len)
#define HIDIOCGFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x07, len)
#endif

/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <unistd.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>

const char *bus_str(int bus);

#define DATA_NUM 79

struct rtk_update_hid {
	int write_fd;
	int read_fd;
	int keep_polling;
	int rtkbt_thread_id;
	int write_idx;
	int is_updating;
	char data[DATA_NUM];
};
struct rtk_update_hid update_info;
char write_buf[21];

void init_data() {
	perror("init_data");
	int fd = -1;
	int i, n = 0;
	fd = open("/dev/result.dat", O_RDWR);
	if(fd > 0) {
		n = read(fd, update_info.data, DATA_NUM);
		for(i=0; i< n; i++)
			printf("%d = 0x%x \n", i, update_info.data[i]);
	} else
		return;
	update_info.write_idx = 0;
	close(fd);
}
void write_start() {
	perror("***start to update hid device\n ***");
	update_info.is_updating = 1;
	printf("***start to write %d \n***", update_info.write_idx);
	memcpy(write_buf+1, update_info.data+update_info.write_idx , sizeof(write_buf)-1);
	write_buf[0] = 0xFA;
	write(update_info.write_fd, write_buf, sizeof(write_buf));

}

void write_continue() {
	if(update_info.is_updating == 1) {
		printf(" %d is ack!\n", update_info.write_idx);
		update_info.write_idx += sizeof(write_buf)-1;
		if (update_info.write_idx > DATA_NUM ) {
			write_end();
			return;
		}
		printf("start to write %d \n", update_info.write_idx);
		if(update_info.write_idx == 60 ) {
			memcpy(write_buf+1, update_info.data+update_info.write_idx , sizeof(write_buf)-2);
			write_buf[0] = 0xFA;
			write(update_info.write_fd, write_buf, sizeof(write_buf)-1);
		} else {
			memcpy(write_buf+1, update_info.data+update_info.write_idx , sizeof(write_buf)-1);
			write_buf[0] = 0xFA;
			write(update_info.write_fd, write_buf, sizeof(write_buf));
		}

	} else
		perror("update_info.is_updating != true!");
}

void write_end() {
	if(update_info.is_updating == 1) {
		perror("***update hid device success!\n***");
		update_info.is_updating = 0;
	}
}

static int read_event() {
	char buf[18];
	int read_result = 0;
	//perror("start to read data from /dev/hidraw0\n");
	read_result = read(update_info.read_fd, buf, sizeof(buf));
	if(read_result > 0) {
		//perror("read ok!");
		printf("***report id is %d \n***", buf[0]);
		printf("***read len is %d \n***", read_result);
		if(buf[0] == 0x01 && read_result == 2) {
			printf("***receive ack!***");
			write_continue();
		}
	} else {
		perror("read fail!");
		update_info.keep_polling = 0;
	}

	return 0;
}

static void *poll_event_thread(void *arg)
{
    struct pollfd pfds[1];
    int ret;
    pfds[0].fd = update_info.read_fd;
    pfds[0].events = POLLIN;
    perror("start to call poll_event_thread!");
    while(update_info.keep_polling == 1) {
	//perror("start to poll!");
        ret = poll(pfds, 1, 5000);
	//printf("poll result = %d \n", ret);
        if (ret < 0) {
            printf("%s: Cannot poll for fds: %s\n", __FUNCTION__, strerror(errno));
	    update_info.keep_polling = -1;
            break;
        }
        if (pfds[0].revents & POLLIN) {
            //perror("pull OK!");
            ret = read_event();
            if (ret){
                break;
            }
        } else {
		//write_start();
	}
    }

    update_info.rtkbt_thread_id = -1;
    return 0;
}

static inline pthread_t rtkbt_create_thread(void *(*start_routine)(void *), void * arg){
    perror("create_thread: entered \n");
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread_id = -1;
    if ( pthread_create(&thread_id, &thread_attr, start_routine, arg)!=0 )
    {
        printf("pthread_create : %s", strerror(errno));
        return -1;
    }
    perror("create_thread: thread created successfully\n");
    return thread_id;
}

int main(int argc, char **argv)
{
	int fd;
	int i, res, desc_size = 0, count = 1;
	char buf[256];
	struct hidraw_report_descriptor rpt_desc;
	struct hidraw_devinfo info;
	memset(&rpt_desc, 0x0, sizeof(rpt_desc));
	memset(&info, 0x0, sizeof(info));
	memset(buf, 0x0, sizeof(buf));
	
	memset(&update_info, 0x0, sizeof(update_info));

	fd = open("/dev/hidraw0", O_RDWR);

	if (fd < 0) {
		perror("Unable to open /dev/hidraw0");
		return 1;
	} else {
		perror("open /dev/hidraw0 success!");
		/* Get Raw Info */
		res = ioctl(fd, HIDIOCGRAWINFO, &info);
		if (res < 0) {
			perror("HIDIOCGRAWINFO");
		} else {
			printf("Raw Info:\n");
			printf("\tbustype: %d (%s)\n",
				info.bustype, bus_str(info.bustype));
			printf("\tvendor: 0x%04hx\n", info.vendor);
			printf("\tproduct: 0x%04hx\n", info.product);
		}
		update_info.write_fd = fd;
		update_info.read_fd = fd;
	}
	init_data();
	write_start();
	update_info.keep_polling = 1;
	poll_event_thread(NULL);
	update_info.keep_polling = -1;
	///update_info.rtkbt_thread_id = rtkbt_create_thread(poll_event_thread, NULL);
	return 0;
}

const char *
bus_str(int bus)
{
	switch (bus) {
	case BUS_USB:
		return "USB";
		break;
	case BUS_HIL:
		return "HIL";
		break;
	case BUS_BLUETOOTH:
		return "Bluetooth";
		break;
	case BUS_VIRTUAL:
		return "Virtual";
		break;
	default:
		return "Other";
		break;
	}
}


