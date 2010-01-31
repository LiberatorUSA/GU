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

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef __MATERIALMANAGER_H__
#include "OgreMaterialManager.h"
#define __MATERIALMANAGER_H__
#endif /* __MATERIALMANAGER_H__ ? */

#ifndef _Material_H__
#include "OgreMaterial.h"
#define _Material_H__
#endif /* _Material_H__ ? */

#ifndef __OgreManualObject_H__
#include "OgreManualObject.h"
#define __OgreManualObject_H__
#endif /* __OgreManualObject_H__ ? */

#ifndef __MeshManager_H__
#include "OgreMeshManager.h"
#define __MeshManager_H__
#endif /* __MeshManager_H__ ? */

#ifndef GUCE_CORE_CGUCEAPPLICATION_H
#include "CGUCEApplication.h"
#define GUCE_CORE_CGUCEAPPLICATION_H
#endif /* GUCE_CORE_CGUCEAPPLICATION_H ? */

#ifndef GUCEF_CORE_DVMD5UTILS_H
#include "dvmd5utils.h"
#define GUCEF_CORE_DVMD5UTILS_H
#endif /* GUCEF_CORE_DVMD5UTILS_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFER_H
#include "CDynamicBuffer.h"
#define GUCEF_CORE_CDYNAMICBUFFER_H
#endif /* GUCEF_CORE_CDYNAMICBUFFER_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFERACCESS_H
#include "CDynamicBufferAccess.h"
#define GUCEF_CORE_CDYNAMICBUFFERACCESS_H
#endif /* GUCEF_CORE_CDYNAMICBUFFERACCESS_H ? */

#ifndef GUCEF_CORE_CSUBFILEACCESS_H
#include "gucefCORE_CSubFileAccess.h"
#define GUCEF_CORE_CSUBFILEACCESS_H
#endif /* GUCEF_CORE_CSUBFILEACCESS_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#include "guCApluginPOF_CPOFMeshCodec.h"

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
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CPOFMeshCodec::CPOFMeshCodec( void )
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/
    
CPOFMeshCodec::~CPOFMeshCodec()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

Ogre::MeshPtr
CPOFMeshCodec::DecodePOFMesh( const CString& meshName   ,
                              const CPOFModel& data     ,
                              const UInt32 selectedMesh ) const
{GU_TRACE;

    const TPOFTexData& modelData = data.GetData();
    const TPOFMesh& mesh = modelData.meshes[ selectedMesh ];
    const TPOFMeshBSPData& bspData = mesh.bsp_data;
    
    Ogre::ManualObject object( meshName );
    
    Int32 i,j;
    
    // Render all the textured polygons
    if( mesh.bsp_data.n_tmap > 0 )
    {          
        Int32 previousTexture = -1;
        for( i=0; i<mesh.bsp_data.n_tmap; ++i )
        {
	        const TPOFMapPoly& poly = mesh.bsp_data.tmappolys[ i ];
	        Int32 textureIndex = poly.tmap_num;
	        if( ( textureIndex + modelData.textoffset ) != modelData.ignoreTxt )
            {
                /*
                 *      if this polygon doesn't have the
                 *      invisible texture on it
                 *      ( see below where the TXTR header is
                 *      parsed )
                 *      we can display it, otherwise we wont
                 *      display it, thus making it invisible.
                 */ 
                if ( previousTexture != textureIndex )
                {
                    object.begin( modelData.textures[ textureIndex ], Ogre::RenderOperation::OT_TRIANGLE_STRIP );
                } 

                // Set the normal for this face
                object.normal( poly.normal.x ,
                               poly.normal.y ,
                               poly.normal.z );

                // set all the verteces for this polygon (most likely 3 which is a triangle)
                for( j=0; j<poly.nverts; ++j )
                {			 
                    Int32 index = poly.vertnum[ j ];
                    object.textureCoord( poly.u[ j ] ,
                                         poly.v[ j ] );

                    object.position( mesh.bsp_data.vertexes[ index ].vertex_data.x ,
                                     mesh.bsp_data.vertexes[ index ].vertex_data.y ,
                                     mesh.bsp_data.vertexes[ index ].vertex_data.z );
                                     
                    object.index( index );
		        }
		        
		        // Check if we reached the end
		        if ( i+1 < mesh.bsp_data.n_tmap )
		        {
		            // Check if the next texture is a different texture
		            Int32 nextTexture = mesh.bsp_data.tmappolys[ i+1 ].tmap_num;
		            if ( nextTexture + modelData.textoffset != modelData.ignoreTxt )
		            {
		                if ( textureIndex != nextTexture )
		                {
		                    // End of the segment with the same material so call end()
		                    object.end();
		                }
                    }
		        }
		        else
		        {
		            object.end();
		        }
		        previousTexture = textureIndex;
	        }
        }
    }

    // render all the non-textured polygons
    CString nonTexturedMaterial = "noTexture";
    if( mesh.bsp_data.n_fply > 0 )
    {
        object.begin( nonTexturedMaterial, Ogre::RenderOperation::OT_TRIANGLE_STRIP );
        
        for( i=0; i<mesh.bsp_data.n_fply; ++i )
        {                       
            const TPOFFlatPoly& poly = mesh.bsp_data.flatpolys[ i ];
            object.normal( poly.normal.x ,
                           poly.normal.y ,
                           poly.normal.z );

            for( j=0; j<mesh.bsp_data.flatpolys[ i ].nverts; ++j )
            {
                Int32 index = mesh.bsp_data.flatpolys[ i ].vertnum[ j ];

                // set the colour to the flatpoly's colour.
                object.colour( poly.red   ,
                               poly.green ,
                               poly.blue  );	  

                object.position( mesh.bsp_data.vertexes[ index ].vertex_data.x ,
                                 mesh.bsp_data.vertexes[ index ].vertex_data.y ,
                                 mesh.bsp_data.vertexes[ index ].vertex_data.z );
                                 
                object.index( index );
            }
            
        }
        
        object.end();
    }
    
    // Now we convert the data into a mesh    
    Ogre::MeshPtr meshPtr;
    try
    {
        meshPtr = object.convertToMesh( meshName ); 
    }
    catch ( Ogre::Exception& e )
    {
        GUCEF_DEBUG_LOG( 0, "CPOFMeshCodec: Ogre exception while converting the Ogre object data to a mesh: " + e.getFullDescription() );
    }
    return meshPtr;
}

/*-------------------------------------------------------------------------*/
    
Ogre::MeshPtr
CPOFMeshCodec::DecodePOFModel( const CString& meshName     ,
                               const CPOFModel& data       ,
                               const CString& selectedMesh )
{GU_TRACE;

    const TPOFHData& headerData = data.GetHeaderData();
    
    Int32 rootMesh = GUCEF::CORE::StringToUInt32( selectedMesh );
    if ( rootMesh < headerData.num_subobjects )
    {
        return DecodePOFMesh( meshName     ,
                              data         ,
                              rootMesh     );
    }
    
    // No such mesh
    GUCEF_DEBUG_LOG( 0, "CPOFMeshCodec: Decode of POF mesh " + selectedMesh + " failed because no such mesh can be found" );
    return Ogre::MeshPtr();
}

/*-------------------------------------------------------------------------*/
    
Ogre::MeshPtr
CPOFMeshCodec::Decode( const CString& meshName      ,
                       GUCEF::CORE::CIOAccess& data ,
                       const CString& selectedMesh  )
{GU_TRACE;

    CPOFModel pofModel;
    if ( pofModel.LoadModel( data ) )
    {
        return DecodePOFModel( meshName     ,
                               pofModel     ,
                               selectedMesh );
    }
    
    GUCEF_DEBUG_LOG( 0, "CPOFMeshCodec: Decode failed because of failure to load data from POF file" );
    return Ogre::MeshPtr();
}

/*-------------------------------------------------------------------------*/

CString
CPOFMeshCodec::GetType( void ) const
{GU_TRACE;

    return "pof";
}

/*-------------------------------------------------------------------------*/

void
CPOFMeshCodec::DecodePOFModel( const CString& meshNamePrefix ,
                               const CPOFModel& data         ,
                               TMeshMap& meshMap             ) const
{GU_TRACE;

    const TPOFTexData& modelData = data.GetData();
    const TPOFHData& headerData = data.GetHeaderData();
    
    for ( Int32 i=0; i<headerData.num_subobjects; ++i )
    {
        const TPOFMesh& mesh = modelData.meshes[ i ];
        if ( mesh.submodel_parent == -1 )
        {
            CString completeMeshName = meshNamePrefix + "(" + GUCEF::CORE::Int32ToString( i ) + ")";
            Ogre::MeshPtr meshPtr = DecodePOFMesh( completeMeshName ,
                                                   data             ,
                                                   i                );
                                                   
            if ( !meshPtr.isNull() )
            {
                GUCEF_DEBUG_LOG( 0, "CPOFMeshCodec: loaded selected mesh from POF file with name " + completeMeshName );
                meshMap[ completeMeshName ] = meshPtr;
            }
            else
            {
                GUCEF_DEBUG_LOG( 0, "CPOFMeshCodec: Decode failed of selected mesh from POF file with name " + completeMeshName );
            }
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CPOFMeshCodec::Decode( const CString& meshNamePrefix ,
                       GUCEF::CORE::CIOAccess& data  ,
                       TMeshMap& meshMap             )
{GU_TRACE;
    
    data.Open();
    
    CPOFModel pofModel;
    if ( pofModel.LoadModel( data ) )
    {
        DecodePOFModel( meshNamePrefix ,
                        pofModel       ,
                        meshMap        );
        return;
    }
    
    GUCEF_DEBUG_LOG( 0, "CPOFMeshCodec: Decode failed because of failure to load data from POF file" );   
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace PLUGINPOF */
}; /* namespace CA */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
