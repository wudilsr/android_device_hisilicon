/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _BOOT_H_
#define _BOOT_H_

#define SZ_1KB		1024
#define SZ_1MB		(SZ_1KB*SZ_1KB)

static inline void DWB(void) /* drain write buffer */
{
    asm volatile (
        "mcr p15, 0, %0, c7, c10, 4\n" : : "r" (0)
        );
}

static inline void writel(unsigned val, unsigned addr)
{
    DWB();
    (*(volatile unsigned *) (addr)) = (val);
    DWB();
}

static inline void writew(unsigned val, unsigned addr)
{
    DWB();
    (*(volatile unsigned short *) (addr)) = (val);
    DWB();
}

static inline void writeb(unsigned val, unsigned addr)
{
    DWB();
    (*(volatile unsigned char *) (addr)) = (val);
    DWB();
}

static inline unsigned readl(unsigned addr)
{
    return (*(volatile unsigned *) (addr));
}

static inline unsigned readw(unsigned addr)
{
    return (*(volatile unsigned short *) (addr));
}

static inline unsigned char readb(unsigned addr)
{
    return (*(volatile unsigned char *) (addr));
}

static inline void clr_bit( unsigned val, unsigned bit )
{
    (val) = ( val & ( ~( 1<<bit ) ) );
}

static inline void set_bit( unsigned val, unsigned bit )
{
    (val) = ( val | ( 1<<bit ) );
}

void enable_irq(void);

/* manage a list of functions to call */
void boot_register_poll_func(void (*func)(void));
void boot_poll(void);
void boot_unregister_all_poll_func(void);

/* console.c */
void dprintf(const char *fmt, ...);
void dprintf_set_putc(void (*func)(unsigned));
void dprintf_set_flush(void (*func)(void));

/* gpio */
void gpio_output_enable(unsigned n, unsigned out);
void gpio_write(unsigned n, unsigned on);
int gpio_read(unsigned n);

/* misc.c */
void *alloc(unsigned sz); /* alloc 32byte aligned memory */
void *alloc_page_aligned(unsigned sz);

void *memcpy(void *dst, const void *src, unsigned len);
void *memset(void *dst, unsigned val, unsigned len);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *cs, const char *ct, unsigned int count);
int memcmp(const void *a, const void *b, unsigned len);
char *strstr(const char *s1, const char *s2);
int strlen(const char *s);
char *strncpy(char *dest, const char *src, unsigned int count);
char *strcat(char *s, const char *append);
char *strncat(char *dst, const char *src, unsigned int n);

/* clock */
unsigned cycles_per_second(void);
void print_cpu_speed(void);
//void mdelay(unsigned msecs);
//void udelay(unsigned usecs);

/* LCD */
void console_init(void);
void console_reinit(void);
void console_set_colors(unsigned bg, unsigned fg);
void console_clear(void);
void console_putc(unsigned n);
void console_flush(void);

void cprintf(const char *fmt, ...);

const char *get_fastboot_version(void);
void usbloader_init(void);

/* provided by board files */
void set_led(int on);

typedef void (*irq_handler)(unsigned n);

#define DIGEST_SIZE 20
#define SIGNATURE_SIZE 256

void compute_digest(void *data, unsigned len, void *digest_out);
int is_signature_okay(void *digest, void *signature, void *pubkey);

#if 0
#define __attr_used __attribute__((used))
#define __attr_init __attribute__((__section__(".init.func.0")))
#define boot_init_hook(func) \
static int (*__boot_init_hook__)(void) __attr_used __attr_init = func
#endif


#define DBG_ERR		0x0001	/* report all error returns */
#define DBG_WARNING		0x0002	/* warning info*/
#define DBG_INFO		0x0004	/* debug info */
#define DBG_ALL		0xffff
#define DBG_NONE	0x0000

#define DEBUG_LEVEL	(DBG_ERR)
#define USB_DBG(level, fmt, ...)	\
	do {							\
		if ((level) & DEBUG_LEVEL)			\
			cprintf("USB: " fmt, ## __VA_ARGS__);	\
	} while (0)

#define DBG_DUMP_BUF(buf, len) do{\
	int i;\
	int *p = (void*)(buf);\
	for(i=0; i<(int)((len)/sizeof(*p)); i++){\
		cprintf("0x%x ", *(p+i));\
		if( !((i+1) & 0x07) )\
			cprintf("\n");\
	}\
	cprintf("\n");\
}while(0)

#endif
