



#ifndef _DX_VOS_RNG_H
#define _DX_VOS_RNG_H

/*! \file DX_VOS_RNG.h
    \brief This module defines the wrapper to the OS-dependent random
    seed function.
*/

#include "DX_VOS_BaseTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*! Sets the seed for the random number generator.
	When setting the seed to the same specified value the same random numbers
	series will be generated in the following calls	to DX_VOS_RandomGen().
	*/
void DX_VOS_SetRandomSeed(DxUint32 seed);

/*! \return a random 32 bit value. */
DxUint32 DX_VOS_RandomGen(void);

void DX_VOS_GenerateRandomVector(DxUint8* outVector, DxUint32 vectorSize);

void DX_VOS_GenerateRandomBytes(DxUint8* outVector, DxUint32 vectorSize);



#ifdef  __cplusplus
}
#endif


#endif /* ifndef _DX_VOS_RNG_H */









