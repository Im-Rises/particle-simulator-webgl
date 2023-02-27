# Test building

## Build

Run this command in the build-emscripten directory:

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release ..
```

Example:

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release ..
```

Then run this command in the same directory:

```bash
make
```
