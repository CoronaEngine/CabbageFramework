#include "ResourceSystem.h"
#include "ECS/Components.h"
#include <stb_image.h>

#include <iostream>
#include <sstream>

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
    std::cout << "ResourceSystem::start() called\n";
    mainloopThread = std::make_shared<std::thread>(&ResourceSystem::mainloop, this);
}

void ResourceSystem::mainloop()
{
    static int i = 1;
    do
    {
        std::stringstream msg;
        msg << std::this_thread::get_id() << " --> ResourceSystem tick " << i << "\n";
        std::cout << msg.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (++i);
}