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

#ifndef GU_CORE_COGREDEBUGOVERLAY_H
#define GU_CORE_COGREDEBUGOVERLAY_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCE_CORE_CWINDOWMANAGER_H
#include "CWindowManager.h"
#define GUCE_CORE_CWINDOWMANAGER_H
#endif /* GUCE_CORE_CWINDOWMANAGER_H ? */

#ifndef __FrameListener_H__
#include "OgreFrameListener.h"
#define __FrameListener_H__
#endif /* __FrameListener_H__ ? */

#ifndef GU_CORE_MACROS_H
#include "guCORE_macros.h"
#define GU_CORE_MACROS_H
#endif /* GU_CORE_MACROS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace Ogre { class Overlay; class OverlayManager; }

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

class GU_CORE_EXPORT_CPP COgreDebugOverlay : protected Ogre::FrameListener
{
    public:
    
    COgreDebugOverlay( void );
    
    virtual ~COgreDebugOverlay();
              
    const Ogre::Overlay* GetOverlay( void ) const;
    
    void Show( void );
    
    void Hide( void );

    protected:
    
    /** Called when a frame is about to begin rendering.
        @return
            True to go ahead, false to abort rendering and drop
            out of the rendering loop.
    */
    virtual bool frameStarted( const Ogre::FrameEvent& evt );
    
    /** Called just after a frame has been rendered.
        @return
            True to continue with the next frame, false to drop
            out of the rendering loop.
    */
    virtual bool frameEnded( const Ogre::FrameEvent& evt );
    
    private:
    
    COgreDebugOverlay( const COgreDebugOverlay& src );
    COgreDebugOverlay& operator=( const COgreDebugOverlay& src );
    
    bool LinkOverlay( void );
    
    private:
    
    Ogre::Overlay* m_debugOverlay;
    Ogre::OverlayManager* m_overlayManager;
    GUCE::CORE::TWindowContextPtr m_window;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_COGREDEBUGOVERLAY_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 17-03-2007 :
        - Dinand: Initial implementation

-----------------------------------------------------------------------------*/