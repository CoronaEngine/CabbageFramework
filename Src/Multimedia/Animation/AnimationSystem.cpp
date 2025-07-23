#include "AnimationSystem.h"
#include <ECS/ECSWorld.h>
#include <iostream>
#include <sstream>
#include <thread>

AnimationSystem::~AnimationSystem()
{
    std::cout << "=== AnimationSystem exited ===\n";
    mainloopThread->join();
}

AnimationSystem &AnimationSystem::get()
{
    static AnimationSystem instance;
    return instance;
}

void AnimationSystem::start()
{
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&AnimationSystem::stop>(this);
    std::cout << "AnimationSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&AnimationSystem::mainloop, this);
}

void AnimationSystem::stop()
{
    running = false;
}

void AnimationSystem::mainloop()
{
    static int i = 1;
    do
    {
        if (i % 5 == 0)
        {
            ECSWorld::get().submitTask([this] {
                testTask();
            });
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i && running);
}