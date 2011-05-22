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


IF NOT DEFINED GUCE_HOME (
  ECHO WARNING: GUCE_HOME not defined, falling back to relative path guesswork
  SET GUCE_HOME=%CD%\..\..\..\..\GUCE\trunk
)
ECHO GUCE_HOME=%GUCE_HOME%

IF NOT DEFINED GUCE_HOME (
  ECHO Error: GUCE_HOME is not defined
  GOTO END
)

GOTO FIND_GU_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR


REM -----------------------------------------------------

:FIND_GU_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR

SET GENERATORPATH=%GU_THEBATCHDIR%\..\..\common\bin\MVC9\bin\Debug
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST="%GENERATORPATH%\%GENERATOREXE%"

ECHO Test path = "%EXETEST%"
IF EXIST "%EXETEST%" (
  ECHO Warning: Using GU CMake debug MVC9 development version of the ProjectGenerator
  GOTO RUN_CMAKELISTGENERATOR
)

IF NOT EXIST "%EXETEST%" (
  ECHO Cannot locate GU CMake MVC9 debug development version of the ProjectGenerator, trying GUCE
  GOTO FIND_GUCE_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR
)

cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR

REM -----------------------------------------------------

:FIND_GUCE_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR

SET GENERATORPATH=%GUCE_HOME%\..\..\common\bin\MVC9\bin\Debug
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST="%GENERATORPATH%\%GENERATOREXE%"

ECHO Test path = %EXETEST%
IF EXIST %EXETEST% (
  ECHO Warning: Using GUCE CMake debug MVC9 development version of the ProjectGenerator
  GOTO RUN_CMAKELISTGENERATOR
)

IF NOT EXIST %EXETEST% (
  ECHO Cannot locate GUCE CMake MVC9 debug development version of the ProjectGenerator, trying GUCEF
  GOTO FIND_GUCEF_OLD_SLN_DEBUG_CMAKELISTGENERATOR
)

cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR

REM -----------------------------------------------------

:FIND_GUCEF_OLD_SLN_DEBUG_CMAKELISTGENERATOR

SET GENERATORPATH=%GUCEF_HOME%\common\bin\Debug_MVC9
SET GENERATOREXE=ProjectGenerator_d.exe
SET EXETEST=%GENERATORPATH%\%GENERATOREXE%

ECHO Test path = %EXETEST%
IF EXIST %EXETEST% (
  ECHO Warning: Using GUCEF Debug_MVC9 development version of the ProjectGenerator
  GOTO RUN_CMAKELISTGENERATOR
)

IF NOT EXIST %EXETEST% (
  ECHO Cannot locate old GUCEF MVC9 debug development version of the ProjectGenerator, trying CMake version
  GOTO FIND_GUCEF_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR
)

cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR

REM -----------------------------------------------------

:FIND_GUCEF_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR

SET GENERATORPATH=%GUCEF_HOME%\common\bin\MVC9\bin\Debug
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST=%GENERATORPATH%\%GENERATOREXE%

ECHO Test path = %EXETEST%
IF EXIST %EXETEST% (
  ECHO Warning: Using GUCEF CMake debug MVC9 development version of the ProjectGenerator
  GOTO RUN_CMAKELISTGENERATOR
)

IF NOT EXIST %EXETEST% (
  ECHO Cannot locate GUCEF CMake MVC9 debug development version of the ProjectGenerator, trying GUCE
  GOTO FIND_GUCE_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR
)

cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR

REM -----------------------------------------------------

:FIND_GUCE_CMAKE_SLN_DEBUG_CMAKELISTGENERATOR

SET GENERATORPATH=%GUCE_HOME%\common\bin\MVC9\bin\Debug
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST=%GENERATORPATH%\%GENERATOREXE%

ECHO Test path = %EXETEST%
IF EXIST %EXETEST% (
  ECHO Warning: Using GUCE CMake debug MVC9 development version of the ProjectGenerator
  GOTO RUN_CMAKELISTGENERATOR
)

IF NOT EXIST %EXETEST% (
  ECHO Cannot locate GUCE CMake MVC9 debug development version of the ProjectGenerator, trying release version
  GOTO FIND_GUCEF_RELEASE_CMAKELISTGENERATOR
)

cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR


REM -----------------------------------------------------

:FIND_GUCEF_RELEASE_CMAKELISTGENERATOR

SET GENERATORPATH=%GUCEF_HOME%\tools\ProjectGenerator\bin\ReleasedBins\Win32\5April2011
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST="%GENERATORPATH%\%GENERATOREXE%"

ECHO Test path = %EXETEST%
IF EXIST %EXETEST% (
  ECHO Using released version of ProjectGenerator dated 5th April 2011
  GOTO RUN_CMAKELISTGENERATOR
)

IF NOT EXIST %EXETEST% (
  ECHO Error: Unable to locate GUCEF's released ProjectGenerator, trying GUCE release version
  GOTO FIND_GUCE_RELEASE_CMAKELISTGENERATOR
)
    
cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR


REM -----------------------------------------------------

:FIND_GUCE_RELEASE_CMAKELISTGENERATOR

SET GENERATORPATH=%GUCE_THEBATCHDIR%\..\..\tools\ProjectGenerator\bin\ReleasedBins\Win32\5April2011
SET GENERATOREXE=ProjectGenerator.exe
SET EXETEST=%GENERATORPATH%\%GENERATOREXE%

ECHO Test path = %EXETEST%
IF NOT EXIST %EXETEST% (
  ECHO Error: Unable to locate GUCE's ProjectGenerator, cannot locate any kind of generator
  GOTO END
)

cd %GU_THEBATCHDIR%
GOTO RUN_CMAKELISTGENERATOR


REM -----------------------------------------------------


:RUN_CMAKELISTGENERATOR

SET PATH=%GENERATORPATH%;%PATH%

cd %GU_THEBATCHDIR%
cd..
cd..

IF NOT DEFINED GU_HOME (
  ECHO GU environment variable not found, setting it
  SET GU_HOME=%CD%
  ECHO GU_HOME=%CD%
)

%GENERATOREXE% *rootDir=%GUCEF_HOME%* *rootDir=%GUCE_HOME%* *rootDir=%GU_HOME%* *outputDir=%GU_HOME%* *cmakgen:TemplateDir=%GUCEF_HOME%\projects\CMake\ProjectGenTemplates* *generators=cmake* *dirsToIgnore=.svn;_svn* *projectName=GU*
cd %GU_THEBATCHDIR%
GOTO END

REM -----------------------------------------------------

:END

IF NOT DEFINED NOPAUSE (
  PAUSE
)