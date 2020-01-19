New-Item -ItemType Directory -Force -Path C:\src\github.com\clarkezone

push-location C:\src\github.com\clarkezone
git clone https://github.com/clarkezone/angle.git
#start-process "git" "clone https://github.com/clarkezone/angle.git" -wait
set-location angle
git checkout UniversalCompositorNativeWindow
$env:DEPOT_TOOLS_WIN_TOOLCHAIN=0
python scripts/bootstrap.py
write-output "Calling gclient"
gclient sync
pop-location