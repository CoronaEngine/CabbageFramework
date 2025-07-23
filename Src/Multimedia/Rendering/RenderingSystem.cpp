#include "RenderingSystem.h"
#include <ECS/ECSWorld.h>
#include <iostream>
#include <sstream>
#include <thread>

RenderingSystem::~RenderingSystem()
{
    std::cout << "=== RenderingSystem exited ===\n";
    mainloopThread->join();
}

RenderingSystem &RenderingSystem::get()
{
    static RenderingSystem instance;
    return instance;
}

void RenderingSystem::start()
{
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&RenderingSystem::stop>(this);
    std::cout << "RenderingSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&RenderingSystem::mainloop, this);
}

void RenderingSystem::stop()
{
    running = false;
}

void RenderingSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> RenderSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i && running);
}