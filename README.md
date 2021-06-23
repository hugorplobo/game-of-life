# game-of-life

![Game screenshot](https://i.imgur.com/f1MC0Nz.gif)

Conway's game of life implementation in C with Raylib.

## How it was made
The game was made in pure C with [Raylib](https://github.com/raysan5/raylib).

## How to build
There is a CMakeLists file for building with CMake, you first need the Raylib header and lib folders.

To compile Raylib, view the instructions for your operating system

- [Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
- [Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
- [MacOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS)

You can also download a Raylib release [here](https://github.com/raysan5/raylib/releases).

Once compiled or downloaded the Raylib, put the header and lib files inside the include and lib folders, respectively. After, use these commands:

```
mkdir build
cd build
cmake ..
cmake --build .
```

Note 1: If you want to build in Windows with MinGW, use `cmake .. -G "MinGW Makefiles"` instead of just `cmake ..`.
Note 2: You can use another build system instead of `cmake --build .` if you want it.

## Features

- Press the `spacebar key` to pause and unpause the game.
- While the game is paused, you can draw and erase using the `left and right mouse buttons` respectively.
- Press the `C key` to enable and disable the color mode.
- Press the `R key` to generate a new game.
- Press the `N key` to clear the entire game.

> Thank you for visiting my repository!
