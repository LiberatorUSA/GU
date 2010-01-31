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

//-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------//

#ifndef GUCEF_CORE_CIOACCESS_H
#include "CIOAccess.h"
#define GUCEF_CORE_CIOACCESS_H
#endif /* GUCEF_CORE_CIOACCESS_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#include "guCApluginPOF_CPOFModel.h"

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

CPOFModel::CPOFModel( void )
    : m_header()              ,
      m_data()                ,
      m_headerLoaded( false )
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CPOFModel::~CPOFModel()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

//void
//CPOFModel::Load_Textures( void )
//{GU_TRACE;
//        /*
//         *      Load all textures trough the texture manager
//         */
//        char *tmp;
//        const TTexdata* texptr = NULL;
//        for( Int32 i=0; i<data->numtex; i++ )
//        {
//                tmp = Extract_File_Ext( data->textures[ i ] );
//                if ( !tmp || !strcmp( tmp, "" ) )
//                {
//                	/*
//                         *	No extension so we add one ourselfs
//                         */
//                        char *new_tname = new char[ strlen( data->textures[ i ] )+5 ];
//                        strcpy( new_tname, data->textures[ i ] );
//                        strcat( new_tname, ".pcx" );
//                        new_tname[ strlen( data->textures[ i ] )+4 ] = '\0';
//                        delete []data->textures[ i ];
//                        data->textures[ i ] = new_tname;
//                }
//                free( tmp );
//
//                if ( strcmp( data->textures[ i ], "invisible" ) )
//                {
//                	texptr = e->textures.Get_Texture( data->textures[ i ], GL_TEXTURE_2D, GL_RGB, NULL );
//                        if ( texptr )
//                        {
//                        	data->texnames[ i ] = texptr->texname;
//                        }
//                        else
//                        {
//                        	tsprintf( "CPOF: Cannot obtain texture %s\n", data->textures[ i ] );
//                        }
//                }
//        }
//}

//---------------------------------------------------------------------------

//void
//CPOFModel::Render_Cube( TPOFVector *minimal, TPOFVector *maximum )
//{
//        /*
//         *      Render cube for minimal and maximum given
//         */
//        glBegin( GL_LINES );
//         // TODO : make this
//        glEnd();
//}
//
////---------------------------------------------------------------------------
//
//char*
//CPOFModel::DARead_String( FILE* fptr )
//{
//        /*
//         *      Read a string from file and dynamicly allocate the needed
//         *      space
//         */
//        Int32 strlength;
//        fread( &strlength, 4, 1, fptr );
//        char *buf = new char[ strlength+1 ];
//        buf[ strlength ] = 0;
//        fread( buf, strlength, 1, fptr );
//        return ( buf );
//}

//---------------------------------------------------------------------------

CString
CPOFModel::ReadString( GUCEF::CORE::CIOAccess& file ) const
{GU_TRACE;

    /*
     *      Read a string from file and dynamicly allocate the needed
     *      space
     */
    Int32 strLength;
    file.Read( &strLength, 4, 1 );
    if ( strLength > 0 )
    {
        char* strBuffer = new char[ strLength ];
        file.Read( strBuffer, strLength, 1 );
        CString theString( strBuffer, strLength );
        delete []strBuffer;
        return theString;
    }
    return CString();
}

////---------------------------------------------------------------------------
//
//GLint
//CPOFModel::Make_Shield_DList( void )
//{
//        /*
//         *      Make a display list from the ship's shield
//         */
//        UInt32 i;
//        Int32 mcount=0;
//        Int32 mindex=0;
//
//        /*
//         *      Create display list
//         */
//        GLint lid=glGenLists(1);
//        glNewList( lid, GL_COMPILE );
//
//        /*
//         *      Provide verteces for shield.
//         *      We use triangles
//         */
//        glBegin( GL_TRIANGLES );
//        for( i=0; i< data->shield.num_faces; i++ )
//        {
//                glNormal3f( data->shield.face_normal[ i ].x,
//                            data->shield.face_normal[ i ].y,
//                            data->shield.face_normal[ i ].z );
//                glVertex3f( data->shield.position[ data->shield.face_vertices[ i ].a ].x,
//                            data->shield.position[ data->shield.face_vertices[ i ].a ].y,
//                            data->shield.position[ data->shield.face_vertices[ i ].a ].z );
//                glVertex3f( data->shield.position[ data->shield.face_vertices[ i ].b ].x,
//                            data->shield.position[ data->shield.face_vertices[ i ].b ].y,
//                            data->shield.position[ data->shield.face_vertices[ i ].b ].z );
//                glVertex3f( data->shield.position[ data->shield.face_vertices[ i ].c ].x,
//                            data->shield.position[ data->shield.face_vertices[ i ].c ].y,
//                            data->shield.position[ data->shield.face_vertices[ i ].c ].z );
//        }
//        glEnd();
//
//        /*
//         *      Finish up list and return it's ID
//         */
//        glEndList();
//        return lid;
//}
//
////---------------------------------------------------------------------------
//
//void
//CPOFModel::Load_Mesh( FILE *fptr, Int32 datasize, Int32 startoffset, Int32 obj )
//{
//}

//---------------------------------------------------------------------------

bool
CPOFModel::LoadMesh( GUCEF::CORE::CIOAccess& file ,
                     Int32 datasize               ,
                     Int32 startoffset            ,
                     Int32 obj                    )
{GU_TRACE;
    
    /*
     *	DECENT Network description:
     *	The BSP data in FreeSpace in kinda similar to the Descent 1-3
     *	BSP data (also called IDTA). Many deja-vu's here and there :).
     *	In FreeSpace the BSP data is located in the POF files.
     */
    Int32 initPos = startoffset;

    // Move to start of mesh
    file.Seek( startoffset, SEEK_SET );

    Int32 type=1, size, flatno=0, tmapno=0, bboxno=0, sortno=0;
    
    // since I don't know how many polygons there are, I'll set it to 4096, if I find the BIG ships need more, I'll raise it.
    m_data.meshes[ obj ].bsp_data.flatpolys = new TPOFFlatPoly[ 1000 ];
    m_data.meshes[ obj ].bsp_data.tmappolys = new TPOFMapPoly[ 4096 ]; // these are the most used, so I'll make it big.
    m_data.meshes[ obj ].bsp_data.boundboxes = new TPOFBoundBox[ 1000 ];
    m_data.meshes[ obj ].bsp_data.sortnorms = new TPOFSortNormals[ 1000 ];

    while( file.Tell() < ( unsigned )initPos+datasize )
    {
        file.Read( &type, 4, 1 );
        Int32 start = file.Tell()-4; /* used to skip the offset in type 1 */
        file.Read( &size, 4, 1 );
        
        switch( type )
        {
            case 0:
            {
                /*
                 *	This is just an indicator marker and has
                 *	no data fields
                 *
                 *	DECENT Network description:
                 *	EOF - Means end of tree reached
                 *	+ 0 int id = 0
                 *	+ 4 int size
                 */
                break;
            }
            case 1:
            {
                /*
                 *      load all the vertexes
                 *
                 *	DECENT Network description:
                 *      DEFPOINTS - Defines the vertices
                 *       + 0 int id = 1
                 *       + 4 int size
                 *       + 8 int n_verts
                 *       +12 int n_norms
                 *       +16 int offset -> from start of chunk to vertex data
                 *       +20 n_verts*char norm_counts
                 *       +offset vertex_data -> Each vertex n is a point followed by norm_counts[n] normals.
                 */
                file.Read( &m_data.meshes[ obj ].bsp_data.n_verts, 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.n_norms, 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.offset, 4, 1 );

                m_data.meshes[ obj ].bsp_data.norm_counts = new Int8[ m_data.meshes[ obj ].bsp_data.n_verts+1 ];
                for( Int32 i=0; i< m_data.meshes[ obj ].bsp_data.n_verts; ++i )
                {
                    file.Read( &m_data.meshes[ obj ].bsp_data.norm_counts[ i ], 1, 1 );
                }

                file.Seek( start+m_data.meshes[ obj ].bsp_data.offset, SEEK_SET );
                m_data.meshes[ obj ].bsp_data.vertexes = new TPOFVertex[ m_data.meshes[ obj ].bsp_data.n_verts+1 ];

                for( Int16 i=0; i<m_data.meshes[ obj ].bsp_data.n_verts; ++i )
                {
                    m_data.meshes[ obj ].bsp_data.vertexes[ i ].vertex_normals = new TPOFVector[ m_data.meshes[ obj ].bsp_data.n_norms ];
                    ReadVector( file, m_data.meshes[ obj ].bsp_data.vertexes[ i ].vertex_data );

                    for( Int16 j=0; j<m_data.meshes[ obj ].bsp_data.norm_counts[ i ]; ++j )
                    {
                        ReadVector( file, m_data.meshes[ obj ].bsp_data.vertexes[ i ].vertex_normals[ j ] );
                    }
                }
                break;
            }
            case 2:
            {
                /*
                 *      a flat (nontextured) polygon
                 *
                 *	DECENT Network description:
                 *      FLATPOLY - Flat (non-textured) polygon
                 *       + 0 int id = 2
                 *       + 4 int size
                 *       + 8 vector normal
                 *       +20 vector center
                 *       +32 float radius
                 *       +36 int nverts
                 *       +40 byte red
                 *       +41 byte green
                 *       +42 byte blue
                 *       +43 byte pad
                 *       for each vertex, i {
                 *        short vertnum[i]
                 *        short normnum[i]
                 *       }
                 *
                 */
                ReadVector( file, m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].normal );
                ReadVector( file, m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].center );
                file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].radius, 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].nverts, 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].red, 1, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].green, 1, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].blue, 1, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].pad, 1, 1 );
                m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].vertnum = new short[ m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].nverts ];
                m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].normnum = new short[ m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].nverts ];

                for( Int32 i=0; i<m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].nverts; i++ )
                {
                    file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].vertnum[ i ], 2, 1 );
                    file.Read( &m_data.meshes[ obj ].bsp_data.flatpolys[ flatno ].normnum[ i ], 2, 1 );
                }
                flatno++;
                break;
            }
            case 3:
            {
                /*
                 *      a textured polygon
                 *
                 *	DECENT Network description:
                 *       TMAPPOLY - Textured polygons
                 *       + 0 int id = 3
                 *       + 4 int size
                 *       + 8 vector normal
                 *       +20 vector center
                 *       +32 float radius
                 *       +36 int nverts
                 *       +40 int tmap_num
                 *       for each vertex, i {
                 *        short vertnum[i]
                 *        short normnum[i]
                 *        float u[i]
                 *        float v[i]
                 *       }
                 */
                ReadVector( file, m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].normal );
                ReadVector( file, m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].center );
                file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].radius, 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].nverts, 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].tmap_num, 4, 1 );

                m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].vertnum = new Int16[ m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].nverts ];
                m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].normnum = new Int16[ m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].nverts ];
                m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].u = new Float32[ m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].nverts ];
                m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].v = new Float32[ m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].nverts ];

                for( Int32 i=0; i<m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].nverts; ++i )
                {
                    file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].vertnum[ i ], 2, 1 );
                    file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].normnum[ i ], 2, 1 );
                    file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].u[ i ], 4, 1 );
                    file.Read( &m_data.meshes[ obj ].bsp_data.tmappolys[ tmapno ].v[ i ], 4, 1 );
                }
                ++tmapno;
                break;
            }
            case 4:
            {
                /*
                 *	Sort normals, used to split the data
                 *      recursively which is the essance of the
                 *	BSP tree.
                 *
                 *	DECENT Network description:
                 *       SORTNORM - Sortnorms are planes that split the model recursively
                 *       + 0 int id = 4
                 *       + 4 int size
                 *       + 8 vector plane_normal
                 *       +20 vector plane_point
                 *       +32 int reserved -> set to 0
                 *       +36 int front_offset -> Only recurse into this if non-zero.
                 *       +40 int back_offset -> Only recurse into this if non-zero.
                 *       +44 int prelist_offset -> Only recurse into this if non-zero.
                 *       +48 int postlist_offset -> Only recurse into this if non-zero.
                 *       +52 int online_offset -> Only recurse into this if non-zero.
                 *       +56 vector min_bounding_box_point -> of all polys under here
                 *       +68 vector max_bounding_box_point -> of all polys under here
                 */
                ReadVector( file, m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].plane_normal );
                ReadVector( file, m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].plane_point );
                file.Read( &m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].reserved , 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].front_offset , 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].back_offset , 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].prelist_offset , 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].postlist_offset , 4, 1 );
                file.Read( &m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].online_offset , 4, 1 );
                ReadVector( file, m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].min_bounding_box_point );
                ReadVector( file, m_data.meshes[ obj ].bsp_data.sortnorms[ sortno ].max_bounding_box_point );
                break;
            }
            case 5:
            {
                /*
                 *      a bounding box
                 *
                 *	DECENT Network description:
                 *       BOUNDBOX - Bounding boxes are used to speed up lighting and collision calculations.
                 *       + 0 int id = 5
                 *       + 4 int size
                 *       + 8 vector min_point
                 *       +20 vector max_point
                 */
                ReadVector( file, m_data.meshes[ obj ].bsp_data.boundboxes[ bboxno ].min_point );
                ReadVector( file, m_data.meshes[ obj ].bsp_data.boundboxes[ bboxno ].max_point );
                bboxno++;
                break;
            }
            default :
            {
                GUCEF_DEBUG_LOG( 0, "Invalid POF Mesh field encountered" );
                break;
            }
        }
    }
    m_data.meshes[ obj ].bsp_data.n_fply = flatno;
    m_data.meshes[ obj ].bsp_data.n_tmap = tmapno;
    m_data.meshes[ obj ].bsp_data.n_bbox = bboxno;

    return true;
}

//---------------------------------------------------------------------------

//GLint
//CPOFModel::Make_Mesh_DList( int obj )
//{
//        /*
//         *      Turn mesh verteces data into a display list for the specified
//         *      object
//         */
//        Int32 i,j;
//
//        GLint lid=glGenLists( 1 );
//        if( data->meshes[ obj ].bsp_data.n_tmap > 0 )
//        {
//                glNewList( lid, GL_COMPILE );           
//                for( i=0; i<data->meshes[ obj ].bsp_data.n_tmap; i++ )
//                {
//                        switch( data->meshes[ obj ].bsp_data.tmappolys[ i ].nverts )
//                        {
//                                case 3:{ glBegin( GL_TRIANGLES ); break;}
//                                case 4:{ glBegin( GL_QUADS ); break;}
//                                default:{ glBegin( GL_POLYGON ); break;}
//                        }
//
//		        if( ( data->meshes[ obj ].bsp_data.tmappolys[ i ].tmap_num + data->textoffset ) != data->ignoreTxt )
//                        {
//                                /*
//                                 *      if this polygon doesn't have the
//                                 *      invisible texture on it
//                                 *      ( see below where the TXTR header is
//                                 *      parsed )
//                                 *      we can display it, otherwise we wont
//                                 *      display it, thus making it invisible.
//                                 */
//			        glBindTexture( GL_TEXTURE_2D,
//                                               data->texnames[ data->meshes[ obj ].bsp_data.tmappolys[ i ].tmap_num ] );
//                                glNormal3f( data->meshes[ obj ].bsp_data.tmappolys[ i ].normal.x,
//                                            data->meshes[ obj ].bsp_data.tmappolys[ i ].normal.y,
//                                            data->meshes[ obj ].bsp_data.tmappolys[ i ].normal.z );
//
//                                for( j=0; j<data->meshes[ obj ].bsp_data.tmappolys[ i ].nverts; j++ )
//                                {			 
//                                        Int32 index = data->meshes[ obj ].bsp_data.tmappolys[ i ].vertnum[ j ];
//                                        glTexCoord2f( data->meshes[ obj ].bsp_data.tmappolys[ i ].u[ j ],
//                                                      data->meshes[ obj ].bsp_data.tmappolys[ i ].v[ j ] );
//                                        glVertex3f( data->meshes[ obj ].bsp_data.vertexes[ index ].vertex_data.x,
//                                                    data->meshes[ obj ].bsp_data.vertexes[ index ].vertex_data.y,
//                                                    data->meshes[ obj ].bsp_data.vertexes[ index ].vertex_data.z );
//			        }
//		        }
//                glEnd ();
//                }
//        glEndList();
//        }
//
//        /*
//         *      draw a nontextured poly
//         */
//        if( data->meshes[ obj ].bsp_data.n_fply > 0 )
//        {
//                glNewList( lid, GL_COMPILE );
//                for( i=0; i<data->meshes[ obj ].bsp_data.n_fply; i++ )
//                {
//                        switch( data->meshes[ obj ].bsp_data.flatpolys[ i ].nverts )
//                        {
//                                case 3:{ glBegin( GL_TRIANGLES ); break; }
//                                case 4:{ glBegin( GL_QUADS ); break; }
//                                default:{ glBegin( GL_POLYGON ); break; }
//                        }
//
//                        glNormal3f( data->meshes[ obj ].bsp_data.flatpolys[ i ].normal.x,
//                                    data->meshes[ obj ].bsp_data.flatpolys[ i ].normal.y,
//                                    data->meshes[ obj ].bsp_data.flatpolys[ i ].normal.z );
//                                    
//                        for( j=0; j<data->meshes[ obj ].bsp_data.flatpolys[ i ].nverts; j++ )
//                        {
//                                Int32 index = data->meshes[ obj ].bsp_data.flatpolys[ i ].vertnum[ j ];
//				//glColor4f(1.0, 1.0, 1.0, 1.0);
//
//				/*
//                                 *      set the colour to the flatpoly's colour.
//                                 */
//	                        glColor3s( data->meshes[ obj ].bsp_data.flatpolys[ i ].red,
//                                           data->meshes[ obj ].bsp_data.flatpolys[ i ].green,
//                                           data->meshes[ obj ].bsp_data.flatpolys[ i ].blue );	  
//
//                                glVertex3f( data->meshes[ obj ].bsp_data.vertexes[ index ].vertex_data.x,
//                                            data->meshes[ obj ].bsp_data.vertexes[ index ].vertex_data.y,
//                                            data->meshes[ obj ].bsp_data.vertexes[ index ].vertex_data.z );
//                        }
//                        glEnd ();
//                }
//                glEndList();
//        }
//        return lid;
//}
//
////---------------------------------------------------------------------------
//
//void
//CPOFModel::Make_Meshes( FILE *fptr )
//{
//
//}

//---------------------------------------------------------------------------

bool
CPOFModel::LoadAllMeshData( GUCEF::CORE::CIOAccess& file )
{GU_TRACE;

    GUCEF_DEBUG_LOG( 0, "Loading all POF mesh data" );
    
    Int32 i,j, k;
    for( i=0; i<m_header.num_subobjects; ++i )
    {
        /*
         *  if the current object isn't a child object, in other
         *	words the top most object in our object tree.
         */
        if( m_data.meshes[ i ].submodel_parent == -1 )
        {
            /*
             *  load its mesh
             */
            LoadMesh( file                                  ,
                      m_data.meshes[ i ].bsp_data_size      ,
                      m_data.meshes[ i ].bsp_start_location ,
                      i                                     );

            /*
             *  and then load the meshes for its children,
             *  if it has any (if num_children is 0, it wont loop at all)
             */
            for( j=0; j<m_data.meshes[ i ].num_children; ++j )
            {
                LoadMesh( file                                                                          ,
                          m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].bsp_data_size      ,
                          m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].bsp_start_location ,
                          m_data.meshes[ i ].submodel_children[ j ]                                     );

                /*
                 *  and on the off chance this has a child (some turrets do)
                 */
                for( k=0; k<m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].num_children; k++ )
                {
                    LoadMesh( file                                                                                                                ,
                              m_data.meshes[ m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].submodel_children[ k ] ].bsp_data_size      ,
                              m_data.meshes[ m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].submodel_children[ k ] ].bsp_start_location ,
                              m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].submodel_children[ k ]                                    );

                    m_data.meshes[ m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].submodel_children[ k ] ].meshListNo = 0; // <- OpenGL display list ID
                }
                m_data.meshes[ m_data.meshes[ i ].submodel_children[ j ] ].meshListNo = 0; // <- OpenGL display list ID
            }
            m_data.meshes[ i ].meshListNo = 0; // <- OpenGL display list ID
        }		
    }
    
    return true;
}

/*-------------------------------------------------------------------------*/

const TPOFHData&
CPOFModel::GetHeaderData( void ) const
{GU_TRACE;
    
    return m_header;
}

/*-------------------------------------------------------------------------*/

void
CPOFModel::ReadVector( GUCEF::CORE::CIOAccess& file ,
                       TPOFVector& pofVector        ) const
{GU_TRACE;

    file.Read( &pofVector.x, 4, 1 );
    file.Read( &pofVector.y, 4, 1 );
    file.Read( &pofVector.z, 4, 1 );
}

/*-------------------------------------------------------------------------*/

const TPOFTexData&
CPOFModel::GetData( void ) const
{GU_TRACE;

    return m_data;
}

/*-------------------------------------------------------------------------*/

bool
CPOFModel::LoadModel( GUCEF::CORE::CIOAccess& file )
{GU_TRACE;

    m_headerLoaded = false;
    if ( LoadHeaderData( file ) )
    {
        return LoadAllMeshData( file );
    }
    return false;
}

/*-------------------------------------------------------------------------*/

void
CPOFModel::ZeroVectorStruct( TPOFVector& vector )
{GU_TRACE;

    vector.x = 0.0f;
    vector.y = 0.0f;
    vector.z = 0.0f;
}

/*-------------------------------------------------------------------------*/

void
CPOFModel::ZeroMeshBSPDataStruct( TPOFMeshBSPData& bspData )
{GU_TRACE;

    memset( &bspData, 0, sizeof( TPOFMeshBSPData ) );
}

/*-------------------------------------------------------------------------*/

void
CPOFModel::ZeroMeshStruct( TPOFMesh& mesh )
{GU_TRACE;

    mesh.submodel_number = 0;
    mesh.radius = 0.0;
    mesh.submodel_parent = -1;        // What submodel is this model's parent. Equal to -1 if none.
    mesh.num_children = 0;            // the number of children.
    mesh.submodel_children = NULL;    // what submodels are childs to this object.
    ZeroVectorStruct( mesh.offset );  // Offset to from parent object

    ZeroVectorStruct( mesh.geometric_center );
    ZeroVectorStruct( mesh.bounding_box_min_point );
    ZeroVectorStruct( mesh.bounding_box_max_point );

    mesh.submodel_name = NULL;
    mesh.properites = NULL;
    mesh.movement_type = 0;
    mesh.movement_axis = 0;

    mesh.reserved = 0;                      // must be 0
    mesh.bsp_data_size = 0;                 // number of bytes now following
    mesh.bsp_start_location = 0;            // the offset into the file for the bsp data.
    ZeroMeshBSPDataStruct( mesh.bsp_data ); // contains actual polygons, etc.
    mesh.meshListNo = 0;
}

/*-------------------------------------------------------------------------*/

bool
CPOFModel::LoadHeaderData( GUCEF::CORE::CIOAccess& file )
{GU_TRACE;

    if ( m_headerLoaded ) return true;
    
    GUCEF_DEBUG_LOG( 0, "Loading all POF header data" );

    /*
     *      This loads all the header info from the file
     *      but don't be fooled,.. this is HUGE :)
     */
    Int32 length;
    m_data.textoffset = -1;

    /*
     *      Check first header as a POF validity check
     *      should always be "PSPO"
     *
     *	DECENT Network description:
     *	The file format is a binary file using standard Intel data types.
     *	The header consists of a signature and the file version number
     *	PSPO stood for Parallax Software Polygon Object at one time.
     *	Conflict, Descent: FreeSpace shipped at POF version 20.14,
     *	so version would be equal to 2014 in most POF files (not all).
     *	FreeSpace 2 shipped at POF version 21.17, some files are 21.16
     *
     *	The file format is a binary file using standard Intel data types.
     *	The header consists of a signature and the file version number:
     *	char[4] file_id   -> must be 'PSPO'
     *	int version       -> Major version*100+Minor version
     */
    char blockID[]={0,0,0,0,0};
    file.Setpos( 0 );
    file.Read( blockID, 4, 1 );
    if( strcmp( blockID, "PSPO" ) != 0 )
    {
        /*
         *      Invalid file
         */
        GUCEF_DEBUG_LOG( 0, "Invalid header ID found in the POF file" ); 
        return false;
    }

    /*
     *	Now we read in the POF File version
     */
    file.Read( &m_header.version, 4, 1 );
    GUCEF_DEBUG_LOG( 0, "POF file is of version: " + GUCEF::CORE::Int32ToString( m_header.version ) );

    /*
     *      Go trough each section of the POF file seperated by headers
     *      loading data as we go.
     *
     *	DECENT Network description:
     *	The rest of the file is a bunch of chunks. Each chunk is:
     *	char[4] chunk_id  -> one of the available chunk types
     *	int length        -> length of the chunk.
     */
    while( !file.Eof() )
    {
        memset( blockID, 0, 5 );
        file.Read( blockID, 1, 4 );
        GUCEF_DEBUG_LOG( 0, "POF header block found of type \"" + CString( blockID, 4 ) + "\"" );
        
        if ( ( 0 == strcmp( blockID, "HDR2" ) ) || 
             ( 0 == strcmp( blockID, "OHDR" ) )  )
        {
            /*
             *	DECENT Network description:
             *	'OHDR' (FreeSpace 1) and 'HDR2' (FreeSpace 2) -
             *	Object header info
             *
             *	Notes:
             *      -  for version<2009, mass is a volume mass
             *      -  for version>=2009, mass is an area mass
             *      -  conversion: area_mass=4.65*(vol_mass^2/3);
             *	   also scale moment_inertia by vol_mass/area_mass
             *      -  (*) if there is no cross_section data,
             *	   num_cross_sections is -1 instead of 0, as
             *	   one would expect.
             */              
            Int32 i;
            file.Read( &length, 4, 1 );
            if ( m_header.version >= 2116 )
            {
                /*
                 *	DECENT Network description:
                 *      - FreeSpace 2
                 *       float max_radius   -> maximum radius of entire ship
                 *       int obj_flags      -> object flags. Bit 1 = Textures contain tiling
                 *       int num_subobjects -> number of subobjects
                 */
                file.Read( &m_header.max_radius, 4, 1 );
                file.Read( &m_header.obj_flags, 4, 1 );
                file.Read( &m_header.num_subobjects, 4, 1 );
            }
            else
            {
                /*
                 *	DECENT Network description:
                 *	- Freespace 1
                 *       int num_subobjects  -> number of subobjects
                 *       float max_radius    -> maximum radius of entire ship
                 *       int obj_flags       -> object flags. Bit 1 = Textures contain tiling
                 */
                file.Read( &m_header.num_subobjects, 4, 1 );
                file.Read( &m_header.max_radius, 4, 1 );
                file.Read( &m_header.obj_flags, 4, 1 );
            }

            /*
             *	DECENT Network description:
             *	vector min_bounding  -> min bounding box point
             *	vector max_bounding  -> max bounding box point
             */
            ReadVector( file, m_header.min_bounding );
            ReadVector( file, m_header.max_bounding );

            /*
             *	DECENT Network description:
             *       int num_detaillevels        -> number of detail levels
             *       for each detail_level, i {
             *        int sobj_detailevels[i]    -> subobject number for detail level I, 0 being highest.
             *       }
             */
            file.Read( &m_header.num_detaillevels, 4, 1 );
            m_header.sobj_detaillevels = new Int32[ m_header.num_detaillevels ];
            for( i=0; i<m_header.num_detaillevels; i++ )
            {
                file.Read( &m_header.sobj_detaillevels[ i ], 4, 1 );
            }

            /*
             *	DECENT Network description:
             *	int num_debris -> number of debris pieces that model explodes into
             *	for each debris piece, i
             *	   int sobj_debris[i]   -> subobject number for debris piece i
             */
            file.Read( &m_header.num_debris, 4, 1 );
            m_header.sobj_debris = new Int32[ m_header.num_debris ];
            for( i=0; i<m_header.num_debris; i++ )
            {
                file.Read( &m_header.sobj_debris[ i ], 4, 1 );
            }

            /*
             *	DECENT Network description:
             *	float mass -> see notes below
             *	vector mass_center -> center of mass
             *	float[3][3] moment_inertia -> moment of inertia
             */
            if( m_header.version >= 1903 )
            {
                file.Read( &m_header.mass, 4, 1 );
                ReadVector( file, m_header.mass_center );
                for( i=0; i<3; ++i )
                {
                    for( Int32 j=0; j<3; j++ )
                    {
                        file.Read( &m_header.moment_inertia[ i ][ j ], 4, 1 );
                    }
                }
            }

            /*
             *	DECENT Network description:
             *	int num_cross_sections     -> number of cross sections (used for exploding ship) (*)
             *	for each cross_section, i {
             *	  float depth[i]
             *	  float radius[i]
             *	}
             */
            if( m_header.version >= 2014 )
            {
                file.Read( &m_header.num_cross_sections, 4, 1 );  //note: this is -1 if there aren't any, not 0.
                if( m_header.num_cross_sections > 0 )
                {
                    m_header.depth = new Float32[ m_header.num_cross_sections ];
                    m_header.radius = new Float32[ m_header.num_cross_sections ];
                    for( Int32 i=0; i<m_header.num_cross_sections; ++i )
                    {
                        file.Read( &m_header.depth[ i ], 4, 1 );
                        file.Read( &m_header.radius[ i ], 4, 1 );
                    }
                }
            }

            /*
             *	DECENT Network description:
             *	int num_lights    -> number of precalculated muzzle flash lights
             *	for each light {
             *	  vector location
             *	  int light_type  -> type of light
             *	}
             */
            if( m_header.version >= 2007 )
            {
                file.Read( &m_header.num_lights, 4, 1 );
                if( m_header.num_lights > 0 )
                {
                    m_header.location = new TPOFVector[ m_header.num_lights ];
                    m_header.light_type = new Int32[ m_header.num_lights ];
                    for( Int32 i=0; i<m_header.num_lights; ++i )
                    {
                        ReadVector( file, m_header.location[ i ] );
                        file.Read( &m_header.light_type[ i ], 4, 1 );
                    }
                }
            }

            /*
             *      allocate the array for the meshes and init them
             */
            m_data.meshes = new TPOFMesh[ m_header.num_subobjects ];
            for ( Int32 i=0; i<m_header.num_subobjects; ++i )
            {
                ZeroMeshStruct( m_data.meshes[ i ]);
            }
        }
        else
        if ( 0 == strcmp( blockID, "TXTR" ) )
        {
            /*
             *      this reads in the textures this model uses,
             *      and allocates and stores the strings
             *
             *	DECENT Network description:
             *	A list of textures used on this ship.
             *	The order they appear here is the number that a
             *	face uses to reference a particular texture.
             */ 
            file.Read( &length, 4, 1 );
            file.Read( &m_data.numtex, 4, 1 );

            /*
             *      Allocate array to store texture names
             */
            m_data.textures = new CString[ m_data.numtex ];
            m_data.texnames = new UInt32[ m_data.numtex ];
            memset( m_data.texnames, 0, sizeof(UInt32)*m_data.numtex );

            /*
             *      Read the texture names.
             *      Note that name can also me "invisible"
             *      this is not a texture but a polly that should
             *      not be drawn.
             */
            for( Int32 i=0; i<m_data.numtex; ++i )
            {
                m_data.textures[ i ] = ReadString( file );
            }
        }
        else
        if ( ( 0 == strcmp( blockID, "OBJ2" ) ) ||
             ( 0 == strcmp( blockID, "SOBJ" ) )  )
        {       
            /*
             *      this reads in object information.
             *	Note that the mesh itself is not actually read
             *	here, just it's location and properties.
             *
             *	DECENT Network description:
             *	'SOBJ' (FreeSpace 1) and 'OBJ2' (FreeSpace 2) -
             *	Data for a subobject. Contains some info and a
             *	bunch of vertices and polygons in the form of a
             *	BSP tree or Octree depending on how you look at
             *	it.
             */
           
            /*
             *	Load submodel number and init it's data
             *
             *	DECENT Network description:
             *	int submodel_number  -> What submodel number this is.
             */
            int modnum;
            file.Read( &length, 4, 1 );
            Int32 orgFilePos = file.Tell();
            file.Read( &modnum, 4, 1 );
            m_data.meshes[ modnum ].num_children = 0;
            m_data.meshes[ modnum ].submodel_children = NULL;
            m_data.meshes[ modnum ].submodel_number = modnum;

            if( m_header.version >= 2116 )
            {
                /*
                 *	DECENT Network description:
                 *      - FreeSpace 2
                 *        float radius        -> radius of this subobject
                 *        int submodel_parent -> What submodel is this model's parent. Equal to -1 if none.
                 *        vector offset       -> Offset to from parent object <- Added 09/10/98
                 */
                file.Read( &m_data.meshes[ modnum ].radius, 4, 1 );
                file.Read( &m_data.meshes[ modnum ].submodel_parent, 4, 1 );
                ReadVector( file, m_data.meshes[ modnum ].offset );
            }
            else
            {
                /*
                 *	DECENT Network description:
                 *      - FreeSpace 1
                 *        int submodel_parent -> What submodel is this model's parent. Equal to -1 if none.
                 *        vector offset       -> Offset to from parent object <- Added 09/10/98
                 *        float radius        -> radius of this subobject
                 */
                file.Read( &m_data.meshes[ modnum ].submodel_parent, 4, 1 );
                ReadVector( file, m_data.meshes[ modnum ].offset );
                file.Read( &m_data.meshes[ modnum ].radius, 4, 1 );
            }

            ReadVector( file, m_data.meshes[ modnum ].geometric_center );
            ReadVector( file, m_data.meshes[ modnum ].bounding_box_min_point );
            ReadVector( file, m_data.meshes[ modnum ].bounding_box_max_point );

            m_data.meshes[ modnum ].submodel_name = ReadString( file );
            m_data.meshes[ modnum ].properites = ReadString( file );

            file.Read( &m_data.meshes[ modnum ].movement_type, 4, 1 );
            file.Read( &m_data.meshes[ modnum ].movement_axis, 4, 1 );

            /*
             *	DECENT Network description:
             *       int reserved         -> must be 0
             *       int bsp_data_size    -> number of bytes now following
             *       char[bsp_data_size] bsp_data  -> contains actual polygons, etc.
             */
            file.Read( &m_data.meshes[ modnum ].reserved, 4, 1 ); // must always be 0
            if ( m_data.meshes[ modnum ].reserved != 0 ) return false; // should be 0
            file.Read( &m_data.meshes[ modnum ].bsp_data_size, 4, 1 );
            m_data.meshes[ modnum ].bsp_start_location = file.Tell();

            /*
             *	If this object has a parent we will hook them
             *	together here
             */
            if( m_data.meshes[ modnum ].submodel_parent != -1 )
            {
                m_data.meshes[ m_data.meshes[ modnum ].submodel_parent ].num_children++;
                m_data.meshes[ m_data.meshes[ modnum ].submodel_parent ].submodel_children = ( Int32* )realloc( m_data.meshes[ m_data.meshes[ modnum ].submodel_parent ].submodel_children, 4*m_data.meshes[ m_data.meshes[ modnum ].submodel_parent ].num_children );
                m_data.meshes[ m_data.meshes[ modnum ].submodel_parent ].submodel_children[ m_data.meshes[ m_data.meshes[ modnum ].submodel_parent ].num_children-1 ] = modnum;
            }

            /*
             *	Now we jump past the mesh data to next POF file
             *	segment. We will read the mesh later with the
             *	rest of the meshes.
             */
            file.Seek( orgFilePos + length, SEEK_SET ); 
        }
        else
        if ( 0 == strcmp( blockID, "SHLD" ) )
        {
            /*
             *      this reads in the shield
             */
            file.Read( &length, 4, 1 );
            file.Read( &m_data.shield.num_vertices, 4, 1 );
            m_data.shield.position = new TPOFVector[ m_data.shield.num_vertices ];

            UInt32 i;
            for( i=0; i<m_data.shield.num_vertices; i++ )
            {
                ReadVector( file, m_data.shield.position[ i ] );
            }
            file.Read( &m_data.shield.num_faces, 4, 1 );
            m_data.shield.face_normal = new TPOFVector[ 4*m_data.shield.num_faces ];
            m_data.shield.face_vertices = new TPOFInt3[ 4*m_data.shield.num_faces ];

            m_data.shield.neighbours = new TPOFInt3[ 4*m_data.shield.num_faces ];

            for( i=0; i<m_data.shield.num_faces; ++i )
            {
                ReadVector( file, m_data.shield.face_normal[ i ] );
                file.Read( &m_data.shield.face_vertices[ i ].a, 4, 1 );
                file.Read( &m_data.shield.face_vertices[ i ].b, 4, 1 );
                file.Read( &m_data.shield.face_vertices[ i ].c, 4, 1 );
                file.Read( &m_data.shield.neighbours[ i ].a, 4, 1 );
                file.Read( &m_data.shield.neighbours[ i ].b, 4, 1 );
                file.Read( &m_data.shield.neighbours[ i ].c, 4, 1 );
            }
            
            m_data.shield.shieldListNo = 0; // <- OpenGL shield display list id
        }
        else
        /*
         *      here's a bunch of parts of the objects I don't do
         *      anything with yet.
         */
        if ( 0 == strcmp( blockID, "PINF" ) )
        {
            /*
             *	DECENT Network description:
             *	'PINF' - Miscellaneous info about the POF file,
             *	command line, etc.
             *	Contains a block of NULL-terminated strings.
             *	Just read chunk size bytes and stuff it into a
             *      string.
             */ 
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "PATH" ) )
        {
            /*
             *	DECENT Network description:
             *       'PATH' - Paths for docking and AI ships to follow
             *
             *       int num_paths
             *       for each path, p {
             *        string name[p]             // name
             *        string parent[p]           // parent's name
             *        int num_verts[p]
             *        for each vert, v {
             *          vector pos[p,v]
             *          float radius[p,v]
             *          int num_turrets[p,v]
             *          for each turret, t {
             *           int sobj_number[p,v,t]  // subobject number
             *          }
             *        }
             *       }
             */ 
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "SPCL" ) )
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, " EYE" ) )
        {
            /*
             *	DECENT Network description:
             *	Data for eye points (Where pilot looks in 1st
             *	person views). Note the space in front of EYE.
             *
             *       int num_eye_positions
             *       for each eye_position, e {
             *        int sobj_number[e]      // subobject number this eye is attached to
             *        vector sobj_offset[e]   // offset from subobject
             *        vector normal[e]
             *       }
             */
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "GPNT" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "MPNT" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "TGUN" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "TMIS" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "DOCK" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "FUEL" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "INSG" ))
        {
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
        else
        if ( 0 == strcmp( blockID, "ACEN" ))
        {
            /*
             *	DECENT Network description:
             *	'ACEN' - Auto-Centering info (FreeSpace 2 only)
             *	vector point -> autocentering point for the
             *	entire model
             *	The autocentering point was basically just a
             *	little convenient extra data we stuck in models
             *	where the pivot point of the model wasn't at the
             *	center. Since we rotate ships in the tech room
             *	by rotating around the pivot point, it looked
             *	dumb when the colossus' rear end was in the
             *	middle of the screen and it was spinning on it.
             *	So the autocenter point was just a point pretty
             *	much near the model we could use to push an
             *	extra matrix onto our transform stack and have
             *	it show up centered around it.
             *	The point itself is in model coordinates.
             */ 
            if ( 1 != file.Read( &length, 4, 1 ) ) break;
            if ( 0 != file.Seek( length, SEEK_CUR ) ) break;
        }
    } 

    m_headerLoaded = true;
    return true;
}

//---------------------------------------------------------------------------

//void
//CPOFModel::Render( void )
//{
//	SObj_Render( 0 );
//        e->glstates.Syncronize();
//}
//
////---------------------------------------------------------------------------
//
//void
//CPOFModel::SObj_Render( Int32 subobj )
//{
//        /*
//         *      Render requested sub object
//         */
//         e->Output_glErrors();
//        glRotatef( 180.0, 0.0, 1.0, 0.0 );
//	glCallList( data->meshes[ subobj ].meshListNo );
//        #ifdef DEBUG_MODE
//        e->Output_glErrors();
//        #endif /* DEBUG_MODE */
//	Int32 i,j,k;
//	if( showchildren )
//        {
//                for( j=0; j< data->meshes[ subobj ].num_children; j++ )
//                {
//                        glPushMatrix();
//                        Int32 childModNum = data->meshes[ subobj ].submodel_children[ j ];
//                        glTranslatef( data->meshes[ childModNum ].offset.x,
//                                      data->meshes[ childModNum ].offset.y,
//                                      data->meshes[ childModNum ].offset.z );
//                        glCallList( data->meshes[ childModNum ].meshListNo );
//                        for( k=0; k<data->meshes[ data->meshes[ subobj ].submodel_children[ j ] ].num_children; k++ )
//                        {
//                                Int32 nextChildModNum = data->meshes[ childModNum ].submodel_children[ k ];
//                                glPushMatrix();										
//                                glTranslatef( data->meshes[ nextChildModNum ].offset.x,
//                                              data->meshes[ nextChildModNum ].offset.y,
//                                              data->meshes[ nextChildModNum ].offset.z );
//                                glCallList( data->meshes[ nextChildModNum ].meshListNo );
//                                glPopMatrix();
//                        }
//			glPopMatrix();
//		}
//	}
//
//	if ( showboundboxes )
//        {
//                /*
//                 *      Render bounding boxes, usefull for testing collision
//                 *      detection
//                 */
//                if ( lighting ) glDisable( GL_LIGHTING );
//                if ( textured ) glDisable( GL_TEXTURE_2D );
//                glColor3f( 0.6, 0.6, 0.6 );
//
//		/*
//                 *      show the main object boundbox
//                 */
//                glPushMatrix();
//                Render_Cube( &data->meshes[ subobj ].bounding_box_min_point,
//                             &data->meshes[ subobj ].bounding_box_max_point );
//	        glPopMatrix();
//
//	        /*
//                 *      show all the others.
//                 */
//                for( i=0; i<data->meshes[ subobj ].bsp_data.n_bbox; i++ )
//                {
//                        glPushMatrix();
//	                Render_Cube( &data->meshes[ subobj ].bsp_data.boundboxes[ i ].min_point,
//                                     &data->meshes[ subobj ].bsp_data.boundboxes[ i ].max_point );
//                        glPopMatrix();
//	        }
//
//                if ( lighting ) glEnable( GL_LIGHTING );
//	        if ( textured ) glEnable( GL_TEXTURE_2D );
//	}
//
//        if ( showshield )
//        {
//                /*
//                 *      show the shield mesh,
//                 *      we use the FS2 kinda look
//                 */
//                glColor4f( 0.0, 0.0, 1.0, 0.3 );
//                glDisable( GL_LIGHTING );
//                glDisable( GL_TEXTURE_2D );
//	        glFrontFace( GL_CCW );
//                glCallList( data->shield.shieldListNo );
//                glFrontFace( GL_CW );
//                glEnable(GL_LIGHTING);
//	        glEnable(GL_TEXTURE_2D);
//        }
//}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace PLUGINPOF */
}; /* namespace CA */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
