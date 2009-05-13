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

#ifndef GU_CORE_CPRODUCTINFOLIST_H
#define GU_CORE_CPRODUCTINFOLIST_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <map>

#ifndef GUCEF_CORE_EXCEPTIONMACROS_H
#include "ExceptionMacros.h"
#define GUCEF_CORE_EXCEPTIONMACROS_H
#endif /* GUCEF_CORE_EXCEPTIONMACROS_H ? */

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

class GU_CORE_EXPORT_CPP CProductInfoList : public GUCEF::CORE::CIConfigurable
{
    public:
    
    typedef std::map< CString, CProductInfo > TProductMap;
    typedef CProductInfo::TDeploymentStatus   TDeploymentStatus;
    typedef CProductInfo::TProductType        TProductType;  

    CProductInfoList( void );
    
    CProductInfoList( const CProductInfoList& src );
    
    virtual ~CProductInfoList();

    CProductInfoList& operator=( const CProductInfoList& src );

    virtual bool SaveConfig( GUCEF::CORE::CDataNode& node );
                                
    virtual bool LoadConfig( const GUCEF::CORE::CDataNode& node );
    
    TProductMap& GetList( const TDeploymentStatus deploymentStatus );
    
    const TProductMap& GetList( const TDeploymentStatus deploymentStatus ) const;

    void RetrieveListSubSet( const TProductType productType           ,
                             CProductInfoList& productList            ) const;
    
    void RetrieveListSubSet( const TDeploymentStatus deploymentStatus ,
                             const TProductType productType           ,
                             CProductInfoList& productList            ) const;
                             
    bool MergeProduct( const CProductInfo& productInfo );
    
    bool MergeProductList( const CProductInfoList& productInfoList );
    
    CProductInfo* RetrieveProductInfo( const CString& combinedProductString );
    
    const CProductInfo* RetrieveProductInfo( const CString& combinedProductString ) const;
    
    GUCEF_DEFINE_MSGEXCEPTION( GU_CORE_EXPORT_CPP, EInvalidDeploymentType );
    
    private:
    
    TProductMap m_availableProducts;
    TProductMap m_installedProducts;
    TProductMap m_updatingProducts;
    TProductMap m_downloadingProducts;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GU */

/*-------------------------------------------------------------------------*/

#endif /* GU_CORE_CPRODUCTINFOLIST_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 11-02-2008 :
        - Initial implementation
          
---------------------------------------------------------------------------*/
