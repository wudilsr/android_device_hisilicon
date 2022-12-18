/**
**  @file nocs_csd.h 
**
** @brief
**    Chipset Security Driver API for NOCS Secure chipset
**
**  $Id: //CAK/components/csdapi/MAIN/src/nocs_csd.h#10 $
**
** REMARK:
**   Comments in this file use special tags to allow automatic API documentation 
**   generation in HTML format, using the GNU-General Public Licensed Doxygen 
**   tool. For more information about Doxygen, please check www.doxygen.org
**
**   Depending on the platform, the CHM file may not open properly if it is 
**   stored on a network drive. So either the file should be moved on a local 
**   drive or add the following registry entry on Windows platform (regedit):\n
**   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\\ItssRestrictions] "MaxAllowedZone"=dword:00000003
*/  

#ifndef CSD_H
#define CSD_H

/**
 * Defines the version number of the CSD API. Note also that this version number 
 * does not correspond to the version number of the software version. 
 * @warning Do not update these values
*/
#define CSDAPI_VERSION_MAJOR  3
#define CSDAPI_VERSION_MEDIUM 3
#define CSDAPI_VERSION_MINOR  5

/** @page p_history History
 *
 *   - <b> 3.3.5 2012/10/05 Jean-Luc Bussy</b>
 *     - Removed CTR mode that was introduced in this API by mistake
 *
 *   - <b> 3.3.4 2012/06/29 Jean-Luc Bussy</b>
 *     - Defined NOCS3 and NOCS1 API profiles and tagged each function with the
 *       applicable NOCS version.
 *     - Updated functions description layout
 *
 *   - <b> 3.3.3 2012/05/25 Jean-Luc Bussy</b>
 *     - The function csdGetNuid() must apply to NOCS3.0 chipsets as well. 
 *       Modified the function description accordingly.
 *
 *   - <b> 3.3.2 2012/05/15 Jean-Luc Bussy</b>
 *     - Updated some doxygen group definitions
 *     - Fixed few minor description inconsistencies
 *
 *   - <b> 3.3.1 2012/05/02 Jean-Luc Bussy</b>
 *     - Removed all flash protection key encryption/decryption operations. Now 
 *       part of SEC API RAM2RAM operations.
 *     - Removed variable declaration for TCsdKeyLadderDeactivationFlag and 
 *       TCsdScsActivationFlag and made it types of TCsdActivationFlag 
 *
 *   - <b> 3.2.1 2012/03/01 11:30:00 Nocs team</b>
 *     - Cosmetical changes only. Added Copyright information in order to generate 
 *       new chm file.
 *
 *   - <b> 3.2.0 2012/02/22 11:30:00 Nocs team</b>
 *     - Added NOCS1.x functions csdGetNuid(), csdSetScsTotalAreaSize() 
 *       and csdGetScsTotalAreaSize(), csdEncryptDataWithClearTextHostKey(),
 *       csdDecryptDataWithClearTextHostKey(), csdEncryptDataWithSecretContentKey()
 *       and csdEncryptDataWithSecretContentKey(). 
 *     - Removed the functions csdEncryptData(), csdDecryptData(), 
 *       csdSetClearTextRam2RamHostKey(), csdSetProtectedRam2RamContentKeys(). 
 *     - Removed csdEncryptDataWithClearTextFlashProtectionKey().
 *  
 *   - <b> 3.1.0 2011/12/13 11:30:00 Nocs team</b>
 *     - Added csdGetApiVersion function
 *  
 *   - <b> 3.0.1 2011/08/15 11:30:00 Nocs team </b>
 *     - Updated comments 
 *     - Added the following functions:
 *       - csdSetRamUnscrambledStorageSize
 *       - csdGetRamUnscrambledStorageSize
 *     - Change CSD_SCS_PV_DTE_BOOT_CODE_AREA_SIZE name to
 *       CSD_SCS_PV_SCS_TOTAL_AREA_SIZE.
 *     - Added missing type: TCsdFPKeyPathHandle
 *  
 *   - <b> 3.0.0 2011/07/29 11:30:00 Nocs team </b>
 *     - First version to be used for NOCS3 Certification.
 */

/******************************************************************************/
/*                                                                            */
/*                               INCLUDE FILES                                */
/*                                                                            */
/******************************************************************************/

#include <stddef.h>


/******************************************************************************/
/*                                                                            */
/*                             OVERALL DOCUMENTATION                          */
/*                                                                            */
/******************************************************************************/

/** 
 * @mainpage Overview
 *  - @subpage p_preface
 *  - @subpage p_history
 *  - @subpage p_emi
 *  - @subpage p_api_profile
 *  
 *  <hr>Copyright &copy; 2012 Nagravision. All rights reserved.\n
 *  CH-1033 Cheseaux, Switzerland\n
 *  Tel: +41 21 7320311  Fax: +41 21 7320100\n
 *  http://www.nagra.com
 *
 *  All trademarks and registered trademarks are the property of their respective
 *  owners.
 *
 *  This document is supplied with an understanding that the notice(s) herein or
 *  any other contractual agreement(s) made that instigated the delivery of a
 *  hard copy, electronic copy, facsimile or file transfer of this document are
 *  strictly observed and maintained.
 *
 *  The information contained in this document is subject to change without notice.
 *
 *  <b>Security Policy of Nagravision Kudelski Group</b>\n
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 */

/** @page p_preface Preface
 *
 *  <h2>Purpose</h2>
 *  This document is intended for the manufacturers of MPEG secure chipsets who 
 *  are partners of Nagravision and whose chipset implements security features as 
 *  required  by NOCS requirement specification.
 *
 *  This document specifies the CSD - Chipset Security Driver Application Programming 
 *  Interface that exposes security functionalities defined in the NOCS specification.
 *
 *  It is assumed that the reader is familiar with the NOCS concepts, requirements 
 *  and recommendations.
 *
 *  This API shall be implemented by the chipset manufacturers for any new NOCS 
 *  secure chipset that is candidate to a Nagra NOCS certification.
 *
 *  <hr><h2>Audience</h2>
 *  This document is intended for MPEG secure chipset manufacturers implementing  
 *  NOCS requirements and candidate to a NOCS certification.
 *  
 *  <hr><h2>References</h2>
 *  - [EMI] Nagravision, System Architecture, Encryption Method Indicator Specification, 
 *    Version 1.0.7\n
 *  - [NOCS3REQ] Nagravision, NOCS3.0 Security Requirements Specification\n
 */

/** @page p_emi Encryption Method Indicator (EMI)
 *  
 *  There are many ways to encrypt data. An encryption algorithm (like AES, 
 *  TDES, ...) with optionally its associated mode of operation (like ECB, CBC) 
 *  has, of course, to be chosen but this is often not enough to 
 *  specify unequivocally an encryption method. Indeed, some less obvious 
 *  information like data handling and key formats have also to be well defined 
 *  if interoperability between different platforms shall be ensured. Moreover 
 *  it is impossible to build a pre-defined exhaustive list of parameters 
 *  qualifying explicitly each Encryption Method because the parameters needed 
 *  could be specific to a given Encryption Method only. 
 *  
 *  Therefore, in order to deal with this complexity and to have a mean to 
 *  uniquely identify the way data are encrypted/decrypted, Nagravision 
 *  allocates a unique 16-bits identifier, referred to as EMI, to all referenced 
 *  Encryption Methods (see [EMI]). Each Encryption Method identified by its EMI 
 *  has a dedicated detailed specification. That specification might either be 
 *  an international standard or a Nagravision specification.
 *  
 */

/** @page p_api_profile NOCS3/NOCS1 API Profiles
 *  
 *  The CSD API applies to NOCS1 and NOCS3 chipset certification. However, depending
 *  on the NOCS version, some functions need to be implemented and some others
 *  not. This section defines two profiles to know exactly which functions has
 *  to be implemented for the certification of a NOCS1 or NOCS3 chipset.
 *
 *  <hr><h2>NOCS3 Profile</h2>
 *  The certification of a NOCS3 chipset requires <b>all functions</b> of this 
 *  API to be implemented, <b>except</b>:
 *  - csdSetScsTotalAreaSize()
 *  - csdGetScsTotalAreaSize()
 *
 *  <hr><h2>NOCS1 Profile</h2>
 *  The certification of a NOCS1 chipset requires <b>all functions</b> of this 
 *  API to be implemented, <b>except</b>:
 *  - csdGetNuid64()
 *  - csdSetRamUnscrambledStorageSize()
 *  - csdGetRamUnscrambledStorageSize()
 *  - csdSetScsPv()
 *  - csdGetScsPv()
 *  - csdEnableRamScrambling()
 *  - csdGetScramblingActivationFlag()
 *  - csdEnableFlashProtection()
 *  - csdGetFlashProtectionActivationFlag()
*/

/******************************************************************************/
/*                                                                            */
/*                              GROUPS DEFINITION                             */
/*                                                                            */
/******************************************************************************/

/** @defgroup driversetting Driver Settings */

/** @defgroup chipinfo Chipset Configuration */

/** @defgroup scsboot SCS & Boot Configuration */

/** @defgroup memprot Memory Protection 
 *  @defgroup flashprot Flash Protection 
 *  @ingroup memprot
 *
 *  @defgroup ramprot RAM Protection 
 *  @ingroup memprot
*/

/** @defgroup debug Debug Interface */

/** @defgroup ram2ram RAM 2 RAM Operations */

/** @defgroup dvr DVR Key Safe */

/** @defgroup dsc DSC Functions */

/** @defgroup scr SCR Functions*/


/******************************************************************************/
/*                                                                            */
/*                              VERSION TOOL                                  */
/*                                                                            */
/******************************************************************************/

#ifndef CSD_TOOL_VERSION
#define CSD_TOOL_STRINGIFY(s) CSD_TOOL_TOSTRING(s)
#define CSD_TOOL_TOSTRING(s)  #s

#define CSD_TOOL_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
#define CSD_TOOL_VERSION_DOT(a, b, c) a ##.## b ##.## c
#define CSD_TOOL_VERSION(a, b, c) CSD_TOOL_VERSION_DOT(a, b, c)
#endif

#define CSDAPI_VERSION_INTER CSD_TOOL_VERSION(CSDAPI_VERSION_MAJOR, \
              CSDAPI_VERSION_MEDIUM, \
              CSDAPI_VERSION_MINOR)

#define CSDAPI_VERSION_INT   CSD_TOOL_VERSION_INT(CSDAPI_VERSION_MAJOR, \
            CSDAPI_VERSION_MEDIUM, \
            CSDAPI_VERSION_MINOR)

#define CSDAPI_VERSION_STRING  "CSDAPI_" CSD_TOOL_STRINGIFY(CSDAPI_VERSION_INTER)



/******************************************************************************/
/*                                                                            */
/*                              TYPE DEFINITION                               */
/*                                                                            */
/******************************************************************************/

/**
 *  @brief
 *    Boolean Type.
*/
typedef unsigned char TCsdBoolean;

#ifndef FALSE
/**
 *  @brief
 *    The boolean FALSE value.
*/
#define FALSE      0
#endif

#ifndef TRUE
/**
 *  @brief
 *    The boolean TRUE value.
*/
#define TRUE        (!FALSE)
#endif

/**
 *  @brief
 *    Define the parameters for the initialization of the Chipset Security
 *    Driver.
 *
 *    SCsdInitParameters is a chipset specific structure that has to be defined
 *    in nocs_csd_impl.h.
*/

typedef struct SCsdInitParameters TCsdInitParameters;

/**
 *  @brief
 *    Define the parameters for the termination of the Chipset Security Driver.
 *
 *    SCsdTerminateParameters is a chipset specific structure that has to be
 *    defined in nocs_csd_impl.h.
*/

typedef struct SCsdTerminateParameters TCsdTerminateParameters;

/**
 *  @brief
 *    20 characters strings.
 *
 *  Defines a string buffer of 20 characters.
*/
typedef unsigned char TCsd20CharsString[20];

/**
 *  @brief
 *    32 bits vectors.
 *
 *  TCsd4BytesVector defines a 32 bits vector for the MarketSegmentID,
 *  CheckNumber and NUID values. 
*/
typedef unsigned char TCsd4BytesVector[4];

/**
 *  @brief
 *    64 bits vectors.
 *
 *  TCsd8BytesVector defines a 64 bits vector for the NUID 64 bit
 *  value. 
*/
typedef unsigned char TCsd8BytesVector[8];

/**
 *  @brief
 *    Define the set of available memory interface during the chipset boot.
 *
 *  ECsdBootMode is a chipset specific enumeration to be defined in 
 *  nocs_csd_impl.h. Each implementation shall define its own set of available 
 *  memory interface from which the chipset is able to boot according to its 
 *  capabilities.
*/
typedef enum ECsdBootMode TCsdBootMode;


/**
 *  @brief
 *    Define the set of available NOCS3 SCS sizes.
 *
 *  ECsdScsSize is a chipset specific enumeration to be defined in 
 *  nocs_csd_impl.h. Each implementation shall define its own set of 4 available 
 *  sizes from which the chipset is able to boot.
*/
typedef enum ECsdScsSize TCsdScsSize;

/**
 *  @brief
 *    Defines the state of the Activation Flag of either the SCS, Scrambling or Flash Protection.
 *
 *  Defines the state of the SCS, Scrambling or Flash Protection Activation Flag.
*/
typedef enum
{
  CSD_ACTIVATION_FLAG_SET = 0,
    /**< The PV value is set or the functionality is enabled.
     */
  CSD_ACTIVATION_FLAG_NOT_SET,
    /**< The PV value is not see or the functionality is disabled.
     */
  LAST_CSD_ACTIVATION_FLAG
    /**< Upper boundary of the TCsdActivationFlag type.
     */
}TCsdActivationFlag;

/*
 * @brief
 * Defines the state of the SCS Activation, used by the function 
 * csdGetScsActivationFlag().
 *
 */
typedef TCsdActivationFlag TCsdScsActivationFlag;
    /**< Defines the state of the SCS Activation, used by the function 
     * csdGetScsActivationFlag().
     */
typedef TCsdActivationFlag TCsdKeyLadderDeactivationFlag;
    /**< Defines the state of the Key ladder deactivation, used by the 
     * function API csdGetKeyLadderDeactivationFlag().
     */


/**
 *  @brief
 *    Defines names related to the SCS Persistent Values.
 *
*/
typedef enum
{
  CSD_SCS_PV_EXT_BOOT_FLASH_DEV_PARAMS = 0,
    /**< External Boot Flash Device Parameters: PV to configure the External 
     * Non-Volatile Storage.
     */
  CSD_SCS_PV_EXT_RAM_PARAMS,
    /**< External RAM Parameters: PV to configure the External RAM.
     */
  CSD_SCS_PV_SCS_TOTAL_AREA_SIZE,
    /**< SCS Total Area Size: PV to set the SCS Total Area Size.
     */
  CSD_SCS_PV_ACTIVE_INDICATOR,
    /**< Active Indicator: PV to determine the active region of the Ext. SCS FW.
     */
  CSD_SCS_PV_FULL_EXT_FW_UPGRADE_ADDR,
    /**< Full External Firmware Upgrade Address: PV to set the address of the Full 
     *   External FW Upgrade.
     */
  CSD_SCS_PV_FULL_EXT_FW_UPGRADE_SIZE,
    /**< Full External Firmware Upgrade Size: PV to set the size of the Full 
     *   External FW Upgrade.
     */
  CSD_SCS_PV_PATCH_EXT_FW_UPGRADE_ADDR,
    /**< Patch External Firmware Upgrade Address: PV to set the address of the 
     *   Patch External FW Upgrade.
     */
  CSD_SCS_PV_PATCH_EXT_FW_UPGRADE_SIZE,
    /**< Patch External Firmware Upgrade Size: PV to set the Size of the Patch 
     *   External FW Upgrade.
     */
  CSD_SCS_PV_VERSIONING_REF,
    /**< Versioning_Ref: PV to set Versioning_REF value.
     */
  LAST_CSD_SCS_PV_ID
    /**< Upper boundary of the TCsdScsPvId type.
     */
}TCsdScsPvId;

/*!
 *  @brief
 *    Size of SCS_Total_Area.
 *
 *  Defines the size of the SCS_Total_Area as defined in NOCS 1.X.
*/
typedef enum
{
  CSD_SCS_TOTAL_AREA_SIZE_16K = 0,
    /*!< The total area size checked by SCS is of 16 Kbytes.
     */
  CSD_SCS_TOTAL_AREA_SIZE_32K,
    /*!< The total area size checked by SCS is of 32 Kbytes.
     */
  CSD_SCS_TOTAL_AREA_SIZE_64K,
    /*!< The total area size checked by SCS is of 64 Kbytes.
     */
  CSD_SCS_TOTAL_AREA_SIZE_128K,
    /*!< The total area size checked by SCS is of 128 Kbytes.
     */
  CSD_SCS_TOTAL_AREA_SIZE_256K,
    /*!< The total area size checked by SCS is of 256 Kbytes.
     */
  CSD_SCS_TOTAL_AREA_SIZE_UNPROGRAMMED,
    /*!< The total area size checked by SCS is not programmed.
     */
  CSD_SCS_TOTAL_AREA_SIZE_NOT_SUPPORTED,
    /*!< The total area size checked by SCS is not supported.
     */
  LAST_CSD_SCS_TOTAL_AREA_SIZE
    /*!< Upper boundary of the TCsdScsTotalAreaSize type.
     */
}TCsdScsTotalAreaSize;

/*!
 *  @brief
 *    Define the cryptographic algorithm supported by Nagra for the RAM2RAM
 *    Crypto Engine operations.
 *
*/
typedef enum
{
  CSD_R2R_ALGORITHM_AES_128 = 0,
    /*!< AES 128 bits defined in FIPS-197, Advanced Encryption Standard.
     */
  CSD_R2R_ALGORITHM_TDES_K1K2K1,
    /*!< TDES algorithm in key option 2 defined in FIPS-46-3, Data
         Encryption Standard (DES).
     */
  LAST_CSD_R2R_ALGORITHM
    /*!< Upper boundary of the TCsdAlgorithm type.
     */
}TCsdR2RAlgorithm;

/*!
 *  @brief
 *    Define the cryptographic algorithm mode supported by Nagra for the data
 *    operations.
 *
 *  Define the cryptographic algorithm mode supported by Nagra for the data
 *  operations except the received transport stream processing.
*/
typedef enum
{
  CSD_R2R_CRYPTO_OPERATION_MODE_ECB = 0,
    /*!< Electronic Code Book mode 
     */
  CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
    /*!< Ciphered Block Chaining mode
     */
  LAST_CSD_R2R_CRYPTO_OPERATION_MODE
    /*!< Upper boundary of the TCsdR2RCryptoOperationMode type.
     */
}
TCsdR2RCryptoOperationMode;


/**
 *  @brief
 *   SCsdScsPvPathHandle is a chipset specific structure to be defined in 
 *   nocs_csd_impl.h. It holds all relevant information needed by the CSD in 
 *   order to set PV Params into the appropriated location. 
*/ 
typedef struct SCsdScsPvPathHandle TCsdScsPvPathHandle;


/**
 *  @brief
 *    Defines the debug interface access mode.
*/
typedef enum
{
  CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN = 0,
    /**< The debug interface is completly open without access protection.
     */
  CSD_DEBUG_INTERFACE_ACCESS_MODE_PASSWORD_PROTECTED,
    /**< The debug interface is protected by a password which has to be checked
         to unlock the interface.
     */
  CSD_DEBUG_INTERFACE_ACCESS_MODE_CLOSED,
    /**< The debug interface is completly closed and debug access is impossible.
      */
  CSD_DEBUG_INTERFACE_ACCESS_MODE_INCONSISTENT_STATE,
    /**< The debug interface has an inconsistent protection state.
     */
  LAST_CSD_DEBUG_INTERFACE_ACCESS_MODE
    /**< Upper boundary of the TCsdDebugInterfaceAccessMode type.
     */
}TCsdDebugInterfaceAccessMode;

/**
 *  @brief
 *    Define the byte as an 8 bits vector.
 *
 *  Definition of the byte as an 8 bits vector. This type is the smallest piece
 *  of data in the API.
*/
typedef unsigned char TCsdUnsignedInt8;

/**
 *  @brief
 *    Define a type as an 16 bits vector.
 *
 *  Definition of a type as an 16 bits vector. 
*/
typedef unsigned short int TCsdUnsignedInt16;

/**
 *  @brief
 *    Define a type as an 32 bits vector.
 *
 *  Definition of a type as an 32 bits vector. 
*/
typedef unsigned long int     TCsdUnsignedInt32;

/**
 *  @brief
 *    Define the Size data type.
 *
 *  Re-definition of the size from the size_t defined in the stddef.h file.
*/
typedef size_t TCsdSize;


/**
 *  @brief
 *   SCsdScrKeyPathHandle is a chipset specific structure to be defined in 
 *   nocs_csd_impl.h. It holds all relevant information needed by the CSD in 
 *   order to set the key of the Stream Crypto Engine into the appropriated 
 *   location.
*/ 
typedef struct SCsdScrKeyPathHandle TCsdScrKeyPathHandle;

/**
 *  @brief
 *   SCsdDscKeyPathHandle is a chipset specific structure to be defined in 
 *   nocs_csd_impl.h. It holds all relevant information needed by the CSD in 
 *   order to set the key, used by the Transport Stream Crypto Engine, into the 
 *   appropriated location.
*/ 
typedef struct SCsdDscKeyPathHandle TCsdDscKeyPathHandle;

/**
 *  @brief
 *   SCsdR2RKeyPathHandle is a chipset specific structure to be defined in 
 *   nocs_csd_impl.h. It holds all relevant information needed by the CSD in 
 *   order to set the key, used by the RAM2RAM Crypto Engine, into the 
 *   appropriated location.
*/ 
typedef struct SCsdR2RKeyPathHandle TCsdR2RKeyPathHandle;

/**
 *  @brief
 *   TCsdR2RCipheredProtectingKeys defines an array of 16-bytes R2R Ciphered
 *   Protecting Keys.
 *   CSD_R2R_NB_OF_PROTECTING_KEYS defines the number of Ciphered Protecting
 *   Keys for the Key Ladder. The default value is set to 2 as required in NOCS3. 
*/
#ifndef CSD_R2R_NB_OF_PROTECTING_KEYS
#define CSD_R2R_NB_OF_PROTECTING_KEYS 2
#endif

#if CSD_R2R_NB_OF_PROTECTING_KEYS == 0
typedef void* TCsdR2RCipheredProtectingKeys;
#define NO_PROTECTING_KEYS NULL
#else
typedef TCsdUnsignedInt8 TCsdR2RCipheredProtectingKeys \
          [CSD_R2R_NB_OF_PROTECTING_KEYS][16];
#endif

/**
 *  @brief
 *   TCsdDscCipheredProtectingKeys defines an array of 16-bytes DSC Ciphered
 *   Protecting Keys.
 *   CSD_DSC_NB_OF_PROTECTING_KEYS defines the number of Ciphered Protecting
 *   Keys for the Key Ladder. The default value is set to 2 as required in NOCS3. 
*/
#ifndef CSD_DSC_NB_OF_PROTECTING_KEYS
#define CSD_DSC_NB_OF_PROTECTING_KEYS 2
#endif

typedef TCsdUnsignedInt8 TCsdDscCipheredProtectingKeys \
          [CSD_DSC_NB_OF_PROTECTING_KEYS][16];

/**
 *  @brief
 *   TCsdScrCipheredProtectingKeys defines an array of 16-bytes SCR Ciphered
 *   Protecting Keys.
 *   CSD_SCR_NB_OF_PROTECTING_KEYS defines the number of Ciphered Protecting
 *   Keys for the Key Ladder. The default value is set to 2 as required in NOCS3. 
*/
#ifndef CSD_SCR_NB_OF_PROTECTING_KEYS
#define CSD_SCR_NB_OF_PROTECTING_KEYS 2
#endif

typedef TCsdUnsignedInt8 TCsdScrCipheredProtectingKeys \
          [CSD_SCR_NB_OF_PROTECTING_KEYS][16];

/*
 * EXTERNAL_CSD_STATUS_OFFSET could be defined in nocs_csd_impl.h and so,
 * allows the chipset manufacturer to define an offset on the lowest status
 * value returned by the CSD driver to specify its own return status code range.
 * By default CSD_STATUS_OFFSET will be set to 0.
*/
#ifdef EXTERNAL_CSD_STATUS_OFFSET
#define CSD_STATUS_OFFSET   EXTERNAL_CSD_STATUS_OFFSET
#else
#define CSD_STATUS_OFFSET   0
#endif

/**
 *  @brief
 *    Return values of the CSD functions.
 *
*/
typedef enum
{
  CSD_NO_ERROR = CSD_STATUS_OFFSET,
    /**< The intended operation was executed successfully.
     */
  CSD_ERROR,
    /**< The function terminated abnormally. The intended operation failed.
     */
  CSD_ERROR_DRIVER_ALREADY_INITIALIZED,
    /**<  The CSD is already initialized.
     */
  CSD_ERROR_INVALID_PARAMETERS,
    /**< The passed parameters are invalid.
     */
  CSD_ERROR_OPERATION_NOT_ALLOWED,
    /**< The requested operation is not allowed.
     */
  CSD_ERROR_OPERATION_NOT_SUPPORTED,
    /**< The requested operation is not supported by the chipset.
     */
  CSD_ERROR_INVALID_KEY_PATH_HANDLE,
    /**< The handle used for the cryptographic operation are invalid.
     */
  LAST_CSD_STATUS
    /**< TCsdStatus type upper boundary.
     */
} TCsdStatus;



/******************************************************************************/
/*                                                                            */
/*                             FUNCTION PROTOTYPES                            */
/*                                                                            */
/******************************************************************************/


/**
 *  @ingroup driversetting
 *
 *  @brief
 *    Initialize the CSD.
 *
 *    It has to be called once before any other function of the CSD
 *    API. This function initializes the dedicated hardware is required.
 *
 *    pxInitParameters is a pointer to a chipset specific structure. It has to be
 *    set prior to any initialization of CSD driver. In the case where external
 *    drivers would be used by the CSD, these drivers shall be initialized outside
 *    the CSD and before any calls to the CSD API.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in,out]  pxInitParameters
 *    Pointer to the location where to find the initialization parameters of the
 *    Chipset Security Driver.
 *
 *  @retval   CSD_NO_ERROR
 *    Initialization was completed successfully.
 *
 *  @retval   CSD_ERROR_DRIVER_ALREADY_INITIALIZED
 *    CSD has been already initialized.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    Structure pointed by pxInitParameters is invalid or corrupted.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdInitialize
(
  TCsdInitParameters*  pxInitParameters
);

/**
 *  @ingroup driversetting
 *
 *  @brief
 *    Terminate and clean CSD internal structures.
 *
 *    It terminates operations of the software that implements the CSD
 *    API. Among others, the function shall free all resources previously
 *    allocated by the CSD API.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in,out]  pxTerminateParameters
 *    Pointer to the location where to find the termination parameters of the 
 *    Chipset Security Driver.
 *
 *  @retval   CSD_NO_ERROR
 *    Termination was completed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    Structure pointed by pxTerminateParameters is invalid or corrupted.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdTerminate
(
  TCsdTerminateParameters*  pxTerminateParameters
);

/**
 *  @ingroup driversetting
 *
 *  @brief
 *    This function returns the version of the CSD API. Use the macro 
 *    #CSDAPI_VERSION_INT to assign the right value.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     pxCsdApiVersion
 *    32 bit value where the function has to write the CSD driver API version 
 *    using the macro CSDAPI_VERSION_INT.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    pxCsdApiVersion parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *    
*/
TCsdStatus csdGetApiVersion
(
  TCsdUnsignedInt32*  pxCsdApiVersion
);

/**
 *  @ingroup driversetting
 *
 *  @brief
 *    This function returns the version of the CSD Driver Implementation. It is 
 *    represented as a character string, the internal format being chipset 
 *    manufacturer dependent. However, the length of the string is fixed at 20 
 *    characters. The string must be terminated by the null character '\\0'.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *              
 *  @param[out]     xSoftwareVersion
 *    20 characters string where the function has to write the software version 
 *    string.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdGetSoftwareVersion
(
  TCsd20CharsString  xSoftwareVersion
);

/**
 *  @ingroup chipinfo
 *
 * @brief
 *    This function returns the revision (also called die version) for a given 
 *    chipset.
 *    
 *    Revision may include major and minor revision information. It is 
 *    represented as a character string, the internal format being chipset 
 *    manufacturer dependent. However, this internal format has to be agreed 
 *    with Nagravision and the chipset manufacturer. In any case, the size of 
 *    the string returned by the function is a maximum size of 20 characters 
 *    including the end character '\\0'.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xChipRevision
 *    20 characters string where the function has to write the chipset revision 
 *    string.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdGetChipRevision
(
  TCsd20CharsString xChipRevision
);

/**
 *  @ingroup chipinfo
 *
 * @brief
 *   This function returns the chip extension (Persistent Value Configuration) 
 *   for a given chipset.
 *
 *   It is represented as a character string, the internal format being chipset
 *   manufacturer dependent. However, this internal format has to be agreed with
 *   Nagravision and the chipset manufacturer. In any case, the size of the
 *   string returned by the function is fixed at 20 characters. The string must
 *   be terminated by the end character '\\0'.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xChipExtension
 *    20 characters string where the function has to write the chipset  
 *    configuration string.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdGetChipExtension
(
  TCsd20CharsString xChipExtension
);

/*!
 *  @ingroup chipinfo
 *
 *  @brief
 *    Get the chip Nagra Unique Id (NUID)
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xNuid
 *    4-bytes vector where the function has to write the NUID.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    -# For NOCS1.x, this function returns the NagraUniqueID32 that is programmed
 *      into the on-chip non-modifiable memory by the chipset manufacturer.
 *    -# For NOCS3.0, this function returns the 32 least significant bits of 
 *       NagraUniqueID64 that is programmed into the on-chip non-modifiable memory
 *       by the chipset manufacturer. 
*/
TCsdStatus csdGetNuid
(
  TCsd4BytesVector xNuid
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function returns the NagraUniqueID64 (NUID) that is programmed into 
 *    the NOCS3 on-chip non-modifiable memory by the chipset manufacturer.
 *    
 *  @applies
 *    NOCS3 only
 *
 *  @param[out]     xNuid64
 *    8-bytes vector where the function has to write the NUID64.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdGetNuid64
(
  TCsd8BytesVector xNuid64
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    Return the NAGRA NUID check number of the chipset, as requested by the 
 *    Nagravision NUID Reporting procedure.
 *
 *    The computation of NUID Check Number is chipset-specific, and is the 
 *    result of a computation involving the NUID64 and the Master Root Key. 
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xNUIDCheckNumber
 *    4-bytes vector where the function has to write the NUID Check Number.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    In case of NOCS1.x implementation, Nagravision and the chipset
 *    manufacturer will commonly agree during the NOCS certification process on 
 *    how to compute the NUID Check Number for this secure chipset.
*/
TCsdStatus csdGetNUIDCheckNumber
(
  TCsd4BytesVector xNUIDCheckNumber
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    Returns the CSC Data check number of the chipset.
 *
 *    The computation of CSC Data Check Number is the result of a computation 
 *    involving the TDES-RootKey128, a 16-bytes data as well as the RAM2RAM 
 *    Crypto Engine. 
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xCSCData
 *    16-bytes vector where the function has to read the data used to compute
 *    the check number.
 *  @param[out]     xCSCDCheckNumber
 *    4-bytes vector where the function has to write the CSC Data Check Number.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    As there may be several ways of configuring the RAM2RAM Crypto Engine and 
 *    its Key Ladder to compute the CSC Data Check Number, Nagravision and the 
 *    chipset manufacturer will commonly agree during the NOCS certification 
 *    process of a chipset on how to compute the CSC Data Check Number for this 
 *    secure chipset. Refer to the Security Driver Implementation Proposal 
 *    document for more details about this computation.
*/
TCsdStatus csdGetCSCDCheckNumber
(
  const TCsdUnsignedInt8    xCSCData[16],
        TCsd4BytesVector    xCSCDCheckNumber
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    Return the STBCASN check number of the chipset.
 *
 *    The computation of STBCASN is the result of a computation involving the 
 *    TDES-RootKey128, a 4-bytes data as well as the RAM2RAM Crypto Engine. 
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xSTBCASNData
 *    4-bytes vector where the function has to read the Data used to compute the
 *    check number.
 *
 *  @param[out]     xSTBCASNCheckNumber
 *    4-bytes vector where the function has to write the STB CA Check Number.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *                
 *  @note
 *    As there may be several ways of configuring the RAM2RAM Crypto Engine and 
 *    its Key Ladder to compute the STBCASN Check Number, Nagravision and the 
 *    chipset manufacturer will commonly agree during the NOCS certification 
 *    process of a chipset on how to compute the STBCASN Check Number for this 
 *    secure chipset. Refer to the Security Driver Implementation Proposal 
 *    document for more details about this computation.
*/  
TCsdStatus csdGetSTBCASNCheckNumber
(
  const TCsdUnsignedInt8    xSTBCASNData[4],
        TCsd4BytesVector    xSTBCASNCheckNumber
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    Return the Data Integrity check number of the chipset.
 *
 *    The computation of Data Integrity Check Number is chipset-specific, and is 
 *    the result of a computation involving the TDES-RootKey128, a data as well 
 *    as the RAM2RAM Crypto Engine.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      pxData
 *    Pointer to the location where the function has to read the Data used to 
 *    compute the check number.
 *
 *  @param[in]      xDataSize
 *    Size in bytes of the Data. It shall be defined between 1 and 16 bytes.
 *    
 *  @param[out]     xDataIntegrityCheckNumber
 *    4-bytes vector where the function has to write the Data Integrity Check
 *    Number.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid, e.g. xDataSize size not comprised
 *    between 1 and 16 bytes.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    As there may be several ways of configuring the RAM2RAM Crypto Engine and 
 *    its Key Ladder to compute the Data Integrity Check Number, Nagravision and 
 *    the chipset manufacturer will commonly agree during the NOCS certification 
 *    process of a chipset on how to compute the Data Integrity Check Number for 
 *    this secure chipset. Refer to the Security Driver Implementation Proposal 
 *    document for more details about this computation.
*/     
TCsdStatus csdGetDataIntegrityCheckNumber
(
  const TCsdUnsignedInt8* pxData,
  		TCsdSize           xDataSize,
        TCsd4BytesVector   xDataIntegrityCheckNumber
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function writes the chipset STBCASN.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xStbCaSn
 *    MSBF 4-bytes vector containing the STBCASN to be written in chipset memory.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The STBCASN has already been set to a different value and has been locked.
 *    
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdGetStbCaSn()
*/
TCsdStatus csdSetStbCaSn
(
  const TCsd4BytesVector xStbCaSn
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function reads the chipset STBCASN.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xStbCaSn
 *    MSBF 4-bytes vector where to copy to the chipset STBCASN
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdSetStbCaSn()
*/
TCsdStatus csdGetStbCaSn
(
  TCsd4BytesVector xStbCaSn
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function writes the chipset market segment ID
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xMarketSegmentId
 *     MSBF 4-bytes vector containing the market segment ID to be written in 
 *     chipset memory.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The market segment ID has already been set to a different value and has
 *    been locked.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdGetMarketSegmentId
*/
TCsdStatus csdSetMarketSegmentId
(
  const TCsd4BytesVector xMarketSegmentId
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function reads the market segment ID of the chipset.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xMarketSegmentId
 *    MSBF 4-bytes vector where to copy chipset market segment ID
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdSetMarketSegmentId
*/
TCsdStatus csdGetMarketSegmentId
(
  TCsd4BytesVector xMarketSegmentId
);

/**
 *  @ingroup scsboot
 *
 * @brief
 *   This function configures the Boot Mode of the chipset. Once this mode has 
 *   been been set, the chipset will always boot in this Boot Mode. 
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xBootMode
 *    Mode which has to be used by the Boot Mode
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The boot mode passed as parameter is out of type.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The boot mode has already been set to a different valid boot mode and has 
 *    been locked.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    This error is returned if the chipset does not need an internal
 *    configuration setting to boot
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *    
 *  @note
 *    -# TCsdBootMode is a specific enumeration type which has to be defined by 
 *       the chipset manufacturer depending on the Boot Mode supported by the 
 *       chipset.
 *    -# If the Boot Mode passed as parameter is already set when this function
 *       is called, it shall return CSD_NO_ERROR.  
 *
 *  @see csdGetBootMode         
*/
TCsdStatus csdSetBootMode
(
  TCsdBootMode xBootMode
);

/**
 *  @ingroup scsboot
 *
 * @brief
 *   This functions reads the Boot Mode configured. 
 *
 *   If the hardware chipset technology allows an unprogrammed state for the Boot
 *   Mode, then the enumeration type shall define this state. The function shall
 *   return this state when it is necessary.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     pxBootMode
 *    Pointer to the location where the function has to write the Boot Mode.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    This error is returned if the chipset does not need an internal
 *    configuration setting to boot
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdSetBootMode
*/
TCsdStatus csdGetBootMode
(
  TCsdBootMode* pxBootMode
);

/**
 *  @ingroup scsboot
 *
 *  @brief
 *    This function enable the Secure Chipset Startup mechanism.
 *
 *    Once enabled, this feature cannot be disabled (this mechanism is enforced 
 *    by hardware). 
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @retval   CSD_NO_ERROR
 *    The SCS feature has been successfully enabled or the SCS feature was 
 *    already enabled when this function is called.
 *
 *  @retval   CSD_ERROR
 *    This error shall be returned in all other error cases and the call shall 
 *    have no effect.
*/
TCsdStatus csdEnableScs
(
  void
);

/**
 *  @ingroup scsboot
 *
 *  @brief
 *    This functions reads the SCS Activation Flag
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     pxScsActivationFlagState
 *    Pointer to the location where the function has to write the SCS Activation 
 *    Flag State.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
*/
TCsdStatus csdGetScsActivationFlag
(
  TCsdActivationFlag* pxScsActivationFlagState
);

/**
 *  @ingroup scsboot
 *
 *  @brief
 *    This function writes an SCS Persistent Value Parameter.
 *
 *    It switches the state of one of the NOCS related SCS Persistent Value bit 
 *    fields identified by xScsPvParamsId to the state specified in pxPvValue.
 *
 *  @applies
 *    NOCS3 only
 *
 *  @param[in]      xScsPvParamsId
 *    SCS Persistent Value Parameters Identification.
 *
 *  @param[in,out]  pxPvPathHandle
 *    Pointer to the location where the function has to read the structure which 
 *    defines the SCS PV path used during SCS.
 *
 *  @param[in]      xPvLength
 *    Size in bytes of pxPvValue array.
 *
 *  @param[in]      pxPvValue
 *    Array containing the value of the parameter to be written
 *                   
 *  @retval   CSD_NO_ERROR
 *    The persistent value bit field has been written successfully or the bit field
 *    was already in the requested state when this function is called.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *              One or several parameter are invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The PV has already been set to a different value and has been locked.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    This error is returned in all other error cases and the call shall have no
 *    effect.
 *
 *  @see csdGetScsPv
*/
TCsdStatus csdSetScsPv
(
  TCsdScsPvId            xScsPvParamsId,
  TCsdScsPvPathHandle*  pxPvPathHandle, 
  TCsdUnsignedInt16      xPvLength,
  TCsdUnsignedInt8*     pxPvValue
);

/**
 *  @ingroup scsboot
 *
 *  @brief
 *    This functions reads an SCS Persistent Value.
 *
 *  @applies
 *    NOCS3 only
 *
 *  @param[in]      xScsPvParamsId
 *                   SCS Persistent Value Parameters Identification.
 *
 *  @param[in,out]  pxPvPathHandle
 *    Pointer to the location where the function has to read the structure which 
 *    defines the SCS PV path used during SCS.
 *
 *  @param[in]      xPvLength
 *    Size in bytes of the pxPvValue array
 *
 *  @param[in]      pxPvValue
 *    Array where to copy the persistent value field
 *                   
 *  @retval   CSD_NO_ERROR
 *    The persistent value field has been read successfully
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    One or several parameter are invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested PV Parameter is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    Any other error
 *
 *  @see csdSetScsPv
 */
TCsdStatus csdGetScsPv
(
  TCsdScsPvId            xScsPvParamsId,
  TCsdScsPvPathHandle*  pxPvPathHandle,
  TCsdUnsignedInt16      xPvLength,
  TCsdUnsignedInt8*     pxPvValue
);

/*!
 *  @ingroup scsboot
 *
 *  @brief
 *    This functions configures the size of the memory checked by the SCS 
 *    mechanism (SCS_Total_Area).
 *
 *    It only applies to chipset where this size is configured in persistent
 *    values (e.g. fuses).
 *    
 *  @applies
 *    NOCS1 only
 *
 *  @param[in]      xScsTotalAreaSize
 *    Size of SCS_Total_Area.
 *
 *  @retval   CSD_NO_ERROR
 *    The SCS_Total_Area size has been configured successfully or it was already
 *    configured to the requested value.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The SCS_Total_Area passed as parameter is out of type.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The SCS_Total_Area has already been set to a different valid size and has
 *    been locked.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    This function is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation
 *    failed.
 *
 *  @see csdGetScsTotalAreaSize
*/
TCsdStatus csdSetScsTotalAreaSize
(
  TCsdScsTotalAreaSize xScsTotalAreaSize
);

/*!
 *  @ingroup scsboot
 *
 *  @brief
 *    This function reads the size of the memory area checked by the SCS
 *    (SCS_Total_Area).
 *
 *  @applies
 *    NOCS1 only
 *
 *  @param[out]     pxTotalAreaSize
 *    Pointer to the location where the function has to write the size of
 *    SCS_Total_Area.
 *
 *  @retval   CSD_NO_ERROR
 *    Size SCS_Total_Area has been read successfully.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The size read is supported by the chipset but not defined in NOCS 1.x
 *    specification, or this feature is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    Any other error
 *
 *  @see csdSetScsTotalAreaSize
 */
TCsdStatus csdGetScsTotalAreaSize
(
  TCsdScsTotalAreaSize* pxTotalAreaSize
);


/**
 *  @ingroup ramprot
 *
 *  @brief
 *    This function configures the size of the RAM unscrambled storage.
 *
 *  @applies
 *    NOCS3 only
 *
 *  @param[in]      pxPvRamUnscrambledStorageSize
 *    Persistent Value in MSBF which will defines the RAM unscrambled storage size.
 *
 *  @param[in]      xPvLength
 *    Size in bytes of the pxUnscrambledStorageSize array
 *
 *  @retval   CSD_NO_ERROR
 *    The size of the RAM unscrambled storage has been configured successfully
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid or undefined
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The RAM Unscrambled Storage Size has already been set to a different value
 *    and has been locked.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The function is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    Any other error
 *
 *  @see csdGetRamUnscrambledStorageSize
*/
TCsdStatus csdSetRamUnscrambledStorageSize
(
  TCsdUnsignedInt8*  pxPvRamUnscrambledStorageSize,
  TCsdUnsignedInt16   xPvLength
);

/**
 *  @ingroup ramprot
 *
 *  @brief
 *    This function reads the size of the RAM unscrambled storage
 *
 *  @applies
 *    NOCS3 only
 *
 *  @param[out]     pxPvRamUnscrambledStorageSize
 *    Pointer to the location where the function has to write the Persistent 
 *    Value in MSBF which will defines the Ram Unscrambled Storage Size.
 *
 *  @param[in]      xPvLength
 *    Size in bytes of the pxUnscrambledStorageSize array
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The function is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    Any other error
 *
 *  @see csdSetRamUnscrambledStorageSize
 */
TCsdStatus csdGetRamUnscrambledStorageSize
(
  TCsdUnsignedInt8*  pxPvRamUnscrambledStorageSize,
  TCsdUnsignedInt16   xPvLength
);

/**
 *  @ingroup ramprot
 *
 *  @brief
 *    This function enables the RAM scrambling. Once enabled, this feature can
 *    no longer be disabled.
 *
 *  @applies
 *    NOCS3 only
 *
 *  @retval   CSD_NO_ERROR
 *    The RAM scrambling has been enabled successfully, or was already enabled.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *     This feature is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    This error is returned in all other cases and the call shall have no effect.
*/
TCsdStatus csdEnableRamScrambling
(
  void
);

/**
 *  @ingroup ramprot
 *
 *  @brief
 *    This function reads the RAM scrambling activation flag.
 *
 *  @applies
 *    NOCS3 only
 *
 *  @param[out]     pxScramblingActivationFlagState
 *    Pointer to the location where the function has to write the scrambling
 *    activation flag
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The function is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    This error is returned in all other cases and the call shall have no effect.
*/
TCsdStatus csdGetScramblingActivationFlag
(
  TCsdActivationFlag* pxScramblingActivationFlagState
);

/**
 *  @ingroup flashprot
 *
 *  @brief
 *    This function enables the flash protection mechanism. Once enabled, this
 *    feature can no longer be disabled (it is enforced by hardware).
 *
 *  @applies
 *    NOCS3 only
 *
 *  @retval   CSD_NO_ERROR
 *    The flash protection mechanism has been enabled successfully or was already
 *    enabled when the function is called.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The function is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    This error is returned in all other cases and the call shall have no effect.
*/
TCsdStatus csdEnableFlashProtection
(
  void
);

/**
 *  @ingroup flashprot
 *
 *  @brief
 *    This function reads the flash protection activation flag
 *
 *  @applies
 *    NOCS3 only
 *
 *  @param[out]     pxFlashProtectionActivationFlagState
 *    Pointer to the location where the function has to write the flash
 *    protection activation flag state.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The passed parameter is invalid.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The function is not supported by the chipset.
 *
 *  @retval   CSD_ERROR
 *    This error is returned in all other cases and the call shall have no effect.
*/
TCsdStatus csdGetFlashProtectionActivationFlag
(
  TCsdActivationFlag* pxFlashProtectionActivationFlagState
);

/**
 *  @ingroup debug
 *
 *  @brief
 *    This function selects the debug interfaces protection level. Only 
 *    transitions from a less secure to a more secure state are permitted (this 
 *    mechanism is enforced by hardware).
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xDebugInterfaceProtectionLevel
 *    New protection level which has to be used by the debug interface protection
 *    mechanism.
 *
 *  @retval   CSD_NO_ERROR
 *    The debug protection level has been set successfully, or was already set
 *    to the desired level of security.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    The protection level passed as parameter is out of type.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_ALLOWED
 *    The requested protection level is less secure than the current protection 
 *    level.
 *
 *  @retval   CSD_ERROR
 *    This error is returned in all other cases and the call shall have no effect.
 *  
 *  @note
 *    In case the debug interface would be in an inconsistent state when this
 *    function is called, and assuming the new state selected is more secure, 
 *    then this function shall anyway switch to the new state.
 *
 *  @see csdGetDebugInterfaceProtectionLevel
*/
TCsdStatus csdSelectDebugInterfaceProtectionLevel
(
  TCsdDebugInterfaceAccessMode xDebugInterfaceProtectionLevel
);

/**
 *  @ingroup debug
 *
 *  @brief
 *    This function returns the current protection level of the debug interface.
 *    
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     pxDebugInterfaceProtectionLevel
 *    Pointer to the location where the function has to write the debug interface 
 *    protection level. The level can be one of the following values:
 *    - #CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN: debug interface is fully and 
 *      unconditionally functional.
 *    - #CSD_DEBUG_INTERFACE_ACCESS_MODE_PASSWORD_PROTECTED: debug interface is 
 *      password protected.
 *    - #CSD_DEBUG_INTERFACE_ACCESS_MODE_CLOSED: debug interface is unconditionally
 *      disabled.
 *    - #CSD_DEBUG_INTERFACE_ACCESS_MODE_INCONSISTENT_STATE: debug interface is
 *      in an inconsistent state.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    A parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdSelectDebugInterfaceProtectionLevel
 */
TCsdStatus csdGetDebugInterfaceProtectionLevel
(
  TCsdDebugInterfaceAccessMode* pxDebugInterfaceProtectionLevel
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function disables the usage of chipset key ladders content keys.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @warning
 *    The deactivation does not concern the Nagra CERT block key ladders, neither
 *    the chipset key ladder used for the flash protection mechanism.
 *
 *  @see csdGetKeyLadderDeactivationFlag
*/
TCsdStatus csdDeactivateKeyLadder
(
  void
);

/**
 *  @ingroup chipinfo
 *
 *  @brief
 *    This function reads the state of the key ladder content keys deactivation
 *    flag.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     pxKeyLadderDeactivationFlagState
 *    Pointer to the location where the function has to return the key ladder 
 *    deactivation flag state.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    A passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdDeactivateKeyLadder
*/
TCsdStatus csdGetKeyLadderDeactivationFlag
(
 TCsdActivationFlag* pxKeyLadderDeactivationFlagState
);

/**
 *  @ingroup dvr
 *
 *  @brief
 *    This function returns the DVR key of the chipset.
 *
 *  	When the client application needs to encrypt or decrypt a piece of content 
 *  	for HDD recording and playback, it has to use a specific key. This key is 
 *  	not stored in clear-text form, but TDES encrypted with a secret content
 *  	key. This	encrypted version of the key is called a Keysafe and is defined
 *  	as follows:
 *  	Keysafe = [0xbf 0x18 0x6a 0x73 0xec 0x86 0x3f 0x25 
 *  	           0x9b 0xe8 0x03 0x52 0x40 0xd7 0x37 0x8c]
 *  	
 *    The decryption of Keysafe is the result of a computation involving the 
 *    TDES-RootKey128, the key ladder as well as the RAM2RAM crypto engine.
 
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[out]     xDvrKey
 *    16-bytes vector where the function has to write the DVR key.
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    A passed parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *  	As there may be several ways of configuring the RAM2RAM crypto engine and 
 *  	its key ladder to compute the DVR key, Nagravision and the chipset 
 *  	manufacturer will commonly agree during the NOCS certification process of 
 *  	a chipset on how to decrypt the Keysafe for this secure chipset. Refer to 
 *  	the Security Driver Implementation Proposal document for more details 
 *  	about this computation.
*/
TCsdStatus csdGetDvrKey
(
  TCsdUnsignedInt8    xDvrKey[16]
);


/******************************************************************************/
/*                                                                            */
/*                       Legacy RAM2RAM Functions                             */
/*                                                                            */
/******************************************************************************/



/**
 *  @ingroup ram2ram
 *
 *  @brief
 *  	This function sets a clear-text host key (software provided key) into the 
 *  	specified path of the RAM2RAM crypto engine and requests it to encrypt a 
 *  	block of data.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xAlgorithm
 *    Cryptographic algorithm (TDES or AES) to be used by the RAM2RAM crypto
 *    engine for the encryption operation.
 *
 *  @param[in]      xMode
 *    Cryptographic operation mode (ECB, CBC) to be used by the RAM2RAM crypto
 *    engine
 *
 *  @param[in]      pxClearTextHostKey
 *    Buffer containing the clear-text host key.
 *
 *  @param[in]      xClearTextHostKeySize
 *    Size in bytes of the clear-text host key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). This IV shall be used
 *    to initialize the CBC chaining register of the RAM2RAM crypto engine,
 *    provided the boolean xRefreshIv is TRUE. If xRefreshIv is FALSE, the CBC
 *    chaining register shall remain unchanged. The IV does not apply to ECB.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the algorithm
 *    cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @param[in]      xRefreshIv
 *    If TRUE, the CBC chaining register shall be loaded with the value pointed 
 *    by pxInitializationVector. If FALSE, the CBC chaining register shall 
 *    remain unchanged and pxInitializationVector shall be ignored.
 *
 *  @param[in,out]  pxR2RKeyPathHandle
 *    Pointer to the chipset specific structure that defines the key path used
 *    to set the clear-text host key.
 *
 *  @param[in]      pxInputData
 *    Buffer containing the input data to be encrypted.
 *
 *  @param[out]     pxOutputData
 *    Buffer where to store the output data.
 *
 *  @param[in]      xDataSize
 *    Size in bytes of input and output data. It must be a multiple of the 
 *    algorithm cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.   
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance,
 *    all parameters are consistent, but the algorithm or chaining mode is not
 *    supported by the chipset.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - NULL input/output buffers
 *    - NULL key buffers
 *    - The size of the clear-text host key is different from 16 bytes
 *    - The size of the initialization vector is unsupported (different from
 *      8 and 16 bytes) or does not match the cryptographic algorithm.
 *    - The size of input data (xDataSize) is not a multiple of the cipher
 *      block size.
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdDecryptDataWithClearTextHostKey
*/
TCsdStatus csdEncryptDataWithClearTextHostKey
(
        TCsdR2RAlgorithm            xAlgorithm,
        TCsdR2RCryptoOperationMode  xMode,
  const TCsdUnsignedInt8*          pxClearTextHostKey,
        TCsdSize                    xClearTextHostKeySize,
  const TCsdUnsignedInt8*          pxInitializationVector,
        TCsdSize                    xInitializationVectorSize,
        TCsdBoolean        	        xRefreshIv,
        TCsdR2RKeyPathHandle*      pxR2RKeyPathHandle,
  const TCsdUnsignedInt8*          pxInputData,
        TCsdUnsignedInt8*          pxOutputData,
        TCsdSize                    xDataSize
);

/**
 *  @ingroup ram2ram
 *
 *  @brief
 *  	This function sets a clear-text host key (software provided key) into the 
 *  	specified path of the RAM2RAM crypto engine and requests it to decrypt a 
 *  	block of data.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xAlgorithm
 *    Cryptographic algorithm (TDES or AES) to be used by the RAM2RAM crypto
 *    engine for the decryption operation.
 *
 *  @param[in]      xMode
 *    Cryptographic operation mode (ECB, CBC) to be used by the RAM2RAM crypto
 *    engine
 *
 *  @param[in]      pxClearTextHostKey
 *    Buffer containing the clear-text host key.
 *
 *  @param[in]      xClearTextHostKeySize
 *    Size in bytes of the clear-text host key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). This IV shall be used
 *    to initialize the CBC chaining register of the RAM2RAM crypto engine,
 *    provided the boolean xRefreshIv is TRUE. If xRefreshIv is FALSE, the CBC
 *    chaining register shall remain unchanged. The IV does not apply to ECB.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the algorithm
 *    cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @param[in]      xRefreshIv
 *    If TRUE, the CBC chaining register shall be loaded with the value pointed 
 *    by pxInitializationVector. If FALSE, the CBC chaining register shall 
 *    remain unchanged and pxInitializationVector shall be ignored.
 *
 *  @param[in,out]  pxR2RKeyPathHandle
 *    Pointer to the chipset specific structure that defines the key path used
 *    to set the clear-text host key.
 *
 *  @param[in]      pxInputData
 *    Buffer containing the input data to be decrypted.
 *
 *  @param[out]     pxOutputData
 *    Buffer where to store the output data.
 *
 *  @param[in]      xDataSize
 *    Size in bytes of input and output data. It must be a multiple of the 
 *    algorithm cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.   
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance,
 *    all parameters are consistent, but the algorithm or chaining mode is not
 *    supported by the chipset.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - NULL input/output buffers
 *    - NULL key buffers
 *    - The size of the clear-text host key is different from 16 bytes
 *    - The size of the initialization vector is unsupported (different from
 *      8 and 16 bytes) or does not match the cryptographic algorithm.
 *    - The size of input data (xDataSize) is not a multiple of the cipher
 *      block size.
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdEncryptDataWithClearTextHostKey
*/
TCsdStatus csdDecryptDataWithClearTextHostKey
(
        TCsdR2RAlgorithm            xAlgorithm,
        TCsdR2RCryptoOperationMode  xMode,
  const TCsdUnsignedInt8*          pxClearTextHostKey,
        TCsdSize                    xClearTextHostKeySize,
  const TCsdUnsignedInt8*          pxInitializationVector,
        TCsdSize                    xInitializationVectorSize,
        TCsdBoolean        	        xRefreshIv,
        TCsdR2RKeyPathHandle*      pxR2RKeyPathHandle,
  const TCsdUnsignedInt8*          pxInputData,
        TCsdUnsignedInt8*          pxOutputData,
        TCsdSize                    xDataSize
);


/**
 *  @ingroup ram2ram
 *
 *  @brief
 *  	This function sets a secret key (key ladder provided key) into the 
 *  	specified path of the RAM2RAM crypto engine and requests it to encrypt a 
 *  	block of data.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xAlgorithm
 *    Cryptographic algorithm (TDES or AES) to be used by the RAM2RAM crypto
 *    engine for the encryption operation.
 *
 *  @param[in]      xMode
 *    Cryptographic operation mode (ECB, CBC) to be used by the RAM2RAM crypto
 *    engine
 *
 *  @param[in]      xR2RCipheredProtectingKeys
 *    Buffer containing an array of ciphered protecting keys. The number of 
 *    protecting keys contained in this array is defined by the constant 
 *    #CSD_R2R_NB_OF_PROTECTING_KEYS. It is always set to 2 in case of a NOCS3
 *    chipset.
 *
 *  @param[in]      pxCipheredContentKey
 *    Buffer containing the ciphered content key (ciphered form of secret
 *    content key)
 *
 *  @param[in]      xCipheredContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). This IV shall be used
 *    to initialize the CBC chaining register of the RAM2RAM crypto engine,
 *    provided the boolean xRefreshIv is TRUE. If xRefreshIv is FALSE, the CBC
 *    chaining register shall remain unchanged. The IV does not apply to ECB.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the algorithm
 *    cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @param[in]      xRefreshIv
 *    If TRUE, the CBC chaining register shall be loaded with the value pointed 
 *    by pxInitializationVector. If FALSE, the CBC chaining register shall 
 *    remain unchanged and pxInitializationVector shall be ignored.
 *
 *  @param[in,out]  pxR2RKeyPathHandle
 *    Pointer to the chipset specific structure that defines the key path used
 *    to set the cphered content key.
 *
 *  @param[in]      pxInputData
 *    Buffer containing the input data to be encrypted.
 *
 *  @param[out]     pxOutputData
 *    Buffer where to store the output data.
 *
 *  @param[in]      xDataSize
 *    Size in bytes of input and output data. It must be a multiple of the 
 *    algorithm cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.   
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance,
 *    all parameters are consistent, but the algorithm or chaining mode is not
 *    supported by the chipset.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - NULL input/output buffers
 *    - NULL key buffers
 *    - The size of the ciphered content key is different from 16 bytes
 *    - The size of the initialization vector is unsupported (different from
 *      8 and 16 bytes) or does not match the cryptographic algorithm.
 *    - The size of input data (xDataSize) is not a multiple of the cipher
 *      block size.
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdDecryptDataWithSecretContentKey
*/
TCsdStatus csdEncryptDataWithSecretContentKey
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8*              pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8*              pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean                     xRefreshIv,
        TCsdR2RKeyPathHandle*          pxR2RKeyPathHandle,
  const TCsdUnsignedInt8*              pxInputData,
        TCsdUnsignedInt8*              pxOutputData,
        TCsdSize                        xDataSize
);


/**
 *  @ingroup ram2ram
 *
 *  @brief
 *  	This function sets a secret key (key ladder provided key) into the 
 *  	specified path of the RAM2RAM crypto engine and requests it to decrypt a 
 *  	block of data.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xAlgorithm
 *    Cryptographic algorithm (TDES or AES) to be used by the RAM2RAM crypto
 *    engine for the decryption operation.
 *
 *  @param[in]      xMode
 *    Cryptographic operation mode (ECB, CBC) to be used by the RAM2RAM crypto
 *    engine
 *
 *  @param[in]      xR2RCipheredProtectingKeys
 *    Buffer containing an array of ciphered protecting keys. The number of 
 *    protecting keys contained in this array is defined by the constant 
 *    #CSD_R2R_NB_OF_PROTECTING_KEYS. It is always set to 2 in case of a NOCS3
 *    chipset.
 *
 *  @param[in]      pxCipheredContentKey
 *    Buffer containing the ciphered content key (ciphered form of secret
 *    content key)
 *
 *  @param[in]      xCipheredContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). This IV shall be used
 *    to initialize the CBC chaining register of the RAM2RAM crypto engine,
 *    provided the boolean xRefreshIv is TRUE. If xRefreshIv is FALSE, the CBC
 *    chaining register shall remain unchanged. The IV does not apply to ECB.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the algorithm
 *    cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @param[in]      xRefreshIv
 *    If TRUE, the CBC chaining register shall be loaded with the value pointed 
 *    by pxInitializationVector. If FALSE, the CBC chaining register shall 
 *    remain unchanged and pxInitializationVector shall be ignored.
 *
 *  @param[in,out]  pxR2RKeyPathHandle
 *    Pointer to the chipset specific structure that defines the key path used
 *    to set the cphered content key.
 *
 *  @param[in]      pxInputData
 *    Buffer containing the input data to be decrypted.
 *
 *  @param[out]     pxOutputData
 *    Buffer where to store the output data.
 *
 *  @param[in]      xDataSize
 *    Size in bytes of input and output data. It must be a multiple of the 
 *    algorithm cipher block size (8 bytes for TDES and 16 bytes for AES).
 *
 *  @retval   CSD_NO_ERROR
 *    The intended operation was executed successfully.   
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance,
 *    all parameters are consistent, but the algorithm or chaining mode is not
 *    supported by the chipset.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - NULL input/output buffers
 *    - NULL key buffers
 *    - The size of the ciphered content key is different from 16 bytes
 *    - The size of the initialization vector is unsupported (different from
 *      8 and 16 bytes) or does not match the cryptographic algorithm.
 *    - The size of input data (xDataSize) is not a multiple of the cipher
 *      block size.
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @see csdEncryptDataWithSecretContentKey
*/
TCsdStatus csdDecryptDataWithSecretContentKey
(
        TCsdR2RAlgorithm                xAlgorithm,
        TCsdR2RCryptoOperationMode      xMode,
  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
  const TCsdUnsignedInt8*              pxCipheredContentKey,
        TCsdSize                        xCipheredContentKeySize,
  const TCsdUnsignedInt8*              pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdBoolean        		          xRefreshIv,
        TCsdR2RKeyPathHandle*          pxR2RKeyPathHandle,
  const TCsdUnsignedInt8*              pxInputData,
        TCsdUnsignedInt8*              pxOutputData,
        TCsdSize                        xDataSize
);



/******************************************************************************/
/*                                                                            */
/*                                    DSC                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup dsc
 *
 *  @brief
 *    This function sets an odd and even clear-text host keys (i.e. CWs) into  
 *    the specified path of the transport stream crypto engine for decryption
 *    operations.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA2, DVB-CSA3) 
 *    and block cipher modes (ECB, CBC) to be used by the transport stream
 *    crypto engine.
 *
 *  @param[in]      pxClearTextDscOddHostKey
 *    Buffer containing the odd clear-text host key. It is set to NULL if no odd 
 *    key is available.
 *
 *  @param[in]      xClearTextDscOddHostKeySize
 *    Size in bytes of the odd clear-text host key:
 *    - Key not available: 0 bytes
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
 *
 *  @param[in]      pxClearTextDscEvenHostKey
 *    Buffer containing the even clear-text host key. It is set to NULL if no 
 *    even key is available.
 *
 *  @param[in]      xClearTextDscEvenHostKeySize
 *    Size in bytes of the even clear-text host key:
 *    - Key not available: 0 byte
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
 *
 *  @param[in,out]  pxDscKeyPathHandle
 *    Pointer to the structure which defines the key path used to set the keys.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance, a 
 *    valid EMI is provided by the caller, but the chipset does not support it.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - Both odd and even key buffers are NULL
 *    - Both odd and even key sizes are 0
 *    - Unsupported key sizes (different from 0, 8 and 16 bytes)
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    -# EMI to be supported covers all MPEG TS algorithms, i.e. all EMI 0x00xx
 *    	 defined in [EMI] specification.
 *    -# If one of the host keys (odd or even) is not available, the driver must
 *       not change the content of the underlying key register.
*/
TCsdStatus csdSetClearTextDscHostKeys
(
        TCsdUnsignedInt16         xEmi,
  const TCsdUnsignedInt8*        pxClearTextDscOddHostKey,
        TCsdSize                  xClearTextDscOddHostKeySize,
  const TCsdUnsignedInt8*        pxClearTextDscEvenHostKey,
        TCsdSize                  xClearTextDscEvenHostKeySize,
        TCsdDscKeyPathHandle*    pxDscKeyPathHandle
);

/**
 *  @ingroup dsc
 *
 *  @brief
 *  	This function configures the key ladder with the ciphered protecting keys
 *  	and sets the content keys provided in protected form into the specified 
 *    path of the	transport stream crypto engine for decryption operations.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES, DVB-CSA2, DVB-CSA3) 
 *    and block cipher modes (ECB, CBC) to be used by the transport stream
 *    crypto engine.
 *
 *  @param[in]      xDscCipheredProtectingKeys
 *    Buffer containing an array of ciphered protecting keys. The number of 
 *    protecting keys contained in this array is defined by the constant 
 *    #CSD_DSC_NB_OF_PROTECTING_KEYS. It is always set to 2 in case of a NOCS3
 *    chipset.
 *
 *  @param[in]      pxCipheredDscOddContentKey
 *    Buffer containing the ciphered odd content key
 *
 *  @param[in]      xCipheredDscOddContentKeySize
 *    Size in bytes of the ciphered odd content key:
 *    - Key not available: 0 byte
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
 
 *  @param[in]      pxCipheredDscEvenContentKey
 *    Buffer containing the ciphered even content key
 *
 *  @param[in]      xCipheredDscEvenContentKeySize
 *    Size in bytes of the ciphered even content key:
 *    - Key not available: 0 byte
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *    - DVB-CSA2: 8 bytes
 *    - DVB-CSA3: 16 bytes
 *
 *  @param[in,out]  pxDscKeyPathHandle
 *    Pointer to the structure which defines the key path used to set the keys.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance, a 
 *    valid EMI is provided by the caller, but the chipset does not support it.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - Both odd and even ciphered content key buffers are NULL
 *    - Both odd and even ciphered content key sizes are 0
 *    - Unsupported ciphered content key sizes (different from 0, 8 and 16 bytes)
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    -# EMI to be supported covers all MPEG TS algorithms, i.e. all EMI 0x00xx
 *    	 defined in [EMI] specification.
 *    -# If one of the ciphered content keys (odd or even) is not available, the
 *       driver must not change the content of the underlying key register.
*/
TCsdStatus csdSetProtectedDscContentKeys
(
        TCsdUnsignedInt16               xEmi,
  const TCsdDscCipheredProtectingKeys   xDscCipheredProtectingKeys,
  const TCsdUnsignedInt8*              pxCipheredDscOddContentKey,
        TCsdSize                        xCipheredDscOddContentKeySize,
  const TCsdUnsignedInt8*              pxCipheredDscEvenContentKey,
        TCsdSize                        xCipheredDscEvenContentKeySize,
        TCsdDscKeyPathHandle*          pxDscKeyPathHandle
);


/******************************************************************************/
/*                                                                            */
/*                                    SCR                                     */
/*                                                                            */
/******************************************************************************/

/**
 *  @ingroup scr
 *
 *  @brief
 *  	This function sets a clear-text host key (software provided key) into the 
 *  	specified path of the stream crypto engine for encryption operations.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES) and block cipher 
 *    modes (ECB, CBC) to be used by the stream crypto engine.
 *
 *  @param[in]      pxClearTextScrHostKey
 *    Buffer containing the clear-text host key.
 *
 *  @param[in]      xClearTextScrHostKeySize
 *    Size in bytes of the clear-text host key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). If no IV is required, 
 *    pxInitializationVector is set to NULL.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitializationVectorSize is set to zero.
 *
 *  @param[in,out]  pxScrKeyPathHandle
 *    Pointer to the structure which defines the key path used to set the key.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance, a 
 *    valid EMI is provided by the caller, but the chipset does not support it.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - Content key buffer is NULL
 *    - Content key size different from 16 bytes
 *    - Inconsistent IV size (different from 8 bytes for TDES and from 16 bytes
 *      for AES).
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    EMIs supported by this function are defined in [EMI] and are:
 *    - "MPEG TS Stream AES & TDES EMIs"  
 *    - "Other Standards Stream EMIs"
 *
 *  @see csdSetClearTextScrDecryptionKey
*/
TCsdStatus csdSetClearTextScrEncryptionKey
(
        TCsdUnsignedInt16           xEmi,
  const TCsdUnsignedInt8*          pxClearTextScrHostKey,
        TCsdSize                    xClearTextScrHostKeySize,
  const TCsdUnsignedInt8*          pxInitializationVector,
        TCsdSize                    xInitializationVectorSize,
        TCsdScrKeyPathHandle*      pxScrKeyPathHandle
);

/**
 *  @ingroup scr
 *
 *  @brief
 *  	This function sets a clear-text host key (software provided key) into the 
 *  	specified path of the stream crypto engine for decryption operations.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES) and block cipher 
 *    modes (ECB, CBC) to be used by the stream crypto engine.
 *
 *  @param[in]      pxClearTextScrHostKey
 *    Buffer containing the clear-text host key.
 *
 *  @param[in]      xClearTextScrHostKeySize
 *    Size in bytes of the clear-text host key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). If no IV is required, 
 *    pxInitializationVector is set to NULL.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitializationVectorSize is set to zero.
 *
 *  @param[in,out]  pxScrKeyPathHandle
 *    Pointer to the structure which defines the key path used to set the key.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance, a 
 *    valid EMI is provided by the caller, but the chipset does not support it.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - Content key buffer is NULL
 *    - Content key size different from 16 bytes
 *    - Inconsistent IV size (different from 8 bytes for TDES and from 16 bytes
 *      for AES).
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    EMIs supported by this function are defined in [EMI] and are:
 *    - "MPEG TS Stream AES & TDES EMIs"  
 *    - "Other Standards Stream EMIs"
 *
 *  @see csdSetClearTextScrEncryptionKey
*/
TCsdStatus csdSetClearTextScrDecryptionKey
(
        TCsdUnsignedInt16           xEmi,
  const TCsdUnsignedInt8*          pxClearTextScrHostKey,
        TCsdSize                    xClearTextScrHostKeySize,
  const TCsdUnsignedInt8*      	   pxInitializationVector,
        TCsdSize                    xInitializationVectorSize,
        TCsdScrKeyPathHandle*      pxScrKeyPathHandle
);


/**
 *  @ingroup scr
 *
 *  @brief
 *  	This function configures the key ladder with the ciphered protecting keys
 *  	and sets the content key provided in protected form into the specified 
 *    path of the	stream crypto engine for decryption operations.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES) and block cipher 
 *    modes (ECB, CBC) to be used by the stream crypto engine.
 *
 *  @param[in]      xScrCipheredProtectingKeys
 *    Buffer containing an array of ciphered protecting keys. The number of 
 *    protecting keys contained in this array is defined by the constant 
 *    #CSD_SCR_NB_OF_PROTECTING_KEYS. It is always set to 2 in case of a NOCS3
 *    chipset.
 *
 *  @param[in]      pxCipheredScrContentKey
 *    Buffer containing the ciphered content key
 *
 *  @param[in]      xCipheredScrContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). 
 *    If no IV is required, pxInitializationVector is set to NULL.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitializationVectorSize is set to zero.
 *
 *  @param[in,out]  pxScrKeyPathHandle
 *    Pointer to the structure which defines the key path used to set the key.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance, a 
 *    valid EMI is provided by the caller, but the chipset does not support it.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - Ciphered content key buffer is NULL
 *    - Ciphered content key size different from 16 bytes
 *    - Inconsistent IV size (different from 8 bytes for TDES and from 16 bytes
 *      for AES).
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    EMIs supported by this function are defined in [EMI] and are:
 *    - "MPEG TS Stream AES & TDES EMIs"  
 *    - "Other Standards Stream EMIs"
 *
 *  @see csdSetProtectedScrEncryptionKey
*/
TCsdStatus csdSetProtectedScrDecryptionKey
(
        TCsdUnsignedInt16                xEmi,
  const TCsdScrCipheredProtectingKeys    xScrCipheredProtectingKeys,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                         xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                         xInitializationVectorSize,
        TCsdScrKeyPathHandle*           pxScrKeyPathHandle
);


/**
 *  @ingroup scr
 *
 *  @brief
 *  	This function configures the key ladder with the ciphered protecting keys
 *  	and sets the content key provided in protected form into the specified 
 *    path of the	stream crypto engine for encryption operations.
 *
 *  @applies
 *    NOCS1 and NOCS3
 *
 *  @param[in]      xEmi
 *    Identifier of the cryptographic algorithm (TDES, AES) and block cipher 
 *    modes (ECB, CBC) to be used by the stream crypto engine.
 *
 *  @param[in]      xScrCipheredProtectingKeys
 *    Buffer containing an array of ciphered protecting keys. The number of 
 *    protecting keys contained in this array is defined by the constant 
 *    #CSD_SCR_NB_OF_PROTECTING_KEYS. It is always set to 2 in case of a NOCS3
 *    chipset.
 *
 *  @param[in]      pxCipheredScrContentKey
 *    Buffer containing the ciphered content key
 *
 *  @param[in]      xCipheredScrContentKeySize
 *    Size in bytes of the ciphered content key:
 *    - TDES keying option 2: 2*8=16 bytes
 *    - AES: 16 bytes
 *
 *  @param[in]      pxInitializationVector
 *    Buffer containing the initialization vector (IV). If no IV is required, 
 *    pxInitializationVector is set to NULL.
 *
 *  @param[in]      xInitializationVectorSize
 *    Size in bytes of the initialization vector. It is equal to the cipher
 *    block size (8 bytes for TDES and 16 bytes for AES). If no IV is
 *    required (ECB mode), xInitializationVectorSize is set to zero.
 *
 *  @param[in,out]  pxScrKeyPathHandle
 *    Pointer to the structure which defines the key path used to set the key.
 *
 *  @retval   CSD_ERROR_OPERATION_NOT_SUPPORTED
 *    The requested operation is not supported by the chipset. For instance, a 
 *    valid EMI is provided by the caller, but the chipset does not support it.
 *
 *  @retval   CSD_ERROR_INVALID_PARAMETERS
 *    An invalid parameter is provided:
 *    - Ciphered content key buffer is NULL
 *    - Ciphered content key size different from 16 bytes
 *    - Inconsistent IV size (different from 8 bytes for TDES and from 16 bytes
 *      for AES).
 *
 *  @retval   CSD_ERROR_INVALID_KEY_PATH_HANDLE
 *    The key path handle passed as parameter is invalid.
 *
 *  @retval   CSD_ERROR
 *    The function terminated abnormally. The intended operation failed.
 *
 *  @note
 *    EMIs supported by this function are defined in [EMI] and are:
 *    - "MPEG TS Stream AES & TDES EMIs"  
 *    - "Other Standards Stream EMIs"
 *
 *  @see csdSetProtectedScrDecryptionKey
*/
TCsdStatus csdSetProtectedScrEncryptionKey
(
        TCsdUnsignedInt16               xEmi,
  const TCsdScrCipheredProtectingKeys   xScrCipheredProtectingKeys,
  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
        TCsdSize                        xCipheredScrContentKeySize,
  const TCsdUnsignedInt8*               pxInitializationVector,
        TCsdSize                        xInitializationVectorSize,
        TCsdScrKeyPathHandle*           pxScrKeyPathHandle
); 


#endif /* CSD_H */

/* nocs_csd.h */
