#global
$targetroot = (get-item $PSScriptRoot).Directory.Parent.FullName
$anglebuildroot="C:\src\github.com\clarkezone\angle"
$anglebuilduwproot=$anglebuildroot+"\out\DebugUWP\"
$anglebuildwin32root=$anglebuildroot+"\out\DebugWin32\"

#uwp
$targetuwpbin = $targetroot + "dependencies\Angle\UWPBin"
$targetuwplib = $targetroot + "dependencies\Angle\UWPLib"

Write-Host $targetuwpbin
New-Item -ItemType Directory -Force -Path $targetuwpbin
Copy-Item $anglebuilduwproot"libGLESv2.dll" $targetuwpbin -Force
Copy-Item $anglebuilduwproot"libGLESv2.dll.pdb" $targetuwpbin -Force
Copy-Item $anglebuilduwproot"libegl.dll" $targetuwpbin -Force
Copy-Item $anglebuilduwproot"libegl.dll.pdb" $targetuwpbin -Force

Write-Host $targetuwplib
New-Item -ItemType Directory -Force -Path $targetuwplib
Copy-Item $anglebuilduwproot"libegl.dll.lib" $targetuwplib -Force
Copy-Item $anglebuilduwproot"libGLESv2.dll.lib" $targetuwplib -Force

#Win32
$targetwin32bin = $targetroot + "dependencies\Angle\Win32Bin"
$targetwin32lib = $targetroot + "dependencies\Angle\Win32Lib"
Write-Host $targetwin32lib
New-Item -ItemType Directory -Force -Path $targetwin32bin
Copy-Item $anglebuildwin32root"libGLESv2.dll" $targetwin32bin -Force
Copy-Item $anglebuildwin32root"libGLESv2.dll.pdb" $targetwin32bin -Force
Copy-Item $anglebuildwin32root"libegl.dll" $targetwin32bin -Force
Copy-Item $anglebuildwin32root"libegl.dll.pdb" $targetwin32bin -Force

Write-Host $targetwin32lib
New-Item -ItemType Directory -Force -Path $targetwin32lib
Copy-Item $anglebuildwin32root"libegl.dll.lib" $targetwin32lib -Force
Copy-Item $anglebuildwin32root"libGLESv2.dll.lib" $targetwin32lib -Force

#include
$targetinclude = $targetroot + 'dependencies\Angle\Include'
Write-Host $targetinclude
New-Item -ItemType Directory -Force -Path $targetinclude
Get-ChildItem -Path ($anglebuildroot+"\include\") | % { 
    Copy-Item $_.FullName $targetinclude -Recurse -force
}
