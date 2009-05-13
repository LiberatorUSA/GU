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

#ifndef GU_CORE_CGAME_H
#define GU_CORE_CGAME_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_ESTRUCTS_H
#include "EStructs.h"
#define GUCEF_CORE_ESTRUCTS_H
#endif /* GUCEF_CORE_ESTRUCTS_H ? */

#ifndef GU_CORE_MACROS_H
#include "guCORE_macros.h"
#define GU_CORE_MACROS_H
#endif /* GU_CORE_MACROS_H ? */

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

class GU_CORE_EXPORT_CPP CGame
{
    public:
    
    CGame( void );

    virtual ~CGame();
    
    typedef GUCEF::CORE::TVersion   TVersion;
    
    virtual bool StartSPGame( void ) = 0;
    
    /**
     *  returns the active game type.
     *  for example: 'Capture the flag'
     *  If no game is active an empty string should be returned
     */
    virtual const CString& GetActiveGameType( void ) const = 0;

    /**
     *  returns the name of the game genre.
     *  for example: 'Boardgame'
     */
    virtual const CString& GetGameGenre( void ) const = 0;
    
    /**
     *  returns the title of the game.
     *  for example: 'Tic-Tac-Toe'
     */
    virtual const CString& GetGameTitle( void ) const = 0;
    
    /**
     *  returns the version of the game.
     */
    virtual const TVersion& GetGameVersion( void ) const = 0;
    
    /**
     *  Identifier used by abstract factories
     */
    virtual const CString& GetType( void ) const;
    
    private:
    
    CGame( const CGame& src );             /**< not implemented: makes no sense */
    CGame& operator=( const CGame& src );  /**< not implemented: makes no sense */
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CGAME_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 14-01-2007 :
        - Dinand: Initial implementation

---------------------------------------------------------------------------*/
