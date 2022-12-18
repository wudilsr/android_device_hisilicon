#include "tee_mem_mgmt_api.h"
#include "tee_internal_api.h"
#include "ta_framework.h"
#include "tee_trusted_storage_api.h"
#include "ta_framework.h"
#include <sre_mem.h>
#include "tee_fs.h"
#define TA_DEBUG
#include "tee_log.h"

uint32_t sstrlen(char* s)
{
    char *sc;
    for(sc=s; *sc!='\0';++sc)
    {
    }
    return sc-s;
}

static void print_buffer(char* p, uint32_t size)
{
    uint32_t i;
    char c;

    uart_printf("\n");
    for(i=0; i<size; i++){
        uart_printf("%d ", *(p+i));
    }
    uart_printf("\n");
}

//right params test
void TEE_AllocateTransientObject_test001()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_AllocateTransientObject_test001 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_AllocateTransientObject_test001 test faile\n");
		}else {
		ta_debug("------------TEE_AllocateTransientObject_test001 test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

}

//size=0x00000801 >0x00000800 test
void TEE_AllocateTransientObject_test002()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_AllocateTransientObject_test002 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00001001,(&first_object));
	if(result!=TEE_ERROR_BAD_PARAMETERS)
		{
		  ta_debug("------------TEE_AllocateTransientObject_test002 test faile\n,0x%x",result);
		}else {
		ta_debug("------------exception test success TEE_AllocateTransientObject_test002 test success\n");

			}

}


//size=0x00000801 >0x00000800 test
void TEE_AllocateTransientObject_test003()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_AllocateTransientObject_test003 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,NULL);
	if(result!=TEE_ERROR_BAD_PARAMETERS)
		{
		  ta_debug("------------TEE_AllocateTransientObject_test003 test faile\n");
		}else {
		ta_debug("------------TEE_AllocateTransientObject_test003 test success\n");

			}

}

//right params test
void TEE_InitRefAttribute_test001()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_InitRefAttribute_test001 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_InitRefAttribute_test001 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_InitRefAttribute_test001 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
     //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(first_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject test success\n");}
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);

        }

//buffer is null test
void TEE_PopulateTransientObject_test001()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_PopulateTransientObject_test001 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test001 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test001 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
        //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(NULL, NULL, 1);
	if(result!=TEE_ERROR_BAD_PARAMETERS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test001 TEE_PopulateTransientObject buffer is null test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test001 TEE_PopulateTransientObject buffer is null  test success\n");}
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);

        }

//buffer is null test
void TEE_PopulateTransientObject_test002()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_PopulateTransientObject_test002 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test002 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test002 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
       //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(first_object, aes_attribute, 6);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test002 TEE_PopulateTransientObject number  exception test success\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test002 TEE_PopulateTransientObject number  exception test faile\n");}


        }


//exception test closeobject then populate
void TEE_PopulateTransientObject_test003()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_PopulateTransientObject_test003 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test003 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test003 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
      //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	TEE_CloseObject( first_object);
/*
	result=TEE_PopulateTransientObject(first_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test003 test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test003 test success\n");}

    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
*/
        }

//exception test init object then populate
void TEE_PopulateTransientObject_test004()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="------And finally we \n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_PopulateTransientObject_test004 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test004 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test004 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(first_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test004 test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test004 test success\n");}
    ta_debug("---1 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);

	//
	 TEE_Attribute *aes_attribute2;
    aes_attribute2 = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute2 == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute2, TEE_ATTR_SECRET_VALUE, p_buffer,(size_t)strlen(p_buffer));
    ta_debug("buffer2 of attribute is %s \n",aes_attribute2->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute2->content.ref.length);

	result=TEE_PopulateTransientObject(first_object, aes_attribute2, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_PopulateTransientObject_test004 test faile\n");
		}else {
		ta_debug("------------TEE_PopulateTransientObject_test004 test success\n");}

    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("---2 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);

        }


//right params test
void TEE_GetObjectBufferAttribute_test001()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_GetObjectBufferAttribute_test001 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_GetObjectBufferAttribute_test001 test faile\n");
		}else {
		ta_debug("------------TEE_GetObjectBufferAttribute_test001 test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
      //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

    TEE_PopulateTransientObject(first_object, aes_attribute, 1);
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);

    uint32_t get_ret;
    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    get_ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(get_ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("buffer of attribute is %s \n",testget_buff);
        ta_debug("lengrh of attribute is 0x%x \n",*size);
    }
}

//objectUsage right is change test deny right
void TEE_GetObjectBufferAttribute_test002()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_GetObjectBufferAttribute_test002 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_GetObjectBufferAttribute_test002 test faile\n");
		}else {
		ta_debug("------------TEE_GetObjectBufferAttribute_test002 test success\n");
   /* ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);*/
			}

    TEE_Attribute *aes_attribute;
       //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));
 /*
    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);
*/
    TEE_PopulateTransientObject(first_object, aes_attribute, 1);
 /*
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
    */
    uint32_t get_ret;
    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    get_ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(get_ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("buffer of attribute is %s \n",testget_buff);
        ta_debug("lengrh of attribute is 0x%x \n",*size);
    }

	TEE_CloseObject( first_object);
	/*
    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT |TEE_USAGE_MAC | TEE_USAGE_SIGN |TEE_USAGE_VERIFY |TEE_USAGE_DERIVE  ;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("----------objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    get_ret = TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(get_ret == TEE_SUCCESS){
        testget_buff1[*size]='\0';
        ta_debug("-----------buffer of attribute is %s \n",testget_buff1);
        ta_debug("------------lengrh of attribute is 0x%x \n",*size1);
    }
    else{
        ta_debug("-------------not have permission\n");
    }
    ta_debug("----------------FreeTransient is end! \n");
    TEE_Free((void*)aes_attribute);
    */

}


//exception test not ini object
void TEE_GetObjectBufferAttribute_test003()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_GetObjectBufferAttribute_test003 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_GetObjectBufferAttribute_test003 test faile\n");
		}else {
		ta_debug("------------TEE_GetObjectBufferAttribute_test003 test exception test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}


    uint32_t get_ret;
    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    get_ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(get_ret == TEE_SUCCESS){
		ta_debug("------------TEE_GetObjectBufferAttribute_test003 test faile\n");

    }else{
         ta_debug("TEE_GetObjectBufferAttribute_test003 exception test success\n");
		// testget_buff[*size]='\0';
       // ta_debug("buffer of attribute is %s \n",testget_buff);
       // ta_debug("lengrh of attribute is 0x%x \n",*size);
	}
}



//right params write -read
void TEE_CreatePersistentObject_test001()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_CreatePersistentObject_test001 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test001 TEE_CreatePersistentObject success\n");

}

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test001 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test001 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test001 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test001 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);
	//tee_storage_exit();

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test001 test end\n");

	}

//right params read -read
void TEE_CreatePersistentObject_test002()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_CreatePersistentObject_test002 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test002 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test002 TEE_CreatePersistentObject success\n");

}

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test002 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test002 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test002 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test002 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test002 test end\n");

}

//right params read/write -read
void TEE_CreatePersistentObject_test003()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_CreatePersistentObject_test003 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rw_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test003 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test003 TEE_CreatePersistentObject success\n");

}

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test003 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test003 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test003 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test003 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

   // TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test003 test end\n");

}

//right params write -write
void TEE_CreatePersistentObject_test004()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=80;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test004 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_CreatePersistentObject success\n");

}

      result=TEE_WriteObjectData(first_object,writeData,(size_t)(sstrlen((char*)writeData)));
        if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_WriteObjectData faile\n");
		}else
			{
               ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_WriteObjectData success\n");
		}

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test004 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test004 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

   // TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test004 test end\n");

}

//faile test read -write
void TEE_CreatePersistentObject_test005()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test005 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_CreatePersistentObject success\n");

}

      result=TEE_WriteObjectData(first_object,writeData,(size_t)(sstrlen((char*)writeData)));
           if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_WriteObjectData deny test success\n");
		}else
			{
               ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_WriteObjectData faile\n");
		}

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test005 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test005 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test005 test end\n");

}


// test read/write -write
void TEE_CreatePersistentObject_test006()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test006 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rw_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_CreatePersistentObject success\n");

}

      result=TEE_WriteObjectData(first_object,writeData,(size_t)(sstrlen((char*)writeData)));
          if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_WriteObjectData faile\n");
		}else
			{
               ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_WriteObjectData success\n");
		}

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test006 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test006 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

   // TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test006 test end\n");

}


// test read/write -truncate
void TEE_CreatePersistentObject_test007()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test007 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rw_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,10);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_TruncateObjectData faile\n");
	  }else{
               ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_TruncateObjectData success\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test007 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test007 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test007 test end\n");

}

// test write -truncate
void TEE_CreatePersistentObject_test008()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test008 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,10);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_TruncateObjectData faile\n");
	  }else{
               ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_TruncateObjectData success\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test008 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test008 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test008 test end\n");

}

// test read -truncate
void TEE_CreatePersistentObject_test009()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test009 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,10);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_TruncateObjectData deny test success\n");
	  }else{
               ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_TruncateObjectData faile\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test009 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test009 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test009 test end\n");

}

// test write -truncate size>object
void TEE_CreatePersistentObject_test010()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CreatePersistentObject_test010 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,100);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_TruncateObjectData faile\n");
	  }else{
               ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_TruncateObjectData success\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CreatePersistentObject_test010 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CreatePersistentObject_test010 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_CreatePersistentObject_test008 test end\n");

}

// test write -close and delete object w_meta_flags
void TEE_CloseAndDeletePersistentObject_test001()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CloseAndDeletePersistentObject_test001 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,10);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_TruncateObjectData faile\n");
	  }else{
               ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_TruncateObjectData success\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), w_meta_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CloseAndDeletePersistentObject_test001 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_ReadObjectData faile\n");
	}

    //TEE_CloseObject( first_object);

    TEE_CloseAndDeletePersistentObject(first_object);

	open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_OpenPersistentObject flag test success\n");
}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test001 TEE_OpenPersistentObject faile\n");
}

     ta_debug("------------TEE_CloseAndDeletePersistentObject_test001 test end\n");

}


// except test write -close and delete object r_flags
void TEE_CloseAndDeletePersistentObject_test002()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CloseAndDeletePersistentObject_test002 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,10);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_TruncateObjectData faile\n");
	  }else{
               ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_TruncateObjectData success\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CloseAndDeletePersistentObject_test002 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_ReadObjectData faile\n");
	}

    //TEE_CloseObject( first_object);

    TEE_CloseAndDeletePersistentObject(first_object);

	open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test002 TEE_OpenPersistentObject success\n");
}

     ta_debug("------------TEE_CloseAndDeletePersistentObject_test002 test end\n");
	 TEE_CloseObject( first_object);

}


// except test write -close and delete object w_flags
void TEE_CloseAndDeletePersistentObject_test003()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mqqq This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"---mq This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_CloseAndDeletePersistentObject_test003 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_CreatePersistentObject success\n");

}

      result=TEE_TruncateObjectData(first_object,10);
	  if(result!=TEE_SUCCESS){
                ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_TruncateObjectData faile\n");
	  }else{
               ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_TruncateObjectData success\n");
	  }

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), w_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_CloseAndDeletePersistentObject_test003 TEE_ReadObjectData  faile!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
    }else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_ReadObjectData success\n");
	}

    //TEE_CloseObject( first_object);

    TEE_CloseAndDeletePersistentObject(first_object);

	open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), w_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test003 TEE_OpenPersistentObject success\n");
}

     ta_debug("------------TEE_CloseAndDeletePersistentObject_test003 test end\n");
	 TEE_CloseObject( first_object);

}

void TEE_CloseAndDeletePersistentObject_test004()
{
uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_CloseAndDeletePersistentObject_test004 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test004 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CloseAndDeletePersistentObject_test004 TEE_CreatePersistentObject success\n");
ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
    ta_debug("---1 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);//没有分配空间

}

    //TEE_CloseObject( first_object);

}

// right params flag is meta
void TEE_RenamePersistentObject_test001()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META ,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="---mq rename test This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID=NULL;
    void* trunc_objectID=NULL;
    char  write_buffer[255];
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_RenamePersistentObject_test001 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_meta_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_CreatePersistentObject success\n");
strcpy(write_buffer,first_object->dataName);
ta_debug("----------------new name is %s \n",write_buffer);

}


	  result=TEE_RenamePersistentObject(first_object, rename_objectID, (size_t)strlen(rename_objectID));
    if(result != TEE_SUCCESS)
    {
        ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_RenamePersistentObject faile\n");
    }else{
         ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_RenamePersistentObject success\n");
		 strcpy(read_buffer,first_object->dataName);
		 ta_debug("----------------new name is %s \n",read_buffer);
		 ta_debug("----------------len is %x \n",strlen(rename_objectID));
	}


    TEE_CloseObject( first_object);


}


// exception test  flag is write
void TEE_RenamePersistentObject_test002()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META ,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="---mq rename test This a sierraware\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID=NULL;
    void* trunc_objectID=NULL;
    char  write_buffer[255];
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_RenamePersistentObject_test002 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_RenamePersistentObject_test002 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_RenamePersistentObject_test002 TEE_CreatePersistentObject success\n");
strcpy(write_buffer,first_object->dataName);
ta_debug("----------------new name is %s \n",write_buffer);

}


	  result=TEE_RenamePersistentObject(first_object, rename_objectID, (size_t)strlen(rename_objectID));
    if(result != TEE_SUCCESS)
    {
        ta_debug(" ------------------exception test success TEE_RenamePersistentObject_test002 TEE_RenamePersistentObject success\n");
    }else{
         ta_debug(" ------------------exception test faile TEE_RenamePersistentObject_test002 TEE_RenamePersistentObject faile\n");
		 strcpy(read_buffer,first_object->dataName);
		 ta_debug("----------------new name is %s \n",read_buffer);
	}


    TEE_CloseObject( first_object);


}



// exception test  flag is write
void TEE_RenamePersistentObject_test003()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META ,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="---mq rename test This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID=NULL;
    void* trunc_objectID=NULL;
    char  write_buffer[255];
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_RenamePersistentObject_test003 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_RenamePersistentObject_test003 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_RenamePersistentObject_test003 TEE_CreatePersistentObject success\n");
strcpy(write_buffer,first_object->dataName);
ta_debug("----------------new name is %s \n",write_buffer);

}


	  result=TEE_RenamePersistentObject(first_object, rename_objectID, (size_t)strlen(rename_objectID));
    if(result != TEE_SUCCESS)
    {
        ta_debug(" ------------------exception test success TEE_RenamePersistentObject_test003 TEE_RenamePersistentObject success\n");
    }else{
         ta_debug(" ------------------exception test faile TEE_RenamePersistentObject_test003 TEE_RenamePersistentObject faile\n");
		 strcpy(read_buffer,first_object->dataName);
		 ta_debug("----------------new name is %s \n",read_buffer);
	}


    TEE_CloseObject( first_object);


}


// exception test size>64
void TEE_RenamePersistentObject_test004()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META ,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/newaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt";
    void* initialData="---mq rename test This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID=NULL;
    void* trunc_objectID=NULL;
    char  write_buffer[255];
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_RenamePersistentObject_test004 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_meta_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_RenamePersistentObject_test004 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_RenamePersistentObject_test004 TEE_CreatePersistentObject success\n");
strcpy(write_buffer,first_object->dataName);
ta_debug("----------------new name is %s \n",write_buffer);

}


	  result=TEE_RenamePersistentObject(first_object, rename_objectID, (size_t)strlen(rename_objectID));
    if(result != TEE_SUCCESS)
    {
        ta_debug(" ------------------TEE_RenamePersistentObject_test004 TEE_RenamePersistentObject exception test success\n");
    }else{
         ta_debug(" ------------------TEE_RenamePersistentObject_test004 TEE_RenamePersistentObject faile\n");
		 strcpy(read_buffer,first_object->dataName);
		 ta_debug("----------------new name is %s \n",read_buffer);
		 ta_debug("----------------len is %x \n",strlen(rename_objectID));
	}


    TEE_CloseObject( first_object);


}

//right params
void TEE_GetObjectInfo_test001()
{
uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_GetObjectInfo_test001 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_GetObjectInfo_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_GetObjectInfo_test001 TEE_CreatePersistentObject success\n");

}
	TEE_ObjectInfo *objectinfo_test;
    objectinfo_test = (TEE_ObjectInfo*)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    TEE_GetObjectInfo(first_object, objectinfo_test);
    ta_debug("--------objectinfo objectType is 0x%x \n",objectinfo_test->objectType);
    ta_debug("--------objectinfo objectSize is 0x%x \n",objectinfo_test->objectSize);
    ta_debug("-------objectinfo maxObjectsize is 0x%x \n",objectinfo_test->maxObjectSize);
    ta_debug("---------objectinfo objectUsage is 0x%x \n",objectinfo_test->objectUsage);
    ta_debug("--------objectinfo dataSize is 0x%x \n",objectinfo_test->dataSize);
    ta_debug("----------objectinfo dataPosition is 0x%x \n",objectinfo_test->dataPosition);
    ta_debug("-----------objectinfo handleFlags is 0x%x \n",objectinfo_test->handleFlags);
    TEE_CloseObject( first_object);
    TEE_Free( objectinfo_test);
     ta_debug("------------TEE_GetObjectInfo_test001 test end\n");
}

//right params flag=r_flags
void TEE_GetObjectInfo_test002()
{
uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_GetObjectInfo_test002 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_GetObjectInfo_test002 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_GetObjectInfo_test002 TEE_CreatePersistentObject success\n");

}
	TEE_ObjectInfo *objectinfo_test;
    objectinfo_test = (TEE_ObjectInfo*)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    TEE_GetObjectInfo(first_object, objectinfo_test);
    ta_debug("--------objectinfo objectType is 0x%x \n",objectinfo_test->objectType);
    ta_debug("--------objectinfo objectSize is 0x%x \n",objectinfo_test->objectSize);
    ta_debug("-------objectinfo maxObjectsize is 0x%x \n",objectinfo_test->maxObjectSize);
    ta_debug("---------objectinfo objectUsage is 0x%x \n",objectinfo_test->objectUsage);
    ta_debug("--------objectinfo dataSize is 0x%x \n",objectinfo_test->dataSize);
    ta_debug("----------objectinfo dataPosition is 0x%x \n",objectinfo_test->dataPosition);
    ta_debug("-----------objectinfo handleFlags is 0x%x \n",objectinfo_test->handleFlags);
    TEE_CloseObject( first_object);
    TEE_Free( objectinfo_test);
     ta_debug("------------TEE_GetObjectInfo_test002 test end\n");
}

//right params flag=w_meta_flags
void TEE_GetObjectInfo_test003()
{
uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_GetObjectInfo_test003 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_meta_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_GetObjectInfo_test003 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_GetObjectInfo_test003 TEE_CreatePersistentObject success\n");

}
	TEE_ObjectInfo *objectinfo_test;
    objectinfo_test = (TEE_ObjectInfo*)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    TEE_GetObjectInfo(first_object, objectinfo_test);
    ta_debug("--------objectinfo objectType is 0x%x \n",objectinfo_test->objectType);
    ta_debug("--------objectinfo objectSize is 0x%x \n",objectinfo_test->objectSize);
    ta_debug("-------objectinfo maxObjectsize is 0x%x \n",objectinfo_test->maxObjectSize);
    ta_debug("---------objectinfo objectUsage is 0x%x \n",objectinfo_test->objectUsage);
    ta_debug("--------objectinfo dataSize is 0x%x \n",objectinfo_test->dataSize);
    ta_debug("----------objectinfo dataPosition is 0x%x \n",objectinfo_test->dataPosition);
    ta_debug("-----------objectinfo handleFlags is 0x%x \n",objectinfo_test->handleFlags);
    TEE_CloseObject( first_object);
    TEE_Free( objectinfo_test);
     ta_debug("------------TEE_GetObjectInfo_test003 test end\n");
}


//right params
void TEE_ResetTransientObject_test001()
	{
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="--- mq This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;

 ta_debug("------------TEE_ResetTransientObject_test001 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_ResetTransientObject_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_ResetTransientObject_test001 TEE_CreatePersistentObject success\n");
 ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

}
TEE_ResetTransientObject(first_object);

    TEE_CloseObject( first_object);

    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, strlen(create_objectID), r_flags, (&first_object));
if(open_write_retval!=TEE_SUCCESS){
ta_debug(" ------------------TEE_ResetTransientObject_test001 TEE_OpenPersistentObject faile\n");
}else{
ta_debug(" ------------------TEE_ResetTransientObject_test001 TEE_OpenPersistentObject success\n");
}
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS){
        ta_debug("------------TEE_ResetTransientObject_test001 TEE_ReadObjectData  success!\n");
        read_buffer[*count]='\0';
        ta_debug("-----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("---------------read is end  \n");
        ta_debug("--------------read count is 0x%x  \n",*count);
        ta_debug("----------------read content is %s \n",read_buffer);
         ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
    }else{
ta_debug(" ------------------TEE_ResetTransientObject_test001 TEE_ReadObjectData faile\n");
	}

    TEE_CloseObject( first_object);

    //TEE_CloseAndDeletePersistentObject(first_object);
     ta_debug("------------TEE_ResetTransientObject_test001 test end\n");

	}


//right params
void TEE_ResetTransientObject_test002()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_ResetTransientObject_test002 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_ResetTransientObject_test002 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_ResetTransientObject_test002 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

	ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
			}

    TEE_Attribute *aes_attribute;
       //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(first_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_ResetTransientObject_test002 TEE_PopulateTransientObject number  test faile\n");
		}else {
		ta_debug("------------TEE_ResetTransientObject_test002 TEE_PopulateTransientObject number  test success\n");}
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
	ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

   TEE_ResetTransientObject(first_object);

	  ta_debug("------attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
	ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

        }

//right params
void TEE_ResetTransientObject_test003()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="------mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_ResetTransientObject_test003 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_ResetTransientObject_test003 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_ResetTransientObject_test003 TEE_AllocateTransientObject  test success\n");
    ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
			}

    TEE_Attribute *aes_attribute;
       //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(first_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_ResetTransientObject_test003 TEE_PopulateTransientObject number  test faile\n");
		}else {
		ta_debug("------------TEE_ResetTransientObject_test003 TEE_PopulateTransientObject number  test success\n");}
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
	ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

   TEE_ResetTransientObject(first_object);

	  ta_debug("------1 attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
	ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

	TEE_CloseObject( first_object);

        }

//right test
void TEE_CopyObjectAttributes_test001()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;
    TEE_ObjectHandle third_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;

    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test001 TEE_AllocateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test001 TEE_AllocateTransientObject test success\n");
		ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

			}

	//
	 result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&third_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test001 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test001 TEE_AllocateTransientObject  test success\n");
			}

    TEE_Attribute *aes_attribute;

    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));

    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);

	result=TEE_PopulateTransientObject(third_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test001 test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test001 test success\n");
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",third_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",third_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",third_object->Attribute->content.ref.length);}
	//

	crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, third_object , initialData, (size_t)(sstrlen((char*)initialData)), (&second_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CopyObjectAttributes_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CopyObjectAttributes_test001 TEE_CreatePersistentObject success\n");

}
      TEE_CopyObjectAttributes(first_object,second_object);

	  ta_debug("------objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);
	ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);


}

//exception test  transient to transient
void TEE_CopyObjectAttributes_test002()
{
 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;
    TEE_ObjectHandle third_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;

	//
	 result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&third_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test002 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test002 TEE_AllocateTransientObject  test success\n");
			}

    TEE_Attribute *aes_attribute;

    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));



	result=TEE_PopulateTransientObject(third_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test002  TEE_PopulateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test002 TEE_PopulateTransientObject test success\n");

    ta_debug("buffer of attribute is %s \n",third_object->Attribute->content.ref.buffer);
    }

	result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test001 TEE_AllocateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test001 TEE_AllocateTransientObject test success\n");

    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);

			}

		TEE_CopyObjectAttributes(first_object,third_object);

    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);




}


//exception test transient copy to persistent
void TEE_CopyObjectAttributes_test003()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get \n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;
    TEE_ObjectHandle third_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;

    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test003 TEE_AllocateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test003 TEE_AllocateTransientObject test success\n");

			}
		TEE_Attribute *aes_attribute2;

    aes_attribute2 = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute2 == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute2, TEE_ATTR_SECRET_VALUE, attrsbuffer,(size_t)strlen(attrsbuffer));



	result=TEE_PopulateTransientObject(first_object, aes_attribute2, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test003 test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test003 test success\n");

    ta_debug("---1 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
   }

	//
	 result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&third_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test003 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test003 TEE_AllocateTransientObject  test success\n");
			}

    TEE_Attribute *aes_attribute;

    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));



	result=TEE_PopulateTransientObject(third_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test003 test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test003 test success\n");

    ta_debug(" buffer of attribute is %s \n",third_object->Attribute->content.ref.buffer);
    }
	//

	crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, third_object , initialData, (size_t)(sstrlen((char*)initialData)), (&second_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_CopyObjectAttributes_test003 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_CopyObjectAttributes_test003 TEE_CreatePersistentObject success\n");
ta_debug("---2 second_object buffer of attribute is %s \n",second_object->Attribute->content.ref.buffer);
}



      TEE_CopyObjectAttributes(second_object,first_object);
ta_debug("---3 second_object buffer of attribute is %s \n",second_object->Attribute->content.ref.buffer);


}

//exception test  destobject is initialized
void TEE_CopyObjectAttributes_test004()
{
 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get \n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;
    TEE_ObjectHandle third_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;

	//
	 result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&third_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test004 TEE_AllocateTransientObject  test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test004 TEE_AllocateTransientObject  test success\n");
			}

    TEE_Attribute *aes_attribute;

    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));


	result=TEE_PopulateTransientObject(third_object, aes_attribute, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test004  TEE_PopulateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test004 TEE_PopulateTransientObject test success\n");

    ta_debug("---1 buffer of attribute is %s \n",third_object->Attribute->content.ref.buffer);
    }

	result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test004 TEE_AllocateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test004 TEE_AllocateTransientObject test success\n");

    ta_debug("---2 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);

			}
		//
		 TEE_Attribute *aes_attribute2;

    aes_attribute2 = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute2 == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute2, TEE_ATTR_SECRET_VALUE, attrsbuffer,(size_t)strlen(attrsbuffer));


	result=TEE_PopulateTransientObject(first_object, aes_attribute2, 1);
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_CopyObjectAttributes_test004  TEE_PopulateTransientObject test faile\n");
		}else {
		ta_debug("------------TEE_CopyObjectAttributes_test004 TEE_PopulateTransientObject test success\n");

    ta_debug("---3 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    }
//
		TEE_CopyObjectAttributes(first_object,third_object);

    ta_debug("----4 buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);

}

//right params
void TEE_RestrictObjectUsage_test001()
{
   uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="/data/new.txt";
    void* initialData="This a sierraware created sample initial data\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID="/test.dir/delete.txt";
    void* trunc_objectID="/test.dir/truncate.txt";
    char  write_buffer[255]={"This a test string\n"};
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="This will get populated sometimes in the test fn\n";
    void* p_buffer="And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="---mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=46;



    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;

    TEE_Whence whence;
    whence=0x00000000;
    TEEC_Result result;


    ta_debug("------------TEE_RestrictObjectUsage_test001 test start\n");
    result=TEE_AllocateTransientObject(TEE_TYPE_AES, 0x00000800,(&first_object));
	if(result!=TEE_SUCCESS)
		{
		  ta_debug("------------TEE_RestrictObjectUsage_test001 test faile\n");
		}else {
		ta_debug("------------TEE_RestrictObjectUsage_test001 test success\n");
   /* ta_debug("objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);*/
			}

    TEE_Attribute *aes_attribute;
        //need to allocate
    aes_attribute = (TEE_Attribute*)TEE_Malloc(sizeof(TEE_Attribute),0);
    if(aes_attribute == NULL) {
        ta_error("not available to allocate \n");
        return TEE_ERROR_OUT_OF_MEMORY;
    }
    TEE_InitRefAttribute(aes_attribute, TEE_ATTR_SECRET_VALUE, attr_buffer,(size_t)strlen(attr_buffer));
 /*
    ta_debug("Initattribute is end! \n");
    ta_debug("attribute ID is 0x%x \n",aes_attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",aes_attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",aes_attribute->content.ref.length);
*/
    TEE_PopulateTransientObject(first_object, aes_attribute, 1);
 /*
    ta_debug("Populate is end! \n");
    ta_debug("attribute ID is 0x%x \n",first_object->Attribute->attributeID);
    ta_debug("buffer of attribute is %s \n",first_object->Attribute->content.ref.buffer);
    ta_debug("lengrh of attribute is 0x%x \n",first_object->Attribute->content.ref.length);
    */
    uint32_t get_ret;
    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    get_ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(get_ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
         ta_debug("----------1 objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    }


    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT ;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("----------2 objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
   objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_EXTRACTABLE ;
   TEE_RestrictObjectUsage(first_object, objectUsage);
   ta_debug("----------3 objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);

    TEE_Free((void*)aes_attribute);


}

//memory part


//rihgt param
void Malloc_test_001(void)
{
    char *buffer1=NULL;
    int32_t i, ret;

    ta_debug("-------- malloc test hint = 0 -------\n");
    buffer1 = TEE_Malloc(16, 0);
    if(buffer1){
        ta_debug("Malloc_test_001 success, buffer:");
        print_buffer(buffer1, 16);
		TEE_Free(buffer1);
    }else
        ta_debug("Malloc_test_001 buffer1 failed\n");
}

//size=0 faile test
void Malloc_test_002(void)
{
    char *buffer1=NULL;
    int32_t i, ret;

    ta_debug("-------- malloc test hint = 0 -------\n");
    buffer1 = TEE_Malloc(0, 0);
    if(buffer1){
        ta_debug("Malloc_test_002 faile, buffer:");
        print_buffer(buffer1, 0);
		TEE_Free(buffer1);
    }else
        ta_debug("Malloc_test_002 buffer1 exception test success\n");
}

//rihgt param
void Malloc_test_003(void)
{
    char *buffer1=NULL;
    int32_t i, ret;

    ta_debug("-------- malloc test hint = 1 -------\n");
    buffer1 = TEE_Malloc(100, 1);
    if(buffer1){
        ta_debug("Malloc_test_003 success, buffer:");
        print_buffer(buffer1, 100);
		TEE_Free(buffer1);
    }else
        ta_debug("Malloc_test_003 buffer1 failed\n");
}

//buffer is null
void Malloc_test_004(void)
{
    char *buffer1=NULL;

    ta_debug("-------- buffer is null test free -------\n");
    TEE_Free(buffer1);

}

//size>4K faile
void Malloc_test_005(void)
{
    char *buffer1=NULL;
    int32_t i, ret;

    ta_debug("-------- malloc test size>4K-------\n");
    buffer1 = TEE_Malloc(1024*4, 0);
    if(buffer1){
        ta_debug("Malloc_test_005 success, buffer:");
        print_buffer(buffer1, 16);
		TEE_Free(buffer1);
    }else
        ta_debug("Malloc_test_005 buffer1 failed\n");
}

//right param
void Malloc_test_006()
{
          char *buffer1=NULL;
    int32_t i, ret;

/* mem fill test */
    ta_debug("-------- Malloc_test_006 mem fill test -------\n");
    buffer1 = TEE_Malloc(20, 0);
    ta_debug("base buff:");
    print_buffer(buffer1, 20);
    ta_debug("top 10 fill with a:");
    TEE_MemFill(buffer1, 'a', 10);
    print_buffer(buffer1, 20);
    ta_debug("last 10 fill with b:");
    TEE_MemFill(buffer1+10, 'b', 10);
    print_buffer(buffer1, 20);
	TEE_Free(buffer1);
}

//right param
void Malloc_test_007()
{
          char *buffer1=NULL;
    int32_t i, ret;

/* mem fill test */
    ta_debug("-------- Malloc_test_007 mem fill test -------\n");
    buffer1 = TEE_Malloc(20, 0);
    ta_debug("base buff:");
    print_buffer(buffer1, 20);
    ta_debug("top 10 fill with a:");
    TEE_MemFill(buffer1, 1, 6);
    print_buffer(buffer1, 20);
    ta_debug("last 10 fill with b:");
    TEE_MemFill(buffer1+10, 2, 6);
    print_buffer(buffer1, 20);
	TEE_Free(buffer1);
}

//write size>20
void Malloc_test_008()
{
          char *buffer1=NULL;
    int32_t i, ret;

/* mem fill test */
    ta_debug("-------- Malloc_test_008 mem fill test -------\n");
    buffer1 = TEE_Malloc(20, 0);
    ta_debug("base buff:");
    print_buffer(buffer1, 20);
    ta_debug("top 12 fill with 1:");
    TEE_MemFill(buffer1, 1, 12);
    print_buffer(buffer1, 20);
    ta_debug("last 10 fill with 2:");
    TEE_MemFill(buffer1+10, 2, 20);
    print_buffer(buffer1, 20);
	TEE_Free(buffer1);
}

//buffer1=NULL
void Malloc_test_009()
{
          char *buffer1=NULL;
    int32_t i, ret;

/* mem fill test */
    ta_debug("-------- Malloc_test_009 mem fill test -------\n");

    TEE_MemFill(NULL, 2, 20);

}

//right param
void Malloc_test_010()
{
      char *buffer1=NULL, *buffer2=NULL;
    ta_debug("-------- Malloc_test_010 mem move test -------\n");
	buffer1 = TEE_Malloc(20, 0);
	ta_debug("buffer1:");
    print_buffer(buffer1, 20);
    buffer2 = TEE_Malloc(20, 0);
    ta_debug("buffer2:");
    print_buffer(buffer2, 20);
	TEE_MemFill(buffer1, 'abcdefg', 10);
	TEE_MemFill(buffer2+10, 'c', 10);
		ta_debug("buffer1:");
    print_buffer(buffer1, 20);
	    ta_debug("buffer2:");
    print_buffer(buffer2, 20);

	    ta_debug(" --> move top 10 of buffer1 to buffer 2\n");
    ta_debug("buffer2:");
    TEE_MemMove(buffer2, buffer1, 10);
    print_buffer(buffer2, 20);

    ta_debug(" --> move total of buffer1 to buffer 2\n");
    ta_debug("buffer2:");
    TEE_MemMove(buffer2, buffer1, 20);
    print_buffer(buffer2, 20);
	TEE_Free(buffer1);
	TEE_Free(buffer2);
}

// param is null
void Malloc_test_011()
{
      char *buffer1=NULL, *buffer2=NULL;
    ta_debug("-------- Malloc_test_011 mem move test -------\n");
	buffer1 = TEE_Malloc(20, 0);
	ta_debug("buffer1:");
    print_buffer(buffer1, 20);
    buffer2 = TEE_Malloc(20, 0);
    ta_debug("buffer2:");
    print_buffer(buffer2, 20);
	TEE_MemFill(buffer1, 'a', 10);
	TEE_MemFill(buffer2+10, 'c', 10);

	    ta_debug(" --> move top 10 of buffer1 to buffer 2\n");
    ta_debug("buffer2:");
    TEE_MemMove(NULL, NULL, 10);
    print_buffer(buffer2, 20);

    ta_debug(" --> move total of buffer1 to buffer 2\n");
    ta_debug("buffer2:");
    TEE_MemMove(buffer2, buffer1, 20);
    print_buffer(buffer2, 20);

	TEE_Free(buffer1);
	TEE_Free(buffer2);
}

//free buffer 2 times
void Malloc_test_012(void)
{
    char *buffer1=NULL;
    int32_t i, ret;

    buffer1 = TEE_Malloc(16, 0);
    if(buffer1){
        ta_debug("Malloc_test_012 success, buffer:");
        print_buffer(buffer1, 16);
		TEE_Free(buffer1);
		TEE_Free(buffer1);
    }else
        ta_debug("Malloc_test_012 buffer1 failed\n");
}

//chixu
static int count=0;
void Malloc_test_013(void)
{
    char *buffer1=NULL;
    int32_t i, ret;

    buffer1 = TEE_Malloc(100, 0);
    if(buffer1){
	count++;
        ta_debug("Malloc_test_013 success, buffer: count=%d\n", count);
        print_buffer(buffer1, 100);

    }else
        ta_debug("Malloc_test_013 buffer1 failed\n");
}

//right param buffer1=buffer2
void Malloc_test_014()
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

       buffer1 = TEE_Malloc(20, 0);
	buffer2 = TEE_Malloc(20, 0);

           ta_debug("--------Malloc_test_014 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "abcdefg", sizeof("abcdefg"));
    TEE_MemMove(buffer2, "abcdefg", sizeof("abcdefg"));
    ret = TEE_MemCompare(buffer1, buffer2, 20);
    ret = TEE_MemCompare(buffer1, buffer2, 20);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0){
        ta_debug(" success buffer1 == buffer2\n");
	TEE_Free(buffer1);
	TEE_Free(buffer2);
	}
    else if(ret > 0)
        ta_debug("faile buffer1 > buffer2\n");
    else
        ta_debug("faile buffer1 < buffer2\n");
}

	//right param buffer1<buffer2
void Malloc_test_015()
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

       buffer1 = TEE_Malloc(20, 0);
	buffer2 = TEE_Malloc(20, 0);

           ta_debug("--------Malloc_test_015 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "90", sizeof("90"));
    TEE_MemMove(buffer2, "100", sizeof("100"));
    ret = TEE_MemCompare(buffer1, buffer2, 20);
    ret = TEE_MemCompare(buffer1, buffer2, 20);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0)
        ta_debug(" faile buffer1 == buffer2\n");

    else if(ret > 0)
        ta_debug("success buffer1 > buffer2\n");
    else{
        ta_debug("faile buffer1 < buffer2\n");
		TEE_Free(buffer1);
	TEE_Free(buffer2);
    }
}

		//right param buffer1>buffer2
void Malloc_test_016()
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

       buffer1 = TEE_Malloc(20, 0);
	buffer2 = TEE_Malloc(20, 0);

           ta_debug("--------Malloc_test_016 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "987", sizeof("987"));
    TEE_MemMove(buffer2, "123456", sizeof("123456"));
    ret = TEE_MemCompare(buffer1, buffer2, 20);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0)
        ta_debug(" faile buffer1 == buffer2\n");

    else if(ret > 0){
        ta_debug("success buffer1 > buffer2\n");
			TEE_Free(buffer1);
	TEE_Free(buffer2);
      }
    else
        ta_debug("faile buffer1 < buffer2\n");

}

				//param is null
void Malloc_test_017()
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

       buffer1 = TEE_Malloc(20, 0);
	buffer2 = TEE_Malloc(20, 0);

           ta_debug("--------Malloc_test_017 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "987", sizeof("987"));
    TEE_MemMove(buffer2, "123456", sizeof("123456"));
    ret = TEE_MemCompare(NULL, NULL, 20);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0)
        ta_debug(" success buffer1 == buffer2==null\n");

    else if(ret > 0){
        ta_debug("success buffer1 > buffer2\n");
			TEE_Free(buffer1);
	TEE_Free(buffer2);
      }
    else
        ta_debug("faile buffer1 < buffer2\n");

}

//size=-1
void Malloc_test_018()
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

       buffer1 = TEE_Malloc(20, 0);
	buffer2 = TEE_Malloc(20, 0);

           ta_debug("--------Malloc_test_018 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "787", sizeof("787"));
    TEE_MemMove(buffer2, "987", sizeof("987"));
    ret = TEE_MemCompare(buffer1, buffer2, -1);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0)
        ta_debug(" faile buffer1 == buffer2\n");

    else if(ret > 0)
        ta_debug("success buffer1 > buffer2\n");
    else
        ta_debug("faile buffer1 < buffer2\n");

	           ta_debug("--------Malloc_test_018 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "787", sizeof("787"));
    TEE_MemMove(buffer2, "787", sizeof("787"));
    ret = TEE_MemCompare(buffer1, buffer2, -1);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0)
        ta_debug(" faile buffer1 == buffer2\n");

    else if(ret > 0)
        ta_debug("success buffer1 > buffer2\n");
    else
        ta_debug("faile buffer1 < buffer2\n");

		           ta_debug("--------Malloc_test_018 mem compare test1 -------\n");
    TEE_MemMove(buffer1, "987", sizeof("987"));
    TEE_MemMove(buffer2, "787", sizeof("787"));
    ret = TEE_MemCompare(buffer1, buffer2, -1);

    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
    if(ret == 0)
        ta_debug(" faile buffer1 == buffer2\n");

    else if(ret > 0)
        ta_debug("success buffer1 > buffer2\n");
    else
        ta_debug("faile buffer1 < buffer2\n");

}

//move  size=-1
void Malloc_test_019(void)
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

       buffer1 = TEE_Malloc(20, 0);
	buffer2 = TEE_Malloc(20, 0);
	    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);

	    TEE_MemMove(buffer1, "787", sizeof("787"));
    TEE_MemMove(buffer2, "987", sizeof("987"));

	    ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);

	TEE_MemMove(buffer2, buffer2, -1);

	 ta_debug("buffer1 = %s\n", buffer1);
    ta_debug("buffer2 = %s\n", buffer2);
TEE_Free(buffer1);
	TEE_Free(buffer2);

}

//right param
void Malloc_test_020(void)
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

    ta_debug("--------Malloc_test_020 mem realloc test -------\n");
    buffer1 = TEE_Malloc(8, 0);
    ta_debug("malloc buffer1 addr = 0x%x\n", buffer1);
    TEE_MemFill(buffer1, 33, 8);
    ta_debug("fill buffer with 33!\n");
	print_buffer(buffer1, 8);
    buffer1 = TEE_Realloc(buffer1, 10);
    if(buffer1){
        ta_debug("realloc success, buffer1 addr = 0x%x\n", buffer1);
        ta_debug("buffer1:");
        print_buffer(buffer1, 10);
		TEE_Free(buffer1);
    }else
        ta_debug("malloc buffer1 failed\n");
}

//buffer=null
void Malloc_test_021(void)
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

    ta_debug("--------Malloc_test_021 mem realloc test -------\n");
    buffer1 = TEE_Malloc(8, 0);
    ta_debug("malloc buffer1 addr = 0x%x\n", buffer1);
    TEE_MemFill(buffer1, 33, 8);
    ta_debug("fill buffer with 33!\n");
	print_buffer(buffer1, 8);
    buffer1 = TEE_Realloc(buffer2, 10);
    if(buffer1){
        ta_debug("realloc success, buffer1 addr = 0x%x\n", buffer1);
        ta_debug("buffer1:");
        print_buffer(buffer1, 8);
		TEE_Free(buffer1);
    }else
        ta_debug("malloc buffer1 failed\n");
	TEE_Free(buffer1);
}

//size=0
void Malloc_test_022(void)
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

    ta_debug("--------Malloc_test_022 mem realloc test -------\n");
    buffer1 = TEE_Malloc(8, 0);
    ta_debug("malloc buffer1 addr = 0x%x\n", buffer1);
    TEE_MemFill(buffer1, 33, 8);
    ta_debug("fill buffer with 33!\n");
	print_buffer(buffer1, 8);
    buffer1 = TEE_Realloc(buffer1, 0);
    if(buffer1){
        ta_debug("exception test faile , buffer1 addr = 0x%x\n", buffer1);
        ta_debug("buffer1:");
        print_buffer(buffer1, 10);
		TEE_Free(buffer1);
    }else
        ta_debug("exception test success \n");
	TEE_Free(buffer1);
}

//size=-1
void Malloc_test_023(void)
{
       char *buffer1=NULL, *buffer2=NULL;
       int32_t i, ret;

    ta_debug("--------Malloc_test_023 mem realloc test -------\n");
    buffer1 = TEE_Malloc(8, 0);
    ta_debug("malloc buffer1 addr = 0x%x\n", buffer1);
    TEE_MemFill(buffer1, 33, 8);
    ta_debug("fill buffer with 33!\n");
	print_buffer(buffer1, 8);
    buffer1 = TEE_Realloc(buffer1, -1);
    if(buffer1){
        ta_debug("realloc faile, buffer1 addr = 0x%x\n", buffer1);
        ta_debug("buffer1:");
        print_buffer(buffer1, 10);
		TEE_Free(buffer1);
    }else
        ta_debug("exception test malloc buffer1 failed so test success\n");
	TEE_Free(buffer1);
}

//改data 原始数据
TEE_Result test_integrity1_persistent_object_001(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data111111111111111111111111\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=70;
    uint32_t count[1];

    ta_debug("test_integrity1_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);

    /*改变数据文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w;
    int32_t read_count;
    fd_m=fopen(datafilename,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = fwrite(w_buffer,10, fd_m);
    ta_debug("w_buffer is %s\n",w_buffer);
    fclose(fd_m);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }

    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}

//改data hash数据
TEE_Result test_integrity1_persistent_object_002(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity1_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);

    /*改变数据文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据

    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w;
    int32_t read_count;
    fd_m=fopen(datahashfile,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = fwrite(w_buffer,10, fd_m);
    ta_debug("w_buffer is %s\n",w_buffer);
    fclose(fd_m);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }

    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}

//改attr 原始数据
TEE_Result test_integrity1_persistent_object_003(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity1_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);

    /*改变数据文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据

    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w;
    int32_t read_count;
    fd_m=fopen(infofile,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = fwrite(w_buffer,10, fd_m);
    ta_debug("w_buffer is %s\n",w_buffer);
    fclose(fd_m);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }

    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}

//改attr hash数据
TEE_Result test_integrity1_persistent_object_004(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity1_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);

    /*改变数据文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w;
    int32_t read_count;
    fd_m=fopen(infohfile,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = fwrite(w_buffer,10, fd_m);
    ta_debug("w_buffer is %s\n",w_buffer);
    fclose(fd_m);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }

    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}

//校验空文件
TEE_Result test_integrity1_persistent_object_005(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity1_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);

    /*改变数据文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w;
    int32_t read_count;
    fd_m=fopen(infohfile,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = fwrite(w_buffer,10, fd_m);
    ta_debug("w_buffer is %s\n",w_buffer);
    fclose(fd_m);
	    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }


case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}

TEE_Result test_integrity5_persistent_object_006(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity5_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);


    /*修改文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w,ret_c;
    int32_t read_count;
    fd_m=fopen(datafilename,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = ftruncate(datafilename,10);
    if(ret_w<0)
        ta_debug("modify write error and ret_w is 0x%x~~~~~~~~~~~~~\n",ret_w);
    ta_debug("w_buffer is %s\n",w_buffer);
    ret_c = fclose(fd_m);
    if(ret_c < 0)
        ta_debug("modify open error and ret_c is 0x%x~~~~~~~~~~~~~\n",ret_c);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity5_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity5_persistent_object failed.\n");
    return TEE_FAIL;

}

TEE_Result test_integrity5_persistent_object_007(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity5_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);


    /*修改文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w,ret_c;
    int32_t read_count;
    fd_m=fopen(datafilename,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = ftruncate(datahashfile,10);
    if(ret_w<0)
        ta_debug("modify write error and ret_w is 0x%x~~~~~~~~~~~~~\n",ret_w);
    ta_debug("w_buffer is %s\n",w_buffer);
    ret_c = fclose(fd_m);
    if(ret_c < 0)
        ta_debug("modify open error and ret_c is 0x%x~~~~~~~~~~~~~\n",ret_c);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity5_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity5_persistent_object failed.\n");
    return TEE_FAIL;

}
TEE_Result test_integrity5_persistent_object_008(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity5_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);


    /*修改文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w,ret_c;
    int32_t read_count;
    fd_m=fopen(datafilename,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = ftruncate(infofile,10);
    if(ret_w<0)
        ta_debug("modify write error and ret_w is 0x%x~~~~~~~~~~~~~\n",ret_w);
    ta_debug("w_buffer is %s\n",w_buffer);
    ret_c = fclose(fd_m);
    if(ret_c < 0)
        ta_debug("modify open error and ret_c is 0x%x~~~~~~~~~~~~~\n",ret_c);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity5_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity5_persistent_object failed.\n");
    return TEE_FAIL;

}

TEE_Result test_integrity5_persistent_object_009(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];

    ta_debug("test_integrity5_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);


    /*修改文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w,ret_c;
    int32_t read_count;
    fd_m=fopen(datafilename,TEE_DATA_FLAG_ACCESS_READ|TEE_DATA_FLAG_ACCESS_WRITE);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    ret_w = ftruncate(infohfile,10);
    if(ret_w<0)
        ta_debug("modify write error and ret_w is 0x%x~~~~~~~~~~~~~\n",ret_w);
    ta_debug("w_buffer is %s\n",w_buffer);
    ret_c = fclose(fd_m);
    if(ret_c < 0)
        ta_debug("modify open error and ret_c is 0x%x~~~~~~~~~~~~~\n",ret_c);

    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity5_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity5_persistent_object failed.\n");
    return TEE_FAIL;

}

//改data 原始数据
TEE_Result test_integrity1_persistent_object_0010(void)
{

	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             w_meta_flags=TEE_DATA_FLAG_ACCESS_WRITE_META ,
             rw_flags=(TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE),
             a_attribute_val=0x00000005,b_attribute_val=0x00000007,
             pop_ret_val,attribute_cnt=0x00000003,seek_ret_val,open_seek_retval,
             crt_ret_val,write_ret_val,open_write_retval,read_ret_val,
             open_read_retval,open_ret_val,open_delete_retval,allocate1_ret_val,
             allocate2_ret_val,rd_trunc_cnt=0x00000000,open_truncate_retval,
             trunc_size=0x0000000A,truncate_ret_val,rdtest_truncated_retval,
             optest_truncated_retval,rdtest_written_retval,
             optest_written_retval,rd_write_cnt=0x00000000,read_cnt=0x00000000,
             trunc_cnt=0x00000000,open_rename_retval,de_a,
             rd_rename_cnt=0x00000000,optest_renamed_retval,rename_ret_val,
             rdtest_renamed_retval,optest_deleted_retval;


    int32_t offset=0x00000003;
    size_t objectIDLen=0x00000040,read_size=0x0000000F,rd_trunc_size=0x0000000A,
           rd_write_size=0x0000002C,rd_rename_size=0x0000000C;
    void* open_objectID="/test.dir/test.txt";
    void* rename_objectID="crt.txt";
    void* initialData="---mq rename test This a sierraware created sample initial data\n";
	void* writeData="--- ---mq This a test string\n";
    void* create_objectID="/data/crt.txt";
    void* create3_objectID="/data/crt3.txt";
    void* read_objectID="/test.dir/read.txt";
    void* write_objectID="/test.dir/write.txt";
    void* seek_objectID="/test.dir/seek.txt";
    void* delete_objectID=NULL;
    void* trunc_objectID=NULL;
    char  write_buffer[255];
    char  read_buffer[255],rd_trunc_buffer[255],rd_write_buffer[255],rd_rename_buffer[255];
    void* attrsbuffer="---mq This will get populated sometimes in the test fn\n";
    void* p_buffer="---mq And finally we tested GP_INTERNAL_STORAGE APP\n";
    void* attr_buffer="--- mq test save attribute\n";
    uint32_t count[1];
    size_t read_test_size=90;
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据


    TEE_ObjectHandle crtattributes ;
    TEE_ObjectHandle first_object;
    TEE_ObjectHandle second_object;
	int32_t fd_m;

    TEE_Whence whence;
    whence=0x00000000;
	TEEC_Result result;

 ta_debug("------------TEE_RenamePersistentObject_test001 test start\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_meta_flags, TEE_HANDLE_NULL , initialData, (size_t)(sstrlen((char*)initialData)), (&first_object));

if(crt_ret_val!=TEE_SUCCESS){
ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_CreatePersistentObject faile\n");

}else{
ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_CreatePersistentObject success\n");
strcpy(write_buffer,first_object->dataName);
ta_debug("----------------new name is %s \n",write_buffer);

}


	  result=TEE_RenamePersistentObject(first_object, rename_objectID, (size_t)strlen(rename_objectID));
    if(result != TEE_SUCCESS)
    {
        ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_RenamePersistentObject faile\n");
    }else{
         ta_debug(" ------------------TEE_RenamePersistentObject_test001 TEE_RenamePersistentObject success\n");
		 strcpy(read_buffer,first_object->dataName);
		 ta_debug("----------------new name is %s \n",read_buffer);
		 ta_debug("----------------len is %x \n",strlen(rename_objectID));
	}


    TEE_CloseObject( first_object);

	 open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }

    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}

//不改data 原始数据
TEE_Result test_integrity1_persistent_object_0011(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ,
             w_flags=TEE_DATA_FLAG_ACCESS_WRITE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=70;
    uint32_t count[1];

    ta_debug("test_integrity1_persistent_object start:============\n");
    ta_debug("creat file, write file for data and infoattr  \n");

    /*创建persistent object: flag为写操作(会将initialData和object info和attributes写入flash)*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("the creat persistent fun return value is  0x%x \n \n",crt_ret_val);
    ta_debug("datasize is 0x%x\n",first_object->ObjectInfo->dataSize);
    TEE_CloseObject( first_object);

    /*改变数据文件*/
    char *datafilename = "816C0DD90927C5A2062968420E5B3ADDFBEA1FDD"; //data 原始数据
    char *datahashfile = "3037248F6D980322E62CFCC33B0B083F1B75FB43"; //data hash数据
    char *infofile = "3D32026DD445E86C6DB33948A16EE9002B6DDD20";  //attr 原始数据
    char *infohfile = "280155828150A0BE9AE034EFDA2BA852CA0F7988"; //attr hash数据
    char *w_buffer = "123456789";
    char buffer[128];
    int32_t fd_m,ret_read,ret_w;
    int32_t read_count;


    /*打开已经创建的文件，进行initial data的读取*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS == open_write_retval)
    {
        ta_error("exception test success :Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }

    /*删除所有文件，避免影响后续测试*/
    fd_m = fremove(datafilename);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(datahashfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infofile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
    fd_m = fremove(infohfile);
    if(fd_m<0)
        ta_debug("modify open error and fd_m is 0x%x~~~~~~~~~~~~~\n",fd_m);
case2_pass:
    ta_debug("test_integrity1_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_integrity1_persistent_object failed.\n");
    return TEE_FAIL;

}



/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
TEE_Result TEE_AllocatePersistentObjectEnumerator_001(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);
    enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);
    while(1)
        {
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;

ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");
/*    ta_debug("objectinfo objectType is 0x%x \n",enum_objectInfo.objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",enum_objectInfo.objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",enum_objectInfo.maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",enum_objectInfo.objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",enum_objectInfo.dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",enum_objectInfo.dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",enum_objectInfo.handleFlags);
*/

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);
TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//start two times
TEE_Result TEE_StartPersistentObjectEnumerator_001(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);
    enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);
	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);
    while(1)
        {
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;

ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");
/*    ta_debug("objectinfo objectType is 0x%x \n",enum_objectInfo.objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",enum_objectInfo.objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",enum_objectInfo.maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",enum_objectInfo.objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",enum_objectInfo.dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",enum_objectInfo.dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",enum_objectInfo.handleFlags);
*/

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);
TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//there is no first_objectEnumerator then use start
TEE_Result TEE_StartPersistentObjectEnumerator_002(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
//enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);
	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);
    while(1)
        {
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;

ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);
TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//there is no object in enum then use TEE_GetNextPersistentObject
TEE_Result TEE_GetNextPersistentObject_001(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);
	//enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);
    while(1)
        {
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;

ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);
TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//enum_objectIDLen=0
TEE_Result TEE_GetNextPersistentObject_002(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);
	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);
    while(1)
        {
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;

ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);
TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//reset后打印object，查看是否reset成功
TEE_Result TEE_ResetPersistentObjectEnumerator_001(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);

	ta_debug("-------------1 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);

	ta_debug("-------------2 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

    while(1)
        {
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;

ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);

	ta_debug("-------------3 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//reset后打印object，查看是否reset成功test first_objectEnumerator=null
TEE_Result TEE_ResetPersistentObjectEnumerator_002(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);

	ta_debug("-------------1 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);

	ta_debug("-------------2 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	int32_t i=1;
    while(1)
        {

			ta_debug("-------------zpzpzpzp  %d time print is               ---------\n",i);
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	i++;
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;


ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(NULL);

	ta_debug("-------------3 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

TEE_FreePersistentObjectEnumerator(first_objectEnumerator);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//test first_objectEnumerator=null
TEE_Result TEE_FreePersistentObjectEnumerator_001(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_AllocatePersistentObjectEnumerator_001 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);

	ta_debug("-------------1 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);

	ta_debug("-------------2 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	int32_t i=1;
    while(1)
        {

			ta_debug("-------------zpzpzpzp  %d time print is               ---------\n",i);
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	i++;
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;


ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);

	ta_debug("-------------3 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

TEE_FreePersistentObjectEnumerator(NULL);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);
    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//test first_objectEnumerator=null
TEE_Result TEE_FreePersistentObjectEnumerator_002(void)
{
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE,r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;

    void* create_objectID1="crt.txt1";
    void* create_objectID2="crt.txt2";
    void* create_objectID3="crt.txt3";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("TEE_FreePersistentObjectEnumerator_002  test  start:============\n");

#if 1
    /*first creat with all of flags*/
    ta_debug("creat 3 times\n");
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID1, strlen(create_objectID1),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID2, strlen(create_objectID2),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&second_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID3, strlen(create_objectID3),w_flags|r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&third_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }
    ta_debug("TEE_FreePersistentObjectEnumerator_002 TEE_CreatePersistentObject three times success:============\n");


    TEE_CloseObject(second_object);
    TEE_CloseObject( third_object);
    TEE_CloseObject( first_object);
    #endif
TEE_ObjectEnumHandle first_objectEnumerator;
    TEE_Result enum_ret = TEE_SUCCESS;
    TEE_ObjectInfo enum_objectInfo;
    TEE_ObjectInfo *p_objectInfo;
    char enum_objectID[64];
    size_t enum_objectIDLen;
    p_objectInfo = (TEE_ObjectInfo *)TEE_Malloc(sizeof(TEE_ObjectInfo),0);
    enum_ret = TEE_AllocatePersistentObjectEnumerator(&first_objectEnumerator);

	ta_debug("-------------1 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

	enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);

	ta_debug("-------------2 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	int32_t i=1;
    while(1)
        {

			ta_debug("-------------zpzpzpzp  %d time print is               ---------\n",i);
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	i++;
enum_ret = TEE_GetNextPersistentObject(first_objectEnumerator,  p_objectInfo, enum_objectID,  &enum_objectIDLen );
if(enum_ret != TEE_SUCCESS)
    break;


ta_debug("-------------print objectinfo start ---------\n");
ta_debug("enum_objectID is %s\n",enum_objectID);
ta_debug("enum_objectIDLen is %d\n",enum_objectIDLen);
ta_debug("objectinfo objectType is 0x%x \n",p_objectInfo->objectType);
    ta_debug("objectinfo objectSize is 0x%x \n",p_objectInfo->objectSize);
    ta_debug("objectinfo maxObjectsize is 0x%x \n",p_objectInfo->maxObjectSize);
    ta_debug("objectinfo objectUsage is 0x%x \n",p_objectInfo->objectUsage);
    ta_debug("objectinfo dataSize is 0x%x \n",p_objectInfo->dataSize);
    ta_debug("objectinfo dataPosition is 0x%x \n",p_objectInfo->dataPosition);
    ta_debug("objectinfo handleFlags is 0x%x \n",p_objectInfo->handleFlags);
ta_debug("-------------print objectinfo end ---------\n");

        }
    TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);

	ta_debug("-------------3 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

		enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);

	ta_debug("-------------4 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
	ta_debug("1addr is 0x%x\n",first_objectEnumerator);
TEE_FreePersistentObjectEnumerator(first_objectEnumerator);

ta_debug("-------------5 print first_objectEnumerator start ---------\n");
  ta_debug("2addr is 0x%x\n",first_objectEnumerator);
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

	TEE_ResetPersistentObjectEnumerator(first_objectEnumerator);

	ta_debug("-------------6 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);

enum_ret = TEE_StartPersistentObjectEnumerator(first_objectEnumerator, storageID);

	ta_debug("-------------7 print first_objectEnumerator start ---------\n");
    ta_debug("ObjectID is %s\n",first_objectEnumerator->ObjectID);
    ta_debug("storageID is %d\n",first_objectEnumerator->storageID);
TEE_Free(p_objectInfo);

#if 1
ta_debug("------------------------open 3 times\n");
    /*first creat without share_XX flag, so the follow-up open will be fail*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID1,strlen(create_objectID1), r_flags|w_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("---------------open for test no share_XX is OK\n");
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID2,strlen(create_objectID2), w_flags|ws_flags | TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("-------------third for no share_XX is OK\n");


        open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID3,strlen(create_objectID3), r_flags|rs_flags|w_flags| TEE_DATA_FLAG_ACCESS_WRITE_META, (&third_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("----------------fourth for no share_XX is OK\n");


    TEE_CloseAndDeletePersistentObject( first_object);
    TEE_CloseAndDeletePersistentObject( second_object);
    TEE_CloseAndDeletePersistentObject( third_object);

ta_debug("test for zp\n");
struct teststruct{
	int a;
	int b;
}testssa;
struct teststruct *tss;
tss = (struct teststruct *)TEE_Malloc(sizeof(struct teststruct), 0);
tss->a=12;
tss->b=13;
TEE_Free(tss);
ta_debug("tss->a is %d\n",tss->a);
ta_debug("tss->b is %d\n",tss->b);



    #endif

case2_pass:
    ta_debug("test_case14_persistent_object pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("test_cas14_persistent_object failed.\n");
    return TEE_FAIL;


}

//right param test
TEE_Result attr_rsap_transient_object_001(void)
{
    TEE_ObjectHandle first_object;
    TEE_Result ret;
    TEE_Attribute *rsa_attribute;
    void* attr_buffer1="test save attriasdfffffffffffffffffffffffffffbute\n";
    void* attr_buffer2="abc\n";

    ta_debug("attr_rsap_transient_object_001 start:============\n");
    ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY, 0x00000800,(&first_object));
    if (TEE_SUCCESS != ret)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case1_error;
    }
    ta_debug("------objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("------objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("------objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("------objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("------objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("------objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("------objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

    //need to allocate
    rsa_attribute = (TEE_Attribute*)TEE_Malloc(2*sizeof(TEE_Attribute),0);
    if(rsa_attribute == NULL) {
        ta_error("------not available to allocate \n");
        goto case1_error;
    }
    TEE_InitRefAttribute(&(rsa_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer1,(size_t)strlen(attr_buffer1));

    ta_debug("---------Initattribute is end! \n");
    ta_debug("---------attribute ID is 0x%x \n",rsa_attribute[0].attributeID);
    ta_debug("---------buffer of attribute is %s \n",rsa_attribute[0].content.ref.buffer);
    ta_debug("---------lengrh of attribute is 0x%x \n",rsa_attribute[0].content.ref.length);

    TEE_InitRefAttribute(&(rsa_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT, attr_buffer2, (size_t)strlen(attr_buffer2));

    ta_debug("--------Initattribute is end! \n");
    ta_debug("--------attribute ID is 0x%x \n",rsa_attribute[1].attributeID);
    ta_debug("--------buffer of attribute is %s \n",rsa_attribute[1].content.ref.buffer);
    ta_debug("--------lengrh of attribute is 0x%x \n",rsa_attribute[1].content.ref.length);

    ret = TEE_PopulateTransientObject(first_object, rsa_attribute, 2);
    if (TEE_SUCCESS != ret)
    {
        ta_error("--------Failed to execute TEE_PopulateTransientObject:ret = %d\n", ret);
        goto case1_error;
    }
    ta_debug("----------Populate is end! \n");
    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[0].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("----------lengrh of attribute is 0x%x \n",first_object->Attribute[0].content.ref.length);

    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[1].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------lengrh of attribute is 0x%x \n",first_object->Attribute[1].content.ref.length);

    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        ta_error("-----------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }
    if (ret == TEE_ERROR_ITEM_NOT_FOUND)
        ta_debug("-----------not foundis right\n");
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_RSA_PUBLIC_EXPONENT, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("-----------buffer of attribute is %s \n",testget_buff);
        ta_debug("-----------lengrh of attribute is 0x%x \n",*size);
    }
    else
    {
        ta_error("------------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }

    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("------------objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ret = TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);

    /*check the return value.Make sure get objectBufferAttribute is denied*/
    if (TEE_ERROR_ACCESS_DENIED != ret)
    {
        ta_error("-------------Failed to execute TEE_GetObjectBufferAttribute:does not return TEE_ERROR_ACCESS_DENIED ret = %d\n", ret);
        goto case1_error;
    }
    else
    {
        ta_debug("-------------success to restrict object usage \n");
    }

    /*    if(ret == TEE_SUCCESS){
          testget_buff1[*size]='\0';
          ta_debug("buffer of attribute is %s \n",testget_buff1);
          ta_debug("lengrh of attribute is 0x%x \n",*size1);
          ta_debug("Failed to ")
          }
          else{
          ta_debug("not have permission\n");
          }*/
    ta_debug("-------------FreeTransient is end! \n");
    TEE_ResetTransientObject(first_object);
    ta_debug("------------reset is end\n");
    TEE_FreeTransientObject(first_object);
    ta_debug("-------------free is end\n");
    ta_debug("############y00201671 debug Transient Object end.  ^o^   \n");

    ta_debug("------------OK test storage start!!!~~~~~~~~~2\n");
    TEE_Free((void*)rsa_attribute);

case1_pass:
    ta_debug("-------------attr_rsap_transient_object_001 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case1_error:
    ta_error("--------------attr_rsap_transient_object_001 failed.\n");
    return TEE_FAIL;

}

//TEE_ATTR_RSA_MODULUS param size is  >256 exception test
TEE_Result attr_rsap_transient_object_002(void)
{
    TEE_ObjectHandle first_object;
    TEE_Result ret;
    TEE_Attribute *rsa_attribute;
    void* attr_buffer1="test save attriasdfffffffffffffffffffffffffffbute,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,miaoqiang test data,\n";
    void* attr_buffer2="abc\n";

    ta_debug("attr_rsap_transient_object_002 start:============\n");
    ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY, 0x00000800,(&first_object));
    if (TEE_SUCCESS != ret)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case1_error;
    }
    ta_debug("------objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("------objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("------objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("------objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("------objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("------objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("------objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

    //need to allocate
    rsa_attribute = (TEE_Attribute*)TEE_Malloc(2*sizeof(TEE_Attribute),0);
    if(rsa_attribute == NULL) {
        ta_error("------not available to allocate \n");
        goto case1_error;
    }
    TEE_InitRefAttribute(&(rsa_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer1,(size_t)strlen(attr_buffer1));

    ta_debug("---------Initattribute is end! \n");
    ta_debug("---------attribute ID is 0x%x \n",rsa_attribute[0].attributeID);
    ta_debug("---------buffer of attribute is %s \n",rsa_attribute[0].content.ref.buffer);
    ta_debug("---------lengrh of attribute is 0x%x \n",rsa_attribute[0].content.ref.length);

    TEE_InitRefAttribute(&(rsa_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT, attr_buffer2, (size_t)strlen(attr_buffer2));

    ta_debug("--------Initattribute is end! \n");
    ta_debug("--------attribute ID is 0x%x \n",rsa_attribute[1].attributeID);
    ta_debug("--------buffer of attribute is %s \n",rsa_attribute[1].content.ref.buffer);
    ta_debug("--------lengrh of attribute is 0x%x \n",rsa_attribute[1].content.ref.length);

    ret = TEE_PopulateTransientObject(first_object, rsa_attribute, 2);
    if (TEE_SUCCESS != ret)
    {
        ta_error("--------exception test success size>256\n");
		TEE_FreeTransientObject(first_object);
		TEE_Free((void*)rsa_attribute);
        goto case1_pass;
    }
    ta_debug("----------Populate is end! \n");
    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[0].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("----------lengrh of attribute is 0x%x \n",first_object->Attribute[0].content.ref.length);

    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[1].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------lengrh of attribute is 0x%x \n",first_object->Attribute[1].content.ref.length);

    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        ta_error("-----------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }
    if (ret == TEE_ERROR_ITEM_NOT_FOUND)
        ta_debug("-----------not foundis right\n");
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_RSA_PUBLIC_EXPONENT, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("-----------buffer of attribute is %s \n",testget_buff);
        ta_debug("-----------lengrh of attribute is 0x%x \n",*size);
    }
    else
    {
        ta_error("------------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }

    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("------------objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ret = TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);

    /*check the return value.Make sure get objectBufferAttribute is denied*/
    if (TEE_ERROR_ACCESS_DENIED != ret)
    {
        ta_error("-------------Failed to execute TEE_GetObjectBufferAttribute:does not return TEE_ERROR_ACCESS_DENIED ret = %d\n", ret);
        goto case1_error;
    }
    else
    {
        ta_debug("-------------success to restrict object usage \n");
    }

    /*    if(ret == TEE_SUCCESS){
          testget_buff1[*size]='\0';
          ta_debug("buffer of attribute is %s \n",testget_buff1);
          ta_debug("lengrh of attribute is 0x%x \n",*size1);
          ta_debug("Failed to ")
          }
          else{
          ta_debug("not have permission\n");
          }*/
    ta_debug("-------------FreeTransient is end! \n");
    TEE_ResetTransientObject(first_object);
    ta_debug("------------reset is end\n");
    TEE_FreeTransientObject(first_object);
    ta_debug("-------------free is end\n");
    ta_debug("############y00201671 debug Transient Object end.  ^o^   \n");

    ta_debug("------------OK test storage start!!!~~~~~~~~~2\n");
    TEE_Free((void*)rsa_attribute);

case1_pass:
    ta_debug("-------------attr_rsap_transient_object_002 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case1_error:
    ta_error("--------------attr_rsap_transient_object_002 failed.\n");
    return TEE_FAIL;

}

//TEE_ATTR_RSA_PUBLIC_EXPONENT param size is  >4 exception test
TEE_Result attr_rsap_transient_object_003(void)
{
    TEE_ObjectHandle first_object;
    TEE_Result ret;
    TEE_Attribute *rsa_attribute;
    void* attr_buffer1="test save attriasdfffffffffffffffffffffffffffbute\n";
    void* attr_buffer2="abcde\n";

    ta_debug("attr_rsap_transient_object_003 start:============\n");
    ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY, 0x00000800,(&first_object));
    if (TEE_SUCCESS != ret)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case1_error;
    }
    ta_debug("------objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("------objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("------objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("------objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("------objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("------objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("------objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

    //need to allocate
    rsa_attribute = (TEE_Attribute*)TEE_Malloc(2*sizeof(TEE_Attribute),0);
    if(rsa_attribute == NULL) {
        ta_error("------not available to allocate \n");
        goto case1_error;
    }
    TEE_InitRefAttribute(&(rsa_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer1,(size_t)strlen(attr_buffer1));

    ta_debug("---------Initattribute is end! \n");
    ta_debug("---------attribute ID is 0x%x \n",rsa_attribute[0].attributeID);
    ta_debug("---------buffer of attribute is %s \n",rsa_attribute[0].content.ref.buffer);
    ta_debug("---------lengrh of attribute is 0x%x \n",rsa_attribute[0].content.ref.length);

    TEE_InitRefAttribute(&(rsa_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT, attr_buffer2, (size_t)strlen(attr_buffer2));

    ta_debug("--------Initattribute is end! \n");
    ta_debug("--------attribute ID is 0x%x \n",rsa_attribute[1].attributeID);
    ta_debug("--------buffer of attribute is %s \n",rsa_attribute[1].content.ref.buffer);
    ta_debug("--------lengrh of attribute is 0x%x \n",rsa_attribute[1].content.ref.length);

    ret = TEE_PopulateTransientObject(first_object, rsa_attribute, 2);
    if (TEE_SUCCESS != ret)
    {
        ta_error("--------exception test success size>4\n");
		TEE_FreeTransientObject(first_object);
		TEE_Free((void*)rsa_attribute);
        goto case1_pass;
    }
    ta_debug("----------Populate is end! \n");
    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[0].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("----------lengrh of attribute is 0x%x \n",first_object->Attribute[0].content.ref.length);

    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[1].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------lengrh of attribute is 0x%x \n",first_object->Attribute[1].content.ref.length);

    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        ta_error("-----------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }
    if (ret == TEE_ERROR_ITEM_NOT_FOUND)
        ta_debug("-----------not foundis right\n");
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_RSA_PUBLIC_EXPONENT, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("-----------buffer of attribute is %s \n",testget_buff);
        ta_debug("-----------lengrh of attribute is 0x%x \n",*size);
    }
    else
    {
        ta_error("------------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }

    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("------------objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ret = TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);

    /*check the return value.Make sure get objectBufferAttribute is denied*/
    if (TEE_ERROR_ACCESS_DENIED != ret)
    {
        ta_error("-------------Failed to execute TEE_GetObjectBufferAttribute:does not return TEE_ERROR_ACCESS_DENIED ret = %d\n", ret);
        goto case1_error;
    }
    else
    {
        ta_debug("-------------success to restrict object usage \n");
    }

    /*    if(ret == TEE_SUCCESS){
          testget_buff1[*size]='\0';
          ta_debug("buffer of attribute is %s \n",testget_buff1);
          ta_debug("lengrh of attribute is 0x%x \n",*size1);
          ta_debug("Failed to ")
          }
          else{
          ta_debug("not have permission\n");
          }*/
    ta_debug("-------------FreeTransient is end! \n");
    TEE_ResetTransientObject(first_object);
    ta_debug("------------reset is end\n");
    TEE_FreeTransientObject(first_object);
    ta_debug("-------------free is end\n");
    ta_debug("############y00201671 debug Transient Object end.  ^o^   \n");

    ta_debug("------------OK test storage start!!!~~~~~~~~~2\n");
    TEE_Free((void*)rsa_attribute);

case1_pass:
    ta_debug("-------------attr_rsap_transient_object_003 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case1_error:
    ta_error("--------------attr_rsap_transient_object_003 failed.\n");
    return TEE_FAIL;

}

//TEE_ATTR_RSA_PUBLIC_EXPONENT param size=0
TEE_Result attr_rsap_transient_object_004(void)
{
    TEE_ObjectHandle first_object;
    TEE_Result ret;
    TEE_Attribute *rsa_attribute;
    void* attr_buffer1="test save attriasdfffffffffffffffffffffffffffbute\n";
    void* attr_buffer2="";

    ta_debug("attr_rsap_transient_object_004 start:============\n");
    ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY, 0x00000800,(&first_object));
    if (TEE_SUCCESS != ret)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case1_error;
    }
    ta_debug("------objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("------objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("------objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("------objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("------objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("------objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("------objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

    //need to allocate
    rsa_attribute = (TEE_Attribute*)TEE_Malloc(2*sizeof(TEE_Attribute),0);
    if(rsa_attribute == NULL) {
        ta_error("------not available to allocate \n");
        goto case1_error;
    }
    TEE_InitRefAttribute(&(rsa_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer1,(size_t)strlen(attr_buffer1));

    ta_debug("---------Initattribute is end! \n");
    ta_debug("---------attribute ID is 0x%x \n",rsa_attribute[0].attributeID);
    ta_debug("---------buffer of attribute is %s \n",rsa_attribute[0].content.ref.buffer);
    ta_debug("---------lengrh of attribute is 0x%x \n",rsa_attribute[0].content.ref.length);

    TEE_InitRefAttribute(&(rsa_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT, attr_buffer2, (size_t)strlen(attr_buffer2));

    ta_debug("--------Initattribute is end! \n");
    ta_debug("--------attribute ID is 0x%x \n",rsa_attribute[1].attributeID);
    ta_debug("--------buffer of attribute is %s \n",rsa_attribute[1].content.ref.buffer);
    ta_debug("--------lengrh of attribute is 0x%x \n",rsa_attribute[1].content.ref.length);

    ret = TEE_PopulateTransientObject(first_object, rsa_attribute, 2);
    if (TEE_SUCCESS != ret)
    {
        ta_error("--------exception test success size>4\n");
		TEE_FreeTransientObject(first_object);
		TEE_Free((void*)rsa_attribute);
        goto case1_pass;
    }
    ta_debug("----------Populate is end! \n");
    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[0].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("----------lengrh of attribute is 0x%x \n",first_object->Attribute[0].content.ref.length);

    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[1].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------lengrh of attribute is 0x%x \n",first_object->Attribute[1].content.ref.length);

    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        ta_error("-----------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }
    if (ret == TEE_ERROR_ITEM_NOT_FOUND)
        ta_debug("-----------not foundis right\n");
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_RSA_PUBLIC_EXPONENT, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("-----------buffer of attribute is %s \n",testget_buff);
        ta_debug("-----------lengrh of attribute is 0x%x \n",*size);
    }
    else
    {
        ta_error("------------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }

    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("------------objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ret = TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);

    /*check the return value.Make sure get objectBufferAttribute is denied*/
    if (TEE_ERROR_ACCESS_DENIED != ret)
    {
        ta_error("-------------Failed to execute TEE_GetObjectBufferAttribute:does not return TEE_ERROR_ACCESS_DENIED ret = %d\n", ret);
        goto case1_error;
    }
    else
    {
        ta_debug("-------------success to restrict object usage \n");
    }

    /*    if(ret == TEE_SUCCESS){
          testget_buff1[*size]='\0';
          ta_debug("buffer of attribute is %s \n",testget_buff1);
          ta_debug("lengrh of attribute is 0x%x \n",*size1);
          ta_debug("Failed to ")
          }
          else{
          ta_debug("not have permission\n");
          }*/
    ta_debug("-------------FreeTransient is end! \n");
    TEE_ResetTransientObject(first_object);
    ta_debug("------------reset is end\n");
    TEE_FreeTransientObject(first_object);
    ta_debug("-------------free is end\n");
    ta_debug("############y00201671 debug Transient Object end.  ^o^   \n");

    ta_debug("------------OK test storage start!!!~~~~~~~~~2\n");
    TEE_Free((void*)rsa_attribute);

case1_pass:
    ta_debug("-------------attr_rsap_transient_object_002 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case1_error:
    ta_error("--------------attr_rsap_transient_object_002 failed.\n");
    return TEE_FAIL;

}


//TEE_ATTR_RSA_MODULUS param size=0
TEE_Result attr_rsap_transient_object_005(void)
{
    TEE_ObjectHandle first_object;
    TEE_Result ret;
    TEE_Attribute *rsa_attribute;
    void* attr_buffer1="";
    void* attr_buffer2="abc\n";

    ta_debug("attr_rsap_transient_object_005 start:============\n");
    ret = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY, 0x00000800,(&first_object));
    if (TEE_SUCCESS != ret)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case1_error;
    }
    ta_debug("------objectinfo objectType is 0x%x \n",first_object->ObjectInfo->objectType);
    ta_debug("------objectinfo objectSize is 0x%x \n",first_object->ObjectInfo->objectSize);
    ta_debug("------objectinfo maxObjectsize is 0x%x \n",first_object->ObjectInfo->maxObjectSize);
    ta_debug("------objectinfo objectUsage is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ta_debug("------objectinfo dataSize is 0x%x \n",first_object->ObjectInfo->dataSize);
    ta_debug("------objectinfo dataPosition is 0x%x \n",first_object->ObjectInfo->dataPosition);
    ta_debug("------objectinfo handleFlags is 0x%x \n",first_object->ObjectInfo->handleFlags);

    //need to allocate
    rsa_attribute = (TEE_Attribute*)TEE_Malloc(2*sizeof(TEE_Attribute),0);
    if(rsa_attribute == NULL) {
        ta_error("------not available to allocate \n");
        goto case1_error;
    }
    TEE_InitRefAttribute(&(rsa_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer1,(size_t)strlen(attr_buffer1));

    ta_debug("---------Initattribute is end! \n");
    ta_debug("---------attribute ID is 0x%x \n",rsa_attribute[0].attributeID);
    ta_debug("---------buffer of attribute is %s \n",rsa_attribute[0].content.ref.buffer);
    ta_debug("---------lengrh of attribute is 0x%x \n",rsa_attribute[0].content.ref.length);

    TEE_InitRefAttribute(&(rsa_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT, attr_buffer2, (size_t)strlen(attr_buffer2));

    ta_debug("--------Initattribute is end! \n");
    ta_debug("--------attribute ID is 0x%x \n",rsa_attribute[1].attributeID);
    ta_debug("--------buffer of attribute is %s \n",rsa_attribute[1].content.ref.buffer);
    ta_debug("--------lengrh of attribute is 0x%x \n",rsa_attribute[1].content.ref.length);

    ret = TEE_PopulateTransientObject(first_object, rsa_attribute, 2);
    if (TEE_SUCCESS != ret)
    {
        ta_error("--------exception test success size>4\n");
		TEE_FreeTransientObject(first_object);
		TEE_Free((void*)rsa_attribute);
        goto case1_pass;
    }
    ta_debug("----------Populate is end! \n");
    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[0].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("----------lengrh of attribute is 0x%x \n",first_object->Attribute[0].content.ref.length);

    ta_debug("-----------attribute ID is 0x%x \n",first_object->Attribute[1].attributeID);
    ta_debug("-----------buffer of attribute is %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------lengrh of attribute is 0x%x \n",first_object->Attribute[1].content.ref.length);

    char testget_buff[128],testget_buff1[128];
    size_t size[1],size1[1];
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        ta_error("-----------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }
    if (ret == TEE_ERROR_ITEM_NOT_FOUND)
        ta_debug("-----------not foundis right\n");
    ret=TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_RSA_PUBLIC_EXPONENT, testget_buff,  size);
    if(ret == TEE_SUCCESS){
        testget_buff[*size]='\0';
        ta_debug("-----------buffer of attribute is %s \n",testget_buff);
        ta_debug("-----------lengrh of attribute is 0x%x \n",*size);
    }
    else
    {
        ta_error("------------Failed to execute TEE_GetObjectBufferAttribute:ret = %d\n", ret);
        goto case1_error;
    }

    uint32_t objectUsage = TEE_USAGE_ENCRYPT |  TEE_USAGE_DECRYPT;
    TEE_RestrictObjectUsage(first_object, objectUsage);
    ta_debug("------------objectinfo objectUsage1 is 0x%x \n",first_object->ObjectInfo->objectUsage);
    ret = TEE_GetObjectBufferAttribute(first_object,TEE_ATTR_SECRET_VALUE, testget_buff,  size);

    /*check the return value.Make sure get objectBufferAttribute is denied*/
    if (TEE_ERROR_ACCESS_DENIED != ret)
    {
        ta_error("-------------Failed to execute TEE_GetObjectBufferAttribute:does not return TEE_ERROR_ACCESS_DENIED ret = %d\n", ret);
        goto case1_error;
    }
    else
    {
        ta_debug("-------------success to restrict object usage \n");
    }

    /*    if(ret == TEE_SUCCESS){
          testget_buff1[*size]='\0';
          ta_debug("buffer of attribute is %s \n",testget_buff1);
          ta_debug("lengrh of attribute is 0x%x \n",*size1);
          ta_debug("Failed to ")
          }
          else{
          ta_debug("not have permission\n");
          }*/
    ta_debug("-------------FreeTransient is end! \n");
    TEE_ResetTransientObject(first_object);
    ta_debug("------------reset is end\n");
    TEE_FreeTransientObject(first_object);
    ta_debug("-------------free is end\n");
    ta_debug("############y00201671 debug Transient Object end.  ^o^   \n");

    ta_debug("------------OK test storage start!!!~~~~~~~~~2\n");
    TEE_Free((void*)rsa_attribute);

case1_pass:
    ta_debug("-------------attr_rsap_transient_object_005 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case1_error:
    ta_error("--------------attr_rsap_transient_object_005 failed.\n");
    return TEE_FAIL;

}

//test data is right
TEE_Result attr_rsap_transient_object_006(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *aes_attribute;
	uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* attr_buffer1="0123456789012345678901234567890123456789";
    void* attr_buffer2="abc";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsap.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("attr_rsap_transient_object_006 start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_PUBLIC_KEY, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("-----------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    aes_attribute = (TEE_Attribute*)TEE_Malloc(2*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(aes_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(aes_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT, attr_buffer2,(size_t)strlen(attr_buffer2));
    ret = TEE_PopulateTransientObject(second_object, aes_attribute, 2);
    if (TEE_SUCCESS != ret)
    {
        ta_error("-------------Failed to execute TEE_PopulateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("--------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("---------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("---------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("---------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("----------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr222 is right\n");
    ta_debug("-------------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("---------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("-----------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("----------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("------------------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("------------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-------------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("----------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("------------------attr222 is right\n");

    /*object info会随着create和open进行修改*/
    /*    if (memcmp((void *)(first_object->ObjectInfo), (void *)(&first_object_info), sizeof(TEE_ObjectInfo)))
          {
          ta_error("object info read from flash is not equal to second object.\n");
          goto case3_error;
          }*/

    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("---------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("--------------read content is %s \n",read_buffer);
            ta_error("-------------flash content is %s \n",initialData);
            ta_error("--------------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("---------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("----------------read is end  \n");
        ta_debug("-------------------read count is 0x%x  \n",*count);
        ta_debug("------------------read content is %s \n",read_buffer);
    }
    else{
        ta_error("-------------------read error\n");
        ta_error("-----------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("--------------read is end  \n");
        ta_error("----------------read count is 0x%x  \n",*count);
        ta_error("-----------------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
case3_pass:
    TEE_Free((void*)aes_attribute);
    ta_debug("----------------attr_rsap_transient_object_006 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case3_error:
    ta_error("----------------attr_rsap_transient_object_006 failed.\n");
    return TEE_FAIL;
}

//right params
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_001(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_001 start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
        ta_error("----------Failed to execute TEE_PopulateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_001 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_001 failed.\n");
    return TEE_FAIL;
}

//TEE_ATTR_RSA_MODULUS size>256 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_002(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest,miaoqiangexceptiontest";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_002 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_002 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_002 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}


//TEE_ATTR_RSA_PUBLIC_EXPONENT size>4 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_003(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a1234";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_003 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_003 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_003 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_ATTR_RSA_PRIVATE_EXPONENT size>256 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_004(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_004 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------TEE_TYPE_RSA_KEYPAIR_test_004 exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_004 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_004 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_ATTR_RSA_PRIME1 size>128 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_005(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_005 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------TEE_TYPE_RSA_KEYPAIR_test_005 exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_005 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_005 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_ATTR_RSA_PRIME2 size>128 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_006(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_006 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------TEE_TYPE_RSA_KEYPAIR_test_006 exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_006 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_006 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_ATTR_RSA_EXPONENT1 size>128 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_007(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_007 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------TEE_TYPE_RSA_KEYPAIR_test_007 exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_007 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_007 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_ATTR_RSA_EXPONENT2 size>128 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_008(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_008 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------TEE_TYPE_RSA_KEYPAIR_test_008 exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_008 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_008 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_ATTR_RSA_COEFFICIENT size>128 exception test
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_009(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_009 exception test start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------TEE_TYPE_RSA_KEYPAIR_test_009 exception test  pass \n");
        goto case3_pass;
    }
    ta_debug("---------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[2].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[3].content.ref.buffer);
    ta_debug("-------------zpsecond_object attributes  %s \n",second_object->Attribute[4].content.ref.buffer);
    ta_debug("------------zpsecond_object attributes  %s \n",second_object->Attribute[5].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[6].content.ref.buffer);
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[7].content.ref.buffer);

    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, attr_buffer[i], (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("---------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("-------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("-------------Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("------------attr%d is right\n",(i+1));
    }


    TEE_FreeTransientObject(second_object);
    //TEE_CloseObject( second_object);

case3_error:
    ta_error("-------------TEE_TYPE_RSA_KEYPAIR_test_009 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("-----------TEE_TYPE_RSA_KEYPAIR_test_009 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;


}

//TEE_TYPE_RSA_KEYPAIR type create flash
TEE_Result TEE_TYPE_RSA_KEYPAIR_test_010(void)
{
    TEE_ObjectHandle second_object, first_object;
    TEE_Attribute *rsak_attribute;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    char *attr_buffer[8];
    attr_buffer[0]="01234567890123456789012123456789012123456789012123";
    attr_buffer[1]="a12";
    attr_buffer[2]="asd123456789012123456789012fasdf";
    attr_buffer[3]="ghs123456789012123456789012dfhsdfh";
    attr_buffer[4]="sdfg123456789012123456789012shsdh";
    attr_buffer[5]="asdfaghfgsdfg123456789012123456789012shsdh";
    attr_buffer[6]="fhjjjjsdfg123456789012123456789012shsdh";
    attr_buffer[7]="fffffffsdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crtrsak.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;
    uint32_t i=0;


    ta_debug("-------------TEE_TYPE_RSA_KEYPAIR_test_010 start:============\n");
    ta_debug("test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_RSA_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    rsak_attribute = (TEE_Attribute*)TEE_Malloc(8*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(rsak_attribute[0]), TEE_ATTR_RSA_MODULUS, attr_buffer[0],(size_t)strlen(attr_buffer[0]));
    TEE_InitRefAttribute(&(rsak_attribute[1]), TEE_ATTR_RSA_PUBLIC_EXPONENT , attr_buffer[1],(size_t)strlen(attr_buffer[1]));
    TEE_InitRefAttribute(&(rsak_attribute[2]), TEE_ATTR_RSA_PRIVATE_EXPONENT, attr_buffer[2],(size_t)strlen(attr_buffer[2]));
    TEE_InitRefAttribute(&(rsak_attribute[3]), TEE_ATTR_RSA_PRIME1, attr_buffer[3],(size_t)strlen(attr_buffer[3]));
    TEE_InitRefAttribute(&(rsak_attribute[4]), TEE_ATTR_RSA_PRIME2, attr_buffer[4],(size_t)strlen(attr_buffer[4]));
    TEE_InitRefAttribute(&(rsak_attribute[5]), TEE_ATTR_RSA_EXPONENT1, attr_buffer[5],(size_t)strlen(attr_buffer[5]));
    TEE_InitRefAttribute(&(rsak_attribute[6]), TEE_ATTR_RSA_EXPONENT2, attr_buffer[6],(size_t)strlen(attr_buffer[6]));
    TEE_InitRefAttribute(&(rsak_attribute[7]), TEE_ATTR_RSA_COEFFICIENT, attr_buffer[7],(size_t)strlen(attr_buffer[7]));


    ret = TEE_PopulateTransientObject(second_object, rsak_attribute, 8);
    if (TEE_SUCCESS != ret)
    {
        ta_error("Failed to execute TEE_PopulateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    ta_debug("zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, first_object->Attribute[i].content.ref.buffer, (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("attr%d is right\n",(i+1));
    }

    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[2].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[3].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[4].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[5].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[6].content.ref.buffer);
    ta_debug("zpfirst_object attributes  %s \n",first_object->Attribute[7].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    for(i=0;i<8;i++)
    {
        if (memcmp(second_object->Attribute[i].content.ref.buffer, first_object->Attribute[i].content.ref.buffer, (size_t)(strlen(attr_buffer[i]))))
        {
            ta_error("second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
            ta_error("first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
            ta_error("Failed to set persisten object attributes buffer.\n");
            goto case3_error;
        }
        ta_debug("attr%d is right\n",(i+1));
    }

    ta_debug("first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("attr222 is right\n");

    /*object info会随着create和open进行修改*/
    /*    if (memcmp((void *)(first_object->ObjectInfo), (void *)(&first_object_info), sizeof(TEE_ObjectInfo)))
          {
          ta_error("object info read from flash is not equal to second object.\n");
          goto case3_error;
          }*/

    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("read content is %s \n",read_buffer);
            ta_error("flash content is %s \n",initialData);
            ta_error("Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("read is end  \n");
        ta_debug("read count is 0x%x  \n",*count);
        ta_debug("read content is %s \n",read_buffer);
    }
    else{
        ta_error("read error\n");
        ta_error("the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("read is end  \n");
        ta_error("read count is 0x%x  \n",*count);
        ta_error("read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    /*判断是否删除成功*/
    /*    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID, objectIDLen, r_flags, (&first_object));
          if (TEE_SUCCESS == open_write_retval)
          {
          ta_error("Close and delete persistent object failed :ret = %x\n", open_write_retval);
          goto case3_error;
          }*/
    //TEE_CloseObject(first_object);
    TEE_CloseObject( second_object);
#endif
case3_pass:
    TEE_Free((void*)rsak_attribute);
    ta_debug("TEE_TYPE_RSA_KEYPAIR_test_010 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case3_error:
    ta_error("TEE_TYPE_RSA_KEYPAIR_test_010 failed.\n");
    return TEE_FAIL;
}

//TEE_TYPE_DH_KEYPAIR type right params
TEE_Result TEE_TYPE_DH_KEYPAIR_test_001(void)
{
    TEE_ObjectHandle second_object, first_object;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    TEE_Attribute *dh_attribute;
    void* attr_buffer1="01234567890123456789012123456789012123456789012123";
    void* attr_buffer2="a123456789012123456789012bc";
    void* attr_buffer3="asd123456789012123456789012fasdf";
    void* attr_buffer4="ghs123456789012123456789012dfhsdfh";
    void* attr_buffer5="sdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crt12.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("-----------TEE_TYPE_DH_KEYPAIR_test_001 start:============\n");
    ta_debug("--------------test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_DH_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------------------Failed to execute TEE_AllocateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    dh_attribute = (TEE_Attribute*)TEE_Malloc(5*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(dh_attribute[0]), TEE_ATTR_DH_PRIME, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(dh_attribute[1]), TEE_ATTR_DH_BASE , attr_buffer2,(size_t)strlen(attr_buffer2));
    TEE_InitRefAttribute(&(dh_attribute[2]), TEE_ATTR_DH_PUBLIC_VALUE, attr_buffer3,(size_t)strlen(attr_buffer3));
    TEE_InitRefAttribute(&(dh_attribute[3]), TEE_ATTR_DH_PRIVATE_VALUE, attr_buffer4,(size_t)strlen(attr_buffer4));
    TEE_InitRefAttribute(&(dh_attribute[4]), TEE_ATTR_DH_SUBPRIME, attr_buffer5,(size_t)strlen(attr_buffer5));

    ret = TEE_PopulateTransientObject(second_object, dh_attribute, 5);
    if (TEE_SUCCESS != ret)
    {
        ta_error("----------------Failed to execute TEE_PopulateTransientObject:ret = %d\n", ret);
        goto case3_error;
    }
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("------------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("-------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------attr222 is right\n");
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("--------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-----------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("---------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("--------------attr222 is right\n");


    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("----------read content is %s \n",read_buffer);
            ta_error("----------flash content is %s \n",initialData);
            ta_error("-----------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("--------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("-------read is end  \n");
        ta_debug("--------read count is 0x%x  \n",*count);
        ta_debug("----------read content is %s \n",read_buffer);
    }
    else{
        ta_error("--------read error\n");
        ta_error("------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("------------read is end  \n");
        ta_error("----------read count is 0x%x  \n",*count);
        ta_error("-----------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
#endif
case3_pass:
    TEE_Free((void*)dh_attribute);
    ta_debug("TEE_TYPE_DH_KEYPAIR_test_001 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case3_error:
    ta_error("TEE_TYPE_DH_KEYPAIR_test_001 failed.\n");
    return TEE_FAIL;
}

//TEE_TYPE_DH_KEYPAIR TEE_ATTR_DH_PRIME>256 exception test
TEE_Result TEE_TYPE_DH_KEYPAIR_test_002(void)
{
    TEE_ObjectHandle second_object, first_object;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    TEE_Attribute *dh_attribute;
    void* attr_buffer1="01234567890123456789012123456789012123456789012123,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    void* attr_buffer2="a123456789012123456789012bc";
    void* attr_buffer3="asd123456789012123456789012fasdf";
    void* attr_buffer4="ghs123456789012123456789012dfhsdfh";
    void* attr_buffer5="sdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crt12.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("-----------TEE_TYPE_DH_KEYPAIR_test_002 start:============\n");
    ta_debug("--------------test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_DH_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------------------TEE_TYPE_DH_KEYPAIR_test_002 exception test pass\n");
        goto case3_error;
    }
    dh_attribute = (TEE_Attribute*)TEE_Malloc(5*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(dh_attribute[0]), TEE_ATTR_DH_PRIME, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(dh_attribute[1]), TEE_ATTR_DH_BASE , attr_buffer2,(size_t)strlen(attr_buffer2));
    TEE_InitRefAttribute(&(dh_attribute[2]), TEE_ATTR_DH_PUBLIC_VALUE, attr_buffer3,(size_t)strlen(attr_buffer3));
    TEE_InitRefAttribute(&(dh_attribute[3]), TEE_ATTR_DH_PRIVATE_VALUE, attr_buffer4,(size_t)strlen(attr_buffer4));
    TEE_InitRefAttribute(&(dh_attribute[4]), TEE_ATTR_DH_SUBPRIME, attr_buffer5,(size_t)strlen(attr_buffer5));

    ret = TEE_PopulateTransientObject(second_object, dh_attribute, 5);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------------TEE_TYPE_DH_KEYPAIR_test_002 exception test pass\n");
        goto case3_pass;
    }
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("------------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("-------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------attr222 is right\n");
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("--------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-----------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("---------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("--------------attr222 is right\n");


    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("----------read content is %s \n",read_buffer);
            ta_error("----------flash content is %s \n",initialData);
            ta_error("-----------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("--------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("-------read is end  \n");
        ta_debug("--------read count is 0x%x  \n",*count);
        ta_debug("----------read content is %s \n",read_buffer);
    }
    else{
        ta_error("--------read error\n");
        ta_error("------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("------------read is end  \n");
        ta_error("----------read count is 0x%x  \n",*count);
        ta_error("-----------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
#endif

case3_error:
    ta_error("-----------TEE_TYPE_DH_KEYPAIR_test_002 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)dh_attribute);
    ta_debug("-----TEE_TYPE_DH_KEYPAIR_test_002 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//TEE_TYPE_DH_KEYPAIR TEE_ATTR_DH_BASE>256 exception test
TEE_Result TEE_TYPE_DH_KEYPAIR_test_003(void)
{
    TEE_ObjectHandle second_object, first_object;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    TEE_Attribute *dh_attribute;
    void* attr_buffer1="01234567890123456789012123456789012123456789012123";
    void* attr_buffer2="a123456789012123456789012bc,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    void* attr_buffer3="asd123456789012123456789012fasdf";
    void* attr_buffer4="ghs123456789012123456789012dfhsdfh";
    void* attr_buffer5="sdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crt12.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("-----------TEE_TYPE_DH_KEYPAIR_test_003 start:============\n");
    ta_debug("--------------test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_DH_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------------------TEE_TYPE_DH_KEYPAIR_test_003 exception test pass\n");
        goto case3_error;
    }
    dh_attribute = (TEE_Attribute*)TEE_Malloc(5*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(dh_attribute[0]), TEE_ATTR_DH_PRIME, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(dh_attribute[1]), TEE_ATTR_DH_BASE , attr_buffer2,(size_t)strlen(attr_buffer2));
    TEE_InitRefAttribute(&(dh_attribute[2]), TEE_ATTR_DH_PUBLIC_VALUE, attr_buffer3,(size_t)strlen(attr_buffer3));
    TEE_InitRefAttribute(&(dh_attribute[3]), TEE_ATTR_DH_PRIVATE_VALUE, attr_buffer4,(size_t)strlen(attr_buffer4));
    TEE_InitRefAttribute(&(dh_attribute[4]), TEE_ATTR_DH_SUBPRIME, attr_buffer5,(size_t)strlen(attr_buffer5));

    ret = TEE_PopulateTransientObject(second_object, dh_attribute, 5);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------------TEE_TYPE_DH_KEYPAIR_test_003 exception test pass\n");
        goto case3_pass;
    }
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("------------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("-------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------attr222 is right\n");
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("--------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-----------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("---------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("--------------attr222 is right\n");


    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("----------read content is %s \n",read_buffer);
            ta_error("----------flash content is %s \n",initialData);
            ta_error("-----------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("--------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("-------read is end  \n");
        ta_debug("--------read count is 0x%x  \n",*count);
        ta_debug("----------read content is %s \n",read_buffer);
    }
    else{
        ta_error("--------read error\n");
        ta_error("------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("------------read is end  \n");
        ta_error("----------read count is 0x%x  \n",*count);
        ta_error("-----------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
#endif

case3_error:
    ta_error("-----------TEE_TYPE_DH_KEYPAIR_test_003 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)dh_attribute);
    ta_debug("-----TEE_TYPE_DH_KEYPAIR_test_003 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//TEE_TYPE_DH_KEYPAIR TEE_ATTR_DH_PUBLIC_VALUE>256 exception test
TEE_Result TEE_TYPE_DH_KEYPAIR_test_004(void)
{
    TEE_ObjectHandle second_object, first_object;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    TEE_Attribute *dh_attribute;
    void* attr_buffer1="01234567890123456789012123456789012123456789012123";
    void* attr_buffer2="a123456789012123456789012bc";
    void* attr_buffer3="asd123456789012123456789012fasdf,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    void* attr_buffer4="ghs123456789012123456789012dfhsdfh";
    void* attr_buffer5="sdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crt12.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("-----------TEE_TYPE_DH_KEYPAIR_test_004 start:============\n");
    ta_debug("--------------test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_DH_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------------------TEE_TYPE_DH_KEYPAIR_test_004 exception test pass\n");
        goto case3_error;
    }
    dh_attribute = (TEE_Attribute*)TEE_Malloc(5*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(dh_attribute[0]), TEE_ATTR_DH_PRIME, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(dh_attribute[1]), TEE_ATTR_DH_BASE , attr_buffer2,(size_t)strlen(attr_buffer2));
    TEE_InitRefAttribute(&(dh_attribute[2]), TEE_ATTR_DH_PUBLIC_VALUE, attr_buffer3,(size_t)strlen(attr_buffer3));
    TEE_InitRefAttribute(&(dh_attribute[3]), TEE_ATTR_DH_PRIVATE_VALUE, attr_buffer4,(size_t)strlen(attr_buffer4));
    TEE_InitRefAttribute(&(dh_attribute[4]), TEE_ATTR_DH_SUBPRIME, attr_buffer5,(size_t)strlen(attr_buffer5));

    ret = TEE_PopulateTransientObject(second_object, dh_attribute, 5);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------------TEE_TYPE_DH_KEYPAIR_test_004 exception test pass\n");
        goto case3_pass;
    }
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("------------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("-------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------attr222 is right\n");
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("--------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-----------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("---------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("--------------attr222 is right\n");


    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("----------read content is %s \n",read_buffer);
            ta_error("----------flash content is %s \n",initialData);
            ta_error("-----------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("--------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("-------read is end  \n");
        ta_debug("--------read count is 0x%x  \n",*count);
        ta_debug("----------read content is %s \n",read_buffer);
    }
    else{
        ta_error("--------read error\n");
        ta_error("------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("------------read is end  \n");
        ta_error("----------read count is 0x%x  \n",*count);
        ta_error("-----------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
#endif

case3_error:
    ta_error("-----------TEE_TYPE_DH_KEYPAIR_test_004 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)dh_attribute);
    ta_debug("-----TEE_TYPE_DH_KEYPAIR_test_004 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}


//TEE_TYPE_DH_KEYPAIR TEE_ATTR_DH_PRIVATE_VALUE>256 exception test
TEE_Result TEE_TYPE_DH_KEYPAIR_test_005(void)
{
    TEE_ObjectHandle second_object, first_object;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    TEE_Attribute *dh_attribute;
    void* attr_buffer1="01234567890123456789012123456789012123456789012123";
    void* attr_buffer2="a123456789012123456789012bc";
    void* attr_buffer3="asd123456789012123456789012fasdf";
    void* attr_buffer4="ghs123456789012123456789012dfhsdfh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    void* attr_buffer5="sdfg123456789012123456789012shsdh";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crt12.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("-----------TEE_TYPE_DH_KEYPAIR_test_005 start:============\n");
    ta_debug("--------------test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_DH_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------------------TEE_TYPE_DH_KEYPAIR_test_005 exception test pass\n");
        goto case3_error;
    }
    dh_attribute = (TEE_Attribute*)TEE_Malloc(5*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(dh_attribute[0]), TEE_ATTR_DH_PRIME, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(dh_attribute[1]), TEE_ATTR_DH_BASE , attr_buffer2,(size_t)strlen(attr_buffer2));
    TEE_InitRefAttribute(&(dh_attribute[2]), TEE_ATTR_DH_PUBLIC_VALUE, attr_buffer3,(size_t)strlen(attr_buffer3));
    TEE_InitRefAttribute(&(dh_attribute[3]), TEE_ATTR_DH_PRIVATE_VALUE, attr_buffer4,(size_t)strlen(attr_buffer4));
    TEE_InitRefAttribute(&(dh_attribute[4]), TEE_ATTR_DH_SUBPRIME, attr_buffer5,(size_t)strlen(attr_buffer5));

    ret = TEE_PopulateTransientObject(second_object, dh_attribute, 5);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------------TEE_TYPE_DH_KEYPAIR_test_005 exception test pass\n");
        goto case3_pass;
    }
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("------------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("-------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------attr222 is right\n");
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("--------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-----------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("---------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("--------------attr222 is right\n");


    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("----------read content is %s \n",read_buffer);
            ta_error("----------flash content is %s \n",initialData);
            ta_error("-----------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("--------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("-------read is end  \n");
        ta_debug("--------read count is 0x%x  \n",*count);
        ta_debug("----------read content is %s \n",read_buffer);
    }
    else{
        ta_error("--------read error\n");
        ta_error("------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("------------read is end  \n");
        ta_error("----------read count is 0x%x  \n",*count);
        ta_error("-----------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
#endif

case3_error:
    ta_error("-----------TEE_TYPE_DH_KEYPAIR_test_005 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)dh_attribute);
    ta_debug("-----TEE_TYPE_DH_KEYPAIR_test_005 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//TEE_TYPE_DH_KEYPAIR TEE_ATTR_DH_SUBPRIME>256 exception test
TEE_Result TEE_TYPE_DH_KEYPAIR_test_006(void)
{
    TEE_ObjectHandle second_object, first_object;
	 uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    TEE_Attribute *dh_attribute;
    void* attr_buffer1="01234567890123456789012123456789012123456789012123";
    void* attr_buffer2="a123456789012123456789012bc";
    void* attr_buffer3="asd123456789012123456789012fasdf";
    void* attr_buffer4="ghs123456789012123456789012dfhsdfh";
    void* attr_buffer5="sdfg123456789012123456789012shsdh,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest,miaoqiangexceptiongtest";
    TEE_Result allocate1_ret_val,crt_ret_val, ret, open_write_retval, read_ret_val;
    uint32_t w_flags=TEE_DATA_FLAG_ACCESS_WRITE,
             r_flags=TEE_DATA_FLAG_ACCESS_READ;
    void* create3_objectID="/data/crt12.txt";
    size_t objectIDLen=0x00000040;
    void* initialData="This a sierraware created sample initial data\n";
    char  read_buffer[255];
    uint32_t count[1];
    size_t read_test_size=46;
    void* create_objectID="/data/crt.txt";
    TEE_ObjectInfo first_object_info;


    ta_debug("-----------TEE_TYPE_DH_KEYPAIR_test_006 start:============\n");
    ta_debug("--------------test attribute storage!!---------------\n");


    //need to allocate
    allocate1_ret_val = TEE_AllocateTransientObject(TEE_TYPE_DH_KEYPAIR, 0x00000800,(&second_object));
    if (TEE_SUCCESS != allocate1_ret_val)
    {
        ta_error("------------------TEE_TYPE_DH_KEYPAIR_test_006 exception test pass\n");
        goto case3_error;
    }
    dh_attribute = (TEE_Attribute*)TEE_Malloc(5*sizeof(TEE_Attribute),0);
    TEE_InitRefAttribute(&(dh_attribute[0]), TEE_ATTR_DH_PRIME, attr_buffer1,(size_t)strlen(attr_buffer1));
    TEE_InitRefAttribute(&(dh_attribute[1]), TEE_ATTR_DH_BASE , attr_buffer2,(size_t)strlen(attr_buffer2));
    TEE_InitRefAttribute(&(dh_attribute[2]), TEE_ATTR_DH_PUBLIC_VALUE, attr_buffer3,(size_t)strlen(attr_buffer3));
    TEE_InitRefAttribute(&(dh_attribute[3]), TEE_ATTR_DH_PRIVATE_VALUE, attr_buffer4,(size_t)strlen(attr_buffer4));
    TEE_InitRefAttribute(&(dh_attribute[4]), TEE_ATTR_DH_SUBPRIME, attr_buffer5,(size_t)strlen(attr_buffer5));

    ret = TEE_PopulateTransientObject(second_object, dh_attribute, 5);
    if (TEE_SUCCESS != ret)
    {
       TEE_FreeTransientObject(second_object);
        ta_error("----------------TEE_TYPE_DH_KEYPAIR_test_006 exception test pass\n");
        goto case3_pass;
    }
    ta_debug("-----------zpsecond_object attributes  %s \n",second_object->Attribute[0].content.ref.buffer);
    ta_debug("--------------zpsecond_object attributes  %s \n",second_object->Attribute[1].content.ref.buffer);
    /*创建persistent object, 为key object:既有数据流，又有attributes。写入flash*/
    crt_ret_val=TEE_CreatePersistentObject(storageID, create3_objectID, strlen(create3_objectID),w_flags, second_object , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("------------------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case3_error;
    }
#if 1
    /*检查是否将transient object的attributes赋值给persistent object*/
    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("-------------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("-------------second_object attributes is %s \n",second_object->Attribute->content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute->content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("---------attr222 is right\n");
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("-----------zpfirst_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    /*将objectinfo进行保存，方便后面的flash读取后的比较*/
    memcpy((void * )(&first_object_info), (void * )(first_object->ObjectInfo), sizeof(TEE_ObjectInfo));


    TEE_CloseObject(first_object);

    /*打开前面创建的object*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create3_objectID, strlen(create3_objectID), r_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case3_error;
    }
    ta_debug("----------openend\n");

    /*检查objectinfo和attributes是否存入成功*/

    if (memcmp(second_object->Attribute[0].content.ref.buffer, first_object->Attribute[0].content.ref.buffer, (size_t)(strlen(attr_buffer1))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[0].content.ref.buffer);
        ta_error("------------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
        ta_error("-------------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }
    ta_debug("--------attr111 is right\n");
    if (memcmp(second_object->Attribute[1].content.ref.buffer, first_object->Attribute[1].content.ref.buffer, (size_t)(strlen(attr_buffer2))))
    {
        ta_error("----------second_object attributes is %s \n",second_object->Attribute[1].content.ref.buffer);
        ta_error("-----------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
        ta_error("-----------Failed to set persisten object attributes buffer.\n");
        goto case3_error;
    }

    ta_debug("---------first_object attributes  %s \n",first_object->Attribute[0].content.ref.buffer);
    ta_debug("------------first_object attributes  %s \n",first_object->Attribute[1].content.ref.buffer);
    ta_debug("--------------attr222 is right\n");


    /*读取已经存入的数据*/
    read_ret_val = TEE_ReadObjectData(first_object,read_buffer,read_test_size, count);
    read_buffer[*count]='\0';
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("----------read content is %s \n",read_buffer);
            ta_error("----------flash content is %s \n",initialData);
            ta_error("-----------Failed to read buffer.\n");
            goto case3_error;
        }
        if (*count != read_test_size)
        {
            ta_error("--------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case3_error;
        }

        ta_debug("----------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_debug("-------read is end  \n");
        ta_debug("--------read count is 0x%x  \n",*count);
        ta_debug("----------read content is %s \n",read_buffer);
    }
    else{
        ta_error("--------read error\n");
        ta_error("------------the objectType is 0x%x \n",first_object->ObjectInfo->objectType);
        ta_error("------------read is end  \n");
        ta_error("----------read count is 0x%x  \n",*count);
        ta_error("-----------read content is %s \n",read_buffer);
        goto case3_error;
    }



    /*删除对应的文件*/
    //    TEE_CloseAndDeletePersistentObject(TEE_HANDLE_NULL);
    TEE_CloseAndDeletePersistentObject(first_object);
    TEE_CloseObject( second_object);
#endif

case3_error:
    ta_error("-----------TEE_TYPE_DH_KEYPAIR_test_006 failed.\n");
    return TEE_FAIL;

case3_pass:
    TEE_Free((void*)dh_attribute);
    ta_debug("-----TEE_TYPE_DH_KEYPAIR_test_006 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

/*创建文件(data stream object)，写入flash，并读出来进行数据流的验证*/
//first is w_flags|ws_flags|r_flags|rs_flags,secend is  r_flags|rs_flags
TEE_Result persistent_object_share_test_001(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_001 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags|ws_flags|r_flags|rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_001 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_001 failed.\n");
    return TEE_FAIL;


}

//first is r_flags,secend is  r_flags exception test
TEE_Result persistent_object_share_test_002(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_002 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_002 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_002 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_002 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//first is r_flags|rs_flags,secend is  r_flags exception test
TEE_Result persistent_object_share_test_003(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_003 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags|rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_003 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_003 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_003 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//first is r_flags,secend is  w_flags exception test
TEE_Result persistent_object_share_test_004(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_004 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags|rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_004 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_004 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_004 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//first is r_flags|rs_flags|ws_flags|w_flags,secend is  TEE_DATA_FLAG_ACCESS_WRITE_META exception test
TEE_Result persistent_object_share_test_005(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_005 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags|rs_flags|ws_flags|w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), TEE_DATA_FLAG_ACCESS_WRITE_META, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_005 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_005 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_005 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//first is rs_flags,secend is  w_flags|ws_flags exception test
TEE_Result persistent_object_share_test_006(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_006 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), w_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_006 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_006 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_006 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//first is 0,secend is  r_flags|rs_flags exception test
TEE_Result persistent_object_share_test_007(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_007 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),0, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID),  r_flags|rs_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_007 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_007 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_007 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

//first is r_flags|rs_flags,secend is  r_flags|rs_flags
TEE_Result persistent_object_share_test_008(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_008 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags|rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_008 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_008 failed.\n");
    return TEE_FAIL;


}

//first is r_flags|rs_flags|ws_flags,secend is  r_flags|rs_flags|ws_flags
TEE_Result persistent_object_share_test_009(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_009 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags|rs_flags|ws_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_009 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_009 failed.\n");
    return TEE_FAIL;


}

//first is w_flags|ws_flags|r_flags|rs_flags,secend is  w_flags|ws_flags
TEE_Result persistent_object_share_test_010(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_010 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),w_flags|ws_flags|r_flags|rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), w_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_010 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_010 failed.\n");
    return TEE_FAIL;


}

//first is w_flags|ws_flags|r_flags|rs_flags,secend is  rs_flags|ws_flags
TEE_Result persistent_object_share_test_011(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_011 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),r_flags|rs_flags|ws_flags|w_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), rs_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------persistent_object_share_test_011 exception test success \n");
		TEE_CloseObject( first_object);
		TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
		TEE_CloseAndDeletePersistentObject( first_object);
        goto case2_pass;
    }
    ta_debug("------------second open for share_read is OK\n");


    read_ret_val = TEE_ReadObjectData(second_object,read_buffer,read_test_size, count);
    if(read_ret_val == TEE_SUCCESS)
    {
        ta_debug("------------read success!\n");
        read_buffer[*count]='\0';
        /*对读出的数据进行判断，保证读出的数据与creat object时写入的相同*/
        if (memcmp(read_buffer, initialData, read_test_size))
        {
            ta_error("------------read content is %s \n",read_buffer);
            ta_error("---------flash content is %s \n",initialData);
            ta_error("----------Failed to read buffer.\n");
            goto case2_error;
        }
        if (*count != read_test_size)
        {
            ta_error("-------------read length(read_test_size=%d) is not equal to count(count=%d).\n", read_test_size, *count);
            goto case2_error;
        }

        ta_debug("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_debug("-----------read is end  \n");
        ta_debug("----------read count is 0x%x  \n",*count);
        ta_debug("-----------read content is %s \n",read_buffer);
    }
    else{

        ta_error("------------read error\n");
        ta_error("-----------the objectType is 0x%x \n",second_object->ObjectInfo->objectType);
        ta_error("-----------read is end  \n");
        ta_error("-----------read count is 0x%x  \n",*count);
        ta_error("-------read content is %s \n",read_buffer);
        goto case2_error;
    }

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_error:
    ta_error("---------persistent_object_share_test_011 failed.\n");
    return TEE_FAIL;

case2_pass:
    ta_debug("-------------persistent_object_share_test_011 exception test pass:^o^   ^o^\n");
    return TEE_SUCCESS;

}

TEE_Result persistent_object_share_test_012(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_012 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rs_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_012 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_012 failed.\n");
    return TEE_FAIL;


}

TEE_Result persistent_object_share_test_013(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_013 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),ws_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), w_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_013 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_013 failed.\n");
    return TEE_FAIL;


}

TEE_Result persistent_object_share_test_014(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------persistent_object_share_test_014 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rs_flags|ws_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID),r_flags|rs_flags| w_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);

case2_pass:
    ta_debug("-------------persistent_object_share_test_014 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------persistent_object_share_test_014 failed.\n");
    return TEE_FAIL;


}

TEE_Result panic_test_001(void)
{
    uint32_t r_flags=TEE_DATA_FLAG_ACCESS_READ,w_flags=TEE_DATA_FLAG_ACCESS_WRITE,rs_flags=TEE_DATA_FLAG_SHARE_READ,ws_flags=TEE_DATA_FLAG_SHARE_WRITE;
    uint32_t storageID=TEE_OBJECT_STORAGE_PRIVATE;
    void* create_objectID="crt.txt";
    size_t objectIDLen=0x00000007;
    void* initialData="This a sierraware created sample initial data\n";
    TEE_ObjectHandle first_object,second_object,third_object,fourth_object,fifth_object,sixth_object;
    TEE_Result crt_ret_val, open_write_retval, read_ret_val;
    char  read_buffer[255];
    size_t read_test_size=46;
    uint32_t count[1];
    ta_debug("------------panic_test_001 start:============\n");

    /*first creat with all of flags*/
    ta_debug("-----------flags is 0x%x\n",(w_flags|ws_flags|r_flags|rs_flags));
    crt_ret_val=TEE_CreatePersistentObject(storageID, create_objectID, strlen(create_objectID),rs_flags|ws_flags, TEE_HANDLE_NULL , initialData, (size_t)(strlen((char*)initialData)), (&first_object));
    if (TEE_SUCCESS != crt_ret_val)
    {
        ta_error("-----------Failed to execute TEE_CreatePersistentObject:ret = %x\n", crt_ret_val);
        goto case2_error;
    }


    /*second open with share_read flag*/
    open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID),r_flags|rs_flags| w_flags|ws_flags, (&second_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("------------Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }
    ta_debug("------------second open for share_read is OK\n");

    TEE_CloseObject(second_object);
    TEE_CloseObject( first_object);
      open_write_retval = TEE_OpenPersistentObject(storageID, create_objectID,strlen(create_objectID), r_flags|rs_flags|TEE_DATA_FLAG_ACCESS_WRITE_META, (&first_object));
    if (TEE_SUCCESS != open_write_retval)
    {
        ta_error("Failed to execute TEE_OpenPersistentObject:ret = %x\n", open_write_retval);
        goto case2_error;
    }else{ta_debug("-----------before delete open object success ! \n");}

    TEE_CloseAndDeletePersistentObject( first_object);
	TEE_CloseObject( first_object);

case2_pass:
    ta_debug("-------------panic_test_001 pass:^o^   ^o^\n");
    return TEE_SUCCESS;

case2_error:
    ta_error("---------panic_test_001 failed.\n");
    return TEE_FAIL;


}


int m_main_storage()
{
ta_debug("------------m_main_storage test start");

/*TEE_AllocateTransientObject_test001();

int m_main_storage()
{
ta_debug("------------m_main_storage test start");

/*TEE_AllocateTransientObject_test001();
TEE_AllocateTransientObject_test002();
TEE_AllocateTransientObject_test003();
TEE_InitRefAttribute_test001();
TEE_PopulateTransientObject_test001();
TEE_PopulateTransientObject_test002();
TEE_PopulateTransientObject_test003();
TEE_PopulateTransientObject_test004();
TEE_GetObjectBufferAttribute_test001();
TEE_GetObjectBufferAttribute_test002();
TEE_CreatePersistentObject_test001();
TEE_CreatePersistentObject_test002();        //bug
TEE_CreatePersistentObject_test003();
TEE_CreatePersistentObject_test004();
TEE_CreatePersistentObject_test005();
TEE_CreatePersistentObject_test006();
TEE_CreatePersistentObject_test007();
TEE_CreatePersistentObject_test008();
TEE_CreatePersistentObject_test009();        //bug
TEE_CreatePersistentObject_test010();
TEE_CloseAndDeletePersistentObject_test001();
TEE_CloseAndDeletePersistentObject_test002();
TEE_CloseAndDeletePersistentObject_test003();
TEE_RenamePersistentObject_test001();          //bug
TEE_RenamePersistentObject_test002();
TEE_RenamePersistentObject_test003();
TEE_RenamePersistentObject_test004();
TEE_GetObjectInfo_test001();
TEE_GetObjectInfo_test002();
TEE_GetObjectInfo_test003();
TEE_GetObjectBufferAttribute_test003();
TEE_ResetTransientObject_test001();
TEE_ResetTransientObject_test002();
TEE_ResetTransientObject_test003();
TEE_CopyObjectAttributes_test001();
TEE_CopyObjectAttributes_test002();
TEE_CopyObjectAttributes_test003();
TEE_CopyObjectAttributes_test004();
TEE_RestrictObjectUsage_test001();

    Malloc_test_001();
      Malloc_test_002();
      Malloc_test_003();
      Malloc_test_004();
      Malloc_test_005();
      Malloc_test_006();
      Malloc_test_007();
     // Malloc_test_008(); //测试用例不合理
      Malloc_test_009();
     Malloc_test_010();
	 Malloc_test_011();
	 Malloc_test_012();*/

/* 	 int j;
        for(j=1;j<20;j++){
         Malloc_test_013();
          }*/

    /*   Malloc_test_014();
       Malloc_test_015();
       Malloc_test_016();
       Malloc_test_017();
    //   Malloc_test_018(); //测试用例不合理
    //   Malloc_test_019();//测试用例不合理
	 Malloc_test_020();
	  Malloc_test_021();
	  Malloc_test_022();
	 Malloc_test_023(); */
/*
	 while(1)
           Malloc_test_020(); */

   /*  test_integrity1_persistent_object_001();
      test_integrity1_persistent_object_002();
      test_integrity1_persistent_object_003();
      test_integrity1_persistent_object_004();
      test_integrity1_persistent_object_005();
      test_integrity5_persistent_object_006();
      test_integrity5_persistent_object_007();
      test_integrity5_persistent_object_008();
      test_integrity5_persistent_object_009();
      test_integrity1_persistent_object_0010();  //bug*/
      //test_integrity1_persistent_object_0011();
      //TEE_AllocatePersistentObjectEnumerator_001();
	//  TEE_StartPersistentObjectEnumerator_001();
	 // TEE_StartPersistentObjectEnumerator_002();
	// TEE_GetNextPersistentObject_001();  //bug
	//TEE_GetNextPersistentObject_002();
	//TEE_ResetPersistentObjectEnumerator_002();
	//TEE_FreePersistentObjectEnumerator_001();
	//TEE_FreePersistentObjectEnumerator_002(); //bug
	 /*attr_rsap_transient_object_001();
	attr_rsap_transient_object_002();
	 attr_rsap_transient_object_003();
	attr_rsap_transient_object_004();
	attr_rsap_transient_object_005();
	attr_rsap_transient_object_006();
	TEE_TYPE_RSA_KEYPAIR_test_001();
	  TEE_TYPE_RSA_KEYPAIR_test_002();
	 TEE_TYPE_RSA_KEYPAIR_test_003();
	  TEE_TYPE_RSA_KEYPAIR_test_004();
	  TEE_TYPE_RSA_KEYPAIR_test_005();
	  TEE_TYPE_RSA_KEYPAIR_test_006();
	  TEE_TYPE_RSA_KEYPAIR_test_007();
	  TEE_TYPE_RSA_KEYPAIR_test_008();
	  TEE_TYPE_RSA_KEYPAIR_test_009();
	  TEE_TYPE_RSA_KEYPAIR_test_010();
	  TEE_TYPE_DH_KEYPAIR_test_001();
	TEE_TYPE_DH_KEYPAIR_test_002();
	  TEE_TYPE_DH_KEYPAIR_test_003();
	  TEE_TYPE_DH_KEYPAIR_test_004();
	  TEE_TYPE_DH_KEYPAIR_test_005();
	  TEE_TYPE_DH_KEYPAIR_test_006();
	  persistent_object_share_test_001();
	  persistent_object_share_test_002();
	  persistent_object_share_test_003();
	  persistent_object_share_test_004();
	  persistent_object_share_test_005();
	  persistent_object_share_test_006();
	  persistent_object_share_test_007();
	  persistent_object_share_test_008();
	  persistent_object_share_test_009();
	  persistent_object_share_test_010();
	  persistent_object_share_test_011();
	  persistent_object_share_test_012();
	  persistent_object_share_test_013();
	  persistent_object_share_test_014();*/
	  panic_test_001();

      tee_storage_exit();
      ta_debug("--------------m_main_storage test end");
      return 0;
}
