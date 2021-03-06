@echo off

SET GU_THEBATCHDIR=%CD%

IF NOT DEFINED GUCEF_HOME (
  ECHO WARNING: GUCEF_HOME not defined, falling back to relative path guesswork
  SET GUCEF_HOME=%CD%\..\..\..\..\GUCEF\trunk
)
ECHO GUCEF_HOME=%GUCEF_HOME%

IF NOT DEFINED GUCEF_HOME (
  ECHO Error: GUCEF_HOME is not defined
  GOTO END
)

GOTO FIND_GUCEF_CMAKE_SLN_DEBUG_MVC9_PROJECTGENERATOR


REM -----------------------------------------------------

:FIND_GUCEF_RELEASE_PROJECTGENERATOR

SET GENERATORPATH=%GUCEF_HOME%\tools\ProjectGenerator\bin\ReleasedBins\Win32\5April2011\
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST=%GENERATORPATH%\%GENERATOREXE%

ECHO Test path = "%EXETEST%"
IF EXIST "%EXETEST%" (
  ECHO Using released version of ProjectGenerator dated 5th April 2011
  GOTO RUN_PROJECTGENERATOR
)

IF NOT EXIST "%EXETEST%" (
  ECHO Error: Unable to locate GUCEF released ProjectGenerator
  GOTO END
)
    
cd "%GU_THEBATCHDIR%"
GOTO RUN_PROJECTGENERATOR

REM -----------------------------------------------------

:FIND_GUCEF_CMAKE_SLN_DEBUG_MVC9_PROJECTGENERATOR

SET GENERATORPATH=%GUCEF_HOME%\common\bin\MVC9\bin\Debug
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST=%GENERATORPATH%\%GENERATOREXE%

ECHO Test path = "%EXETEST%"
IF EXIST "%EXETEST%" (
  ECHO Warning: Using CMake debug development version of the ProjectGenerator
  GOTO RUN_PROJECTGENERATOR
)

IF NOT EXIST "%EXETEST%" (
  ECHO Cannot locate CMake debug development version of the ProjectGenerator
  GOTO FIND_GUCEF_RELEASE_PROJECTGENERATOR
)

cd "%GU_THEBATCHDIR%"
GOTO RUN_PROJECTGENERATOR


REM -----------------------------------------------------

:RUN_PROJECTGENERATOR

SET PATH="%GENERATORPATH%";%PATH%

IF NOT DEFINED GUCE_HOME (
  ECHO WARNING: GUCE_HOME not defined, falling back to relative path
  SET GUCE_HOME=%GU_THEBATCHDIR%\..\..\..\..\GUCE\trunk
)

IF NOT DEFINED GU_HOME (
  ECHO WARNING: GU_HOME not defined, falling back to relative path
  SET GU_HOME=%GU_THEBATCHDIR%\..\..
)

ECHO GUCE_HOME = %GUCE_HOME%
ECHO GU_HOME = %GU_HOME%

%GENERATOREXE% *rootDir=%GUCEF_HOME%* *rootDir=%GUCE_HOME%* *rootDir=%GU_HOME%* *outputDir=%GU_HOME%* *generators=androidmake* *dirsToIgnore=.svn;_svn* *projectName=GU*
cd "%GU_THEBATCHDIR%"
GOTO END


REM -----------------------------------------------------

:END

IF NOT DEFINED NOPAUSE (
  PAUSE
)