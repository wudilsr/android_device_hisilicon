#include <stdlib.h>
#include <string.h>

#include "teletext_debug.h"
#include "teletext_data.h"
#include "teletext_parse.h"
#include "teletext_showpage.h"
#include "hi_unf_ttx.h"
#include "teletext_utils.h"

#define TTX_COLOR_NUM (8)    /** The number  of color */

#define P_CHARACTER(x) ((x) & 0x7F)
#define P_ADDITION(x) ((x) & 0x80)
#define P_GCODE(x) (((x) & 0x300) >> 8)
#define P_MARKS(x) (((x) & 0x3C00) >> 10)

#define TTX_GET_COLOR(entry) (g_u32RedefColorMap[entry])

#define TTX_SHOWPAGE_LOCK()  \
    do{\
        int ret = pthread_mutex_lock(&pstCurrentPoint->Mutexlock);\
        if(ret != 0){\
            HI_ERR_TTX("TTX call pthread_mutex_lock(SHOWPAGE) failure ret = 0x%x\n",ret);\
        }\
    }while(0)

#define TTX_SHOWPAGE_UNLOCK()  \
    do{\
        int ret = pthread_mutex_unlock(&pstCurrentPoint->Mutexlock);\
        if(ret != 0){\
            HI_ERR_TTX("TTX call pthread_mutex_unlock(SHOWPAGE) failure ret = 0x%x\n",ret);\
        }\
    }while(0)


/**  Color set */
static HI_U32 s_ColorSet[TTX_COLOR_NUM] =
{
    0xff000000,   /**black */
    0xffff0000,  /**red */
    0xff00ff00, /**green*/
    0xffffff00, /**yellow*/
    0xff0000ff,/**blue*/
    0xffff00ff,/**magenta */
    0xff00ffff,/**cyan */
    0xffffffff /**white */
};
TTX_TRIPLET_PARSER g_stTripParser[TTX_MAX_OPEN_OBJECTS];

/* character set maps */
static const TTX_DEF_G0G2_S g_stDefG0G2Map0000[8] =
{
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ENGLISH},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_GERMAN},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SWEDISH},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ITALIAN},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_FRENCH},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PORTUGUESE},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_CZECH},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PRIMARY}/*C12 C13 C14: 111*/

};
static const TTX_DEF_G0G2_S g_stDefG0G2Map0001[8] =
{
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_POLISH},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_GERMAN},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SWEDISH},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ITALIAN},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_FRENCH},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_CZECH},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PRIMARY}/*C12 C13 C14: 111*/

};
static const TTX_DEF_G0G2_S g_stDefG0G2Map0010[8] =
{
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ENGLISH},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_GERMAN},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SWEDISH},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ITALIAN},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_FRENCH},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PORTUGUESE},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_TURKISH},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PRIMARY}/*C12 C13 C14: 111*/

};
static const TTX_DEF_G0G2_S g_stDefG0G2Map0011[8] =
{
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 1001*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SERBIAN},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_RUMANIAN}/*C12 C13 C14: 111*/

};
static const TTX_DEF_G0G2_S g_stDefG0G2Map0100[8] =
{
    {HI_UNF_TTX_G0SET_CYRILLIC_1, HI_UNF_TTX_G2SET_CYRILLIC, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_GERMAN},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ESTONIAN},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_LETTISH},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_CYRILLIC_2, HI_UNF_TTX_G2SET_CYRILLIC, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_CYRILLIC_3, HI_UNF_TTX_G2SET_CYRILLIC, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_CZECH},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT}/*C12 C13 C14: 111*/
};
static const TTX_DEF_G0G2_S g_stDefG0G2Map0110[8] =
{
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_TURKISH},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_GREEK, HI_UNF_TTX_G2SET_GREEK, HI_UNF_TTX_NATION_SET_BUTT}/*C12 C13 C14: 111*/

};
static const TTX_DEF_G0G2_S g_stDefG0G2Map1000[8] =
{
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_ENGLISH},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_FRENCH},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_ARABIC, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_BUTT}/*C12 C13 C14: 111*/

};
static const TTX_DEF_G0G2_S g_stDefG0G2Map1010[8] =
{
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 000*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 001*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 010*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 011*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 100*/
    {HI_UNF_TTX_G0SET_HEBREW, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 101*/
    {HI_UNF_TTX_G0SET_BUTT, HI_UNF_TTX_G2SET_BUTT, HI_UNF_TTX_NATION_SET_BUTT},/*C12 C13 C14: 110*/
    {HI_UNF_TTX_G0SET_ARABIC, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_BUTT}/*C12 C13 C14: 111*/

};
static const TTX_SEC_G0_S g_stSecG0Map0000[8] =
{
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_ENGLISH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_GERMAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_SWEDISH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_ITALIAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_FRENCH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_PORTUGUESE},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_CZECH},/**/
    {HI_UNF_TTX_G0SET_BUTT,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};

static const TTX_SEC_G0_S g_stSecG0Map0001[8] =
{
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_POLISH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_GERMAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_SWEDISH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_ITALIAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_FRENCH},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_CZECH},/**/
    {HI_UNF_TTX_G0SET_BUTT,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};

static const TTX_SEC_G0_S g_stSecG0Map0010[8] =
{
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_POLISH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_GERMAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_SWEDISH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_ITALIAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_FRENCH},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_PORTUGUESE},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_TURKISH},/**/
    {HI_UNF_TTX_G0SET_BUTT,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};
static const TTX_SEC_G0_S g_stSecG0Map0011[8] =
{
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_SERBIAN},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,   HI_UNF_TTX_NATION_SET_RUMANIAN}/**/
};

static const TTX_SEC_G0_S g_stSecG0Map0100[8] =
{
    {HI_UNF_TTX_G0SET_CYRILLIC_1,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_GERMAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_ESTONIAN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_LETTISH},/**/
    {HI_UNF_TTX_G0SET_CYRILLIC_2,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_CYRILLIC_3,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_CZECH},/**/
    {HI_UNF_TTX_G0SET_BUTT,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};

static const TTX_SEC_G0_S g_stSecG0Map0110[8] =
{
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_TURKISH},/**/
    {HI_UNF_TTX_G0SET_GREEK,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};

static const TTX_SEC_G0_S g_stSecG0Map1000[8] =
{
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_ENGLISH},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_NATION_SET_FRENCH},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_ARABIC,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};

static const TTX_SEC_G0_S g_stSecG0Map1010[8] =
{
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_HEBREW,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_NATION_SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_ARABIC,   HI_UNF_TTX_NATION_SET_BUTT}/**/
};


static const TTX_MODIFIED_G0G2_S g_stModifiedG0G2Map00XX[8] =
{
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,   HI_UNF_TTX_G2SET_LATIN}/**/
};
static const TTX_MODIFIED_G0G2_S g_stModifiedG0G2Map0100[8] =
{
    {HI_UNF_TTX_G0SET_CYRILLIC_1,  HI_UNF_TTX_G2SET_CYRILLIC},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_CYRILLIC_2,  HI_UNF_TTX_G2SET_CYRILLIC},/**/
    {HI_UNF_TTX_G0SET_CYRILLIC_3,  HI_UNF_TTX_G2SET_CYRILLIC},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_BUTT,   HI_UNF_TTX_G2SET_BUTT}/**/
};
static const TTX_MODIFIED_G0G2_S g_stModifiedG0G2Map0110[8] =
{
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_LATIN},/**/
    {HI_UNF_TTX_G0SET_GREEK,   HI_UNF_TTX_G2SET_GREEK}/**/
};
static const TTX_MODIFIED_G0G2_S g_stModifiedG0G2Map1000[8] =
{
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_ARABIC},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_LATIN,  HI_UNF_TTX_G2SET_ARABIC},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_ARABIC,   HI_UNF_TTX_G2SET_ARABIC}/**/
};
static const TTX_MODIFIED_G0G2_S g_stModifiedG0G2Map1010[8] =
{
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_HEBREW,  HI_UNF_TTX_G2SET_ARABIC},/**/
    {HI_UNF_TTX_G0SET_BUTT,  HI_UNF_TTX_G2SET_BUTT},/**/
    {HI_UNF_TTX_G0SET_ARABIC,HI_UNF_TTX_G2SET_ARABIC}/**/
};

typedef struct tagTTX_LANGUAGE_S
{
    HI_U8                       u8LanguageCode[4];
    HI_UNF_TTX_G0SET_E          enG0Set;
    HI_UNF_TTX_G2SET_E          enG2Set;
    HI_UNF_TTX_NATION_SET_E enNationSet;
}TTX_LANGUAGE_S;

TTX_LANGUAGE_S g_stLanguageCode[] =
{
    #if 0
    {"cze", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_CZECH},
    {"slo", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_CZECH},
    {"eng", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ENGLISH},
    {"est", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ESTONIAN},
    {"fre", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_FRENCH},
    {"ger", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_GERMAN},
    {"ita", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_ITALIAN},
    {"lit", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_LETTISH},
    {"pol", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_POLISH},
    {"por", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PORTUGUESE},
    {"spa", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_PORTUGUESE},
    {"rum", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_RUMANIAN},
    {"slv", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SERBIAN},
    {"swe", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SWEDISH},
    {"fin", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_SWEDISH},
    {"tur", HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN, HI_UNF_TTX_NATION_SET_TURKISH},
    #endif
    {"per", HI_UNF_TTX_G0SET_ARABIC, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_BUTT},
    {"ara", HI_UNF_TTX_G0SET_ARABIC, HI_UNF_TTX_G2SET_ARABIC, HI_UNF_TTX_NATION_SET_BUTT}
};

/** Debug , print the name of color */
static  HI_VOID  TTX_PutColor(HI_U32 u32Color)
{
    switch (u32Color)
    {
    case 0:
        HI_INFO_TTX("ABlack");
        break;
    case 1:
        HI_INFO_TTX("ARed");
        break;
    case 2:
        HI_INFO_TTX("AGreen");
        break;
    case 3:
        HI_INFO_TTX("AYellow");
        break;
    case 4:
        HI_INFO_TTX("ABlue");
        break;
    case 5:
        HI_INFO_TTX("AMagenta");
        break;
    case 6:
        HI_INFO_TTX("ACyan");
        break;
    case 7:
        HI_INFO_TTX("AWhite");
        break;
    case 0x10:
        HI_INFO_TTX("MBlack");
        break;
    case 0x11:
        HI_INFO_TTX("MRed");
        break;
    case 0x12:
        HI_INFO_TTX("MGreen");
        break;
    case 0x13:
        HI_INFO_TTX("MYellow");
        break;
    case 0x14:
        HI_INFO_TTX("MBlue");
        break;
    case 0x15:
        HI_INFO_TTX("MMagenta");
        break;
    case 0x16:
        HI_INFO_TTX("MCyan");
        break;
    case 0x17:
        HI_INFO_TTX("MWhite");
        break;
    case 0x1c:
        HI_INFO_TTX("BBACK");
        break;
    default:
        HI_INFO_TTX(" ");
        break;
    }
}

/** A char  is a space char or not */
static HI_BOOL TTX_IsSpaceChar(HI_U32 u32Index)
{
    HI_BOOL bIsSpace = HI_FALSE;
    HI_U32 u32Char = u32Index;

    if (P_CHARACTER(u32Char) <= 0x20)
    {
        bIsSpace = HI_TRUE;
    }

    if (3 == P_GCODE(u32Char))
    {
        bIsSpace = HI_FALSE;
    }

    return bIsSpace;
}

/** A char  is a mosaic char or not */
static  HI_BOOL  TTX_IsMosaicChar(HI_BOOL bMosMode, HI_U32 u32Index)
{
    HI_BOOL bIsMosChar = HI_FALSE;
    HI_U32 u32Char = 0;

    if (u32Index < 0x20)
    {
        bIsMosChar = HI_FALSE;
        return bIsMosChar;
    }

    u32Char = u32Index;

    if (P_ADDITION(u32Char))   /** The char specify  by packet 26 */
    {
        switch (P_GCODE(u32Char))
        {
        case 0:                              /** G0 char  */
            bIsMosChar = HI_FALSE;
            break;
        case 1:                         /** G1 char  */
            u32Char = P_CHARACTER(u32Char) - 32;
            if ((u32Char < 32) || (u32Char >= 64))
            {
                bIsMosChar = HI_TRUE;
            }
            else
            {
                bIsMosChar = HI_FALSE;
            }

            break;
        case 2:                      /** G2 char */
            bIsMosChar = HI_FALSE;
            break;
        case 3:                    /** G3 char */
            bIsMosChar = HI_FALSE;
            break;
        default:
            bIsMosChar = HI_FALSE;
            break;
        }
    }
    else
    {
        u32Char = P_CHARACTER(u32Char) - 32;  /** Visible char  start from 0x20*/
        if (bMosMode)     /** Mosaic char  */
        {
            if ((u32Char < 32) || (u32Char >= 64))
            {
                bIsMosChar = HI_TRUE;
            }
            else
            {
                bIsMosChar = HI_FALSE;
            }
        }
        else
        {
            bIsMosChar = HI_FALSE;
        }
    }

    return bIsMosChar;
}

/** Record  a flash area */
static HI_VOID  TTX_ADD_FlashArea(TTX_FLAAREA_S ** ppstFlaAreaHead, TTX_FLAAREA_S *  pstInitFlashArea)
{
    if (((HI_NULL) == pstInitFlashArea) || (HI_NULL == ppstFlaAreaHead))  /** Invalid param, just return */
    {
        return;
    }

    if (HI_NULL == *ppstFlaAreaHead)
    {
        (*ppstFlaAreaHead) = pstInitFlashArea;
        (*ppstFlaAreaHead)->pstNext = HI_NULL;
    }
    else
    {
        pstInitFlashArea->pstNext = (*ppstFlaAreaHead);
        *ppstFlaAreaHead = pstInitFlashArea;
    }
}

/** Release  all flash area */
static HI_VOID   TTX_Release_FlashArea(TTX_FLAAREA_S * pstFlashAreaHead)
{
    TTX_FLAAREA_S *  pstFlashPoint, *pstFlashLastPoint;

    if (HI_NULL == pstFlashAreaHead)    /** Invalid param, just return */
    {
        return;
    }

    pstFlashPoint = pstFlashAreaHead;
    while (HI_NULL != pstFlashPoint)
    {
        pstFlashLastPoint = pstFlashPoint;
        pstFlashPoint = pstFlashPoint->pstNext;
        free(pstFlashLastPoint);
    }

    return;
}

static HI_VOID TTX_DecShowPage(TTX_PAGE_CONTEXT_S  *  pstContextHead)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32LineNum = 0, u32ColumnNum = 0, u32RowCount = 0, u32ColCount = 0;
    HI_U32 i = 0, j = 0, k = 0, C10 = 0, u32Fillback = 0;
    HI_UNF_TTX_COLOR TmpForeground = 0xffffffff;

    HI_UNF_TTX_COLOR BackgroundRec[72];/*40+16+16*/
    HI_BOOL bSetAForeground = HI_FALSE;
    HI_BOOL bSetFlash = HI_FALSE;
    HI_BOOL bSpacingAttr = HI_FALSE;
    HI_BOOL bSetMForeground = HI_FALSE;
    HI_BOOL bMosaic = HI_FALSE;
    HI_BOOL bLarged   = HI_FALSE;
    HI_BOOL bDoubleSize = HI_FALSE;
    HI_BOOL bHoldMosaic = HI_FALSE;
    HI_BOOL bReleaseMos = HI_FALSE;
    HI_BOOL bContiguous = HI_TRUE;
    HI_BOOL bBoxPage  = HI_FALSE;
    HI_BOOL bStartBox = HI_FALSE;
    HI_BOOL bEsc = HI_FALSE;
    HI_BOOL bUseDefaultCharSet = HI_TRUE;
    HI_BOOL bModifiedG0G2 = HI_FALSE;
    HI_BOOL bEnhanceChar = HI_FALSE;/*char defined by X26 or object*/
    HI_BOOL bFlag = HI_FALSE;
    HI_U8      u8LOPFlash = 0;
    TTX_DISP_ATTR stLOPAttr;

    HI_U8  u8NumOfSubPg = TTX_MAX_SUBPAGENO, u8szSubPage[TTX_MAX_SUBPAGENO] = {0}; /** National char set */
    HI_UNF_TTX_NATION_SET_E enNationSet = HI_UNF_TTX_NATION_SET_PRIMARY;
    HI_UNF_TTX_G0SET_E enG0Set = HI_UNF_TTX_G0SET_LATIN;   /** G0  Char set */
    HI_UNF_TTX_G0SET_E enLOPG0Set = HI_UNF_TTX_G0SET_LATIN;   /** LOP G0  Char set */
    HI_UNF_TTX_G0SET_E enModifiedG0Set = HI_UNF_TTX_G0SET_LATIN;   /** modified G0  Char set */
    HI_UNF_TTX_G2SET_E enG2Set = HI_UNF_TTX_G2SET_LATIN;   /** G2  Char set */
    HI_UNF_TTX_G2SET_E enLOPG2Set = HI_UNF_TTX_G2SET_LATIN;   /** LOP G2  Char set */
    HI_UNF_TTX_G2SET_E enModifiedG2Set = HI_UNF_TTX_G2SET_LATIN;   /** modified G2  Char set */
    HI_UNF_TTX_CHARSET_E enCharSet = HI_UNF_TTX_CHARSET_G0;
    HI_U32 u32CurrentCh   = 0, u32TempCh = 0, u32MosaicCh = 0;
    HI_U32 u32aPageNum[6] = {0, 0, 0, 0, 0, 0};   /** Page num and subpage nums  */
    TTX_FLAAREA_S  *pstFlashArea = NULL;   /**  Flash area */
    HI_UNF_TTX_CHARATTR_S stCharAttr;
    HI_UNF_TTX_PAGEAREA_S stPageArea;
    HI_UNF_TTX_DRAWCAHR_S stDrawCharParam;
    HI_UNF_TTX_FILLRECT_S stFillRectParam;
    HI_UNF_TTX_REFRESHLAYER_S stRefrshLayerParam;
    TTX_PAGE_CONTEXT_S * pstCurrentPoint = pstContextHead;

    static HI_U32 u32MaxColNum = TTX_LOP_COL_NUM;/*max column num, if has sidepanel, this value is 56*/

    HI_U32 u32OpenCount = 0;/*the num of opened triplet */

    HI_U8 u8DataLine[TTX_LINE_MEM_SIZE];

    TTX_TRIPLET_PARSER* pstParser;

    HI_U32 u32Parser;

    HI_U32 u32Band;
    HI_U32 u32DesignCode = 0;

     /* current cell data combined with enhancement data */
    TTX_DISP_ATTR stCMBAttr;                /* current attribute */
    //HI_U8   u8CMBFlash;           /* current flash attribute */
    HI_U8   u8CMBDRCSChar;        /* current DRCS char */
    HI_U8   u8CMBDRCSSubPage = 0;     /* current DRCS sub-page number */

    /* current priorities */
    HI_U8 u8CharPriority;
    HI_U8 u8ForePriority;
    HI_U8 u8BackPriority;
    HI_U8 u8AttrPriority;
    HI_U8 u8FlashPriority;

        /* background color for current row and screen */
    HI_U8 u8DefRowColor;
    HI_U8 u8FullRowColor;
    HI_U8 bBlackBgSubstitute;

    /* current cell position */
    HI_U32 u32Cell;

    HI_U8 u8Charset = 0;
    HI_U8 u8Accent = 2;
    HI_U8 u8MagNum = 0;

    HI_UNF_TTX_PAGE_ADDR_S* pstPage;
    TTX_DRCS_MODE_E enDRCSMode;
    HI_U32 u32DRCSColorInfo[120];
    HI_UNF_TTX_DRAWDRCSCHAR_S stDRCSCharParam;
    HI_UNF_TTX_BUFFER_PARAM_S stBuffParam;



    if (HI_NULL == pstCurrentPoint)      /**  Invalid  page context ,  just  return  */
    {
        HI_ERR_TTX("In TTX_ShowPage, Invalid  page context\n");
        return;
    }

    pstCurrentPoint->bInvalidReq = HI_FALSE;
    memset(u8DataLine, 0 , TTX_LINE_MEM_SIZE);

    /**parse MOT page, at level 1.0 and 1.5,this function will return failure ,so we not judge the return value*/
    bFlag = ((HI_TRUE == pstCurrentPoint->bHasP27_4) || (HI_TRUE == pstCurrentPoint->bHasP27_5)) ? HI_TRUE : HI_FALSE;
    (HI_VOID)TTX_DecodeMOTPage(&pstCurrentPoint->stCurPgAddr, &pstCurrentPoint->stMOTInfo, bFlag);

    /**set colormap to default*/
    memcpy(g_u32RedefColorMap, g_u32DefaultColorMap, 128);

     /**convert the color from step 16 to 256 */
    for(i = 0; i < 32; i++)
    {       
        g_u32RedefColorMap[i] = TTX_COLOR_CONVERT(g_u32RedefColorMap[i] );    
    }
    g_u32RedefColorMap[8] = 0;/*the entry 8 of default color map is transparent*/
    u8MagNum = pstCurrentPoint->stCurPgAddr.u8MagazineNum & 0x7;

    bFlag = HI_FALSE;
    if(HI_TRUE == g_bHasM29_0[u8MagNum])
    {
        memcpy(g_u32RedefColorMap + 16, g_stM29_0_Info[u8MagNum].u32CLUT2_3, 64);
        bFlag = HI_TRUE;
    }

    if(HI_TRUE == pstCurrentPoint->bHasP28_0)
    {
        memcpy(g_u32RedefColorMap + 16, pstCurrentPoint->stP28_0_Info.u32CLUT2_3, 64);
        bFlag = HI_TRUE;
    }

    /**convert the color from step 16 to 256 */
    if(HI_TRUE == bFlag)
    {
        for(i = 16; i < 32; i++)
        {       
            g_u32RedefColorMap[i] = TTX_COLOR_CONVERT(g_u32RedefColorMap[i] );        
        }
        bFlag = HI_FALSE;
    }
    
    
    if(HI_TRUE == g_bHasM29_4[u8MagNum])
    {
        memcpy(g_u32RedefColorMap, g_stM29_4_Info[u8MagNum].u32CLUT0_1, 64);
        bFlag = HI_TRUE;
    }       

    if(HI_TRUE == pstCurrentPoint->bHasP28_4)
    {
        memcpy(g_u32RedefColorMap, pstCurrentPoint->stP28_4_Info.u32CLUT0_1, 64);
        bFlag = HI_TRUE;
    }

     /**convert the color from step 16 to 256 */
    if(HI_TRUE == bFlag)
    {
        for(i = 0; i < 16; i++)
        {       
            g_u32RedefColorMap[i] = TTX_COLOR_CONVERT(g_u32RedefColorMap[i] );        
        }
    }    
     
    if(HI_FALSE == pstCurrentPoint->bHasP28_0)
    {
        if(HI_FALSE == pstCurrentPoint->bHasP28_4)
        {
            if(HI_FALSE == g_bHasM29_0[u8MagNum])
            {
                if(HI_TRUE == g_bHasM29_4[u8MagNum])
                {
                    memcpy(&pstCurrentPoint->stP28_0_Info, g_stM29_4_Info + u8MagNum, sizeof(TTX_P28_0_M29_0_INFO_S) - 64);
                }
                else
                {
                    pstCurrentPoint->stP28_0_Info.u82ndG0 = pstCurrentPoint->stP28_0_Info.u8DefG0G2;
                }
            }
            else
            {
                memcpy(&pstCurrentPoint->stP28_0_Info, g_stM29_0_Info + u8MagNum, sizeof(TTX_P28_0_M29_0_INFO_S) - 64);
            }
        }
        else
        {
            memcpy(&pstCurrentPoint->stP28_0_Info, &pstCurrentPoint->stP28_4_Info, sizeof(TTX_P28_0_M29_0_INFO_S) - 64);
        }
    }

    if(HI_FALSE == pstCurrentPoint->bHasP28_1)
    {
        if(HI_TRUE == g_bHasM29_1[u8MagNum])
        {
            memcpy(&pstCurrentPoint->stP28_1_Info, g_stM29_1_Info + u8MagNum, sizeof(TTX_P28_1_M29_1_INFO_S));
        }
    }

    /** black background substitute */
    pstCurrentPoint->bBlackBgSubstitute = HI_FALSE;

    pstCurrentPoint->u8BandStart[0] = 0;
    pstCurrentPoint->u8BandEnd[0] = 40;
    pstCurrentPoint->u8BandStart[1] = 40;
    pstCurrentPoint->u8BandEnd[1] = 40;
    pstCurrentPoint->u8BandStart[2] = 72;
    pstCurrentPoint->u8BandEnd[2] = 72;

    if((HI_TRUE == pstCurrentPoint->bHasP28_0) ||(HI_TRUE == pstCurrentPoint->bHasP28_4) || (HI_TRUE == g_bHasM29_0[u8MagNum]) || (HI_TRUE == g_bHasM29_4[u8MagNum]))
    {
        pstCurrentPoint->bBlackBgSubstitute = pstCurrentPoint->stP28_0_Info.bBlackBgSubstitute ? HI_TRUE : HI_FALSE;
        //if(pstCurrentPoint->stP28_0_Info.bSidePanelStatus)
        {
            i = pstCurrentPoint->stP28_0_Info.u8SidePanelCols;

            if(i)
            {
                if(pstCurrentPoint->stP28_0_Info.bSidePanelRight)
                {
                    pstCurrentPoint->u8BandEnd[1] = pstCurrentPoint->u8BandStart[1] + i;
                }
                if(pstCurrentPoint->stP28_0_Info.bSidePanelLeft)
                {
                    pstCurrentPoint->u8BandStart[2] = pstCurrentPoint->u8BandEnd[2] - (16 - i);
                }
            }
            else
            {
                if(pstCurrentPoint->stP28_0_Info.bSidePanelRight)
                {
                    pstCurrentPoint->u8BandEnd[1] = pstCurrentPoint->u8BandStart[1] + 16;
                }
                else if(pstCurrentPoint->stP28_0_Info.bSidePanelLeft)
                {
                    pstCurrentPoint->u8BandStart[2] = pstCurrentPoint->u8BandEnd[2] - 16;
                }
            }
        }
    }
    else if(HI_TRUE ==pstCurrentPoint->stMOTInfo.bFallback)
    {
        pstCurrentPoint->bBlackBgSubstitute = pstCurrentPoint->stMOTInfo.bBlackBgSubstitute;

        if (pstCurrentPoint->stMOTInfo.bSidePanelLeft && pstCurrentPoint->stMOTInfo.bSidePanelRight)
        {
            pstCurrentPoint->stP28_0_Info.bSidePanelLeft  = HI_TRUE;
            pstCurrentPoint->stP28_0_Info.bSidePanelRight = HI_TRUE;
            pstCurrentPoint->stP28_0_Info.u8SidePanelCols = 8;
            pstCurrentPoint->u8BandEnd[1]       = 40 + 8;
            pstCurrentPoint->u8BandStart[2]      = 40 + 16 + 8;
        }
        else if (pstCurrentPoint->stMOTInfo.bSidePanelRight)
        {
            pstCurrentPoint->stP28_0_Info.bSidePanelRight = HI_TRUE;
            pstCurrentPoint->stP28_0_Info.u8SidePanelCols = 16;
            pstCurrentPoint->u8BandEnd[1]       = 40 + 16;
        }
        else if (pstCurrentPoint->stMOTInfo.bSidePanelLeft)
        {
            pstCurrentPoint->stP28_0_Info.bSidePanelLeft = HI_TRUE;
            pstCurrentPoint->stP28_0_Info.u8SidePanelCols = 16;
            pstCurrentPoint->u8BandStart[2]      = 40 + 16;
        }
    }

    pstCurrentPoint->u8BandLeft[0] = pstCurrentPoint->u8BandEnd[2] -  pstCurrentPoint->u8BandStart[2];/**normal area*/
    pstCurrentPoint->u8BandLeft[1] = pstCurrentPoint->u8BandLeft[0] + 40;/**right side panel*/
    pstCurrentPoint->u8BandLeft[2] = 0;/**left side panel*/

      /** black background substitute */
    bBlackBgSubstitute = pstCurrentPoint->bBlackBgSubstitute;

    /** default row color */
    u8DefRowColor = pstCurrentPoint->stP28_0_Info.u8DefRowColor;

    if(pstCurrentPoint->stP28_0_Info.bSidePanelRight || pstCurrentPoint->stP28_0_Info.bSidePanelLeft)
    {
        pstCurrentPoint->u32ColumnNum = TTX_CMB_COL_NUM;
    }
    else
    {
        pstCurrentPoint->u32ColumnNum = TTX_LOP_COL_NUM;
    }

    if(u32MaxColNum != pstCurrentPoint->u32ColumnNum)
    {
        u32MaxColNum = pstCurrentPoint->u32ColumnNum;
        if (HI_TRUE == pstCurrentPoint->bNavigation)
        {
            stBuffParam.u32Row = TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR;
        }
        else
        {
            stBuffParam.u32Row = TTX_ROW_NUM + TTX_SUBPAGE_BAR;
        }

        stBuffParam.u32Column = u32MaxColNum;
        if (HI_SUCCESS != TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_DESTROY_BUFF, (HI_VOID *)1))
        {
            HI_ERR_TTX("TTX_Show_CallBack:HI_UNF_TTX_CB_DESTROY_BUFF error!\n");
            return;
        }

        if (HI_SUCCESS != TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_CREATE_BUFF, &stBuffParam))
        {
            HI_ERR_TTX("TTX_Show_CallBack: HI_UNF_TTX_CB_CREATE_BUFF error!\n");
            return;
        }
    }


    if ((pstCurrentPoint->u32Flag >> 1) & 0x1)/** flag C5 */
    {
        HI_INFO_TTX("C5,NewFlash and boxed\n");
        bBoxPage = HI_TRUE;
    }

    if ((pstCurrentPoint->u32Flag >> 2) & 0x1)   /** flag C6 */
    {
        HI_INFO_TTX("C6,Subpage boxed\n");
        bBoxPage = HI_TRUE;
    }

    if ((pstCurrentPoint->u32Flag >> 3) & 0x1)  /** flag C7  */
    {
        HI_INFO_TTX("C7, row 0 not display\n");
        u32LineNum = 1;
    }

    C10 = (pstCurrentPoint->u32Flag >> 6) & 0x1;   /** flag C10 */
    if (1 == C10)
    {
        HI_INFO_TTX("C10,row 1-24 not display");
    }

    if (bBoxPage || (1 == C10))
    {
        pstCurrentPoint->bUpdateTime = HI_FALSE;
    }
    else
    {
        pstCurrentPoint->bUpdateTime = HI_TRUE;
    }

    if (HI_NULL != pstCurrentPoint->pFlaAreaHead)   /** Before  show a page ,release the flash area of prve page */
    {
        HI_INFO_TTX("Release   ");
        TTX_Release_FlashArea(pstCurrentPoint->pFlaAreaHead);
        pstCurrentPoint->pFlaAreaHead = HI_NULL;
    }

    if (1 == C10)      /** don't display the page */
    {
        if (pstCurrentPoint->bNavigation)
        {
            s32Ret = TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR,
                                      u32MaxColNum);
        }
        else
        {
            s32Ret = TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32MaxColNum);
        }

        stFillRectParam.pstPageArea = &stPageArea;
        stFillRectParam.u32Color = 0x00000000;
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
        stRefrshLayerParam.pstPageArea = &stPageArea;
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);

        if(HI_SUCCESS != s32Ret)
        {
            HI_WARN_TTX("in 1 == C10 condition,TTX_DecShowPage, Errors occur \n");
        }
        
        return;
    }

    if (bBoxPage)   /** Subtitle , set the background  transparent */
    {
        if (pstCurrentPoint->bNavigation)
        {
            s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR,
                                       u32MaxColNum);
        }
        else
        {
            s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32MaxColNum);
        }

        stFillRectParam.pstPageArea = &stPageArea;
        stFillRectParam.u32Color = 0x00000000;
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
    }
    else
    {
        if (pstCurrentPoint->bTtxMix)
        {
            stFillRectParam.u32Color = 0x00000000;
        }
        else
        {
            stFillRectParam.u32Color = 0xff000000;/**black*/
        }

        stFillRectParam.pstPageArea = &stPageArea;
        if (pstCurrentPoint->bNavigation)
        {
            s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR, u32MaxColNum);
        }
        else
        {
            s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM, u32MaxColNum);
        }

        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);

        u8NumOfSubPg = TTX_MAX_SUBPAGENO;
        s32Ret |= TTX_Data_GetSubpageNum(pstCurrentPoint->stCurPgAddr.u8MagazineNum,
                                         pstCurrentPoint->stCurPgAddr.u8PageNum,
                                         u8szSubPage, &u8NumOfSubPg);
        if (u8NumOfSubPg == 0)      /** no subpage */
        {
            stFillRectParam.u32Color = 0x00000000;
            if (pstCurrentPoint->bNavigation)
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, TTX_ROW_NUM + TTX_NAVIGATION_BAR, 0, TTX_SUBPAGE_BAR,
                                           u32MaxColNum);
            }
            else
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, TTX_ROW_NUM, 0, TTX_SUBPAGE_BAR, u32MaxColNum);
            }

            s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
        }
    }


    /** find packet 26*/
    if(HI_SUCCESS != TTX_Data_FindPacket(pstCurrentPoint->pstCurPage, 26, 0, u8DataLine))
    {
        u32OpenCount = 0;

        for(i = 0; i < 4; i++)
        {
            if(pstCurrentPoint->stMOTInfo.stDefaultObject[i].u8ObjectType)
            {

                HI_U32 u32Pos = 0xff;

                if(TTX_DecodePOPPage(i < 2? &pstCurrentPoint->stMOTInfo.stGPOP : &pstCurrentPoint->stMOTInfo.stNPOP, \
                    pstCurrentPoint->stMOTInfo.stDefaultObject + i, &u32Pos, u8DataLine))
                {
                    /*find the object*/
                    if(u32Pos != 0xff)
                    {
                        pstParser = g_stTripParser + i;
                        pstParser->bOpen = HI_TRUE;
                        pstParser->bRowOpen = HI_FALSE;
                        pstParser->bStartDefine = HI_TRUE;
                        pstParser->u8ObjectType = pstCurrentPoint->stMOTInfo.stDefaultObject[i].u8ObjectType;

                        pstParser->u8Priority       = OBJECT_PRIORITY(pstParser->u8ObjectType);
                        pstParser->u8ActiveRow      = 0;
                        pstParser->u8ActiveCol      = 0;
                        pstParser->u8OffsetRow      = 0;
                        pstParser->u8OffsetCol      = 0;
                        pstParser->u8OriginRow      = 0;
                        pstParser->u8OriginCol      = 0;
                        pstParser->stAttr.u8ForeColor = pstParser->u8ObjectType == PASSIVE_OBJECT ? TTX_COLOR_WHITE : TTX_COLOR_UNDEFINED;
                        pstParser->stAttr.u8BackColor = pstParser->u8ObjectType == PASSIVE_OBJECT ? TTX_COLOR_BLACK : TTX_COLOR_UNDEFINED;
                        pstParser->u8Flash          = 0xff;
                        pstParser->u8GDRCSSubPage   = 0;
                        pstParser->u8NDRCSSubPage   = 0;
                        memcpy(pstParser->u8Data,  u8DataLine, TTX_LINE_MEM_SIZE);
                        pstParser->pu8Triplet = pstParser->u8Data + 3 + u32Pos * 3;
                        pstParser->u8TripletPos     = (HI_U8)u32Pos;

                        u32OpenCount++;
                    }
                }
            }

        }
    }
    else /** if packet x/26 is found... */
    {
        pstParser = g_stTripParser;
        pstParser->bOpen = HI_TRUE;
        pstParser->bRowOpen = HI_FALSE;
        pstParser->bStartDefine = HI_FALSE;
        pstParser->u8ObjectType = ACTIVE_OBJECT;/* just like active objects */

        pstParser->u8Priority       = OBJECT_PRIORITY(ACTIVE_OBJECT) + 1;
        pstParser->u8ActiveRow      = 0;
        pstParser->u8ActiveCol      = 0;
        pstParser->u8OffsetRow      = 0;
        pstParser->u8OffsetCol      = 0;
        pstParser->u8OriginRow      = 0;
        pstParser->u8OriginCol      = 0;
        pstParser->stAttr.u8ForeColor = TTX_COLOR_UNDEFINED;
        pstParser->stAttr.u8BackColor =  TTX_COLOR_UNDEFINED;
        pstParser->u8Flash          = 0xff;
        pstParser->u8GDRCSSubPage   = 0;
        pstParser->u8NDRCSSubPage   = 0;
        memcpy(pstParser->u8Data,  u8DataLine, TTX_LINE_MEM_SIZE);
        pstParser->pu8Triplet = pstParser->u8Data + 3;
        pstParser->u8TripletPos     = 0;

        u32OpenCount  = 1;
        u32DesignCode = 1;
    }

    for (; u32LineNum < TTX_ROW_NUM; u32LineNum++)
    {
        if (bLarged)   /** Double height or double size ,ingore  the next line */
        {
            bLarged = HI_FALSE;
            bDoubleSize   = HI_FALSE;
            stLOPAttr.bDHeight = HI_FALSE;
            stLOPAttr.bDWidth = HI_FALSE;
            continue;
        }
        bLarged = HI_FALSE;

        if (bBoxPage)
        {
            bFlag = HI_TRUE;/*if this line has not valid char ,skip it */
            u32Band = 0;
            for (u32ColumnNum = pstCurrentPoint->u8BandStart[u32Band]; u32ColumnNum < pstCurrentPoint->u8BandEnd[u32Band]; u32ColumnNum++)
            {
                if (pstCurrentPoint->u32aPageText[u32LineNum][u32ColumnNum] > 0x20)
                {
                    bFlag = HI_FALSE;
                    break;
                }
            }

            if (HI_TRUE == bFlag)
            {
                continue;
            }
        }

        u8FullRowColor = u8DefRowColor;

        for(u32Band = 0; u32Band < 3; u32Band++)/*0:Normal area 1:Right sidepanel 2:Left sidepanel*/
        {
            HI_U32 u32X;/*the actual column num in screen*/


            u32CurrentCh = 0;
            u32MosaicCh = 0x20;
            u32Fillback = 0;
            bSetFlash = HI_FALSE;
            bSetAForeground = HI_FALSE;
            bSetMForeground = HI_FALSE;
            TmpForeground = pstCurrentPoint->stP28_0_Info.u8ForeCLUT + TTX_COLOR_WHITE;
            bMosaic = HI_FALSE;
            bStartBox = HI_FALSE;
            //bLarged = HI_FALSE;
            bDoubleSize = HI_FALSE;
            bHoldMosaic = HI_FALSE;
            bReleaseMos = HI_FALSE;
            bContiguous = HI_TRUE;
            bEsc = HI_FALSE;
            u8LOPFlash = 0;
            bModifiedG0G2 = HI_FALSE;
            bUseDefaultCharSet = HI_TRUE;
            bEnhanceChar = HI_FALSE;

            /* reset LOP attributes at the row beginning */
            stLOPAttr.bDHeight = HI_FALSE;
            stLOPAttr.bBox = HI_FALSE;
            stLOPAttr.bConceal = HI_FALSE;
            stLOPAttr.bUnderline = HI_FALSE;
            stLOPAttr.bInvert = HI_FALSE;
            stLOPAttr.bSeparated = HI_FALSE;
            stLOPAttr.bDWidth = HI_FALSE;
            stLOPAttr.bChanged = HI_FALSE;

            stLOPAttr.u8BackColor     = bBlackBgSubstitute ? u8FullRowColor : pstCurrentPoint->stP28_0_Info.u8BackCLUT + TTX_COLOR_BLACK;
            stLOPAttr.u8ForeColor     = pstCurrentPoint->stP28_0_Info.u8ForeCLUT + TTX_COLOR_WHITE;

            TTX_Show_GetLOPG0G2AndNationSet(pstCurrentPoint, bUseDefaultCharSet, &enLOPG0Set, &enLOPG2Set, &enNationSet);

            for (u32ColumnNum = pstCurrentPoint->u8BandStart[u32Band], u32X = pstCurrentPoint->u8BandLeft[u32Band]; \
                u32ColumnNum < pstCurrentPoint->u8BandEnd[u32Band]; u32ColumnNum++, u32X++)
            {
                if (bSetAForeground)       /** Set alpha foreground  color */
                {
                    bMosaic = HI_FALSE;
                    stLOPAttr.u8ForeColor = TmpForeground;
                    bSetAForeground = HI_FALSE;
                }

                if (bSetMForeground)   /** Set mosaic foreground  color */
                {
                    bMosaic = HI_TRUE;
                    stLOPAttr.u8ForeColor = TmpForeground;
                    bSetMForeground = HI_FALSE;
                }

                if (bSetFlash)     /** Start Flash */
                {
                    u8LOPFlash = 1;
                    bSetFlash = HI_FALSE;
                }

                if (bStartBox)
                {
                    stLOPAttr.bBox = HI_TRUE;
                }
                else
                {
                    stLOPAttr.bBox = HI_FALSE;
                }

                if (bReleaseMos)
                {
                    bHoldMosaic = HI_FALSE;
                    bReleaseMos = HI_FALSE;
                }

                if(bEsc)
                {
                    bEsc = HI_FALSE;
                    bUseDefaultCharSet = (bUseDefaultCharSet == HI_TRUE) ? HI_FALSE:HI_TRUE;
                    TTX_Show_GetLOPG0G2AndNationSet(pstCurrentPoint, bUseDefaultCharSet, &enLOPG0Set, &enLOPG2Set, &enNationSet);
                }

                if(!u32Band)/*normal area*/
                {
                    u32CurrentCh = pstCurrentPoint->u32aPageText[u32LineNum][u32ColumnNum];
                    
                    if (u32CurrentCh != 0xff)/**  not invalid  char */
                    {
                        u32TempCh = P_CHARACTER(u32CurrentCh);
                     
                        /* process space attributes */
                        if (u32TempCh < 0x20)
                        {

                            switch (u32TempCh)
                            {
                                case 0x0:              /** Set foreground color */
                                case 0x1:
                                case 0x2:
                                case 0x3:
                                case 0x4:
                                case 0x5:
                                case 0x6:
                                case 0x7:
                                {
                                    bSetAForeground = HI_TRUE;
                                    TmpForeground = u32TempCh | pstCurrentPoint->stP28_0_Info.u8ForeCLUT;//s_ColorSet[u32TempCh];
                                    if (TmpForeground != stLOPAttr.u8BackColor)
                                    {
                                        stLOPAttr.bConceal = HI_FALSE;    /** The Background color be same to foreground color  , conceal */
                                    }
                                    else
                                    {
                                        stLOPAttr.bConceal = HI_TRUE;
                                    }

                                    TTX_PutColor(u32TempCh);
                                }
                                break;
                            case 0x08:          /** Flash will begin from the next char */
                                HI_INFO_TTX("Flash1:(%d,%d)", u32LineNum, u32ColumnNum);
                                bSetFlash = HI_TRUE;
                                //u8LOPFlash = 1;
                                break;
                            case 0x09:        /** Flash end */
                                HI_INFO_TTX("Flash0:(%d,%d)", u32LineNum, u32ColumnNum);
                                u8LOPFlash = 0;
                                break;
                            case 0x0A:
                                HI_INFO_TTX("Box0");
                                bStartBox = HI_FALSE;
                                break;
                            case 0x0B:
                                HI_INFO_TTX("Box1");
                                bStartBox = HI_TRUE;
                                break;
                            case 0x0C:                    /** Normal size  */
                                stLOPAttr.bDHeight = HI_FALSE;
                                stLOPAttr.bDWidth = HI_FALSE;
                                bDoubleSize   = HI_FALSE;
                                bHoldMosaic = HI_FALSE;
                                HI_INFO_TTX("NS1");
                                break;
                            case 0x0D:                /** Double height */
                                stLOPAttr.bDHeight = HI_TRUE;
                                bLarged = HI_TRUE;
                                bDoubleSize  = HI_FALSE;
                                bHoldMosaic  = HI_FALSE;
                                u32Fillback += 1;
                                HI_INFO_TTX("DH");
                                break;
                            case 0x0E:          /** Double width  nonsupport for the moment*/
                                stLOPAttr.bDWidth = HI_FALSE;
                                bDoubleSize   = HI_FALSE;
                                stLOPAttr.bDHeight = HI_FALSE;
                                bHoldMosaic = HI_FALSE;
                                HI_INFO_TTX("DW");
                                break;
                            case 0x0F:        /** Double size , treated as double Height*/
                                bDoubleSize = HI_FALSE;
                                bLarged = HI_TRUE;
                                stLOPAttr.bDWidth  = HI_FALSE;
                                stLOPAttr.bDHeight = HI_TRUE;
                                bHoldMosaic  = HI_FALSE;
                                u32Fillback += 1;
                                HI_INFO_TTX("NS0");
                                break;
                            case 0x10:
                            case 0x11:
                            case 0x12:
                            case 0x13:
                            case 0x14:
                            case 0x15:
                            case 0x16:
                            case 0x17:
                            {
                                bSetMForeground = HI_TRUE;            /** Set foreground color and mosaic mode */
                                TmpForeground = (u32TempCh - 0x10) | pstCurrentPoint->stP28_0_Info.u8ForeCLUT;
                                if (TmpForeground != stLOPAttr.u8BackColor)
                                {
                                    stLOPAttr.bConceal = HI_FALSE;
                                }
                                else
                                {
                                    stLOPAttr.bConceal = HI_TRUE;
                                }

                                TTX_PutColor(u32TempCh);
                            }
                                break;
                            case 0x18:
                                stLOPAttr.bConceal = HI_TRUE;               /** Conceal */
                                HI_INFO_TTX("Con1");
                                break;
                            case 0x19:
                                bContiguous = HI_TRUE;       /** Contiguous mosaic */
                                HI_INFO_TTX("Cont1");
                                break;
                            case 0x1A:
                                bContiguous = HI_FALSE;         /** Seperated  mosaic */
                                HI_INFO_TTX("Cont0");
                                break;
                            case 0x1B:
                                bEsc = HI_TRUE;
                                HI_INFO_TTX("Switch G0 Set");
                                break;
                            case 0x1C:
                                stLOPAttr.u8BackColor = bBlackBgSubstitute ? u8FullRowColor : pstCurrentPoint->stP28_0_Info.u8BackCLUT;//s_ColorSet[0];      /** Black  background */
                                if (stLOPAttr.u8ForeColor != stLOPAttr.u8BackColor)
                                {
                                    stLOPAttr.bConceal = HI_FALSE;
                                }
                                else
                                {
                                    stLOPAttr.bConceal = HI_TRUE;
                                }

                                TTX_PutColor(u32TempCh);
                                break;
                            case 0x1D:
                                stLOPAttr.u8BackColor = (stLOPAttr.u8ForeColor & 0x7) | pstCurrentPoint->stP28_0_Info.u8BackCLUT;
                                stLOPAttr.bConceal = HI_TRUE;
                                HI_INFO_TTX("SetB");
                                break;
                            case 0x1E:              /** Hold mosaic */
                                bHoldMosaic = HI_TRUE;
                                HI_INFO_TTX("Hold1");
                                break;
                            case 0x1F:                /** Release mosaic */
                                bReleaseMos = HI_TRUE;
                                HI_INFO_TTX("Hold0");
                                break;
                            default:
                                HI_INFO_TTX("Unkown char");
                                break;
                            }
                            bSpacingAttr = HI_TRUE;
                        }
                        else
                        {
                            bSpacingAttr = HI_FALSE;
                        }
                    }
                    
                }

                if (bBoxPage && !stLOPAttr.bBox) //Box flag
                {
                    BackgroundRec[u32ColumnNum] = 0;/*transparent*/
                    continue;
                }


                 /* take LOP attributes as default before parsing enhancement data */
                stCMBAttr         = stLOPAttr;
                u8CMBDRCSChar     = 0xff;
                //u8CMBFlash        = u8LOPFlash;

                 /****************************/
                /* PROCESS ENHANCEMENT DATA */
                /****************************/


                u8CharPriority  = OBJECT_PRIORITY(ACTIVE_OBJECT);
                u8ForePriority  = OBJECT_PRIORITY(ACTIVE_OBJECT);
                u8BackPriority  = OBJECT_PRIORITY(ACTIVE_OBJECT);
                u8AttrPriority  = OBJECT_PRIORITY(ACTIVE_OBJECT);
                u8FlashPriority = OBJECT_PRIORITY(ACTIVE_OBJECT);
                u32Cell = (u32LineNum << 8) + u32ColumnNum;

                for(u32Parser = 0; u32Parser < u32OpenCount; u32Parser++)
                {
                    pstParser = g_stTripParser + u32Parser;
                    if(pstParser->bOpen)
                    {
                        HI_BOOL bRowOpen = pstParser->bRowOpen;
                        HI_U8 u8Addr, u8Mode, u8Data;
                        while((pstParser->bOpen && ((((HI_U32)pstParser->u8ActiveRow << 8) + pstParser->u8ActiveCol) <= u32Cell)) || (pstParser->u8ActiveCol >= 0x48 && pstParser->u8ActiveRow <= u32LineNum))
                        {
                            if(!TTX_DecodeHam24_18(pstParser->pu8Triplet, &u8Addr, &u8Mode, &u8Data))
                            {
                                pstParser->bOpen = HI_FALSE;
                                break;
                            }
                            /* parse those triplets that will change active position */
                            if(u8Addr < 40)
                            {
                                switch (u8Mode)
                                {
                                    case 0x04:
                                    case 0x05:
                                    case 0x06:
                                    case 0x0a: /* triplets for PDC or reserved triplets */
                                        break;
                                    default: /* other triplets all effect active position */
                                        pstParser->u8ActiveCol = pstParser->u8OriginCol + u8Addr;
                                        break;
                                }
                            }
                            else if(u8Addr < 64)
                            {
                                switch (u8Mode)
                                {
                                    case 0x00: /* 00000 full screen color */

                                    /* fall through */
                                    case 0x01: /* 00001 full row color */
                                    if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                    {
                                        pstParser->u8ActiveCol = pstParser->u8OriginCol;
                                        pstParser->u8ActiveRow = u8Addr - 40;
                                        if (pstParser->u8ActiveRow == 0)
                                        {
                                            pstParser->u8ActiveRow = 24;
                                        }
                                        pstParser->u8ActiveRow += pstParser->u8OriginRow;
                                    }
                                    break;

                                    case 0x04: /* 00100 set active position */
                                    pstParser->u8ActiveCol = pstParser->u8OriginCol + u8Data;
                                    pstParser->u8ActiveRow = u8Addr - 40;
                                    if (pstParser->u8ActiveRow == 0)
                                    {
                                        pstParser->u8ActiveRow = 24;
                                    }
                                    pstParser->u8ActiveRow += pstParser->u8OriginRow;
                                    break;

                                    case 0x07: /* 00111 address display row 0 */
                                    if (pstParser->u8ObjectType == ACTIVE_OBJECT && u8Addr == 0x3f)
                                    {
                                        pstParser->u8ActiveCol = pstParser->u8OriginCol;
                                        pstParser->u8ActiveRow = pstParser->u8OriginRow;
                                    }
                                    break;
                                }
                            }
                              /* if the element is at the current position... */
                            if ((pstParser->u8ActiveRow == u32LineNum) && (pstParser->u8ActiveCol == u32ColumnNum))
                            {
                                bRowOpen = pstParser->bRowOpen = HI_TRUE;

                                if (u8Addr < 40) /* column address */
                                {
                                    if (u8Mode > 0x10) /* 10001 ~ 11111 G0 character with diacritical mark */
                                    {

                                            u8Charset = 0;
                                            u8Accent = u8Mode & 0x0f;
                                        goto PutChar;
                                    }
                                    else
                                    {
                                        switch (u8Mode)
                                        {
                                            case 0x09: /* 01001 character from the G0 set ( level 2.5 & 3.5 ) */
                                            case 0x10: /* 10000 G0 character without diacritical mark */
                                                if (u8Data == 0x2A)
                                                {
                                                    /* replace packet x/26 character '*' by '@' in case of no diacritical mark */

                                                    u8Data = '@';
                                                }
                                                u8Charset = 0;
                                                u8Accent = 0;
                                                goto PutChar;
                                            case 0x01: /* 00001 block mosaic character from the G1 set */
                                                u8Charset = 1;
                                                /* patch: see ETSI EN 300 706 15.7.1 NOTE 3 */
                                                //if (u8Charset < 14) u8Charset = 0;
                                                u8Accent = 0;
                                                goto PutChar;
                                            case 0x0f: /* 01111 character from the G2 set */
                                                u8Charset = 2;
                                                u8Accent = 0;
                                                goto PutChar;

                                            case 0x02: /* 00010 line drawing or smoothed mosaic character form the G3 set ( level 1.5 ) */
                                            case 0x0b: /* 01011 line drawing or smoothed mosaic character from the G3 set ( level 2.5 & 3.5 ) */
                                                u8Charset = 3;
                                                u8Accent = 0;
                                        PutChar:
                                            if (u8Data >= 0x20 && pstParser->u8Priority >= u8CharPriority)
                                            {
                                                bEnhanceChar = HI_TRUE;
                                                TTX_SetPgActPos(pstCurrentPoint, u32LineNum, u32ColumnNum, u8Charset, u8Data, u8Accent);
                                                if (pstParser->u8ObjectType == PASSIVE_OBJECT)
                                                {
                                                    stCMBAttr.u8ForeColor = pstParser->stAttr.u8ForeColor;
                                                    stCMBAttr.u8BackColor = pstParser->stAttr.u8BackColor;
                                                    //u8CMBFlash        = pstParser->u8Flash;
                                                    u8ForePriority  = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                    u8BackPriority  = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                    u8AttrPriority  = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                    u8FlashPriority = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                }

                                                u8CharPriority = pstParser->u8Priority;
                                            }

                                            break;
                                        case 0x00: /* 00000 foreground color */
                                            if (!(u8Data & 0x60))
                                            {
                                                if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                                {
                                                    stLOPAttr.u8ForeColor = u8Data & 0x1f;
                                                    if (u8ForePriority <= pstParser->u8Priority)
                                                    {
                                                        stCMBAttr.u8ForeColor  = stLOPAttr.u8ForeColor;
                                                        u8ForePriority = pstParser->u8Priority;
                                                    }
                                                }
                                                else
                                                {
                                                    pstParser->stAttr.u8ForeColor = u8Data & 0x1f;
                                                }
                                            }
                                            break;

                                        case 0x03: /* 00011 background color */
                                            if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                            {
                                                stLOPAttr.u8BackColor = u8Data & 0x1f;
                                                if (u8BackPriority <= pstParser->u8Priority)
                                                {
                                                    stCMBAttr.u8BackColor = stLOPAttr.u8BackColor;
                                                    u8BackPriority = pstParser->u8Priority;
                                                }
                                            }
                                            else
                                            {
                                                pstParser->stAttr.u8BackColor = u8Data & 0x1f;
                                            }
                                            break;

                                        case 0x0c: /* 01100 display attributes */
                                            if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                            {

                                                stLOPAttr.bDHeight = (u8Data & 0x1) ? HI_TRUE : HI_FALSE;
                                                stLOPAttr.bBox = (u8Data & 0x2) ? HI_TRUE : HI_FALSE;
                                                stLOPAttr.bConceal = (u8Data & 0x4) ? HI_TRUE : HI_FALSE;
                                                stLOPAttr.bUnderline = (u8Data & 0x20) ? HI_TRUE : HI_FALSE;
                                                stLOPAttr.bInvert = (u8Data & 0x10) ? HI_TRUE : HI_FALSE;
                                                stLOPAttr.bSeparated = (u8Data & 0x20) ? HI_TRUE : HI_FALSE;
                                                stLOPAttr.bDWidth = (u8Data & 0x40) ? HI_TRUE : HI_FALSE;

                                                if (!stLOPAttr.bSeparated)
                                                {
                                                    bContiguous = HI_TRUE; /* level one separated-mosaic can be canceled by local enhancement data or active objects */
                                                }

                                                if (u8AttrPriority <= pstParser->u8Priority)
                                                {
                                                    stCMBAttr.bDHeight = stLOPAttr.bDHeight ;
                                                    stCMBAttr.bBox = stLOPAttr.bBox;
                                                    stCMBAttr.bConceal = stLOPAttr.bConceal;
                                                    stCMBAttr.bUnderline =stLOPAttr.bUnderline;
                                                    stCMBAttr.bInvert = stLOPAttr.bInvert;
                                                    stCMBAttr.bSeparated = stLOPAttr.bSeparated;
                                                    stCMBAttr.bDWidth =  stLOPAttr.bDWidth;
                                                    u8AttrPriority = pstParser->u8Priority;
                                                }
                                            }
                                            else
                                            {
                                                pstParser->stAttr.bDHeight = (u8Data & 0x1) ? HI_TRUE : HI_FALSE;
                                                pstParser->stAttr.bBox = (u8Data & 0x2) ? HI_TRUE : HI_FALSE;
                                                pstParser->stAttr.bConceal = (u8Data & 0x4) ? HI_TRUE : HI_FALSE;
                                                pstParser->stAttr.bUnderline = (u8Data & 0x20) ? HI_TRUE : HI_FALSE;
                                                pstParser->stAttr.bInvert = (u8Data & 0x10) ? HI_TRUE : HI_FALSE;
                                                pstParser->stAttr.bSeparated = (u8Data & 0x20) ? HI_TRUE : HI_FALSE;
                                                pstParser->stAttr.bDWidth = (u8Data & 0x40) ? HI_TRUE : HI_FALSE;


                                                pstParser->stAttr.bChanged = HI_TRUE;
                                            }
                                            break;

                                        case 0x07: /* 00111 additional flash functions */
                                            if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                            {
                                                if (u8FlashPriority <= pstParser->u8Priority)
                                                {
                                                    u8LOPFlash = u8Data & 0x1f;
                                                    //u8CMBFlash = u8LOPFlash;
                                                    u8FlashPriority = pstParser->u8Priority;
                                                }
                                            }
                                            else
                                            {
                                                pstParser->u8Flash = u8Data & 0x1f;
                                            }
                                            break;

                                        case 0x08: /* 01000 modified G0 and G2 character design */
                                            TTX_Show_GetModifiedG0G2(u8Data & 0x7f, &enModifiedG0Set, &enModifiedG2Set);
                                            bModifiedG0G2 = HI_TRUE;
                                            break;

                                        case 0x0d: /* 01101 DRCS character invokation */
                                            if (pstParser->u8Priority >= u8CharPriority)
                                            {
                                                if (u8Data & 0x40)
                                                {
                                                    if (pstCurrentPoint->stMOTInfo.stNDRCS.u8PageNum != 0xff)
                                                    {
                                                        u8CMBDRCSChar    = u8Data;/*u8CMBDRCSChar:is the PTU num*/
                                                        u8CMBDRCSSubPage = pstParser->u8NDRCSSubPage;/*CMBDRCSSubPage is the subpage num, which the PTU be defined*/
                                                    }
                                                }
                                                else
                                                {
                                                    if (pstCurrentPoint->stMOTInfo.stGDRCS.u8PageNum != 0xff)
                                                    {
                                                        u8CMBDRCSChar    = u8Data;
                                                        u8CMBDRCSSubPage = pstParser->u8GDRCSSubPage;
                                                    }
                                                }
                                                if (u8CMBDRCSChar != 0xff)
                                                {
                                                    if (pstParser->u8ObjectType == PASSIVE_OBJECT)
                                                    {
                                                        stCMBAttr         = pstParser->stAttr;
                                                        //u8CMBFlash        = pstParser->u8Flash;
                                                        u8ForePriority  = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                        u8BackPriority  = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                        u8AttrPriority  = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                        u8FlashPriority = OBJECT_PRIORITY(PASSIVE_OBJECT);
                                                    }
                                                    u8CharPriority = pstParser->u8Priority;
                                                }
                                            }
                                            break;

                                        case 0x0e: /* 01110 font style */
                                            /* only for level 3.5 */
                                            break;
                                        }
                                    }
                                }
                                else if (u8Addr < 64) /* row address */
                                {
                                    switch (u8Mode)
                                    {
                                    case 0x00: /* 00000 full screen color */
                                        if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                        {
                                            if (!(u8Data & 0xe0))
                                            {
                                                u8DefRowColor = u8Data;
                                                u8FullRowColor = u8DefRowColor;

                                                if (bBlackBgSubstitute)
                                                {
                                                    stLOPAttr.u8BackColor = u8FullRowColor;
                                                    stCMBAttr.u8BackColor = u8FullRowColor;
                                                }
                                            }
                                        }
                                        break;

                                    case 0x07: /* 00111 address display row 0 */
                                        if (u8Addr != 0x3f) break;
                                        /* fall through */

                                    case 0x01: /* 00001 full row color */
                                        if (pstParser->u8ObjectType == ACTIVE_OBJECT)
                                        {
                                            switch (u8Data & 0x60) /* s1 s0, bit6 bit5 */
                                            {
                                            case 0x60:
                                                u8DefRowColor = u8Data & 0x1f;
                                                /* fall through */
                                            case 0x00:
                                                u8FullRowColor = u8Data & 0x1f;
                                                if (bBlackBgSubstitute)
                                                {
                                                    stLOPAttr.u8BackColor = u8FullRowColor;
                                                    stCMBAttr.u8BackColor = u8FullRowColor;
                                                }
                                                break;
                                            }
                                        }
                                        break;

                                    case 0x10: /* 10000 origin modifier */
                                        pstParser->u8OffsetRow = u8Addr - 40;
                                        pstParser->u8OffsetCol = u8Data;
                                        break;

                                    case 0x11: /* 10001 active object invokation */
                                    case 0x12: /* 10001 adaptive object invokation */
                                    case 0x13: /* 10001 passive object invokation */
                                        if (u32OpenCount >= TTX_MAX_OPEN_OBJECTS)
                                        {
                                            /* object buffer is full, try to clean up */
                                            TTX_TRIPLET_PARSER *p;
                                            TTX_TRIPLET_PARSER *q = g_stTripParser;
                                            HI_U32 m, n = 0;

                                            for (m = 0; m < u32OpenCount; m++)
                                            {
                                                p = g_stTripParser + m;
                                                if (p->bOpen)
                                                {
                                                    if (p != q)
                                                    {
                                                        memcpy(q, p, sizeof(TTX_TRIPLET_PARSER));
                                                        if (m == u32Parser)
                                                        {
                                                            u32Parser = n;
                                                            pstParser = q;
                                                        }
                                                    }
                                                    n++;
                                                    q = g_stTripParser + n;
                                                }
                                            }
                                            u32OpenCount = n;
                                        }

                                        if (u32OpenCount < TTX_MAX_OPEN_OBJECTS)
                                        {
                                            TTX_TRIPLET_PARSER *p = g_stTripParser + u32OpenCount;
                                            p->stAttr.bDHeight = HI_FALSE;
                                            p->stAttr.bBox = HI_FALSE;
                                            p->stAttr.bConceal = HI_FALSE;
                                            p->stAttr.bUnderline = HI_FALSE;
                                            p->stAttr.bInvert = HI_FALSE;
                                            p->stAttr.bSeparated = HI_FALSE;
                                            p->stAttr.bDWidth = HI_FALSE;
                                            p->stAttr.bChanged = HI_FALSE;

                                            p->bRowOpen         = HI_FALSE;
                                            p->bStartDefine     = HI_TRUE;
                                            p->u8ObjectType     = u8Mode & 0x0f;
                                            p->u8Priority       = OBJECT_PRIORITY(p->u8ObjectType);
                                            p->u8ActiveRow      = pstParser->u8OffsetRow + u32LineNum;
                                            p->u8ActiveCol      = pstParser->u8OffsetCol + u32ColumnNum;
                                            p->u8OffsetRow      = 0;
                                            p->u8OffsetCol      = 0;
                                            p->u8OriginRow      = pstParser->u8OffsetRow + u32LineNum;
                                            p->u8OriginCol      = pstParser->u8OffsetCol + u32ColumnNum;
                                            p->stAttr.u8ForeColor = p->u8ObjectType == PASSIVE_OBJECT ? TTX_COLOR_WHITE : 0xff;
                                            p->stAttr.u8BackColor = p->u8ObjectType == PASSIVE_OBJECT ? TTX_COLOR_BLACK : 0xff;
                                            p->u8Flash          = p->u8ObjectType == PASSIVE_OBJECT ? 0x00 : 0xff;
                                            p->u8GDRCSSubPage   = 0;
                                            p->u8NDRCSSubPage   = 0;

                                            if (u8Addr & 0x10) /* POP or GPOP object */
                                            {
                                                TTX_OBJECT_POINTER_S  ObjPtr;
                                                HI_U32            u32Pos;

                                                ObjPtr.u8ObjectType = u8Mode & 0x0f;
                                                ObjPtr.u8SubPageNum = u8Data & 0x0f;
                                                ObjPtr.u8PointerTab = u8Addr & 0x03;
                                                u8Data >>= 4;
                                                ObjPtr.u8PointerPos = u8Data & 0x1;
                                                u8Data >>= 1;
                                                ObjPtr.u8TripletNum = u8Data + (u8Data << 1) + (u8Mode & 0x0f);

                                                if(HI_SUCCESS == TTX_DecodePOPPage(u8Addr & 0x8 ? &pstCurrentPoint->stMOTInfo.stGPOP : &pstCurrentPoint->stMOTInfo.stNPOP, &ObjPtr, &u32Pos, u8DataLine))
                                                {
                                                    if(0xff != u32Pos)
                                                    {
                                                        memcpy(p->u8Data,  u8DataLine, TTX_LINE_MEM_SIZE);
                                                        p->pu8Triplet = p->u8Data + 3 + u32Pos * 3;
                                                        p->u8TripletPos     = (HI_U8)u32Pos;
                                                        p->bOpen        = HI_TRUE;
                                                        u32OpenCount++;
                                                    }
                                                }
                                            }
                                            else /* local object */
                                            {

                                                if(HI_SUCCESS == TTX_Data_FindPacket(pstCurrentPoint->pstCurPage, 26, ((u8Data >> 4) & 0x7) + ((u8Addr & 0x1 ) << 3), u8DataLine))
                                                {
                                                    p->u8TripletPos = u8Data & 0x0f;
                                                    if(p->u8TripletPos < 13)
                                                    {
                                                        memcpy(p->u8Data,  u8DataLine, TTX_LINE_MEM_SIZE);
                                                        p->pu8Triplet = p->u8Data + 3 + p->u8TripletPos * 3;
                                                        p->bOpen        = HI_TRUE;
                                                        u32OpenCount++;
                                                    }
                                                }

                                            }

                                            pstParser->u8OffsetRow = pstParser->u8OffsetCol = 0;
                                        }
                                        break;

                                    case 0x18: /* 11000 DRCS mode */
                                        if (u8Data & 0x40) /* normal DRCS */
                                        {
                                            pstParser->u8NDRCSSubPage = u8Data & 0x0f;
                                            pstCurrentPoint->stMOTInfo.stNDRCS.u16PageSubCode = pstParser->u8NDRCSSubPage;
                                        }
                                        else /* global DRCS */
                                        {
                                            pstParser->u8GDRCSSubPage = u8Data & 0x0f;
                                            pstCurrentPoint->stMOTInfo.stGDRCS.u16PageSubCode = pstParser->u8GDRCSSubPage;

                                        }
                                        break;
                                    case 0x15: /* 10101 active object definition */
                                    case 0x16: /* 10110 adaptive object definition */
                                    case 0x17: /* 10111 passive object definition */
                                        if (pstParser->bStartDefine)
                                            pstParser->bStartDefine = HI_FALSE;
                                        else
                                            pstParser->bOpen = HI_FALSE;
                                        break;

                                    case 0x1f: /* 11111 termination marker */
                                        pstParser->bOpen = HI_FALSE;
                                        break;
                                    }
                                }
                                else /* invalid row address... */
                                {
                                    /* error */
                                    pstParser->bOpen = HI_FALSE;
                                    break;
                                }
                            }
                            else /* if active position changed... */
                            {
                                /* if it's the last element on this row... */
                                if (pstParser->u8ActiveRow != u32LineNum)
                                {
                                    pstParser->bRowOpen = HI_FALSE;
                                }
                            }

                            if( (pstParser->u8ActiveCol >= 0x48) && (pstParser->u8ActiveRow <= u32LineNum) )
                            {
                                /* read the next triplet */
                                pstParser->u8TripletPos++;
                                if (pstParser->u8TripletPos >= 13)
                                {
                                     /* goto the next packet */
                                     if(HI_SUCCESS == TTX_Data_FindPacket(pstCurrentPoint->pstCurPage, 26, u32DesignCode, u8DataLine))
                                     {
                                        pstParser->u8TripletPos = 0;
                                        memcpy(pstParser->u8Data,  u8DataLine, TTX_LINE_MEM_SIZE);
                                        pstParser->pu8Triplet = pstParser->u8Data + 3;
                                        u32DesignCode++;
                                     }
                                    else
                                    {
                                        /* error */
                                        pstParser->bOpen = HI_FALSE;
                                        break;
                                    }
                                }
                                else
                                {
                                    pstParser->pu8Triplet += 3;
                                }
                            }

                            /* if we are before the current position... */
                            if ((((HI_U32)pstParser->u8ActiveRow << 8) + pstParser->u8ActiveCol) <= u32Cell)
                            {
                                /* read the next triplet */
                                pstParser->u8TripletPos++;
                                if (pstParser->u8TripletPos >= 13)
                                {
                                    /* goto the next packet */
                                     if(HI_SUCCESS == TTX_Data_FindPacket(pstCurrentPoint->pstCurPage, 26, u32DesignCode, u8DataLine))
                                     {
                                        pstParser->u8TripletPos = 0;
                                        memcpy(pstParser->u8Data,  u8DataLine, TTX_LINE_MEM_SIZE);
                                        pstParser->pu8Triplet = pstParser->u8Data + 3;
                                        u32DesignCode++;
                                     }
                                    else
                                    {
                                        /* error */
                                        pstParser->bOpen = HI_FALSE;
                                        break;
                                    }
                                }
                                else
                                {
                                    pstParser->pu8Triplet += 3;
                                }
                            }

                        }

                         /* overwrite LOP attributes with adaptive object attributes */
                        if (pstParser->u8ObjectType == ADAPTIVE_OBJECT && bRowOpen)
                        {
                            if (pstParser->stAttr.u8ForeColor != 0xff && u8ForePriority <= OBJECT_PRIORITY(ADAPTIVE_OBJECT))
                            {
                                stCMBAttr.u8ForeColor = pstParser->stAttr.u8ForeColor;
                                u8ForePriority = OBJECT_PRIORITY(ADAPTIVE_OBJECT);
                            }
                            if (pstParser->stAttr.u8BackColor != 0xff && u8BackPriority <= OBJECT_PRIORITY(ADAPTIVE_OBJECT))
                            {
                                stCMBAttr.u8BackColor = pstParser->stAttr.u8BackColor;
                                u8BackPriority = OBJECT_PRIORITY(ADAPTIVE_OBJECT);
                            }
                            if (pstParser->stAttr.bChanged && u8AttrPriority <= OBJECT_PRIORITY(ADAPTIVE_OBJECT))
                            {
                                stCMBAttr.bDHeight = pstParser->stAttr.bDHeight ;
                                stCMBAttr.bBox = pstParser->stAttr.bBox;
                                stCMBAttr.bConceal = pstParser->stAttr.bConceal;
                                stCMBAttr.bUnderline =pstParser->stAttr.bUnderline;
                                stCMBAttr.bInvert = pstParser->stAttr.bInvert;
                                stCMBAttr.bSeparated = pstParser->stAttr.bSeparated;
                                stCMBAttr.bDWidth =  pstParser->stAttr.bDWidth;

                                u8AttrPriority = OBJECT_PRIORITY(ADAPTIVE_OBJECT);
                            }
                            if (pstParser->u8Flash != 0xff && u8FlashPriority <= OBJECT_PRIORITY(ADAPTIVE_OBJECT))
                            {
                                //u8CMBFlash = pstParser->u8Flash;
                                u8FlashPriority = OBJECT_PRIORITY(ADAPTIVE_OBJECT);
                            }
                        }
                    }


                }

                /*the display data may be rewrited by object or the data of side panels may be defined*/
                u32CurrentCh = pstCurrentPoint->u32aPageText[u32LineNum][u32ColumnNum];
                if (u32CurrentCh == 0xff)     /**  invalid  char */
                {
                    continue;
                }

                if (TTX_IsMosaicChar(bMosaic, u32CurrentCh))
                {
                    u32MosaicCh = u32CurrentCh;
                }

                BackgroundRec[u32ColumnNum] =  TTX_GET_COLOR(stCMBAttr.u8BackColor);
                if (pstCurrentPoint->bFlash && u8LOPFlash && (!TTX_IsSpaceChar(u32CurrentCh)))
                {
                    pstFlashArea = (TTX_FLAAREA_S *)malloc(sizeof(TTX_FLAAREA_S));  /**  Record a flash area except space */
                    if (HI_NULL != pstFlashArea)
                    {
                        pstFlashArea->u8LineNum = (HI_U8) u32LineNum;
                        pstFlashArea->u8ColNum = u32X;
                        pstFlashArea->u8DoubleHeight = stCMBAttr.bDHeight;
                        pstFlashArea->u8DoubleWidth = stCMBAttr.bDWidth;
                        pstFlashArea->u8DoubleSize = bDoubleSize;
                        enCharSet = TTX_Show_GetCharSet(u32CurrentCh, bMosaic);
                        if(bModifiedG0G2 && bEnhanceChar)
                        {
                            enG0Set = enModifiedG0Set;
                            enG2Set = enModifiedG2Set;
                            bEnhanceChar = HI_FALSE;
                        }
                        else
                        {
                            enG0Set = enLOPG0Set;
                            enG2Set = enLOPG2Set;
                        }
                        TTX_Show_SetCharAttr(&(pstFlashArea->stCharAttr), P_CHARACTER(u32CurrentCh), bContiguous, enG0Set, enG2Set,
                                             enCharSet, enNationSet);
                        pstFlashArea->ForegdCol = TTX_GET_COLOR(stCMBAttr.u8ForeColor);
                        pstFlashArea->BackgdCol = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                        pstFlashArea->pstNext = HI_NULL;
                        TTX_ADD_FlashArea(&(pstCurrentPoint->pFlaAreaHead), pstFlashArea);
                    }
                }

                if ((u32Fillback == 1) && (stCMBAttr.bDHeight|| bDoubleSize)) /** Double height or double size , fill  the space of lower line*/
                {
                    if (!pstCurrentPoint->bTtxMix)
                    {
                        for (i = 0; i <= u32X; i++)
                        {
                            s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum + 1, i, 1, 1);
                            stFillRectParam.pstPageArea = &stPageArea;
                            stFillRectParam.u32Color = BackgroundRec[i];
                            s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT,
                                                        (HI_VOID *)&stFillRectParam);
                        }
                    }

                    u32Fillback += 1;
                }

                if ((u32Fillback > 1) && (!stCMBAttr.bDHeight) && (!bDoubleSize))  /** Restore to normal size ,fill the space in the next line  */
                {
                    if (!pstCurrentPoint->bTtxMix)   /** Not mix*/
                    {
                        s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum + 1, u32X, 1, 1);
                        stFillRectParam.pstPageArea = &stPageArea;
                        stFillRectParam.u32Color = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT,
                                                    (HI_VOID *)&stFillRectParam);
                    }
                }

                /*DRCS char*/
                if((0xff != u8CMBDRCSChar) && (0xff != u8CMBDRCSSubPage))
                {
                    if(u8CMBDRCSChar & 0x40)/*normal DRCS*/
                    {
                        pstCurrentPoint->stMOTInfo.stNDRCS.u16PageSubCode = u8CMBDRCSSubPage;
                        pstPage = &pstCurrentPoint->stMOTInfo.stNDRCS;
                    }
                    else
                    {
                        pstCurrentPoint->stMOTInfo.stGDRCS.u16PageSubCode = u8CMBDRCSSubPage;
                        pstPage = &pstCurrentPoint->stMOTInfo.stGDRCS;
                    }
                    if(HI_SUCCESS == TTX_DecodeDRCSPage(pstCurrentPoint, pstPage, u8CMBDRCSChar, &enDRCSMode, u32DRCSColorInfo))
                    {
                        if(TTX_DRCS_MODE_0 == enDRCSMode)
                        {

                            for(i = 0; i < 120; i++)
                            {
                                k= (!(*(u32DRCSColorInfo + i))) ? stCMBAttr.u8ForeColor : stCMBAttr.u8BackColor;
                                *(u32DRCSColorInfo + i) = TTX_GET_COLOR(k);
                            }
                        }
                        /*draw DRCS char*/
                        if (stCMBAttr.bConceal && pstCurrentPoint->bConceal)
                        {
                            if (!pstCurrentPoint->bTtxMix)   /**  Not mix */
                            {
                                u32ColCount = ((stCMBAttr.bDWidth || bDoubleSize) ? 2 : 1);
                                u32RowCount = ((stCMBAttr.bDHeight || bDoubleSize) ? 2 : 1);
                                s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                                stFillRectParam.pstPageArea = &stPageArea;
                                stFillRectParam.u32Color = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT,
                                                            (HI_VOID *)&stFillRectParam);
                            }
                        }
                        else
                        {
                            u32ColCount = ((stCMBAttr.bDWidth || bDoubleSize) ? 2 : 1);
                            u32RowCount = ((stCMBAttr.bDHeight || bDoubleSize) ? 2 : 1);

                            s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                            stDRCSCharParam.pstPageArea   = &stPageArea;
                            if (pstCurrentPoint->bTtxMix)
                            {
                                stDrawCharParam.u32Background = 0x00000000;
                            }
                            else
                            {
                                stDrawCharParam.u32Background = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                            }
                            stDRCSCharParam.pu32DRCSColorInfo = u32DRCSColorInfo;
                            stDRCSCharParam.enDRCSSize = (enDRCSMode < TTX_DRCS_MODE_3) ? HI_UNF_TTX_DRCS_SIZE_NORMAL : HI_UNF_TTX_DRCS_SIZE_SMALL;
                            s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWDRCSCHAR,
                                                        (HI_VOID *)&stDRCSCharParam);
                        }


                    }
                }
                else
                {
                    if (TTX_IsSpaceChar(u32CurrentCh))
                    {
                        u32ColCount = ((stCMBAttr.bDWidth || bDoubleSize) ? 2 : 1);
                        u32RowCount = ((stCMBAttr.bDHeight || bDoubleSize) ? 2 : 1);

                        /** Holdmosaic  , mosaic mode  ,space attribute */
                        if (bMosaic && bHoldMosaic && bSpacingAttr)
                        {
                            TTX_Show_SetCharAttr(&stCharAttr, P_CHARACTER(u32MosaicCh), bContiguous, enG0Set, enG2Set,
                                                 HI_UNF_TTX_CHARSET_G1, 0);
                            stDrawCharParam.pstCharAttr = &stCharAttr;
                            s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                            stDrawCharParam.pstPageArea   = &stPageArea;
                            stDrawCharParam.u32Foreground = TTX_GET_COLOR(stCMBAttr.u8ForeColor);
                            if (pstCurrentPoint->bTtxMix)
                            {
                                stDrawCharParam.u32Background = 0x00000000;
                            }
                            else
                            {
                                stDrawCharParam.u32Background = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                            }

                            s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR,
                                                        (HI_VOID *)&stDrawCharParam);
                        }
                        else
                        {
                            if (!pstCurrentPoint->bTtxMix)
                            {
                                s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                                stFillRectParam.pstPageArea = &stPageArea;
                                stFillRectParam.u32Color = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT,
                                                            (HI_VOID *)&stFillRectParam);
                            }
                        }
                    }
                    else           /** None  space char */
                    {
                        if (stCMBAttr.bConceal && pstCurrentPoint->bConceal)
                        {
                            if (!pstCurrentPoint->bTtxMix)   /**  Not mix */
                            {
                                u32ColCount = ((stCMBAttr.bDWidth || bDoubleSize) ? 2 : 1);
                                u32RowCount = ((stCMBAttr.bDHeight || bDoubleSize) ? 2 : 1);
                                s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                                stFillRectParam.pstPageArea = &stPageArea;
                                stFillRectParam.u32Color = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT,
                                                            (HI_VOID *)&stFillRectParam);
                            }
                        }
                        else
                        {
                            u32ColCount = ((stCMBAttr.bDWidth || bDoubleSize) ? 2 : 1);
                            u32RowCount = ((stCMBAttr.bDHeight || bDoubleSize) ? 2 : 1);
                            enCharSet = TTX_Show_GetCharSet(u32CurrentCh, bMosaic);
                            if(bModifiedG0G2 && bEnhanceChar)
                            {
                                enG0Set = enModifiedG0Set;
                                enG2Set = enModifiedG2Set;
                                bEnhanceChar = HI_FALSE;
                            }
                            else
                            {
                                enG0Set = enLOPG0Set;
                                enG2Set = enLOPG2Set;
                            }
                            TTX_Show_SetCharAttr(&stCharAttr, P_CHARACTER(u32CurrentCh), bContiguous, enG0Set, enG2Set, enCharSet,
                                                 enNationSet);
                            stDrawCharParam.pstCharAttr = &stCharAttr;
                            s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                            stDrawCharParam.pstPageArea   = &stPageArea;
                            stDrawCharParam.u32Foreground = TTX_GET_COLOR(stCMBAttr.u8ForeColor);
                            if (pstCurrentPoint->bTtxMix)
                            {
                                stDrawCharParam.u32Background = 0x00000000;
                            }
                            else
                            {
                                stDrawCharParam.u32Background = TTX_GET_COLOR(stCMBAttr.u8BackColor);
                            }

                            s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR,
                                                        (HI_VOID *)&stDrawCharParam);
                        }
                    }

                    if (P_MARKS(u32CurrentCh))                   /** Diacritical mark */
                    {
                        u32ColCount = ((stCMBAttr.bDWidth || bDoubleSize) ? 2 : 1);
                        u32RowCount = ((stCMBAttr.bDHeight || bDoubleSize) ? 2 : 1);
                        TTX_Show_SetCharAttr(&stCharAttr, P_MARKS(u32CurrentCh) + 0x40, HI_FALSE, enG0Set, enG2Set,
                                             HI_UNF_TTX_CHARSET_G2, 0);
                        stDrawCharParam.pstCharAttr = &stCharAttr;
                        s32Ret |= TTX_Show_SetArea(&stPageArea, u32LineNum, u32X, u32RowCount, u32ColCount);
                        stDrawCharParam.pstPageArea   = &stPageArea;
                        stDrawCharParam.u32Foreground = TTX_GET_COLOR(stCMBAttr.u8ForeColor);
                        stDrawCharParam.u32Background = TTX_GET_COLOR(stCMBAttr.u8ForeColor);
                        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR, (HI_VOID *)&stDrawCharParam);
                    }
                }


            }
        }

        HI_INFO_TTX("\n");/**  Debug */
    }

    if (!bBoxPage)   /**  Not subtitle */
    {
        if (pstCurrentPoint->u8szInputNum[2] != 0x2d)    /**  0x2d, the ASCII of ' -'.  Show page and subpage number */
        {
            if (pstCurrentPoint->stCurPgAddr.u8MagazineNum == 0)
            {
                u32aPageNum[0] = 8 + 0x30;
            }
            else
            {
                u32aPageNum[0] = pstCurrentPoint->stCurPgAddr.u8MagazineNum + 0x30;
            }

            u32aPageNum[1] = pstCurrentPoint->stCurPgAddr.u8PageNum / 16 + 0x30;
            u32aPageNum[2] = pstCurrentPoint->stCurPgAddr.u8PageNum % 16 + 0x30;
            u32aPageNum[3] = 0x2e;
            u32aPageNum[4] = pstCurrentPoint->stCurPgAddr.u16PageSubCode / 10 + 0x30;
            u32aPageNum[5] = pstCurrentPoint->stCurPgAddr.u16PageSubCode % 10 + 0x30;

            /*display the magazine num ,page num and subpage in the start of row 0*/
            for (j = 0; j < 6; j++)
            {
                TTX_Show_SetCharAttr(&stCharAttr, u32aPageNum[j], HI_FALSE, HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN,
                                     HI_UNF_TTX_CHARSET_G0, 0);
                stDrawCharParam.pstCharAttr = &stCharAttr;
                s32Ret |= TTX_Show_SetArea(&stPageArea, 0, j + 1, 1, 1);
                stDrawCharParam.pstPageArea   = &stPageArea;
                stDrawCharParam.u32Foreground = 0xff00ff00;
                if (pstCurrentPoint->bTtxMix)
                {
                    stDrawCharParam.u32Background = 0x00000000;
                }
                else
                {
                    stDrawCharParam.u32Background = 0xff000000;
                }

                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR, (HI_VOID *)&stDrawCharParam);
            }
        }

        /** Add  four navigation key at the bottom of teletext pages */
        if (pstCurrentPoint->bNavigation)
        {
            if (!pstCurrentPoint->bTtxMix)
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, TTX_ROW_NUM, 1, 1, u32MaxColNum / 4);
                stFillRectParam.pstPageArea = &stPageArea;
                stFillRectParam.u32Color = s_ColorSet[1];    /** Red key */
                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
                stPageArea.u32Column = 1 + 1 * u32MaxColNum / 4;
                stFillRectParam.u32Color = s_ColorSet[2];   /** Green  key */
                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
                stPageArea.u32Column = 1 + 2 * u32MaxColNum / 4;
                stFillRectParam.u32Color = s_ColorSet[3];   /** Yellow key */
                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
                stPageArea.u32Column = 1 + 3 * u32MaxColNum / 4;
                stPageArea.u32ColumnCount = (u32MaxColNum / 4 - 1);
                stFillRectParam.u32Color = s_ColorSet[6];   /** Cyan key */
                s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);
            }

            for (i = 0; i < 4; i++)      /** Add  the page address of navigation key */
            {
                if (pstCurrentPoint->astLink27[i].u8MagazineNum == 0)
                {
                    u32aPageNum[0] = 8 + 0x30;
                }
                else
                {
                    u32aPageNum[0] = pstCurrentPoint->astLink27[i].u8MagazineNum + 0x30;
                }

                u32aPageNum[1] = pstCurrentPoint->astLink27[i].u8PageNum / 16 + 0x30;
                u32aPageNum[2] = pstCurrentPoint->astLink27[i].u8PageNum % 16 + 0x30;

                for (j = 0; j < 3; j++)
                {
                    TTX_Show_SetCharAttr(&stCharAttr, u32aPageNum[j], HI_FALSE, HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN,
                                         HI_UNF_TTX_CHARSET_G0, 0);
                    stDrawCharParam.pstCharAttr = &stCharAttr;
                    s32Ret |= TTX_Show_SetArea(&stPageArea, TTX_ROW_NUM, 4 + i * u32MaxColNum / 4 + j, 1, 1);
                    stDrawCharParam.pstPageArea   = &stPageArea;
                    stDrawCharParam.u32Foreground = s_ColorSet[4];
                    stDrawCharParam.u32Background = s_ColorSet[7];
                    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR,
                                                (HI_VOID *)&stDrawCharParam);
                }
            }
        }
    }

    if (bBoxPage)
    {
        if (pstCurrentPoint->bNavigation)
        {
            s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR,
                                       u32MaxColNum);
        }
        else
        {
            s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32MaxColNum);
        }

        stRefrshLayerParam.pstPageArea = &stPageArea;
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);
    }
    else
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, 1, 32);
        stRefrshLayerParam.pstPageArea = &stPageArea;
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);

        if (pstCurrentPoint->bNavigation)
        {
            if (u8NumOfSubPg > 0)/** Have subpage,don't refresh and just refresh by updatetask  */
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, 1, 0, TTX_ROW_NUM, u32MaxColNum);
            }
            else
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, 1, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32MaxColNum);
            }
        }
        else
        {
            if (u8NumOfSubPg > 0)
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, 1, 0, TTX_ROW_NUM - 1, u32MaxColNum);
            }
            else
            {
                s32Ret |= TTX_Show_SetArea(&stPageArea, 1, 0, TTX_ROW_NUM, u32MaxColNum);
            }
        }

        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_TTX("TTX_DecShowPage, Errors occur while call functions\n");
    }
}

HI_VOID TTX_Show_ShowPage(TTX_PAGE_CONTEXT_S  *  pstContextHead)
{
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;

    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return;
    }

    TTX_SHOWPAGE_LOCK();
    if(HI_TRUE == pstCurrentPoint->bTTXSearching)
    {
        pstCurrentPoint->bTTXSearching = HI_FALSE;
    }
    if (!pstCurrentPoint->bTtxHiden)
    {
        TTX_DecShowPage(pstCurrentPoint);
    }

    pstCurrentPoint->bProcessed = HI_TRUE;
    TTX_SHOWPAGE_UNLOCK();
}

HI_S32  TTX_Show_SetArea(HI_UNF_TTX_PAGEAREA_S * pstPageArea, HI_U32 u32Row, HI_U32 u32Colunm, HI_U32 u32RowCount,
                         HI_U32 u32ColCount)
{
    if (HI_NULL == pstPageArea)
    {
        return HI_FAILURE;
    }

    pstPageArea->u32Row = u32Row;
    pstPageArea->u32Column   = u32Colunm;
    pstPageArea->u32RowCount = u32RowCount;
    pstPageArea->u32ColumnCount = u32ColCount;

    return HI_SUCCESS;
}

HI_VOID   TTX_Show_SetCharAttr(HI_UNF_TTX_CHARATTR_S * pstCharAttr, HI_U32 u32Index,
                                      HI_BOOL bContiguous, HI_UNF_TTX_G0SET_E enG0Set, HI_UNF_TTX_G2SET_E enG2Set,
                                      HI_UNF_TTX_CHARSET_E enCharSet, HI_U8 u8NationSet)

{
    if (HI_NULL == pstCharAttr)
    {
        return;
    }

    pstCharAttr->u32Index = u32Index;
    pstCharAttr->bContiguous = bContiguous;
    pstCharAttr->enG0Set     = enG0Set;
    pstCharAttr->enG2Set     = enG2Set;
    pstCharAttr->enCharSet   = enCharSet;
    pstCharAttr->u8NationSet = u8NationSet;
    return;
}

HI_UNF_TTX_CHARSET_E    TTX_Show_GetCharSet(HI_U32 u32Index, HI_BOOL bMosMod)
{
    HI_UNF_TTX_CHARSET_E enCharSet = HI_UNF_TTX_CHARSET_G0;
    HI_U32 u32Char = u32Index;

    if (u32Index < 0x20)
    {
        return enCharSet;
    }

    if (P_ADDITION(u32Char))   /** The char specify  by packet 26 */
    {
        switch (P_GCODE(u32Char))
        {
        case 0:                              /** G0 char  */
            enCharSet = HI_UNF_TTX_CHARSET_G0;
            break;
        case 1:                         /** G1 char  */
            u32Char = P_CHARACTER(u32Char) - 32;
            if ((u32Char < 32) || (u32Char >= 64))
            {
                enCharSet = HI_UNF_TTX_CHARSET_G1;
            }
            else
            {
                enCharSet = HI_UNF_TTX_CHARSET_G0;
            }

            break;
        case 2:                      /** G2 char */
            enCharSet = HI_UNF_TTX_CHARSET_G2;
            break;
        case 3:                    /** G3 char */
            enCharSet = HI_UNF_TTX_CHARSET_G3;
            break;
        default:
            enCharSet = HI_UNF_TTX_CHARSET_G0;
            break;
        }
    }
    else
    {
        u32Char = P_CHARACTER(u32Char) - 32;   /** Visible char  begin with 0x20*/

        if (bMosMod)     /** Mosaic char  */
        {
            if ((u32Char < 32) || (u32Char >= 64))
            {
                enCharSet = HI_UNF_TTX_CHARSET_G1;
            }
            else
            {
                enCharSet = HI_UNF_TTX_CHARSET_G0;
            }
        }
        else
        {
            enCharSet = HI_UNF_TTX_CHARSET_G0;
        }
    }

    return enCharSet;
}


HI_VOID TTX_Show_GetLOPG0G2AndNationSet(TTX_PAGE_CONTEXT_S*  pstContextHead, HI_BOOL bUseDefaultCharSet, HI_UNF_TTX_G0SET_E* penG0Set, HI_UNF_TTX_G2SET_E* penG2Set, HI_UNF_TTX_NATION_SET_E* penNationSet)
{
    HI_U8 u8MagNum;
    HI_U8 u8DefG0G2;
    HI_U8 u8SecG0;
    HI_U8 i;
    HI_U32 u32MaxLanNum;
    HI_UNF_TTX_G0SET_E enDefG0Set = HI_UNF_TTX_G0SET_BUTT;
    HI_UNF_TTX_G0SET_E enSecG0Set = HI_UNF_TTX_G0SET_BUTT;
    HI_UNF_TTX_G2SET_E enG2Set = HI_UNF_TTX_G2SET_BUTT;
    HI_UNF_TTX_NATION_SET_E enDefNationSet = HI_UNF_TTX_NATION_SET_BUTT;
    HI_UNF_TTX_NATION_SET_E enSecNationSet = HI_UNF_TTX_NATION_SET_BUTT;
    TTX_DEF_G0G2_S* pstDefG0G2 = HI_NULL;
    TTX_SEC_G0_S* pstSecG0 = HI_NULL;
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;
    u8MagNum = pstCurrentPoint->stCurPgAddr.u8MagazineNum & 0x7;


    /*if has defined the G0,G2,nation set by enhancement packet*/
    if((HI_TRUE == pstCurrentPoint->bHasP28_0) ||(HI_TRUE == pstCurrentPoint->bHasP28_4) || (HI_TRUE == g_bHasM29_0[u8MagNum]) || (HI_TRUE == g_bHasM29_4[u8MagNum]))
    {
        u8DefG0G2 = pstCurrentPoint->stP28_0_Info.u8DefG0G2;
        u8SecG0 = pstCurrentPoint->stP28_0_Info.u82ndG0;
        switch((u8DefG0G2 >> 3) & 0xf)
        {
            case 0:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map0000;
                break;
            case 1:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map0001;
                break;
            case 2:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map0010;
                break;
            case 3:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map0011;
                break;
            case 4:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map0100;
                break;
            case 6:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map0110;
                break;
            case 8:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map1000;
                break;
            case 0xa:
                pstDefG0G2 = (TTX_DEF_G0G2_S*)g_stDefG0G2Map1010;
                break;
            default:
                break;
        }
        if(HI_NULL != pstDefG0G2)
        {
            i = u8DefG0G2 & 0x7;
            pstDefG0G2 += i;
            enDefG0Set = pstDefG0G2->enG0Set;
            enG2Set = pstDefG0G2->enG2Set;
            enDefNationSet = pstDefG0G2->enNationSet;
        }

        switch((u8SecG0 >> 3) & 0xf)
        {
            case 0:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map0000;
                break;
            case 1:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map0001;
                break;
            case 2:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map0010;
                break;
            case 3:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map0011;
                break;
            case 4:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map0100;
                break;
            case 6:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map0110;
                break;
            case 8:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map1000;
                break;
            case 0xa:
                pstSecG0 = (TTX_SEC_G0_S*)g_stSecG0Map1010;
                break;
            default:
                break;
        }
        if(HI_NULL != pstSecG0)
        {
            i = u8SecG0 & 0x7;
            pstSecG0 += i;
            enSecG0Set = pstSecG0->enG0Set;
            enSecNationSet = pstSecG0->enNationSet;
        }

        if(HI_TRUE == bUseDefaultCharSet)
        {
            *penG0Set = enDefG0Set;
            *penNationSet = enDefNationSet;
        }
        else
        {
            *penG0Set = enSecG0Set;
            *penNationSet = enSecNationSet;
        }
        *penG2Set = enG2Set;
    }
    else
    {
        u32MaxLanNum = sizeof(g_stLanguageCode)/sizeof(TTX_LANGUAGE_S);
        for(i = 0; i < u32MaxLanNum; i++)
        {
            if((pstCurrentPoint->u8Language[0] == g_stLanguageCode[i].u8LanguageCode[0])\
                && (pstCurrentPoint->u8Language[1] == g_stLanguageCode[i].u8LanguageCode[1])\
                && (pstCurrentPoint->u8Language[2] == g_stLanguageCode[i].u8LanguageCode[2]))
            {
                *penNationSet = g_stLanguageCode[i].enNationSet;
                *penG0Set = g_stLanguageCode[i].enG0Set;
                *penG2Set = g_stLanguageCode[i].enG2Set;
                break;
            }
        }

        if(i >= u32MaxLanNum)
        {
            i = (pstCurrentPoint->u32Flag >> 8) & 0x07; /** National char set */
            *penNationSet = g_stDefG0G2Map0010[i].enNationSet;
             /*set char set to default value*/
            *penG0Set = HI_UNF_TTX_G0SET_LATIN;
            *penG2Set = HI_UNF_TTX_G2SET_LATIN;
        }
        else
        {
             /*no found  X/28/0, X/28/4,M/29/0,M/29/4 conditon,need change charset,use default charset*/
            if(HI_FALSE == bUseDefaultCharSet)
            {
                *penG0Set = HI_UNF_TTX_G0SET_LATIN;
                *penG2Set = HI_UNF_TTX_G2SET_LATIN;
                *penNationSet = HI_UNF_TTX_NATION_SET_PRIMARY;
            }
        }
    }

    *penG0Set  = (HI_UNF_TTX_G0SET_BUTT == *penG0Set)? HI_UNF_TTX_G0SET_LATIN:*penG0Set;
    *penG2Set  = (HI_UNF_TTX_G2SET_BUTT == *penG2Set)? HI_UNF_TTX_G2SET_LATIN:*penG2Set;
    *penNationSet = (HI_UNF_TTX_NATION_SET_BUTT == *penNationSet)?HI_UNF_TTX_NATION_SET_PRIMARY:*penNationSet;

    return;
}

HI_VOID TTX_Show_GetModifiedG0G2(HI_U8 u8ModifiedValue, HI_UNF_TTX_G0SET_E* penG0Set, HI_UNF_TTX_G2SET_E* penG2Set)
{
    HI_U32 i;
    TTX_MODIFIED_G0G2_S* pstModifiedG0G2 = HI_NULL;
    i = (u8ModifiedValue >> 3) & 0xf;
    switch(i)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            pstModifiedG0G2 = (TTX_MODIFIED_G0G2_S*)g_stModifiedG0G2Map00XX;
            break;
        case 4:
            pstModifiedG0G2 = (TTX_MODIFIED_G0G2_S*)g_stModifiedG0G2Map0100;
            break;
        case 6:
            pstModifiedG0G2 = (TTX_MODIFIED_G0G2_S*)g_stModifiedG0G2Map0110;
            break;
        case 8:
            pstModifiedG0G2 = (TTX_MODIFIED_G0G2_S*)g_stModifiedG0G2Map1000;
            break;
        case 0xa:
            pstModifiedG0G2 = (TTX_MODIFIED_G0G2_S*)g_stModifiedG0G2Map1010;
            break;
        default:
            break;
    }
    if (HI_NULL != pstModifiedG0G2)
    {
        i = u8ModifiedValue & 0x7;
        *penG0Set = pstModifiedG0G2[i].enG0Set;
        *penG2Set = pstModifiedG0G2[i].enG2Set;
    }
    else
    {
        *penG0Set = HI_UNF_TTX_G0SET_LATIN;
        *penG2Set = HI_UNF_TTX_G2SET_LATIN;
    }
    return;
}

HI_S32 TTX_Show_SetOSDOutput_ON(TTX_PAGE_CONTEXT_S * pstContextHead)
{
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;

    if (HI_NULL == pstCurrentPoint)        /** Invalid param, just return */
    {
        return HI_FAILURE;
    }

    TTX_SHOWPAGE_LOCK();

    pstCurrentPoint->bTtxHiden = HI_FALSE;

    TTX_SHOWPAGE_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 TTX_Show_SetOSDOutput_OFF(TTX_PAGE_CONTEXT_S * pstContextHead)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_TTX_FILLRECT_S stFillRectParam;
    HI_UNF_TTX_REFRESHLAYER_S stRefrshLayerParam;
    HI_UNF_TTX_PAGEAREA_S stPageArea;
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;

    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return HI_FAILURE;
    }

    TTX_SHOWPAGE_LOCK();

    pstCurrentPoint->bTtxHiden   = HI_TRUE;
    pstCurrentPoint->bUpdateTime = HI_FALSE;

    if (pstCurrentPoint->bNavigation)
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR,
                                   pstCurrentPoint->u32ColumnNum);
    }
    else
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, pstCurrentPoint->u32ColumnNum);
    }

    stFillRectParam.pstPageArea = &stPageArea;
    stFillRectParam.u32Color = 0x00000000;
    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);

    stRefrshLayerParam.pstPageArea = &stPageArea;
    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);

   TTX_SHOWPAGE_UNLOCK();

    return s32Ret;
}

/**  Enable  or disalbe the output */
HI_S32 TTX_Show_SetOSDOutputMsg(TTX_PAGE_CONTEXT_S * pstContextHead, HI_BOOL bEnable)
{
    HI_S32 s32Ret;
    TTX_MSG_ACTION_E enMsgAction;
    HI_HANDLE hDispalyHandle;

    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;

    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return HI_FAILURE;
    }

    if (bEnable)
    {
        enMsgAction = TTX_MSG_ACTION_OSDOUTPUT_ON;
    }
    else
    {
        enMsgAction = TTX_MSG_ACTION_OSDOUTPUT_OFF;
    }

    hDispalyHandle = 0x7f7f0000 | enMsgAction;
    s32Ret = TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_TTX_TO_APP_MSG, (HI_VOID *) &hDispalyHandle);

    return s32Ret;
}

HI_VOID    TTX_Show_ShowPrompt(TTX_PAGE_CONTEXT_S * pstContextHead)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 i = 0, j = 0;
    HI_UNF_TTX_CHARATTR_S stCharAttr;
    HI_UNF_TTX_DRAWCAHR_S stDrawCharParam;
    HI_UNF_TTX_FILLRECT_S stFillRectParam;
    HI_UNF_TTX_REFRESHLAYER_S stRefrshLayerParam;
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = HI_NULL;
    HI_UNF_TTX_PAGEAREA_S stPageArea;
    HI_U8 u8szPrompt[22] = {0x54, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x78, 0x74, 0x20,
                            0x53, 0x65, 0x61, 0x72, 0x63, 0x68, 0x69, 0x6e, 0x67, 0x2e, 0x2e, 0x2e, 0};/** Teletext Searching... */
    HI_U32 u32ColNum;

    pstCurrentPoint = pstContextHead;
    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return;
    }

    TTX_SHOWPAGE_LOCK();

    if (pstCurrentPoint->bTtxHiden)
    {
        TTX_SHOWPAGE_UNLOCK();

        return;
    }

    u32ColNum = pstCurrentPoint->u32ColumnNum;
    if (pstCurrentPoint->bNavigation)
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR, u32ColNum);
    }
    else
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32ColNum);
    }

    stFillRectParam.pstPageArea = &stPageArea;
    stFillRectParam.u32Color = 0xff000000;
    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);

    for (i = 0, j = 9; i < 21; i++, j++)
    {
        TTX_Show_SetCharAttr(&stCharAttr, u8szPrompt[i], HI_FALSE, HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN,HI_UNF_TTX_CHARSET_G0, 0);
        stDrawCharParam.pstCharAttr = &stCharAttr;
        s32Ret |= TTX_Show_SetArea(&stPageArea, 13, j, 1, 1);
        stDrawCharParam.pstPageArea   = &stPageArea;
        stDrawCharParam.u32Foreground = s_ColorSet[3];
        stDrawCharParam.u32Background = s_ColorSet[0];
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR, (HI_VOID *)&stDrawCharParam);
    }

    if (pstCurrentPoint->bNavigation)
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR, u32ColNum);
    }
    else
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32ColNum);
    }

    stRefrshLayerParam.pstPageArea = &stPageArea;
    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);

    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_TTX("TTX_Show_ShowPrompt, Errors occur while call functions\n");
    }
    pstCurrentPoint->bTTXSearching = HI_TRUE;
    TTX_SHOWPAGE_UNLOCK();
}

HI_VOID  TTX_ShowPromptMsg(TTX_PAGE_CONTEXT_S * pstContextHead)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TTX_MSG_ACTION_E enMsgAction;
    HI_HANDLE hDispalyHandle;
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;

    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return;
    }

    enMsgAction = TTX_MSG_ACTION_SHOWPROMPT_SEARCH;
    hDispalyHandle = 0x7f7f0000 | enMsgAction;
    s32Ret = TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_TTX_TO_APP_MSG, (HI_VOID *) &hDispalyHandle);

    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_TTX("TTX_ShowPromptMsg, Errors occur while call functions\n");
    }
}

HI_VOID    TTX_Show_ShowPromptTimeOut(TTX_PAGE_CONTEXT_S * pstContextHead)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 i = 0, j = 0;
    HI_UNF_TTX_CHARATTR_S stCharAttr;
    HI_UNF_TTX_DRAWCAHR_S stDrawCharParam;
    HI_UNF_TTX_FILLRECT_S stFillRectParam;
    HI_UNF_TTX_REFRESHLAYER_S stRefrshLayerParam;
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = HI_NULL;
    HI_UNF_TTX_PAGEAREA_S stPageArea;
    HI_U8 u8szPrompt[26] = {0x54, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x78, 0x74, 0x20,
                            0x49, 0x73, 0x20, 0x4e, 0x6f, 0x74, 0x20, 0x41, 0x76, 0x61, 0x69, 0x6c, 0x61,0x62, 0x6c, 0x65, 0};/** Teletext Is Not Available */
    HI_U32 u32ColNum;

    pstCurrentPoint = pstContextHead;
    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return;
    }

    TTX_SHOWPAGE_LOCK();

    if (pstCurrentPoint->bTtxHiden)
    {
        TTX_SHOWPAGE_UNLOCK();
        return;
    }

    u32ColNum = pstCurrentPoint->u32ColumnNum;
    if (pstCurrentPoint->bNavigation)
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR, u32ColNum);
    }
    else
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32ColNum);
    }

    stFillRectParam.pstPageArea = &stPageArea;
    stFillRectParam.u32Color = 0xff000000;
    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_FILLRECT, (HI_VOID *)&stFillRectParam);

    for (i = 0, j = 9; i < 25; i++, j++)
    {
        TTX_Show_SetCharAttr(&stCharAttr, u8szPrompt[i], HI_FALSE, HI_UNF_TTX_G0SET_LATIN, HI_UNF_TTX_G2SET_LATIN,HI_UNF_TTX_CHARSET_G0, 0);
        stDrawCharParam.pstCharAttr = &stCharAttr;
        s32Ret |= TTX_Show_SetArea(&stPageArea, 13, j, 1, 1);
        stDrawCharParam.pstPageArea   = &stPageArea;
        stDrawCharParam.u32Foreground = s_ColorSet[3];
        stDrawCharParam.u32Background = s_ColorSet[0];
        s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_DRAWCHAR, (HI_VOID *)&stDrawCharParam);
    }

    if (pstCurrentPoint->bNavigation)
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_NAVIGATION_BAR + TTX_SUBPAGE_BAR, u32ColNum);
    }
    else
    {
        s32Ret |= TTX_Show_SetArea(&stPageArea, 0, 0, TTX_ROW_NUM + TTX_SUBPAGE_BAR, u32ColNum);
    }

    stRefrshLayerParam.pstPageArea = &stPageArea;
    s32Ret |= TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_APP_REFRESH, (HI_VOID *)&stRefrshLayerParam);

    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_TTX("TTX_Show_ShowPromptTimeOut, Errors occur while call functions\n");
    }
    pstCurrentPoint->bTTXSearching = HI_FALSE;
    TTX_SHOWPAGE_UNLOCK();
}

HI_VOID  TTX_ShowPromptTimeOutMsg(TTX_PAGE_CONTEXT_S * pstContextHead)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TTX_MSG_ACTION_E enMsgAction;
    HI_HANDLE hDispalyHandle;
    TTX_PAGE_CONTEXT_S  * pstCurrentPoint = pstContextHead;

    if (HI_NULL == pstCurrentPoint)    /** Invalid param, just return */
    {
        return;
    }

    enMsgAction = TTX_MSG_ACTION_SHOWPROMPT_SEARCH_TIMEOUT;
    hDispalyHandle = 0x7f7f0000 | enMsgAction;
    s32Ret = TTX_Show_CallBack(pstCurrentPoint, HI_UNF_TTX_CB_TTX_TO_APP_MSG, (HI_VOID *) &hDispalyHandle);

    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_TTX("TTX_ShowPromptTimeOutMsg, Errors occur while call functions\n");
    }
}
HI_S32 TTX_Show_CallBack(TTX_PAGE_CONTEXT_S *pstContextHead, HI_UNF_TTX_CB_E enCBType, HI_VOID *pvParam)
{
    TTX_PAGE_CONTEXT_S *  pstCurrentPoint = pstContextHead;

    if ((HI_NULL == pstCurrentPoint) || (HI_NULL == pstCurrentPoint->pfnCallBackFunction))
    {
        return HI_FAILURE;
    }
    return pstCurrentPoint->pfnCallBackFunction( pstCurrentPoint->hTTX, enCBType, pvParam);
}
