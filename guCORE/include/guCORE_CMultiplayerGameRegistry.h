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

#ifndef GU_CORE_CMULTIPLAYERGAMEREGISTRY_H
#define GU_CORE_CMULTIPLAYERGAMEREGISTRY_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CTREGISTRY_H
#include "CTRegistry.h"         /* registry template */
#define GUCEF_CORE_CTREGISTRY_H
#endif /* GUCEF_CORE_CTREGISTRY_H ? */

#ifndef GU_CORE_CMULTIPLAYERGAME_H
#include "guCORE_CMultiplayerGame.h"
#define GU_CORE_CMULTIPLAYERGAME_H
#endif /* GU_CORE_CMULTIPLAYERGAME_H ? */

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
 
typedef GUCEF::CORE::CTRegistry< CMultiplayerGame >  CMultiplayerGameRegistry; 
typedef CMultiplayerGameRegistry::TRegisteredObjPtr  CMultiplayerGamePtr;

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CMULTIPLAYERGAMEREGISTRY_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 08-04-2005 :
        - Initial implementation
          
---------------------------------------------------------------------------*/
