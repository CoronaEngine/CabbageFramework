#include "AudioSystem.h"
#include <ECS/ECSWorld.h>
#include <iostream>
#include <sstream>

AudioSystem::~AudioSystem()
{
    std::cout << "=== AudioSystem exited ===\n";
    mainloopThread->join();
}

AudioSystem &AudioSystem::get()
{
    static AudioSystem instance;
    return instance;
}

void AudioSystem::start()
{
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&AudioSystem::stop>(this);
    std::cout << "AudioSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&AudioSystem::mainloop, this);
}

void AudioSystem::stop()
{
    running = false;
}

void AudioSystem::mainloop()
{
    static int i = 1;
    do
    {
        ECSWorld::get().submitTask([this] {
            testTask(i);
        });
        ECSWorld::get().submitTask([this] {
            testTask2();
        });
        ECSWorld::get().submitTask([this] {
            testTask(i * 2);
        });
        ECSWorld::get().submitTask([this] {
            testTask(i * 3);
        });
        ECSWorld::get().submitTask([this] {
            testTask(i * 4);
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i && running);
}