@echo off
setlocal EnableDelayedExpansion

pushd C:\src\github.com\clarkezone\angle
set DEPOT_TOOLS_WIN_TOOLCHAIN=0
IF not EXIST Out (mkdir Out)
if not EXIST Out\DebugUWP (mkdir Out\DebugUWP)
if not EXIST Out\DebugWin32 (mkdir Out\DebugWin32)
echo # Set build arguments here. See `gn buildargs`. > Out\DebugUWP\args.gn
echo target_os = "winuwp" >> Out\DebugUWP\args.gn
echo is_clang = false^ >> Out\DebugUWP\args.gn
call gn gen out\debuguwp --sln=angle-debug --ide=vs2019
call gn gen out\debugwin32 --sln=angle-debug --ide=vs2019
popd