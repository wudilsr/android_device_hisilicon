#include "hi_mmz.h"

#define MMZ_DEBUG 0
int call_debug(unsigned long arg0, unsigned long arg1, unsigned long arg2, unsigned long arg3)
{
	switch(arg0){
		case MMZ_DEBUG:
			mmz_dump();
			break;
		default:
			break;
	}
}
