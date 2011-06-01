/*
 *  guCORE: Desktop launcher for the Galaxy Unlimited platform
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
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

#ifndef GUCE_H
#include "guce.h"       /* main GUCE engine include */
#define GUCE_H
#endif /* GUCE_H ? */

#ifndef GU_CORE_CGAMECENTER_H
#include "guCORE_CGameCenter.h"
#define GU_CORE_CGAMECENTER_H
#endif /* GU_CORE_CGAMECENTER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

/**
 *  Dummy class to get around allocations when obtaining info from the exception object
 *  If we crashed due to some memory allocation problem then we don't want to perform any
 *  allocations that are not absolutely required
 */
class CAccessOgreException : public Ogre::Exception
{
        public:
        
        inline const Ogre::String& GetFile( void ) const
        {
                return file;
        }
        
        inline const Ogre::String& GetFullDescription( void ) const
        {
                return description;
        }        
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Application entry point
 */
#ifdef GUCEF_MSWIN_BUILD

int __stdcall
WinMain( HINSTANCE hinstance     ,
         HINSTANCE hprevinstance ,
         LPSTR lpcmdline         ,
         int ncmdshow            )

#else

int __stdcall
main( const char* argv[] ,
      int argc           )

#endif

{GUCE_TRACE;

    #ifdef GUCE_CORE_DEBUG_MODE
    //GUCEF::CORE::GUCEF_LogStackToStdOut();
    //GUCEF::CORE::GUCEF_SetStackLogging( 1 );
    #endif /* GUCE_CORE_DEBUG_MODE ? */

    GUCEF::CORE::CLogManager* logManager = GUCEF::CORE::CLogManager::Instance();
    
    GUCEF::CORE::CString logFilename = GUCEF::CORE::RelativePath( "$CURWORKDIR$" );
    GUCEF::CORE::AppendToPath( logFilename, "GU_Log.txt" );
    GUCEF::CORE::CFileAccess logFileAccess( logFilename, "w" );
    
    GUCEF::CORE::CStdLogger logger( logFileAccess );
    #ifdef GUCE_CORE_DEBUG_MODE
    logger.SetMinimalLogLevel( GUCEF::CORE::LOGLEVEL_EVERYTHING );
    #endif /* GUCE_CORE_DEBUG_MODE ? */
    logManager->AddLogger( &logger ); 

    #if defined( GUCEF_MSWIN_BUILD ) && defined( GUCE_CORE_DEBUG_MODE )
    GUCEF::CORE::CMSWinConsoleLogger consoleOut;
    consoleOut.SetMinimalLogLevel( GUCEF::CORE::LOGLEVEL_NORMAL );
    logManager->AddLogger( &consoleOut );
    #endif /* GUCEF_MSWIN_BUILD && GUCE_CORE_DEBUG_MODE ? */
    
    logManager->FlushBootstrapLogEntriesToLogs();
                
    try 
    {        
        /*
         *      Get some pointers to system components
         */
        GUCEF::CORE::CConfigStore* configStore = GUCEF::CORE::CConfigStore::Instance();
        GUCEF::CORE::CDStoreCodecPluginManager* dataStorageCodecMan = GUCEF::CORE::CDStoreCodecPluginManager::Instance();        
        GUCE::CORE::CGUCEApplication* app = GUCE::CORE::CGUCEApplication::Instance();
        
        /*
         *  Call some singletons etc. for no reason except to prevent the compiler from
         *  'optimizing' the dependencies away.
         */
        GUCE::GUI::CGUIManager::Instance();
        GU::CORE::CGameCenter::Instance();
        
        #if defined( GUCEF_MSWIN_BUILD )
        GUCEF::CORE::CMsWin32ConsoleWindow win32Console;
        win32Console.ConsoleWindowCreate();
	    win32Console.Show();
        #endif
         
        // Load data store codec's so we can load config
        GUCEF::CORE::CDStoreCodecPluginManager* dstoreCodecPluginManager = GUCEF::CORE::CDStoreCodecPluginManager::Instance();
        dstoreCodecPluginManager->LoadAll( GUCEF::CORE::RelativePath( "$MODULEDIR$" ) ); 

        /*
         *      Load the configuration
         */
        configStore->SetConfigFile( "$MODULEDIR$\\GU_Config.xml" );                
        if ( configStore->LoadConfig() )
        {
            /*
             *      Start the Application
             */
            #ifdef GUCE_MSWIN_BUILD
            
            int retval = app->Main( hinstance     ,
                                    lpcmdline     ,
                                    ncmdshow      ,
                                    true          );
            #else
            
            int retval = app->main( argv ,
                                    argc ,
                                    true );            
            
            #endif
            
            /*
             *      Save the configuration changes
             */                                                                             
            configStore->SaveConfig( "GU" );  
            
            return retval;                                                                  
        }
        else
        {
            GUCEF::CORE::CString msg( "Failed to load application configuration\n" );
            msg += "Unable to load \"" + configStore->GetConfigFile() + "\" using codec " + configStore->GetCodec();
            GUCEF::CORE::ShowErrorMessage( "Startup error" ,
                                           msg.C_String()  );           
        }
        
    }    
    catch ( GUCEF::CORE::CException& e )
    {
        #ifdef GUCE_CORE_DEBUG_MODE
        GUCEF::CORE::GUCEF_PrintCallstack();
        GUCEF::CORE::GUCEF_DumpCallstack( "CallstackDump.txt" );
        #endif /* GUCE_CORE_DEBUG_MODE ? */
            
        GUCEF::CORE::CString msg( "GUCEF exception during program execution\n\n" );
        msg += "file: " + GUCEF::CORE::CString( e.GetOriginFile() ) + "\n" + "line: " + GUCEF::CORE::Int32ToString( e.GetOriginLineNr() );
        
        GUCEF::CORE::ShowErrorMessage( "Unhandled GUCEF exception" ,
                                       msg.C_String()              );                  
    }    
    catch( Ogre::Exception& e )
    {
        #ifdef GUCE_CORE_DEBUG_MODE
        GUCEF::CORE::GUCEF_PrintCallstack();
        GUCEF::CORE::GUCEF_DumpCallstack( "CallstackDump.txt" );
        #endif /* GUCE_CORE_DEBUG_MODE ? */
        
        CAccessOgreException& ea = static_cast<CAccessOgreException&>( e );
        
        GUCEF::CORE::CString msg( "Ogre exception during program execution\n\n" );
        msg += "file: " + ea.GetFile() + "\n" + "line: " + GUCEF::CORE::Int32ToString( e.getLine() ) + "\ndescription: " + ea.GetFullDescription();
        
        GUCEF::CORE::ShowErrorMessage( "Unhandled Ogre exception" ,
                                       msg.C_String()             );        
    }                                                                                
    catch( std::bad_alloc& e )
    {
        #ifdef GUCE_CORE_DEBUG_MODE
        GUCEF::CORE::GUCEF_PrintCallstack();
        GUCEF::CORE::GUCEF_DumpCallstack( "CallstackDump.txt" );
        #endif /* GUCE_CORE_DEBUG_MODE ? */
        
        GUCEF::CORE::CString msg( "Memory allocation failure during program execution\n\n" + GUCEF::CORE::CString( e.what() ) );
        GUCEF::CORE::ShowErrorMessage( "Unhandled STL bad_alloc exception" ,
                                       msg.C_String()                      );    
    }    
    catch( std::exception& e )
    {
        #ifdef GUCE_CORE_DEBUG_MODE
        GUCEF::CORE::GUCEF_PrintCallstack();
        GUCEF::CORE::GUCEF_DumpCallstack( "CallstackDump.txt" );
        #endif /* GUCE_CORE_DEBUG_MODE ? */
        
        GUCEF::CORE::CString msg( "STL exception during program execution\n\n" + GUCEF::CORE::CString( e.what() ) );
        GUCEF::CORE::ShowErrorMessage( "Unhandled STL exception" ,
                                       msg.C_String()            );        
    }    
    catch ( ... )
    {
        #ifdef GUCE_CORE_DEBUG_MODE
        GUCEF::CORE::GUCEF_PrintCallstack();
        GUCEF::CORE::GUCEF_DumpCallstack( "CallstackDump.txt" );
        #endif /* GUCE_CORE_DEBUG_MODE ? */
        
        GUCEF::CORE::ShowErrorMessage( "Unknown exception"                                                                 ,
                                       "Unhandled exception during program execution, the application will now terminate"  );
    }
    return 1;                                                                                                                              
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 13-01-2007
        - Dinand: Initial version

-----------------------------------------------------------------------------*/