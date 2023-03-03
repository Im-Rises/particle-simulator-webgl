#!/usr/bin/env bash

# Delete CMake cache directories and files in the current directory and all subdirectories

# Delete CMakeCache.txt files and CMakeLists.txt.user
find . -type f -name 'CMakeCache.txt*' -delete

# Delete CMakeFiles directories
find . -type d -name 'CMakeFiles' -exec rm -rf {} +

# Delete CMakeScripts directories
find . -type d -name 'CMakeScripts' -exec rm -rf {} +

# Delete Testing directories
find . -type d -name 'Testing' -exec rm -rf {} +

# Delete Makefile files
find . -type f -name 'Makefile' -delete

# Delete cmake_install.cmake files
find . -type f -name 'cmake_install.cmake' -delete

# Delete install_manifest.txt files
find . -type f -name 'install_manifest.txt' -delete

# Delete compile_commands.json files
find . -type f -name 'compile_commands.json' -delete

# Delete CTestTestfile.cmake files
find . -type f -name 'CTestTestfile.cmake' -delete

# Delete _deps directories
find . -type d -name '_deps' -exec rm -rf {} +

# Delete .cmake directories
find . -type d -name '.cmake' -exec rm -rf {} +

# Delete files ending with .cbp
find . -type f -name '*.cbp' -delete

# Delete directories ending with .cbp
find . -type d -name 'cmake-build-*' -exec rm -rf {} +
