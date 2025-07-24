#pragma once

#include <entt/entt.hpp>

class ISystem
{
  public:
    explicit ISystem(const entt::entity &ownerScene = entt::null);
    virtual ~ISystem();

    virtual void registerEvents(entt::dispatcher &dispatcher) = 0;
    virtual void onStart() = 0;
    virtual void onQuit() = 0;

    virtual const char *getName() const = 0; // 调使用的名字

  private:
    void _onStart();
    void _onQuit();

  protected:
    entt::entity ownerScene;
    bool running;
};