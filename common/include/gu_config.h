/*
 * Copyright (C) Dinand Vanvelzen. 2002 - 2006.  All rights reserved.
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

/*
 *  This header contains build switches relative to the entire GU platform
 */

#ifndef GU_CONFIG_H
#define GU_CONFIG_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCE_CONFIG_H
#include "GUCE_config.h"       /* include for deriving some flags from GUCE */
#define GUCE_CONFIG_H
#endif /* GUCE_CONFIG_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      BUILD DEFINES                                                      //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *  In this section you can define some flags that influence the building process
 *  Note that usually it is best not to do this but to let the autodetection
 *  macros in GU_macros.h set the flags for you 
 */

/*-------------------------------------------------------------------------*/

/*
 *      Target platform selection switches
 *      By default autodetects
 */
// #define GU_LINUX_BUILD
// #define GU_MSWIN_BUILD

/*-------------------------------------------------------------------------*/

/*
 *      Switches for setting of the calling convention used
 *      Defaults to CALLSPEC_C
 */
// #define GU_USE_CALLSPEC_C
// #define GU_USE_CALLSPEC_STD
// #define GU_USE_CALLSPEC_PASCAL
// #define GU_USE_CALLSPEC_FAST

// #define GU_USE_PLUGIN_CALLSPEC_C
// #define GU_USE_PLUGIN_CALLSPEC_STD
// #define GU_USE_PLUGIN_CALLSPEC_PASCAL
// #define GU_USE_PLUGIN_CALLSPEC_FAST

/*-------------------------------------------------------------------------*/

/*
 *      Switches for manually setting the bit target
 *      Default is 32bit, may be able to autodetect
 */
// #define GU_32BIT
// #define GU_64BIT

/*-------------------------------------------------------------------------*/

/*
 *      Debug mode
 */
// #define GU_DEBUG_MODE
// #define GU_DEBUG_VERBOSE

/*-------------------------------------------------------------------------*/

#endif /* GU_CONFIG_H */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 30-09-2006 :
       - Dinand: Initial version of this file.

-----------------------------------------------------------------------------*/
