/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_CUTILS_ATOMIC_ARM_HISILICON_H
#define ANDROID_CUTILS_ATOMIC_ARM_HISILICON_H

#include <stdint.h>
#include "cutils/cpu-features.h"

extern inline void android_compiler_barrier(void)
{
    __asm__ __volatile__ ("" : : : "memory");
}

extern inline void android_memory_barrier(void)
{
    typedef void (kuser_memory_barrier)(void);
    (*(kuser_memory_barrier*)0xffff0fa0)();
}
extern inline void android_memory_store_barrier(void)
{
    android_memory_barrier();
}

extern inline int32_t android_atomic_acquire_load(volatile const int32_t* ptr)
{
    int32_t value = *ptr;
    android_memory_barrier();
    return value;
}

extern inline int32_t android_atomic_release_load(volatile const int32_t* ptr)
{
    android_memory_barrier();
    return *ptr;
}

extern inline void android_atomic_acquire_store(int32_t value,
        volatile int32_t* ptr)
{
    *ptr = value;
    android_memory_barrier();
}

extern inline void android_atomic_release_store(int32_t value,
        volatile int32_t* ptr)
{
    android_memory_barrier();
    *ptr = value;
}

extern inline int android_atomic_cas(int32_t old_value, int32_t new_value,
                                     volatile int32_t* ptr)
{
    typedef int (kuser_cmpxchg)(int32_t, int32_t, volatile int32_t*);
    int32_t prev, status;
    prev = *ptr;
    do
    {
        status = (*(kuser_cmpxchg*)0xffff0fc0)(old_value, new_value, ptr);
        if (__builtin_expect(status == 0, 1))
        { return 0; }
        prev = *ptr;
    }
    while (prev == old_value);
    return 1;
}

extern inline int android_atomic_acquire_cas(int32_t old_value,
        int32_t new_value,
        volatile int32_t* ptr)
{
    int status = android_atomic_cas(old_value, new_value, ptr);
    android_memory_barrier();
    return status;
}

extern inline int android_atomic_release_cas(int32_t old_value,
        int32_t new_value,
        volatile int32_t* ptr)
{
    android_memory_barrier();
    return android_atomic_cas(old_value, new_value, ptr);
}

extern inline int32_t android_atomic_add(int32_t increment,
        volatile int32_t* ptr)
{
    int32_t prev, status;
    android_memory_barrier();
    do
    {
        prev = *ptr;
        status = android_atomic_cas(prev, prev + increment, ptr);
    }
    while (__builtin_expect(status != 0, 0));
    return prev;
}

extern inline int32_t android_atomic_inc(volatile int32_t* addr)
{
    return android_atomic_add(1, addr);
}

extern inline int32_t android_atomic_dec(volatile int32_t* addr)
{
    return android_atomic_add(-1, addr);
}

extern inline int32_t android_atomic_and(int32_t value, volatile int32_t* ptr)
{
    int32_t prev, status;
    android_memory_barrier();
    do
    {
        prev = *ptr;
        status = android_atomic_cas(prev, prev & value, ptr);
    }
    while (__builtin_expect(status != 0, 0));
    return prev;
}

extern inline int32_t android_atomic_or(int32_t value, volatile int32_t* ptr)
{
    int32_t prev, status;
    android_memory_barrier();
    do
    {
        prev = *ptr;
        status = android_atomic_cas(prev, prev | value, ptr);
    }
    while (__builtin_expect(status != 0, 0));
    return prev;
}

#endif /* ANDROID_CUTILS_ATOMIC_ARM_HISILICON_H */
