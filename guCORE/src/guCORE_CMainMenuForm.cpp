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

#include "guCORE_CMainMenuForm.h"

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

CMainMenuForm::CMainMenuForm( void )
    : CFormEx()                      ,
      m_exitButton( NULL )           ,
      m_downloadsButton( NULL )      ,
      m_settingsButton( NULL )       ,
      m_multiplayerButton( NULL )    ,
      m_singleplayerButton( NULL )   ,
      m_backgroundImageFrame( NULL )
{GUCE_TRACE;

}

/*-------------------------------------------------------------------------*/
    
CMainMenuForm::~CMainMenuForm()
{GUCE_TRACE;

}

/*-------------------------------------------------------------------------*/

void
CMainMenuForm::OnPreLayoutLoad( void )
{GUCE_TRACE;

    m_exitButton = NULL;
    m_downloadsButton = NULL;
    m_settingsButton = NULL;
    m_multiplayerButton = NULL;
    m_singleplayerButton = NULL;
    m_backgroundImageFrame = NULL;
}

/*-------------------------------------------------------------------------*/

void
CMainMenuForm::OnPostLayoutLoad( void )
{GUCE_TRACE;

    m_exitButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "ExitButton" ) );
    m_downloadsButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "DownloadsButton" ) );
    m_settingsButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "SettingsButton" ) );
    m_multiplayerButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "MultiplayerButton" ) );
    m_singleplayerButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "SingleplayerButton" ) );
    m_backgroundImageFrame = static_cast< GUCEF::GUI::CImageFrame* >( GetWidget( "MainMenuBackground" ) );
}

/*-------------------------------------------------------------------------*/

GUCEF::GUI::CImageFrame*
CMainMenuForm::GetBackgroundImageFrame( void )
{GUCE_TRACE;

    return m_backgroundImageFrame;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CMainMenuForm::GetExitButton( void )
{GUCE_TRACE;

    return m_exitButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CMainMenuForm::GetDownloadsButton( void )
{GUCE_TRACE;

    return m_downloadsButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CMainMenuForm::GetSettingsButton( void )
{GUCE_TRACE;

    return m_settingsButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CMainMenuForm::GetMultiplayerButton( void )
{GUCE_TRACE;

    return m_multiplayerButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CButton*
CMainMenuForm::GetSingleplayerButton( void )
{GUCE_TRACE;

    return m_singleplayerButton;
}

/*-------------------------------------------------------------------------*/

const CString&
CMainMenuForm::GetClassTypeName( void ) const
{GUCE_TRACE;

    static const CString typeName = "GU::CORE::CMainMenuForm";
    return typeName;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
