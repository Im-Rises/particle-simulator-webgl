@echo off

REM Delete CMake cache directories and files in the current directory and all subdirectories

REM Define array of files and directories to delete
set to_delete[0]=CMakeCache.txt*
set to_delete[1]=CMakeLists.txt.user
set to_delete[2]=CMakeFiles
set to_delete[3]=CMakeScripts
set to_delete[4]=Testing
set to_delete[5]=Makefile
set to_delete[6]=cmake_install.cmake
set to_delete[7]=install_manifest.txt
set to_delete[8]=compile_commands.json
set to_delete[9]=CTestTestfile.cmake
set to_delete[10]=_deps
set to_delete[11]=.cmake
set to_delete[12]=*.cbp
set to_delete[13]=cmake-build-*

REM Loop through array and delete files and directories
for %%i in (%to_delete%) do (
  for /d /r %%j in (%%i) do (
    echo Deleting directory "%%~j"
    rmdir /s /q "%%~j"
  )
  for /r %%j in (%%i) do (
    echo Deleting file "%%~j"
    del /f "%%~j"
  )
)
