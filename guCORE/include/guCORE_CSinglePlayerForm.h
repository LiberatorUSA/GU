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

#ifndef GU_CORE_CSINGLEPLAYERFORM_H
#define GU_CORE_CSINGLEPLAYERFORM_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_GUI_CFORMEX_H
#include "gucefGUI_CFormEx.h"
#define GUCEF_GUI_CFORMEX_H
#endif /* GUCEF_GUI_CFORMEX_H ? */

#ifndef GUCEF_GUI_CBUTTON_H
#include "gucefGUI_CButton.h"
#define GUCEF_GUI_CBUTTON_H
#endif /* GUCEF_GUI_CBUTTON_H ? */

#ifndef GUCEF_GUI_CLISTBOX_H
#include "gucefGUI_CListbox.h"
#define GUCEF_GUI_CLISTBOX_H
#endif /* GUCEF_GUI_CLISTBOX_H ? */

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

class GU_CORE_EXPORT_CPP CSinglePlayerForm : public GUCEF::GUI::CFormEx
{
    public:
    
    CSinglePlayerForm( void );
    
    virtual ~CSinglePlayerForm();
    
    virtual GUCEF::GUI::CButton* GetMenuButton( void );
    
    virtual GUCEF::GUI::CButton* GetPlayButton( void );
    
    virtual GUCEF::GUI::CListbox* GetGamesListbox( void );

    protected:
    
    virtual void OnPreLayoutLoad( void );
    
    virtual void OnPostLayoutLoad( void );
   
    private:
    
    CSinglePlayerForm( const CSinglePlayerForm& src );
    CSinglePlayerForm& operator=( const CSinglePlayerForm& other );
    
    private:
    
    GUCEF::GUI::CButton* m_menuButton;
    GUCEF::GUI::CButton* m_playButton;
    GUCEF::GUI::CListbox* m_gamesListbox;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CSINGLEPLAYERFORM_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 10-02-2008 :
        - Dinand: Initial implementation

---------------------------------------------------------------------------*/
