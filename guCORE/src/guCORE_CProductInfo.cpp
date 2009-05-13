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

#ifndef GUCEF_CORE_CDATANODE_H
#include "CDataNode.h"
#define GUCEF_CORE_CDATANODE_H
#endif /* GUCEF_CORE_CDATANODE_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#include "guCORE_CProductInfo.h"

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

CProductInfo::CProductInfo( void )
    : CIConfigurable()                             ,
      m_name()                                     ,
      m_description()                              ,
      m_infoURL()                                  ,
      m_patchListURL()                             ,
      m_version()                                  ,
      m_deploymentState( DEPLOYMENTSTATE_UNKNOWN ) ,
      m_productType( PRODUCTTYPE_UNKNOWN )
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CProductInfo::~CProductInfo()
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CProductInfo::CProductInfo( const CProductInfo& src )
    : CIConfigurable()                           ,
      m_name( src.m_name )                       ,
      m_description( src.m_description )         ,
      m_infoURL( src.m_infoURL )                 ,
      m_patchListURL( src.m_patchListURL )       ,
      m_version( src.m_version )                 ,
      m_deploymentState( src.m_deploymentState ) ,
      m_productType( src.m_productType )
{GU_TRACE;

}

/*-------------------------------------------------------------------------*/

CProductInfo&
CProductInfo::operator=( const CProductInfo& src )
{GU_TRACE;

    if ( &src != this )
    {
        m_name = src.m_name;
        m_description = src.m_description;
        m_infoURL = src.m_infoURL;
        m_patchListURL = src.m_patchListURL;
        m_version = src.m_version;
        m_deploymentState = src.m_deploymentState;
        m_productType = src.m_productType;
    }
    return *this;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetName( const CString& name )
{GU_TRACE;

    m_name = name;
}

/*-------------------------------------------------------------------------*/

const CString&
CProductInfo::GetName( void ) const
{GU_TRACE;

    return m_name;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetParentName( const CString& name )
{GU_TRACE;

    m_parentName = name;
}

/*-------------------------------------------------------------------------*/

const CString&
CProductInfo::GetParentName( void ) const
{GU_TRACE;

    return m_parentName;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetDescription( const CString& description )
{GU_TRACE;

    m_description = description;
}

/*-------------------------------------------------------------------------*/

const CString&
CProductInfo::GetDescription( void ) const
{GU_TRACE;

    return m_description;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetInfoURL( const CString& infoURL )
{GU_TRACE;

    m_infoURL = infoURL;
}

/*-------------------------------------------------------------------------*/

const CString&
CProductInfo::GetInfoURL( void ) const
{GU_TRACE;

    return m_infoURL;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetPatchListURL( const CString& patchListURL )
{GU_TRACE;

    m_patchListURL = patchListURL;
}

/*-------------------------------------------------------------------------*/

const CString&
CProductInfo::GetPatchListURL( void ) const
{GU_TRACE;

    return m_patchListURL;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetDeploymentState( const TDeploymentStatus deploymentState )
{GU_TRACE;

    m_deploymentState = deploymentState;
}

/*-------------------------------------------------------------------------*/

const CProductInfo::TDeploymentStatus
CProductInfo::GetDeploymentState( void ) const
{GU_TRACE;

    return m_deploymentState;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetProductType( const TProductType productType )
{GU_TRACE;

    m_productType = productType;
}

/*-------------------------------------------------------------------------*/

const CProductInfo::TProductType
CProductInfo::GetProductType( void ) const
{GU_TRACE;

    return m_productType;
}

/*-------------------------------------------------------------------------*/

void
CProductInfo::SetVersion( const GUCEF::CORE::TVersion& version )
{GU_TRACE;
    
    m_version = version;
}

/*-------------------------------------------------------------------------*/

const GUCEF::CORE::TVersion&
CProductInfo::GetVersion( void ) const
{GU_TRACE;

    return m_version;
}

/*-------------------------------------------------------------------------*/

bool
CProductInfo::operator<( const CProductInfo& other ) const
{GU_TRACE;

    return GetCombinedProductString() < other.GetCombinedProductString();
}

/*-------------------------------------------------------------------------*/

CString
CProductInfo::ProductTypeToString( const TProductType productType )
{GU_TRACE;

    switch ( productType )
    {
        case PRODUCTTYPE_INDEPENDANT :
        {
            return "Independent";
        }
        case PRODUCTTYPE_MODIFICATION :
        {
            return "Modification";
        }
        case PRODUCTTYPE_EXPANSION :
        {
            return "Expansion";
        }
        case PRODUCTTYPE_PLUGIN :
        {
            return "Plugin";
        }
        default:
        {
            return "Unknown";
        }
    }
}

/*-------------------------------------------------------------------------*/

const CProductInfo::TProductType
CProductInfo::StringToProductType( const CString& productType )
{GU_TRACE;

    if ( productType.Equals( "Independent", false ) )
    {
        return PRODUCTTYPE_INDEPENDANT;
    }
    if ( productType.Equals( "Modification", false ) )
    {
        return PRODUCTTYPE_MODIFICATION;
    }
    if ( productType.Equals( "Expansion", false ) )
    {
        return PRODUCTTYPE_EXPANSION;
    }
    if ( productType.Equals( "Plugin", false ) )
    {
        return PRODUCTTYPE_PLUGIN;
    }
    return PRODUCTTYPE_UNKNOWN;
}

/*-------------------------------------------------------------------------*/

CString
CProductInfo::DeploymentStateToString( TDeploymentStatus deploymentState )
{GU_TRACE;
    
    switch ( deploymentState )
    {
        case DEPLOYMENTSTATE_INSTALLED :
        {
            return "Installed";
        }
        case DEPLOYMENTSTATE_UPDATING :
        {
            return "Updating";
        }
        case DEPLOYMENTSTATE_DOWNLOADING :
        {
            return "Downloading";
        }
        case DEPLOYMENTSTATE_AVAILABLEFORDOWNLOAD :
        {
            return "AvailableForDownload";
        }
        default :
        {
            return "Unknown";
        }
    }
}

/*-------------------------------------------------------------------------*/

const CProductInfo::TDeploymentStatus
CProductInfo::StringToDeploymentState( const CString& deploymentState )
{GU_TRACE;

    if ( deploymentState.Equals( "Installed", false ) )
    {
        return DEPLOYMENTSTATE_INSTALLED;
    }
    if ( deploymentState.Equals( "Updating", false ) )
    {
        return DEPLOYMENTSTATE_UPDATING;
    }
    if ( deploymentState.Equals( "Downloading", false ) )
    {
        return DEPLOYMENTSTATE_DOWNLOADING;
    }
    if ( deploymentState.Equals( "AvailableForDownload", false ) )
    {
        return DEPLOYMENTSTATE_AVAILABLEFORDOWNLOAD;
    }
    return DEPLOYMENTSTATE_UNKNOWN;    
}

/*-------------------------------------------------------------------------*/

bool
CProductInfo::SaveConfig( GUCEF::CORE::CDataNode& node )
{GU_TRACE;

    GUCEF::CORE::CDataNode newNode( "ProductInfo" );
    newNode.SetAttribute( "Name", m_name );
    newNode.SetAttribute( "Description", m_description ); 
    newNode.SetAttribute( "Version", GUCEF::CORE::VersionToString( m_version ) );
    newNode.SetAttribute( "ProductType", ProductTypeToString( m_productType ) );
    newNode.SetAttribute( "DeploymentState", DeploymentStateToString( m_deploymentState ) );
    newNode.SetAttribute( "PatchListURL", m_patchListURL );
    newNode.SetAttribute( "InfoURL", m_infoURL );
    node.AddChild( newNode );
    return true;
}

/*-------------------------------------------------------------------------*/
                                
bool
CProductInfo::LoadConfig( const GUCEF::CORE::CDataNode& node )
{GU_TRACE;

    const GUCEF::CORE::CDataNode* infoNode = node.Find( "ProductInfo" );
    if ( NULL != infoNode )
    {
        const GUCEF::CORE::CDataNode::TNodeAtt* att = NULL;
        att = infoNode->GetAttribute( "Name" );
        if ( NULL != att )
        {
            m_name = att->value;
        }
        att = infoNode->GetAttribute( "Version" );
        if ( NULL != att )
        {
            m_version = GUCEF::CORE::StringToVersion( att->value );
        }
        att = infoNode->GetAttribute( "Description" );
        if ( NULL != att )
        {
            m_name = att->value;
        }
        att = infoNode->GetAttribute( "ProductType" );
        if ( NULL != att )
        {
            m_name = StringToProductType( att->value );
        }
        att = infoNode->GetAttribute( "DeploymentState" );
        if ( NULL != att )
        {
            m_name = StringToDeploymentState( att->value );
        }        
        att = infoNode->GetAttribute( "PatchListURL" );
        if ( NULL != att )
        {
            m_patchListURL = att->value;
        }
        att = infoNode->GetAttribute( "InfoURL" );
        if ( NULL != att )
        {
            m_infoURL = att->value;
        }
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

CString
CProductInfo::GetCombinedProductString( void ) const
{GU_TRACE;
    
    const CString& mainName = m_parentName.Length() > 0 ? m_parentName : m_name;
    CString path = mainName + '/' + GUCEF::CORE::VersionToString( m_version ) + '/';
  
    if ( ( m_productType != CProductInfo::PRODUCTTYPE_UNKNOWN )     &&
         ( m_productType != CProductInfo::PRODUCTTYPE_INDEPENDANT )  )
    {
        path += CProductInfo::ProductTypeToString( m_productType ) + "s/";
        if ( m_productType != CProductInfo::PRODUCTTYPE_PLUGIN )
        {
            path += GUCEF::CORE::VersionToString( m_version ) + '/';
        }
        if ( m_parentName.Length() > 0 )
        {
            path += m_name;
        }
    }
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
