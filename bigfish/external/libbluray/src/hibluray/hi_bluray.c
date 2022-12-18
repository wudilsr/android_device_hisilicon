/*
 * hi_bluray.c
 *
 *  Created on: 2013-3-30
 *      Author: z00187490
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <dlfcn.h>
#include <dirent.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "file/file.h"
#include "util/macro.h"
#include "util/logging.h"
#include "util/strutl.h"
#include "libudf.h"

#define AVSEEK_SIZE (0x10000)

typedef struct Context {
    union {
    libudf_file_t*          udf_file;
    libudf_dir_t*           udf_dir;
    };
    struct udf_api  udf_api;
} Context;

static void file_close_udf(BD_FILE_H *file)
{
    if (file) {

        Context *c= file->internal;
        c->udf_api.close_file(c->udf_file);

        BD_DEBUG(DBG_FILE, "Closed LINUX file (%p)\n", (void*)file);
        X_FREE(file->internal);
        X_FREE(file);
    }
}

static int64_t file_seek_udf(BD_FILE_H *file, int64_t offset, int32_t origin)
{
    BD_DEBUG(DBG_FILE,"seek to:%lld origin:%d\n",  offset, origin);

    Context *c= file->internal;
    return c->udf_api.seek_file(c->udf_file, offset, origin);
}

static int64_t file_tell_udf(BD_FILE_H *file)
{

    Context *c= file->internal;
    return c->udf_api.seek_file(c->udf_file, 0, SEEK_SIZE);
}

static int file_eof_udf(BD_FILE_H *file)
{

    Context *c= file->internal;
    return c->udf_api.seek_file(c->udf_file, 0, SEEK_CUR) ==
        c->udf_api.seek_file(c->udf_file, 0, SEEK_SIZE);
}

#define BD_MAX_SSIZE ((int64_t)(((size_t)-1)>>1))

static int64_t file_read_udf(BD_FILE_H *file, uint8_t *buf, int size)
{

    if (size > 0 && size < BD_MAX_SSIZE) {
        Context *c= file->internal;
        return c->udf_api.read_file(c->udf_file, buf, size);
    }

    BD_DEBUG(DBG_FILE | DBG_CRIT, "Ignoring invalid read of size %"PRId64" (%p)\n", size, (void*)file);
    return -1;
}

static int64_t file_write_udf(BD_FILE_H *file, const uint8_t *buf, int64_t size)
{
    BD_DEBUG(DBG_FILE | DBG_CRIT, "Ignoring invalid write of size %"PRId64" (%p)\n", size, (void*)file);
    return -1;
}

BD_FILE_H *file_open_udf(const char* filename, const char *mode)
{
    int ret;
    Context* c = NULL;
    BD_FILE_H *file = malloc(sizeof(BD_FILE_H));
    memset(file, 0, sizeof(BD_FILE_H));
    if (!file) {
        return NULL;
    }
    c = malloc(sizeof(Context));
    memset(c, 0, sizeof(Context));
    if (!file || !c) {
        goto fail;
    }

    BD_DEBUG(DBG_FILE, "Opening UDF file %s... (%p)\n", filename, (void*)file);
    file->close = file_close_udf;
    file->seek = file_seek_udf;
    file->read = file_read_udf;
    file->write = file_write_udf;
    file->tell = file_tell_udf;
    file->eof = file_eof_udf;

    ret = udf_api_load(&c->udf_api);
    if (ret < 0)
    {
        BD_DEBUG(DBG_FILE, "load udf api failed\n");
        goto fail;
    }

    c->udf_file = c->udf_api.open_file(filename);
    if (!c->udf_file)
    {
        BD_DEBUG(DBG_FILE, "open udf %s failed\n", filename);
        udf_api_close(&c->udf_api);
        goto fail;
    }
    file->internal = c;
    return file;

fail:
    BD_DEBUG(DBG_FILE, "Error opening file! (%p)\n", (void*)file);
    X_FREE(c);
    X_FREE(file);

    return NULL;
}

static void _dir_close_udf(BD_DIR_H *dir)
{
    Context* c;
    if (dir) {
        c = (Context*)dir->internal;
        c->udf_api.close_dir(c->udf_dir);

        BD_DEBUG(DBG_DIR, "Closed POSIX dir (%p)\n", (void*)dir);
        X_FREE(c);
        X_FREE(dir);
    }
}

static int _dir_read_udf(BD_DIR_H *dir, BD_DIRENT *entry)
{
    int result;
    Context* c;
    struct udf_dir_ent udf_ent;

    c = (Context*)dir->internal;
    result = c->udf_api.read_dir(c->udf_dir, &udf_ent);
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    }
    strncpy(entry->d_name, udf_ent.name, 256);

    return 0;
}

BD_DIR_H *dir_open_udf(const char* dirname)
{
    Context* c = malloc(sizeof(Context));
    BD_DIR_H *dir = malloc(sizeof(BD_DIR_H));

    int ret = udf_api_load(&c->udf_api);
    if (ret < 0)
    {
        BD_DEBUG(DBG_FILE, "load udf api failed\n");
        goto fail;
    }

    BD_DEBUG(DBG_DIR, "Opening UDF dir %s... (%p)\n", dirname, (void*)dir);
    dir->close = _dir_close_udf;
    dir->read = _dir_read_udf;
    dir->internal = c;
    c->udf_dir = c->udf_api.open_dir(dirname);

    if (c->udf_dir) {
        return dir;
    }
fail:
    BD_DEBUG(DBG_DIR, "Error opening dir! (%p)\n", (void*)dir);

    X_FREE(dir);
    X_FREE(c);

    return NULL;
}
