#-------------------------------------------------------------------
# This file is part of the CMake build system for GUCE
#     (Galaxy Unlimited Engine)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

include( GUConfigTargets )


function(ogre_config_lib LIBNAME)
  GU_config_lib( ${LIBNAME} )
endfunction(ogre_config_lib)

function(ogre_config_plugin PLUGINNAME)
  GU_config_plugin( ${PLUGINNAME} )
endfunction(ogre_config_plugin)

function(ogre_config_tool TOOLNAME)
  GU_config_tool( ${TOOLNAME} )
endfunction(ogre_config_tool)