
#ifndef __CPU_PAGETABLE_H__
#define __CPU_PAGETABLE_H__

#include <sre_base.h>

#define PAGE_SIZE               4096
#define PAGE_SHIFT              12
#define PAGE_MASK               0xFFFFF000
#define PAGE_OFFSET_MASK        0x00000FFF

#define SECTION_SIZE            (1 << 20)
#define SECTION_SHIFT           20
#define SECTION_MASK            0xFFF00000
#define SECTION_OFFSET_MASK     0x000FFFFF

#define VIR_ASPACE_SIZE     (1 << 26)

#define PAGE_TABLE_ENTRIES 4096
#define PAGE_TABLE_ENTRY_WIDTH 4
#define PAGE_TABLE_SIZE (PAGE_TABLE_ENTRIES * PAGE_TABLE_ENTRY_WIDTH)


#define SECURE_ACCESS_DOMAIN    0

#define L1_SECTION_AP_MASK  0x3

/* XN Bit Values */
#define L1_EXECUTE_NEVER    1
#define L1_EXECUTE_ALLOW    0

#define L1_TYPE_MASK            0x3
#define L1_TYPE_FAULT           0x0
#define L1_TYPE_COARSE          0x1
#define L1_TYPE_SECTION         0x2

#define L1_SECTION_B_SHIFT  2
#define L1_SECTION_C_SHIFT  3
#define L1_SECTION_XN_SHIFT 4
#define L1_DOMAIN_SHIFT     5
#define L1_SECTION_AP_SHIFT 10
#define L1_SECTION_TEX_SHIFT    12
#define L1_SECTION_AP2_SHIFT    15
#define L1_SECTION_S_SHIFT  16
#define L1_SECTION_NG_SHIFT 17  /* Non-Global bit*/
#define L1_SECTION_NS_SHIFT 19  /* Non-Secure bit*/
#define L1_SECTION_NS_MASK  0x1
#define L1_SECTION_NS_IDX_MASK  (L1_SECTION_NS_MASK << L1_SECTION_NS_SHIFT)
#define L1_DOMAIN_MASK          0xf
#define L1_DOMAIN_IDX_MASK      (L1_DOMAIN_MASK << L1_DOMAIN_SHIFT)

#define SECTION_BASE_MASK       0xfff00000

#define FSR_TYPE_MASK           0x40f
#define FSR_ALIGN_FAULT         0x1
#define FSR_EXT_ABORT_L1        0xc
#define FSR_EXT_ABORT_L2        0xe
#define FSR_TRANS_SEC           0x5
#define FSR_TRANS_PAGE          0x7
#define FSR_DOMAIN_SEC          0x9
#define FSR_DOMAIN_PAG          0xb
#define FSR_PERM_SEC            0xd
#define FSR_PERM_PAGE           0xf

#define FSR_DOMAIN_MASK         0xf0
#define FSR_WNR_MASK            0x800
#define FSR_EXT_MASK            0x1000

/*h00206996 modify begin, pagetable attributes*/
#define TTBR_FLAGS_C_BIT (0x1 << 0)
#define TTBR_FLAGS_S_BIT (0x1 << 1)
#define TTBR_FLAGS_RGN(val) ((val & 0x3) << 3)
#define TTBR_FLAGS_NOS_BIT (0x1 << 5)
#define TTBR_FLAGS_IRGN_BIT (0x1 << 6)

/*outer and Inner Write-Back, Write-Allocate
  consistent with pagetable memory attribtue TEX C B 111
 */
#define TTBR_FLAGS (TTBR_FLAGS_IRGN_BIT |TTBR_FLAGS_RGN(0x01) )
/*h00206996 modify end*/

/**
 * @brief Section page table entry
 */
struct cpu_section {
/*! Virtual address */
    UINT32 va;
/*! Physical address */
    UINT32 pa;
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
/*! Padding */
    UINT32 pad:15;
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

extern UINT32 secure_page_table[PAGE_TABLE_ENTRIES];

UINT32* get_secure_ptd(void);
UINT32* map_secure_page_table(void);

int map_section_entry(UINT32 *pgd, struct cpu_section *entry, INT32 map_to_ns_flag);
int unmap_section_entry(UINT32* pgd, UINT32 va, UINT32 ap, INT32 map_to_ns_flag);
int unmap_ns_section_entry(UINT32* pgd, UINT32 va);
void mmu_init(void);
void mmu_insert_pt0(UINT32* addr);
void mmu_insert_pt1(UINT32* addr);
void mmu_enable_virt_addr(void);
void mmu_disable_virt_addr(void);
void set_domain(UINT8 domain, enum_access_type access);

#endif
