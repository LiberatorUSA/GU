/*
 *  guCORE: Main module of the Galaxy Unlimited system
 *  Copyright (C) 2002 - 2008.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 */

#ifndef GU_CORE_MACROS_H
#define GU_CORE_MACROS_H

/*
 *      Build configuration specific macros.
 *      Also includes the generic macros which are build config independant.
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GU_CORE_ETYPES_H
#include "guCORE_ETypes.h"          /* often used simple types */
#define GU_CORE_ETYPES_H
#endif /* GU_CORE_ETYPES_H ? */

#ifndef GU_CORE_CONFIG_H
#include "guCORE_config.h"
#define GU_CORE_CONFIG_H
#endif /* GU_CORE_CONFIG_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      GENERAL MACROS                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Macros for dynamic linking. Use the switches in the
 *      config file to control the export type.
 */
#undef GU_EXPORTSPEC
#ifdef GU_CORE_BUILD_MODULE
  #define GU_EXPORTSPEC GUCE_EXPORT
#else
  #define GU_EXPORTSPEC GUCE_IMPORT
#endif /* GU_CORE_BUILD_MODULE */

#undef GU_CORE_EXPORT_CPP
#ifdef GU_CORE_EXPORT_CPP_CODE
  #define GU_CORE_EXPORT_CPP GU_EXPORTSPEC
#else
  #define GU_CORE_EXPORT_CPP
#endif /* GU_CORE_EXPORT_CPP_CODE */

#undef GU_CORE_EXPORT_C
#ifdef GU_CORE_EXPORT_C_CODE
  #define GU_CORE_EXPORT_C GU_EXPORTSPEC
#else
  #define GU_CORE_EXPORT_C
#endif /* GU_CORE_EXPORT_C_CODE */

/*-------------------------------------------------------------------------*/

#ifdef GUCE_TRACE
  #define GU_TRACE GUCE_TRACE
#else
  #ifdef GUCEF_TRACE
    #define GU_TRACE GUCEF_TRACE  
  #endif
#endif

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_MACROS_H ? */
