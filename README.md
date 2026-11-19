# Sonic 3 Retro Engine

An original C++20 engine project inspired by the 2D platforming technology and gameplay systems of the Retro Engine-era Sonic games.

This repository does not contain Sega or Headcannon source code, proprietary game data, or extracted assets. Use only assets you created or are authorized to use.

## Milestone 1: Engine foundation
- C++20 application entry point
- SDL3 window, renderer, event loop, and frame timing
- CMake build configuration
- GitHub Actions checks for Windows and Linux

## Build
Requirements: CMake 3.24+, a C++20 compiler, and internet access for CMake to download SDL3.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Roadmap
1. SDL3 platform layer and game loop
2. Input abstraction and fixed-step simulation
3. Sprite animation and rendering
4. Tile maps and collision
5. Momentum-based player physics
6. Objects, enemies, rings, and level systems
7. Audio, menus, save data, and platform polish

Independent implementation; not an official Sonic product and not affiliated with Sega or Headcannon.