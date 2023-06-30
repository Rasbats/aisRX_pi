call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
@echo off

set CONFIGURATION=RelWithDebInfo

set wxWidgets_ROOT_DIR=D:\Documents\MyRIS\aisRX_pi\cache\wxWidgets-3.2.1
set wxWidgets_LIB_DIR=D:\Documents\MyRIS\aisRX_pi\cache\wxWidgets-3.2.1\lib\vc14x_dll

SET PATH=%PATH%;%WXWIN%;%wxWidgets_LIB_DIR%;C:\Program Files (x86)\Poedit\Gettexttools\bin;
set PATH=C:\Program Files\Cmake\bin;%PATH%

if exist build (rmdir /s /q build)
mkdir build && cd build

cmake -A Win32 -G "Visual Studio 17 2022" ^
        -DCMAKE_GENERATOR_PLATFORM=Win32 ^
        -DwxWidgets_LIB_DIR=%wxWidgets_LIB_DIR% ^
        -DwxWidgets_ROOT_DIR=%wxWidgets_ROOT_DIR% ^
        -DOCPN_TARGET_TUPLE=msvc-wx32;10;x86_64 ^
        ..

cmake --build . --target tarball --config %CONFIGURATION%

cmd /k
