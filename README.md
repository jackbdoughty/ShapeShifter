# README 
## Introduction

Hi! This is a project I made as part of my ALevel Computer Science coursework, it acts as an investigation into three-dimensional computer graphics.

## Installation

Installation is fairly straitforward using CMake for Linux, Windows and MacOS platforms, the exception being that MacOS requires a couple extra steps.

### Linux and Windows

Make sure before starting that CMake and preferably OpenGL is installed correctly.

1) Download and extract the source files from the repository. It is best not to rearrange the file structure of the source files as this could cause dependancy issues. 
2) Open a terminal and change the working directory to ShapeShifter.
```
cd <path_to>/ShapeShifter
```
3) Make a new directory and make that your working directory. It can be called anything as this will just be the build directory for CMake. I usually name it 'CMake'.
```
mkdir CMake
cd ./CMake
```
4) Build and compile using CMake. This method below will use your default C compiler, if you need additional build arguments see the [CMake documentation](https://cmake.org/cmake/help/latest/manual/cmake.1.html).
```
cmake ..
cmake --build .
```
5) The executable will be stored under `<path_to>/ShapeShifter/bin`.

### MacOS

The installation is very much the same except the executable must be ran via the command line until a patch for this is released.

1) Perform steps 1-4 in the above section.
2) Navigate to the new `bin` diretory where the excecutable is, and run it.
```
cd ../bin
./ShapeShifter
```
## How to Use

- Simply click and drag the shape onscreen to rotate it. The scroll-wheel / track pad can be used to zoom in/out.
- The menu on the far left of the screen is used to control all the properties of the shape. It's best to explore all the options :).
- Use `esc` or the exit button to leave the app.
- Each axes is labelled with a colour. <span style="color: red">`x` is red</span>, <span style="color: green">`y` is green</span> and <span style="color: blue">`z` is blue</span>.