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

#include "guCORE_CSinglePlayerForm.h"

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

CSinglePlayerForm::CSinglePlayerForm( void )
    : CFormEx()              ,
      m_menuButton( NULL )   ,
      m_playButton( NULL )   ,
      m_gamesListbox( NULL )
{GUCE_TRACE;

}

/*-------------------------------------------------------------------------*/
    
CSinglePlayerForm::~CSinglePlayerForm()
{GUCE_TRACE;

}

/*-------------------------------------------------------------------------*/

void
CSinglePlayerForm::OnPreLayoutLoad( void )
{GUCE_TRACE;

    m_menuButton = NULL;
    m_playButton = NULL;
    m_gamesListbox = NULL;
}

/*-------------------------------------------------------------------------*/

void
CSinglePlayerForm::OnPostLayoutLoad( void )
{GUCE_TRACE;

    m_menuButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "MenuButton" ) );
    m_playButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "PlayButton" ) );
    m_gamesListbox = static_cast< GUCEF::GUI::CListbox* >( GetWidget( "GamesListbox" ) );
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CSinglePlayerForm::GetMenuButton( void )
{GUCE_TRACE;

    return m_menuButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CSinglePlayerForm::GetPlayButton( void )
{GUCE_TRACE;

    return m_playButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CListbox*
CSinglePlayerForm::GetGamesListbox( void )
{GUCE_TRACE;

    return m_gamesListbox;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
