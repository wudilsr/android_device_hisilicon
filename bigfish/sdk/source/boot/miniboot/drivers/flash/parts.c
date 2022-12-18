/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <flash.h>
#include <malloc.h>
#include <errno.h>
#include <env_set.h>
#include <string.h>
#include <cmdline-parser.h>

//#define MODULE_DEBUG
#include <debug.h>

/*****************************************************************************/

static char *devpart_duplicate(const char *devpartname)
{
	size_t size;
	char *devpart;
	char *tail;
	char *bootargs = env_get("bootargs");

	if (!bootargs)
		return NULL;

	devpart = strstr(bootargs, devpartname);
	if (!devpart)
		return NULL;

	/* "mtdparts" or "blkdevparts" should appeare only once in bootargs */
	devpart += strlen(devpartname) + 1;
	if (*(devpart - 1) != '=')
		return NULL;

	tail = strchr(devpart, ' ');
	if (tail)
		size = tail - devpart;
	else
		size = strlen(devpart);

	return strndup(devpart, size);
}
/*****************************************************************************/

static int enum_part(int slot, struct cmdline_subpart *subpart, void *param)
{
	char *partname = *(char **)param;

	if (strncmp(subpart->name, partname, sizeof(subpart->name)))
		return 0;

	*(struct cmdline_subpart **)param = subpart;
	return 1;
}
/*****************************************************************************/
/*
 * bootargs="mtdparts=hinand:2M(boot),4M(kernel),60M(rootfs),40M(test),-(others)"
 * @devpartname - device partition name, such as "mtdparts", "blkdevparts"
 * @devname     - device name, such as "hinand", "hi_sfc", "emmcblk0"
 * @partname    - partition name. such as "boot", "kernel", ...
 *
 */
int flash_find_part(const char *devpartname, const char *devname,
		    const char *partname, uint64 *start, uint64 *size)
{
	int ret;
	char *str_part;
	struct cmdline_parts *devparts;
	struct cmdline_parts *parts;
	struct cmdline_subpart *subpart;

	ASSERT(devpartname != NULL && devname != NULL && partname != NULL);
	ASSERT(start != NULL && size != NULL);

	str_part = devpart_duplicate(devpartname);
	if (!str_part)
		return -ENODEV;

	ret = cmdline_parts_parse(&devparts, str_part);

	free(str_part);

	if (ret)
		return ret;

	ret = -ENODEV;

	parts = cmdline_parts_find(devparts, devname);
	if (!parts)
		goto fail;

	subpart = (struct cmdline_subpart *)partname;
	cmdline_parts_set(parts, (uint64)(~0ULL), 0, enum_part, (void *)&subpart);

	/* no found partition. */
	if ((char *)subpart == partname)
		goto fail;

	*start = subpart->from;
	*size = subpart->size;

	ret = 0;
fail:
	cmdline_parts_free(&devparts);
	return ret;
}

