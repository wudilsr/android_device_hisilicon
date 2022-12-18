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

#include <run.h>
#include <string.h>
#include <env_set.h>
#include <boot.h>
#include <stdio.h>
#include <kern_param.h>
#include <malloc.h>
#include <params.h>

struct tag_hdr_t {
	uint32 size;  /* tag size (data + head) 4bytes unit */
	uint32 type;  /* tag type */
};

#ifndef CONFIG_SDKVERSION
#  define CONFIG_SDKVERSION     "sdk version unknown"
#endif /* CONFIG_SDKVERSION */

/*****************************************************************************/

static struct tag_hdr_t *fill_tag(struct tag_hdr_t *tag, uint32 type, char *buf,
				  uint32 buflen)
{
	tag->type = type;
	tag->size = (sizeof(struct tag_hdr_t) + buflen + 3) >> 2;
	memcpy((char *)&tag[1], buf, buflen);
	return (struct tag_hdr_t *)((uint32 *)tag + tag->size);
}
/*****************************************************************************/

static struct tag_hdr_t *get_tag_buf(struct tag_hdr_t *tag, uint32 type,
				     char **buf, uint32 buflen)
{
	tag->type = type;
	tag->size = (sizeof(struct tag_hdr_t) + buflen + 3) >> 2;
	*buf = (char*)&tag[1];
	return (struct tag_hdr_t *)((uint32 *)tag + tag->size);
}
/*****************************************************************************/

static struct tag_hdr_t *setup_param_tag(struct tag_hdr_t *tag)
{
	char *buf = (char*)&tag[1];

	tag->type = 0x70000001;
	tag->size = (sizeof(struct tag_hdr_t) + get_param_tag_data(buf) + 3) >> 2;

	return (struct tag_hdr_t *)((uint32 *)tag + tag->size);
}
/*****************************************************************************/

uint32 get_kern_tags(uint32 kernel)
{
	char *buf;
	int buflen;
	uint32 *num;
	uint32 start = CONFIG_TAG_OFFSET; // TODO: XXX
	struct tag_hdr_t *tag = (struct tag_hdr_t *)start;

	printf("Save kernel parameter to 0x%08x\n", start);
	/* tag start symbol */
	buflen = sizeof(int) * 3;
	tag = get_tag_buf(tag, 0x54410001, &buf, buflen);
	memset(buf, 0, buflen);

	tag = get_tag_buf(tag, 0x54410002, (char **)&num, sizeof(int) * 2);
	// TODO: 这里应该从系统自动获取
	*num++ = _1G;
	*num++ = 0;

#ifdef CONFIG_BOOTARGS_MERGE
	buf = bootargs_merge();
#else
	buf = env_get("bootargs");
#endif
	if (buf) {
		tag = fill_tag(tag, 0x54410009, buf, strlen(buf) + 1);
#ifdef CONFIG_BOOTARGS_MERGE
		free(buf);
#endif
	}
	tag = fill_tag(tag, 0x726d6d75, CONFIG_SDKVERSION, sizeof(CONFIG_SDKVERSION));

#ifdef CONFIG_BOOTREG
	{
		int tmp = _blank_zone_end - _blank_zone_start;
		tag = get_tag_buf(tag, 0x53000001, &buf, sizeof(int) + tmp);
		*(int*)buf = tmp;
		memcpy(buf + sizeof(int), (char *)_blank_zone_start, tmp);
	}
#endif /* CONFIG_BOOTREG */

	tag = setup_param_tag(tag);

	/* tag end symbol */
	tag->size = 0;
	tag->type = 0;

	return start;
}

