@echo off
call getanglefork.bat
call createangletargets.bat
call buildangletargets.bat
call Powershell.exe -executionpolicy remotesigned -File copylocal.ps1