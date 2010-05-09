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
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CGUCEFAPPLICATION_H
#include "CGUCEFApplication.h"
#define GUCEF_CORE_CGUCEFAPPLICATION_H
#endif /* GUCEF_CORE_CGUCEFAPPLICATION_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCE_CORE_CGUCEAPPLICATION_H
#include "CGUCEApplication.h"
#define GUCE_CORE_CGUCEAPPLICATION_H
#endif /* GUCE_CORE_CGUCEAPPLICATION_H ? */

#ifndef GUCE_CORE_MISCUTILS_H
#include "miscutils.h"
#define GUCE_CORE_MISCUTILS_H
#endif /* GUCE_CORE_MISCUTILS_H ? */

#ifndef GUCE_GUI_CGUIMANAGER_H
#include "CGUIManager.h"
#define GUCE_GUI_CGUIMANAGER_H
#endif /* GUCE_GUI_CGUIMANAGER_H ? */

#include "guCORE_CGameCenter.h"

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

CGameCenter* CGameCenter::g_instance = NULL;

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CGameCenter::CGameCenter( void )
    : m_gameRegistry()                       ,
      m_mpGameRegistry()                     ,
      m_gameFactory()                        ,
      m_mpGameFactory()                      ,
      m_configRoot()                         ,
      m_nameOfGameConfigFile( "config.dat" ) ,
      m_gameConfigFileCodec( "xml" )         ,
      m_appArgsList()                        ,
      m_console( NULL )                      ,
      m_ogreDebugOverlay( NULL )             ,
      m_menuController()                     ,
      m_startupComplete( false )
{GU_TRACE;

    SubscribeTo( GUCEF::CORE::CGUCEFApplication::Instance(), GUCEF::CORE::CGUCEFApplication::AppInitEvent );
    SubscribeTo( GUCE::GUI::CGUIManager::Instance(), GUCE::GUI::CGUIManager::GUIInitializedEvent );
    
    SubscribeTo( &GUCEF::CORE::CGUCEFApplication::Instance()->GetPulseGenerator() , 
                 GUCEF::CORE::CPulseGenerator::PulseEvent                         ,
                 &TEventCallback( this, &GU::CORE::CGameCenter::OnPulse )         );
}

/*-------------------------------------------------------------------------*/

CGameCenter::~CGameCenter()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CGameCenter*
CGameCenter::Instance( void )
{GU_TRACE;

    if ( g_instance == NULL )
    {
        g_instance = new CGameCenter();
    }
    return g_instance;
}

/*-------------------------------------------------------------------------*/

CMenuController&
CGameCenter::GetMenuController( void )
{GU_TRACE;

    return m_menuController;
}

/*-------------------------------------------------------------------------*/
    
CGameRegistry&
CGameCenter::GetGameRegistry( void )
{GU_TRACE;

    return m_gameRegistry;
}

/*-------------------------------------------------------------------------*/
    
CGameFactory&
CGameCenter::GetGameFactory( void )
{GU_TRACE;

    return m_gameFactory;
}

/*-------------------------------------------------------------------------*/

CMultiplayerGameRegistry&
CGameCenter::GetMultiplayerGameRegistry( void )
{GU_TRACE;

    return m_mpGameRegistry;
}

/*-------------------------------------------------------------------------*/
    
CMultiplayerGameFactory&
CGameCenter::GetMultiplayerGameFactory( void )
{GU_TRACE;

    return m_mpGameFactory;
}

/*-------------------------------------------------------------------------*/

void
CGameCenter::Deinstance( void )
{GU_TRACE;

    delete g_instance;
    g_instance = NULL;
}

/*-------------------------------------------------------------------------*/

CString
CGameCenter::GetGameConfigPath( const CString& gameTitle ) const
{GU_TRACE;

    CString gameConfigRoot( m_configRoot );
    GUCEF::CORE::AppendToPath( gameConfigRoot, gameTitle );
    GUCEF::CORE::AppendToPath( gameConfigRoot, m_nameOfGameConfigFile );
    return gameConfigRoot;
}

/*-------------------------------------------------------------------------*/

bool
CGameCenter::GetGameConfig( const CString& gameTitle       ,
                            GUCEF::CORE::CDataNode& config ) const
{GU_TRACE;

    CString gameConfigPath( GetGameConfigPath( gameTitle ) );
    
    return GUCE::CORE::VFSLoadDataTree( gameConfigPath        ,
                                        m_gameConfigFileCodec ,
                                        &config               );
}

/*-------------------------------------------------------------------------*/

bool
CGameCenter::LaunchSPGame( const CString& gameTitle )
{GU_TRACE;

    GUCEF::CORE::CDataNode gameConfig;
    if ( GetGameConfig( gameTitle  ,
                        gameConfig ) )
    {
        CGame* newGame = m_gameFactory.Create( gameTitle  ,
                                               gameConfig );
        
        if ( NULL != newGame )
        {                            
            if ( newGame->StartSPGame() )
            {
                m_gameRegistry.Register( gameTitle           ,
                                         CGamePtr( newGame ) );
                                         
                return true;
            }

            m_gameFactory.Destroy( newGame );
        }
    }
    return false;
}

/*-------------------------------------------------------------------------*/

bool
CGameCenter::LaunchMPGame( const CString& gameTitle )
{GU_TRACE;

    GUCEF::CORE::CDataNode gameConfig;
    if ( GetGameConfig( gameTitle  ,
                        gameConfig ) )
    {
        CMultiplayerGame* newGame = m_mpGameFactory.Create( gameTitle  ,
                                                            gameConfig );
        
        if ( NULL != newGame )
        {                       //@TODO: fix     
            if ( newGame->StartSPGame() )
            {
                m_mpGameRegistry.Register( gameTitle                      ,
                                           CMultiplayerGamePtr( newGame ) );
                                         
                return true;
            }

            m_mpGameFactory.Destroy( newGame );
        }
    }
    return false;
}

/*-------------------------------------------------------------------------*/

const GUCEF::CORE::CValueList&
CGameCenter::GetAppArgs( void ) const
{GU_TRACE;

    return m_appArgsList;
}

/*-------------------------------------------------------------------------*/

void
CGameCenter::OnAppInitEvent( GUCEF::CORE::CICloneable* eventdata )
{GU_TRACE;

    GUCEF::CORE::CGUCEFApplication::SAppInitEventData& appArgs = static_cast< GUCEF::CORE::CGUCEFApplication::TAppInitEventData* >( eventdata )->GetData();
    
    // first we concatenate all the argument strings
    CString args;
    for ( Int32 i=0; i<appArgs.argc; ++i )
    {
        args += appArgs.argv[ i ];
    }
    
    // We now parse the application arguments
    m_appArgsList.DeleteAll();
    m_appArgsList.SetMultiple( args, '\"' );
}

/*-------------------------------------------------------------------------*/

void
CGameCenter::ShowMenu( void )
{GU_TRACE;

    m_menuController.SetVisibility( true );
}

/*-------------------------------------------------------------------------*/

void
CGameCenter::OnStartupComplete( GUCE::CORE::TWindowContextPtr& windowContext )
{GU_TRACE;

    if ( m_menuController.InitGUIForms( windowContext ) )
    {
        if ( m_appArgsList.HasKey( "LaunchSPGame" ) )
        {
            LaunchSPGame( m_appArgsList.GetValue( "LaunchSPGame" ) );
        }
        else
        if ( m_appArgsList.HasKey( "LaunchMPGame" ) )
        {
            LaunchMPGame( m_appArgsList.GetValue( "LaunchMPGame" ) );
        }
        else
        {
            ShowMenu();
        }
        m_startupComplete = true;
    }
    else
    {
        GUCE::CORE::CGUCEApplication::Instance()->Stop();
    }
    
}

/*-------------------------------------------------------------------------*/

void
CGameCenter::OnPulse( GUCEF::CORE::CNotifier* notifier                 ,
                      const GUCEF::CORE::CEvent& eventid               ,
                      GUCEF::CORE::CICloneable* eventdata /* = NULL */ )
{GU_TRACE;
  
    if ( m_startupComplete )
    {
        try
        {
            if ( !Ogre::Root::getSingletonPtr()->renderOneFrame() )
            {
                    GUCE::CORE::CGUCEApplication::Instance()->Stop();
                    return;
            }
        }
        catch ( Ogre::Exception& /* e */ )
        {
            GUCEF_ERROR_LOG( 0, "CGameCenter::OnPulse(): Exception during Ogre frame rendering" );
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CGameCenter::OnNotify( GUCEF::CORE::CNotifier* notifier                 ,
                       const GUCEF::CORE::CEvent& eventid               ,
                       GUCEF::CORE::CICloneable* eventdata /* = NULL */ )
{GU_TRACE;

    if ( GUCEF::CORE::CGUCEFApplication::AppInitEvent == eventid ) 
    {
        OnAppInitEvent( eventdata );
    }
    else
    if ( GUCE::GUI::CGUIManager::GUIInitializedEvent == eventid )
    {        
        GUCE::GUI::CGUIManager::TGUIInitializedEventData* eData = static_cast< GUCE::GUI::CGUIManager::TGUIInitializedEventData* >( eventdata );
        OnStartupComplete( eData->GetData() );
    }
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
