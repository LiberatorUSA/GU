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

#ifndef GU_CA_PLUGIN_POF_ETYPES_H
#define GU_CA_PLUGIN_POF_ETYPES_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GU_CORE_ETYPES_H
#include "guCORE_ETypes.h"   /* GU::CORE types are imported */
#define GU_CORE_ETYPES_H
#endif /* GU_CORE_ETYPES_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CONSTANTS                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Maximum and minimal values for the simple types which we are about to
 *      define.
 */
#define GU_CA_PLUGIN_POF_INT8MAX     GUCORE_INT8MAX
#define GU_CA_PLUGIN_POF_INT8MIN     GUCORE_INT8MIN
#define GU_CA_PLUGIN_POF_UINT8MAX    GUCORE_UINT8MAX
#define GU_CA_PLUGIN_POF_UINT8MIN    GUCORE_UINT8MIN
#define GU_CA_PLUGIN_POF_INT16MAX    GUCORE_INT16MAX
#define GU_CA_PLUGIN_POF_INT16MIN    GUCORE_INT16MIN
#define GU_CA_PLUGIN_POF_UINT16MAX   GUCORE_UINT16MAX
#define GU_CA_PLUGIN_POF_UINT16MIN   GUCORE_UINT16MIN
#define GU_CA_PLUGIN_POF_INT32MAX    GUCORE_INT32MAX
#define GU_CA_PLUGIN_POF_INT32MIN    GUCORE_INT32MIN
#define GU_CA_PLUGIN_POF_UINT32MAX   GUCORE_UINT32MAX
#define GU_CA_PLUGIN_POF_UINT32MIN   GUCORE_UINT32MIN
#define GU_CA_PLUGIN_POF_FLOAT32MAX  GUCORE_FLOAT32MAX
#define GU_CA_PLUGIN_POF_FLOAT32MIN  GUCORE_FLOAT32MIN

/*--------------------------------------------------------------------------*/

/*
 *  We only have to define types when using C++ due to namespacing 
 *  For C the gucefCORE versions are automaticly used in the global namespace
 */
#ifdef __cplusplus
/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CA {
namespace PLUGINPOF {

/*-------------------------------------------------------------------------//
//                                                                         //
//      TYPES                                                              //
//                                                                         //
//-------------------------------------------------------------------------*/

typedef GU::CORE::UInt8 UInt8;    /* 1 byte, unsigned */
typedef GU::CORE::Int8 Int8;      /* 1 byte, signed */

typedef GU::CORE::UInt16 UInt16;   /* 2 bytes, unsigned */
typedef GU::CORE::Int16 Int16;     /* 2 bytes, signed */

typedef GU::CORE::UInt32 UInt32;   /* 4 bytes, unsigned */
typedef GU::CORE::Int32  Int32;    /* 4 bytes, signed */

typedef GU::CORE::Int64 Int64;     /* 8 bytes, signed */
typedef GU::CORE::UInt64 UInt64;   /* 8 bytes, unsigned */

typedef GU::CORE::Float32 Float32;  /* 4 bytes, signed, decimal */
typedef GU::CORE::Float64 Float64;  /* 8 bytes, signed, decimal */

typedef GU::CORE::CString CString;

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace PLUGINPOF */
}; /* namespace CA */
}; /* namespace GU */

/*--------------------------------------------------------------------------*/

#endif /* __cplusplus ? */

#endif /* GU_CA_PLUGIN_POF_ETYPES_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 31-12-2004 :
       - Dinand: Added this section

-----------------------------------------------------------------------------*/