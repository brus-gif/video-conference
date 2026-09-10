@echo off
rem ============================================================
rem  MeetingGrid Build + Deploy (one click)
rem  Usage : deploy.bat [Release|Debug] [deploy-dir]
rem  Env   : set QTDIR / VSDIR to override defaults
rem  Output: <deploy-dir>\bin\MeetingGrid.exe and MeetingGridServer.exe
rem          (Qt runtime + plugins bundled, portable to another PC)
rem ============================================================
setlocal
cd /d "%~dp0"

set "CONFIG=%~1"
if "%CONFIG%"=="" set "CONFIG=Release"
set "DEPLOY=%~2"
if "%DEPLOY%"=="" set "DEPLOY=%~dp0out\deploy\%CONFIG%"

if not defined VSDIR set "VSDIR=C:\Program Files\Microsoft Visual Studio\2022\Community"
if not defined QTDIR set "QTDIR=C:\Qt\6.11.1\msvc2022_64"

set "VCVARS=%VSDIR%\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" (
    echo [ERROR] vcvars64.bat not found: %VCVARS%
    echo Install VS2022 C++ toolset or set VSDIR to your VS root, then retry.
    exit /b 1
)
if not exist "%QTDIR%\lib\cmake\Qt6\Qt6Config.cmake" (
    echo [ERROR] Qt6 CMake config not found: %QTDIR%
    echo Install Qt msvc2022_64 or set QTDIR to your Qt dir, then retry.
    exit /b 1
)

call "%VCVARS%" >nul
if errorlevel 1 exit /b 1

rem ---- Configure (retry once after removing stale cache from another machine) ----
echo [1/4] CMake configure ... Qt="%QTDIR%"
cmake -S . -B build -DCMAKE_PREFIX_PATH="%QTDIR%" >nul 2>cmake_config_err.log
if errorlevel 1 (
    echo [INFO] configure failed. Removing stale CMakeCache.txt and retrying ...
    type cmake_config_err.log
    del /q "build\CMakeCache.txt" 2>nul
    cmake -S . -B build -DCMAKE_PREFIX_PATH="%QTDIR%" || exit /b 1
)
del /q cmake_config_err.log 2>nul

echo [2/4] Build MeetingGrid + MeetingGridServer (%CONFIG%)
cmake --build build --config %CONFIG% --target MeetingGrid MeetingGridServer || exit /b 1

echo [3/4] Install exes and deploy Qt runtime to "%DEPLOY%"
cmake --install build --config %CONFIG% --prefix "%DEPLOY%" || exit /b 1

echo [3.1] windeployqt -> MeetingGrid.exe
"%QTDIR%\bin\windeployqt.exe" --no-translations "%DEPLOY%\bin\MeetingGrid.exe" || exit /b 1

if exist "%DEPLOY%\bin\MeetingGridServer.exe" (
    echo [3.2] windeployqt -> MeetingGridServer.exe
    "%QTDIR%\bin\windeployqt.exe" --no-translations "%DEPLOY%\bin\MeetingGridServer.exe" >nul 2>&1
)
if not exist "%DEPLOY%\bin\platforms\qwindows.dll" (
    echo [ERROR] Qt platform plugin missing after deploy.
    exit /b 1
)

echo [4/4] Done.
echo.
echo Deployed to: %DEPLOY%\bin
echo.
echo How to run the networked meeting:
echo   1. Terminal A : "%DEPLOY%\bin\MeetingGridServer.exe"
echo   2. Terminal B : "%DEPLOY%\bin\MeetingGrid.exe"   (open two clients)
echo      Both click the network-meeting button, server ws://^<host-ip^>:8090
echo      (local test: ws://127.0.0.1:8090). A creates room, B joins by id.
echo      Verify video / audio / screen share / chat.
echo Tests:
echo   ctest --test-dir build -C %CONFIG% --output-on-failure
echo   node server\test\smoke_test.mjs [port]    (run while server is up)
echo.
endlocal
