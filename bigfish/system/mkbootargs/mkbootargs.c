#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define FLASH_SIZE   128*1024
#define BOOTARGS_LEN 4096

#define XMK_STR(x)	#x
#define MK_STR(x)	XMK_STR(x)

#define CFG_EVN_BOOTDELAY   0
#define CFG_EVN_BOOTBAUDRATE       115200
#define CFG_EVN_BOOTETHADDR        00:00:00:00:01:02

static char environment[BOOTARGS_LEN] = {
#ifdef	CFG_EVN_BOOTFILE
	"bootfile=" MK_STR (CFG_EVN_BOOTFILE) "\0"
#endif
#if defined(CFG_EVN_BOOTCOMMAND)
	"bootcmd=" MK_STR(CFG_EVN_BOOTCOMMAND) "\0"
#endif
#if defined(CFG_EVN_BOOTDELAY) && (CFG_EVN_BOOTDELAY >= 0)
	"bootdelay=" MK_STR (CFG_EVN_BOOTDELAY) "\0"
#endif
#if defined(CFG_EVN_BAUDRATE) && (CONFIG_EVN_BAUDRATE >= 0)
	"baudrate=" MK_STR (CFG_EVN_BOOTBAUDRATE) "\0"
#endif

#ifdef	CFG_EVN_BOOTETHADDR
	"ethaddr=" MK_STR (CFG_EVN_BOOTETHADDR) "\0"
#endif
#ifdef	CFG_EVN_BOOTSERVERIP
	"serverip=" MK_STR (CFG_EVN_BOOTSERVERIP) "\0"
#endif
#ifdef	CFG_EVN_BOOTIPADDR
	"ipaddr=" MK_STR (CFG_EVN_BOOTIPADDR) "\0"
#endif
#ifdef	CFG_EVN_BOOTNETMASK
	"netmask=" MK_STR (CFG_EVN_BOOTNETMASK) "\0"
#endif

#ifdef  CFG_EXTRA_ENV_SETTINGS
        CFG_EXTRA_ENV_SETTINGS
#endif
	"\0"		/* Termimate struct environment data with 2 NULs */
};

#define BUILD_XML 0

int main(int argc, char *argv[] )
{
    FILE* fp = NULL;
    FILE* fp_input = NULL;
    FILE* fp_xml=   NULL;
    char* buf = NULL;
    int   Size=512; // flash size.
    long  int   totalhiflashsize=-1;
    long  int   totalnandflashsize=256*1024;
    unsigned long  crc;
    char line[512];
	char bootargs_input[1024]="bootargs_input.txt";
	char bootargs_bin[1024]="bootargs.bin";
    char *strsrc;
    int offset = 0;
	int oc = 0;

    if (argc < 2)
    {
        printf("Usage: mkbootargs:\n"
		       "       -r bootargs_input: read a bootargs.txt\n"
		   "       -o bootargs_bin: write a bootargs.bin\n"
               "       -s bootargssize: size in KB. usually, bootargssize is set to the bootargs partition size. default:512.\n"
               "       -p SPI flash size: size in MB. usually, SPI flash size-Total partition size is set to 'other' partition of SPI flash . default:0MB.\n"
               "       -n Nand flash size: size in MB. usually, Nand flash size-Total partition size is set to 'other' partition of Nand flash . default:256MB.\n"
               "       mkbootargs will read a 'bootargs_input.txt' and generat a 'bootargs.bin' and 'Partition_table.xml'.\n");
        printf("Example:./makebootargs -s 64\n");
        return 1;
    }

	while((oc = getopt(argc, argv, "r:o:s:p:n:")) != -1)
	{
		switch(oc)
		{
		case 'r':{
		sprintf(bootargs_input,"%s",optarg);
		printf("optarg:%s\n",optarg);
		}
		break;
		case 'o':{
		sprintf(bootargs_bin,"%s",optarg);
		printf("optarg:%s\n",optarg);
		}
		break;
		case 's':{
		Size = atoi(optarg);
		printf("optarg:%s\n",optarg);
		}
		break;
		case 'p':{
		totalhiflashsize = atoi(optarg);
		printf("optarg:%s\n",optarg);
		}
		break;
		case 'n':{
		totalnandflashsize = atoi(optarg);
		printf("optarg:%s\n",optarg);
		}
		break;
		default:{
		printf("unknow args\n");
		}
		break;
		}
	}

//    Size = atoi(argv[1]);
    if (Size > 1)
    {
        printf("flash size is %dKB.\n", Size);
        Size = Size * 1024;
    }
    else
    {
        printf("flash size too small.\n");
    }

    if(argc>2)
    {
        //totalhiflashsize = atoi(argv[2]);
        if (totalhiflashsize > 1)
        {
            printf("total hi flash size is %luMB.\n", totalhiflashsize);
            totalhiflashsize = totalhiflashsize * 1024;
        }
        else
        {
            printf("total hi flash size is too small.\n");
            //return -1;
            totalhiflashsize=-1;
        }
    }

    if(argc>3)
    {
        //totalnandflashsize = atoi(argv[3]);
        if (totalnandflashsize > 1)
        {
            printf("total nand flash size is %luMB.\n", totalnandflashsize);
            totalnandflashsize = totalnandflashsize * 1024;
        }
        else
        {
            printf("total nand flash size is too small.\n");
           // return -1;
           totalnandflashsize=-1;
        }
    }

    fp = fopen(bootargs_bin, "w+b");
    if(NULL == fp)
    {
        printf("open bootargs.bin error.");
        return -1;
    }
#if BUILD_XML
    fp_xml = fopen("Partition_table.xml", "w+");
    if(NULL == fp_xml)
    {
        printf("open Partition_table.xml error.");
		fclose(fp);
        return -1;
    }
#endif
    fp_input = fopen(bootargs_input, "rb");
    if(NULL == fp_input)
    {
        printf("open 'bootargs_input' faild, please input bootargs:");
		fclose(fp);
		fclose(fp_xml);
		return -1;
       // fp_input = stdin;
    }

    buf =malloc(Size);
    if(NULL == buf)
    {
        printf("open bootargs out of memory\n");
        fclose(fp);
		fclose(fp_xml);
		fclose(fp_input);
        return -1;
    }
    strsrc=malloc(Size*sizeof(char));
    if(NULL == strsrc)
    {
        printf("open bootargs out of memory\n");
        fclose(fp);
		fclose(fp_xml);
		fclose(fp_input);
		free(buf);
        return -1;
    }

    memset(buf, 0x00, Size);
    memset(strsrc, 0x00, Size);
    char* tmp = NULL;
    int len = 0;

    while (fgets(line, 511, fp_input) != NULL)
    {
        strcat(strsrc,line);
        tmp = line;
        while(*tmp != '\0')
        {
            if(*tmp == '\n' || (*tmp == 0xd))
            {
                *tmp = '\0';
            }

            tmp++;
        }

        len = strlen(line);
        printf("%d--%s\n", len, line);
        memcpy(buf+4+offset, line, len);
        offset += len + 1;
        //offset += sprintf(buf+4+offset, "%s", line);
        //offset++; /* '\0' */
        memset(line, 512, 0);
    }
#if BUILD_XML
    printf("strcat str:%s\n",strsrc);
    char strrootfstype[20];
    char *pos=NULL;
    //int len=0;
    char *poshinand=NULL;
    char* posrootfs=NULL;
    int posappendpartn1=-1;
    int posappendpartn2=-1;
    int  t=0;
    long int  startaddr=0;
    int  ifhinand=0;
	len = 0;
#if 0
	pos=strstr(strsrc,"rootfstype=");                 /* check if exist "rootfstype=" string */
    if(pos==NULL)
    {
        printf("can not find index char in source");
        goto LL;
    }

    if (sscanf(pos,"rootfstype=%s ",strrootfstype) != 1)   /* get rootfs type string */
    {
        printf("failed to get output char in source");
        goto LL;
    }
#endif
    pos=strstr(strsrc,"mtdparts=");                      /* check if exist "mtdparts=" string */
    if(pos==NULL)
    {
        printf("can not find index string 'mtdparts' in source");
        goto LL;
    }

    strcpy(strsrc,pos);                                 /* copy string since "mtdparts=" */
    len=strlen(strsrc);

    pos=strstr(strsrc,"(rootfs)");
    if(pos==NULL)
    {
	    pos=strstr(strsrc,"(system)");
		if (pos==NULL){
        printf("can not find index string '(rootfs)' in source");
        goto LL;
		}
    }
    posrootfs=pos;          /*mark rootfs partition name pos*/

    while(len--)
    {
        pos=NULL;
        pos=strchr(strsrc,':');
        if(strsrc[len]==0x3a)                  /* change char ':' to char ','*/
        {
           strsrc[len]=',';
        }
        if(strsrc[len]==0x3b)                   /*mark hinand start pos ';'*/
        {
           poshinand=&strsrc[len];
        }
        if(strsrc[len]==0x2d)                    /*mark other partition start pos '-'*/
        {
            if(posappendpartn2==-1)
            {
                 posappendpartn2=&strsrc[len]-strsrc;
            }
            else
            {
                 posappendpartn1=&strsrc[len]-strsrc;
            }
        }
    }
    if((posappendpartn1==-1)&&(posappendpartn2!=-1))  /*mark other partition(hiflash or nandflash) start pos '-'*/
    {
       if((poshinand-strsrc)>posappendpartn2)
       {
            posappendpartn1=posappendpartn2;
            posappendpartn2=-1;
       }
    }

    printf("<?xml version=\"1.0\" encoding=\"GB2312\" ?>\n");
    printf(" <Partition_Info>\n");
    fprintf(fp_xml,"<?xml version=\"1.0\" encoding=\"GB2312\" ?>\n");
    fprintf(fp_xml," <Partition_Info>\n");

   do
    {
        char strpartitionname[20];  /*partition */
        char strpartitionlen[20];  /*len & size */
        long int  partitionlen[20];
        int  partitionlenoutput=0;
        int  startaddroutput=0;
        char partitionlenunit=0;
        char startaddrunit=0;
        int pos0=0;
        int posx=0;


        if(strchr(strsrc,',')==NULL)                 /*can not find ',':end of index string*/
        {
            break;
        }
        pos0=strchr(strsrc,',')-strsrc;            /*len & size string pos */
        posx=strchr(strsrc,'(')-strsrc;
        strsrc[pos0]=' ';
        strsrc[posx]=' ';

        char*rfstype=((posrootfs-strsrc)==posx)?strrootfstype:"None";/*mark rootfs type*/

        strncpy(strpartitionlen,&strsrc[pos0+1],posx-pos0-1);           /*len & size string*/
        sscanf(strpartitionlen,"%lu",&partitionlen[t]);         /*partition len & size */
        if((strsrc[posx-1]==0x4d)||(strsrc[posx-1]==0x6d)) /*if size is M,change to K*/
        {
            partitionlen[t]=partitionlen[t]*1024;
        }

        pos0=posx;                                         /*partition name string pos */
        posx=strchr(strsrc,')')-strsrc;
        strsrc[posx]=' ';

        /*--------------format to output-----------*/

        strncpy(strpartitionname,&strsrc[pos0+1],posx-pos0-1);       /*partition name string*/
        strpartitionname[posx-pos0-1]='\0';

        startaddr=((t==0)||(startaddr==-1))?0:(partitionlen[t-1]+startaddr);

        if((poshinand!=NULL)&&(&strsrc[posx]>poshinand))  /*Nand or Spi flash type*/
        {
            ifhinand=1;
        }
        else
        {
            ifhinand=0;
        }
        char*flashtype=(ifhinand==1)?"Nand":"Spi"; /*mark flash type*/

        if(pos0-1==posappendpartn1)
        {
            if(totalhiflashsize==-1)
            {
                partitionlen[t]=0;
            }
            else
            {
                if(startaddr+partitionlen[t]>totalhiflashsize)
                {
                    printf("total hiflash size %luMB is too small!\n",totalhiflashsize/1024);
                    break;
                }
                partitionlen[t]=totalhiflashsize-startaddr;  /*other partition(hiflash) length define by user,form input parameter*/
            }
        }
        else if(pos0-1==posappendpartn2)
        {
            if(totalnandflashsize==-1)
            {
                partitionlen[t]=0;
            }
            else
            {
                if(startaddr+partitionlen[t]>totalnandflashsize)
                {
                    printf("total nand flash size %luMB is too small!\n",totalnandflashsize/1024);
                    break;
                }
                partitionlen[t]=totalnandflashsize-startaddr; /*other partition(nandflash) length define by user,form parameter*/
            }
        }

        if((partitionlen[t]%1024==0)&&(partitionlen[t]>=1024))   /*format lenght unit*/
        {
            partitionlenoutput=partitionlen[t]/1024;
            partitionlenunit='M';
        }
        else
        {
            partitionlenoutput=partitionlen[t];
            partitionlenunit='K';
        }

        if((startaddr%1024==0)&&(startaddr>=1024))
        {
            startaddroutput=startaddr/1024;
            startaddrunit='M';
        }
        else
        {
            startaddroutput=startaddr;
            startaddrunit='K';
        }

        printf("    <Part Sel=0 PartitionName=\"%s\"    FlashType=\"%s\" FileSystem=\"%s\" Start=\"%d%c\"  Length=\"%d%c\"   SelectFile=\"\"/>\n",strpartitionname,flashtype,rfstype,startaddroutput,startaddrunit,partitionlenoutput,partitionlenunit);
        fprintf(fp_xml,"    <Part Sel=0 PartitionName=%s   FlashType=\"%s\" FileSystem=\"%s\" Start=\"%d%c\"  Length=\"%d%c\"   SelectFile=\"\"/>\n",strpartitionname,flashtype,rfstype,startaddroutput,startaddrunit,partitionlenoutput,partitionlenunit);
        if((poshinand!=NULL)&&(&strsrc[posx+1]==poshinand))  /*reset start address between hiflash to nandflash*/
        {
            startaddr=-1;
        }
        memset(strpartitionlen,0,sizeof(strpartitionlen));
        memset(strpartitionname,0,sizeof(strpartitionname));
        t++;
    }while(1) ;
    printf(" </Partition_Info>\n");
    fprintf(fp_xml," </Partition_Info>\n");

#endif
    crc=crc32(0,buf+4, Size-4);
    memcpy(buf,(unsigned char*)&crc,4);

    /* init flash data */
    fwrite(buf, Size, 1, fp);

LL:
    free(buf);
	free(strsrc);
    fclose(fp);
	if (fp_xml) fclose(fp_xml);

    if (fp_input != stdin)
    {
        fclose(fp_input);
    }

    return 0;
}
