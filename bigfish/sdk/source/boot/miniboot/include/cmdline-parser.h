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

#ifndef CMDLINEPARSEH
#define CMDLINEPARSEH

#include <stddef.h>

/* partition flags */
#define PF_RDONLY                   0x01 /* Device is read only */
#define PF_POWERUP_LOCK             0x02 /* Always locked after reset */
#define MAX_PARTNAME                32

struct cmdline_subpart {
	char name[MAX_PARTNAME]; /* partition name, such as 'rootfs' */
	uint64 from;
	uint64 size;
	int flags;
	struct cmdline_subpart *next_subpart;
};

struct cmdline_parts {
	char name[MAX_PARTNAME]; /* block device, such as 'mmcblk0' */
	unsigned int nr_subparts;
	struct cmdline_subpart *subpart;
	struct cmdline_parts *next_parts;
};

void cmdline_parts_free(struct cmdline_parts **parts);

int cmdline_parts_parse(struct cmdline_parts **parts, const char *cmdline);

struct cmdline_parts *cmdline_parts_find(struct cmdline_parts *parts,
					 const char *bdev);

int cmdline_parts_set(struct cmdline_parts *parts, uint64 disk_size,
		      int slot,
		      int (*add_part)(int, struct cmdline_subpart *, void *),
		      void *param);

#endif /* CMDLINEPARSEH */
