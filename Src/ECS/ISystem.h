#pragma once

#include <entt/entt.hpp>

class ISystem
{
  public:
    ISystem(const entt::entity &ownerScene = entt::null);
    virtual ~ISystem();

    virtual void registerEvents(entt::dispatcher &dispatcher) = 0;
    virtual void onStart() = 0;
    virtual void onQuit() = 0;

    virtual const char *getName() const = 0; // 调使用的名字

  protected:
    entt::entity ownerScene;
    bool running;
};