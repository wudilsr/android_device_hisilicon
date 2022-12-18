#include <stdlib.h>
#include <stdio.h>
#include <sys/statfs.h>
#include <cutils/log.h>
#include <sys/wait.h>

#define ERR_R       -1
#define OK_R        0
#define BUF_SIZE    1024

int isSystemSuccessful(pid_t status)
{
    if(-1 == status){
        SLOGE("system error!!");
        return -1;
    }else{
        if (WIFEXITED(status)){
            if (0 == WEXITSTATUS(status)){
                return 0;

            }else{
                SLOGE("run shell script fail, script exit code: %d",WEXITSTATUS(status));
                return -1;
            }
        }else{
            SLOGE("exit status = [%d]",WEXITSTATUS(status));
            return -1;
        }
    }

}

/** Check the free space storage
  * CN: 检测存储的空余空间
  * param[in 1]  limitSize
  * param[in 2]  mount path
  * param[in 3]  remove dir 1
  * param[in 4]  remove dir 2
  * param[in 5]  remove dir 3
  *
  *  ...
  *  ...
  *  ...
  *
  * param[in X]  remove dir X
  *
  **/
int main(int argc , char * argv[])
{
    if(argc < 4)
        return ERR_R ;

    unsigned freeSize ;
    struct statfs diskinfo ;
    char buf[BUF_SIZE] = {0};
    int  limit   = atoi(argv[1]);
    char *path   = argv[2];
    int i ;
    pid_t status ;

    if( statfs(path , &diskinfo) != 0)
        return ERR_R ;

    freeSize = ((diskinfo.f_bavail * diskinfo.f_bsize) >> 20 );
    SLOGD("freeSize=%u\n",freeSize);

    if( freeSize < limit ){
        for( i = 3 ; i < argc ; i++ ) {
            sprintf(buf,"busybox rm -rf %s/* ",argv[i]);
            status = system(buf);
            if (isSystemSuccessful(status) != 0) {
                SLOGE("fsSpaceCheck run system rm (%s) error!",buf);
            }
        }
    }
    return OK_R;
}
