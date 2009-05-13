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

#ifndef GU_CORE_CMULTIPLAYERGAME_H
#define GU_CORE_CMULTIPLAYERGAME_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_COMCORE_CHOSTADDRESS_H
#include "CHostAddress.h"
#define GUCEF_COMCORE_CHOSTADDRESS_H
#endif /* GUCEF_COMCORE_CHOSTADDRESS_H ? */

#ifndef GU_CORE_CGAME_H
#include "guCORE_CGame.h"
#define GU_CORE_CGAME_H
#endif /* GU_CORE_CGAME_H ? */

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

class GU_CORE_EXPORT_CPP CMultiplayerGame : public CGame
{
    public:
    
   // static const GUCEF::CORE::CEvent GameHostingStartedEvent;
  //  static const GUCEF::CORE::CEvent GameConnectStartedEvent;
    
    public:
    
    CMultiplayerGame( void );
    
    virtual ~CMultiplayerGame();
    
    virtual bool ConnectTo( const GUCEF::COMCORE::CHostAddress& hostAddress ) = 0;
    
    virtual bool Host( const UInt16 port          ,
                       const bool dedicatedServer ) = 0;

    private:
    
    CMultiplayerGame( const CMultiplayerGame& src );             /**< not implemented: makes no sense */
    CMultiplayerGame& operator=( const CMultiplayerGame& src );  /**< not implemented: makes no sense */
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CMULTIPLAYERGAME_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 14-01-2007 :
        - Dinand: Initial implementation

---------------------------------------------------------------------------*/