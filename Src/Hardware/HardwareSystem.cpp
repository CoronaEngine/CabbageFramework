#include "HardwareSystem.h"
#include <ECS/ECSWorld.h>
#include <iostream>
#include <sstream>

HardwareSystem::~HardwareSystem()
{
    std::cout << "=== HardwareSystem exited ===\n";
    mainloopThread->join();
}

HardwareSystem &HardwareSystem::get()
{
    static HardwareSystem instance;
    return instance;
}

void HardwareSystem::start()
{
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&HardwareSystem::stop>(this);
    std::cout << "HardwareSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&HardwareSystem::mainloop, this);
}

void HardwareSystem::stop()
{
    running = false;
}

void HardwareSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> HardwareSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i && running);
}