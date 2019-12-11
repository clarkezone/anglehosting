set ROOT=C:\src\github.com\clarkezone\angle
set UWPROOT=%ROOT%\out\DebugUWP\
set WIN32ROOT=%ROOT%\out\DebugWin32\

IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies)
IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\Angle (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies\ANGLE)
IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\Angle (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies\ANGLE\Include)
IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\UWPBin (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies\ANGLE\UWPBin)
IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\UWPBin (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies\ANGLE\UWPLib)
IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\Win32Bin (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies\ANGLE\Win32Bin)
IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\Win32Bin (mkdir C:\src\github.com\clarkezone\anglehosting\dependencies\ANGLE\Win32Lib)

IF not EXIST C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Include (
xcopy %ROOT%\include\*.* C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Include\ /s /e
)

copy %UWPROOT%libGLESv2.dll C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\UWPBin\.
copy %UWPROOT%libGLESv2.dll.pdb C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\UWPBin\.
copy %UWPROOT%libEGL.dll C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\UWPBin\.
copy %UWPROOT%libEGL.dll.pdb C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\UWPBin\.

copy %UWPROOT%libEGL.dll.lib C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\UWPLib\.
copy %UWPROOT%libGLESv2.dll.lib C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\UWPLib\.

copy %WIN32ROOT%libGLESv2.dll C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Win32Bin\.
copy %WIN32ROOT%libGLESv2.dll.pdb C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Win32Bin\.
copy %WIN32ROOT%libEGL.dll C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Win32Bin\.
copy %WIN32ROOT%libEGL.dll.pdb C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Win32Bin\.

copy %WIN32ROOT%libEGL.dll.lib C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Win32Lib\.
copy %WIN32ROOT%libGLESv2.dll.lib C:\src\github.com\clarkezone\anglehosting\dependencies\Angle\Win32Lib\.