/*
 *  guCApluginPOF: Generic GUCEF plugin for decoding "Violation" POF models
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

#ifndef GU_CA_PLUGIN_POF_MACROS_H
#define GU_CA_PLUGIN_POF_MACROS_H

/*
 *      Build configuration specific macros.
 *      Also includes the generic macros which are build config independant.
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GU_CORE_MACROS_H
#include "guCORE_macros.h"
#define GU_CORE_MACROS_H
#endif /* GU_CORE_MACROS_H ? */

#ifndef GU_CA_PLUGIN_POF_ETYPES_H
#include "guCApluginPOF_ETypes.h"      /* simple types */
#define GU_CA_PLUGIN_POF_ETYPES_H
#endif /* GU_CA_PLUGIN_POF_ETYPES_H ? */

#ifndef GU_CA_PLUGIN_POF_CONFIG_H
#include "guCApluginPOF_config.h"
#define GU_CA_PLUGIN_POF_CONFIG_H
#endif /* GU_CA_PLUGIN_POF_CONFIG_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      GENERAL MACROS                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

#undef GU_CA_PLUGIN_POF_EXPORT
#ifdef GU_CA_PLUGIN_POF_BUILD_MODULE
  #define GU_CA_PLUGIN_POF_EXPORT GUCE_EXPORT
#else
  #define GU_CA_PLUGIN_POF_EXPORT GUCE_IMPORT
#endif /* GU_CA_PLUGIN_POF_BUILD_MODULE ? */

#undef GU_CA_PLUGIN_POF_EXPORT_CPP
#ifdef GU_CA_PLUGIN_POF_EXPORT_CPP_CODE
  #define GU_CA_PLUGIN_POF_EXPORT_CPP GU_CA_PLUGIN_POF_EXPORT  
#else
  #define GU_CA_PLUGIN_POF_EXPORT_CPP
#endif /* GU_CA_PLUGIN_POF_EXPORT_CPP_CODE */

#undef GU_CA_PLUGIN_POF_EXPORT_C 
#ifdef GU_CA_PLUGIN_POF_EXPORT_C_CODE
  #define GU_CA_PLUGIN_POF_EXPORT_C GU_CA_PLUGIN_POF_EXPORT
#else
  #define GU_CA_PLUGIN_POF_EXPORT_C
#endif /* GU_CA_PLUGIN_POF_EXPORT_C_CODE */

/*-------------------------------------------------------------------------*/

#endif /* GU_CA_PLUGIN_POF_MACROS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 26-03-2005 :
       - Initial version of this file.

-----------------------------------------------------------------------------*/
