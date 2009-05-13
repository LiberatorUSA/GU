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

#ifndef GU_CORE_CGAMECENTER_H
#define GU_CORE_CGAMECENTER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CVALUELIST_H
#include "CValueList.h"
#define GUCEF_CORE_CVALUELIST_H
#endif /* GUCEF_CORE_CVALUELIST_H ? */

#ifndef GUCE_GUI_CCONSOLE_H
#include "guceGUI_CConsole.h"
#define GUCE_GUI_CCONSOLE_H
#endif /* GUCE_GUI_CCONSOLE_H ? */

#ifndef GU_CORE_COGREDEBUGOVERLAY_H
#include "guCORE_COgreDebugOverlay.h"
#define GU_CORE_COGREDEBUGOVERLAY_H
#endif /* GU_CORE_COGREDEBUGOVERLAY_H ? */

#ifndef GU_CORE_CGAMEFACTORY_H
#include "guCORE_CGameFactory.h"
#define GU_CORE_CGAMEFACTORY_H
#endif /* GU_CORE_CGAMEFACTORY_H ? */

#ifndef GU_CORE_CMULTIPLAYERGAMEFACTORY_H
#include "guCORE_CMultiplayerGameFactory.h"
#define GU_CORE_CMULTIPLAYERGAMEFACTORY_H
#endif /* GU_CORE_CMULTIPLAYERGAMEFACTORY_H ? */

#ifndef GU_CORE_CGAMEREGISTRY_H
#include "guCORE_CGameRegistry.h"
#define GU_CORE_CGAMEREGISTRY_H
#endif /* GU_CORE_CGAMEREGISTRY_H ? */

#ifndef GU_CORE_CMULTIPLAYERGAMEREGISTRY_H
#include "guCORE_CMultiplayerGameRegistry.h"
#define GU_CORE_CMULTIPLAYERGAMEREGISTRY_H
#endif /* GU_CORE_CMULTIPLAYERGAMEREGISTRY_H ? */

#ifndef GU_CORE_CMENUCONTROLLER_H
#include "guCORE_CMenuController.h"
#define GU_CORE_CMENUCONTROLLER_H
#endif /* GU_CORE_CMENUCONTROLLER_H ? */

#ifndef GU_CORE_CDOWNLOADSMANAGER_H
#include "guCORE_CDownloadsManager.h"
#define GU_CORE_CDOWNLOADSMANAGER_H
#endif /* GU_CORE_CDOWNLOADSMANAGER_H ? */

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
 
class CGUCOREModule;

/*-------------------------------------------------------------------------*/
 
/**
 *  This is the main interconnect point for all GU related products
 *  All games should register at the game center, if they do they will become
 *  available to the GU platform.
 */
class GU_CORE_EXPORT_CPP CGameCenter : public GUCEF::CORE::CObservingNotifier
{
    public:
    
    static CGameCenter* Instance( void );
    
    CGameRegistry& GetGameRegistry( void );
    
    CGameFactory& GetGameFactory( void );
    
    const GUCEF::CORE::CValueList& GetAppArgs( void ) const;

    CMultiplayerGameRegistry& GetMultiplayerGameRegistry( void );
    
    CMultiplayerGameFactory& GetMultiplayerGameFactory( void );
    
    bool LaunchSPGame( const CString& gameTitle );
    
    bool LaunchMPGame( const CString& gameTitle );
    
    CMenuController& GetMenuController( void );
    
    CDownloadsManager& GetDownloadsManager( void );

    protected:
    
    virtual void OnNotify( GUCEF::CORE::CNotifier* notifier           ,
                           const GUCEF::CORE::CEvent& eventid         ,
                           GUCEF::CORE::CICloneable* eventdata = NULL );    
    
    void OnPulse( GUCEF::CORE::CNotifier* notifier           ,
                  const GUCEF::CORE::CEvent& eventid         ,
                  GUCEF::CORE::CICloneable* eventdata = NULL );
                               
    private:
    friend class CGUCOREModule;
    
    static void Deinstance( void );
    
    private:
    typedef GUCEF::CORE::CTEventHandlerFunctor< CGameCenter > TEventCallback;
    
    CGameCenter( void );
    CGameCenter( const CGameCenter& src );
    ~CGameCenter();
    CGameCenter& operator=( const CGameCenter& src );
    
    void OnAppInitEvent( GUCEF::CORE::CICloneable* eventdata );
    
    void OnStartupComplete( void );
    
    void ShowMenu( void );

    CString GetGameConfigPath( const CString& gameTitle ) const;
    
    bool GetGameConfig( const CString& gameTitle       ,
                        GUCEF::CORE::CDataNode& config ) const;
    
    private:
    
    CGameRegistry m_gameRegistry;
    CMultiplayerGameRegistry m_mpGameRegistry;
    CGameFactory m_gameFactory;
    CMultiplayerGameFactory m_mpGameFactory;
    CString m_configRoot;
    CString m_nameOfGameConfigFile;
    CString m_gameConfigFileCodec;
    GUCEF::CORE::CValueList m_appArgsList;
    CString m_guiConfigRoot;
    GUCE::GUI::CConsole* m_console;
    COgreDebugOverlay* m_ogreDebugOverlay;
    CMenuController m_menuController;
    CDownloadsManager m_downloadsManager;
    bool m_startupComplete;
    static CGameCenter* g_instance;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CGAMECENTER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 08-04-2005 :
        - Initial implementation
          
---------------------------------------------------------------------------*/
