#pragma once
#include <SDL3/SDL.h>
namespace retro {
class Engine {
public:
    Engine() = default;
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    bool initialize();
    void run();
    void shutdown();
private:
    void processEvents();
    void update(double deltaSeconds);
    void render();
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    bool running_ = false;
};
}
