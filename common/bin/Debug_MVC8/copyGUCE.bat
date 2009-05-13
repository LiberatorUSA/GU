copy %GUCEF_HOME%\common\bin\Debug_MVC8\*.dll %GUCE_HOME%\common\bin\Debug_MVC8
mkdir %GUCE_HOME%\common\bin\Debug_MVC8\plugins
copy %GUCEF_HOME%\common\bin\Debug_MVC8\plugins\*.dll %GUCE_HOME%\common\bin\Debug_MVC8\plugins
copy %OGRE_HOME%\lib\*.dll %~dp0
copy %GUCE_HOME%\common\bin\Debug_MVC8\*.dll %~dp0
mkdir %~dp0\plugins
copy %GUCE_HOME%\common\bin\Debug_MVC8\plugins\*.dll %~dp0\plugins
pause
