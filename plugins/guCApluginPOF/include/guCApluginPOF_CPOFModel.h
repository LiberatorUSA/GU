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

#ifndef GU_CA_PLUGIN_POF_CPOFMODEL_H
#define GU_CA_PLUGIN_POF_CPOFMODEL_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GU_CA_PLUGIN_POF_MACROS_H
#include "guCApluginPOF_macros.h"
#define GU_CA_PLUGIN_POF_MACROS_H
#endif /* GU_CA_PLUGIN_POF_MACROS_H ? */

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
//      TYPES                                                              //
//                                                                         //
//-------------------------------------------------------------------------*/

struct SPOFInt3
{
    Int32 a;
    Int32 b;
    Int32 c;
};

typedef struct SPOFInt3 TPOFInt3;

/*--------------------------------------------------------------------------*/

/*
 *      a vector
 */
struct SPOFVector
{
    Float32 x;
    Float32 y;
    Float32 z;
};

typedef struct SPOFVector TPOFVector;

/*--------------------------------------------------------------------------*/

/*
 *      Stores a vertex's x, y and z plus it's normals
 */
struct SPOFVertex
{
    TPOFVector vertex_data; // Each vertex n is a point followed by norm_counts[n] normals.
    TPOFVector *vertex_normals;
};

typedef struct SPOFVertex TPOFVertex;

/*--------------------------------------------------------------------------*/

/*
 *      a nontextured polygon
 */
struct SPOFFlatPoly
{
    TPOFVector normal;
    TPOFVector center;
    float radius;
    Int32 nverts;
    Int16 red;
    Int16 green;
    Int16 blue;
    Int8 pad; // I assume this is padding...
    Int16 *vertnum;
    Int16 *normnum;
};

typedef struct SPOFFlatPoly TPOFFlatPoly;

/*--------------------------------------------------------------------------*/

/*
 *      a textured polygon of a POF model
 */
struct SPOFMapPoly
{
        TPOFVector normal;
        TPOFVector center;
        float radius;
        Int32 nverts;
        Int32 tmap_num; // the texture for this poly
        Int16 *vertnum;
        Int16 *normnum;
        float *u;
        float *v;
};

typedef struct SPOFMapPoly TPOFMapPoly;

/*--------------------------------------------------------------------------*/

/*
 *      Bounding box of the POF model
 */
struct SPOFBoundBox
{
    TPOFVector min_point;
    TPOFVector max_point;
};

typedef struct SPOFBoundBox TPOFBoundBox;

/*--------------------------------------------------------------------------*/

/**
 *	Sort normals, this is the stored data in the POF which allows us to
 *	rebuild the precompiled BSP tree.
 *	Sortnorms are planes that split the model recursively.
 */
struct STPOFSortNormals
{
    TPOFVector plane_normal;           /* Normal of the splitting plane */
    TPOFVector plane_point;            /* point in our splitting plane */
    UInt32 reserved;                   /* set to 0 */
    UInt32 front_offset;               /* Only recurse into this if non-zero. */
    UInt32 back_offset;                /* Only recurse into this if non-zero. */
    UInt32 prelist_offset;             /* Only recurse into this if non-zero. */
    UInt32 postlist_offset;            /* Only recurse into this if non-zero. */
    UInt32 online_offset;              /* Only recurse into this if non-zero. */
    TPOFVector min_bounding_box_point; /* of all polys under here */
    TPOFVector max_bounding_box_point; /* of all polys under here */
};

typedef struct STPOFSortNormals TPOFSortNormals;

/*--------------------------------------------------------------------------*/

/**
 *   mesh data for a subobject
 */
struct SPOFMeshBSPData
{
    Int32 n_verts;
    Int32 n_norms;
    Int32 offset;      // from start of chunk to vertex data
    Int8 *norm_counts;

    TPOFVertex* vertexes;
    TPOFFlatPoly *flatpolys;
    TPOFMapPoly *tmappolys;
    TPOFBoundBox *boundboxes;
    TPOFSortNormals *sortnorms;
    Int32 n_tmap,n_fply,n_bbox;
};

typedef struct SPOFMeshBSPData TPOFMeshBSPData;

/*--------------------------------------------------------------------------*/

/**
 *   subobject meshes information
 */
struct SPOFMesh
{
    Int32 submodel_number;    // What submodel number this is.

    float radius;             // radius of this subobject
    Int32 submodel_parent;    // What submodel is this model's parent. Equal to -1 if none.
    Int32 num_children;       // the number of children.
    Int32 *submodel_children; // what submodels are childs to this object.
    TPOFVector offset;        // Offset to from parent object

    TPOFVector geometric_center;
    TPOFVector bounding_box_min_point;
    TPOFVector bounding_box_max_point;

    CString submodel_name;
    CString properites;
    Int32 movement_type;
    Int32 movement_axis;

    Int32 reserved;           // must be 0
    Int32 bsp_data_size;      // number of bytes now following
    Int32 bsp_start_location; // the offset into the file for the bsp data.
    TPOFMeshBSPData bsp_data; // contains actual polygons, etc.
    Int32 meshListNo;
};

typedef struct SPOFMesh TPOFMesh;

/*--------------------------------------------------------------------------*/

/*
 *  shield mesh stuff
 */
struct SPOFShield
{
    UInt32 num_vertices;
    TPOFVector *position;

    UInt32 num_faces;
    TPOFVector *face_normal;
    TPOFInt3 *face_vertices;
    TPOFInt3 *neighbours;
    Int32 shieldListNo;
};

typedef struct SPOFShield TPOFShield;

/*--------------------------------------------------------------------------*/

/*
 *  POF Header data
 */
struct SPOFHData
{
    Int32 version;            // version of POF model format that was loaded
    float max_radius;         // maximum radius of entire ship
    Int32 obj_flags;          // object flags. Bit 1 = Textures contain tiling
    Int32 num_subobjects;     // number of subobjects
    TPOFVector min_bounding;  // min bounding box point
    TPOFVector max_bounding;  // max bounding box point

    Int32 num_detaillevels;   // number of detail levels
    Int32 *sobj_detaillevels; // subobject number for detail level I, 0 being highest.

    Int32 num_debris;         // number of debris pieces that model explodes into
    Int32 *sobj_debris;       // subobject number for debris piece x

    float mass;
    TPOFVector mass_center;    // center of mass
    float moment_inertia[3][3];// moment of inertia

    Int32 num_cross_sections; // number of cross sections (used for exploding ship)  if there is no cross_section data, num_cross_sections is -1 instead of 0, as one would expect.
    float *depth;
    float *radius;

    Int32 num_lights;         // number of precalculated muzzle flash lights
    TPOFVector *location;
    Int32 *light_type;        // type of light
};

typedef struct SPOFHData TPOFHData;

/*--------------------------------------------------------------------------*/

/*
 *  Texture data
 */
struct SPOFTexData
{
    Int8 ignoreTxt;
    Int8 numtex;              /* number of textures this model has */
    CString *textures;        /* filename strings of images used for textures */
    UInt32 *texnames;         /* OpenGL texnames */

    Int32 textoffset;         // the number of textures to skip for this object
    TPOFShield shield;
    TPOFMesh *meshes;
};

typedef struct SPOFTexData TPOFTexData;

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *  This is a class for loading and rendering a POF format model.
 *  the POF format was designed by Violalion for the Decent and Freespace series.
 *  POF is a format meant for spacecraft models. POF mesh data is stored as
 *  a Leaf based BSP tree.
 */
class GU_CA_PLUGIN_POF_EXPORT_CPP CPOFModel
{
    public :

    CPOFModel( void );

    ~CPOFModel();

    const TPOFHData& GetHeaderData( void ) const;
    
    const TPOFTexData& GetData( void ) const;

    bool LoadModel( GUCEF::CORE::CIOAccess& file ); 
        
    private:
    
    CPOFModel( const CPOFModel& src );
    CPOFModel& operator=( const CPOFModel& src );
    
    bool LoadHeaderData( GUCEF::CORE::CIOAccess& file );
    
    bool LoadAllMeshData( GUCEF::CORE::CIOAccess& file );    

    bool LoadMesh( GUCEF::CORE::CIOAccess& file ,
                   Int32 datasize               ,
                   Int32 startoffset            ,
                   Int32 obj                    );
    
    void ReadVector( GUCEF::CORE::CIOAccess& file ,
                     TPOFVector& pofVector        ) const;

    CString ReadString( GUCEF::CORE::CIOAccess& file ) const;
    
    void ZeroMeshStruct( TPOFMesh& mesh );
    
    void ZeroVectorStruct( TPOFVector& vector );
    
    void ZeroMeshBSPDataStruct( TPOFMeshBSPData& bspData );
    
    private:
    
    TPOFHData m_header;
    TPOFTexData m_data;
    bool m_headerLoaded;        
};

/*-------------------------------------------------------------------------*/

#endif /* GU_CA_PLUGIN_POF_CPOF_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace PLUGINPOF */
}; /* namespace CA */
}; /* namespace GU */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 24-7-2003 :
       - Renamed TPOFTexData variable to data from texdata since this is more
         accurate.
       - This loader is now part of the GUCE library.
       - Moved all types to cpp file and made forward declarations for structs.
         In order to do this i had to change the main data structs into pointers
         to these structs and thus change the refrencing everywhere internally.
         Since there where so many types this really cleans up the header.
- 23-7-2003 :
        - Wanted to have some fun with good old freespace 2 models so i continued
          working on this loader. I fixed a number of bugs:
            - Version number now gets read correctly.
            - TPOFVector's now get read correctly.
            - Fixed subobject loader by first reading a 4 byte garbage field.
            - Mesh loading of normals was being done by reading a 1 byte value
              into a 4 byte variable. Since the variable was not initialized we
              ended up with garbage. This is now fixed.
        - Added lots of comment in the loader code from information i found
          on the decent network website.
        - Changed some Int8* to char*
        - Temporaraly removed all ancestors since the code it was inheriting
          from no longer gets used.
        - Updated Load_Textures() for use with the latest CEngineCore class.
- 24-1-2003 :
        - Note to self : this model loader uses new and delete for memory
          management not malloc and free !!!
        - The POF models used by Violation do not store the texture file's
          extension. We will compansate by appending .pcx in Load_Textures()
          if no extension is found. I chose pcx because that's what all the old
          models used as texture.
- 22-1-2003 :
        - Obtained code on which i based this class from the Freespace 2
          source code that was released.
        - Grouped everything into structs because there is a wopping amount
          of information stored in a POF


//---------------------------------------------------------------------------*/