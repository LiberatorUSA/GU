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

#ifndef GU_CORE_CGUCOREMODULE_H
#define GU_CORE_CGUCOREMODULE_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEGUI_MACROS_H
#include "guceGUI_macros.h"         /* often used guceGUI macros */
#define GUCEGUI_MACROS_H
#endif /* GUCEGUI_MACROS_H ? */

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

class CGUCOREModule
{
    public:
    
    static bool Load( void );
    
    static bool Unload( void );
    
    private:
    CGUCOREModule( void );
    CGUCOREModule( const CGUCOREModule& src );
    ~CGUCOREModule();
    CGUCOREModule& operator=( const CGUCOREModule& src );
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
          
#endif /* GU_CORE_CGUCOREMODULE_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 26-04-2005 :
        - Initial implementation

-----------------------------------------------------------------------------*/