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

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCE_CORE_CGUCEAPPLICATION_H
#include "CGUCEApplication.h"
#define GUCE_CORE_CGUCEAPPLICATION_H
#endif /* GUCE_CORE_CGUCEAPPLICATION_H ? */

#ifndef GUCEF_GUI_CGUIMANAGER_H
#include "gucefGUI_CGUIManager.h"
#define GUCEF_GUI_CGUIMANAGER_H
#endif /* GUCEF_GUI_CGUIMANAGER_H ? */

#ifndef GUCE_GUI_CGUIMANAGER_H
#include "CGUIManager.h"
#define GUCE_GUI_CGUIMANAGER_H
#endif /* GUCE_GUI_CGUIMANAGER_H ? */

#ifndef GUCE_CORE_MISCUTILS_H
#include "miscutils.h"
#define GUCE_CORE_MISCUTILS_H
#endif /* GUCE_CORE_MISCUTILS_H ? */

#ifndef GU_CORE_CPRODUCTMANAGER_H
#include "guCORE_CProductManager.h"
#define GU_CORE_CPRODUCTMANAGER_H
#endif /* GU_CORE_CPRODUCTMANAGER_H ? */

#include "guCORE_CMenuController.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

const GUCEF::CORE::CEvent CMenuController::MenuSystemInitializedEvent = "GU::CORE::CMenuController::MenuSystemInitializedEvent";

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/
    
void
CMenuController::RegisterEvents( void )
{GU_TRACE;

    MenuSystemInitializedEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

CMenuController::CMenuController( void )
    : CObservingNotifier()     ,
      m_guiConfigRoot( "GUI" ) ,
      m_settingsMenuForm()     ,
      m_downloadsMenuForm()    ,
      m_mainMenuForm()         ,
      m_meshViewer()          
{GU_TRACE;

    RegisterEvents();
}

/*-------------------------------------------------------------------------*/
    
CMenuController::~CMenuController()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

const CString&
CMenuController::GetClassTypeName( void ) const
{GU_TRACE;

    static const CString typeName = "GU::CORE::CMenuController";
    return typeName;
}

/*-------------------------------------------------------------------------*/

bool
CMenuController::InitGUIForms( GUCE::CORE::TWindowContextPtr& windowContext )
{GU_TRACE;

    GUCEF::GUI::TGuiContextPtr guiContext = windowContext->GetGuiContext();    
    m_guiConfigRoot = "GUI/" + GUCE::GUI::CGUIManager::Instance()->GetSelectedDriverName();
    
    // Load the main menu form and setup the callbacks
    CString layoutFilePath = m_guiConfigRoot;    
    GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/MainMenu.layout" );
    m_mainMenuForm.SetContext( guiContext );
    if ( m_mainMenuForm.LoadLayout( layoutFilePath ) )
    {
        SubscribeTo( m_mainMenuForm.GetSettingsButton()                                             ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                        ,
                     &TEventCallback( this, &CMenuController::OnMainMenuFormSettingsButtonClicked ) );

        SubscribeTo( m_mainMenuForm.GetSingleplayerButton()                                             ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                            ,
                     &TEventCallback( this, &CMenuController::OnMainMenuFormSinglePlayerButtonClicked ) );

        SubscribeTo( m_mainMenuForm.GetDownloadsButton()                                         ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                     ,
                     &TEventCallback( this, &CMenuController::OnMainMenuDownloadsButtonClicked ) );

        SubscribeTo( m_mainMenuForm.GetExitButton()                                             ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                    ,
                     &TEventCallback( this, &CMenuController::OnMainMenuFormExitButtonClicked ) );
    
        m_mainMenuForm.SetVisibility( false );
    }
    else
    {
        return false;
    }
    
    GUCEF::GUI::CImageFrame* backdrop = m_mainMenuForm.GetBackgroundImageFrame();
    if ( NULL != backdrop )
    {         /*   //  Disabled: makes testing 2 slow 
        CString imageFilePath = m_guiConfigRoot;
        GUCEF::CORE::AppendToPath( imageFilePath, "Images/basic_logo_1400.jpg" );
        GUCEF::IMAGE::CImage image;
        if ( GUCE::CORE::VFSLoadImage( imageFilePath, image ) )
        {
            backdrop->SetImage( image );
        }       */   
    }

    // Load the settings menu form and setup the callbacks
    layoutFilePath = m_guiConfigRoot;
    GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/SettingsMenu.layout" );
    m_settingsMenuForm.SetContext( guiContext );
    if ( m_settingsMenuForm.LoadLayout( layoutFilePath ) )
    {
        SubscribeTo( m_settingsMenuForm.GetMenuButton()                                         ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                    ,
                     &TEventCallback( this, &CMenuController::OnSettingsFormMenuButtonClicked ) );

        // Load the video settings menu form and setup the callbacks
        GUCE::GUI::CVideoSettingsForm& vsForm = m_settingsMenuForm.GetVideoSettingsForm();
        layoutFilePath = m_guiConfigRoot;
        GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/VideoSettings.layout" );
        if ( !vsForm.LoadLayout( layoutFilePath ) )
        {
            return false;
        }
        
        GUCE::CORE::CVideoOptions videoOptions;
        GUCE::CORE::CVideoOptions::RetrieveOptionsFromOS( videoOptions );
        if ( !vsForm.SetVideoOptions( videoOptions ) ) return false;
        
        GUCE::CORE::CVideoSettings videoSettings;
        GUCE::CORE::TWindowContextPtr windowContext = GUCE::CORE::CGUCEApplication::Instance()->GetPrimaryWindowContext();
        GUCE::CORE::CVideoSettings::RetrieveSettingsFromRenderWindow( *windowContext->GetOgreWindowPtr() ,
                                                                      videoSettings                      );
        if ( !vsForm.SetVideoSettings( videoSettings ) ) return false;
        
        SubscribeTo( vsForm.GetApplyButton()                                                          ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                          ,
                     &TEventCallback( this, &CMenuController::OnVideoSettingsFormApplyButtonClicked ) );
        
        m_settingsMenuForm.SetActiveTab( 0 );
        m_settingsMenuForm.SetVisibility( false );
    }

    // Load the single player menu form and setup the callbacks
    layoutFilePath = m_guiConfigRoot;
    GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/SinglePlayerMenu.layout" );
    m_singlePlayerMenuForm.SetContext( guiContext );
    if ( m_singlePlayerMenuForm.LoadLayout( layoutFilePath ) )
    {
        SubscribeTo( m_singlePlayerMenuForm.GetMenuButton()                                         ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                        ,
                     &TEventCallback( this, &CMenuController::OnSinglePlayerFormMenuButtonClicked ) );
    
    }
    else
    {
        //return false;
    }

    // Load the downloads menu form and setup the callbacks
    layoutFilePath = m_guiConfigRoot;
    GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/DownloadsMenu.layout" );
    m_downloadsMenuForm.SetContext( guiContext );
    if ( m_downloadsMenuForm.LoadLayout( layoutFilePath ) )
    {
        SubscribeTo( m_downloadsMenuForm.GetMenuButton()                                         ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                     ,
                     &TEventCallback( this, &CMenuController::OnDownloadsFormMenuButtonClicked ) );
        SubscribeTo( m_downloadsMenuForm.GetRefreshButton()                                       ,
                     GUCEF::GUI::CButton::ButtonClickedEvent                                      ,
                     &TEventCallback( this, &CMenuController::OnDownloadsFormRefreshButtonClicked ) );
    
    }
    else
    {
        //return false;
    }
    
    layoutFilePath = m_guiConfigRoot;
    GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/MeshViewer.layout" );
    m_meshViewer.GetMeshViewerForm().SetContext( guiContext );
    if ( m_meshViewer.GetMeshViewerForm().LoadLayout( layoutFilePath ) )
    {
        layoutFilePath = m_guiConfigRoot;
        GUCEF::CORE::AppendToPath( layoutFilePath, "Forms/FileSystemDialog.layout" );    
        if ( m_meshViewer.GetFileOpenDialog().LoadLayout( layoutFilePath ) )
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        //return false;
    }
    
    NotifyObservers( MenuSystemInitializedEvent );
    return true;
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnMainMenuFormSettingsButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                      const GUCEF::CORE::CEvent& eventid  ,
                                                      GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    m_meshViewer.ShowModal();
    
    //m_settingsMenuForm.SetVisibility( true );
    //m_mainMenuForm.SetVisibility( false );    
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnMainMenuFormSinglePlayerButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                          const GUCEF::CORE::CEvent& eventid  ,
                                                          GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    m_singlePlayerMenuForm.SetVisibility( true );
    m_mainMenuForm.SetVisibility( false );
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnMainMenuDownloadsButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                   const GUCEF::CORE::CEvent& eventid  ,
                                                   GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    m_downloadsMenuForm.SetVisibility( true );
    m_mainMenuForm.SetVisibility( false );
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnMainMenuFormExitButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                  const GUCEF::CORE::CEvent& eventid  ,
                                                  GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    GUCE::CORE::CGUCEApplication::Instance()->Stop();    
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnDownloadsFormMenuButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                   const GUCEF::CORE::CEvent& eventid  ,
                                                   GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    m_downloadsMenuForm.SetVisibility( false );
    m_mainMenuForm.SetVisibility( true );
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnDownloadsFormRefreshButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                      const GUCEF::CORE::CEvent& eventid  ,
                                                      GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    switch ( m_downloadsMenuForm.GetActiveTab() )
    {
        case CDownloadsMenuForm::DOWNLOADSTAB_AVAILABLE :
        {
            CDownloadsManager& dlManager = CProductManager::Instance()->GetDownloadsManager();
            dlManager.RefreshAvailableDownloadsList();        
            return;
        }
        default :
        {
            return;
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnSettingsFormMenuButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                  const GUCEF::CORE::CEvent& eventid  ,
                                                  GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    m_settingsMenuForm.SetVisibility( false );
    m_mainMenuForm.SetVisibility( true );
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnSinglePlayerFormMenuButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                      const GUCEF::CORE::CEvent& eventid  ,
                                                      GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    m_singlePlayerMenuForm.SetVisibility( false );
    m_mainMenuForm.SetVisibility( true );
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnVideoSettingsFormApplyButtonClicked( GUCEF::CORE::CNotifier* notifier    ,
                                                        const GUCEF::CORE::CEvent& eventid  ,
                                                        GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    GUCE::CORE::CVideoSettings videoSettings;    
    if ( m_settingsMenuForm.GetVideoSettingsForm().GetVideoSettings( videoSettings ) )
    {
        GUCE::CORE::TWindowContextPtr windowContext = GUCE::CORE::CGUCEApplication::Instance()->GetPrimaryWindowContext();
        GUCE::CORE::CWindowManager::Instance()->ApplyVideoSettings( windowContext, videoSettings );
    }
}

/*-------------------------------------------------------------------------*/
                                                                             
void
CMenuController::SetVisibility( const bool isVisible )
{GU_TRACE;

    m_mainMenuForm.SetVisibility( isVisible );
}

/*-------------------------------------------------------------------------*/

void
CMenuController::OnNotify( GUCEF::CORE::CNotifier* notifier                 ,
                           const GUCEF::CORE::CEvent& eventid               ,
                           GUCEF::CORE::CICloneable* eventdata /* = NULL */ )
{GU_TRACE;

    
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
