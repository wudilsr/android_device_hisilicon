/** 
 * \file
 * \brief Describes the information about HiSilicion SecureMMZ.
*/


#ifndef __SEC_MMZ_H__
#define __SEC_MMZ_H__

#include "mmz.h"

/*************************** Macro Definition ****************************/
/** \addtogroup     SecureMMZ */
/** @{ */  /** <!-- [SecureMMZ] */

/** @} */  /*! <!-- Macro Definition End */
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/******************************* API Declaration *****************************/
/** \addtogroup      SecureMMZ*/
/** @{*/  /** <!-- -SecureMMZ=*/

/**
\brief Allocate memory block.
\attention \n
N/A
\param[in]  size        The size of the memory block to be allocated.
\param[in]  mmz_name    The name of the memory pool for allocation, should be "SEC-MMZ" currently.
\param[in]  mmb_name    The name of the memory block.
\retval ::non-zero   Success, return the physical address of the block.
\retval ::NULL       Fail to allocate memory block.
\see \n
N/A
*/
void *HI_SEC_MMZ_New(unsigned int size , char *mmz_name, char *mmb_name);

/**
\brief Free the memory block.
\attention \n
N/A
\param[in]  phys_addr    The physical address of the memory block.
\retval ::0   Success.
\retval ::non-zero Fail to free the memory block.
\see \n
N/A
*/
int HI_SEC_MMZ_Delete(unsigned int phys_addr);

/**
\brief Map the memory block.
\attention \n
N/A
\param[in]  phys_addr    The physical address of the memory block.                       
\param[in]  cached       Indicating whether the memory is cached or non-cacheable, 1 - cached, 0 - non-cacheable      
\retval ::The virtual address   Success                                           
\retval ::NULL   Fail to map the memory block                                   
\see \n
N/A
*/
void *HI_SEC_MMZ_Map(unsigned int phys_addr, unsigned int cached);

/**
\brief Unmap the memory block.
\attention \n
N/A
\param[in]  phys_addr    The physical address of the memory block.          
\retval ::0   Success                                                     
\retval ::non-zero  Fail to unmap the memory block.                          
\see \n
N/A
*/
int HI_SEC_MMZ_Unmap(unsigned int phys_addr);

/**
\brief Cache flush.
\attention \n
N/A
\param[in]  phys_addr    The physical address of the memory block.     
\retval ::0   Success                                                    
\retval ::non-zero  Fail to flush the memory block.                         
\see \n
N/A
*/
int HI_SEC_MMZ_Flush(unsigned int phys_addr);

/**
\brief Allocate and map the memory block.
\attention \n
N/A
\param[in]  size        The size of the memory block to be allocated.             
\param[in]  cached       Indicating whether the memory is cached or non-cacheable, , 1 - cached, 0 - non-cacheable  .      
\param[in]  mmz_name    The name of the memory pool to allocate from.            
\param[in]  mmb_name    The name of the memory block.                            
\param[in]  phys_addr    The physical address of the memory block.              
\retval ::non-zero   Success, return the physical address of the block.         
\retval ::NULL       Fail to new or map.                              
\see \n
N/A
*/
void *HI_SEC_MMZ_NewAndMap(unsigned long size , unsigned int cached, char *mmz_name, char *mmb_name, char **phys_addr);

/**
\brief Free and unmap the memory block.
\attention \n
N/A
\param[in]  phys_addr    The physical address of the memory block.  
\retval ::0   Success                                           
\retval ::non-zero  Fail to delete or unmap.              
\see \n
N/A
*/
int HI_SEC_MMZ_DelAndUnmap(unsigned long phys_addr);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SEC_MMZ_H__ */
