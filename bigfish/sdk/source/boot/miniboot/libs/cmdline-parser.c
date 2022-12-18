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

#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <cmdline-parser.h>

//#define MODULE_DEBUG
#include <debug.h>

/*****************************************************************************/

static int parse_subpart(struct cmdline_subpart **subpart, char *partdef)
{
	int ret = 0;
	struct cmdline_subpart *new_subpart;

	*subpart = NULL;

	new_subpart = zmalloc(sizeof(struct cmdline_subpart));
	if (!new_subpart)
		return -ENOMEM;

	if (*partdef == '-') {
		new_subpart->size = (uint64)(~0ULL);
		partdef++;
	} else {
		new_subpart->size = (uint64)memparse(partdef, &partdef);
		if (new_subpart->size == 0ULL) {
			pr_warn("cmdline partition size is invalid.\n");
			ret = -EINVAL;
			goto fail;
		}
	}

	if (*partdef == '@') {
		partdef++;
		new_subpart->from = (uint64)memparse(partdef, &partdef);
	} else {
		new_subpart->from = (uint64)(~0ULL);
	}

	if (*partdef == '(') {
		int length;
		char *next = strchr(++partdef, ')');

		if (!next) {
			pr_warn("cmdline partition format is invalid.\n");
			ret = -EINVAL;
			goto fail;
		}

		length = min_t(int, next - partdef,
			       sizeof(new_subpart->name) - 1);
		strncpy(new_subpart->name, partdef, length);
		new_subpart->name[length] = '\0';

		partdef = ++next;
	} else
		new_subpart->name[0] = '\0';

	new_subpart->flags = 0;

	if (!strncmp(partdef, "ro", 2)) {
		new_subpart->flags |= PF_RDONLY;
		partdef += 2;
	}

	if (!strncmp(partdef, "lk", 2)) {
		new_subpart->flags |= PF_POWERUP_LOCK;
		partdef += 2;
	}

	*subpart = new_subpart;
	return 0;
fail:
	free(new_subpart);
	return ret;
}
/*****************************************************************************/

static void free_subpart(struct cmdline_parts *parts)
{
	struct cmdline_subpart *subpart;

	while (parts->subpart) {
		subpart = parts->subpart;
		parts->subpart = subpart->next_subpart;
		free(subpart);
	}
}
/*****************************************************************************/

static int parse_parts(struct cmdline_parts **parts, const char *bdevdef)
{
	int ret = -EINVAL;
	char *next;
	int length;
	struct cmdline_subpart **next_subpart;
	struct cmdline_parts *newparts;
	char buf[MAX_PARTNAME + 32 + 4];

	*parts = NULL;

	newparts = zmalloc(sizeof(struct cmdline_parts));
	if (!newparts)
		return -ENOMEM;

	next = strchr(bdevdef, ':');
	if (!next) {
		pr_warn("cmdline partition has no block device.\n");
		goto fail;
	}

	length = min_t(int, next - bdevdef, sizeof(newparts->name) - 1);
	strncpy(newparts->name, bdevdef, length);
	newparts->name[length] = '\0';

	next_subpart = &newparts->subpart;

	while (next && *(++next)) {
		bdevdef = next;
		next = strchr(bdevdef, ',');

		length = (!next) ? (sizeof(buf) - 1) :
			min_t(int, next - bdevdef, sizeof(buf) - 1);

		strncpy(buf, bdevdef, length);
		buf[length] = '\0';

		ret = parse_subpart(next_subpart, buf);
		if (ret)
			goto fail;

		newparts->nr_subparts++;
		next_subpart = &(*next_subpart)->next_subpart;
	}

	if (!newparts->subpart) {
		pr_warn("cmdline partition has no valid partition.\n");
		ret = -EINVAL;
		goto fail;
	}

	*parts = newparts;

	return 0;
fail:
	free_subpart(newparts);
	free(newparts);
	return ret;
}
/*****************************************************************************/

void cmdline_parts_free(struct cmdline_parts **parts)
{
	struct cmdline_parts *next_parts;

	while (*parts) {
		next_parts = (*parts)->next_parts;
		free_subpart(*parts);
		free(*parts);
		*parts = next_parts;
	}
}
/*****************************************************************************/

int cmdline_parts_parse(struct cmdline_parts **parts, const char *cmdline)
{
	int len;
	int ret;
	char *buf;
	char *pbuf;
	char *next;
	struct cmdline_parts **next_parts;

	*parts = NULL;

	len = strlen(cmdline);
	next = pbuf = buf = malloc(len + 1);
	if (!buf)
		return -ENOMEM;
	memcpy(buf, cmdline, len + 1);

	next_parts = parts;

	while (next && *pbuf) {
		next = strchr(pbuf, ';');
		if (next)
			*next = '\0';

		ret = parse_parts(next_parts, pbuf);
		if (ret)
			goto fail;

		if (next)
			pbuf = ++next;

		next_parts = &(*next_parts)->next_parts;
	}

	if (!*parts) {
		pr_warn("cmdline partition has no valid partition.\n");
		ret = -EINVAL;
		goto fail;
	}

	ret = 0;
done:
	free(buf);
	return ret;

fail:
	cmdline_parts_free(parts);
	goto done;
}
/*****************************************************************************/

struct cmdline_parts *cmdline_parts_find(struct cmdline_parts *parts,
					 const char *bdev)
{
	while (parts && strncmp(bdev, parts->name, sizeof(parts->name)))
		parts = parts->next_parts;
	return parts;
}

/*****************************************************************************/
/*
 *  add_part()
 *    0 success.
 *    1 can not add so many partitions.
 */
int cmdline_parts_set(struct cmdline_parts *parts, uint64 disk_size,
		      int slot,
		      int (*add_part)(int, struct cmdline_subpart *, void *),
		      void *param)
{
	uint64 from = 0;
	struct cmdline_subpart *subpart;

	for (subpart = parts->subpart; subpart;
	     subpart = subpart->next_subpart, slot++) {
		if (subpart->from == (uint64)(~0ULL))
			subpart->from = from;
		else
			from = subpart->from;

		if (from >= disk_size)
			break;

		if (subpart->size > (disk_size - from))
			subpart->size = disk_size - from;

		from += subpart->size;

		if (add_part(slot, subpart, param))
			break;
	}

	return slot;
}
