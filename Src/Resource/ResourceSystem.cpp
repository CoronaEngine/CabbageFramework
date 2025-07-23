#include "ResourceSystem.h"
#include "ECS/ECSWorld.h"
#include <stb_image.h>

#include <iostream>
#include <sstream>

ResourceSystem::~ResourceSystem()
{
    std::cout << "=== ResourceSystem exited ===\n";
    mainloopThread->join();
}

ResourceSystem &ResourceSystem::get()
{
    static ResourceSystem instance;
    return instance;
}

const aiScene *ResourceSystem::loadScene(const std::string &path)
{
    return nullptr;
}

const aiScene *ResourceSystem::loadModel(const std::string &path)
{
    return nullptr;
}

const unsigned char *ResourceSystem::loadTexture(const std::string &path)
{
    return nullptr;
}

const aiScene *ResourceSystem::loadAnimation(const std::string &path)
{
    return nullptr;
}

void ResourceSystem::start()
{
    ECSWorld::get().getDispatcher().sink<EngineStopEvent>().connect<&ResourceSystem::stop>(this);
    std::cout << "ResourceSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&ResourceSystem::mainloop, this);
}

void ResourceSystem::stop()
{
    running = false;
}

void ResourceSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i && running);
}