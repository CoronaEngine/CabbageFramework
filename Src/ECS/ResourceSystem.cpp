#include "ResourceSystem.h"
#include "Components.h"

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