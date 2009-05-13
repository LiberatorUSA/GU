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

#ifndef GU_CORE_CDOWNLOADSMANAGER_H
#define GU_CORE_CDOWNLOADSMANAGER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CTCLONEABLEOBJ_H
#include "CTCloneableObj.h"
#define GUCEF_CORE_CTCLONEABLEOBJ_H
#endif /* GUCEF_CORE_CTCLONEABLEOBJ_H ? */

#ifndef GUCEF_CORE_CURLDATARETRIEVER_H
#include "CURLDataRetriever.h"
#define GUCEF_CORE_CURLDATARETRIEVER_H
#endif /* GUCEF_CORE_CURLDATARETRIEVER_H ? */

#ifndef GUCEF_PATCHER_CPATCHMANAGER_H
#include "gucefPATCHER_CPatchManager.h"
#define GUCEF_PATCHER_CPATCHMANAGER_H
#endif /* GUCEF_PATCHER_CPATCHMANAGER_H ? */

#ifndef GU_CORE_CPRODUCTINFO_H
#include "guCORE_CProductInfo.h"
#define GU_CORE_CPRODUCTINFO_H
#endif /* GU_CORE_CPRODUCTINFO_H ? */

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
 *  Manager for all content downloads
 */
class GU_CORE_EXPORT_CPP CDownloadsManager : public GUCEF::CORE::CObservingNotifier
{
    public:
    
    static const GUCEF::CORE::CEvent DownloadStartedEvent;
    static const GUCEF::CORE::CEvent DownloadStoppedEvent;
    static const GUCEF::CORE::CEvent DownloadStopRequestedEvent;
    static const GUCEF::CORE::CEvent DownloadFinishedEvent;
    static const GUCEF::CORE::CEvent DownloadPausedEvent;
    static const GUCEF::CORE::CEvent DownloadResumedEvent;
    static const GUCEF::CORE::CEvent PatchTaskEventReceivedEvent;
    
    typedef GUCEF::CORE::CTCloneableObj< CProductInfo > TDownloadEventData;
    typedef TDownloadEventData  TDownloadStartedEventData;
    typedef TDownloadEventData  TDownloadStoppedEventData;
    typedef TDownloadEventData  TDownloadStopRequestedEventData;
    typedef TDownloadEventData  TDownloadFinishedEventData;
    typedef TDownloadEventData  TDownloadPausedEventData;
    typedef TDownloadEventData  TDownloadResumedEventData;
    
    struct SProductPatchEventData
    {
        CProductInfo productInfo;               /** product for which a patch event was emitted */ 
        GUCEF::PATCHER::CPatchEngine& notifier; /** patch engine that emitted the event */
        GUCEF::CORE::CEvent patchEvent;         /** patch event emitted for the given product */
        GUCEF::CORE::CICloneable* eventData;    /** event data for the given patch event */
    };
    typedef struct SProductPatchEventData TProductPatchEventData;
    typedef GUCEF::CORE::CTCloneableObj< TProductPatchEventData > TPatchTaskEventReceivedEventData;
    
    static void RegisterEvents( void );
    
    public:
    
    typedef std::map< CString, CProductInfo > TProductMap;
    
    CDownloadsManager( void );
    
    virtual ~CDownloadsManager();
    
    bool StartDownload( const CProductInfo& productInfo );

    bool PauseDownload( const CProductInfo& productInfo );
    
    bool ResumeDownload( const CProductInfo& productInfo );
    
    bool RequestDownloadToStop( const CProductInfo& productInfo );
        
    void GetDownloadList( TProductMap& list ) const;

    bool ObtainAvailableDownloadsList( const CString& listUrl );
    
    void RefreshAvailableDownloadsList( void );
    
    bool SaveConfig( GUCEF::CORE::CDataNode& node );
                                
    bool LoadConfig( const GUCEF::CORE::CDataNode& node );    
    
    private:
    
    typedef GUCEF::CORE::CTEventHandlerFunctor< CDownloadsManager > TEventCallback;
    
    virtual void OnNotify( GUCEF::CORE::CNotifier* notifier           ,
                           const GUCEF::CORE::CEvent& eventid         ,
                           GUCEF::CORE::CICloneable* eventdata = NULL );

    virtual void OnADListRetrievalEvent( GUCEF::CORE::CNotifier* notifier           ,
                                         const GUCEF::CORE::CEvent& eventid         ,
                                         GUCEF::CORE::CICloneable* eventdata = NULL );
    
    private:
    
    CDownloadsManager( const CDownloadsManager& src );
    CDownloadsManager& operator=( const CDownloadsManager& src );
        
    private:    
     
    TProductMap m_productMap;
    CString m_patchEngineConfigTemplatePath;
    CString m_patchEngineConfigTemplateCodec;
    GUCEF::PATCHER::CPatchManager m_patchManager;
    GUCEF::CORE::CURLDataRetriever m_adListUrlRetiever;
    bool m_resumeDownloadsOnStartup;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CDOWNLOADSMANAGER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 11-02-2008 :
        - Initial implementation
          
---------------------------------------------------------------------------*/
