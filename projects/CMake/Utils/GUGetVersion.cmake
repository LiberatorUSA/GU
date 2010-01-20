#-------------------------------------------------------------------
# This file is part of the CMake build system for GU
#     (Galaxy Unlimited)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

include(PreprocessorUtils)

macro(GU_get_version HEADER)
  file(READ ${HEADER} TEMP_VAR_CONTENTS)
  get_preprocessor_entry(TEMP_VAR_CONTENTS GU_VERSION_MAJOR GU_VERSION_MAJOR)
  get_preprocessor_entry(TEMP_VAR_CONTENTS GU_VERSION_MINOR GU_VERSION_MINOR)
  get_preprocessor_entry(TEMP_VAR_CONTENTS GU_VERSION_PATCH GU_VERSION_PATCH)
  get_preprocessor_entry(TEMP_VAR_CONTENTS GU_VERSION_NAME GU_VERSION_NAME)
  get_preprocessor_entry(TEMP_VAR_CONTENTS GU_VERSION_SUFFIX GU_VERSION_SUFFIX)
  set(GU_VERSION "${GU_VERSION_MAJOR}.${GU_VERSION_MINOR}.${GU_VERSION_PATCH}")
endmacro()
