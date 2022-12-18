
#ifndef __CPU_PAGETABLE_H__
#define __CPU_PAGETABLE_H__

#include <sre_base.h>
#include <sre_arm_mmu.h>
#include <sre_task.h>


extern UINT32 g_TEXT_BASE;//added by fangjian
extern UINT32 g_TRUSTEDCORE_VIRT_BASE;//added by fangjian
extern UINT32 g_TASK_MEM_BASE_ADDRESS;//added by fangjian
extern UINT32 g_TRUSTEDCORE_KERNEL_MEM_SIZE;//added by fangjian

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif


#ifdef ARM_PAE
/* Physical address in the system */
typedef UINT64 paddr_t;

/* PTE type */
typedef UINT64 pte_t;

/* Page table pointer */
typedef UINT64 pmd_t;
#else
/* Physical address in the system */
typedef UINT32 paddr_t;

/* PTE type */
typedef UINT32 pte_t;
#endif

/* Global page table pointer definition */
typedef pte_t* pgd_t;

#define virt_to_phys(addr)  ((paddr_t)((UINT32)(addr) - g_TRUSTEDCORE_VIRT_BASE + g_TEXT_BASE))
#define phys_to_virt(addr)  ((UINT32)((addr) - g_TEXT_BASE + g_TRUSTEDCORE_VIRT_BASE))

/**
 * @brief Section page table entry
 */
struct cpu_section {
/*! Virtual address */
    UINT32 va;
/*! Physical address */
    paddr_t pa;
/*! Size */
    UINT32 sz;
/*! NS bit */
    UINT32 ns:1;
/*! NG bit */
    UINT32 ng:1;
/*! Shared bit */
    UINT32 s:1;
/*! Tex bits */
    UINT32 tex:3;
/*! AP bit */
    UINT32 ap:3;
/*! Implementation defined */
    UINT32 imp:1;
/*! Domain field */
    UINT32 dom:4;
/*! XN bit */
    UINT32 xn:1;
/*! Cache bit */
    UINT32 c:1;
/*! Bufferable bit */
    UINT32 b:1;
/*! Priviledged XN */
    UINT32 pxn:1;
/*! Padding */
    UINT32 pad:14;
};

/**
 * @brief Memory access control constants
 */
typedef enum
{
/*!Priv no access, usr no access */
  PRIV_NO_USR_NO = 0,
/*!Priv read/write, usr no access */
  PRIV_RW_USR_NO = 1,
/*!Priv read/write, usr read only */
  PRIV_RW_USR_RO = 2,
/*!Priv read/write, usr read/write */
  PRIV_RW_USR_RW = 3,
/*!Reserved */
  AP_RESERVED = 4,
/*!Priv read only, usr no access */
  PRIV_RO_USR_NO= 5,
/*!Deprecated */
  DEPRECATED=6,
/*!Priv read only, usr read only */
  PRIV_RO_USR_RO= 7,
}ACCESS_TYPE;

/*Access is a two bit field
 *  00 = no access,
 *  01=client,
 *  10=reserved,
 *  11=manager
 */
typedef enum
{
    no_access = 0,
    client,
    reserved,
    manager
}enum_access_type;

typedef enum{
    cache = 1,
    non_cache = 0
}cache_mode_type;

typedef enum
{
    secure = 0,
    non_secure = 1
}secure_mode_type;

typedef enum
{
    USED_BY_SVC = 0,
    USED_BY_USR = 1
}user_mode_type;

typedef struct {
    UINT32 ap  : 3;
    UINT32 tex : 3;
    UINT32 b   : 1;
    UINT32 c   : 1;
    UINT32 xn  : 1;
    UINT32 pxn : 1;
    UINT32 ng  : 1;
}spt_attr;

typedef struct {
    paddr_t phy_addr;
    UINT32 size;
    UINT32 virt_addr;
    spt_attr attr;  //bit[2-0] ap;  bit[5-3] tex; bit[6] b; bit[7] c
    UINT32 reserved1;
    UINT32 reserved2;
}secure_mmu_config;


extern pgd_t secure_page_table;

pgd_t get_secure_ptd(void);
pgd_t map_secure_page_table(void);

int unmap_from_ns(UINT32 va_addr, UINT32 size);
#if 0
int map_discontinuous_phy_mem(UINT32 ns_buff_phy_addr, UINT32 size, secure_mode_type secure_mode, cache_mode_type cache_mode, UINT32 *vm_addr);
int unmap_discontinuous_phy_mem(unsigned int virt_addr, unsigned int total_size);
#endif
#if 0
int map_section_entry(UINT32 *pgd, struct cpu_section *entry, INT32 map_to_ns_flag);
void mmu_init(void);
void mmu_insert_pt0(UINT32* addr);
void mmu_insert_pt1(UINT32* addr);
void mmu_enable_virt_addr(void);
void mmu_disable_virt_addr(void);
void set_domain(UINT8 domain, enum_access_type access);

/* Setup task memory before load */
void SRE_SMemPrepareTaskLoad(UINT32 addr, UINT32 size);
#endif
int map_to_ns(paddr_t phy_addr, UINT32 size, secure_mode_type  non_secure);
int unmap_from_ns_page(UINT32 virt_addr, unsigned int size);
int map_from_ns_page(paddr_t base_addr, unsigned int size, unsigned int* vm_addr, secure_mode_type  non_secure);
UINT32 unmap_task_mem(unsigned int virt_addr, unsigned int size);

//Note:map into TA address space
int mmap(UINT32 phy_addr , UINT32 size, UINT32 *virt_addr,secure_mode_type secure_mode, cache_mode_type cache_mode);
//int mmap(UINT32 phy_addr, UINT32 size, secure_mode_type secure_mode, cache_mode_type cache_mode, UINT32 *va_addr);
int unmap(UINT32 va_addr, UINT32 size);

int sre_mmap(unsigned int base_addr, unsigned int size, unsigned int * vm_addr, secure_mode_type secure_mode, cache_mode_type cache_mode);
int sre_unmap(unsigned int virt_addr, unsigned int size);
//Note:map into RTOSCK address space
int SRE_mem_remap(unsigned int base_addr, unsigned int size, unsigned int * vm_addr, secure_mode_type secure_mode, cache_mode_type cache_mode);
int SRE_mem_unmap(unsigned int virt_addr, unsigned int size);

/*
 *@brief:map discontinuous phy mem to continuous virt mem
 *
 *@param ns_buf_pa[IN]:point to a buffer -- list of TEE_PAGEINFO
 *@param size[IN]:the total size of phy mem (must page align)
 *@param vm_addr[OUT]:
 *@param secure_mode[IN]:
 *@param cache_mode[IN]:
 *@param user_mode[IN]:USED_BY_SVC in rtosck, USED_BY_USR by TA
*/

int map_discontinuous_phy_mem
(
    UINT32 ns_buf_pa, 
    UINT32 size, 
    UINT32 *vm_addr, 
    secure_mode_type secure_mode, 
    cache_mode_type cache_mode, 
    user_mode_type user_mode
);
int unmap_discontinuous_phy_mem(unsigned int virt_addr, unsigned int size, user_mode_type user_mode);


UINT32 release_task_mem(void);
UINT32 map_task_mem_for_ta(UINT32 rnd_offset, UINT32 lib_base_addr, UINT32 lib_size, UINT32 base_addr, UINT32 size);

int task_unmap_from_ns_page(TSK_HANDLE_T uwTaskPID, UINT32 virt_addr, unsigned int size);
int task_map_from_ns_page(TSK_HANDLE_T uwTaskPID, paddr_t base_addr, unsigned int size, unsigned int* vm_addr, secure_mode_type  non_secure);
int task_map_from_task(UINT32 task_id_in, UINT32 va_addr, UINT32 size, UINT32 task_id_out, unsigned int *vm_addr);
int tee_mmu_check_access_rights(UINT32 flag, UINT32 va, UINT32 size);
unsigned int is_valid_virt_mem(unsigned int addr, unsigned n);
#define ACCESS_CHECK(addr, size)  if(!is_valid_virt_mem(addr, size)){\
				    regs->r0 = OS_ERROR;\
				    uart_printf_func("ERROR!!!!, it seems the input buffer is not valid line is %d\n", __LINE__);\
				    break;\
				    }

#define ACCESS_READ_RIGHT_CHECK(addr, size)  if(tee_mmu_check_access_rights(ACCESS_READ, addr, size)){\
				    regs->r0 = OS_ERROR;\
				    uart_printf_func("ERROR!!!!, it seems the input buffer READ denied line is %d\n", __LINE__);\
				    break;\
				    }

#define ACCESS_WRITE_RIGHT_CHECK(addr, size)  if(tee_mmu_check_access_rights(ACCESS_WRITE , addr, size)){\
				    regs->r0 = OS_ERROR;\
				    uart_printf_func("ERROR!!!!, it seems the input buffer write denied line is %d\n", __LINE__);\
				    break;\
				    }

#endif

void asm_memmove(void* dest, void* src, UINT32 size);
void asm_memcpy(void* dest, void* src, UINT32 size);
