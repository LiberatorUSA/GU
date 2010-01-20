/*
 * Copyright (C) Dinand Vanvelzen. 2002 - 2007.  All rights reserved.
 *
 * All source code herein is the property of Dinand Vanvelzen. You may not sell
 * or otherwise commercially exploit the source or things you created based on
 * the source.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL DINAND VANVELZEN BE LIABLE FOR ANY SPECIAL, INCIDENTAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER 
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER OR NOT ADVISED OF 
 * THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF LIABILITY, ARISING OUT 
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 */
 
#ifndef GU_PLATFORM_H
#define GU_PLATFORM_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GU_CONFIG_H
#include "GU_config.h"
#define GU_CONFIG_H
#endif /* GU_CONFIG_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CONSTANTS                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/* Initial platform/compiler-related stuff to set.
*/
#define GU_PLATFORM_WIN32 1
#define GU_PLATFORM_LINUX 2
#define GU_PLATFORM_APPLE 3

#define GU_COMPILER_MSVC 1
#define GU_COMPILER_GNUC 2
#define GU_COMPILER_BORL 3

#define GU_ENDIAN_LITTLE 1
#define GU_ENDIAN_BIG 2

#define GU_ARCHITECTURE_32 1
#define GU_ARCHITECTURE_64 2

/*-------------------------------------------------------------------------//
//                                                                         //
//      MACROS                                                             //
//                                                                         //
//-------------------------------------------------------------------------*/

/* Finds the compiler type and version.
*/
#if defined( _MSC_VER )
#   define GU_COMPILER GU_COMPILER_MSVC
#   define GU_COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define GU_COMPILER GU_COMPILER_GNUC
#   define GU_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define GU_COMPILER GU_COMPILER_BORL
#   define GU_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif


/* Finds the current platform */

#if defined( __WIN32__ ) || defined( _WIN32 )
#   define GU_PLATFORM GU_PLATFORM_WIN32

#elif defined( __APPLE_CC__)
#   define GU_PLATFORM GU_PLATFORM_APPLE

#else
#   define GU_PLATFORM GU_PLATFORM_LINUX
#endif

/*-------------------------------------------------------------------------*/

#endif /* GU_PLATFORM_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 02-01-2007 :
       - Initial version of this file.

---------------------------------------------------------------------------*/