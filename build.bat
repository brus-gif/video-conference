@echo off
rem ============================================================
rem  MeetingGrid build script (Windows + MSVC + Qt 6.11.1)
rem  Usage:  build.bat             Release build
rem          build.bat Debug       Debug build
rem ============================================================

setlocal

rem ---- 只改这两处路径 ----
set "VSDIR=C:\Program Files\Microsoft Visual Studio\2022\Community"
set "QTDIR=C:\Qt\6.11.1\msvc2022_64"
rem -------------------------

set "VCVARS=%VSDIR%\VC\Auxiliary\Build\vcvars64.bat"

if not exist "%VCVARS%" (
    echo [ERROR] vcvars64.bat not found: %VCVARS%
    exit /b 1
)
if not exist "%QTDIR%\lib\cmake\Qt6\Qt6Config.cmake" (
    echo [ERROR] Qt6 CMake config not found: %QTDIR%
    exit /b 1
)

call "%VCVARS%" >nul

set "BUILD_TYPE=Release"
if /I "%~1"=="Debug" set "BUILD_TYPE=Debug"

cd /d "%~dp0"

echo [1/2] CMake configure ...
rem ---- 去掉 -G Ninja 和 -DCMAKE_MAKE_PROGRAM，改用 VS 生成器 ----
cmake -S . -B build -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_PREFIX_PATH=%QTDIR%
if errorlevel 1 exit /b 1

echo [2/2] Build ...
rem ---- 构建时指定配置，输出到 build\Release 或 build\Debug ----
cmake --build build --config %BUILD_TYPE%
if errorlevel 1 exit /b 1

echo.
echo Build OK: %~dp0build\%BUILD_TYPE%\MeetingGrid.exe
endlocal