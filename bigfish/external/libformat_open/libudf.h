/*
 * libudf.h
 *
 *  Created on: 2014Äê6ÔÂ13ÈÕ
 *      Author: z00187490
 */

#ifndef LIBUDF_H_
#define LIBUDF_H_


#include <stdint.h>
#include <dlfcn.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define SEEK_SIZE (0x10000)

typedef struct udf libudf_t;
typedef struct udf_file libudf_file_t;
typedef struct udf_dir libudf_dir_t;

/**
 * API for dllopen
 */
struct udf_api
{
    libudf_t* (*open)(const char* iso_path);
    void (*close)(libudf_t* udf);
    libudf_file_t* (*open_file)(const char* url);
    int (*read_file)(libudf_file_t* udf_file, uint8_t* buf, unsigned int size);
    int64_t (*seek_file)(libudf_file_t* udf_file, int64_t pos, int whence);
    void (*close_file)(libudf_file_t* udf_file);

    libudf_dir_t* (*open_dir)(const char* url);
    void (*close_dir)(libudf_dir_t* dir);
    int (*read_dir)(libudf_dir_t* dir, struct udf_dir_ent* ent);

    void* handle;
};

struct udf_dir_ent {
    char name[256];
};
libudf_t* udf_open(const char* iso_path);
void udf_close(libudf_t* udf);
libudf_file_t* udf_file_open(const char* file_name);
int udf_file_read(libudf_file_t* udf, uint8_t* buf, unsigned int size);
int64_t udf_file_seek(libudf_file_t* udf, int64_t pos, int whence);
void udf_file_close(libudf_file_t* udf);

libudf_dir_t* udf_dir_open(const char* dir_name);
void udf_dir_close(libudf_dir_t* dir);
int udf_dir_read(libudf_dir_t* dir, struct udf_dir_ent* ent);

static inline int udf_api_load(struct udf_api* api)
{
    void* module = dlopen("libudf.so", RTLD_LAZY);
    if (!module)
    {
        return -1;
    }
    api->open        = (libudf_t* (*)(const char*))dlsym(module, "udf_open");
    api->close       = (void (*)(libudf_t*))dlsym(module, "udf_close");
    api->close_file  = (void (*)(libudf_file_t*))dlsym(module, "udf_file_close");
    api->open_file   = (libudf_file_t* (*)(const char*))dlsym(module, "udf_file_open");
    api->read_file   = (int (*)(libudf_file_t*, uint8_t*, unsigned int))dlsym(module, "udf_file_read");
    api->seek_file   = (int64_t (*)(libudf_file_t*, int64_t, int))dlsym(module, "udf_file_seek");
    api->open_dir    = (libudf_dir_t* (*)(const char*))dlsym(module, "udf_dir_open");
    api->close_dir   = (void (*)(libudf_dir_t*))dlsym(module, "udf_dir_close");
    api->read_dir    = (int (*)(libudf_dir_t*, struct udf_dir_ent*))dlsym(module, "udf_dir_read");
    api->handle = module;

    if (!api->close_file || !api->open_file || !api->read_file || !api->seek_file)
    {
        dlclose(module);
        return -1;
    }

    return 0;
}

static inline void udf_api_close(struct udf_api* api)
{
    if (api && api->handle)
    {
        dlclose(api->handle);
        memset(api, 0, sizeof(*api));
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* LIBUDF_H_ */
