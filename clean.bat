@echo off

rem Delete CMake cache directories and files in the current directory and all subdirectories

rem Delete CMakeCache.txt files and CMakeLists.txt.user
for /r %%i in (CMakeCache.txt*) do (
    del "%%i"
)

rem Delete CMakeFiles directories
for /d /r %%i in (CMakeFiles) do (
    rd /s /q "%%i"
)

rem Delete CMakeScripts directories
for /d /r %%i in (CMakeScripts) do (
    rd /s /q "%%i"
)

rem Delete Testing directories
for /d /r %%i in (Testing) do (
    rd /s /q "%%i"
)

rem Delete Makefile files
for /r %%i in (Makefile) do (
    del "%%i"
)

rem Delete cmake_install.cmake files
for /r %%i in (cmake_install.cmake) do (
    del "%%i"
)

rem Delete install_manifest.txt files
for /r %%i in (install_manifest.txt) do (
    del "%%i"
)

rem Delete compile_commands.json files
for /r %%i in (compile_commands.json) do (
    del "%%i"
)

rem Delete CTestTestfile.cmake files
for /r %%i in (CTestTestfile.cmake) do (
    del "%%i"
)

rem Delete _deps directories
for /d /r %%i in (_deps) do (
    rd /s /q "%%i"
)

rem Delete .cmake directories
for /d /r %%i in (.cmake) do (
    rd /s /q "%%i"
)

rem Delete directories ending with .cbp
for /r %%i in (*.cbp) do (
    del "%%i"
)

rem Delete directories with name cmake-build-*
for /d /r %%i in (cmake-build-*) do (
    rd /s /q "%%i"
)
