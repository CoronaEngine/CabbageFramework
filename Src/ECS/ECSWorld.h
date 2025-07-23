#pragma once

#include <entt/entt.hpp>
#include <ktm/ktm.h>

struct EngineStopEvent
{
};

class ECSWorld
{
  public:
    static ECSWorld &get(); // Singleton

  private:
    ECSWorld() = default;
    ECSWorld(const ECSWorld &other) = delete;
    ECSWorld &operator=(const ECSWorld &other) = delete;
    ECSWorld(const ECSWorld &&other) = delete;
    ECSWorld &operator=(const ECSWorld &&other) = delete;

  private:
    entt::registry registry;     // ECS Registry: Operate entities & component
    entt::dispatcher dispatcher; // ECS Dispatcher: Dispatch events
  public:
    entt::registry &getRegistry();
    entt::dispatcher &getDispatcher();

    void start(); // Start ECS World
};