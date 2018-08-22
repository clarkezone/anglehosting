@echo off
::create dependencies dir if not exist

set DEPENDSDIREXISTS=true
if not exist %~dp0..\dependencies set DEPENDSDIREXISTS=false

if %DEPENDSDIREXISTS%==false(
    mkdir %~dp0..\dependencies
)

set ANGLEEXISTS=true
if not exist %~dp0..\dependencies\glesv2.dll set ANGLEEXISTS=false

if %ANGLEEXISTS%==false(
    PowerShell -NoProfile -ExecutionPolicy Bypass -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri https://github.com/clarkezone/angle-1/releases/download/v0.1.1/libGLESv2.zip"

   PowerShell -NoProfile -ExecutionPolicy Bypass -Command "libGLESv2.zip -DestinationPath Angle"

)


