/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_LOG_H_
#define _MALI_LOG_H_

/* MALI_INSTRUMENTED wrappers for instrumented and non-instrumented expansion */
#define MALI_INSTRUMENTED_LOG( args ) do{ ; } while ( 0 )
#define MALI_INSTRUMENTED_SET_LOG_LEVEL( ctx, level ) do{ ; } while ( 0 )
#define MALI_INSTRUMENTED_OPEN_LOG_FILE( ctx,  filename ) do{ ; } while ( 0 )
#define MALI_INSTRUMENTED_CLOSE_LOG_FILE( ctx ) do{ ; } while ( 0 )
#define MALI_INSTRUMENTED_REGISTER_LOG_CALLBACK( ctx, callback ) do{ ; } while ( 0 )
#define MALI_INSTRUMENTED_WRITE_TO_LOG_FILE( ctx, message ) do{ ; } while ( 0 )

#endif /* _MALI_LOG_H_ */

