#include "GeometrySystem.h"
#include <ECS/ECSWorld.h>
#include <iostream>
#include <sstream>

GeometrySystem::~GeometrySystem()
{
    std::cout << "=== GeometrySystem exited ===\n";
    mainloopThread->join();
}

GeometrySystem &GeometrySystem::get()
{
    static GeometrySystem instance;
    return instance;
}

void GeometrySystem::start()
{
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&GeometrySystem::stop>(this);
    std::cout << "GeometrySystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&GeometrySystem::mainloop, this);
}

void GeometrySystem::stop()
{
    running = false;
}

void GeometrySystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> GeometrySystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i && running);
}