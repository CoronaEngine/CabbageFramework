#pragma once

#include <entt/entt.hpp>
#include <concurrencpp/concurrencpp.h>

class ResourceSystem
{
  public:
    static ResourceSystem &get();

  private:
    ResourceSystem();

  public:
    const entt::entity loadScene(entt::registry &registry, const std::string &path);
    const entt::entity loadTexture(entt::registry &registry, const std::string &path);
    const entt::entity loadModel(entt::registry &registry, const std::string &path);
    const entt::entity loadAnimation(entt::registry &registry, const std::string &path);
};