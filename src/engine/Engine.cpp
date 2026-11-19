#include "Engine.hpp"
#include <cstdio>
namespace retro {
Engine::~Engine() { shutdown(); }
bool Engine::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)) {
        std::fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }
    window_ = SDL_CreateWindow("Sonic 3 Retro Engine", 960, 540, SDL_WINDOW_RESIZABLE);
    if (!window_) {
        std::fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        shutdown(); return false;
    }
    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
        std::fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        shutdown(); return false;
    }
    running_ = true;
    return true;
}
void Engine::run()
{
    Uint64 previous = SDL_GetPerformanceCounter();
    while (running_) {
        processEvents();
        const Uint64 current = SDL_GetPerformanceCounter();
        const double frequency = static_cast<double>(SDL_GetPerformanceFrequency());
        const double delta = static_cast<double>(current - previous) / frequency;
        previous = current;
        update(delta); render();
    }
}
void Engine::processEvents()
{
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) running_ = false;
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running_ = false;
    }
}
void Engine::update(double deltaSeconds) { (void)deltaSeconds; }
void Engine::render()
{
    SDL_SetRenderDrawColor(renderer_, 18, 24, 42, 255);
    SDL_RenderClear(renderer_);
    SDL_SetRenderDrawColor(renderer_, 70, 170, 255, 255);
    const SDL_FRect ground{0.0F, 430.0F, 960.0F, 110.0F};
    SDL_RenderFillRect(renderer_, &ground);
    SDL_RenderPresent(renderer_);
}
void Engine::shutdown()
{
    if (renderer_) { SDL_DestroyRenderer(renderer_); renderer_ = nullptr; }
    if (window_) { SDL_DestroyWindow(window_); window_ = nullptr; }
    SDL_Quit(); running_ = false;
}
}
