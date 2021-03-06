@echo off
setlocal

set DEV=C:/Dev
set GOML=%DEV%/getoffmylawn/trunk
set KICKIT=%GOML:/=\%\KickIt.bat

call %KICKIT% Init

call %KICKIT% Lib glm %DEV%/3rdParty/glm-0.9.8.0
call %KICKIT% Lib SDL2 %GOML%/sdl2 %DEV%/3rdParty/SDL2-2.0.7
call %KICKIT% Lib glew %GOML%/glew %DEV%/3rdParty/glew-2.1.0
call %KICKIT% Lib Box2D %GOML%/Box2D %DEV%/3rdParty/Box2D-master
call %KICKIT% Lib lodepng %GOML%/lodepng %DEV%/3rdParty/lodepng-master
call %KICKIT% Lib assimp %GOML%/assimp %DEV%/3rdParty/assimp-5.0.0
call %KICKIT% Lib boost %GOML%/boost %DEV%/3rdParty/boost_1_60_0

call %KICKIT% Target "Visual Studio 14 2015 Win64" Win64-MSVC

endlocal
