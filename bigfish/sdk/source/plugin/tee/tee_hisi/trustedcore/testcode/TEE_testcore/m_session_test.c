/*
 * OpenVirtualization:
 * For additional details and support contact developer@sierraware.com.
 * Additional documentation can be found at www.openvirtualization.org
 *
 * Copyright (C) 2011 SierraWare
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Linux trustzone example application.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "tee_client_storage_api.h"
//#include <sys/time.h>
#define BIGBUFFER 4*1024*1024
static void bindCPU(unsigned int cpu)
{
    int rv;
    //cpu_set_t cpuset;

    //CPU_ZERO(&cpuset);
    //CPU_SET(cpu, &cpuset);
	unsigned long mask = 1; /* processor 0 */

    //rv = sched_setaffinity(0, sizeof(cpuset), &cpuset);
	rv = sched_setaffinity(0, sizeof(mask), &mask);
    if (rv != 0) {
        printf("bindCPU failed, rv = %d\n",rv);
        perror(NULL);
        exit(30);
    }
}

//name==NULL,context.state==INVAILD
void Test_TEEC_InitializeContext001()
{
      TEEC_Context context;
#ifdef CONFIG_STATE
	  context.state = INVALID;
#endif
	  TEEC_Result result;
      result = TEEC_InitializeContext(
               NULL,
               &context);
      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_InitializeContext001 faile\n");
    }
	  else
            printf("Test_TEEC_InitializeContext001 success\n");
	   TEEC_FinalizeContext(&context);
}

//name==NULL,context==NULL
void Test_TEEC_InitializeContext002()
{
      TEEC_Context context;
#ifdef CONFIG_STATE
	  context.state = INVALID;
#endif
	  TEEC_Result result;
      result = TEEC_InitializeContext(
               NULL,
               NULL);
       if(result != TEEC_ERROR_BAD_PARAMETERS) {
        printf("Test_TEEC_InitializeContext002 faile\n");
    }
	  else
             printf("Test_TEEC_InitializeContext002 success\n");
}


//name==NULL,context==INACTIVE
void Test_TEEC_InitializeContext003()
{
      TEEC_Context context;
#ifdef CONFIG_STATE
	  context.state = INVALID;
#endif
	  TEEC_Result result;
      result = TEEC_InitializeContext(
               NULL,
               &context);
       if(result != TEEC_ERROR_BAD_STATE) {
        printf("Test_TEEC_InitializeContext003 faile\n");
    }
	  else
             printf("Test_TEEC_InitializeContext003 success\n");
}

void pthread_OpenSession()
{
TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;
    int pid = (int) getpid();
    int tid = (int) pthread_self();

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];
    printf("\n  PID: %d    TID: %d    SUCCESS\n", pid, tid);

    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("pthread_OpenSession TEEC_InitializeContext faile");
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);
    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                &operation,
                NULL);

    if(result != TEEC_SUCCESS) {
        printf("pthread_OpenSession TEEC_OpenSession faile\n");
    }
	else{
		printf("pthread_OpenSession TEEC_OpenSession success\n");


    printf("sssssession id 0x%x\n", session.session_id);
    printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

	TEEC_CloseSession(&session);
		}
	 TEEC_FinalizeContext(&context);
}

void Test_pthread_OpenSession()
{
    printf("\nTest Test_pthread_OpenSession Concurrent\n");
    pthread_t ntid;
    void *rtn;
    int i;
    pthread_t ids[50];
    for (i=0; i<50; i++)
    {
        int err = pthread_create(&ntid, NULL, &pthread_OpenSession, NULL);
        if (err != 0)
        {
            fprintf(stderr, "can't create thread: %s\n", strerror(err));
            exit(1);
        }
        ids[i] = ntid;
    }
    for (i=0; i<50; i++)
        pthread_join(ids[i], &rtn);
	printf("\nTEST Test_pthread_OpenSession ENDING\n");
}

//right params
void Test_TEEC_OpenSession001()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;
	//double cost_time;
   //clock_t start,end;
   //struct timeval {
//long int tv_sec; // ÃëÊý
//long int tv_usec; // Î¢ÃëÊý
//};


    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;
printf("tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt");
    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_OpenSession001 TEEC_InitializeContext faile");
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);
    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

   //start=clock();
  // struct timeval time1, time2;
//gettimeofday(&time1, NULL);

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                &operation,
                NULL);
  //end=clock();
 // gettimeofday(&time2, NULL);
    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_OpenSession001 TEEC_OpenSession faile");
    }
	else
		printf("Test_TEEC_OpenSession001 TEEC_OpenSession success\n");

    printf("sssssession id 0x%x\n", session.session_id);
    printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);
	//cost_time=(double)(end-start)/CLOCKS_PER_SEC;
    //printf("Time is : %f\n",cost_time);
   // printf("Time is : %f\n",1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec);
  // printf("download time : %ld.%ld s\n",
  //       time2.tv_usec-time1.tv_usec >=0 ? time2.tv_sec-time1.tv_sec : time2.tv_sec-time1.tv_sec-1,
  //      time2.tv_usec-time1.tv_usec >=0 ? (time2.tv_usec-time1.tv_usec)/1000 : (time2.tv_usec-time1.tv_usec)/1000+1000);

	TEEC_CloseSession(&session);
}

      //three params is null;
void Test_TEEC_OpenSession002()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

	    result = TEEC_OpenSession(
                NULL,
                NULL,
                NULL,
                TEEC_LOGIN_PUBLIC,
                NULL,
                &operation,
                NULL);

		 if(result != TEEC_ERROR_BAD_PARAMETERS) {
        printf("Test_TEEC_OpenSession002  faile\n");
    }
	else
		printf("Test_TEEC_OpenSession002  success\n");

}

//context->state = INVALID;
void Test_TEEC_OpenSession003()
{
       TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_OpenSession003 TEEC_InitializeContext faile\n");
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);
    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

#ifdef CONFIG_STATE
    context.state = INVALID;
#endif
    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                &operation,
                NULL);

    if(result != TEEC_ERROR_BAD_STATE) {
        printf("Test_TEEC_OpenSession003  faile\n");
    }
	else
		printf("Test_TEEC_OpenSession003  success\n");
}

//operation=null
void Test_TEEC_OpenSession004()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_OpenSession001 TEEC_InitializeContext faile");
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);
    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_OpenSession004 TEEC_OpenSession faile\n");
    }
	else{
		printf("Test_TEEC_OpenSession004 TEEC_OpenSession success\n");

	TEEC_CloseSession(&session);
	}
}

void pthread_InvokeCommand(void *arg)
{
TEEC_Context context;
    TEEC_Session* session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;
      int pid = (int) getpid();
    int tid = (int) pthread_self();
    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];
   printf("\n  PID: %d    TID: %d    SUCCESS\n", pid, tid);

  session = (TEEC_Session*)arg;
      operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

    result = TEEC_InvokeCommand(
                 session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("pthread_InvokeCommand is faile\n");
    }
	else {
		 printf("pthread_InvokeCommand is success\n");
	 printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);
		}
}

void Test_pthread_InvokeCommand()
{
    printf("\nTest Test_pthread_InvokeCommand Concurrent\n");
    pthread_t ntid;
    void *rtn;
    int i;
    pthread_t ids[5];
	TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;
    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("pthread_InvokeCommand TEEC_InitializeContext is faile\n");
    }
	else
		 printf("pthread_InvokeCommand TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("pthread_InvokeCommand TEEC_OpenSession is faile\n");
    }
    else
       printf("pthread_InvokeCommand TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);



    for (i=0; i<5; i++)
    {
        int err = pthread_create(&ntid, NULL, &pthread_InvokeCommand, &session);
        if (err != 0)
        {
            fprintf(stderr, "can't create thread: %s\n", strerror(err));
            exit(1);
        }
        ids[i] = ntid;
    }
    for (i=0; i<5; i++)
        pthread_join(ids[i], &rtn);



   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
	printf("\nTEST Test_pthread_InvokeCommand ENDING\n");
}

void Test_TEEC_InvokeCommand_BigBuffer()
{
TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char*    testData;

    uint32_t len1;
    char    testData1[BIGBUFFER];

    uint32_t len2;
    char    testData2[BIGBUFFER];

    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand_BigBuffer TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand_BigBuffer TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand_BigBuffer TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand_BigBuffer TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,//TEEC_MEMREF_TEMP_OUTPUT
        TEEC_VALUE_OUTPUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

int k;
testData = (char*)malloc(BIGBUFFER);
    for(k=0;k<BIGBUFFER;k++)
        {
          testData[k]=k;
	}
	testData[BIGBUFFER-1]='\0';
    len=BIGBUFFER;

int j;
    for(j=0;j<BIGBUFFER;j++)
        {
          testData1[j]=j;
	}
	testData1[BIGBUFFER-1]='\0';
    len1=BIGBUFFER;

    operation.params[1].tmpref.buffer = testData; //filebuff
    operation.params[1].tmpref.size = len;


    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;



    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand_BigBuffer is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand_BigBuffer is success\n");

    printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);
free(testData);
   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//right params
void Test_TEEC_InvokeCommand001()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

	//uint8_t* filebuff = NULL; //////

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand001 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand001 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand001 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand001 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

	//	filebuff = (char*)malloc(1000);//////
	//strcpy(filebuff, "Hellonnn");//////
	//   len = strlen("Hellonnn") + 1; //////


    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData; //filebuff
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;



    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand001 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand001 is success\n");

    printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//operation is not null
void Test_TEEC_InvokeCommand002()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand002 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand002 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 &operation,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand002 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand002 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_INPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_VALUE_OUTPUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand002 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand002 is success\n");

    printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//TEEC_PARAM_TYPES test TEEC_NONE
void Test_TEEC_InvokeCommand003()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand003 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand003 TEEC_InitializeContext is success\n");
       operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES(
	        TEEC_NONE,
	        TEEC_NONE,
	        TEEC_NONE,
	        TEEC_NONE);

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 &operation,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand003 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand003 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);


    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand003 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand003 is success\n");

   // printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    //printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//TEEC_PARAM_TYPES TEST
void Test_TEEC_InvokeCommand004()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand004 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand004 TEEC_InitializeContext is success\n");

	 operation.started = 1;

		operation.paramTypes = TEEC_PARAM_TYPES(
	        TEEC_NONE,
	        TEEC_NONE,
	        TEEC_NONE,
	        TEEC_NONE);

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 &operation,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand004 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand004 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_OUTPUT,
        TEEC_VALUE_INOUT,
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_MEMREF_TEMP_INOUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[3].tmpref.buffer = testData;
    operation.params[3].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    operation.params[1].value.a = 0x789;
    operation.params[1].value.b = 0xABC;

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand004 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand004 is success\n");

    printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//TEEC_PARAM_TYPES TEST
void Test_TEEC_InvokeCommand005()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand005 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand005 TEEC_InitializeContext is success\n");

    //operation.started = 1;

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand005 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand005 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_OUTPUT,
        TEEC_VALUE_OUTPUT,
        TEEC_VALUE_OUTPUT,
        TEEC_VALUE_OUTPUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    operation.params[1].value.a = 0x123;
    operation.params[1].value.b = 0x456;

    operation.params[2].value.a = 0x123;
    operation.params[2].value.b = 0x456;

    operation.params[3].value.a = 0x789;
    operation.params[3].value.b = 0xABC;

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand005 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand005 is success\n");

 //   printf("[2]: %s\n", operation.params[2].tmpref.buffer);
    printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);
 printf("[2]: %x %x\n", operation.params[2].value.a, operation.params[2].value.b);


   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//right params
void Test_TEEC_InvokeCommand006()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif

    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand006 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand006 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand006 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand006 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_MEMREF_TEMP_OUTPUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_MEMREF_TEMP_OUTPUT);

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[0].tmpref.buffer = testData;
    operation.params[0].tmpref.size = len;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[1].tmpref.buffer = testData;
    operation.params[1].tmpref.size = len;

    strcpy(testData1, "abcdefgh");
    len1 = strlen("abcdefgh") + 1;
    operation.params[2].tmpref.buffer = testData1;
    operation.params[2].tmpref.size = len1;

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[3].tmpref.buffer = testData;
    operation.params[3].tmpref.size = len;

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand006 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand006 is success\n");

   printf("[1]: %s\n", operation.params[0].tmpref.buffer);
    printf("[2]: %s\n", operation.params[1].tmpref.buffer);
	printf("[3]: %s\n", operation.params[2].tmpref.buffer);
	printf("[4]: %s\n", operation.params[3].tmpref.buffer);
    //printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//right params
void Test_TEEC_InvokeCommand007()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

	    uint32_t len3;
    char    testData3[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand007 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand007 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand007 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand007 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_TEMP_INOUT,
        TEEC_MEMREF_TEMP_INOUT,// TEEC_NONE
        TEEC_MEMREF_TEMP_INOUT,
        TEEC_MEMREF_TEMP_INOUT);

    strcpy(testData, "Hello");
    len = strlen("Hello") + 1;
    operation.params[0].tmpref.buffer = testData;
    operation.params[0].tmpref.size = len;

    strcpy(testData1, "Hello hello");
    len1 = strlen("Hello hello") + 1;
    operation.params[1].tmpref.buffer = testData1;
    operation.params[1].tmpref.size = len1;

    strcpy(testData2, "Hello hello hello");
    len2 = strlen("Hello hello hello") + 1;
    operation.params[2].tmpref.buffer = testData2;
    operation.params[2].tmpref.size = len2;

    strcpy(testData3, "Hello hello hello hello");
    len3 = strlen("Hello hello hello hello ") + 1;
    operation.params[3].tmpref.buffer = testData3;
    operation.params[3].tmpref.size = len3;

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand007 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand007 is success\n");

   printf("[1]: %s\n", operation.params[0].tmpref.buffer);
    printf("[2]: %s\n", operation.params[1].tmpref.buffer);
	printf("[3]: %s\n", operation.params[2].tmpref.buffer);
	printf("[4]: %s\n", operation.params[3].tmpref.buffer);
    //printf("[3]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//right params
void Test_TEEC_InvokeCommand008()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

	    uint32_t len3;
    char    testData3[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand008 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand008 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand008 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand008 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    operation.params[1].value.a = 0x123;
    operation.params[1].value.b = 0x456;

    operation.params[2].value.a = 0x123;
    operation.params[2].value.b = 0x456;

    operation.params[3].value.a = 0x123;
    operation.params[3].value.b = 0x456;

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand008 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand008 is success\n");


    printf("[1]: %x %x\n", operation.params[0].value.a, operation.params[0].value.b);
	printf("[2]: %x %x\n", operation.params[1].value.a, operation.params[1].value.b);
	printf("[3]: %x %x\n", operation.params[2].value.a, operation.params[2].value.b);
	printf("[4]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//tmpref.size=0
void Test_TEEC_InvokeCommand009()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

	    uint32_t len3;
    char    testData3[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand009 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand009 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand009 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand009 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT,
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_MEMREF_TEMP_INOUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    operation.params[1].value.a = 0x123;
    operation.params[1].value.b = 0x456;

    strcpy(testData2, "");
    len2 = strlen("");
    operation.params[2].tmpref.buffer = testData2;
    operation.params[2].tmpref.size = len2;

    strcpy(testData3, "");
    len3 = strlen("");
    operation.params[3].tmpref.buffer = testData3;
    operation.params[3].tmpref.size = len3;

	printf("len2 is %x\n",len2);
	printf("len3 is %x\n",len3);

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_ERROR_BAD_PARAMETERS)
    {
        printf("Test_TEEC_InvokeCommand009 is faile\n");
    }
	else
		 printf("exception test success Test_TEEC_InvokeCommand009 is success\n");


    printf("[1]: %x %x\n", operation.params[0].value.a, operation.params[0].value.b);
	printf("[2]: %x %x\n", operation.params[1].value.a, operation.params[1].value.b);
	printf("[3]: %s\n", operation.params[2].tmpref.buffer);
	printf("[4]: %s\n", operation.params[3].tmpref.buffer);

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//still invoke
void Test_TEEC_InvokeCommand010()
{
      TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    TEEC_Session session1;

    uint32_t len;
    char    testData[256];

    uint32_t len1;
    char    testData1[256];

    uint32_t len2;
    char    testData2[256];

	    uint32_t len3;
    char    testData3[256];

#ifdef CONFIG_STATE
    context.state = INVALID;
    session.state = INVALID;
    operation.state = READY;

    session1.state = INVALID;
#endif


    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand010 TEEC_InitializeContext is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand010 TEEC_InitializeContext is success\n");

    result = TEEC_OpenSession(
                &context,
                &session,
                &svc_id,
                TEEC_LOGIN_PUBLIC,
                NULL,
                 NULL,
                NULL);

    if(result != TEEC_SUCCESS) {
       printf("Test_TEEC_InvokeCommand010 TEEC_OpenSession is faile\n");
    }
    else
       printf("Test_TEEC_InvokeCommand010 TEEC_OpenSession is success  session id is 0x%x\n", session.session_id);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT,
        TEEC_VALUE_INOUT);

    operation.params[0].value.a = 0x123;
    operation.params[0].value.b = 0x456;

    operation.params[1].value.a = 0x123;
    operation.params[1].value.b = 0x456;

    operation.params[2].value.a = 0x123;
    operation.params[2].value.b = 0x456;

    operation.params[3].value.a = 0x123;
    operation.params[3].value.b = 0x456;
   int j;
	for(j=0;j<3;j++){

    result = TEEC_InvokeCommand(
                 &session,
                 ECHO_CMD_ID_SEND_CMD,
                 &operation,
                 NULL);

    if (result != TEEC_SUCCESS)
    {
        printf("Test_TEEC_InvokeCommand010 is faile\n");
    }
	else
		 printf("Test_TEEC_InvokeCommand010 is success\n");


    printf("[1]: %x %x\n", operation.params[0].value.a, operation.params[0].value.b);
	printf("[2]: %x %x\n", operation.params[1].value.a, operation.params[1].value.b);
	printf("[3]: %x %x\n", operation.params[2].value.a, operation.params[2].value.b);
	printf("[4]: %x %x\n", operation.params[3].value.a, operation.params[3].value.b);



		}

   TEEC_CloseSession(&session);
   TEEC_FinalizeContext(&context);
}

//closeSession
//	void Test_TEEC_InvokeCommand011()
//	{
//	      TEEC_CloseSession(&session);

//	}

//right param
void Test_TEEC_AllocateSharedMemory01()
{
       TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];

    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("TEEC_AllocateSharedMemory01 TEEC_InitializeContext faile\n");
    }else
       printf("TEEC_AllocateSharedMemory01 TEEC_InitializeContext success\n");

    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT ;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("TEEC_AllocateSharedMemory01 allocate failed, %x\n", result);
    } else {
        printf("TEEC_AllocateSharedMemory01 allocat success\n");
	TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);
    }
}

//sharedMem.size = 0
void Test_TEEC_AllocateSharedMemory02()
{
       TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];

    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("TEEC_AllocateSharedMemory02 TEEC_InitializeContext faile\n");
    }else
       printf("TEEC_AllocateSharedMemory02 TEEC_InitializeContext success\n");

    sharedMem.size = 0;
    sharedMem.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT ;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_ERROR_BAD_PARAMETERS) {
        printf("TEEC_AllocateSharedMemory02 allocate failed, %x\n", result);
    } else {
       printf("TEEC_AllocateSharedMemory02 allocat success\n");
	TEEC_FinalizeContext(&context);
    }
}

//sharedMem.flags = TEEC_MEM_INOUT
void Test_TEEC_AllocateSharedMemory03()
{
       TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("TEEC_AllocateSharedMemory03 TEEC_InitializeContext faile\n");
    }else
       printf("TEEC_AllocateSharedMemory03 TEEC_InitializeContext success\n");

    sharedMem.size = 1025;
    sharedMem.flags = TEEC_MEM_INOUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("TEEC_AllocateSharedMemory03 allocate failed, %x\n", result);
    } else {
        printf("TEEC_AllocateSharedMemory03 allocat success\n");
	TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);
    }
}

//param is NULL
void Test_TEEC_AllocateSharedMemory04()
{
       TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
       printf("TEEC_AllocateSharedMemory04 TEEC_InitializeContext faile\n");
    }else
       printf("TEEC_AllocateSharedMemory04 TEEC_InitializeContext success\n");

    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INOUT;

    result = TEEC_AllocateSharedMemory(
                NULL,
                NULL);

    if(result != TEEC_ERROR_BAD_PARAMETERS) {
        printf("TEEC_AllocateSharedMemory04 allocate failed, %x\n", result);
    } else {
       printf("TEEC_AllocateSharedMemory04 allocat success\n");

	TEEC_FinalizeContext(&context);
    }
}

//right
    void  Test_TEEC_AllocateSharedMemory05()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory05 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory05 TEEC_InitializeContext success\n");

    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT ;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory05 allocate failed, %x\n", result);
    } else {
        printf("Test_TEEC_AllocateSharedMemory05 allocat success\n");
	strcpy(sharedMem.buffer, "Hello World");
	printf("%s\n", (char*)sharedMem.buffer);
	TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);
    }
}

//right
    void  Test_TEEC_AllocateSharedMemory06()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory06 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory06 TEEC_InitializeContext success\n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory06 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory06 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "Hello World");
	len = strlen("Hello World") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
       }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_WHOLE,
	    TEEC_NONE,
	    TEEC_NONE,
	    TEEC_NONE);

	operation.started = 1;

	operation.params[0].memref.parent = &sharedMem;
	//operation.params[0].memref.offset = 0;
	//operation.params[0].memref.size = 30;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_SUCCESS) {
	    printf("Test_TEEC_AllocateSharedMemory06 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory06 sssssession id 0x%x\n", session.session_id);
		printf("%s\n", (char*)sharedMem.buffer);
		TEEC_CloseSession(&session);
	}

       TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);

}

//TEEC_MEMREF_WHOLE test
    void  Test_TEEC_AllocateSharedMemory07()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory07 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory07 TEEC_InitializeContext success\n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory07 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
        printf("Test_TEEC_AllocateSharedMemory07 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "Hello World");
	len = strlen("Hello World") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
       }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_NONE,
	    TEEC_NONE,
	    TEEC_MEMREF_WHOLE,
	    TEEC_MEMREF_WHOLE);

	operation.started = 1;

	operation.params[2].memref.parent = &sharedMem;
	//operation.params[2].memref.offset = 0;
	//operation.params[2].memref.size = 30;

      operation.params[3].memref.parent = &sharedMem;
	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_SUCCESS) {
	    printf("Test_TEEC_AllocateSharedMemory07 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory07 sssssession id 0x%x\n", session.session_id);
		printf("%s\n", (char*)sharedMem.buffer);
		TEEC_CloseSession(&session);
	}

       TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);

}

//TEEC_MEM_INPUT   ---  TEEC_MEMREF_PARTIAL_INPUT test
    void  Test_TEEC_AllocateSharedMemory08()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory08 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory08 TEEC_InitializeContext success\n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory08 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory08 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "Hello World");
	len = strlen("Hello World") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
       }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_PARTIAL_INPUT,
	    TEEC_NONE,
	    TEEC_NONE,
	    TEEC_MEMREF_PARTIAL_INPUT);

	operation.started = 1;

	operation.params[3].memref.parent = &sharedMem;
	operation.params[3].memref.offset = 0;
	operation.params[3].memref.size = 30;

	operation.params[0].memref.parent = &sharedMem;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = 30;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_SUCCESS) {
	    printf("Test_TEEC_AllocateSharedMemory08 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory08 sssssession id 0x%x\n", session.session_id);
		printf("%s\n", (char*)sharedMem.buffer);
		TEEC_CloseSession(&session);
	}

       TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);

}

//TEEC_MEM_INPUT   ---  TEEC_MEMREF_PARTIAL_OUTPUT test
    void  Test_TEEC_AllocateSharedMemory09()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory09 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory09 TEEC_InitializeContext success\n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory09 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory09 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "Hello World");
	len = strlen("Hello World") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
       }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_PARTIAL_OUTPUT,
	    TEEC_NONE,
	    TEEC_NONE,
	    TEEC_NONE);

	operation.started = 1;

	operation.params[0].memref.parent = &sharedMem;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = 30;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_ERROR_BAD_PARAMETERS) {
	    printf("Test_TEEC_AllocateSharedMemory09 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory09 success  type of memref is different from the parent flags\n");
		printf("%s\n", (char*)sharedMem.buffer);
		//TEEC_CloseSession(&session);
	}

      // TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);

}

//TEEC_MEM_INPUT   ---  TEEC_MEMREF_PARTIAL_OUTPUT test
    void  Test_TEEC_AllocateSharedMemory010()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory010 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory010 TEEC_InitializeContext success\n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_OUTPUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory010 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
        printf("Test_TEEC_AllocateSharedMemory010 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "Hello World");
	len = strlen("Hello World") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
      }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_PARTIAL_INPUT,
	    TEEC_NONE,
	    TEEC_NONE,
	    TEEC_NONE);

	operation.started = 1;

	operation.params[0].memref.parent = &sharedMem;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = 30;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_ERROR_BAD_PARAMETERS) {
	    printf("Test_TEEC_AllocateSharedMemory010 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory010 success  type of memref is different from the parent flags\n");
		printf("%s\n", (char*)sharedMem.buffer);
		//TEEC_CloseSession(&session);
	}

       //TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);

}

//TEEC_MEM_INOUT   ---  TEEC_MEMREF_PARTIAL_INPUT test
    void  Test_TEEC_AllocateSharedMemory011()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory011 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory011 TEEC_InitializeContext success\n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INOUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory011 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
        printf("Test_TEEC_AllocateSharedMemory011 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "Hello World");
	len = strlen("Hello World") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
       }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_PARTIAL_INPUT,
	    TEEC_NONE,
	    TEEC_NONE,
	    TEEC_NONE);

	operation.started = 1;

	operation.params[0].memref.parent = &sharedMem;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = 30;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_SUCCESS) {
	    printf("Test_TEEC_AllocateSharedMemory011 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory011 success id 0x%x\n", session.session_id);
		printf("%s\n", (char*)sharedMem.buffer);
		TEEC_CloseSession(&session);
	}

       TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_FinalizeContext(&context);

}

//right test data
    void  Test_TEEC_AllocateSharedMemory012()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1,sharedMem2;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory012 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory012 TEEC_InitializeContext success  \n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT;
	 sharedMem1.size = 1024;
    sharedMem1.flags = TEEC_MEM_OUTPUT;
	 sharedMem2.size = 1024;
    sharedMem2.flags = TEEC_MEM_INOUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory012 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory012 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "aaaaaaaaaaaaaaaa");
	len = strlen("aaaaaaaaaaaaaaaa") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
       }

	    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem1);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory012 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory012 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem1.buffer, "bbbbbbbbbbbbbbbb");
	len1 = strlen("bbbbbbbbbbbbbbbb") + 1;
	printf("%s\n", (char*)sharedMem1.buffer);
        }

	    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem2);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory012 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory012 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem2.buffer, "cccccccccccccccc");
	len2 = strlen("cccccccccccccccc") + 1;
	printf("%s\n", (char*)sharedMem2.buffer);
      }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_PARTIAL_INPUT,
	    TEEC_MEMREF_PARTIAL_OUTPUT,
	    TEEC_MEMREF_PARTIAL_INOUT,
	    TEEC_NONE);

	operation.started = 1;

	operation.params[0].memref.parent = &sharedMem;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = 30;

	operation.params[1].memref.parent = &sharedMem1;
	operation.params[1].memref.offset = 0;
	operation.params[1].memref.size = 30;

	operation.params[2].memref.parent = &sharedMem2;
	operation.params[2].memref.offset = 0;
	operation.params[2].memref.size = 30;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_SUCCESS) {
	    printf("Test_TEEC_AllocateSharedMemory012 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory012 opensession success id 0x%x\n", session.session_id);
		printf("%s\n", (char*)sharedMem.buffer);
		printf("%s\n", (char*)sharedMem1.buffer);
		printf("%s\n", (char*)sharedMem2.buffer);
		TEEC_CloseSession(&session);
	}

       TEEC_ReleaseSharedMemory(&sharedMem);
	   TEEC_ReleaseSharedMemory(&sharedMem1);
	   TEEC_ReleaseSharedMemory(&sharedMem2);
	TEEC_FinalizeContext(&context);

}

//len write test
    void  Test_TEEC_AllocateSharedMemory013()
{
          TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_SharedMemory sharedMem, sharedMem1,sharedMem2;
    TEEC_SharedMemory nonZeroCopysharedMem;

    TEEC_Result result;

    TEEC_UUID svc_id = TEE_SERVICE_ECHO;

    uint32_t len, len1, len2;
    char    testData[256];



    result = TEEC_InitializeContext(
               NULL,
               &context);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory013 TEEC_InitializeContext faile\n ");
    }else
        printf("Test_TEEC_AllocateSharedMemory013 TEEC_InitializeContext success  \n");



    sharedMem.size = 1024;
    sharedMem.flags = TEEC_MEM_INPUT;
	 sharedMem1.size = 1024;
    sharedMem1.flags = TEEC_MEM_OUTPUT;
	 sharedMem2.size = 1024;
    sharedMem2.flags = TEEC_MEM_INOUT;

    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory013 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory013 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem.buffer, "aaaaaaaaaaaaaaaa");
	len = strlen("aaaaaaaaaaaaaaaa") + 1;
	printf("%s\n", (char*)sharedMem.buffer);
        }

	    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem1);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory013 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
        printf("Test_TEEC_AllocateSharedMemory013 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem1.buffer, "bbbbbbbbbbbbbbbb");
	len1 = strlen("bbbbbbbbbbbbbbbb") + 1;
	printf("%s\n", (char*)sharedMem1.buffer);
      }

	    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem2);

    if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_AllocateSharedMemory013 TEEC_AllocateSharedMemory failed, %x\n", result);
    } else {
       printf("Test_TEEC_AllocateSharedMemory013 TEEC_AllocateSharedMemory success\n");
	strcpy(sharedMem2.buffer, "cccccccccccccccc");
	len2 = strlen("cccccccccccccccc") + 1;
	printf("%s\n", (char*)sharedMem2.buffer);
       }

	operation.paramTypes = TEEC_PARAM_TYPES(
	    TEEC_MEMREF_PARTIAL_INPUT,
	    TEEC_MEMREF_PARTIAL_OUTPUT,
	    TEEC_MEMREF_PARTIAL_INOUT,
	    TEEC_NONE);

	operation.started = 1;

	operation.params[0].memref.parent = &sharedMem;
	operation.params[0].memref.offset = 0;
	operation.params[0].memref.size = 30;

	operation.params[1].memref.parent = &sharedMem1;
	operation.params[1].memref.offset = 6;
	operation.params[1].memref.size = 30;

	operation.params[2].memref.parent = &sharedMem2;
	operation.params[2].memref.offset = 6;
	operation.params[2].memref.size = 8;

	result = TEEC_OpenSession(
	            &context,
	            &session,
	            &svc_id,
	            TEEC_LOGIN_PUBLIC,
	            NULL,
	            &operation,
	            NULL);

	if(result != TEEC_SUCCESS) {
	    printf("Test_TEEC_AllocateSharedMemory013 opensession faild, %x\n", result);
	} else {
		printf("Test_TEEC_AllocateSharedMemory013 opensession success id 0x%x\n", session.session_id);
		printf("%s\n", (char*)sharedMem.buffer);
		printf("%s\n", (char*)sharedMem1.buffer);
		printf("%s\n", (char*)sharedMem2.buffer);
		TEEC_CloseSession(&session);
	}

       TEEC_ReleaseSharedMemory(&sharedMem);
	   TEEC_ReleaseSharedMemory(&sharedMem1);
	   TEEC_ReleaseSharedMemory(&sharedMem2);
	TEEC_FinalizeContext(&context);

}

//right test
void Test_TEEC_RegisterSharedMemory001()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2;
      char    testData[256];

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory001 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory001 TEEC_InitializeContext success  \n");


      sharedMem.size = 1024;
      sharedMem.flags = TEEC_MEM_INOUT;
      result = TEEC_AllocateSharedMemory(
          &context,
          &sharedMem
	  );
      if(result != TEEC_SUCCESS){
          printf("Test_TEEC_RegisterSharedMemory001 allocate mem failed, %x\n", result);
	  }else
            {
             printf("Test_TEEC_RegisterSharedMemory001 TEEC_AllocateSharedMemory success\n");
	  }
	  memset(sharedMem.buffer, 0x00, 1024);
         printf("allocat success\n");
	  strcpy(sharedMem.buffer, "1122334455");
	  printf("%s\n", (char*)sharedMem.buffer);
	  strcpy((char*)sharedMem.buffer + 512, "0123456789");
	  printf("%s\n", (char*)sharedMem.buffer + 512);
	  len = strlen("0123456789") + 1;

      nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory001 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory001 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

	printf("register success\n");
	strcpy(testData, "ABCDEFGHIJK");
	printf("%s\n", testData);
	strcpy(testData + 128, "9876543210");
	printf("%s\n", testData + 128);

	len1 = strlen("ABCDEFGHIJK") + 1;
	len2 = strlen("9876543210") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_PARTIAL_INOUT,
          TEEC_MEMREF_PARTIAL_INOUT,
          TEEC_MEMREF_TEMP_INOUT,
          TEEC_VALUE_INOUT
	);

		operation.params[0].memref.parent = &sharedMem;
		operation.params[0].memref.offset = 512;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 128;
		operation.params[1].memref.size = len2;
		operation.params[2].tmpref.buffer = testData;
		operation.params[2].tmpref.size = len1;
		operation.params[3].value.a = 0x1234;
		operation.params[3].value.b = 0x4567;

		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_SUCCESS){
                  printf("Test_TEEC_RegisterSharedMemory001 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory001 TEEC_OpenSession success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)sharedMem.buffer+512);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+128);
				  printf("%s\n", testData);
				  printf("%x %x\n", operation.params[3].value.a, operation.params[3].value.b);
				  TEEC_CloseSession(&session);
		}

		TEEC_ReleaseSharedMemory(&sharedMem);
		TEEC_FinalizeContext(&context);

}

//nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;
void Test_TEEC_RegisterSharedMemory002()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2;
      char    testData[256];

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory002 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory002 TEEC_InitializeContext success  \n");

	  nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory002 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory002 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

      printf("register success\n");
	  strcpy(testData, "1122334455");
	  printf("%s\n", testData);
	  strcpy(testData + 100, "66778899");
	  printf("%s\n", testData + 100);
	  strcpy(testData + 200, "aabbccddeeff");
	  printf("%s\n", testData + 200);

	  len = strlen("1122334455") + 1;
	  len1 = strlen("66778899") + 1;
	  len2 = strlen("aabbccddeeff") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_WHOLE,
          TEEC_MEMREF_PARTIAL_INPUT,
          TEEC_MEMREF_PARTIAL_OUTPUT,
          TEEC_MEMREF_PARTIAL_INOUT
	);

		operation.params[0].memref.parent = &nonZeroCopysharedMem;
		operation.params[0].memref.offset = 0;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 100;
		operation.params[1].memref.size = len1;
		operation.params[2].memref.parent = &nonZeroCopysharedMem;
		operation.params[2].memref.offset = 150;
		operation.params[2].memref.size = len2;
		operation.params[3].memref.parent = &nonZeroCopysharedMem;
		operation.params[3].memref.offset = 200;
		operation.params[3].memref.size = len2;

		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_SUCCESS){
                  printf("Test_TEEC_RegisterSharedMemory002 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory002 TEEC_OpenSession success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+100);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+150);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+200);
				  TEEC_CloseSession(&session);
		}

		TEEC_ReleaseSharedMemory(&nonZeroCopysharedMem);
		TEEC_FinalizeContext(&context);
}

//nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;
void Test_TEEC_RegisterSharedMemory003()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2,len3;
      char    testData[256];

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory003 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory003 TEEC_InitializeContext success  \n");

	  nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory003 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory003 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

      printf("register success\n");
	  strcpy(testData, "1122334455");
	  printf("%s\n", testData);
	  strcpy(testData + 100, "66778899");
	  printf("%s\n", testData + 100);
	  strcpy(testData + 200, "aabbccddeeff");
	  printf("%s\n", testData + 200);
	  strcpy(testData + 230, "testtesttest");
	  printf("%s\n", testData + 230);

	  len = strlen("1122334455") + 1;
	  len1 = strlen("66778899") + 1;
	  len2 = strlen("aabbccddeeff") + 1;
	  len3 = strlen("testtesttest") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_PARTIAL_INPUT,
          TEEC_MEMREF_PARTIAL_INPUT,
          TEEC_MEMREF_PARTIAL_OUTPUT,
          TEEC_MEMREF_PARTIAL_OUTPUT
	);

		operation.params[0].memref.parent = &nonZeroCopysharedMem;
		operation.params[0].memref.offset = 0;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 100;
		operation.params[1].memref.size = len1;
		operation.params[2].memref.parent = &nonZeroCopysharedMem;
		operation.params[2].memref.offset = 200;
		operation.params[2].memref.size = len2;
		operation.params[3].memref.parent = &nonZeroCopysharedMem;
		operation.params[3].memref.offset = 230;
		operation.params[3].memref.size = len2;

		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_SUCCESS){
                  printf("Test_TEEC_RegisterSharedMemory002 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory002 TEEC_OpenSession success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+100);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+200);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+230);
				  TEEC_CloseSession(&session);
		}

		TEEC_ReleaseSharedMemory(&nonZeroCopysharedMem);
		TEEC_FinalizeContext(&context);
}

//nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;
void Test_TEEC_RegisterSharedMemory004()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2,len3;
      char    testData[256];

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory004 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory004 TEEC_InitializeContext success  \n");

	  nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory004 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory004 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

      printf("register success\n");
	  strcpy(testData, "1122334455");
	  printf("%s\n", testData);
	  strcpy(testData + 100, "66778899");
	  printf("%s\n", testData + 100);
	  strcpy(testData + 200, "aabbccddeeff");
	  printf("%s\n", testData + 200);
	  strcpy(testData + 230, "testtesttest");
	  printf("%s\n", testData + 230);

	  len = strlen("1122334455") + 1;
	  len1 = strlen("66778899") + 1;
	  len2 = strlen("aabbccddeeff") + 1;
	  len3 = strlen("testtesttest") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_NONE,
          TEEC_NONE,
          TEEC_NONE,
          TEEC_NONE
	);

		operation.params[0].memref.parent = &nonZeroCopysharedMem;
		operation.params[0].memref.offset = 0;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 100;
		operation.params[1].memref.size = len1;
		operation.params[2].memref.parent = &nonZeroCopysharedMem;
		operation.params[2].memref.offset = 200;
		operation.params[2].memref.size = len2;
		operation.params[3].memref.parent = &nonZeroCopysharedMem;
		operation.params[3].memref.offset = 230;
		operation.params[3].memref.size = len2;

		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_SUCCESS){
                  printf("Test_TEEC_RegisterSharedMemory004 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory004 TEEC_OpenSession success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+100);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+200);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+230);
				  TEEC_CloseSession(&session);
		}

		TEEC_ReleaseSharedMemory(&nonZeroCopysharedMem);
		TEEC_FinalizeContext(&context);
}

// exceptional test  nonZeroCopysharedMem.flags = TEEC_MEM_INPUT; but TEEC_MEMREF_PARTIAL_OUTPUT
void Test_TEEC_RegisterSharedMemory005()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2,len3;
      char    testData[256];

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory005 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory005 TEEC_InitializeContext success  \n");

	  nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INPUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory005 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory005 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

      printf("register success\n");
	  strcpy(testData, "1122334455");
	  printf("%s\n", testData);
	  strcpy(testData + 100, "66778899");
	  printf("%s\n", testData + 100);
	  strcpy(testData + 200, "aabbccddeeff");
	  printf("%s\n", testData + 200);
	  strcpy(testData + 230, "testtesttest");
	  printf("%s\n", testData + 230);

	  len = strlen("1122334455") + 1;
	  len1 = strlen("66778899") + 1;
	  len2 = strlen("aabbccddeeff") + 1;
	  len3 = strlen("testtesttest") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_PARTIAL_OUTPUT,
          TEEC_MEMREF_PARTIAL_INPUT,
          TEEC_MEMREF_PARTIAL_OUTPUT,
          TEEC_MEMREF_WHOLE
	);

		operation.params[0].memref.parent = &nonZeroCopysharedMem;
		operation.params[0].memref.offset = 0;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 100;
		operation.params[1].memref.size = len1;
		operation.params[2].memref.parent = &nonZeroCopysharedMem;
		operation.params[2].memref.offset = 200;
		operation.params[2].memref.size = len2;
		operation.params[3].memref.parent = &nonZeroCopysharedMem;
		operation.params[3].memref.offset = 230;
		operation.params[3].memref.size = len2;

		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_ERROR_BAD_PARAMETERS){
                  printf("Test_TEEC_RegisterSharedMemory005 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory005 exceptional test  success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+100);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+200);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+230);
				 // TEEC_CloseSession(&session);
		}

		TEEC_ReleaseSharedMemory(&nonZeroCopysharedMem);
		TEEC_FinalizeContext(&context);
}

// exceptional test  nonZeroCopysharedMem.flags = TEEC_MEM_INPUT; but TEEC_MEMREF_PARTIAL_OUTPUT
void Test_TEEC_RegisterSharedMemory006()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2,len3;
      char    testData[256];

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory006 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory006 TEEC_InitializeContext success  \n");

	  nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_OUTPUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory006 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory006 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

      printf("register success\n");
	  strcpy(testData, "1122334455");
	  printf("%s\n", testData);
	  strcpy(testData + 100, "66778899");
	  printf("%s\n", testData + 100);
	  strcpy(testData + 200, "aabbccddeeff");
	  printf("%s\n", testData + 200);
	  strcpy(testData + 230, "testtesttest");
	  printf("%s\n", testData + 230);

	  len = strlen("1122334455") + 1;
	  len1 = strlen("66778899") + 1;
	  len2 = strlen("aabbccddeeff") + 1;
	  len3 = strlen("testtesttest") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_PARTIAL_OUTPUT,
          TEEC_MEMREF_PARTIAL_INPUT,
          TEEC_MEMREF_PARTIAL_OUTPUT,
          TEEC_MEMREF_WHOLE
	);

		operation.params[0].memref.parent = &nonZeroCopysharedMem;
		operation.params[0].memref.offset = 0;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 100;
		operation.params[1].memref.size = len1;
		operation.params[2].memref.parent = &nonZeroCopysharedMem;
		operation.params[2].memref.offset = 200;
		operation.params[2].memref.size = len2;
		operation.params[3].memref.parent = &nonZeroCopysharedMem;
		operation.params[3].memref.offset = 230;
		operation.params[3].memref.size = len2;

		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_ERROR_BAD_PARAMETERS){
                  printf("Test_TEEC_RegisterSharedMemory006 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory006 exceptional test  success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+100);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+200);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+230);
				 // TEEC_CloseSession(&session);
		}

		TEEC_ReleaseSharedMemory(&nonZeroCopysharedMem);
		TEEC_FinalizeContext(&context);
}

//chixu
void Test_TEEC_RegisterSharedMemory007()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2;
      char    testData[256];
     double cost_time;
   clock_t start,end;

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory007 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory007 TEEC_InitializeContext success  \n");


      sharedMem.size = 1024;
      sharedMem.flags = TEEC_MEM_INOUT;
      result = TEEC_AllocateSharedMemory(
          &context,
          &sharedMem
	  );
      if(result != TEEC_SUCCESS){
          printf("Test_TEEC_RegisterSharedMemory007 allocate mem failed, %x\n", result);
            TEEC_FinalizeContext(&context);
		return ;
	  }else
             {
             printf("Test_TEEC_RegisterSharedMemory007 TEEC_AllocateSharedMemory success\n");
	  }
	  memset(sharedMem.buffer, 0x00, 1024);
         printf("allocat success\n");
	  strcpy(sharedMem.buffer, "1122334455");
	  printf("%s\n", (char*)sharedMem.buffer);
	  strcpy((char*)sharedMem.buffer + 512, "0123456789");
	  printf("%s\n", (char*)sharedMem.buffer + 512);
	  len = strlen("0123456789") + 1;

      nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory007 register mem failed, %x\n", result);
             TEEC_ReleaseSharedMemory(&sharedMem);
            TEEC_FinalizeContext(&context);
		return ;
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory007 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

	printf("register success\n");
	strcpy(testData, "ABCDEFGHIJK");
	printf("%s\n", testData);
	strcpy(testData + 128, "9876543210");
	printf("%s\n", testData + 128);

	len1 = strlen("ABCDEFGHIJK") + 1;
	len2 = strlen("9876543210") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_PARTIAL_INOUT,
          TEEC_MEMREF_PARTIAL_INOUT,
          TEEC_MEMREF_TEMP_INOUT,
          TEEC_VALUE_INOUT
	);

		operation.params[0].memref.parent = &sharedMem;
		operation.params[0].memref.offset = 512;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 128;
		operation.params[1].memref.size = len2;
		operation.params[2].tmpref.buffer = testData;
		operation.params[2].tmpref.size = len1;
		operation.params[3].value.a = 0x1234;
		operation.params[3].value.b = 0x4567;

          //    int j;
	  //     for(j=1;j<500;j++){
	//	   	start=clock();
		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_SUCCESS){
                  printf("Test_TEEC_RegisterSharedMemory007 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory007 TEEC_OpenSession success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)sharedMem.buffer+512);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+128);
				  printf("%s\n", testData);
				  printf("%x %x\n", operation.params[3].value.a, operation.params[3].value.b);
				  TEEC_CloseSession(&session);

		}

	  //     	}
		TEEC_ReleaseSharedMemory(&sharedMem);
		TEEC_FinalizeContext(&context);

}

//chixu
void Test_TEEC_RegisterSharedMemory008()
{
      TEEC_Context context;
      TEEC_Session session;
      TEEC_Operation operation;
      TEEC_SharedMemory sharedMem, sharedMem1;
      TEEC_SharedMemory nonZeroCopysharedMem;
      TEEC_Result result;
      TEEC_UUID svc_id = TEE_SERVICE_ECHO;
      uint32_t len, len1, len2;
      char    testData[256];
      double cost_time;
   clock_t start,end;

       result = TEEC_InitializeContext(
               NULL,
               &context);

      if(result != TEEC_SUCCESS) {
        printf("Test_TEEC_RegisterSharedMemory008 TEEC_InitializeContext faile\n ");
      }else
        printf("Test_TEEC_RegisterSharedMemory008 TEEC_InitializeContext success  \n");


      sharedMem.size = 1024;
      sharedMem.flags = TEEC_MEM_INOUT;
      result = TEEC_AllocateSharedMemory(
          &context,
          &sharedMem
	  );
      if(result != TEEC_SUCCESS){
          printf("Test_TEEC_RegisterSharedMemory008 allocate mem failed, %x\n", result);
	  }else
          {
           printf("Test_TEEC_RegisterSharedMemory008 TEEC_AllocateSharedMemory success\n");
	  }
	  memset(sharedMem.buffer, 0x00, 1024);
         printf("allocat success\n");
	  strcpy(sharedMem.buffer, "1122334455");
	  printf("%s\n", (char*)sharedMem.buffer);
	  strcpy((char*)sharedMem.buffer + 512, "0123456789");
	  printf("%s\n", (char*)sharedMem.buffer + 512);
	  len = strlen("0123456789") + 1;

      nonZeroCopysharedMem.buffer = testData;
      nonZeroCopysharedMem.size = 256;
      nonZeroCopysharedMem.flags = TEEC_MEM_INOUT;

      result = TEEC_RegisterSharedMemory(&context,&nonZeroCopysharedMem);

	if(result != TEEC_SUCCESS) {
           printf("Test_TEEC_RegisterSharedMemory008 register mem failed, %x\n", result);
	}else
	{
	     printf("Test_TEEC_RegisterSharedMemory008 TEEC_RegisterSharedMemory success\n");
	}

	memset(nonZeroCopysharedMem.buffer, 0x00, 256);
	memset(testData, 0x00, 256);

	printf("register success\n");
	strcpy(testData, "ABCDEFGHIJK");
	printf("%s\n", testData);
	strcpy(testData + 128, "9876543210");
	printf("%s\n", testData + 128);

	len1 = strlen("ABCDEFGHIJK") + 1;
	len2 = strlen("9876543210") + 1;

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(
          TEEC_MEMREF_PARTIAL_INOUT,
          TEEC_MEMREF_PARTIAL_INOUT,
          TEEC_MEMREF_TEMP_INOUT,
          TEEC_VALUE_INOUT
	);

		operation.params[0].memref.parent = &sharedMem;
		operation.params[0].memref.offset = 512;
		operation.params[0].memref.size = len;
		operation.params[1].memref.parent = &nonZeroCopysharedMem;
		operation.params[1].memref.offset = 128;
		operation.params[1].memref.size = len2;
		operation.params[2].tmpref.buffer = testData;
		operation.params[2].tmpref.size = len1;
		operation.params[3].value.a = 0x1234;
		operation.params[3].value.b = 0x4567;

             int j;
	       for(j=1;j<1000;j++){
              start=clock();
		result = TEEC_OpenSession(
                   &context,
                   &session,
                   &svc_id,
                   TEEC_LOGIN_PUBLIC,
                   NULL,
                   &operation,
                   NULL
		);

		if(result != TEEC_SUCCESS){
                  printf("Test_TEEC_RegisterSharedMemory008 opensession faild, %x\n", result);
		}else{
		                printf("Test_TEEC_RegisterSharedMemory008 TEEC_OpenSession success\n");
                              printf("sssssession id 0x%x\n", session.session_id);
				  printf("%s\n", (char*)sharedMem.buffer+512);
				  printf("%s\n", (char*)nonZeroCopysharedMem.buffer+128);
				  printf("%s\n", testData);
				  printf("%x %x\n", operation.params[3].value.a, operation.params[3].value.b);
				  TEEC_CloseSession(&session);
				  end=clock();
				  cost_time=(double)(end-start)/CLOCKS_PER_SEC;
                              printf("Time is : %f\n",cost_time);
		}

             }
		TEEC_ReleaseSharedMemory(&sharedMem);
		TEEC_FinalizeContext(&context);

}

/* test write file once, file is 01.txt */
void TEEC_FOpen_test001()
{
    printf("----------TEEC_FOpen_test001 start----------\n", __FUNCTION__);
    int fd;
    int ret;
    int32_t write_size;
    char write_buff[128];
    int len;

    TEEC_InitStorageService();

    fd = TEEC_FOpen("/data/01.txt", TEE_DATA_FLAG_ACCESS_WRITE|TEE_DATA_FLAG_CREATE);
    if (fd == -1) {
        printf("%s:TEEC_FOpen_test001 TEEC_FOpen failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }else{
    printf("TEEC_FOpen_test001 success test: fd=%d\n", fd);
     }
    strcpy(write_buff, "0123456789");
    len = strlen("0123456789");
    write_size = TEEC_FWrite(fd, write_buff, len);
    if ((write_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FOpen_test001 TEEC_FWrite failed,errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }

    ret = TEEC_FClose(fd);
    if (ret == -1) {
        printf("%s: TEEC_FClose failed\n");
        goto error;
    }

    TEEC_UninitStorageService();
    return;
error:
    TEEC_UninitStorageService();


}

/* exception test open file is exception.txt that is not exit */
void TEEC_FOpen_test002()
{
    printf("----------TEEC_FOpen_test002 start----------\n", __FUNCTION__);
    int fd;
    int ret;
    int32_t write_size;
    char write_buff[128];
    int len;

    TEEC_InitStorageService();

    fd = TEEC_FOpen("/data/exception.txt", TEE_DATA_FLAG_ACCESS_READ);
    if (fd == -1) {
        printf("%s:TEEC_FOpen_test002 TEEC_FOpen exception test success, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }else{
    printf("TEEC_FOpen_test002 faile test: fd=%d\n", fd);
       }

    TEEC_UninitStorageService();
    return;
error:
    TEEC_UninitStorageService();


}


/*  exception test open file is exception.txt that is not exit */
void TEEC_FOpen_test003()
{
    printf("----------TEEC_FOpen_test003 start----------\n", __FUNCTION__);
    int fd;
    int ret;
    int32_t write_size;
    char write_buff[128];
    int len;

    TEEC_InitStorageService();

    fd = TEEC_FOpen("/data/06.txt", TEE_DATA_FLAG_ACCESS_WRITE);
    if (fd == -1) {
        printf("%s:TEEC_FOpen_test003 TEEC_FOpen exception test success, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }else{
    printf("TEEC_FOpen_test003 success faile\n", fd);
    }

    TEEC_UninitStorageService();
    return;
error:
    TEEC_UninitStorageService();


}

/*   test open file is exception.txt  TEE_DATA_FLAG_CREATE */
void TEEC_FOpen_test004()
{
    printf("----------TEEC_FOpen_test004 start----------\n", __FUNCTION__);
    int fd;
    int ret;
    int32_t write_size;
    char write_buff[128];
    int len;

    TEEC_InitStorageService();

    fd = TEEC_FOpen("/data/01.txt", TEE_DATA_FLAG_CREATE);
    if (fd == -1) {
        printf("%s:TEEC_FOpen_test004 TEEC_FOpen faile, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }else{
    printf("TEEC_FOpen_test004 success : fd=%d\n", fd);
     }

    TEEC_UninitStorageService();


    return;
error:
    TEEC_UninitStorageService();


}

/*   test open file is EXCLUSIVE.txt  TEE_DATA_FLAG_EXCLUSIVE */
void TEEC_FOpen_test005()
{
    printf("----------TEEC_FOpen_test005 start----------\n", __FUNCTION__);
    int fd;
    int ret;
    int32_t write_size;
    char write_buff[128];
    int len;

    TEEC_InitStorageService();

    fd = TEEC_FOpen("/data/01.txt", TEE_DATA_FLAG_EXCLUSIVE);
    if (fd == -1) {
        printf("%s:exception test success TEEC_FOpen_test005 TEEC_FOpen , errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }else{
    printf("TEEC_FOpen_test005 faile : fd=%d\n", fd);
       }

    TEEC_UninitStorageService();


    return;
error:
    TEEC_UninitStorageService();


}

//right test open-write
void TEEC_FWrite_test001()
{
    printf("----------TEEC_FWrite_test001 start----------\n", __FUNCTION__);
    int fd;
    int ret;
    int32_t write_size;
	 int32_t read_size;
    char write_buff[128];
	char read_buff[128];
    int len;

    TEEC_InitStorageService();

    fd = TEEC_FOpen("write", TEE_DATA_FLAG_CREATE|TEE_DATA_FLAG_ACCESS_WRITE);
    if (fd == -1) {
        printf("%s:TEEC_FWrite_test001 TEEC_FOpen faile, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }else{
    printf("TEEC_FWrite_test001 success test: fd=%d\n", fd);
      }
 strcpy(write_buff, "11111");
    len = strlen("11111");
    write_size = TEEC_FWrite(fd, write_buff, len);
    if ((write_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FWrite failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    strcpy(write_buff, "22222");
    len = strlen("22222");
    write_size = TEEC_FWrite(fd, write_buff, len);
    if ((write_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FWrite failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    strcpy(write_buff, "33333");
    len = strlen("33333");
    write_size = TEEC_FWrite(fd, write_buff, len);
    if ((write_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FWrite failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
	ret = TEEC_FClose(fd);
    if (ret == -1) {
        printf("%s: TEEC_FClose failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }


	fd = TEEC_FOpen("write", TEE_DATA_FLAG_ACCESS_READ);
    if (fd == -1) {
        printf("%s: TEEC_FOpen failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("test: fd=%d\n", fd);

    memset(read_buff, 0x00, 128);
    len = 20;
    read_size = TEEC_FRead(fd, read_buff, len);
    if ((read_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FRead failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("read_size=%d, read_buff=%s\n", read_size, read_buff);

    TEEC_UninitStorageService();
    return;
error:
    TEEC_UninitStorageService();


}

/* test write file once, simultaneity, file is 03.txt & 04.txt */
void TEEC_FWrite_test002()
{
    printf("----------TEEC_FWrite_test002 test start---------\n", __FUNCTION__);
    int fd3,fd4;
    int ret;
    int32_t write_size;
    char write_buff[128];
    int len;

    TEEC_InitStorageService();


    fd3 = TEEC_FOpen("/data/03.txt", TEE_DATA_FLAG_ACCESS_WRITE|TEE_DATA_FLAG_CREATE);
    if (fd3 == -1) {
        printf("%s: TEEC_FOpen failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("test: fd3=%d\n", fd3);

    fd4 = TEEC_FOpen("/data/04.txt", TEE_DATA_FLAG_ACCESS_WRITE|TEE_DATA_FLAG_CREATE);
    if (fd4 == -1) {
        printf("%s: TEEC_FOpen failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("test: fd4=%d\n", fd4);

    strcpy(write_buff, "this is file 03.txt");
    len = strlen("this is file 03.txt");
    write_size = TEEC_FWrite(fd3, write_buff, len);
    if ((write_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FWrite failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }

    strcpy(write_buff, "this is file 04.txt");
    len = strlen("this is file 04.txt");
    write_size = TEEC_FWrite(fd4, write_buff, len);
    if ((write_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FWrite failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }

    ret = TEEC_FClose(fd3);
    if (ret == -1) {
        printf("%s: TEEC_FClose failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }

    ret = TEEC_FClose(fd4);
    if (ret == -1) {
        printf("%s: TEEC_FClose failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }

    TEEC_UninitStorageService();
    return;
error:
    TEEC_UninitStorageService();

}


/* test read file once, simultaneity, file is 03.txt & 04.txt */
void TEEC_FRead_test001()
{
    printf("----------TEEC_FRead_test001 start----------\n", __FUNCTION__);
    int fd3,fd4;
    int ret;
    int32_t read_size;
    char read_buff[128];
    int len;

    TEEC_InitStorageService();

    fd3 = TEEC_FOpen("/data/03.txt", TEE_DATA_FLAG_ACCESS_READ);
    if (fd3 == -1) {
        printf("%s: TEEC_FOpen failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("test: fd3=%d\n", fd3);

    fd4 = TEEC_FOpen("/data/04.txt", TEE_DATA_FLAG_ACCESS_READ);
    if (fd4 == -1) {
        printf("%s: TEEC_FOpen failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("test: fd4=%d\n", fd4);

    memset(read_buff, 0x00, 128);
    len = strlen("this is file 03.txt");
    read_size = TEEC_FRead(fd3, read_buff, len);
    if ((read_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FRead failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("read_size=%d, read_buff=%s\n", read_size, read_buff);

    memset(read_buff, 0x00, 128);
    len = strlen("this is file 04.txt");
    read_size = TEEC_FRead(fd4, read_buff, len);
    if ((read_size !=len) && (TEEC_GetFErr() != TEEC_SUCCESS)){
        printf("%s: TEEC_FRead failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }
    printf("read_size=%d, read_buff=%s\n", read_size, read_buff);

    ret = TEEC_FClose(fd3);
    if (ret == -1) {
        printf("%s: TEEC_FClose failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }

    ret = TEEC_FClose(fd4);
    if (ret == -1) {
        printf("%s: TEEC_FClose failed, errno=0x%x\n", __FUNCTION__, TEEC_GetFErr());
        goto error;
    }


    TEEC_UninitStorageService();
    return;
error:
    TEEC_UninitStorageService();

}
int main(void)
{

     // bindCPU(0);
  /*    Test_TEEC_InitializeContext001();
      Test_TEEC_InitializeContext002();
     //// Test_TEEC_InitializeContext003();  É¾µô
      Test_TEEC_OpenSession001();
      Test_TEEC_OpenSession002();
     //// Test_TEEC_OpenSession003();      É¾µô
      Test_TEEC_OpenSession004();
      Test_TEEC_InvokeCommand001();
      Test_TEEC_InvokeCommand002();
      Test_TEEC_InvokeCommand003();
      Test_TEEC_InvokeCommand004();
	  Test_TEEC_InvokeCommand005();
      Test_TEEC_InvokeCommand006();
	  Test_TEEC_InvokeCommand007();
      Test_TEEC_InvokeCommand008();
	  Test_TEEC_InvokeCommand009();
	  Test_TEEC_InvokeCommand010();
	 Test_TEEC_AllocateSharedMemory01();
	  Test_TEEC_AllocateSharedMemory02();
	  Test_TEEC_AllocateSharedMemory03();
	  Test_TEEC_AllocateSharedMemory04();
	  Test_TEEC_AllocateSharedMemory05();
	  Test_TEEC_AllocateSharedMemory06();
	  Test_TEEC_AllocateSharedMemory07();
	  Test_TEEC_AllocateSharedMemory08();
	  Test_TEEC_AllocateSharedMemory09();
	  Test_TEEC_AllocateSharedMemory010();
	  Test_TEEC_AllocateSharedMemory011();
	  Test_TEEC_AllocateSharedMemory012();
	  Test_TEEC_AllocateSharedMemory013();
	  Test_TEEC_RegisterSharedMemory001();
	 Test_TEEC_RegisterSharedMemory002();
	 Test_TEEC_RegisterSharedMemory003();
        Test_TEEC_RegisterSharedMemory004();
        Test_TEEC_RegisterSharedMemory005();
        Test_TEEC_RegisterSharedMemory006(); */
   /*
   int i;
   for(i=1;i<1000;i++){
   Test_TEEC_RegisterSharedMemory007();  //////chixu
     }*/

     //Test_TEEC_RegisterSharedMemory008();  //////chixu

     //  Test_pthread_OpenSession();    //////bingfa
     //Test_pthread_InvokeCommand(); //////bingfa
     //Test_TEEC_InvokeCommand_BigBuffer();

	 /*
	 int i=1;
	 while(i>0)
         {
          Test_TEEC_RegisterSharedMemory007();
	 }
	 */

	 /*
	 int i=1;
	 while(i>0)
         {
          Test_TEEC_InvokeCommand001();
	 }*/

	 TEEC_FOpen_test001();
	 TEEC_FOpen_test002();
	TEEC_FOpen_test003();
	TEEC_FOpen_test004();
	 TEEC_FOpen_test005();
	TEEC_FWrite_test001();
	TEEC_FWrite_test002();
	TEEC_FRead_test001();




	  return 0;
}
