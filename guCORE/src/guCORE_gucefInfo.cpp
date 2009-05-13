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

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_H
#include "gucefCORE.h"
#define GUCEF_CORE_H
#endif /* GUCEF_CORE_H ? */

#ifndef GUCEF_COM_H
#include "gucefCOM.h"
#define GUCEF_COM_H
#endif /* GUCEF_COM_H ? */

#include "guCORE_gucefInfo.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

void
LogAllGUCEFTimeStamps( void )
{GU_TRACE;

    //GUCEF_SYSTEM_LOG( 0, "Using gucefMT module compiled @ " + CString( GUCEF_MT_ModuleCompileTimeStamp() ) );
    //GUCEF_SYSTEM_LOG( 0, "Using gucefCORE module compiled @ " + CString( GUCEF_CORE_ModuleCompileTimeStamp() ) );
    //GUCEF_SYSTEM_LOG( 0, "Using gucefCOM module compiled @ " + CString( GUCEF_COM_ModuleCompileTimeStamp() ) );
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
