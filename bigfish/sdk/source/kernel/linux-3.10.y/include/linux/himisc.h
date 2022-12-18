/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Cai Zhiyong
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

#ifndef __HISI_MISC__
#define __HISI_MISC__

#ifdef CONFIG_BLK_DEV_INITRD
void __init initmrd_reserve_memory(void);
#else
static inline void initmrd_reserve_memory(void) {}
#endif

#ifdef CONFIG_BLK_DEV_LOOP
void __init initfile_reserve_memory(void);
#else
static inline void initfile_reserve_memory(void) {}
#endif

#endif /* __HISI_MISC__ */
