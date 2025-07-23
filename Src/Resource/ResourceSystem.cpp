#include "ResourceSystem.h"
#include "ECS/Components.h"
#include <iostream>
#include <stb_image.h>

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

void ResourceSystem::start(std::shared_ptr<concurrencpp::thread_executor> executor)
{
    std::cout << "ResourceSystem::start() called\n";
    executor->submit([this]() {
        mainloop();
    });
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