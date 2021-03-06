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

#ifndef GU_CORE_ETYPES_H
#define GU_CORE_ETYPES_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_ETYPES_H
#include "gucefCORE_ETypes.h"   /* GUCEF::CORE types are imported */
#define GUCEF_CORE_ETYPES_H
#endif /* GUCEF_CORE_ETYPES_H ? */

#ifndef GUCEF_CORE_CDVSTRING_H
#include "CDVString.h"
#define GUCEF_CORE_CDVSTRING_H
#endif /* GUCEF_CORE_CDVSTRING_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CONSTANTS                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Maximum and minimal values for the simple types which we are about to
 *      define.
 */
#define GUCORE_INT8MAX     GUCEFCORE_INT8MAX
#define GUCORE_INT8MIN     GUCEFCORE_INT8MIN
#define GUCORE_UINT8MAX    GUCEFCORE_UINT8MAX
#define GUCORE_UINT8MIN    GUCEFCORE_UINT8MIN
#define GUCORE_INT16MAX    GUCEFCORE_INT16MAX
#define GUCORE_INT16MIN    GUCEFCORE_INT16MIN
#define GUCORE_UINT16MAX   GUCEFCORE_UINT16MAX
#define GUCORE_UINT16MIN   GUCEFCORE_UINT16MIN
#define GUCORE_INT32MAX    GUCEFCORE_INT32MAX
#define GUCORE_INT32MIN    GUCEFCORE_INT32MIN
#define GUCORE_UINT32MAX   GUCEFCORE_UINT32MAX
#define GUCORE_UINT32MIN   GUCEFCORE_UINT32MIN
#define GUCORE_FLOAT32MAX  GUCEFCORE_FLOAT32MAX
#define GUCORE_FLOAT32MIN  GUCEFCORE_FLOAT32MIN

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
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      TYPES                                                              //
//                                                                         //
//-------------------------------------------------------------------------*/

typedef GUCEF::CORE::UInt8 UInt8;    /* 1 byte, unsigned */
typedef GUCEF::CORE::Int8 Int8;      /* 1 byte, signed */

typedef GUCEF::CORE::UInt16 UInt16;   /* 2 bytes, unsigned */
typedef GUCEF::CORE::Int16 Int16;     /* 2 bytes, signed */

typedef GUCEF::CORE::UInt32 UInt32;   /* 4 bytes, unsigned */
typedef GUCEF::CORE::Int32  Int32;    /* 4 bytes, signed */

typedef GUCEF::CORE::Int64 Int64;     /* 8 bytes, signed */
typedef GUCEF::CORE::UInt64 UInt64;   /* 8 bytes, unsigned */

typedef GUCEF::CORE::Float32 Float32;  /* 4 bytes, signed, decimal */
typedef GUCEF::CORE::Float64 Float64;  /* 8 bytes, signed, decimal */

typedef GUCEF::CORE::CString CString;

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*--------------------------------------------------------------------------*/

#endif /* __cplusplus ? */

#endif /* GU_CORE_ETYPES_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 31-12-2004 :
       - Dinand: Added this section

-----------------------------------------------------------------------------*/