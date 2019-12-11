@echo off

if "%~1"=="" goto BLANK
if "%~2"=="" goto BLANK

if "%~2"=="32" goto BADARCHITECTURE

set DEPENDSDIREXISTS=true
if not exist %~dp0..\dependencies set DEPENDSDIREXISTS=false

if %DEPENDSDIREXISTS% == false (
    mkdir %~dp0..\dependencies
)

set ANGLEEXISTS=true
if not exist %~dp0..\dependencies\Angle\libglesv2.dll set ANGLEEXISTS=false

if %ANGLEEXISTS%==false (
    PowerShell -NoProfile -ExecutionPolicy Bypass -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -UseBasicParsing -Uri https://github.com/clarkezone/angle-1/releases/download/v0.1.1/libGLESv2.zip -OutFile "%~dp0..\dependencies\libGLESv2.zip
    PowerShell -NoProfile -ExecutionPolicy Bypass -Command "Expand-Archive -LiteralPath %~dp0..\dependencies\libGLESv2.zip -DestinationPath "%~dp0..\dependencies\Angle
    DEL %~dp0..\dependencies\libGLESv2.zip
) else (
    ECHO Angle dependencies found.
)

goto DONE

:ERROR
exit /b 1

:BADARCHITECTURE
ECHO At present only 64bit dependencies are available, please build using x64 configuration
exit /b 2

:BLANK

ECHO syntax: getangle.bat projectroot processorarchitecture

:DONE

