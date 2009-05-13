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

#include "guCORE_CDownloadsMenuForm.h"

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

CDownloadsMenuForm::CDownloadsMenuForm( void )
    : CFormEx()                              ,
      m_menuButton( NULL )                   ,
      m_settingsButton( NULL )               ,
      m_refreshButton( NULL )                ,
      m_downloadsTabControl( NULL )          ,
      m_allAvailableDownloadsTabPane( NULL ) ,
      m_transfersTabPane( NULL )             ,
      m_downloadedTabPane( NULL )
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/
    
CDownloadsMenuForm::~CDownloadsMenuForm()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

void
CDownloadsMenuForm::OnPreLayoutLoad( void )
{GU_TRACE;

    m_menuButton = NULL;
    m_settingsButton = NULL;
    m_refreshButton = NULL;
    m_downloadsTabControl = NULL;
    m_allAvailableDownloadsTabPane = NULL;
    m_transfersTabPane = NULL;
    m_downloadedTabPane = NULL;
}

/*-------------------------------------------------------------------------*/

void
CDownloadsMenuForm::OnPostLayoutLoad( void )
{GU_TRACE;

    m_menuButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "MenuButton" ) );
    m_settingsButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "SettingsButton" ) );
    m_refreshButton = static_cast< GUCEF::GUI::CButton* >( GetWidget( "RefreshButton" ) );
    m_downloadsTabControl = static_cast< GUCEF::GUI::CTabControl* >( GetWidget( "DownloadsTabControl" ) );
    m_allAvailableDownloadsTabPane = static_cast< GUCEF::GUI::CTabContentPane* >( GetWidget( "AllAvailableDownloadsTabPane" ) );
    m_transfersTabPane = static_cast< GUCEF::GUI::CTabContentPane* >( GetWidget( "TransfersTabPane" ) );
    m_downloadedTabPane = static_cast< GUCEF::GUI::CTabContentPane* >( GetWidget( "DownloadsTabPane" ) );
}

/*-------------------------------------------------------------------------*/

GUCEF::GUI::CButton*
CDownloadsMenuForm::GetMenuButton( void )
{GU_TRACE;

    return m_menuButton;
}

/*-------------------------------------------------------------------------*/

GUCEF::GUI::CButton*
CDownloadsMenuForm::GetSettingsButton( void )
{GU_TRACE;

    return m_settingsButton;
}

/*-------------------------------------------------------------------------*/

GUCEF::GUI::CButton*
CDownloadsMenuForm::GetRefreshButton( void )
{GU_TRACE;

    return m_refreshButton;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CTabControl*
CDownloadsMenuForm::GetDownloadsTabControl( void )
{GU_TRACE;

    return m_downloadsTabControl;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CTabContentPane*
CDownloadsMenuForm::GetAllAvailableDownloadsTabPane( void )
{GU_TRACE;

    return m_allAvailableDownloadsTabPane;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CTabContentPane*
CDownloadsMenuForm::GetTransfersTabPane( void )
{GU_TRACE;

    return m_transfersTabPane;
}

/*-------------------------------------------------------------------------*/
    
GUCEF::GUI::CTabContentPane*
CDownloadsMenuForm::GetDownloadedTabPane( void )
{GU_TRACE;

    return m_downloadedTabPane;
}

/*-------------------------------------------------------------------------*/

CDownloadsMenuForm::TDownloadsTab
CDownloadsMenuForm::GetActiveTab( void ) const
{GU_TRACE;
    
    if ( NULL != m_downloadsTabControl )
    {
        Int32 tabIndex = m_downloadsTabControl->GetActiveTab();
        switch ( tabIndex )
        {
            case 0 :
            {
                return DOWNLOADSTAB_AVAILABLE;
            }
            case 1 :
            {
                return DOWNLOADSTAB_TRANSFERS;
            }
            case 2 :
            {
                return DOWNLOADSTAB_DOWNLOADED;
            }
            default:
            {
                return DOWNLOADSTAB_NONE;
            }                
        }
    }
    return DOWNLOADSTAB_NONE;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
