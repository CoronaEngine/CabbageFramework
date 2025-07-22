#include "ResourceSystem.h"
#include "Components.h"

ResourceSystem &ResourceSystem::get()
{
    static ResourceSystem instance;
    return instance;
}

const entt::entity ResourceSystem::loadScene(entt::registry &registry, const std::string &path)
{
    return entt::null;
}

const entt::entity ResourceSystem::loadModel(entt::registry &registry, const std::string &path)
{
    return entt::null;
}

const entt::entity ResourceSystem::loadTexture(entt::registry &registry, const std::string &path)
{
    return entt::null;
}

const entt::entity ResourceSystem::loadAnimation(entt::registry &registry, const std::string &path)
{
    return entt::null;
}