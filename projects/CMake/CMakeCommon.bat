@echo off

SET GU_BATCHSTARTDIR=%CD%

ECHO *** Enable command extensions ***

VERIFY OTHER 2>nul
SETLOCAL ENABLEEXTENSIONS
IF ERRORLEVEL 1 (
  REM ERROR: Unable to enable extensions
  PAUSE
)
ENDLOCAL

ECHO *** Locating GUCE ***

IF NOT DEFINED GUCE_HOME (
  ECHO GUCE_HOME not defined, defaulting to local trunk copy
  SET GUCE_HOME=%CD%\..\..\..\..\GUCE\trunk
  cd "%GU_BATCHSTARTDIR%"
)

ECHO GUCE_HOME="%GUCE_HOME%"

ECHO *** Invoking GUCE's CMakeCommon ***

SET SKIP_GUCE_CMAKELISTSFILEGENERATION=TRUE
cd %GUCE_HOME%\projects\CMake\
CALL %GUCE_HOME%\projects\CMake\CMakeCommon.bat
cd "%GU_BATCHSTARTDIR%"

ECHO *** Generate CMakeLists.txt files ***


cd..
cd..
SET GU_HOME=%CD%
ECHO GU_HOME = %GU_HOME%
cd "%GU_BATCHSTARTDIR%"

SET NOPAUSE=TRUE
CALL GenerateCMakeLists.bat

SET OUTPUTDIR=%GU_HOME%\common\bin
SET SRCROOTDIR=%GU_HOME%

ECHO CMake source dir = %SRCROOTDIR%
ECHO CMake output root is = %OUTPUTDIR%

cd "%GU_BATCHSTARTDIR%"

IF NOT DEFINED NOPAUSE (
  PAUSE
)


































