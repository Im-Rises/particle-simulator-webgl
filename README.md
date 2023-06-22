# particle-simulator-webgl

<p align="center">
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/226524871-c73aa62f-d191-42d3-a1b9-ebbfc216a7bb.png" alt="webglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

## Description

This is a particle simulator written in C++ and compiled to WebGL2 using
Emscripten. It is a port of my particle simulator written in C++ and OpenGL which can be
found [here](https://github.com/Im-Rises/ParticleSimulator).
This version is displaying 1 000 000 particles (which can be changed using the integrated UI).
On the contrary of the Desktop version, this version is using a Transform Feedback buffering instead of a SSBO, WebGL2
is limited to OpenGL ES 3.0 which doesn't support SSBOs.

## 🚀🚀[you can try the webgl build online by clicking here](https://im-rises.github.io/particle-simulator-webgl/) 🚀🚀

> **Note**  
> The website work for desktop and mobile, but on mobile you won't be able to use the UI to change the simulation
> parameters.

## Images

![Screenshot 1](https://user-images.githubusercontent.com/59691442/225486502-770ec82b-562a-452b-9ef2-f2a68c6fef18.png)
![Screenshot 2](https://user-images.githubusercontent.com/59691442/225486505-e8ccd756-056a-4507-917a-6be6bd8decb9.png)

## Videos

https://user-images.githubusercontent.com/59691442/225486109-9fb793d5-878f-430b-b418-938535038aed.mp4

## Dependencies

- OpenGL version: 4.6.0
- GLSL version: 4.60
- GLFW version: 3.3.8
- Glad version: 0.1.36
- ImGui version: 1.89.6 WIP
- GLM version: 0.9.8
- Emscripten: 3.1.37

## Building

To build the project, you need to use a UNIX system, like Ubuntu or if you're on Windows you can use WSL.
Then you have to install Emscripten. You can find
instructions on how to install Emscripten here:  
<https://emscripten.org/docs/getting_started/downloads.html>

You also need to have CMake and make installed. You can find instructions on how to
install CMake here:  
<https://cmake.org/install/>

Make can be installed by running this command in the terminal:

```bash
sudo apt install make
```

Once you have Emscripten and CMake installed run this command in the project root directory:

```bash
emcmake cmake .
```

Then run this command in the same directory:

```bash
emmake make
```

## To test the website locally

To test the website locally, you need to have Python installed. You can find instructions on how to install Python here:

<https://www.python.org/downloads/>

Once you have Python installed, run this command in the project build directory:

```bash
python -m http.server
```

Then open your browser and go to this address:

<http://localhost:8000/>

## Controls

The speed and some parameters can be modified directly in the ImGui windows.

| Action                   | Key                                                |
|--------------------------|----------------------------------------------------|
| Translate camera         | WASD (← → ↑ ↓)                                     |
| Pause/Resume             | P                                                  |
| Move up/down camera      | SPACE/SHIFT                                        |
| Rotate camera            | Right Mouse Button + Mouse movement                |
| Toggle UI visible/hidden | F1                                                 |
| Fullscreen               | F11                                                |
| Drag particles           | Left Mouse Button + Mouse movement OR Touch screen |

> **Note**
> The translation commands are set for QWERTY keyboard layout.

## GitHub Actions

This project uses GitHub Actions to build the project and deploy it to GitHub

[![CodeQL](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/codeql.yml)
[![CMake](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cmake.yml)
[![flawfinder](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/flawfinder.yml)
[![cpp-linter](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/cpp-linter.yml)
[![Emscripten-CMake](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/emscripten-cmake.yml/badge.svg)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/emscripten-cmake.yml)
[![Emscripten-Publish](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/emscripten-publish.yml/badge.svg)](https://github.com/Im-Rises/particle-simulator-webgl/actions/workflows/emscripten-publish.yml)

The project is set with a set of different scripts:

- CodeQL: This script is used to check the code for security issues.
- CMake: This script is used to build the project.
- Cpp Cmake Publish: This script is used to publish the project on GitHub.
- Flawfinder: This script is used to check the code for security issues.
- Microsoft C++ Code Analysis: This script is used to check the code for security issues.
- Cpp Linter: This script is used to check the code for security issues.
- Emscripten CMake: This script is used to test build of the project using Emscripten toolchain.
- Emscripten-Publish: This script build to webgl and publish the project on GitHub Pages.

## Libraries

glfw:  
<https://www.glfw.org/docs/latest/>

glm:  
<https://glm.g-truc.net/0.9.9/index.html>

glad:  
<https://glad.dav1d.de/>

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

OpenGL ES 3.0 Reference Pages:  
<https://www.khronos.org/registry/OpenGL-Refpages/es3.0/>

Wikipedia (OpenGL versions):  
<https://en.wikipedia.org/wiki/OpenGL_Shading_Language>

codepen (WebGL 2 Particles):  
<https://codepen.io/stopyransky/pen/gBoQoO>

nopjiap (WebGL 2 Particles):  
<https://github.com/nopjia/particles-mrt>

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/particle-simulator-webgl)](https://github.com/Im-Rises/particle-simulator-webgl/graphs/contributors)
