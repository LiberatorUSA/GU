#-------------------------------------------------------------------
# This file is part of the CMake build system for GU
#     (Galaxy Unlimited)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

######################################################################
# GU BUILD SYSTEM
# Welcome to the CMake build system for GU.
# This is the main file where we prepare the general build environment
# and provide build configuration options.
######################################################################

cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0013 OLD)

project(GU)

# Include necessary submodules
set(CMAKE_MODULE_PATH 
  "${GU_SOURCE_DIR}/projects/CMake"
  "${GU_SOURCE_DIR}/projects/CMake/Utils" 
  "${GU_SOURCE_DIR}/projects/CMake/Packages"
)

include(CMakeDependentOption)
include(MacroLogFeature)
include(GUConfigTargets)
include(PreprocessorUtils)
include(GUCEFFuncRedirect)
include(GUCEFuncRedirect)

set(GU_TEMPLATES_DIR "${GU_SOURCE_DIR}/projects/CMake/Templates")
set(GU_WORK_DIR ${GU_BINARY_DIR})


#####################################################################
# Set up the basic build environment
#####################################################################

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

# determine GU version numbers
include(GUGetVersion)
GU_get_version(${GU_SOURCE_DIR}/common/include/GU_prerequisites.h)
message(STATUS "Configuring GU ${GU_VERSION}")

if (NOT APPLE)
  # Create debug libraries with _d postfix
  set(CMAKE_DEBUG_POSTFIX "_d")
endif ()

# Set compiler specific build flags
if (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-msse)
endif ()
if (MSVC)
  add_definitions(/fp:fast)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX)
  # Test for GCC visibility
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag(-fvisibility=hidden GU_GCC_VISIBILITY)
  if (GU_GCC_VISIBILITY)
    # determine gcc version
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion 
      OUTPUT_VARIABLE GU_GCC_VERSION)
    message(STATUS "Detected g++ ${GU_GCC_VERSION}")
    message(STATUS "Enabling GCC visibility flags")
    set(GU_GCC_VISIBILITY_FLAGS "-DGU_GCC_VISIBILITY -fvisibility=hidden")
  
    # check if we can safely add -fvisibility-inlines-hidden
    string(TOLOWER "${CMAKE_BUILD_TYPE}" GU_BUILD_TYPE)
    if (GU_BUILD_TYPE STREQUAL "debug" AND GU_GCC_VERSION VERSION_LESS "4.2")
      message(STATUS "Skipping -fvisibility-inlines-hidden due to possible bug in g++ < 4.2")
    else ()
      set(GU_GCC_VISIBILITY_FLAGS "${GU_GCC_VISIBILITY_FLAGS} -fvisibility-inlines-hidden")
    endif ()
  endif (GU_GCC_VISIBILITY)
endif (CMAKE_COMPILER_IS_GNUCXX)

# determine system endianess
include(TestBigEndian)
test_big_endian(GU_TEST_BIG_ENDIAN)

# Add common include path
include_directories("${GU_SOURCE_DIR}/common/include")
#include_directories("${GU_BINARY_DIR}/include")
if (APPLE)
  include_directories("${CMAKE_SOURCE_DIR}/GUMain/include/OSX")
endif (APPLE)

# Find dependencies
include(Dependencies)
# definitions for samples
set(GU_LIBRARIES GUCORE ) 

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${GU_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${GU_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${GU_BINARY_DIR}/bin")
if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX
	  "${GU_BINARY_DIR}/sdk" CACHE PATH "GU install prefix" FORCE
    )
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

# Set up iPhone overrides.
if (GU_BUILD_PLATFORM_IPHONE)
  # Force gcc <= 4.2 on iPhone
  include(CMakeForceCompiler)
  CMAKE_FORCE_C_COMPILER(gcc-4.2 GNU)
  CMAKE_FORCE_CXX_COMPILER(gcc-4.2 GNU)

  include_directories("${CMAKE_SOURCE_DIR}/GUMain/include/iPhone")

  # Set build variables
  set(CMAKE_OSX_SYSROOT iphoneos3.0)
  set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_UNIVERSAL_IPHONE_OS)")
  set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework CoreGraphics -framework QuartzCore -framework UIKit ${GU_SOURCE_DIR}/iPhoneDependencies/lib/release/libboost_date_time.a ${GU_SOURCE_DIR}/iPhoneDependencies/lib/release/libboost_thread.a")
  set(XCODE_ATTRIBUTE_SDKROOT iphoneos3.0)
  set(GU_BUILD_RENDERSYSTEM_GLES TRUE CACHE BOOL "Forcing OpenGL ES RenderSystem for iPhone" FORCE)
  set(GU_STATIC TRUE CACHE BOOL "Forcing static build for iPhone" FORCE)
  set(GU_SET_USE_BOOST TRUE CACHE BOOL "Forcing use of Boost libraries for iPhone" FORCE)
  set(GU_USE_BOOST TRUE CACHE BOOL "Forcing use of Boost libraries for iPhone" FORCE)
  set(Boost_FOUND TRUE CACHE BOOL "Forcing use of Boost libraries for iPhone" FORCE)
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.\${PRODUCT_NAME:rfc1034identifier}")

  add_definitions(-fno-regmove)
  remove_definitions(-msse)
elseif (APPLE AND NOT GU_BUILD_PLATFORM_IPHONE)
  # Force gcc <= 4.0 on Mac OS X because 4.2 is not supported prior to Mac OS X 10.5
  include(CMakeForceCompiler)
  CMAKE_FORCE_C_COMPILER(gcc-4.0 GNU)
  CMAKE_FORCE_CXX_COMPILER(gcc-4.0 GNU)

  # Set 10.4 as the base SDK by default
  set(XCODE_ATTRIBUTE_SDKROOT macosx10.4)

  # Make sure that the OpenGL render system is selected for non-iPhone Apple builds
  set(GU_BUILD_RENDERSYSTEM_GL TRUE)
  set(GU_BUILD_RENDERSYSTEM_GLES FALSE)
endif ()

######################################################################
# Provide user options to customise the build process
######################################################################

# Customise what to build
option(GU_STATIC "Static build" FALSE)

set(GU_CONFIG_ALLOCATOR 2 CACHE STRING
"Specify the memory allocator to use. Possible values:
  1 - Standard allocator
  2 - nedmalloc
  3 - User-provided allocator"
)
option(GU_CONFIG_MEMTRACK_DEBUG "Enable GU's memory tracker in debug mode" FALSE)
option(GU_CONFIG_MEMTRACK_RELEASE "Enable GU's memory tracker in release mode" FALSE)

# determine threading options

# Customise what to install


###################################################################
# configure global build settings based on selected build options
###################################################################

include(ConfigureBuild)

##################################################################
# Now setup targets
##################################################################

getenv_path( GUCEF_HOME )
message( STATUS "GUCEF_HOME=${ENV_GUCEF_HOME}" )

# Add GUCEF's common include path
include_directories("${ENV_GUCEF_HOME}/common/include")

# Setup GUCEF modules
add_subdirectory( ${ENV_GUCEF_HOME}/gucefMT ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCORE ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCOMCORE ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefGUI ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefIMAGE ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefMATH ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefINPUT ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefAUDIO ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCOM ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefMULTIPLAY ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefDRN ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefSMDRN ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefPATCHER ${GU_BINARY_DIR} )

# Setup GUCEF plugin dependencies
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCORE/plugins/dstorepluginPARSIFALXML/dependancy/libparsifal ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefINPUT/plugins/inputdriverOIS/dependency/OIS ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefIMAGE/plugins/imgpluginFreeImage/dependencies/FreeImage ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS/plugins/vfspluginZIP/dependencies/zlib ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS/plugins/vfspluginZIP/dependencies/zziplib/zzip ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS/plugins/vfspluginDVP/dependencies/DVPACKSYS ${GU_BINARY_DIR} )

# Setup GUCEF Plugin modules
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCORE/plugins/dstorepluginPARSIFALXML ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS/plugins/vfspluginDVP ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS/plugins/vfspluginVP ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS/plugins/vfspluginZIP ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefIMAGE/plugins/imgpluginFreeImage ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefIMAGE/plugins/imgpluginDEVIL ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefINPUT/plugins/inputdriverOIS ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefINPUT/plugins/inputdriverMSWINMSG ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefINPUT/plugins/inputdriverDIRECTINPUT8 ${GU_BINARY_DIR} )

# Setup GUCEF Test applications
add_subdirectory( ${ENV_GUCEF_HOME}/gucefVFS_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCOM_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCOMCORE_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefMT_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefCORE_TestApp ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefGUI_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefIMAGE_TestApp ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefMULTIPLAY_TestApp ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefMATH_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefINPUT_TestApp ${GU_BINARY_DIR} )
#add_subdirectory( ${ENV_GUCEF_HOME}/gucefAUDIO_TestApp ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/gucefDRN_TestApp ${GU_BINARY_DIR} )

# Setup GUCEF Tools
add_subdirectory( ${ENV_GUCEF_HOME}/tools/DuplicateFileFinder ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/DVPPackTool ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/FileReplacer ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/HDFiller ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/PatcherGUI ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/PatchSetGenerator ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/ServerPortExtender ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/CMakeListGenerator ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCEF_HOME}/tools/CallstackLogAnalyzer ${GU_BINARY_DIR} )

getenv_path( GUCE_HOME )
message( STATUS "GUCE_HOME=${ENV_GUCE_HOME}" )

# Setup Ogre dependencies

add_subdirectory( ${ENV_GUCE_HOME}/dependencies/freetype ${GU_BINARY_DIR} )

# Setup GUCE Ogre dependency
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/OgreMain ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/RenderSystems/GL ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/RenderSystems/Direct3D9 ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/RenderSystems/Direct3D10 ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/RenderSystems/Direct3D11 ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/RenderSystems/GLES ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/PlugIns/OctreeSceneManager ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/Samples/Common ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/Samples/Browser ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/dependencies/Ogre/Samples/Skybox ${GU_BINARY_DIR} )

# Add GUCE's common include path
include_directories( "${ENV_GUCE_HOME}/common/include" )
# Setup GUCE modules
add_subdirectory( ${ENV_GUCE_HOME}/guceCORE ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guceGUI ${GU_BINARY_DIR} )

# Setup GUCE guidriverMyGUIOgre Plugin dependencies
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre/dependencies/MyGUI/Common ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre/dependencies/MyGUI/Tools/FontViewer ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre/dependencies/MyGUI/Tools/ImageSetViewer ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre/dependencies/MyGUI/Tools/LayoutEditor ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre/dependencies/MyGUI/MyGUIEngine ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre/dependencies/MyGUI/Platforms/Ogre/OgrePlatform ${GU_BINARY_DIR} )

# Setup GUCE guidriverMyGUIOgre Plugin module
add_subdirectory( ${ENV_GUCE_HOME}/guidriverMyGUIOgre ${GU_BINARY_DIR} )

# Setup GUCE guidriverCEGUIOgre Plugin module
add_subdirectory( ${ENV_GUCE_HOME}/guidriverCEGUIOgre/dependency/CEGUI/dependencies/pcre ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverCEGUIOgre/dependency/CEGUI ${GU_BINARY_DIR} )
add_subdirectory( ${ENV_GUCE_HOME}/guidriverCEGUIOgre ${GU_BINARY_DIR} )

# Setup GUCE Sample applications
add_subdirectory( ${ENV_GUCE_HOME}/samples/refapp ${GU_BINARY_DIR} )

# Setup GU modules
add_subdirectory( guCORE )
add_subdirectory( gu )

# Setup GU plugins
add_subdirectory( plugins/guCApluginPOF )

# Install documentation
add_subdirectory( docs )

# Install CMake modules
#add_subdirectory( CMake )

# Provide CPack packaging target
#include( Packaging )

# Show feature summary
include( FeatureSummary )

