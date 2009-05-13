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

/*
 *      This is the main include header for the guCORE library.
 *      It is part of a product familiy codebase by name of 
 *      Galaxy Unlimited.
 *
 *      This library houses the shared platform elements used in all
 *      GU products at the context awareness level of GU product
 *      development
 */

#ifndef GU_CORE_H
#define GU_CORE_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Library build configuration      
 */
#ifndef GU_CORE_CONFIG_H
#include "guCORE_config.h"
#define GU_CORE_CONFIG_H
#endif /* GU_CORE_CONFIG_H ? */

/*
 *      Library specific macros and generic macros
 */
#ifndef GU_CORE_MACROS_H
#include "guCORE_macros.h"
#define GU_CORE_MACROS_H
#endif /* GU_CORE_MACROS_H ? */

#ifndef GU_CORE_ETYPES_H
#include "guCORE_ETypes.h"
#define GU_CORE_ETYPES_H
#endif /* GU_CORE_ETYPES_H ? */

/*---------------------------------------------------------------------------/

        C++ includes

/---------------------------------------------------------------------------*/
#ifdef __cplusplus

#ifndef GU_CORE_CMULTIPLAYERGAME_H
#include "guCORE_CMultiplayerGame.h"
#define GU_CORE_CMULTIPLAYERGAME_H
#endif /* GU_CORE_CMULTIPLAYERGAME_H ? */

#ifndef GU_CORE_CGAME_H
#include "guCORE_CGame.h"
#define GU_CORE_CGAME_H
#endif /* GU_CORE_CGAME_H ? */

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

#endif /* __cplusplus ? */
/*--------------------------------------------------------------------------*/

#endif /* GU_CORE_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 07-07-2007 :
       - initial version

-----------------------------------------------------------------------------*/


 
