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

#ifndef GU_CORE_CPRODUCTMANAGER_H
#define GU_CORE_CPRODUCTMANAGER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <set>

#ifndef GU_CORE_CDOWNLOADSMANAGER_H
#include "guCORE_CDownloadsManager.h"
#define GU_CORE_CDOWNLOADSMANAGER_H
#endif /* GU_CORE_CDOWNLOADSMANAGER_H ? */

#ifndef GU_CORE_CPRODUCTINFOLIST_H
#include "guCORE_CProductInfoList.h"
#define GU_CORE_CPRODUCTINFOLIST_H
#endif /* GU_CORE_CPRODUCTINFOLIST_H ? */

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

class GU_CORE_EXPORT_CPP CProductManager : public GUCEF::CORE::CIConfigurable
{
    public:
    
    typedef CProductInfo::TDeploymentStatus  TDeploymentStatus;
    typedef CProductInfo::TProductType       TProductType;
    typedef std::set< CProductInfo >         TProductList; 

    static CProductManager* Instance( void );
    
    bool RetrieveProductInfo( const CString& combinedProductName ,
                              CProductInfo& productInfo          ) const;

    void RetrieveProductList( CProductInfoList& productList ) const;

    void RetrieveProductList( const TDeploymentStatus deploymentState ,
                              const TProductType productType          ,
                              CProductInfoList& productList           ) const;

    bool MergeProductList( const CProductInfoList& productList );
    
    bool MergeProduct( const CProductInfo& productInfo );
    
    virtual bool SaveConfig( GUCEF::CORE::CDataNode& node );
                                
    virtual bool LoadConfig( const GUCEF::CORE::CDataNode& node );

    CString GetProductRoot( const CProductInfo& product ) const;

    void SetCommonProductRoot( const CString commonProductRoot );

    CString GetCommonProductRoot( void ) const;
    
    CDownloadsManager& GetDownloadsManager( void );
    
    private:
    friend class CGUCOREModule;
    
    static void Deinstance( void );
    
    private:
    
    CProductManager( void );
    CProductManager( const CProductManager& src );
    virtual ~CProductManager();
    CProductManager& operator=( const CProductManager& src );
    
    private:
    
    CProductInfoList m_productList;
    CString m_productListPath;
    CString m_productListCodec;
    CString m_productRoot;
    CDownloadsManager m_downloadsManager;
    static CProductManager* g_instance;
    
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CPRODUCTMANAGER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 11-02-2008 :
        - Initial implementation
          
---------------------------------------------------------------------------*/
