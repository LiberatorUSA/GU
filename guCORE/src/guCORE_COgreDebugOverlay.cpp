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

#ifndef __RenderTarget_H__
#include "OgreRenderTarget.h"
#define __RenderTarget_H__
#endif /* __RenderTarget_H__ ? */

#ifndef __RenderWindow_H__
#include "OgreRenderWindow.h"
#define __RenderWindow_H__
#endif /* __RenderWindow_H__ ? */

#ifndef __OverlayManager_H__
#include "OgreOverlayManager.h"
#define __OverlayManager_H__
#endif /* __OverlayManager_H__ ? */

#ifndef __OverlayElement_H__
#include "OgreOverlayElement.h"
#define __OverlayElement_H__
#endif /* __OverlayElement_H__ ? */

#ifndef __StringConverter_H__
#include "OgreStringConverter.h"
#define __StringConverter_H__
#endif /* __StringConverter_H__?  */

#ifndef GUCE_CORE_CGUCEAPPLICATION_H
#include "CGUCEApplication.h"
#define GUCE_CORE_CGUCEAPPLICATION_H
#endif /* GUCE_CORE_CGUCEAPPLICATION_H ? */

#include "guCORE_COgreDebugOverlay.h"   /* declaration for the class implemented here */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

COgreDebugOverlay::COgreDebugOverlay( void )
    : FrameListener()          ,
      m_debugOverlay( NULL )   ,
      m_overlayManager( NULL ) ,
      m_window()
{GUCE_TRACE;

    LinkOverlay();
}

/*--------------------------------------------------------------------------*/

COgreDebugOverlay::~COgreDebugOverlay()
{GUCE_TRACE;

    Ogre::Root::getSingletonPtr()->removeFrameListener( this );
}

/*--------------------------------------------------------------------------*/

bool
COgreDebugOverlay::LinkOverlay( void )
{GUCE_TRACE;

    try
    {
        m_window = GUCE::CORE::CGUCEApplication::Instance()->GetPrimaryWindowContext();
        m_overlayManager = Ogre::OverlayManager::getSingletonPtr();
        
        if ( NULL == m_debugOverlay )
        {        
            m_debugOverlay = Ogre::OverlayManager::getSingleton().getByName( "Core/DebugOverlay" );
            if ( NULL != m_debugOverlay )
            {
                Ogre::Root::getSingletonPtr()->addFrameListener( this );
                return true;
            }
            return false;
        }
        return true;
    }
    catch ( Ogre::Exception& )
    {
        return false;
    }
}
    
/*-------------------------------------------------------------------------*/

bool
COgreDebugOverlay::frameStarted( const Ogre::FrameEvent& evt )
{GUCE_TRACE;

    return true;
}

/*-------------------------------------------------------------------------*/
    
bool
COgreDebugOverlay::frameEnded( const Ogre::FrameEvent& evt )
{GUCE_TRACE;

    if ( NULL != m_debugOverlay )
    {
        static Ogre::String currFps = "Current FPS: ";
        static Ogre::String avgFps = "Average FPS: ";
        static Ogre::String bestFps = "Best FPS: ";
        static Ogre::String worstFps = "Worst FPS: ";
        static Ogre::String tris = "Triangle Count: ";

        // update stats when necessary
        try
        {
            Ogre::OverlayElement* guiAvg = m_overlayManager->getOverlayElement( "Core/AverageFps" );
            Ogre::OverlayElement* guiCurr = m_overlayManager->getOverlayElement( "Core/CurrFps" );
            Ogre::OverlayElement* guiBest = m_overlayManager->getOverlayElement( "Core/BestFps" );
            Ogre::OverlayElement* guiWorst = m_overlayManager->getOverlayElement( "Core/WorstFps" );

            const Ogre::RenderTarget::FrameStats& stats = m_window->GetOgreWindowPtr()->getStatistics();

            guiAvg->setCaption( avgFps + Ogre::StringConverter::toString( stats.avgFPS ) );
            guiCurr->setCaption( currFps + Ogre::StringConverter::toString( stats.lastFPS ) );
            guiBest->setCaption( bestFps + Ogre::StringConverter::toString( stats.bestFPS )
                +" "+Ogre::StringConverter::toString(stats.bestFrameTime)+" ms");
            guiWorst->setCaption(worstFps + Ogre::StringConverter::toString(stats.worstFPS )
                +" "+Ogre::StringConverter::toString(stats.worstFrameTime)+" ms");

            Ogre::OverlayElement* guiTris = m_overlayManager->getOverlayElement( "Core/NumTris" );
            guiTris->setCaption( tris + Ogre::StringConverter::toString( stats.triangleCount ) );

            //Ogre::OverlayElement* guiDbg = m_overlayManager->getOverlayElement( "Core/DebugText" );
            //guiDbg->setCaption( m_window->GetOgreWindowPtr()->getDebugText() );
        }
        catch( Ogre::Exception& )
        {
            // ignore
        }    
    }
    
    return true;
}

/*-------------------------------------------------------------------------*/
        
const Ogre::Overlay*
COgreDebugOverlay::GetOverlay( void ) const
{GUCE_TRACE;
    
    return m_debugOverlay;
}

/*-------------------------------------------------------------------------*/

void
COgreDebugOverlay::Show( void )
{GUCE_TRACE;

    if ( LinkOverlay() )
    {
        m_debugOverlay->show();
    }
}

/*-------------------------------------------------------------------------*/
    
void
COgreDebugOverlay::Hide( void )
{GUCE_TRACE;
    
    if ( LinkOverlay() )
    {
        m_debugOverlay->hide();
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
