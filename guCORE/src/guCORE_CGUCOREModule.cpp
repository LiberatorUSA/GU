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

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#ifndef GU_CORE_CDOWNLOADSMANAGER_H
#include "guCORE_CDownloadsManager.h"
#define GU_CORE_CDOWNLOADSMANAGER_H
#endif /* GU_CORE_CDOWNLOADSMANAGER_H ? */

#ifndef GU_CORE_CGAMECENTER_H
#include "guCORE_CGameCenter.h"
#define GU_CORE_CGAMECENTER_H
#endif /* GU_CORE_CGAMECENTER_H ? */

#ifndef GU_CORE_CPRODUCTMANAGER_H
#include "guCORE_CProductManager.h"
#define GU_CORE_CPRODUCTMANAGER_H
#endif /* GU_CORE_CPRODUCTMANAGER_H ? */

#ifndef GU_CORE_GUCEFINFO_H
#include "guCORE_gucefInfo.h"
#define GU_CORE_GUCEFINFO_H
#endif /* GU_CORE_GUCEFINFO_H ? */

#include "guCORE_CGUCOREModule.h"  /* definition of the class implemented here */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

bool 
CGUCOREModule::Load( void )
{GUCE_TRACE;

    GUCEF_SYSTEM_LOG( 0, "guCORE Module loaded" );
    LogAllGUCEFTimeStamps();
    
    CDownloadsManager::RegisterEvents();
    
    CProductManager::Instance();    
    CGameCenter::Instance();
    return true;
}

/*-------------------------------------------------------------------------*/
        
bool 
CGUCOREModule::Unload( void )
{GUCE_TRACE;
         
    CGameCenter::Deinstance();
    CProductManager::Deinstance();
    
    GUCEF_SYSTEM_LOG( 0, "guCORE Module unloaded" );
    
    return true;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
