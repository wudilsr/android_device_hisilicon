#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <utils/Log.h>

static void generate_btmac(char filepath[])
{
	int fd, i;
	char buf[30];
	uint8_t bt_addr[6];

	ALOGD("Enter %s %s\n",__FUNCTION__,filepath);

	/*Check MAC_ADDR_FILE exist */

	if(access(filepath, F_OK) == 0)
	{
		ALOGD("%s: %s exists",__FUNCTION__, filepath);
		return;
	}
	srand(time(NULL) + getpid());

	memset(bt_addr, 0, sizeof(bt_addr));
	bt_addr[0] = 0x0;
	for(i=1; i<6; i++) {
  		bt_addr[i] = (uint8_t) (rand() >> 8) & 0xFF;
	}

	if(0x9e == bt_addr[3] && 0x8b == bt_addr[4] && (bt_addr[5] <= 0x3f)){
		//get random value
		bt_addr[3] = 0x00;
	}
	
	while((fd = open(filepath, O_CREAT|O_TRUNC|O_RDWR, 0644))<=0);
	{
		sleep(1);
	}
	memset(buf, 0, sizeof(buf));
	sprintf(buf,"%02X:%02X:%02X:%02X:%02X:%02X\0", bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
	write(fd, buf, sizeof(buf));
	close(fd);
	ALOGD("%s: %s fd=%d, data=%s",__FUNCTION__, filepath, fd, buf);
}

int main(int argc, char ** argv)
{
	char filepath[80];
	char cmd[256];
	memset(cmd, 0, sizeof(cmd));
	memset(filepath, 0, sizeof(filepath));
	if(argc != 2)
	{
			ALOGD("Usage:setbtmacaddr <mac_addr_path>\n");
			return 0;
	}
	strncpy(filepath, argv[1], strlen(argv[1]));
	generate_btmac(filepath);
	sprintf(cmd,"/system/bin/chmod 0666 %s", filepath);
	system(cmd);
	system("/system/bin/factory save");
	return 0;
}
