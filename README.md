# particle-simulator-webgl

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

## Description

This is a particle simulator written in C++ and compiled to WebGL using
Emscripten. It is a port of my particle simulator written in C++ and OpenGL which can be found [here](https://github.com/Im-Rises/ParticleSimulator).

You can find the build of the project [here](https://im-rises.github.io/particle-simulator-webgl/).

> **Note:**   
> This project is still in development.

## Images

PLACEHOLDER

## Videos

PLACEHOLDER

## Building

To build the project, you need to use a UNIX system, like Ubuntu or if you're on Windows you can use WSL.
Then you have to install Emscripten. You can find
instructions on how to install Emscripten here:  
<https://emscripten.org/docs/getting_started/downloads.html>

You also need to have CMake installed. You can find instructions on how to
install CMake here:  
<https://cmake.org/install/>

Once you have Emscripten and CMake installed run this command in the project root directory:

```bash
emcmake cmake .
```

Then run this command in the same directory:

```bash
emmake make
```

[//]: # (The build artifacts will be generated in the `build-commandline` directory.)


## To test the website locally

To test the website locally, you need to have Python installed. You can find instructions on how to install Python here:

<https://www.python.org/downloads/>

Once you have Python installed, run this command in the project build directory:

```bash
python -m http.server
```

Then open your browser and go to this address:

<http://localhost:8000/>

## GitHub Actions

This project uses GitHub Actions to build the project and deploy it to GitHub

[![CodeQL](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/codeql.yml)
[![CMake](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cmake.yml)
[![flawfinder](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/flawfinder.yml)
[![cpp-linter](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cpp-linter.yml)
[![Emscripten-CMake](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/emscripten-cmake.yml/badge.svg)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/emscripten-cmake.yml)
[![pages-build-deployment](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/pages/pages-build-deployment)

The project is set with a set of different scripts:

- CodeQL: This script is used to check the code for security issues.
- CMake: This script is used to build the project.
- Cpp Cmake Publish: This script is used to publish the project on GitHub.
- Flawfinder: This script is used to check the code for security issues.
- Microsoft C++ Code Analysis: This script is used to check the code for security issues.
- Cpp Linter: This script is used to check the code for security issues.
- Emscripten CMake: This script is used to test build of the project using Emscripten toolchain.
- Pages Build Deployment: This script is used to publish the project on GitHub Pages.

## Libraries

glfw:  
<https://www.glfw.org/docs/latest/>

glm:  
<https://glm.g-truc.net/0.9.9/index.html>

glad:  
<https://glad.dav1d.de/>

stb (stb_image):  
<https://github.com/nothings/stb/blob/master/stb_image.h>

Dear ImGui:  
<https://github.com/ocornut/imgui>

OpenGL:  
<https://www.opengl.org/>

emscripten:  
<https://emscripten.org/docs/getting_started/downloads.html>

## Documentation

learnopengl (OpenGL tutorial):  
<https://learnopengl.com/In-Practice/2D-Game/Particles>

unrealistic.dev (Change CMake working directory):  
<https://unrealistic.dev/posts/setting-debug-parameters-with-cmake-tools-for-visual-studio>

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/particle-simulator-webgl)](https://github.com/Im-Rises/particle-simulator-webgl/graphs/contributors)
