/*
 *  guCApluginPOF: Generic GUCEF plugin for decoding "Violation" POF models
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

#ifndef GU_CA_PLUGIN_POF_CPOFMESHCODEC_H
#define GU_CA_PLUGIN_POF_CPOFMESHCODEC_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <map>

#ifndef GUCE_CORE_CIMESHCODEC_H
#include "guceCORE_CIMeshCodec.h"
#define GUCE_CORE_CIMESHCODEC_H
#endif /* GUCE_CORE_CIMESHCODEC_H ? */

#ifndef GU_CA_PLUGIN_POF_CPOFMODEL_H
#include "guCApluginPOF_CPOFModel.h"
#define GU_CA_PLUGIN_POF_CPOFMODEL_H
#endif /* GU_CA_PLUGIN_POF_CPOFMODEL_H ? */

namespace Ogre { class ManualObject; }

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CA {
namespace PLUGINPOF {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class CPOFModel;

/*--------------------------------------------------------------------------*/

class GU_CA_PLUGIN_POF_EXPORT_CPP CPOFMeshCodec : public GUCE::CORE::CIMeshCodec
{
    public:
    
    CPOFMeshCodec( void );
    
    virtual ~CPOFMeshCodec();
    
    Ogre::MeshPtr DecodePOFModel( const CString& meshName     ,
                                  const CPOFModel& data       ,
                                  const CString& selectedMesh );
    
    Ogre::MeshPtr DecodePOFMesh( const CString& meshName   ,
                                 const CPOFModel& data     ,
                                 const UInt32 selectedMesh ) const;

    void DecodePOFModel( const CString& meshNamePrefix ,
                         const CPOFModel& data         ,
                         TMeshMap& meshMap             ) const;

    virtual Ogre::MeshPtr Decode( const CString& meshName      ,
                                  GUCEF::CORE::CIOAccess& data ,
                                  const CString& selectedMesh  );
    
    virtual void Decode( const CString& meshNamePrefix ,
                         GUCEF::CORE::CIOAccess& data  ,
                         TMeshMap& meshMap             );
                         
    virtual CString GetType( void ) const;
    
    private:
    
    CPOFMeshCodec( const CPOFMeshCodec& src );
    CPOFMeshCodec& operator=( const CPOFMeshCodec& other );
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace PLUGINPOF */
}; /* namespace CA */
}; /* namespace GU */

/*--------------------------------------------------------------------------*/

#endif /* GU_CA_PLUGIN_POF_CPOFMESHCODEC_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 04-05-2005 :
        - Dinand: Initial version.

-----------------------------------------------------------------------------*/
