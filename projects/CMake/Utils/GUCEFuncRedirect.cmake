#-------------------------------------------------------------------
# This file is part of the CMake build system for GU
#     (Galaxy Unlimited)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

include( GUConfigTargets )


function(GUCE_config_lib LIBNAME)
  GU_config_lib( ${LIBNAME} )
endfunction(GUCE_config_lib)

function(GUCE_config_plugin PLUGINNAME)
  GU_config_plugin( ${PLUGINNAME} )
endfunction(GUCE_config_plugin)

function(GUCE_config_tool TOOLNAME)
  GU_config_tool( ${TOOLNAME} )
endfunction(GUCE_config_tool)