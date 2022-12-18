#include "sre_base.h"
#include "secure_mem.h"

/*
--------------------------- 0x40000000   1024M  ------------------------
		       REGION6 8M                         NON_SEC_MMZ 8M
REGION1 256M  ------------- 0x3F800000   1016M  ------------------------
		               248M
--------------------------- 0x30000000   768M        SEC_MMZ 288M
                       40M
              ------------- 0x2D000000   728M   ------------------------
		       REGION4 8M
REGION2 64M   ------------- 0x2D000000   720M
		       REGION3 16M                             SEC_OS 40M
--------------------------- 0x2C000000   704M
		       REGION5 16M
--------------------------- 0x2B000000   688M  -------------------------
                       688M                       NON_SEC_OS 688M
--------------------------- 0x0                 -------------------------
*/

/* -------------------------------------------------------- */
/* Secure World */
#define REGION1_BASE                (768 * 1024 * 1024)
#define REGION1_SIZE                (256  * 1024 * 1024)

#define REGION2_BASE                (704 * 1024 * 1024)
#define REGION2_SIZE                (64 * 1024 * 1024)

#define REGION3_BASE                (704 * 1024 * 1024)
#define REGION3_SIZE                (16   * 1024 * 1024)

#define REGION4_BASE                (2048 * 1024 * 1024UL)
#define REGION4_SIZE                (2048 * 1024 * 1024UL)

#define REGION5_BASE                (688 * 1024 * 1024)
#define REGION5_SIZE                (16   * 1024 * 1024)

#define REGION6_BASE                (1016 * 1024 * 1024)
#define REGION6_SIZE                (8 * 1024 * 1024)
//TODO:XXX
#define REGION7_BASE                (1024 * 1024 * 1024)//(0)
#define REGION7_SIZE                (1 * 1024 * 1024 * 1024)//(688 * 1024 * 1024)

/* -------------------------------------------------------- */

#define NON_SEC_OS_START            0
#define NON_SEC_OS_SIZE             (REGION5_BASE)

#define SEC_OS_START                (REGION5_BASE)
#define SEC_OS_SIZE                 (REGION3_SIZE + REGION5_SIZE)

#define SEC_MMZ_START               (SEC_OS_START + SEC_OS_SIZE)
#define SEC_MMZ_SIZE                ((REGION1_SIZE + REGION2_SIZE) - (REGION3_SIZE + REGION6_SIZE))

#define NON_SEC_MMZ_START           (SEC_MMZ_START + SEC_MMZ_SIZE)
#define NON_SEC_MMZ_SIZE            (REGION6_SIZE)

/* -------------------------------------------------------- */
void *sec_mem_get_zone_range(int zone, unsigned long *size)
{
	char *addr = NULL;
	unsigned long zone_size;

	switch(zone) {
		case NON_SEC_OS_MEM:
			addr = NON_SEC_OS_START;
			zone_size = NON_SEC_OS_SIZE;
			break;
		case SEC_OS_MEM:
			addr = SEC_OS_START;
			zone_size = SEC_OS_SIZE;
			break;
		case SEC_MMZ_MEM:
			addr = SEC_MMZ_START;
			zone_size = SEC_MMZ_SIZE;
			break;
		case NON_SEC_MMZ_MEM:
			addr = NON_SEC_MMZ_START;
			zone_size = NON_SEC_MMZ_SIZE;
			break;
		default:
			addr = NULL;
			zone_size = 0;
			break;
	};
	
	if (size)
		*size = zone_size;
	
	return addr;
}

/* -------------------------------------------------------- */

static struct tzascregion tzasc0_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = FULL_RIGHT}, //NONE_RIGHT
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = SECURE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = SECURE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = FULL_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT}, // FULL_RIGHT
};

static struct tzascregion tzasc1_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = NON_SECURE_RIGHT}, //NONE_RIGHT
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = NONE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = NONE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = NON_SECURE_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT}, //NON_SECURE_RIGHT
};

static struct tzascregion tzasc2_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = NON_SECURE_RIGHT},
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = NONE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = NONE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = NON_SECURE_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT}, //NON_SECURE_RIGHT
};

static struct tzascregion tzasc3_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = NON_SECURE_RIGHT}, //NONE_RIGHT
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = NONE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = NONE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = NON_SECURE_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT}, //NON_SECURE_RIGHT
};

static struct tzascregion tzasc4_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = NON_SECURE_RIGHT},
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = NONE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = NONE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = NON_SECURE_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT},
};

static struct tzascregion tzasc5_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = NON_SECURE_RIGHT},
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = NONE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = NONE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = NON_SECURE_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT},
};

static struct tzascregion tzasc6_regions[MAX_REGIONS] = {
	/*  region 0 */
	{.en = 1,.base = 0,.size = 0,.sp = NON_SECURE_RIGHT},
	/*      region 1 */
	{.en = 1,.base = REGION1_BASE,.size = REGION1_SIZE,.sp = SECURE_RIGHT},
	/*      region 2 */
	{.en = 1,.base = REGION2_BASE,.size = REGION2_SIZE,.sp = SECURE_RIGHT},
	/*      region 3 */
	{.en = 1,.base = REGION3_BASE,.size = REGION3_SIZE,.sp = NONE_RIGHT},
	/*      region 4 */
	{.en = 1,.base = REGION4_BASE,.size = REGION4_SIZE,.sp = NONE_RIGHT},
	/*      region 5 */
	{.en = 1,.base = REGION5_BASE,.size = REGION5_SIZE,.sp = NONE_RIGHT},
	/*      region 6 */
	{.en = 1,.base = REGION6_BASE,.size = REGION6_SIZE,.sp = NON_SECURE_RIGHT},
	/*      region 7 */
	{.en = 1,.base = REGION7_BASE,.size = REGION7_SIZE,.sp = NONE_RIGHT},
};

static struct ddr_port ports[MAX_PORT_NUMS] = {
	{.master_type = 0, .regions = tzasc0_regions},
	{.master_type = 1, .regions = tzasc1_regions},
	{.master_type = 1, .regions = tzasc2_regions},
	{.master_type = 1, .regions = tzasc3_regions},
	{.master_type = 1, .regions = tzasc4_regions},
	{.master_type = 1, .regions = tzasc5_regions},
	{.master_type = 1, .regions = tzasc6_regions},
};
