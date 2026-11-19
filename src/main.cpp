#include "engine/Engine.hpp"
int main(int argc, char** argv)
{
    (void)argc; (void)argv;
    retro::Engine engine;
    if (!engine.initialize()) return 1;
    engine.run();
    engine.shutdown();
    return 0;
}
