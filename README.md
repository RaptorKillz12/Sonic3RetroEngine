# Sonic3RetroEngine

This repository is the build and development workspace for a Sonic 3-style project based on the open-source **RSDKv5 Decompilation** engine.

## Engine source

The upstream engine is maintained at:
https://github.com/RSDKModding/RSDKv5-Decompilation

The GitHub Actions workflow checks out that repository recursively (including its required submodules), then builds the standalone RSDKv5U engine for Windows and Linux.

**This repository does not include Sonic game code or copyrighted game assets.** The engine by itself is not a finished Sonic 3 game. Game logic and compatible, legally obtained data must be supplied separately.

## Build outputs

Open the Actions tab and select the latest **Build RSDKv5 Engine** run. Successful builds are uploaded as workflow artifacts:

- RSDKv5-Windows
- RSDKv5-Linux

## Android

The upstream project has a separate Android Gradle/NDK project. Its documented setup expects a game project linked into the Android JNI build. We will add the Android APK workflow once the compatible game module and its required assets/data layout are in place; building the engine executable alone does not produce a playable Android game.

## Upstream build settings

- Engine revision: RSDKv5U (RETRO_REVISION=3)
- Renderer: OpenGL (RETRO_SUBSYSTEM=OGL)
- Mod loader: enabled
