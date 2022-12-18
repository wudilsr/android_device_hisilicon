/* ====================================================================
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied.

* Author: y00226912
* Date:    18.03.2013
*
* ==================================================================== */

#include <dlfcn.h>   /* For dynamic loading */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>

#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_VideoExt.h"
#include "OMX_RoleNames.h"

#ifdef ANDROID
#include<utils/Log.h>
#else
#define ALOGD printf  
#define ALOGE printf
#endif

#undef LOG_TAG
#define LOG_TAG "HIOMX_CORE"

#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINT			          ALOGD
#else
#define DEBUG_PRINT
#endif

#define DEBUG_PRINT_ERROR	          ALOGE
#define DEBUG_PRINT_ALWS	          ALOGE


#define DYNAMIC_LOAD
#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))

/* macros */
#define MAX_COMP_NUM                       (3)   // total component num
#define MAX_COMP_INSTANCES                 (32)  // total instances of one component
#define MAX_ROLE_NUM                       (40)  // total roles of all component
#define MAX_COMP_NAME_LEN                  (50)  // max len of one component name
#define MAX_INSTANCES         (MAX_COMP_NUM * MAX_COMP_INSTANCES) // total instances of all components

/* limit the number of max occuring instances of same component,
   tune this if you like */
typedef struct _ComponentTable {

	OMX_STRING name;
	OMX_U16 nRoles;
	OMX_STRING pRoleArray[MAX_ROLE_NUM];
	OMX_HANDLETYPE* pHandle[MAX_COMP_INSTANCES];
	OMX_S32 refCount;

}ComponentTable;


/******************************vars******************************/

static OMX_U32         g_InitCount = 0;
static pthread_mutex_t g_Mutex = PTHREAD_MUTEX_INITIALIZER;

static ComponentTable  g_ComponentTable[MAX_COMP_NUM];
static OMX_U32         g_TableCount = 0;

static OMX_PTR         pModules[MAX_INSTANCES] = {0};
static OMX_PTR         pComponents[COUNTOF(pModules)] = {0};

/* CodecType Relative */
static char *tComponentName[MAX_ROLE_NUM][2] = {
    
	/*video encoder components */
    {OMX_VENC_COMPONENT_NAME,  OMX_ROLE_VIDEO_ENCODER_AVC},
        
	/*video decoder components */
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_AVC},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_VC1},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MPEG1},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MPEG2},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MPEG4},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_H263},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_DIVX3},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_VP8},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_VP6},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_WMV},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_AVS},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_SORENSON},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_HEVC},
	{OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MVC},

  #if (defined(REAL8_SUPPORT) || defined(REAL9_SUPPORT))
    /* For copyright, vfmw didn't support std real. */
    {OMX_VDEC_NORMAL_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_RV},
  #endif
  
    /*secure video decoder components */
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_AVC},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_VC1},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MPEG1},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MPEG2},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_MPEG4},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_DIVX3},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_VP8},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_VP6},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_WMV},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_AVS},
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_HEVC},
        
  #if (defined(REAL8_SUPPORT) || defined(REAL9_SUPPORT))
    /* For copyright, vfmw didn't support std real. */
    {OMX_VDEC_SECURE_COMPONENT_NAME,  OMX_ROLE_VIDEO_DECODER_RV},
  #endif  

	/* terminate the table */
	{NULL, NULL},
	
};

/****************************** FUNCTIONS ******************************/

static OMX_ERRORTYPE OMX_BuildComponentTable()
{
	OMX_U32 i = 0;
	OMX_U32 j = 0;
	OMX_U32 CurRoleNum = 0;
	OMX_CALLBACKTYPE sCallbacks;
	OMX_ERRORTYPE    eError = OMX_ErrorNone;

    memset(&g_ComponentTable, 0, MAX_COMP_NUM*sizeof(ComponentTable));
    
	for (i = 0, CurRoleNum = 0; i < MAX_ROLE_NUM; i ++)
	{
		if (tComponentName[i][0] == NULL)
        {      
		    break;
        }

		if (CurRoleNum < MAX_COMP_NUM)
		{
		    for (j = 0; j < CurRoleNum; j ++)
		    {
		        if (!strcmp(g_ComponentTable[j].name, tComponentName[i][0]))
			    {
		            /* insert the role */
		            if (tComponentName[i][1] != NULL)
		            {
		                g_ComponentTable[j].pRoleArray[g_ComponentTable[j].nRoles] = tComponentName[i][1];
		                g_ComponentTable[j].pHandle[g_ComponentTable[j].nRoles] = NULL; //initialize the pHandle element
		                g_ComponentTable[j].nRoles++;
		            }
		            break;
		        }
		    }

		    if (j == CurRoleNum)
		    {
			    /* new component */
		        if (tComponentName[i][1] != NULL)
			    {
		            g_ComponentTable[CurRoleNum].pRoleArray[0] = tComponentName[i][1];
		            g_ComponentTable[CurRoleNum].nRoles = 1;
		        }

		        g_ComponentTable[CurRoleNum].name = tComponentName[i][0];
		        g_ComponentTable[CurRoleNum].refCount = 0; //initialize reference counter.
		        CurRoleNum++;
		    }
		}
	}

	g_TableCount = CurRoleNum;

	return eError;
}


/******************************Public*Routine******************************\
* OMX_Init()
*
* Description:This method will initialize the OMX Core.  It is the
* responsibility of the application to call OMX_Init to ensure the proper
* set up of core resources.
*
* Returns:    OMX_NOERROR          Successful
*
* Note
*
\************************************************************************/
OMX_ERRORTYPE OMX_Init()
{
	OMX_ERRORTYPE eError = OMX_ErrorNone;

	DEBUG_PRINT("%s :: enter!\n", __func__);

	if(pthread_mutex_lock(&g_Mutex) != 0)
	{
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n",__func__);
		return OMX_ErrorUndefined;
	}

	g_InitCount++;

	if (g_InitCount == 1)
	{
		eError = OMX_BuildComponentTable();
	}

	if(pthread_mutex_unlock(&g_Mutex) != 0)
	{
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n",__func__);
		return OMX_ErrorUndefined;
	}

	DEBUG_PRINT("%s :: exit!\n", __func__);
	return eError;
}


/******************************Public*Routine******************************\
* OMX_GetHandle
*
* Description: This method will create the handle of the COMPONENTTYPE
* If the component is currently loaded, this method will reutrn the
* hadle of existingcomponent or create a new instance of the component.
* It will call the OMX_ComponentInit function and then the setcallback
* method to initialize the callback functions
* Parameters:
* @param[out] pHandle            Handle of the loaded components
* @param[in] cComponentName     Name of the component to load
* @param[in] pAppData           Used to identify the callbacks of component
* @param[in] pCallBacks         Application callbacks
*
* @retval OMX_ErrorUndefined
* @retval OMX_ErrorInvalidComponentName
* @retval OMX_ErrorInvalidComponent
* @retval OMX_ErrorInsufficientResources
* @retval OMX_NOERROR                      Successful
*
* Note
*
\**************************************************************************/

OMX_ERRORTYPE OMX_GetHandle( 
           OMX_HANDLETYPE* pHandle, 
           OMX_STRING cComponentName, 
           OMX_PTR pAppData, 
           OMX_CALLBACKTYPE* pCallBacks)
{
	static const char prefix[] = "lib";
	static const char postfix[] = ".so";

	OMX_ERRORTYPE (*pComponentInit)(OMX_HANDLETYPE, OMX_STRING);
	OMX_ERRORTYPE err = OMX_ErrorNone;
	OMX_COMPONENTTYPE *componentType;
	OMX_U32 refIndex = 0;

	OMX_U32 i = 0;

	DEBUG_PRINT("%s :: enter!\n", __func__);
	DEBUG_PRINT("%s :: component name:%s !\n", __func__, cComponentName);

	if(pthread_mutex_lock(&g_Mutex) != 0)
	{
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n",__func__);
		return OMX_ErrorUndefined;
	}

	if ((NULL == cComponentName) || (NULL == pHandle) || (NULL == pCallBacks))
	{
		err = OMX_ErrorBadParameter;
		DEBUG_PRINT_ERROR("%s :: invalid param!\n", __func__);
		goto UNLOCK_MUTEX;
	}

	/* Verify that the name is not too long and could cause a crash.  Notice
	* that the comparison is a greater than or equals.  This is to make
	* sure that there is room for the terminating NULL at the end of the
	* name. */

	if(strlen(cComponentName) >= MAX_COMP_NAME_LEN)
	{
		err = OMX_ErrorInvalidComponentName;
		DEBUG_PRINT_ERROR("%s :: invalid component name!\n", __func__);
		goto UNLOCK_MUTEX;
	}

	/* Locate the first empty slot for a component.  If no slots
	* are available, error out */
	for(i = 0; i < COUNTOF(pModules); i++)
	{
		if(pModules[i] == NULL)
        {      
			break;
        }
	}

	if(i >= COUNTOF(pModules))
	{
		err = OMX_ErrorInsufficientResources;
		DEBUG_PRINT_ERROR("%s :: modules load too much!\n", __func__);
		goto UNLOCK_MUTEX;
	}

	for (refIndex = 0; refIndex < MAX_COMP_NUM; refIndex++)
	{
		char buf[sizeof(prefix) + MAX_COMP_NAME_LEN + sizeof(postfix)];

		//get the index for the component in the table
		if (strcmp(g_ComponentTable[refIndex].name, cComponentName) != 0)
        {      
			continue;
        }

		/* check if the component is already loaded */
		if (g_ComponentTable[refIndex].refCount >= MAX_COMP_INSTANCES)
		{
			err = OMX_ErrorInsufficientResources;
			DEBUG_PRINT_ERROR("%s :: Max instances of component %s already created.\n", __func__, cComponentName);
			goto UNLOCK_MUTEX;
		}

		/* load the component and check for an error.  If filename is not an
		* absolute path (i.e., it does not  begin with a "/"), then the
		* file is searched for in the following locations:
		*
		*     The LD_LIBRARY_PATH environment variable locations
		*     The library cache, /etc/ld.so.cache.
		*     /lib
		*     /usr/lib
		*
		* If there is an error, we can't go on, so set the error code and exit */

		/* the lengths are defined herein or have been
		* checked already, so strcpy and strcat are
		* are safe to use in this context. */
		strncpy(buf, prefix, sizeof(prefix));
		strncat(buf, cComponentName, strlen(cComponentName));
		strncat(buf, postfix, sizeof(postfix));

		DEBUG_PRINT("%s :: prepare to load  %s\n", __func__, buf);

#ifdef DYNAMIC_LOAD
		pModules[i] = dlopen(buf, RTLD_LAZY | RTLD_GLOBAL);
		if( pModules[i] == NULL )
		{
			DEBUG_PRINT_ERROR("%s :: dlopen %s failed because %s\n", __func__, buf, dlerror());
			err = OMX_ErrorComponentNotFound;
			goto UNLOCK_MUTEX;
		}
		const char *pErr = dlerror();
		if (pErr != NULL)
		{
			DEBUG_PRINT_ERROR("%s:: dlopen failed :%s\n", __func__, pErr);
		}

		/* Get a function pointer to the "OMX_ComponentInit" function.  If
		* there is an error, we can't go on, so set the error code and exit */
		pComponentInit = dlsym(pModules[i], "component_init");
		pErr = dlerror();
		if (pErr != NULL)
		{
			DEBUG_PRINT_ERROR("dlsym error:%s\n", pErr);
		}
		if (pComponentInit == NULL)
		{
			DEBUG_PRINT_ERROR("%s:: dlsym failed for module %p\n", __func__, pModules[i]);
			err = OMX_ErrorComponentNotFound;
			goto CLEAN_UP;
		}
#else
		extern OMX_ERRORTYPE component_init(OMX_HANDLETYPE, OMX_STRING);
		pComponentInit = OMX_ComponentInit;
#endif

		DEBUG_PRINT("%s :: load  %s ok\n", __func__, buf);

		*pHandle = malloc(sizeof(OMX_COMPONENTTYPE));
		if(*pHandle == NULL)
		{
			err = OMX_ErrorInsufficientResources;
			DEBUG_PRINT_ERROR("%s:: malloc of pHandle* failed\n", __func__);
			goto CLEAN_UP;
		}

		/* We now can access the dll.  So, we need to call the "OMX_ComponentInit"
		 * method to load up the "handle" (which is just a list of functions to
		 * call) and we should be all set.*/
		pComponents[i] = *pHandle;
		componentType = (OMX_COMPONENTTYPE*) *pHandle;
		componentType->nSize = sizeof(OMX_COMPONENTTYPE);
		err = (*pComponentInit)(*pHandle, cComponentName);
		if (err != OMX_ErrorNone)
		{
			DEBUG_PRINT_ERROR("%s :: OMX_ComponentInit failed 0x%08x\n", __func__, err);
			goto CLEAN_UP;
		}

		err = (componentType->SetCallbacks)(*pHandle, pCallBacks, pAppData);
		if (err != OMX_ErrorNone)
		{
			DEBUG_PRINT_ERROR("%s :: Core: SetCallBack failed %d\n", __func__, err);
			goto CLEAN_UP;
		}

		/* finally, OMX_ComponentInit() was successful and
		   SetCallbacks was successful, we have a valid instance,
		   so now we increase refCount */
        for(i = 0; i < MAX_COMP_INSTANCES; i++)
        {
            if(g_ComponentTable[refIndex].pHandle[i] == NULL)
            {      
                break;
            }
        }
        
        if(i >= MAX_COMP_INSTANCES)
        {
            DEBUG_PRINT_ERROR("%s :: no available pHandle slot.\n", __func__);
            err = OMX_ErrorInsufficientResources;
        }
        else
        {
            g_ComponentTable[refIndex].pHandle[i] = *pHandle;
            g_ComponentTable[refIndex].refCount += 1;
            err = OMX_ErrorNone;
        }

		goto UNLOCK_MUTEX;  // Component is found, and thus we are done
	}

	// If we are here, we have not found the component
	err = OMX_ErrorComponentNotFound;
	goto UNLOCK_MUTEX;

CLEAN_UP:
	if(*pHandle != NULL)
	{
		free(*pHandle);
		*pHandle = NULL;
	}

	pComponents[i] = NULL;

#ifdef DYNAMIC_LOAD
	dlclose(pModules[i]);
#endif

	pModules[i] = NULL;

UNLOCK_MUTEX:
	if(pthread_mutex_unlock(&g_Mutex) != 0)
	{
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n", __func__);
		err = OMX_ErrorUndefined;
	}

	return (err);
}


/******************************Public*Routine******************************\
* OMX_FreeHandle()
*
* Description:This method will unload the OMX component pointed by
* OMX_HANDLETYPE. It is the responsibility of the calling method to ensure that
* the Deinit method of the component has been called prior to unloading component
*
* Parameters:
* @param[in] hComponent the component to unload
*
* Returns:    OMX_NOERROR          Successful
*
* Note
*
\**************************************************************************/
OMX_ERRORTYPE OMX_FreeHandle (OMX_HANDLETYPE hComponent)
{
	OMX_ERRORTYPE retVal = OMX_ErrorUndefined;
	OMX_COMPONENTTYPE *pHandle = (OMX_COMPONENTTYPE *)hComponent;
	OMX_U32 refIndex = 0;
	OMX_S32 handleIndex = 0;
	OMX_U32 i = 0;

	if(pthread_mutex_lock(&g_Mutex) != 0)
	{
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n", __func__);
		return OMX_ErrorUndefined;
	}

	/* Locate the component handle in the array of handles */
	for(i = 0; i < COUNTOF(pComponents); i++)
	{
		if(pComponents[i] == hComponent)
        {      
			break;
        }
	}

	if(i >= COUNTOF(pComponents))
	{
		DEBUG_PRINT_ERROR("%s :: Core: component %p is not found\n", __func__, hComponent);
		retVal = OMX_ErrorBadParameter;
		goto EXIT;
	}

	/* call component deinit method */
	retVal = pHandle->ComponentDeInit(hComponent);
	if (retVal != OMX_ErrorNone)
	{
		DEBUG_PRINT_ERROR("%s :: ComponentDeInit failed %d\n", __func__, retVal);
		goto EXIT;
	}

	for (refIndex=0; refIndex < MAX_COMP_NUM; refIndex++)
	{
		for (handleIndex=0; handleIndex < MAX_COMP_INSTANCES; handleIndex++)
		{
			/* get the position for the component in the table */
			if (g_ComponentTable[refIndex].pHandle[handleIndex] == hComponent)
			{
				if (g_ComponentTable[refIndex].refCount)
				{
					g_ComponentTable[refIndex].refCount -= 1;
				}
				g_ComponentTable[refIndex].pHandle[handleIndex] = NULL;

#ifdef DYNAMIC_LOAD
				dlclose(pModules[i]);
#endif
				pModules[i] = NULL;
				free(pComponents[i]);
				pComponents[i] = NULL;
				retVal = OMX_ErrorNone;

				goto EXIT;
			}
		}
	}

	// If we are here, we have not found the matching component
	retVal = OMX_ErrorComponentNotFound;

EXIT:
	/* The unload is now complete, so set the error code to pass and exit */
	if(pthread_mutex_unlock(&g_Mutex) != 0)
	{
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n", __func__);
		return OMX_ErrorUndefined;
	}

	return retVal;
}


/******************************Public*Routine******************************\
* OMX_DeInit()
*
* Description:This method will release the resources of the OMX Core.  It is the
* responsibility of the application to call OMX_DeInit to ensure the clean up of these
* resources.
*
* Returns:    OMX_NOERROR          Successful
*
* Note
*
\**************************************************************************/
OMX_ERRORTYPE OMX_Deinit()
{
	if(pthread_mutex_lock(&g_Mutex) != 0) 
       {
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n", __func__);
		return OMX_ErrorUndefined;
	}

	if (g_InitCount)
    {
		g_InitCount--;
	}

	if(pthread_mutex_unlock(&g_Mutex) != 0) 
       {
		DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n", __func__);
		return OMX_ErrorUndefined;
	}

	return OMX_ErrorNone;
}


/*************************************************************************
* OMX_SetupTunnel()
*
* Description: Setup the specified tunnel the two components
*
* Parameters:
* @param[in] hOutput     Handle of the component to be accessed
* @param[in] nPortOutput Source port used in the tunnel
* @param[in] hInput      Component to setup the tunnel with.
* @param[in] nPortInput  Destination port used in the tunnel
*
* Returns:    OMX_NOERROR          Successful
*
* Note
*
**************************************************************************/
/* OMX_SetupTunnel */
OMX_ERRORTYPE OMX_SetupTunnel(
            OMX_IN OMX_HANDLETYPE outputComponent,
            OMX_IN OMX_U32             outputPort,
            OMX_IN OMX_HANDLETYPE  inputComponent,
            OMX_IN OMX_U32              inputPort)
{
	/* Not supported right now */
	DEBUG_PRINT("%s :: OMXCORE API: OMX_SetupTunnel Not implemented \n", __func__);
	return OMX_ErrorNotImplemented;
}


/*************************************************************************
* OMX_ComponentNameEnum()
*
* Description: This method will provide the name of the component at the given nIndex
*
*Parameters:
* @param[out] cComponentName       The name of the component at nIndex
* @param[in] nNameLength                The length of the component name
* @param[in] nIndex                         The index number of the component
*
* Returns:    OMX_NOERROR          Successful
*
* Note
*
**************************************************************************/
OMX_ERRORTYPE OMX_ComponentNameEnum(
            OMX_OUT OMX_STRING cComponentName,
            OMX_IN  OMX_U32 nNameLength,
            OMX_IN  OMX_U32 nIndex)
{
	OMX_ERRORTYPE eError = OMX_ErrorNone;

	if (nIndex >= g_TableCount)
	{
		eError = OMX_ErrorNoMore;
	}
	else
	{
        DEBUG_PRINT("%s :: g_ComponentTable[%ld].name: %s \n", __func__, nIndex,g_ComponentTable[nIndex].name);
        strncpy(cComponentName, g_ComponentTable[nIndex].name, nNameLength);
	}

	return eError;
}


/*************************************************************************
* OMX_GetRolesOfComponent()
*
* Description: This method will query the component for its supported roles
*
*Parameters:
* @param[in] cComponentName     The name of the component to query
* @param[in] pNumRoles     The number of roles supported by the component
* @param[in] roles		The roles of the component
*
* Returns:    OMX_NOERROR          Successful
*                 OMX_ErrorBadParameter		Faliure due to a bad input parameter
*
* Note
*
**************************************************************************/
OMX_ERRORTYPE OMX_GetRolesOfComponent (
            OMX_IN      OMX_STRING cComponentName,
            OMX_INOUT   OMX_U32 *pNumRoles,
            OMX_OUT     OMX_U8 **roles)
{
	OMX_U32 i = 0;
	OMX_U32 j = 0;
	OMX_BOOL bFound = OMX_FALSE;
	OMX_ERRORTYPE eError = OMX_ErrorNone;

	if (cComponentName == NULL || pNumRoles == NULL)
	{
		eError = OMX_ErrorBadParameter;
		goto EXIT;
	}

	while (i < g_TableCount)
	{
		if (strcmp(cComponentName, g_ComponentTable[i].name) == 0)
		{
			bFound = OMX_TRUE;
			break;
		}
		i++;
	}

	if (!bFound)
	{
		eError = OMX_ErrorComponentNotFound;
		DEBUG_PRINT_ERROR("%s :: component %s not found\n",__func__, cComponentName);
		goto EXIT;
	}

	if (roles == NULL)
	{
		*pNumRoles = g_ComponentTable[i].nRoles;
	}
	else
	{
		/* must be second of two calls, pNumRoles is input in this context.
		If pNumRoles is < actual number of roles than we return an error */
		if (*pNumRoles >= g_ComponentTable[i].nRoles)
		{
			for (j = 0; j<g_ComponentTable[i].nRoles; j++)
			{
				strncpy((OMX_STRING)roles[j], g_ComponentTable[i].pRoleArray[j], OMX_MAX_STRINGNAME_SIZE);
			}
			*pNumRoles = g_ComponentTable[i].nRoles;
		}
		else
		{
			eError = OMX_ErrorBadParameter;
			DEBUG_PRINT_ERROR("%s :: pNumRoles (%ld) is less than actual number (%d) of roles for this component %s\n",__func__, *pNumRoles, g_ComponentTable[i].nRoles,cComponentName);
		}
	}

EXIT:
	return eError;
}


/*************************************************************************
* OMX_GetComponentsOfRole()
*
* Description: This method will query the component for its supported roles
*
*Parameters:
* @param[in] role     The role name to query for
* @param[in] pNumComps     The number of components supporting the given role
* @param[in] compNames      The names of the components supporting the given role
*
* Returns:    OMX_NOERROR          Successful
*
* Note
*
**************************************************************************/
OMX_ERRORTYPE OMX_GetComponentsOfRole (
            OMX_IN      OMX_STRING role,
            OMX_INOUT   OMX_U32 *pNumComps,
            OMX_INOUT   OMX_U8  **compNames)
{
	OMX_U32 i = 0;
	OMX_U32 j = 0;
	OMX_U32 k = 0;
	OMX_U32 compOfRoleCount = 0;
	OMX_ERRORTYPE eError = OMX_ErrorNone;

	if (role == NULL || pNumComps == NULL)
	{
		if (role == NULL)
		{
		   DEBUG_PRINT_ERROR("%s :: role is NULL", __func__);
		}

		if (pNumComps == NULL)
		{
		   DEBUG_PRINT_ERROR("%s :: pNumComps is NULL\n", __func__);
		}

		eError = OMX_ErrorBadParameter;
		goto EXIT;
	}

	/* This implies that the g_ComponentTable is not filled */
	if (!g_TableCount)
	{
		eError = OMX_ErrorUndefined;
		DEBUG_PRINT_ERROR("%s :: Component table is empty. Please reload OMX Core\n", __func__);
		goto EXIT;
	}

	/* no matter, we always want to know number of matching components so this will always run */
	for (i = 0; i < g_TableCount; i++)
	{
		for (j = 0; j < g_ComponentTable[i].nRoles; j++)
		{
			if (strcmp(g_ComponentTable[i].pRoleArray[j], role) == 0)
			{
				/* the first call to this function should only count the number of roles*/
				compOfRoleCount++;
			}
		}
	}

	if (compOfRoleCount == 0)
	{
		eError = OMX_ErrorComponentNotFound;
		DEBUG_PRINT_ERROR("%s :: Component supporting role %s was not found\n", __func__, role);
	}

	if (compNames == NULL)
	{
		/* must be the first of two calls */
		*pNumComps = compOfRoleCount;
	}
	else
	{
		/* must be the second of two calls */
		if (*pNumComps < compOfRoleCount)
		{
		    /* pNumComps is input in this context,
		       it can not be less, this would indicate
		       the array is not large enough
		    */
		    eError = OMX_ErrorBadParameter;
		    DEBUG_PRINT_ERROR("%s :: pNumComps (%ld) is less than the actual number (%ld) of components supporting role %s\n", 
                                                      __func__, *pNumComps, compOfRoleCount, role);
		}
		else
		{
		    k = 0;
		    for (i = 0; i < g_TableCount; i++)
		    {
		        for (j = 0; j < g_ComponentTable[i].nRoles; j++)
		        {
		            if (strcmp(g_ComponentTable[i].pRoleArray[j], role) == 0)
		            {
		                /*  the second call compNames can be allocated with the proper size for that number of roles. */
		                compNames[k] = (OMX_U8*)g_ComponentTable[i].name;
		                k++; 
		                if (k == compOfRoleCount)
		                {
		                    /* there are no more components of this role so we can exit here */
		                    *pNumComps = k;
		                    goto EXIT;
		                }
		            }
		        }
		    }
		}
	}

EXIT:
	return eError;
    
}



