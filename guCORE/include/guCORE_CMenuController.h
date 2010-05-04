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

#ifndef GU_CORE_CMENUCONTROLLER_H
#define GU_CORE_CMENUCONTROLLER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_COBSERVINGNOTIFIER_H
#include "CObservingNotifier.h"
#define GUCEF_CORE_COBSERVINGNOTIFIER_H
#endif /* GUCEF_CORE_COBSERVINGNOTIFIER_H ? */

#ifndef GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#include "gucefCORE_CTEventHandlerFunctor.h"
#define GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#endif /* GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H ? */

#ifndef GUCE_CORE_CWINDOWCONTEXT_H
#include "CWindowContext.h"
#define GUCE_CORE_CWINDOWCONTEXT_H
#endif /* GUCE_CORE_CWINDOWCONTEXT_H ? */

#ifndef GUCE_GUI_CGUIMESHVIEWER_H
#include "guceGUI_CMeshViewer.h"
#define GUCE_GUI_CGUIMESHVIEWER_H
#endif /* GUCE_GUI_CGUIMESHVIEWER_H ? */

#ifndef GUCE_GUI_CSETTINGSMENUFORM_H
#include "guceGUI_CSettingsMenuForm.h"
#define GUCE_GUI_CSETTINGSMENUFORM_H
#endif /* GUCE_GUI_CSETTINGSMENUFORM_H ? */

#ifndef GU_CORE_CMAINMENUFORM_H
#include "guCORE_CMainMenuForm.h"
#define GU_CORE_CMAINMENUFORM_H
#endif /* GU_CORE_CMAINMENUFORM_H ? */

#ifndef GU_CORE_CSINGLEPLAYERFORM_H
#include "guCORE_CSinglePlayerForm.h"
#define GU_CORE_CSINGLEPLAYERFORM_H
#endif /* GU_CORE_CSINGLEPLAYERFORM_H ? */

#ifndef GU_CORE_CDOWNLOADSMENUFORM_H
#include "guCORE_CDownloadsMenuForm.h"
#define GU_CORE_CDOWNLOADSMENUFORM_H
#endif /* GU_CORE_CDOWNLOADSMENUFORM_H ? */

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

/**
 *  Controller that manages the GU menu GUI according to the PAC design pattern
 */
class GU_CORE_EXPORT_CPP CMenuController : public GUCEF::CORE::CObservingNotifier
{
    public:
    
    static const GUCEF::CORE::CEvent MenuSystemInitializedEvent;
    
    static void RegisterEvents( void );
    
    public:
    
    CMenuController( void );

    virtual ~CMenuController();

    bool InitGUIForms( GUCE::CORE::TWindowContextPtr& windowContext );
    
    void SetVisibility( const bool isVisible );
    
    virtual const CString& GetClassTypeName( void ) const;

    protected:
    
    /**
     *  @param notifier the notifier that sent the notification
     *  @param eventid the unique event id for an event
     *  @param eventdata optional notifier defined userdata
     */
    virtual void OnNotify( GUCEF::CORE::CNotifier* notifier           ,
                           const GUCEF::CORE::CEvent& eventid         ,
                           GUCEF::CORE::CICloneable* eventdata = NULL );
    
    private:
    
    typedef GUCEF::CORE::CTEventHandlerFunctor< CMenuController > TEventCallback;
    
    CMenuController( const CMenuController& src );             /**< not implemented: makes no sense */
    CMenuController& operator=( const CMenuController& src );  /**< not implemented: makes no sense */

    void OnMainMenuFormSettingsButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                              const GUCEF::CORE::CEvent& eventid         ,
                                              GUCEF::CORE::CICloneable* eventdata = NULL );

    void OnMainMenuFormSinglePlayerButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                                  const GUCEF::CORE::CEvent& eventid         ,
                                                  GUCEF::CORE::CICloneable* eventdata = NULL );

    void OnMainMenuDownloadsButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                           const GUCEF::CORE::CEvent& eventid         ,
                                           GUCEF::CORE::CICloneable* eventdata = NULL );
    
    void OnMainMenuFormExitButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                          const GUCEF::CORE::CEvent& eventid         ,
                                          GUCEF::CORE::CICloneable* eventdata = NULL );

    void OnSettingsFormMenuButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                          const GUCEF::CORE::CEvent& eventid         ,
                                          GUCEF::CORE::CICloneable* eventdata = NULL );
    
    void OnDownloadsFormMenuButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                           const GUCEF::CORE::CEvent& eventid         ,
                                           GUCEF::CORE::CICloneable* eventdata = NULL );

    void OnDownloadsFormRefreshButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                              const GUCEF::CORE::CEvent& eventid         ,
                                              GUCEF::CORE::CICloneable* eventdata = NULL );

    void OnSinglePlayerFormMenuButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                              const GUCEF::CORE::CEvent& eventid         ,
                                              GUCEF::CORE::CICloneable* eventdata = NULL );    

    void OnVideoSettingsFormApplyButtonClicked( GUCEF::CORE::CNotifier* notifier           ,
                                                const GUCEF::CORE::CEvent& eventid         ,
                                                GUCEF::CORE::CICloneable* eventdata = NULL );

    private:
    
    CString m_guiConfigRoot;
    GUCE::GUI::CSettingsMenuForm m_settingsMenuForm;
    CSinglePlayerForm m_singlePlayerMenuForm;
    CDownloadsMenuForm m_downloadsMenuForm;
    CMainMenuForm m_mainMenuForm;
    GUCE::GUI::CMeshViewer m_meshViewer;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CMENUCONTROLLER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 14-01-2007 :
        - Dinand: Initial implementation

---------------------------------------------------------------------------*/
