#include "ResourceSystem.h"
#include "ECS/Components.h"
#include <iostream>

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

const stbi_uc *ResourceSystem::loadTexture(const std::string &path)
{
    stbi_uc *ret = stbi_load(path.c_str(), nullptr, nullptr, nullptr, 0);
    return nullptr;
}

const aiScene *ResourceSystem::loadAnimation(const std::string &path)
{
    return nullptr;
}

void ResourceSystem::mainloop()
{
    static int i = 1;
    std::cout << "ResourceSystem::mainloop() tick " << i++ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}