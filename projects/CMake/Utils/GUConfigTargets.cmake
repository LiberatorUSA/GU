#-------------------------------------------------------------------
# This file is part of the CMake build system for GU
#     (Galaxy Unlimited Engine)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure settings and install targets

if (WIN32)
  set(GU_RELEASE_PATH "/Release")
  set(GU_RELWDBG_PATH "/RelWithDebInfo")
  set(GU_MINSIZE_PATH "/MinSizeRel")
  set(GU_DEBUG_PATH "/Debug")
  set(GU_LIB_RELEASE_PATH "/Release")
  set(GU_LIB_RELWDBG_PATH "/RelWithDebInfo")
  set(GU_LIB_MINSIZE_PATH "/MinSizeRel")
  set(GU_LIB_DEBUG_PATH "/Debug")
  set(GU_PLUGIN_PATH "/opt")
elseif (UNIX)
  set(GU_RELEASE_PATH "")
  set(GU_RELWDBG_PATH "")
  set(GU_MINSIZE_PATH "")
  set(GU_DEBUG_PATH "/debug")
  set(GU_LIB_RELEASE_PATH "")
  set(GU_LIB_RELWDBG_PATH "")
  set(GU_LIB_MINSIZE_PATH "")
  set(GU_LIB_DEBUG_PATH "")
  set(GU_PLUGIN_PATH "/GU")
endif ()

# create vcproj.user file for Visual Studio to set debug working directory
function(GU_create_vcproj_userfile TARGETNAME)
  if (MSVC)
    configure_file(
	  ${GU_TEMPLATES_DIR}/VisualStudioUserFile.vcproj.user.in
	  ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcproj.user
	  @ONLY
	)
  endif ()
endfunction(GU_create_vcproj_userfile)

# install targets according to current build type
function(GU_install_target TARGETNAME SUFFIX)
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${GU_RELEASE_PATH}" CONFIGURATIONS Release None ""
    LIBRARY DESTINATION "lib${GU_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
    ARCHIVE DESTINATION "lib${GU_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
    FRAMEWORK DESTINATION "bin${GU_RELEASE_PATH}" CONFIGURATIONS Release None ""
  )
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${GU_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
    LIBRARY DESTINATION "lib${GU_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
    ARCHIVE DESTINATION "lib${GU_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
    FRAMEWORK DESTINATION "bin${GU_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
  )
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${GU_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
    LIBRARY DESTINATION "lib${GU_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
    ARCHIVE DESTINATION "lib${GU_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
    FRAMEWORK DESTINATION "bin${GU_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
  )
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${GU_DEBUG_PATH}" CONFIGURATIONS Debug
    LIBRARY DESTINATION "lib${GU_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
    ARCHIVE DESTINATION "lib${GU_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
    FRAMEWORK DESTINATION "bin${GU_DEBUG_PATH}" CONFIGURATIONS Debug
  )
endfunction(GU_install_target)

# setup common target settings
function(GU_config_common TARGETNAME)
  set_target_properties(${TARGETNAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${GU_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${GU_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${GU_BINARY_DIR}/bin
  )
  if(GU_BUILD_PLATFORM_IPHONE)
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
    set_target_properties(${TARGETNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${GU_SOURCE_DIR}/GUMain/include/GUStableHeaders.h")
  endif(GU_BUILD_PLATFORM_IPHONE)

  GU_create_vcproj_userfile(${TARGETNAME})

  if (MSVC) 
    add_definitions( "/D_CRT_SECURE_NO_WARNINGS /wd4251 /nologo" )
  endif()

endfunction(GU_config_common)

# setup library build
function(GU_config_lib LIBNAME)
  GU_config_common(${LIBNAME})
  if (GU_STATIC)
    # add static prefix, if compiling static version
    set_target_properties(${LIBNAME} PROPERTIES OUTPUT_NAME ${LIBNAME}Static)

    if(GU_BUILD_PLATFORM_IPHONE)
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${GU_SOURCE_DIR}/GUMain/include/GUStableHeaders.h")
    endif(GU_BUILD_PLATFORM_IPHONE)
  else (GU_STATIC)
    if (CMAKE_COMPILER_IS_GNUCXX)
      # add GCC visibility flags to shared library build
      set_target_properties(${LIBNAME} PROPERTIES COMPILE_FLAGS "${GU_GCC_VISIBILITY_FLAGS}")
	endif (CMAKE_COMPILER_IS_GNUCXX)
	
	# Set some Mac OS X specific framework settings, including installing the headers in subdirs
	if (APPLE AND NOT GU_BUILD_PLATFORM_IPHONE)
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${GU_SOURCE_DIR}/GUMain/include/GUStableHeaders.h")
      set_target_properties(${LIBNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
      add_custom_command(TARGET ${LIBNAME} POST_BUILD
        COMMAND mkdir ARGS -p ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/GU.framework/Headers/Threading
	    COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${GU_SOURCE_DIR}/GUMain/include/Threading/* ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/GU.framework/Headers/Threading/
        COMMAND mkdir ARGS -p ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/GU.framework/Headers/OSX
	    COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${GU_SOURCE_DIR}/GUMain/include/OSX/*.h ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/GU.framework/Headers/OSX/
    )
	endif (APPLE AND NOT GU_BUILD_PLATFORM_IPHONE)
  endif (GU_STATIC)
  GU_install_target(${LIBNAME} "")
  
  if (GU_INSTALL_PDB)
    # install debug pdb files
    if (GU_STATIC)
	  install(FILES ${GU_BINARY_DIR}/lib${GU_LIB_DEBUG_PATH}/${LIBNAME}Static_d.pdb
	    DESTINATION lib${GU_LIB_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${GU_BINARY_DIR}/lib${GU_LIB_RELWDBG_PATH}/${LIBNAME}Static.pdb
	    DESTINATION lib${GU_LIB_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	else ()
	  install(FILES ${GU_BINARY_DIR}/bin${GU_DEBUG_PATH}/${LIBNAME}_d.pdb
	    DESTINATION bin${GU_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${GU_BINARY_DIR}/bin${GU_RELWDBG_PATH}/${LIBNAME}.pdb
	    DESTINATION bin${GU_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	endif ()
  endif ()
endfunction(GU_config_lib)

# setup plugin build
function(GU_config_plugin PLUGINNAME)
  GU_config_common(${PLUGINNAME})
  if (GU_STATIC)
    # add static prefix, if compiling static version
    set_target_properties(${PLUGINNAME} PROPERTIES OUTPUT_NAME ${PLUGINNAME}Static)

    if(GU_BUILD_PLATFORM_IPHONE)
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
      set_target_properties(${PLUGINNAME} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${GU_SOURCE_DIR}/GUMain/include/GUStableHeaders.h")
    endif(GU_BUILD_PLATFORM_IPHONE)
  else (GU_STATIC)
    if (CMAKE_COMPILER_IS_GNUCXX)
      # add GCC visibility flags to shared library build
      set_target_properties(${PLUGINNAME} PROPERTIES COMPILE_FLAGS "${GU_GCC_VISIBILITY_FLAGS}")
      # disable "lib" prefix on Unix
      set_target_properties(${PLUGINNAME} PROPERTIES PREFIX "")
	endif (CMAKE_COMPILER_IS_GNUCXX)	
  endif (GU_STATIC)
  GU_install_target(${PLUGINNAME} ${GU_PLUGIN_PATH})

  if (GU_INSTALL_PDB)
    # install debug pdb files
    if (GU_STATIC)
	  install(FILES ${GU_BINARY_DIR}/lib${GU_LIB_DEBUG_PATH}/${PLUGINNAME}Static_d.pdb
	    DESTINATION lib${GU_LIB_DEBUG_PATH}/opt
		CONFIGURATIONS Debug
	  )
	  install(FILES ${GU_BINARY_DIR}/lib${GU_LIB_RELWDBG_PATH}/${PLUGINNAME}Static.pdb
	    DESTINATION lib${GU_LIB_RELWDBG_PATH}/opt
		CONFIGURATIONS RelWithDebInfo
	  )
	else ()
	  install(FILES ${GU_BINARY_DIR}/bin${GU_DEBUG_PATH}/${PLUGINNAME}_d.pdb
	    DESTINATION bin${GU_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${GU_BINARY_DIR}/bin${GU_RELWDBG_PATH}/${PLUGINNAME}.pdb
	    DESTINATION bin${GU_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	endif ()
  endif ()
endfunction(GU_config_plugin)

# setup GU demo build
function(GU_config_sample SAMPLENAME)
  # The PRODUCT_NAME target setting cannot contain underscores.  Just remove them
  # Known bug in Xcode CFBundleIdentifier processing rdar://6187020
  # Can cause an instant App Store rejection. Also, code signing will fail. 
  #if (GU_BUILD_PLATFORM_IPHONE)
#    string (REPLACE "_" "" SAMPLENAME ${SAMPLENAME})
  #endif()
  GU_config_common(${SAMPLENAME})

  # set install RPATH for Unix systems
  if (UNIX AND GU_FULL_RPATH)
    set_property(TARGET ${SAMPLENAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
    set_property(TARGET ${SAMPLENAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()
  
  if (APPLE)
    # On OS X, create .app bundle
    set_property(TARGET ${SAMPLENAME} PROPERTY MACOSX_BUNDLE TRUE)

	if (GU_BUILD_PLATFORM_IPHONE)
      set (GU_SAMPLE_CONTENTS_PATH 
        ${CMAKE_BINARY_DIR}/bin/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)/$(PRODUCT_NAME).app)
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND cp ARGS ${CMAKE_BINARY_DIR}/bin/*.cfg ${GU_SAMPLE_CONTENTS_PATH}/
	    COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${GU_SOURCE_DIR}/Samples/Media ${GU_SAMPLE_CONTENTS_PATH}/
	    COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${GU_SOURCE_DIR}/Samples/Common/misc/Icon.png ${GU_SAMPLE_CONTENTS_PATH}/
	    COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${GU_SOURCE_DIR}/Samples/Common/misc/Default.png ${GU_SAMPLE_CONTENTS_PATH}/
      )
	else ()
      # also, symlink frameworks so .app is standalone
      # NOTE: $(CONFIGURATION) is not resolvable at CMake run time, it's only 
      # valid at build time (hence parenthesis rather than braces)
      set (GU_SAMPLE_CONTENTS_PATH 
        ${CMAKE_BINARY_DIR}/bin/$(CONFIGURATION)/${SAMPLENAME}.app/Contents)
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND mkdir ARGS -p ${GU_SAMPLE_CONTENTS_PATH}/Frameworks
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/GU.framework 
          ${GU_SAMPLE_CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${CMAKE_SOURCE_DIR}/Dependencies/Cg.framework 
          ${GU_SAMPLE_CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${CMAKE_SOURCE_DIR}/Dependencies/CEGUI.framework 
          ${GU_SAMPLE_CONTENTS_PATH}/Frameworks/
      )
      # now cfg files
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND mkdir ARGS -p ${GU_SAMPLE_CONTENTS_PATH}/Resources
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/plugins.cfg 
          ${GU_SAMPLE_CONTENTS_PATH}/Resources/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/resources.cfg 
          ${GU_SAMPLE_CONTENTS_PATH}/Resources/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/media.cfg 
          ${GU_SAMPLE_CONTENTS_PATH}/Resources/
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/quake3settings.cfg 
          ${GU_SAMPLE_CONTENTS_PATH}/Resources/
      )
      # now plugins
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND mkdir ARGS -p ${GU_SAMPLE_CONTENTS_PATH}/Plugins)
      if (GU_BUILD_RENDERSYSTEM_GL)
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
          COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/RenderSystem_GL.dylib 
            ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
        )
      endif ()
      if (GU_BUILD_RENDERSYSTEM_GLES)
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
          COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/RenderSystem_GLES.a
            ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
        )
      endif ()
      if (GU_BUILD_PLUGIN_BSP)    
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_BSPSceneManager.dylib 
          ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
        )
      endif()
      if (GU_BUILD_PLUGIN_CG)    
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_CgProgramManager.dylib 
          ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
        )
      endif()
      if (GU_BUILD_PLUGIN_OCTREE)    
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_OctreeSceneManager.dylib 
          ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
       )
      endif()
      if (GU_BUILD_PLUGIN_PCZ)    
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
          COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_PCZSceneManager.dylib 
            ${GU_SAMPLE_CONTENTS_PATH}/Plugins/    
        )
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_OctreeZone.dylib 
          ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
      )
      endif()
      if (GU_BUILD_PLUGIN_PFX)    
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_ParticleFX.dylib 
          ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
        )
      endif()
      if (GU_BUILD_CEGUIRENDERER)    
        add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/libCEGUIGURenderer.dylib 
          ${GU_SAMPLE_CONTENTS_PATH}/Plugins/
        )
      endif()
    endif()
  endif (APPLE)

  if (GU_INSTALL_SAMPLES)
    GU_install_target(${SAMPLENAME} "")
    if (GU_INSTALL_PDB)
      # install debug pdb files
      install(FILES ${GU_BINARY_DIR}/bin${GU_DEBUG_PATH}/${SAMPLENAME}.pdb
        DESTINATION bin${GU_DEBUG_PATH} CONFIGURATIONS Debug
        )
      install(FILES ${GU_BINARY_DIR}/bin${GU_RELWDBG_PATH}/${SAMPLENAME}.pdb
        DESTINATION bin${GU_RELWDBG_PATH} CONFIGURATIONS RelWithDebInfo
        )
    endif ()
  endif ()	

endfunction(GU_config_sample)

# setup GU tool build
function(GU_config_tool TOOLNAME)
  GU_config_common(${TOOLNAME})

  # set install RPATH for Unix systems
  if (UNIX AND GU_FULL_RPATH)
    set_property(TARGET ${TOOLNAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
    set_property(TARGET ${TOOLNAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()

  if (GU_INSTALL_TOOLS)
    GU_install_target(${TOOLNAME} "")
    if (GU_INSTALL_PDB)
      # install debug pdb files
      install(FILES ${GU_BINARY_DIR}/bin${GU_DEBUG_PATH}/${TOOLNAME}.pdb
        DESTINATION bin${GU_DEBUG_PATH}
        CONFIGURATIONS Debug
        )
      install(FILES ${GU_BINARY_DIR}/bin${GU_RELWDBG_PATH}/${TOOLNAME}.pdb
        DESTINATION bin${GU_RELWDBG_PATH}
        CONFIGURATIONS RelWithDebInfo
        )
    endif ()
  endif ()	

endfunction(GU_config_tool)
