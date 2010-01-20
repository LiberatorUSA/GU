#-------------------------------------------------------------------
# This file is part of the CMake build system for GU
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#######################################################################
# This file takes care of configuring GU to build with the settings
# given in CMake. It creates the necessary config.h file and will 
# also prepare package files for pkg-config and CMake.
#######################################################################

if (GU_BUILD_PLATFORM_IPHONE)
  set(GU_SET_BUILD_PLATFORM_IPHONE 1)
  set(GU_STATIC 1)
  set(GU_STATIC_LIB 1)
endif()

# should we build static libs?
if (GU_STATIC)
  set(GU_LIB_TYPE STATIC)
else ()
  set(GU_LIB_TYPE SHARED)
endif ()

# configure threading options
set(GU_THREAD_PROVIDER 0)
if (GU_CONFIG_THREADS)
	if (UNIX)
		add_definitions(-pthread)
	endif ()

	if (GU_CONFIG_THREAD_PROVIDER STREQUAL "boost")
		set(GU_THREAD_PROVIDER 1)
		include_directories(${Boost_INCLUDE_DIRS})
		# On MSVC Boost usually tries to autolink boost libraries. However since
		# this behaviour is not available on all compilers, we need to find the libraries
		# ourselves, anyway. Disable auto-linking to avoid mess-ups.
		add_definitions(-DBOOST_ALL_NO_LIB)
		set(GU_THREAD_LIBRARIES ${Boost_LIBRARIES})
	endif ()

	if (GU_CONFIG_THREAD_PROVIDER STREQUAL "poco")
		set(GU_THREAD_PROVIDER 2)
		include_directories(${POCO_INCLUDE_DIRS})
		set(GU_THREAD_LIBRARIES ${POCO_LIBRARIES})
	endif ()

	if (GU_CONFIG_THREAD_PROVIDER STREQUAL "tbb")
		set(GU_THREAD_PROVIDER 3)
		include_directories(${TBB_INCLUDE_DIRS})
		set(GU_THREAD_LIBRARIES ${TBB_LIBRARIES})
	endif ()
endif()


# determine config values depending on build options 
set(GU_SET_DOUBLE 0)
set(GU_SET_ALLOCATOR ${GU_CONFIG_ALLOCATOR})
set(GU_SET_CONTAINERS_USE_ALLOCATOR 0)
set(GU_SET_STRING_USE_ALLOCATOR 0)
set(GU_SET_MEMTRACK_DEBUG 0)
set(GU_SET_MEMTRACK_RELEASE 0)
set(GU_SET_THREADS ${GU_CONFIG_THREADS})
set(GU_SET_THREAD_PROVIDER ${GU_THREAD_PROVIDER})
set(GU_SET_DISABLE_FREEIMAGE 0)
set(GU_SET_DISABLE_DDS 0)
set(GU_SET_DISABLE_ZIP 0)
set(GU_SET_NEW_COMPILERS 0)
set(GU_STATIC_LIB 0)
set(GU_SET_USE_BOOST 0)
if (GU_CONFIG_DOUBLE)
  set(GU_SET_DOUBLE 1)
endif()
if (GU_CONFIG_CONTAINERS_USE_CUSTOM_ALLOCATOR)
  set(GU_SET_CONTAINERS_USE_ALLOCATOR 1)
endif ()
if (GU_CONFIG_STRING_USE_CUSTOM_ALLOCATOR)
  set(GU_SET_STRING_USE_ALLOCATOR 1)
endif ()
if (GU_CONFIG_MEMTRACK_DEBUG)
  set(GU_SET_MEMTRACK_DEBUG 1)
endif()
if (GU_CONFIG_MEMTRACK_RELEASE)
  set(GU_SET_MEMTRACK_RELEASE 1)
endif()
if (GU_CONFIG_DISABLE_FREEIMAGE)
  set(GU_SET_DISABLE_FREEIMAGE 1)
endif()
if (GU_CONFIG_DISABLE_DDS)
  set(GU_SET_DISABLE_DDS 1)
endif()
if (GU_CONFIG_DISABLE_ZIP)
  set(GU_SET_DISABLE_ZIP 1)
endif()
if(GU_CONFIG_NEW_COMPILERS)
  set(GU_SET_NEW_COMPILERS 1)
endif()
if (GU_STATIC)
  set(GU_STATIC_LIB 1)
endif()
if (GU_USE_BOOST)
  set(GU_SET_USE_BOOST 1)
endif()
add_definitions(-DHAVE_GU_BUILDSETTINGS_H)

if (GU_TEST_BIG_ENDIAN)
  set(GU_CONFIG_BIG_ENDIAN 1)
else ()
  set(GU_CONFIG_LITTLE_ENDIAN 1)
endif ()

# generate buildsettings.h 
configure_file(${GU_TEMPLATES_DIR}/GU_buildsettings.h.in ${GU_BINARY_DIR}/include/GU_buildsettings.h @ONLY)
install(FILES ${GU_BINARY_DIR}/include/GU_buildsettings.h DESTINATION include/GU)

# Read contents of the GU_Config.h file
file(READ "${GU_SOURCE_DIR}/common/include/GU_config.h" GU_CONFIG_H)
# add HAVE_GU_BUILDSETTINGS_H preprocessor define
file(WRITE ${GU_BINARY_DIR}/include/GU_config.h "#define HAVE_GU_BUILDSETTINGS_H\n${GU_CONFIG_H}")
install(FILES ${GU_BINARY_DIR}/include/GU_config.h DESTINATION include/GU)


# Create the pkg-config package files on Unix systems
if (UNIX)
  set(GU_LIB_SUFFIX "")
  set(GU_PLUGIN_PREFIX "")
  set(GU_PLUGIN_EXT ".so")
  if (GU_STATIC)
    set(GU_LIB_SUFFIX "${GU_LIB_SUFFIX}Static")
    set(GU_PLUGIN_PREFIX "lib")
    set(GU_PLUGIN_EXT ".a")
  endif ()
  string(TOLOWER "${CMAKE_BUILD_TYPE}" GU_BUILD_TYPE)
  if (GU_BUILD_TYPE STREQUAL "debug")
    set(GU_LIB_SUFFIX "${GU_LIB_SUFFIX}_d")
  endif ()

  set(GU_ADDITIONAL_LIBS "")
  set(GU_CFLAGS "")
  set(GU_PREFIX_PATH ${CMAKE_INSTALL_PREFIX})
  if (GU_CONFIG_THREADS GREATER 0)
    set(GU_CFLAGS "-pthread")
    set(GU_ADDITIONAL_LIBS "${GU_ADDITIONAL_LIBS} -lpthread")
  endif ()
  if (GU_STATIC)
    if (GU_CONFIG_THREADS)
      set(GU_ADDITIONAL_LIBS "${GU_ADDITIONAL_LIBS} -lboost-thread-mt")
    endif ()
    # there is no pkgconfig file for freeimage, so we need to add that lib manually
    set(GU_ADDITIONAL_LIBS "${GU_ADDITIONAL_LIBS} -lfreeimage")
    configure_file(${GU_TEMPLATES_DIR}/GUStatic.pc.in ${GU_BINARY_DIR}/pkgconfig/GU${GU_LIB_SUFFIX}.pc @ONLY)
  else ()
    configure_file(${GU_TEMPLATES_DIR}/GU.pc.in ${GU_BINARY_DIR}/pkgconfig/GU${GU_LIB_SUFFIX}.pc @ONLY)
  endif ()
  install(FILES ${GU_BINARY_DIR}/pkgconfig/GU${GU_LIB_SUFFIX}.pc DESTINATION lib/pkgconfig)

  # configure additional packages
  
endif ()

if (GU_STANDALONE_BUILD)
  set(CMAKE_USE_RELATIVE_PATHS true)
  set(CMAKE_SUPPRESS_REGENERATION true)
endif()

if (MSVC)
  # Enable intrinsics on MSVC in debug mode
  # Not actually necessary in release mode since /O2 implies /Oi but can't easily add this per build type?
  add_definitions(/Oi)
endif (MSVC)

### Commented because the FindGU script can currently fill this role better ###
# # Create the CMake package files
# if (WIN32)
#   set(GU_CMAKE_DIR CMake)
# elseif (UNIX)
#   set(GU_CMAKE_DIR lib/cmake)
# elseif (APPLE)
# endif ()
# configure_file(${GU_TEMPLATES_DIR}/GUConfig.cmake.in ${GU_BINARY_DIR}/cmake/GUConfig.cmake @ONLY)
# configure_file(${GU_TEMPLATES_DIR}/GUConfigVersion.cmake.in ${GU_BINARY_DIR}/cmake/GUConfigVersion.cmake @ONLY)
# install(FILES
#   ${GU_BINARY_DIR}/cmake/GUConfig.cmake
#   ${GU_BINARY_DIR}/cmake/GUConfigVersion.cmake
#   DESTINATION ${GU_CMAKE_DIR}
# )
# 
