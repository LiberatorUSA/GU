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
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCE_CORE_MISCUTILS_H
#include "miscutils.h"
#define GUCE_CORE_MISCUTILS_H
#endif /* GUCE_CORE_MISCUTILS_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#include "guCORE_CProductManager.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GU {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

CProductManager* CProductManager::g_instance = NULL;

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CProductManager*
CProductManager::Instance( void )
{GU_TRACE;

    if ( NULL == g_instance )
    {
        g_instance = new CProductManager();
    }
    return g_instance;    
}

/*-------------------------------------------------------------------------*/

void
CProductManager::Deinstance( void )
{GU_TRACE;

    delete g_instance;
    g_instance = NULL;
}

/*-------------------------------------------------------------------------*/

CProductManager::CProductManager( void )
    : CIConfigurable( true )      ,
      m_productList()             ,
      m_productListPath()         ,
      m_productListCodec( "xml" ) ,
      m_productRoot()             ,
      m_downloadsManager()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CProductManager::~CProductManager()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CDownloadsManager&
CProductManager::GetDownloadsManager( void )
{GU_TRACE;

    return m_downloadsManager;
}

/*-------------------------------------------------------------------------*/

void
CProductManager::RetrieveProductList( CProductInfoList& productList ) const
{GU_TRACE;
    
    RetrieveProductList( CProductInfo::DEPLOYMENTSTATE_UNKNOWN ,
                         CProductInfo::PRODUCTTYPE_UNKNOWN     ,
                         productList                           );
}

/*-------------------------------------------------------------------------*/

void
CProductManager::RetrieveProductList( const TDeploymentStatus deploymentState ,
                                      const TProductType productType          ,
                                      CProductInfoList& productList           ) const
{GU_TRACE;

    m_productList.RetrieveListSubSet( deploymentState ,
                                      productType     ,
                                      productList     );  
}

/*-------------------------------------------------------------------------*/

bool
CProductManager::RetrieveProductInfo( const CString& combinedProductName ,
                                      CProductInfo& productInfo          ) const

{GU_TRACE;
                                      
    const CProductInfo* foundProductInfo = m_productList.RetrieveProductInfo( combinedProductName );
    if ( NULL != foundProductInfo )
    {
        productInfo = *foundProductInfo;
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

bool
CProductManager::MergeProduct( const CProductInfo& productInfo )
{GU_TRACE;

    return m_productList.MergeProduct( productInfo );
}

/*-------------------------------------------------------------------------*/

bool
CProductManager::MergeProductList( const CProductInfoList& productList )
{GU_TRACE;

    return m_productList.MergeProductList( productList );
}

/*-------------------------------------------------------------------------*/

bool
CProductManager::SaveConfig( GUCEF::CORE::CDataNode& node )
{GU_TRACE;

    GUCEF_SYSTEM_LOG( 0, "Saving the product manager configuration" );
    
    GUCEF::CORE::CDataNode* n = node.Structure( "GU%CORE%CProductManager", '%' );
    n->SetAttribute( "ProductListPath", m_productListPath );
    n->SetAttribute( "ProductListCodec", m_productListCodec );
    n->SetAttribute( "CommonProductRoot", m_productRoot );
    m_downloadsManager.SaveConfig( node );
    return true;
}

/*-------------------------------------------------------------------------*/
                                
bool
CProductManager::LoadConfig( const GUCEF::CORE::CDataNode& node )
{GU_TRACE;

    GUCEF_SYSTEM_LOG( 0, "Loading the product manager configuration" );

    GUCEF::CORE::CDataNode* n = node.Search( "GU%CORE%CProductManager", '%', false );
    if ( NULL != n )
    {
        GUCEF::CORE::CDataNode::TNodeAtt* att = NULL;
        att = n->GetAttribute( "ProductListPath" );
        if ( NULL != att )
        {
            m_productListPath = att->value;
        }
        att = n->GetAttribute( "ProductListCodec" );
        if ( NULL != att )
        {
            m_productListCodec = att->value;
        }

        att = n->GetAttribute( "CommonProductRoot" );
        if ( NULL != att )
        {
            m_productRoot = att->value;
        }

        GUCEF::CORE::CDataNode productList;        
        if ( GUCE::CORE::VFSLoadDataTree( m_productListPath  ,
                                          m_productListCodec ,
                                          &productList       ) )
        {
            m_productList.LoadConfig( productList );
        }
        
        m_downloadsManager.LoadConfig( node );
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

void
CProductManager::SetCommonProductRoot( const CString commonProductRoot )
{GU_TRACE;

    m_productRoot = commonProductRoot;
}

/*-------------------------------------------------------------------------*/

CString
CProductManager::GetCommonProductRoot( void ) const
{GU_TRACE;

    return m_productRoot;
}

/*-------------------------------------------------------------------------*/

CString
CProductManager::GetProductRoot( const CProductInfo& product ) const
{GU_TRACE;

    CString path;
    if ( m_productRoot.Length() > 0 )
    {
         path = m_productRoot + '/';
    }
    path += CString( "Products" ) + '/' + product.GetCombinedProductString();
    return path;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/
